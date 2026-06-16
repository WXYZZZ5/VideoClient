#include "ffaframequeue.h"

// 最多缓存25帧，音频帧通常每帧约 10-20ms，25 帧约 0.5 秒缓冲。
#define MAX_FRAME_SIZE 25

FFAFrameQueue::FFAFrameQueue()
    : m_stop(false) {
}

FFAFrameQueue::~FFAFrameQueue() {
    close();
}

void FFAFrameQueue::enqueue(AVFrame* srcFrame) {
    std::unique_lock<std::mutex> lock(mutex);
    cond.wait(lock, [this]() { return frmQueue.size() < MAX_FRAME_SIZE || m_stop.load(); });

    if (m_stop.load()) {
        av_frame_unref(srcFrame);
        return;
    }

    AVFrame* destFrame = av_frame_alloc();
    if (!destFrame) {
        av_frame_unref(srcFrame);
        return;
    }
    // 将 srcFrame 的数据所有权移动到 destFrame，避免拷贝
    av_frame_move_ref(destFrame, srcFrame);
    av_frame_unref(srcFrame);
    frmQueue.push(destFrame);
    cond.notify_one();
}

void FFAFrameQueue::enqueueNull() {
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

void FFAFrameQueue::flushQueue(){
    std::lock_guard<std::mutex>lock(mutex);
    // 循环弹出队首元素，直到队列为空
    while(1){
        AVFrame *frame = peekQueue();
        if(frame == nullptr){
            break;
        }
        frmQueue.pop();
        av_frame_unref(frame);
        av_frame_free(&frame);
    }
    cond.notify_one();
    //    std::cerr<<"flush aframe Queue!"<<std::endl;
}

void FFAFrameQueue::close()
{
    wakeAllThread();
    clearQueue();
}

void FFAFrameQueue::start()
{
    m_stop = false;
}

AVFrame* FFAFrameQueue::peekQueue()
{
    return frmQueue.empty() ? nullptr: frmQueue.front();
}


AVFrame* FFAFrameQueue::dequeue() {
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
    return frame;
}

void FFAFrameQueue::wakeAllThread() {
    m_stop.store(true, std::memory_order_release);
    cond.notify_all();
}

void FFAFrameQueue::clearQueue() {
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
