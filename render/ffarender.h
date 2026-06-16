#ifndef FFARENDER_H
#define FFARENDER_H

#include"thread/ffthread.h"
#include"decoder/ffadecoder.h"
#include<atomic>
#include<QAudioOutput>
#include<QIODevice>
#include<condition_variable>

extern "C"
{
#include"libavformat/avformat.h"
#include"libavutil/samplefmt.h"
}

struct sonicStreamStruct;
class FFADecoder;
class FFAFrameQueue;
class FFPlayerWindow;
class FFPlayerContext;

/**
 * @brief 音频渲染器类（继承自 FFThread，运行在独立线程中）
 *
 * 职责：
 * 1. 从音频帧队列（FFAFrameQueue）中取出解码后的 AVFrame。
 * 2. 使用 Qt 的 QAudioOutput 将音频数据输出到声卡。
 * 3. 支持播放控制：暂停、停止、音量调节、变速播放（通过 Sonic 库）。
 * 4. 维护全局时钟（用于音视频同步）。
 * 5. 发送播放进度事件（FFProcessEvent）和就绪事件（FFReadyEvent）。
 * 6. 处理 seek 和 pause 时的条件变量等待。
 */
class FFARender : public FFThread
{
public:
    FFARender();
    virtual ~FFARender() override;

    void init(FFAFrameQueue* frmQueue_,FFADecoder* aDecoder_,FFPlayerWindow* playerWindow_);
    void stop();
    void pause();
    void wakeAllThread();
    void seek();
    void close();
    // 设置播放速度（如 1.0 正常，2.0 两倍速）
    void setSpeed(float speed_);
    // 设置音量（0.0~1.0）
    void setVolume(double volume);

protected:
    virtual void run() override;

private:
    void initAudio();
    void initAudioPars();
    // 播放一个音频帧（即写入声卡）
    void playAudio(AVFrame* frame);
    // 发送播放进度事件进行UI更新（秒为单位）
    void sendProcessEvent(int curSeconds);

private:
    FFAFrameQueue* frmQueue = nullptr;      // 音频帧队列（输入）
    FFADecoder* aDecoder = nullptr;         // 音频解码器（用于获取参数）
    FFPlayerWindow* playerWindow = nullptr; // 播放器窗口（用于 UI 更新）
    QAudioOutput* aOutput = nullptr;        // Qt 音频输出对象
    QAudioFormat aFormat;                   // 音频输出格式（采样率、声道、样本类型等）
    QIODevice* aDevice;                     // 实际写入音频数据的设备
    QAudioDeviceInfo deviceInfo;            // 当前默认音频输出设备的信息

    FFAudioPars* aPars = nullptr;           // 音频参数（采样率、声道数、格式等）
    uint8_t* abuf = nullptr;                // 临时缓冲区（存储待播放的 PCM 数据）
    int64_t maxBufSize = -1;                // 当前 abuf 的大小（字节）

    int clockBase = 0;                      // 基准值
    std::atomic<bool> readyFlag;            // 是否已经准备好（已发送就绪事件）
    int totalSec = 0;                       // 音频总时长（秒）
    FFPlayerContext* playerCtx = nullptr;   // 播放器上下文（传递给事件）
    int lastSec = -1;                       // 上次发送进度事件的秒数（避免重复发送）

    std::atomic<bool> seekFlag;             // 是否正在 seek
    std::atomic<bool> pauseFlag;            // 暂停标志（true 时渲染线程进入条件变量等待）
    std::condition_variable pauseCond;      // 条件变量，用于暂停/恢复
    std::mutex mutex;                       // 与 pauseCond 配合的互斥锁

    sonicStreamStruct* sonicCtx = nullptr;  // Sonic 变速库的上下文（用于改变播放速度）
    std::atomic<bool> speedFlag;            // 速度改变标志（触发重新创建 Sonic 上下文）
    float speed;                            // 当前播放速度（1.0 为正常）

    uint8_t* abufOut = nullptr;             // 变速后的输出缓冲区（Sonic 输出）
    unsigned int abufOutSize = 0;           // 当前 abufOut 的分配大小（用于 av_fast_malloc）
};

#endif // FFARender_H
