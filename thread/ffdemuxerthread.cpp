#include "ffdemuxerthread.h"
#include"demuxer/ffdemuxer.h"
#include"queue/ffvpacketqueue.h"
#include"queue/ffapacketqueue.h"
#include"queue/ffeventqueue.h"
#include"player/ffplayercontext.h"
#include"event/ffendevent.h"
FFDemuxerThread::FFDemuxerThread()

{

}

FFDemuxerThread::~FFDemuxerThread()
{
    if(demuxer){
        delete demuxer;
        demuxer = nullptr;
    }
    if(playerCtx){
        delete playerCtx;
        playerCtx = nullptr;
    }
}


void FFDemuxerThread::init(FFDemuxer* demuxer_)
{
    demuxer = demuxer_;

    playerCtx = new FFPlayerContext();
    playerCtx->demuxerThread = this;
}

void FFDemuxerThread::wakeAllThread()
{
    if(demuxer){
        demuxer->wakeAllThread();
    }
    cond.notify_all();
}

void FFDemuxerThread::seek(int64_t seekSec)
{
    if(demuxer){
        demuxer->seek(seekSec);
    }
    cond.notify_all();
}

void FFDemuxerThread::close()
{
    if(demuxer){
        demuxer->close();
    }
    cond.notify_all();
}

void FFDemuxerThread::run()
{
    while(!m_stop){
        int ret = demuxer->demux();
        if(ret == 1){ //EOF
            std::unique_lock<std::mutex>lock(mutex);
            std::cerr<<"EOF waiting..."<<std::endl;
            cond.wait(lock);
        }
        if(m_stop){
            break;
        }
    }

}

void FFDemuxerThread::sendStopEvent()
{
    FFEvent* stopEv = new FFEndEvent(playerCtx);
    FFEventQueue::getInstance().enqueue(stopEv);
}
