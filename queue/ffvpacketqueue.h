#ifndef FFVPACKETQUEUE_H
#define FFVPACKETQUEUE_H

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
class FFVPacketQueue
{
public:
    explicit FFVPacketQueue();
    ~FFVPacketQueue();

    FFPacket* dequeue();
    FFPacket *peekQueue();
    void enqueue(AVPacket* pkt);
    void enqueueFlush();
    void enqueueNull();
    void flushQueue();

    size_t getSerial();

    void wakeAllThread();
    void clearQueue();
    void close();
    void start();
private:
    std::mutex mutex;
    std::condition_variable cond;
    std::atomic<size_t> serial;
    std::queue<FFPacket*>pktQueue;
    std::atomic<bool>m_stop;
};

#endif // FFPACKETQUEUE_H
