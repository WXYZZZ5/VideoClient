#include "ffadecoderthread.h"
#include"queue/ffapacketqueue.h"
#include"decoder/ffadecoder.h"
#include"queue/ffpacket.h"
#include"player/ffplayercontext.h"
#include"event/ffendevent.h"
#include"queue/ffeventqueue.h"
FFADecoderThread::FFADecoderThread()
{

}

FFADecoderThread::~FFADecoderThread()
{
    if(aPktQueue){
        delete aPktQueue;
        aPktQueue = nullptr;
    }
    if(aDecoder) {
        delete aDecoder;
        aDecoder = nullptr;
    }
    if(playerCtx){
        delete playerCtx;
        playerCtx = nullptr;
    }

}

void FFADecoderThread::init(FFADecoder *aDecoder_, FFAPacketQueue* aPktQueue_)
{
    aDecoder = aDecoder_;
    aPktQueue = aPktQueue_;

    playerCtx = new FFPlayerContext();
    playerCtx->aDecoderThread = this;
    playerCtx->aPktQueue = aPktQueue_;

}

void FFADecoderThread::wakeAllThread()
{
    if(aPktQueue){
        aPktQueue->wakeAllThread();
    }
    if(aDecoder){
        aDecoder->wakeAllThread();
    }
}

void FFADecoderThread::close()
{
    if(aDecoder){
        aDecoder->close();
    }
}

void FFADecoderThread::run()
{
    while(!m_stop){
        FFPacket* pkt = aPktQueue->dequeue();
        if(pkt == nullptr){
            continue;
        }
        /*如果是 FLUSH 包：
         * pkt->serial = 5
         * aPktQueue->getSerial() = 6
         * 条件 pkt->serial != getSerial() 为 true → 触发 flush 逻辑。
         *
         * 如果是 FLUSH 之后入队的普通包（例如新周期的数据包）：
         * pkt->serial = 6
         * getSerial() = 6
         * 条件为 false → 正常解码。
         */
        if(pkt->serial != aPktQueue->getSerial()){ //seek操作
            aPktQueue->flushQueue();
            // AVFrame维护的是已解码的帧队列，这些帧是在 seek 之前解码得到的，它们对应的是旧时间位置的数据
            aDecoder->flushQueue();
            aDecoder->flushDecoder();

            std::cerr<<"flush aDecoder"<<std::endl;
        }
        else{
            if(pkt->type == NULLP && pkt->packet.data == nullptr){ //读取完毕，冲刷解码器
                aDecoder->decode(nullptr);
                std::cerr<< "null apacket !"<< std::endl;
                aDecoder->enqueueNull();
            }
            else{ //正常读取
                aDecoder->decode(&pkt->packet);

            }
            av_packet_unref(&pkt->packet);
            av_freep(&pkt);
        }
    }
}

void FFADecoderThread::sendEndEvent()
{
    FFEvent* stopEv =new FFEndEvent(playerCtx);
    FFEventQueue::getInstance().enqueue(stopEv);
}


