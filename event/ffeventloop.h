#ifndef FFEVENTLOOP_H
#define FFEVENTLOOP_H

class FFEventQueue;
class FFThreadPool;

#include<thread>
#include<atomic>

/**
 * @brief 事件循环（消费者线程）
 *
 * 职责：
 * - 运行一个独立的线程，不断从事件队列（FFEventQueue）中取出事件对象。
 * - 将每个事件提交给线程池（FFThreadPool）执行，避免阻塞事件循环。
 * - 支持启动、停止、等待线程结束。
 *
 * 为什么需要事件循环？
 * - 将播放器的控制操作（打开文件、暂停、seek、音量调节等）异步化，避免阻塞 UI 线程。
 * - 通过线程池执行事件，可并发处理多个不冲突的事件（如同时调整音量和速度），提高响应性。
 */
class FFEventLoop {
public:
    explicit FFEventLoop();
    ~FFEventLoop();
    void init(FFEventQueue* evQueue_, FFThreadPool* threPool_);
    void start();   // 启动事件循环线程
    void stop();    // 停止事件循环线程
    void wait();    // 等待线程结束（阻塞调用者）
private:
    // 线程主循环：取事件 -> 提交到线程池
    void work();

private:
    FFEventQueue* evQueue;      // 事件队列（生产者写入，消费者读取）
    FFThreadPool* threPool;     // 线程池（实际执行事件的 worker 线程）

    std::thread loopThread;     // 事件循环线程
    std::atomic<bool> m_stop;   // 停止标志

};


#endif // EVENT_LOOP_HPP
