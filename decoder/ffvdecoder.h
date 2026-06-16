#ifndef FFVDECODER_H
#define FFVDECODER_H


#include<iostream>
extern "C"
{
#include<libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/cpu.h>
}
#include<atomic>

class FFVFrameQueue;
class FFVResampler;

struct FFVideoPars{
    int width;                // 宽度
    int height;               // 高度
    AVRational frameRate;     // 帧率
    AVPixelFormat pixFmtEnum; // 像素格式（如 AV_PIX_FMT_YUV420P）
    AVRational timeBase;      // 时间基
};

/**
 * @brief 视频解码器类
 *
 * 职责与音频解码器类似：
 * 1. 初始化解码器（支持多线程解码）。
 * 2. decode() 接收 AVPacket，输出 AVFrame。
 * 3. 如果需要像素格式转换（例如转换为 YUV420P），使用 FFVResampler（实际是视频图像缩放/格式转换器）。
 * 4. 将帧放入 FFVFrameQueue。
 * 5. 支持 flush、停止、队列清理。
 */
class FFVDecoder
{
public:
    explicit FFVDecoder();
    FFVDecoder(const FFVDecoder&) = delete;
    FFVDecoder& operator=(const FFVDecoder&) = delete;
    ~FFVDecoder();

    void decode(AVPacket* packet);
    void init(AVStream *stream_,FFVFrameQueue *frmQueue_);
    void flushDecoder();
    int getTotalSec();
    FFVideoPars* getVideoPars();
    void enqueueNull();

    void wakeAllThread();
    void stop();
    void flushQueue();
    void close();
private:
    void initResampler();
    void initVideoPars(AVFrame* frame);
    void printError(int ret);

private:
    AVCodecContext* codecCtx = nullptr;
    AVStream* stream = nullptr;
    FFVFrameQueue* frmQueue;
    FFVideoPars* vPars = nullptr;      // 解码器原始参数
    FFVideoPars* swsvPars = nullptr;   // 转换目标参数（固定 YUV420P）
    FFVResampler* resampler = nullptr; // 图像格式转换器

    std::atomic<bool>m_stop;
};


#endif
