#ifndef FFVDECODERTHREAD_H
#define FFVDECODERTHREAD_H


#include"ffthread.h"
extern "C"
{
#include"libavformat/avformat.h"
}

class FFVPacketQueue;
class FFVDecoder;
class FFPlayerContext;

class FFVDecoderThread : public FFThread
{
public:
    FFVDecoderThread();
    virtual ~FFVDecoderThread() override;

    void init(FFVDecoder* vDecoder_,FFVPacketQueue* vPktQueue_);
    void wakeAllThread();
    void close();
protected:
    virtual void run() override;

private:
    void sendEndEvent();
private:
    FFVPacketQueue* vPktQueue = nullptr;
    FFVDecoder* vDecoder = nullptr;
    FFPlayerContext* playerCtx = nullptr;
};

#endif // FFVDECODERTHREAD_H
