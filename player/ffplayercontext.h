#ifndef FFPLAYERCONTEXT_H
#define FFPLAYERCONTEXT_H

class FFARender;
class FFVRender;

class FFADecoderThread;
class FFVDecoderThread;

class FFDemuxerThread;

class FFPlayerWindow;

class FFAPacketQueue;
class FFVPacketQueue;

class FFAFrameQueue;
class FFVFrameQueue;

class FFDemuxer;
class FFADecoder;
class FFVDecoder;

struct FFPlayerContext
{
    FFPlayerContext(){
        aRender = nullptr;
        vRender = nullptr;

        aDecoderThread = nullptr;
        vDecoderThread = nullptr;

        demuxerThread = nullptr;

        playerWindow = nullptr;

        aPktQueue = nullptr;
        vPktQueue = nullptr;

        aFrmQueue = nullptr;
        vFrmQueue = nullptr;

        demuxer = nullptr;

        aDecoder = nullptr;
        vDecoder = nullptr;
    }

    FFARender* aRender;
    FFVRender* vRender;

    FFADecoderThread* aDecoderThread;
    FFVDecoderThread* vDecoderThread;

    FFDemuxerThread* demuxerThread;

    FFPlayerWindow* playerWindow;

    FFAPacketQueue* aPktQueue;
    FFVPacketQueue* vPktQueue;

    FFAFrameQueue* aFrmQueue;
    FFVFrameQueue* vFrmQueue;

    FFDemuxer* demuxer;
    FFADecoder* aDecoder;
    FFVDecoder* vDecoder;
};



#endif // FFPLAYERCONTEXT_H
