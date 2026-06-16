#include"ffadecoder.h"
#include"queue/ffaframequeue.h"
#include"resampler/ffaresampler.h"


FFADecoder::FFADecoder()
    :m_stop(false){
}

FFADecoder::~FFADecoder()
{
    close();
}

void FFADecoder::init(AVStream *stream_,FFAFrameQueue* frmQueue_)
{
    stream = stream_;
    frmQueue = frmQueue_;

    // 根据流的编码 ID 查找解码器
    AVCodec* codec = avcodec_find_decoder(stream->codecpar->codec_id);
    if(codec == nullptr){
        std::cerr<<"找不到视频解码器"<<std::endl;
        return;
    }

    // 分配解码器上下文
    codecCtx = avcodec_alloc_context3(codec);
    if(codecCtx== nullptr){
        std::cerr<<"分配解码器上下文失败"<<std::endl;
        avcodec_free_context(&codecCtx);
        return;
    }

    // 将流参数复制到解码器上下文中
    int ret = avcodec_parameters_to_context(codecCtx,stream->codecpar);
    if(ret < 0)
    {
        printError(ret);
        avcodec_free_context(&codecCtx);
        return;
    }

    // 打开解码器
    ret = avcodec_open2(codecCtx,codec,nullptr);
    if(ret < 0)
    {
        printError(ret);
        avcodec_free_context(&codecCtx);
        return;
    }

}

void FFADecoder::flushDecoder()
{
    avcodec_flush_buffers(codecCtx);
}

FFAudioPars *FFADecoder::getAudioPars()
{
    return swraPars;
}

int FFADecoder::getToalSec()
{
     // 根据流时长 + 时间基计算总秒数（四舍五入）
    return static_cast<int>(0.5 + stream->duration * av_q2d(stream->time_base));
}

void FFADecoder::wakeAllThread()
{
    frmQueue->wakeAllThread();
}

void FFADecoder::stop()
{
    m_stop = true;
}

void FFADecoder::enqueueNull()
{
    frmQueue->enqueueNull();
}

void FFADecoder::flushQueue()
{
    frmQueue->flushQueue();
}

void FFADecoder::close()
{
    if(codecCtx){
        avcodec_free_context(&codecCtx);
    }
    if(aPars){
        delete  aPars;
        aPars = nullptr;
    }
    if(swraPars){
        delete swraPars;
        swraPars = nullptr;
    }
    if(resampler){
        delete resampler;
        resampler = nullptr;
    }
}


void FFADecoder::decode(AVPacket *packet)
{
    // 将压缩数据包 (AVPacket) 发送给解码器
    int ret = avcodec_send_packet(codecCtx,packet);
    // EAGAIN表示解码器输出满了，需要先收帧
    if(ret < 0 && ret != AVERROR(EAGAIN)){
        printError(ret);
        avcodec_free_context(&codecCtx);
        return;
    }

    // 分配一个空的 AVFrame 结构体，用于存放解码后的原始音频/视频帧
    AVFrame* frame = av_frame_alloc();
    // 循环尝试从解码器中接收解码好的帧
    // 因为一次 send_packet 可能会产生多个输出帧（比如一个视频包包含多个帧）
    // 所以需要用 while 循环持续调用 receive_frame，直到返回 EAGAIN 或 EOF
    // 循环条件 ret >= 0 意思是：只要上一次 receive_frame 成功（返回0），
    // 就继续下一次尝试；如果 ret < 0（失败）则跳出循环。
    while(ret >= 0){
        // 尝试从解码器中取出一个解码好的帧
        // ret = 0 表示成功取出一帧，frame 中现在装满了有效数据
        // ret = AVERROR(EAGAIN) 表示解码器需要更多输入数据才能输出下一帧
        // ret = AVERROR_EOF 表示所有数据已解码完毕
        // 其他负数表示错误
        ret = avcodec_receive_frame(codecCtx,frame);

        if(ret < 0){
            if(ret == AVERROR_EOF){ // 解码器输出结束
                break;
            }
            else if(ret == AVERROR(EAGAIN)){ // 需要更多输入数据
                continue;
            }
            else{
                printError(ret);
                av_frame_free(&frame);
                avcodec_free_context(&codecCtx);
                return;
            }
        }
        else{
            // 成功解码出一帧
            if(aPars == nullptr){
                aPars = new FFAudioPars();
                swraPars = new FFAudioPars();
                initAudioPars(frame);
                // 如果不一致就创建并初始化一个重采样器进行重采样（至少是转换样本格式)
                if(aPars->aFormatEnum != swraPars->aFormatEnum){
                    resampler = new FFAResampler();
                    initResampler();
                    printFmt();
                }
            }
            if(resampler){
                AVFrame* swrFrame = nullptr;
                // 将源帧 frame 中的音频数据转换为目标格式，并分配一个新的 AVFrame 存储在 swrFrame 中
                resampler->resample(frame,&swrFrame);
                av_frame_unref(frame);
                // 检查线程是否停止
                if(m_stop.load(std::memory_order_acquire)){
                    av_frame_unref(swrFrame);
                    av_frame_free(&swrFrame);
                    m_stop.store(false,std::memory_order_release);
                    break;
                }
                else{
                    frmQueue->enqueue(swrFrame);   // 将重采样后的帧放入队列
                    av_frame_free(&swrFrame);      // 队列会克隆一份，这里释放原帧
                }
            }
            // 无需重采样，直接将原帧放入队列（注意克隆）
            else{
                if(m_stop.load(std::memory_order_acquire)){
                    av_frame_unref(frame);
                    m_stop.store(false,std::memory_order_release);
                    break;
                }
                else{
                    frmQueue->enqueue(frame); // 队列会克隆 frame，原 frame 稍后释放
                }
            }
        }
    }
    av_frame_free(&frame);
}

void FFADecoder::printError(int ret)
{
    char errorBuffer[AV_ERROR_MAX_STRING_SIZE];
    int res = av_strerror(ret,errorBuffer,sizeof errorBuffer);
    if(res < 0){
        std::cerr << "Unknow Error!"<<std::endl;
    }
    else{
        std::cerr<<"Error:"<<errorBuffer<<std::endl;
    }

}

void FFADecoder::initAudioPars(AVFrame *frame)
{
    aPars->timeBase = stream->time_base;
    aPars->nbChannels = frame->channels;
    aPars->aFormatEnum =codecCtx->sample_fmt; // 解码器原始格式
    aPars->sampleSize = av_get_bytes_per_sample(codecCtx->sample_fmt);
    aPars->sampleRate = frame->sample_rate;

    memcpy(swraPars,aPars,sizeof(FFAudioPars));
    swraPars->aFormatEnum = AV_SAMPLE_FMT_S16;
    swraPars->sampleSize = av_get_bytes_per_sample(AV_SAMPLE_FMT_S16);
}

void FFADecoder::initResampler()
{
    resampler->init(aPars,swraPars); // 初始化重采样器（源参数 -> 目标参数）
}

void FFADecoder::printFmt()
{
    std::cout << "audio format : "<< av_get_sample_fmt_name(aPars->aFormatEnum) << std::endl;
    std::cout << "sample_rate : "<< aPars->sampleRate << std::endl;
    std::cout << "channels : "<< aPars->nbChannels << std::endl;
    std::cout << "time_base : "<< aPars->timeBase.num << " / " << aPars->timeBase.den << std::endl;

    std::cerr<<"================="<<std::endl;
    std::cout << "audio format : "<< av_get_sample_fmt_name(swraPars->aFormatEnum) << std::endl;
    std::cout << "sample_rate : "<< swraPars->sampleRate << std::endl;
    std::cout << "channels : "<< swraPars->nbChannels << std::endl;
    std::cout << "time_base : "<< swraPars->timeBase.num << " / " << swraPars->timeBase.den << std::endl;


}
