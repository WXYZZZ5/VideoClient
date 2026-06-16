#ifndef FFAFRAMEQUEUE_H
#define FFAFRAMEQUEUE_H

#include <iostream>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <atomic>

extern "C" {
#include <libavformat/avformat.h>
}

/**
 * @brief 音频帧队列（线程安全）
 *
 * 负责在音频解码线程和音频播放线程之间传递解码后的 AVFrame
 * 支持阻塞入队/出队、最大容量限制、空包（EOF）通知、队列清空、flush 等操作。
 * 注意：此队列存储的是 AVFrame*，但内存管理遵循“生产者负责分配，消费者负责释放”的原则，
 * 不过 enqueue 会通过 av_frame_move_ref 或 av_frame_clone 等机制管理所有权。
 */
class FFAFrameQueue {
public:
    explicit FFAFrameQueue();
    ~FFAFrameQueue();

    void enqueue(AVFrame* srcFrame);
    void enqueueNull();
    AVFrame* dequeue();

    void wakeAllThread();
    void clearQueue();
    // 丢弃所有属于旧周期的帧（seek 后清理）
    void flushQueue();
    void close();
    void start();
private:
    // 查看队首元素但不取出
    AVFrame *peekQueue();
private:
    std::queue<AVFrame*> frmQueue;       // 底层队列，存储 AVFrame 指针
    std::mutex mutex;                    // 互斥锁
    std::condition_variable cond;        // 条件变量，用于阻塞/唤醒
    std::atomic<bool> m_stop;            // 停止标志（true 时所有操作立即返回）
};

#endif // FFAFRAMEQUEUE_H
