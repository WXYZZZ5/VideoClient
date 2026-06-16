#ifndef FFThreadPool_H
#define FFThreadPool_H

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include<atomic>

/**
 * @brief 线程池类
 *
 * 职责：
 * - 维护一组固定数量的工作线程，重复执行提交的任务（函数对象）。
 * - 支持将任意可调用对象（函数、lambda、成员函数）包装为任务并提交。
 * - 支持优雅停止（等待所有当前任务完成）和立即停止。
 *
 *FFThread派生类（解封装线程、解码线程）是工作线程，它们负责持续不断的媒体数据处理（读取包、解码），
 *这些是播放的主数据流，不需要用户每次触发，而是循环执行直到停止。
 *
 *线程池（以及事件队列、事件循环）负责处理用户交互事件（UI触发）或系统事件（如进度更新），
 *这些事件是离散的、异步的，需要快速响应，并且可能涉及跨线程通信（如更新UI）。线程池用来并发执行这些事件，避免阻塞事件循环。
 */
class FFThreadPool {
public:
    explicit FFThreadPool();
    ~FFThreadPool();

    void init(size_t threadCount_);   // 初始化线程池，创建指定数量的工作线程
    void stop();                      // 停止线程池（设置停止标志，唤醒所有线程）
    void wait();                      // 等待所有工作线程结束（join）

    /**
     * @brief 提交一个无参数的任务（函数、lambda、可调用对象）
     * @param func 可调用对象（会被包装为 std::function<void()>）
     */
    template<typename Func>
    void submit(Func func){
        std::function<void()> task = func; // 转换为标准函数对象
        enqueueTask(func);
    }

    /**
     * @brief 提交一个成员函数任务（无参数），执行后自动删除对象
     * @param obj 对象指针（new 出来的，线程池负责 delete）
     * @param memberFunc 成员函数指针
     */
    template<typename Class,typename Func>
    void submit(Class* obj,Func memberFunc){
        std::function<void()> task = [obj,memberFunc](){
            (obj->*memberFunc)();
            delete obj;
        };
        enqueueTask(task);
    }

    /**
     * @brief 提交一个成员函数任务（带参数），执行后自动删除对象
     * @param obj 对象指针
     * @param memberFunc 成员函数指针
     * @param args 参数包（完美转发）
     */
    template<typename Class, typename Func, typename... Args>
    void submit(Class* obj, Func memberFunc, Args&&... args) {
        std::function<void()> task = [obj, memberFunc, args...]() mutable {
            (obj->*memberFunc)(std::forward<Args>(args)...);
            delete obj;
        };
        enqueueTask(task);
    }

private:
    void work();                          // 工作线程的主循环
    std::function<void()> getTask();      // 从任务队列中取一个任务（阻塞）
    void enqueueTask(std::function<void()> task); // 将任务放入队列

private:
    std::vector<std::thread> threadVec;   // 工作线程容器
    std::queue<std::function<void()>> taskQueue; // 任务队列
    std::mutex mutex;                     // 保护任务队列和停止标志
    std::condition_variable cond;         // 用于任务等待和唤醒
    std::atomic<bool> m_stop;             // 停止标志
    size_t threadCount;                   // 线程数量

};
#endif // FFFFThreadPool_H
