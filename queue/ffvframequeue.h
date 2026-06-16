#ifndef FFVFRAMEQUEUE_H
#define FFVFRAMEQUEUE_H

#include <iostream>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <atomic>

extern "C" {
#include <libavformat/avformat.h>
}

/**
 * @brief 视频帧队列（线程安全）
 *
 * 负责在视频解码线程和视频渲染线程之间传递解码后的 AVFrame（YUV/RGB 图像）。
 */
class FFVFrameQueue {
public:
    explicit FFVFrameQueue();
    ~FFVFrameQueue();

    void enqueue(AVFrame* frame);
    AVFrame* dequeue();

    void wakeAllThread();
    void clearQueue();
    void enqueueNull();

    void flushQueue();
    void close();
    void start();

private:
    AVFrame* peekQueue();
private:
    std::queue<AVFrame*> frmQueue;       // 数据队列
    std::mutex mutex;
    std::condition_variable cond;
    std::atomic<bool> m_stop;
};

#endif // FFVFRAMEQUEUE_H
