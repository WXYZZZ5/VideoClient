#include"thread/ffthreadPool.h"
#include<iostream>
FFThreadPool::FFThreadPool()
    :m_stop(true) // 初始状态为停止，需要显式调用 init 启动
{
}

FFThreadPool::~FFThreadPool()
{
    stop();    // 设置停止标志并唤醒线程
    wait();    // 等待所有线程结束
}

void FFThreadPool::init(size_t threadCount_)
{
    // 初始化线程池，创建 threadCount 个工作线程
    threadCount = threadCount_;
    for (size_t i = 0; i < threadCount; ++i) {
        threadVec.emplace_back(std::thread(&FFThreadPool::work,this));
    }
}

void FFThreadPool::work()
{
    m_stop = false;
    while(!m_stop){
        std::function<void()>task = getTask();
        if(task == nullptr){
            return;
        }
        std::cerr<<"task!"<<std::endl;
        task(); // 执行任务
    }
}

std::function<void()> FFThreadPool::getTask()
{
    std::unique_lock<std::mutex>lock(mutex);
    cond.wait(lock, [this]() { return m_stop.load() || !taskQueue.empty(); });

    if(m_stop && taskQueue.empty()){
        return nullptr;
    }

    std::function<void()> task = taskQueue.front();
    taskQueue.pop();
    std::cerr<<"getTask"<<std::endl;
    return task;
}

void FFThreadPool::enqueueTask(std::function<void()>task)
{
    std::lock_guard<std::mutex>lock(mutex);
    taskQueue.push(task);
    cond.notify_one();
}

void FFThreadPool::stop(){
    m_stop.store(true);
    cond.notify_all();
}

void FFThreadPool::wait()
{
    std::lock_guard<std::mutex>lock(mutex);
    for(auto& thread : threadVec){
        if(thread.joinable()){
            thread.join();
        }
    }
}
