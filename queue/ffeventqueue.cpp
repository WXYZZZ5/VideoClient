#include "ffeventqueue.h"
#include "event/ffevent.h"

FFEventQueue::~FFEventQueue()
{
    // 设置停止标志并唤醒所有等待线程，然后删除队列中残留的事件对象。
    std::lock_guard<std::mutex> lock(mutex);
    m_stop.store(true);
    cond.notify_all(); // 唤醒所有可能阻塞在 dequeue 上的线程
    while (!evQueue.empty()) {
        FFEvent* event = evQueue.front();
        evQueue.pop();
        delete event;
    }
}

FFEventQueue &FFEventQueue::getInstance()
{
    static FFEventQueue instance;
    return instance;
}

void FFEventQueue::enqueue(FFEvent* event)
{
    std::lock_guard<std::mutex> lock(mutex);
    evQueue.emplace(event);
//    std::cout<<"enqueue event!"<<std::endl;
    cond.notify_one();
}

FFEvent* FFEventQueue::dequeue()
{
    std::unique_lock<std::mutex> lock(mutex);
    // 等待条件：队列非空 或 停止标志被设置
    cond.wait(lock, [this]() {
        return !evQueue.empty() || m_stop.load();
    });

    if (m_stop.load()) {
        return nullptr;
    }

    FFEvent* event = evQueue.front();
//    std::cout<<"dequeue event!"<<std::endl;
    evQueue.pop();
    return event;
}

void FFEventQueue::clearQueue()
{
    std::lock_guard<std::mutex> lock(mutex);
    while (!evQueue.empty()) {
        FFEvent* event = evQueue.front();
        evQueue.pop();
        delete event;
    }
}

void FFEventQueue::wakeAllThread() {
    std::lock_guard<std::mutex> lock(mutex);
    m_stop.store(true);
    cond.notify_all();
}
