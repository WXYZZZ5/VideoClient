#include "ffreadyevent.h"

FFReadyEvent::FFReadyEvent(FFPlayerContext *playerCtx, int totalSec_,float aspect_)
    :FFEvent (playerCtx),totalSec(totalSec_),aspect(aspect_)
{

}

FFReadyEvent::~FFReadyEvent()
{

}

void FFReadyEvent::work()
{
    // 通知 UI 窗口初始化总时长和宽高比
    QMetaObject::invokeMethod(playerCtx->playerWindow,"initPlayerTotalSec",
                              Qt::QueuedConnection,Q_ARG(int,totalSec),Q_ARG(float,aspect));
}
