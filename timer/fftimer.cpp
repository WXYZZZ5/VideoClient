#include"fftimer.h"
#include"queue/ffvframequeue.h"
#include"ui/ffplayerwindow.h"
#include"globalclock.h"
#include<QMetaObject>
#include<iomanip>
#include"event/ffreadyevent.h"
#include"queue/ffeventqueue.h"
#include"player/ffplayercontext.h"
#include"event/ffendevent.h"

// 忽略同步的阈值（微秒）：如果视频与音频的差值超过 10 秒，放弃同步，恢复默认间隔
#define NOSYNC_THRESHOLD 10000
// 最小/最大间隔调节因子（用于防止间隔变化过激）
const double MIN_INTERVAL_FACTOR = 0.01;   // 最小间隔为标准间隔的 1%（极速追赶）
const double MAX_INTERVAL_FACTOR = 2.0;    // 最大间隔为标准间隔的 2%（最多慢一倍）

FFTimer::FFTimer()
    :m_stop(false),seekFlag(false),pauseFlag(false),speedFlag(false),speed(1.0f),speedFactor(1.0f)
{

}

void FFTimer::init(FFPlayerWindow*playerWindow_, FFVDecoder *vDecoder_,
                   FFVFrameQueue *frmQueue_, FFVRender *vRender_)
{
    playerWindow = playerWindow_;
    vDecoder = vDecoder_;
    frmQueue = frmQueue_;
    vRender = vRender_;

    playerCtx = new FFPlayerContext();
    playerCtx->playerWindow = playerWindow_;
    playerCtx->vRender = vRender_;
    playerCtx->vFrmQueue = frmQueue_;
}


void FFTimer::start() {
    m_stop = false;
    setTimerInterval(0LL); //首帧立即播放。
    // 最后启动线程执行 work()
    timerTread = std::thread(&FFTimer::work,this);
}

void FFTimer::wait()
{
    if (timerTread.joinable()){
        timerTread.join();
        std::cerr<<"timer thread has joined!"<<std::endl;
    }

}

void FFTimer::stop() {
    m_stop = true;
    pauseFlag = false;
    cond.notify_all();
    pauseCond.notify_all();
}

void FFTimer::seek()
{
    if(!seekFlag.load(std::memory_order_acquire))
    {
        seekFlag.store(true,std::memory_order_release);
    }
}

void FFTimer::pause()
{
    // 如果从暂停变为恢复，则唤醒暂停条件变量
    bool flag = pauseFlag.load(std::memory_order_acquire);
    if(flag) {
        pauseCond.notify_one();
    }

    pauseFlag.store(!flag,std::memory_order_release);
}


void FFTimer::close()
{
    seekFlag = false;
    pauseFlag = false;
    speedFlag = false;
    speed = 1.0f;
    speedFactor = 1.0f;
}

void FFTimer::wakeAllThread()
{
    pauseCond.notify_all();
    cond.notify_all();
}

void FFTimer::setSpeed(float speed_)
{
    speedFlag.store(true,std::memory_order_release);
    speed = speed_;
}


void FFTimer::setTimerInterval(std::chrono::milliseconds interval_)
{
    interval = interval_;
}

void FFTimer::setTimerInterval(double interval_)
{
    interval = std::chrono::microseconds(static_cast<int64_t>(interval_));
}

void FFTimer::setTimerInterval(int64_t interval_)
{
    this->interval = std::chrono::microseconds(interval_);
}

void FFARender::seek()
{
    if(!seekFlag.load(std::memory_order_acquire))
    {
        seekFlag.store(true,std::memory_order_release);
    }
}
void FFTimer::playVideo()
{
    // 从队列取出一个视频帧
    AVFrame* frame = frmQueue->dequeue();
    if (frame == nullptr){ // 如果帧为空，则停止定时器
        stop();
        return;
    }

    // 检查暂停标志，若暂停则等待
    if(pauseFlag.load()){
        std::unique_lock<std::mutex>lock(pauseMutex);
        pauseCond.wait(lock);
        pauseFlag.store(false,std::memory_order_release);
    }

    // 如果是空标记帧（data 全为空），释放并返回（不渲染）
    if(!frame->data[0] && !frame->data[1]&&!frame->data[2]){
        av_frame_free(&frame);
        return;
    }

    // 第一次进入时初始化视频参数
    if(vPars == nullptr){
        initVideo();
    }

    int width = frame->width;
    int height = frame->height;

    // 计算当前帧的 PTS（毫秒）和音频时钟的差值 delay
    int64_t videoTime = 1000 * frame->pts * av_q2d(vPars->timeBase); // 当前视频帧的 PTS（毫秒）
    int64_t audioClock = globalClock::getInstance()->getClock(); // 全局音频时钟（毫秒）
    int64_t delay = videoTime - audioClock;

    // 检查速度标志,如果被设置，则更新 speedFactor
    if(speedFlag.load(std::memory_order_acquire)){
        speedFactor = speed;
        speedFlag.store(false,std::memory_order_release);
    }
    // 小延迟时跳过 optimizeSync，直接使用标准帧间隔
	// 音频时钟每 23ms 才更新一次（每帧音频的 PTS）。视频每 33ms 读一次这个时钟。
    // 如果 |delay| ≤ 50ms，这个误差可能主要来自音频时钟的更新延迟，而不是真正的不同步。此时强行调整反而引入抖动。
    int ret = 0;
    if (std::abs(delay) > 50) {
        ret = optimizeSync(delay, static_cast<int64_t>(standardInterval * 1.0 / speedFactor));
    } else {
        setTimerInterval(static_cast<int64_t>(standardInterval / speedFactor));
    }

    if(ret == -1){
        av_frame_unref(frame);
        av_frame_free(&frame);
        return;
    }

    // 如果不需要丢帧，则将 YUV 数据从 frame 拷贝到内部缓冲区
    copyYUV(frame);

    // 通过 Qt 的 invokeMethod 在主线程（UI 线程）中调用 playerWindow->renderYUV 进行渲染显示图像。
    // 注意：playerWindow 是 QWidget，必须在主线程操作，所以使用 QueuedConnection
    QMetaObject::invokeMethod(
                playerWindow, "renderYUV",
                Qt::QueuedConnection,
                Q_ARG(uint8_t*,yBuf),
                Q_ARG(uint8_t*,uBuf),
                Q_ARG(uint8_t*,vBuf),
                Q_ARG(int,width),
                Q_ARG(int,height)
                );

    av_frame_unref(frame);
    av_frame_free(&frame);
}

int FFTimer::optimizeSync(int64_t delay, int64_t standardInterval)
{
    // 延迟过大（超过10秒），放弃同步，恢复标准间隔
    if (std::abs(delay) > NOSYNC_THRESHOLD) {
        setTimerInterval(standardInterval);
    }

    // 根据 delay 的正负 计算因子 factor,delay = videoTime - audioClock
    else {
        double factor = 1.0;
        // 视频帧超前：减缓渲染
        if (delay > 0) {
            // 限制最大 MAX_INTERVAL_FACTOR（2.0），防止单次调整过大造成卡顿
            factor = std::min(1.0 + delay / syncThreshold, MAX_INTERVAL_FACTOR);
        }
        // 视频帧滞后：加快渲染
        else {
            double negativeFactor = std::max(0.25 * speedFactor, 1.0 + delay / syncThreshold); // 最小50%加速
            factor = std::max(MIN_INTERVAL_FACTOR, negativeFactor); // 防止间隔过小
        }

        // 应用安全边界并设置间隔（增加防抖动滤波）
        static double lastInterval = standardInterval;
        double newInterval = standardInterval * factor;

        // 滑动平均滤波：避免因为单次 delay 的偶然波动导致帧间隔剧烈变化，引起视觉闪烁。
        // 80% 依赖上一次的间隔，20% 采纳新的计算值 → 平滑过渡，更稳定。
        newInterval = 0.8 * lastInterval + 0.2 * newInterval;

        setTimerInterval(newInterval);
        lastInterval = newInterval;

        // 如果视频超前太多（超过两倍阈值），主动丢帧以快速追赶
        if (delay < -syncThreshold * 2) {
            static size_t dropCount = 0;
            if (dropCount++ % 2 == 0) {   // 每两帧丢一帧
                setTimerInterval(1LL);    // 设置极小间隔，立即处理下一帧
                return -1;                // 返回 -1 表示丢弃当前帧
            }
        }
    }

    return 0;
}

void FFTimer::initVideo()
{
    vPars = new FFVideoPars();
    memcpy(vPars, vDecoder->getVideoPars(), sizeof(FFVideoPars));
    standardInterval = static_cast<int>(1e6 / av_q2d(vPars->frameRate));
    // 防御：当 frameRate 为 {0,0} 时，av_q2d 返回 NaN
    // static_cast<int>(NaN) = INT_MIN，会导致定时器以最大速度运行
    if (standardInterval <= 0 || standardInterval > 500000) {
        standardInterval = 40000; // 默认 25fps 帧间隔
    }
    syncThreshold = 1000 / av_q2d(vPars->frameRate);

    // 发送就绪事件（视频参数已就绪）
    totalSec = vDecoder->getTotalSec();
    FFEvent* event = new FFReadyEvent(playerCtx,totalSec,vPars->width *1.0f / vPars->height);
    FFEventQueue::getInstance().enqueue(event);

}

FFTimer::~FFTimer() {
    stop();
    close();
}

void FFTimer::work()
{
    // 使用条件变量的 wait_for 实现周期性唤醒，每次唤醒后调用 playVideo() 渲染一帧。
    // 间隔 interval 会根据同步状况动态调整。
    std::unique_lock<std::mutex>lock(mutex);
    while (!m_stop) {
        auto targetWakeTime = std::chrono::steady_clock::now() + interval;
        // 使用条件变量等待到目标时间前 1ms，然后用忙等待弥补最后的精度
        if (interval.count() > 2000) {
            cond.wait_until(lock, targetWakeTime - std::chrono::milliseconds(1));
        } else {
            cond.wait_for(lock, interval);
        }
        // 忙等待：使用 steady_clock 精确补偿最后 1ms 的 timer tick 误差
        while (!m_stop && std::chrono::steady_clock::now() < targetWakeTime) {
            std::this_thread::yield();
        }
        if(!m_stop){
            playVideo();
        }
    }
}

// Y 分量大小：width * height
// U/V 分量大小：width/2 * height/2（每个分量）
void FFTimer::copyYUV(AVFrame *frame)
{
    yBuf = new uint8_t[frame->width * frame->height];
    uBuf = new uint8_t[frame->width * frame->height /4];
    vBuf = new uint8_t[frame->width * frame->height /4];
    for (int i = 0; i < frame->height; i++) {
        memcpy(yBuf + i * frame->width,
               frame->data[0] + i * frame->linesize[0],
               frame->width);
    }

    for (int i = 0; i < frame->height / 2; i++) {
        // 拷贝 U 分量
        memcpy(uBuf + i * frame->width / 2,
               frame->data[1] + i * frame->linesize[1],
               frame->width / 2);

        // 拷贝 V 分量
        memcpy(vBuf + i * frame->width / 2,
               frame->data[2] + i * frame->linesize[2],
               frame->width / 2);
    }
}

