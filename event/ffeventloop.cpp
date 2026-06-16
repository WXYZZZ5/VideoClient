#include"queue/ffeventqueue.h"
#include"thread/ffthreadpool.h"
#include"ffeventloop.h"
#include"ffevent.h"

void FFEventLoop::start() {
    m_stop = false;
    loopThread = std::thread(&FFEventLoop::work,this);
}

void FFEventLoop::stop()
{
    m_stop = true;

}

void FFEventLoop::wait()
{
    if(loopThread.joinable()){
        loopThread.join();
    }
}


void FFEventLoop::work()
{
    while(!m_stop) {
        // 事件队列中：如果队列为空，则阻塞当前线程，直到有事件入队或被唤醒（例如线程停止时）
        FFEvent* event = evQueue->dequeue();
        if(event == nullptr){
            continue;
        }

        // 提交任务到线程池，工作线程去执行任务
        threPool->submit([event]() mutable{
            // 调用具体事件类的业务逻辑（如开始播放、暂停、 seek 等）
            event->work();
            std::cout << "submit task" << std::endl;
            delete event; // 事件使用完后释放内存
        });
    }
}



FFEventLoop::FFEventLoop()
    :m_stop(true)
{

}

FFEventLoop::~FFEventLoop()
{
    stop();
    if(evQueue){
        delete evQueue;
        evQueue = nullptr;
    }
    if(threPool){
        delete threPool;
        threPool = nullptr;
    }
}

void FFEventLoop::init(FFEventQueue *evQueue_, FFThreadPool *threPool_)
{
    evQueue = evQueue_;
    threPool = threPool_;
}
