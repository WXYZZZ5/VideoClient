#ifndef FFTIMER_H
#define FFTIMER_H

#include <functional>
#include <thread>
#include <chrono>
#include<iostream>
#include <atomic>
#include <condition_variable>
#include"decoder/ffvdecoder.h"

class FFVFrameQueue;
class FFPlayerWindow;
class FFPlayerContext;
class FFVRender;

/**
 * @brief 音视频同步定时器类
 *
 * 职责：
 * 1. 维护一个独立的定时器线程，以动态调整的间隔触发视频帧渲染。
 * 2. 从视频帧队列中取出解码后的 AVFrame，计算其 PTS 与音频时钟的差值。
 * 3. 根据差值动态调整下一次渲染的等待时间（即定时器间隔），实现音视频同步。
 * 4. 将视频帧的 YUV 数据拷贝出来，并通过 Qt 信号/槽机制（invokeMethod）传递给 UI 线程进行渲染。
 * 5. 支持暂停、seek、变速播放等控制。
 *
 * 同步策略：
 * - 以音频时钟（globalClock）为主时钟。
 * - 当视频超前（delay < 0）时，加快定时器频率（缩短间隔），加速渲染追上音频。
 * - 当视频滞后（delay > 0）时，减慢定时器频率（拉长间隔），让音频等待视频。
 * - 当延迟过大（超过阈值 NOSYNC_THRESHOLD）时，直接恢复默认间隔（软同步）。
 * - 极端滞后情况下，会主动丢帧（跳过当前帧）来快速追赶。
 */
class FFTimer {
public:
    FFTimer();
    ~FFTimer();

    // 初始化：关联视频窗口、解码器、帧队列、视频渲染器（实际渲染在窗口内完成）
    void init(FFPlayerWindow*playerWindow_, FFVDecoder*vDecoder_,
              FFVFrameQueue* frmQueue_,FFVRender* vRender_);

    void start();
    void wait();
    void stop();
    void seek(); // 用户 seek 时调用，设置 seekFlag
    void pause(); // 切换 pauseFlag,切换暂停/恢复播放
    void close();
    void wakeAllThread();
    void setSpeed(float speed_);

private:
    // 定时器线程的主循环
    void work();
    // 将 AVFrame 中的 YUV420P 数据拷贝到内部缓冲区 yBuf/uBuf/vBuf
    void copyYUV(AVFrame* frame);
    // 根据延迟动态计算下一次定时器间隔，并返回是否应丢帧
    int optimizeSync(int64_t delay, int64_t standardInterval);
    void setTimerInterval(std::chrono::milliseconds interval_); // 设置定时器间隔（毫秒）
    void setTimerInterval(double interval_);                    // 微秒（双精度）
    void setTimerInterval(int64_t interval_);                   // 微秒（整型）
    void initVideo();
    // 实际执行一帧视频的渲染（取出帧、同步、拷贝、触发 UI 渲染）
    void playVideo();

private:
    std::chrono::microseconds interval;     // 当前定时器间隔（微秒），动态变化

    std::thread timerTread;                 // 定时器线程
    bool m_stop;                            // 停止标志

    FFVFrameQueue* frmQueue = nullptr;      // 视频帧队列（输入）
    FFVDecoder* vDecoder = nullptr;         // 视频解码器（用于获取帧率等参数）
    FFVideoPars* vPars = nullptr;           // 视频参数（宽度、高度、帧率、像素格式等）
    FFPlayerWindow* playerWindow = nullptr; // Qt 播放器窗口（用于渲染 YUV）
    FFPlayerContext* playerCtx = nullptr;   // 播放器上下文（传递给事件）
    FFVRender* vRender = nullptr;

    int64_t standardInterval;               // 理论标准帧间隔（微秒） = 1e6 / 帧率，例如 24fps → 41666μs
    int64_t syncThreshold;                  // 同步阈值（微秒） = 1000 / 帧率，例如 24fps → 41.66ms
    int totalSec = -1;                      // 视频总时长（秒）

    std::mutex mutex;                       // 互斥锁
    std::condition_variable cond;           // 定时器线程的条件变量
    std::mutex pauseMutex;                  // 配合 pauseCond 的互斥锁
    std::condition_variable pauseCond;      // 暂停条件变量


    std::atomic<bool> seekFlag;    // seek 标志
    std::atomic<bool> pauseFlag;   // 暂停标志

    uint8_t* yBuf = nullptr;      // Y 分量缓冲区
    uint8_t* uBuf = nullptr;      // U 分量缓冲区
    uint8_t* vBuf = nullptr;      // V 分量缓冲区

    std::atomic<bool> speedFlag;  // 速度改变标志
    float speed;                  // 当前速度（1.0 正常）
    float speedFactor;            // 速度因子（等于 speed，用于调整同步计算）

};

#endif // FFTIMER_H
