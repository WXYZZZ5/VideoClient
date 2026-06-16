#ifndef FFDECODERTHREAD_H
#define FFDECODERTHREAD_H

#include"ffthread.h"
extern "C"
{
#include"libavformat/avformat.h"
}

class FFAPacketQueue;
class FFADecoder;
class FFPlayerContext;
class FFADecoderThread : public FFThread
{
public:
    FFADecoderThread();
    virtual ~FFADecoderThread() override;

    void init(FFADecoder* aDecoder_,FFAPacketQueue* aPktQueue_);
    void wakeAllThread();
    void close();
protected:
    virtual void run() override;

private:
    void sendEndEvent();
private:
    FFAPacketQueue* aPktQueue = nullptr;
    FFADecoder* aDecoder = nullptr;
    FFPlayerContext* playerCtx = nullptr;
};

#endif // FFDECODERTHREAD_H
