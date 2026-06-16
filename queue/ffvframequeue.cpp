#include "ffvframequeue.h"

// 最大容量：只缓存 7 帧视频。视频帧通常占用内存较大（1920x1080 YUV420P 约 3MB/帧），
// 7 帧约 21MB，是合理的缓冲量，同时避免过大延迟。
#define MAX_FRAME_SIZE 7

FFVFrameQueue::FFVFrameQueue()
    : m_stop(false) {
}

FFVFrameQueue::~FFVFrameQueue() {
    close();
}

void FFVFrameQueue::enqueue(AVFrame* frame) {
    std::unique_lock<std::mutex> lock(mutex);
    cond.wait(lock, [this]() { return frmQueue.size() < MAX_FRAME_SIZE || m_stop.load(); });
    if (m_stop.load()) {
        av_frame_unref(frame);
        av_frame_free(&frame);
        return;
    }

//    std::cout<<"enqueue frameQueue Size:"<< frmQueue.size()<<std::endl;
    frmQueue.push(frame);
    cond.notify_one();
}

void FFVFrameQueue::enqueueNull() {
    std::unique_lock<std::mutex> lock(mutex);
    cond.wait(lock, [this]() { return frmQueue.size() < MAX_FRAME_SIZE || m_stop.load(); });

    if (m_stop.load()) {
        return;
    }
    AVFrame* frame = av_frame_alloc();
    if (frame) {
        frame->data[0] = nullptr;
        frame->data[1] = nullptr;
        frame->data[2] = nullptr;
        frmQueue.push(frame);
        cond.notify_one();
    }
}

AVFrame* FFVFrameQueue::dequeue() {
    std::unique_lock<std::mutex> lock(mutex);
    if(m_stop){
        return nullptr;
    }
    cond.wait(lock, [this]() { return !frmQueue.empty() || m_stop.load(); });

    if (m_stop.load()) {
        return nullptr;
    }

    AVFrame* frame = frmQueue.front();
    frmQueue.pop();
    cond.notify_one();
//    std::cout<<"frameQueue Size:"<<frmQueue.size()<<std::endl;
    return frame;
}

void FFVFrameQueue::wakeAllThread() {
    m_stop.store(true, std::memory_order_release);
    cond.notify_all();
}

void FFVFrameQueue::clearQueue() {
    std::lock_guard<std::mutex> lock(mutex);
    while (!frmQueue.empty()) {
        AVFrame* frame = frmQueue.front();
        frmQueue.pop();
        if (frame) {
            av_frame_unref(frame);
            av_frame_free(&frame);
        }
    }
}

void FFVFrameQueue::flushQueue(){
    std::lock_guard<std::mutex>lock(mutex);
    while(1){
        AVFrame *frame = peekQueue();
        if(frame == nullptr){
            break;
        }
        frmQueue.pop();
        av_frame_unref(frame);
        av_frame_free(&frame);

    }
//     std::cerr<<"flush vframe Queue!"<<std::endl;
    cond.notify_one();
}

void FFVFrameQueue::close()
{
    wakeAllThread();
    clearQueue();
}

void FFVFrameQueue::start()
{
    m_stop = false;
}

AVFrame* FFVFrameQueue::peekQueue()
{
    return frmQueue.empty() ? nullptr: frmQueue.front();
}
