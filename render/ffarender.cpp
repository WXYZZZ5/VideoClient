#include "ffarender.h"
#include"queue/ffaframequeue.h"
#include"globalclock.h"
#include"queue/ffeventqueue.h"
#include"event/ffreadyevent.h"
#include"ui/ffplayerwindow.h"
#include"player/ffplayercontext.h"
#include"event/ffendevent.h"
#include"event/ffprocessevent.h"
#include"sonic/sonic.h"

FFARender::FFARender()
    :readyFlag(false),seekFlag(false),pauseFlag(false),speedFlag(false),speed(1)
{

}

FFARender::~FFARender()
{
    //唤醒所有线程，释放资源
    stop();
    close();

    if(playerCtx){
        delete playerCtx;
        playerCtx = nullptr;
    }
    if(abufOut){
        av_freep(&abufOut);
        abufOut = nullptr;
    }
}

void FFARender::close(){
    maxBufSize = -1;
    if(aOutput){
        aOutput->deleteLater();
        aOutput = nullptr;
    }
    if(aPars){
        delete  aPars;
        aPars = nullptr;
    }
    if(abuf){
        av_freep(&abuf);
        abuf = nullptr;
    }
    if(sonicCtx){
        sonicDestroyStream(sonicCtx);
        sonicCtx = nullptr;
    }

    readyFlag = false;
    seekFlag = false;
    pauseFlag = false;
    speedFlag = false;
    speed = 1;
}

void FFARender::setSpeed(float speed_)
{
    speed = speed_;
    speedFlag.store(true,std::memory_order_release);
}

/**
     * @brief 初始化音频渲染器
     * @param frmQueue_    音频帧队列（解码线程放入帧，渲染线程取出）
     * @param aDecoder_    音频解码器（用于获取音频参数）
     * @param playerWindow_ 播放器窗口（用于事件回调）
     */
void FFARender::init(FFAFrameQueue *frmQueue_, FFADecoder *aDecoder_,FFPlayerWindow* playerWindow_)
{
    frmQueue = frmQueue_;
    aDecoder = aDecoder_;

    playerCtx = new FFPlayerContext();
    playerCtx->playerWindow = playerWindow_;
    playerCtx->aRender = this;
    playerCtx->aFrmQueue = frmQueue_;
}

void FFARender::stop()
{
    m_stop = true;
    pauseFlag = false;
    pauseCond.notify_all();
}

void FFARender::pause()
{
    bool flag = pauseFlag.load(std::memory_order_acquire);
    // 原来pauseFlag为 true（暂停中），现在变为 false（恢复）
    pauseFlag.store(!flag,std::memory_order_release);
    // 如果从暂停变为恢复，唤醒条件变量
    if(flag) {
        pauseCond.notify_one();
    }
}

void FFARender::setVolume(double volume)
{
    if(aOutput){
        aOutput->setVolume(volume);
    }
}

void FFARender::wakeAllThread()
{
    pauseCond.notify_all();
}

// 渲染线程主循环
void FFARender::run()
{
    while(!m_stop){
        AVFrame* frame = frmQueue->dequeue();
        if(frame == nullptr){
            m_stop = true;
            break;
        }

        // 如果是第一帧，则初始化参数
        if(aPars == nullptr){
            initAudio();
        }

        // 如果帧没有有效数据（data[0/1/2] 全为 nullptr），则跳过（可能是空帧标记）
        if(!frame->data[0] && !frame->data[1] && !frame->data[2]){
            av_frame_free(&frame);
            continue;
        }

        // 检查暂停标志，如果暂停则等待条件变量
        if(pauseFlag.load(std::memory_order_acquire)){
            std::unique_lock<std::mutex>lock(mutex);

            pauseCond.wait(lock); // 阻塞直到被唤醒
            pauseFlag.store(false,std::memory_order_release); // 唤醒后清除暂停标志
        }

        // 调用 playAudio() 播放该帧（即写入声卡)
        playAudio(frame);

        av_frame_unref(frame);
        av_frame_free(&frame);
    }

}


void FFARender::initAudio()
{
    // 从解码器获取参数并存储到 aPars
    initAudioPars();

    clockBase = aPars->sampleSize * aPars->nbChannels * aPars->sampleRate;

    aFormat.setCodec("audio/pcm");
    aFormat.setSampleRate(aPars->sampleRate);
    aFormat.setChannelCount(aPars->nbChannels);
    aFormat.setSampleSize(16); // 硬编码 16 位（因为解码器已经重采样为 S16）
    aFormat.setSampleType(QAudioFormat::SignedInt);   // 有符号整型
    aFormat.setByteOrder(QAudioFormat::LittleEndian); // 小端序

    // 检查系统默认音频设备是否支持该格式
    deviceInfo = QAudioDeviceInfo::defaultOutputDevice();
    if (!deviceInfo.isFormatSupported(aFormat)) {
        aFormat = deviceInfo.nearestFormat(aFormat); // 取最接近的格式
    }

    // 创建音频输出对象并启动
    aOutput = new QAudioOutput(aFormat);
    aOutput->setVolume(1);
    aDevice = aOutput->start(); // 开始输出，返回 QIODevice 用于写入数据

     // 发送就绪事件，通知界面可以开始播放
    if(!readyFlag.load(std::memory_order_relaxed)){
        totalSec = aDecoder->getToalSec();
        FFEvent* event = new FFReadyEvent(playerCtx,totalSec,-1);
        FFEventQueue::getInstance().enqueue(event);
        readyFlag.store(true,std::memory_order_release);
    }
}

void FFARender::initAudioPars()
{
    // 获取目标音频格式
    FFAudioPars* tmpPars = aDecoder->getAudioPars();
    if(tmpPars == nullptr){
        return;
    }
    aPars = new FFAudioPars();
    memcpy(aPars,tmpPars,sizeof(FFAudioPars));
}

void FFARender::playAudio(AVFrame *frame)
{
    uint8_t* playBuffer = nullptr;
    // 计算帧数据大小
    int64_t bufSize = av_samples_get_buffer_size(
                nullptr,
                aPars->nbChannels,
                frame->nb_samples,
                aPars->aFormatEnum,
                1);

    // 如果当前缓冲区太小，重新分配
    if(bufSize > maxBufSize){
        maxBufSize = bufSize;
        if(abuf){
            av_freep(&abuf);
        }
        abuf = static_cast<uint8_t*>(av_mallocz(maxBufSize));
        if(!abuf){
            std::cerr << "remalloc abuf!" <<std::endl;
            return;
        }
    }

    // 拷贝原始音频数据到 abuf
    memcpy(abuf,frame->data[0],bufSize);
    playBuffer = abuf;

    // 如果速度改变，需要重新创建 Sonic 上下文（因为可能速度值已改变）
    if(speedFlag.load(std::memory_order_acquire)){
        if(sonicCtx != nullptr){
            sonicDestroyStream(sonicCtx);
        }
        sonicCtx = sonicCreateStream(aPars->sampleRate,aPars->nbChannels);

        // speed 为目标速度，pitch 和 rate 保持 1.0（不变调、不变采样率）
        sonicSetSpeed(sonicCtx,speed);
        sonicSetPitch(sonicCtx,1.0f);
        sonicSetRate(sonicCtx, 1.0f);
        speedFlag.store(false,std::memory_order_acquire);
    }

    // 判断当前播放速度偏离正常速度（1.0）的程度是否足够大（超过 0.1），超过则使用 Sonic 进行变速处理
    if(fabs(speed - 1) >= 0.1){
        // (aPars->aFormatEnum)：返回单个样本的字节数（例如 AV_SAMPLE_FMT_S16 返回 2 字节）
        // actual_out_samples:这个音频帧中包含的样本帧数量
        int actual_out_samples = bufSize /
                (aPars->nbChannels * av_get_bytes_per_sample(aPars->aFormatEnum)); //一个“样本帧”的大小

        /**
         * sonicWriteShortToStream：Sonic 库的函数，将 16 位整型交错 PCM 数据写入 Sonic 流。
         * 参数：
         * sonicCtx：已经配置好采样率、声道数和速度的 Sonic 上下文。
         * (int16_t*)abuf：数据指针，强制转换为 int16_t*（因为 Sonic 要求 16 位输入）。
         * actual_out_samples：每个声道的样本数。
         * 返回值 out_ret：非零表示成功，0 表示失败（通常不会失败）。
         */
        int out_ret = sonicWriteShortToStream(sonicCtx,(int16_t*)abuf,actual_out_samples);
        // 返回 Sonic 流中当前可读取的输出样本数
        int num_samples = sonicSamplesAvailable(sonicCtx);

        // 计算输出缓冲区所需大小并分配内存
        int out_size = num_samples * av_get_bytes_per_sample(aPars->aFormatEnum) * aPars->nbChannels;
        av_fast_malloc(&abufOut,&abufOutSize,out_size); //复用已经有的内存

        int sonic_samples = 0;
        if(out_ret){
            // sonicReadShortFromStream：从 Sonic 流中读取变速后的数据到 abufOut
            sonic_samples = sonicReadShortFromStream(sonicCtx,(int16_t*)abufOut,num_samples);
            playBuffer = abufOut;
            // 更新为变速后的实际数据字节数,避免sonic_samples 与 num_samples 不一致，为了安全重新计算
            bufSize = sonic_samples * av_get_bytes_per_sample(aPars->aFormatEnum) * aPars->nbChannels;
        }
    }

    // 更新全局时钟：当前帧的 PTS（转换为毫秒）
    int64_t globalTime = frame->pts * av_q2d(aPars->timeBase) * 1e3;
    // 记录当前音频播放的时间
    // 视频渲染线程会读取这个时钟，根据视频帧的 PTS 与音频时钟的差值，决定是丢弃视频帧还是等待，从而实现音画同步
    // 通常采用音频为主时钟（因为人耳对声音不同步更敏感），所以音频渲染器每次播放一帧后就更新全局时钟。
    globalClock::getInstance()->setClock(globalTime);

    // 发送播放进度事件（转换到秒，四舍五入）
    sendProcessEvent((globalTime+500) / 1000);

    // 将音频数据循环写入 QIODevice（声卡）
    int bytesWrite = 0;
    while(bytesWrite < bufSize){
        int64_t bytes = aDevice->write((const char*)playBuffer + bytesWrite, bufSize - bytesWrite);

        if(bytes <= 0){
            std::this_thread::sleep_for(std::chrono::microseconds(1000));
            continue;
        }
        bytesWrite += bytes;
    }
}

void FFARender::sendProcessEvent(int curSeconds)
{
    // 避免每秒发送多个相同秒数的事件，减少 UI 刷新开销
    if(curSeconds == lastSec){
        return;
    }
    lastSec = curSeconds;
    FFEvent* processEv = new FFProcessEvent(playerCtx,curSeconds);
    // 事件最终通过 FFEventQueue 被 UI 线程接收
    FFEventQueue::getInstance().enqueue(processEv);
}

