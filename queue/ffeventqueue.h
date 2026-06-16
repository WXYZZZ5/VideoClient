#ifndef FFEVENTQUEUE_H
#define FFEVENTQUEUE_H

#include<iostream>
#include<queue>
#include<condition_variable>
#include<mutex>
#include<atomic>

class FFEvent;

/**
 * @brief 线程安全的事件队列（单例模式）
 *
 * 职责：
 * - 存储 FFEvent 对象指针，支持生产者（任意线程）安全地入队。
 * - 支持消费者（事件循环线程）阻塞出队，队列为空时自动等待。
 * - 支持停止队列并清空所有未处理事件，用于程序退出。
 *
 * 设计模式：
 * - 单例模式（Singleton）：整个程序只有一个事件队列，统一管理所有播放器操作事件。
 * - 生产者-消费者模式：使用互斥锁 + 条件变量实现线程安全阻塞队列。
 */
class FFEventQueue final {
public:
    static FFEventQueue& getInstance();

    FFEventQueue(const FFEventQueue&) = delete;
    FFEventQueue& operator=(const FFEventQueue&) = delete;

    void enqueue(FFEvent* event);
    FFEvent* dequeue();
    void clearQueue();
    void wakeAllThread();

    ~FFEventQueue();

private:
    FFEventQueue() : m_stop(false) {}

    std::queue<FFEvent*> evQueue;      // 底层队列（存储事件指针）
    std::condition_variable cond;      // 条件变量，用于阻塞/唤醒消费者
    std::mutex mutex;                  // 互斥锁，保护队列和停止标志
    std::atomic<bool> m_stop;          // 停止标志，指示队列不再接收/处理事件
};

#endif // FFEVENTQUEUE_H
