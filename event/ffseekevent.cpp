#include "ffseekevent.h"
#include"globalclock.h"
FFSeekEvent::FFSeekEvent(FFPlayerContext *playerCtx, int64_t seekSec_)
    :FFEvent (playerCtx),seekSec(seekSec_)
{

}

void FFSeekEvent::work()
{
    // 只通知解封装线程 seek，解封装线程会处理队列 flush 等操作
    playerCtx->demuxerThread->seek(seekSec);
}
