#ifndef FFEVENT_H
#define FFEVENT_H

#include<QMetaObject>
#include"ui/ffplayerwindow.h"
#include"thread/ffdemuxerthread.h"
#include"thread/ffadecoderthread.h"
#include"thread/ffvdecoderthread.h"
#include"render/ffarender.h"
#include"render/ffvrender.h"
#include"player/ffplayercontext.h"
#include"queue/ffapacketqueue.h"
#include"queue/ffvpacketqueue.h"
#include"queue/ffaframequeue.h"
#include"queue/ffvframequeue.h"

#include"decoder/ffadecoder.h"
#include"decoder/ffvdecoder.h"
#include"demuxer/ffdemuxer.h"

// 设计模式：命令模式（Command Pattern），将请求封装为对象，便于排队、异步执行。
class FFEvent
{
public:
    FFEvent(FFPlayerContext* playerCtx_);
    virtual ~FFEvent();

    virtual void work() = 0;

protected:
    // 播放器全局上下文，包含了所有组件指针
    FFPlayerContext* playerCtx = nullptr;

};

#endif // FFEVENT_H

