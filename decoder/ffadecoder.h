#ifndef FFADECODER_H
#define FFADECODER_H

#include<iostream>
#include<atomic>
extern "C"
{
#include<libavformat/avformat.h>
#include<libavutil/samplefmt.h>
}

struct FFAudioPars{
    int sampleRate;                  // 采样率（Hz）
    int nbChannels;                  // 声道数
    AVRational timeBase;             // 时间基（AVStream 的时间基）
    enum AVSampleFormat aFormatEnum; // 样本格式（如 AV_SAMPLE_FMT_FLTP）
    int sampleSize;                  // 每个样本的字节数（av_get_bytes_per_sample）
};

class FFAFrameQueue;   // 音频帧队列（存放 AVFrame）
class FFAResampler;    // 音频重采样器

/**
 * @brief 音频解码器类
 *
 * 职责：
 * 1. 初始化 FFmpeg 音频解码器（根据 AVStream 的 codecpar）。
 * 2. 提供 decode() 函数，接收 AVPacket，解码出 AVFrame。
 * 3. 如果需要重采样（例如将 float planar 转为 S16），使用 FFAResampler 转换。
 * 4. 将解码后的 AVFrame（或重采样后的帧）放入 FFAFrameQueue 供播放线程使用。
 * 5. 支持 flush（seek 时清空解码器缓存）、停止、队列清理等操作。
 */
class FFADecoder
{
public:
    explicit FFADecoder();
    FFADecoder(const FFADecoder&) = delete;
    FFADecoder& operator=(const FFADecoder&) = delete;
    ~FFADecoder();

    /**
     * @brief 解码一个 AVPacket
     * @param packet 输入的压缩包（由解封装线程提供）
     *
     * 内部会调用 avcodec_send_packet / avcodec_receive_frame，
     * 可能多次输出帧（当 packet 中包含多个编码帧时）。
     * 解码后的帧经过重采样（如果需要）后放入帧队列。
     */
    void decode(AVPacket* packet);

    /**
     * @brief 初始化解码器
     * @param stream_     音频流（来自解封装器）
     * @param frmQueue_   输出帧队列（解码后的音频帧将放入此队列）
     */
    void init(AVStream* stream_,FFAFrameQueue* frmQueue_);

    /**
     * @brief 清空解码器内部缓冲（seek 时调用）
     */
    void flushDecoder();
    // 获取原始音频参数
    FFAudioPars* getAudioPars();
    // 获取音频总时长（秒）
    int getToalSec();

    void wakeAllThread();
    void stop();
    // 向帧队列中放入一个空包（EOF 时调用，通知播放线程结束）
    void enqueueNull();
    // 清空帧队列中所有属于旧周期的帧（seek操作后清理）
    void flushQueue();

    void close();
private:
    void printError(int ret);
    void initAudioPars(AVFrame* frame);   // 从第一个解码帧提取音频参数
    void initResampler();                 // 初始化重采样器
    void printFmt();                      // 调试打印参数

private:
    AVCodecContext* codecCtx = nullptr;   // FFmpeg 解码器上下文
    FFAFrameQueue* frmQueue = nullptr;    // 输出帧队列
    AVStream* stream = nullptr;           // 对应的音频流
    FFAudioPars* aPars = nullptr;         // 解码器输出的原始音频格式
    FFAudioPars* swraPars = nullptr;      // 重采样后供播放器使用的目标音频格式（固定为 S16）
    FFAResampler* resampler = nullptr;    // 重采样器（仅在需要时创建）
    std::atomic<bool> m_stop;             // 停止标志（解码线程退出用）
};


#endif
