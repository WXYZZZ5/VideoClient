#ifndef FFAPACKETQUEUE_H
#define FFAPACKETQUEUE_H

#include <condition_variable>
#include <mutex>
#include<queue>
#include<iostream>
#include<atomic>
extern "C"
{
#include <libavformat/avformat.h>
}

class FFPacket;

/**
 * @brief 音频包队列
 *
 * 负责在解封装线程和音频解码线程之间传递音频 AVPacket。
 * 支持阻塞入队/出队、最大容量限制、flush 操作、结束通知等。
 */
class FFAPacketQueue
{
public:
    explicit FFAPacketQueue();
    ~FFAPacketQueue();

    /**
     * @brief 从队列头部取出一个包（阻塞）
     * @return FFPacket* 包指针，如果 m_stop 为 true 则返回 nullptr
     */
    FFPacket* dequeue();
    // 查看队列头部元素但不取出（非阻塞）
    FFPacket *peekQueue();
    // 入队一个普通 AVPacket（内部会转换为 FFPacket 并拷贝数据）
    void enqueue(AVPacket* pkt);
    // 入队一个 FLUSH 包，同时序列号 +1（用于 seek）
    void enqueueFlush();
     // 入队一个 NULLP 包，表示流结束（EOF）
    void enqueueNull();
    // 丢弃所有 serial 小于当前序列号的旧包（seek操作后清理残留包）
    void flushQueue();

    // 获取当前序列号
    size_t getSerial();
    // 清空队列中所有包（不关心 serial）
    void clearQueue();
    // 唤醒所有阻塞在 dequeue 上的线程（通常用于停止播放）
    void wakeAllThread();
    // 关闭队列，唤醒并清空
    void close();
    // 启动队列（重置停止标志）
    void start();

private:
    std::mutex mutex;
    std::condition_variable cond;
    std::atomic<size_t> serial;          // 当前序列号（每次 FLUSH 递增），用于标记不同的 seek 周期
    std::queue<FFPacket*> pktQueue;      // 底层队列（存储指针）
    std::atomic<bool> m_stop;            // 停止标志（true 时所有操作立即返回）


};

#endif // FFAPACKETQUEUE_H
