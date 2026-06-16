#include "ffapacketqueue.h"
#include"ffpacket.h"

#define MAX_PACKET_SIZE 500

FFAPacketQueue::FFAPacketQueue()
    : serial(0),m_stop(false)
{
}

FFAPacketQueue::~FFAPacketQueue()
{
    close();
}

FFPacket* FFAPacketQueue::dequeue()
{
    std::unique_lock<std::mutex> lock(mutex);
    // 阻塞等待，直到队列非空或线程停止
    cond.wait(lock,[this]() { return !pktQueue.empty() || m_stop.load(); });
    if(m_stop.load()){
        return nullptr;
    }
    FFPacket* ffpkt = pktQueue.front();
    pktQueue.pop();
    cond.notify_one();
//    std::cout << "dequeue apacket! "<< std::endl;
    return ffpkt;
}

FFPacket *FFAPacketQueue::peekQueue()
{
    std::lock_guard<std::mutex>lock(mutex);
    return pktQueue.empty()? nullptr : pktQueue.front();
}

void FFAPacketQueue::enqueue(AVPacket *pkt)
{
    std::unique_lock<std::mutex> lock(mutex);
    // 等待队列有空位（避免无限膨胀）或停止
    cond.wait(lock,[this]() { return pktQueue.size() < MAX_PACKET_SIZE  || m_stop.load(); });
    if(m_stop.load()){
        std::cerr<<"m_stop load!"<<std::endl;
        av_packet_unref(pkt);
        return;
    }
    // 为自定义的 FFPacket 结构体分配一块内存，并将这块内存全部清零（av_mallocz 的 z 即 zero）
    // av_mallocz返回void*，使用static_cast转换为FFPacket*
    FFPacket* ffpkt = static_cast<FFPacket*>(av_mallocz(sizeof(FFPacket)));
    /* 将 ffpkt->packet 初始化为一个“空”的 AVPacket，使其内部字段处于有效且可安全释放的状态。
     * 因为第 3 步中的 av_packet_move_ref 会直接操作 ffpkt->packet 的内部指针和引用计数，
     * 如果 ffpkt->packet 处于未初始化状态，可能会导致崩溃或内存泄漏。
     */
    av_init_packet(&ffpkt->packet);
    // 将源包 pkt 中持有的媒体数据的所有权（指针和引用计数）移动到目标包 &ffpkt->packet 中，避免直接拷贝
    av_packet_move_ref(&ffpkt->packet,pkt);
    ffpkt->serial = serial;
    ffpkt->type = NORMAL;

    pktQueue.push(ffpkt);
//    std::cout << "enqueue apacket: "<< pktQueue.size()<< std::endl;
    cond.notify_one();
}

void FFAPacketQueue::enqueueFlush()
{
    std::unique_lock<std::mutex> lock(mutex);
    cond.wait(lock,[this]() { return pktQueue.size() < MAX_PACKET_SIZE || m_stop.load(); });

    if(m_stop){
        return;
    }

    FFPacket* ffpkt = static_cast<FFPacket*>(av_mallocz(sizeof(FFPacket)));
    av_init_packet(&ffpkt->packet);
    ffpkt->type = FLUSH;
    /* 假设当前 serial == 5，那么：
    * 入队的 FLUSH 包携带的 serial = 5（自增前的值）。
    * 队列的 serial 变为 6。
    * 此后，新入队的普通包（通过 enqueue(AVPacket*)）会使用 serial.load() 的当前值，即 6。
    * 关键点： 队列的 getSerial() 返回的是 当前 serial（即最新值 6），而 FLUSH 包本身携带的 serial 是旧值（5）。
    */
    ffpkt->serial = this->serial++; //先赋值后自增，开启新的周期
    pktQueue.push(ffpkt);
    cond.notify_one();
}

void FFAPacketQueue::enqueueNull()
{
    std::unique_lock<std::mutex> lock(mutex);
    cond.wait(lock,[this]() { return pktQueue.size() < MAX_PACKET_SIZE || m_stop.load(); });

    if(m_stop){
        return;
    }

    FFPacket* ffpkt = static_cast<FFPacket*>(av_mallocz(sizeof(FFPacket)));
    av_init_packet(&ffpkt->packet);
    ffpkt->type = NULLP;
    ffpkt->serial = this->serial; //NULLP（结束包）属于当前播放周期，它不开启新的解码周期，所以不自增
    ffpkt->packet.data = nullptr;
    pktQueue.push(ffpkt);

    cond.notify_one();
}

void FFAPacketQueue::flushQueue()
{
    while(1){
        FFPacket* pkt = peekQueue();
        // 如果包为空 或者 遇到当前周期的包，则停止清理
        if(pkt == nullptr || pkt->serial == this->serial){
            break;
        }
        // 如果包序号小于当前周期报序号，则视为上一个seek周期遗留的旧包，则清理掉
        else{
            std::lock_guard<std::mutex>lock(mutex);
            pktQueue.pop();                // 移除旧包
            av_packet_unref(&pkt->packet); // 释放包内数据
            av_freep(&pkt);                // 释放包结构内存
        }
    }
    cond.notify_one();
}

size_t FFAPacketQueue::getSerial()
{
    return serial.load();
}

void FFAPacketQueue::clearQueue()
{
    std::lock_guard<std::mutex>lock(mutex);
    while(!pktQueue.empty()){
        FFPacket* ffpkt = pktQueue.front();
        pktQueue.pop();
        if(ffpkt!=nullptr){
            av_packet_unref(&ffpkt->packet);
            av_freep(&ffpkt);
        }
    }
}

void FFAPacketQueue::wakeAllThread()
{
    m_stop = true;
    cond.notify_all();
}

void FFAPacketQueue::close()
{
    wakeAllThread();
    clearQueue();
}

void FFAPacketQueue::start()
{
    m_stop = false;
}

