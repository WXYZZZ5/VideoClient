#include "ffprocessevent.h"
#include"player/ffplayercontext.h"


FFProcessEvent::FFProcessEvent(FFPlayerContext *playerCtx, int curSec_)
  :FFEvent (playerCtx),curSec(curSec_)
{

}

FFProcessEvent::~FFProcessEvent()
{

}

void FFProcessEvent::work()
{
    // 音频渲染线程（FFARender）每秒计算一次当前进度，但它不能直接调用 UI 函数（跨线程不安全），
    // 因此构造 FFProcessEvent 入队，由事件循环在合适的时机（通过线程池）执行，最终通过 invokeMethod 切换到主线程更新 UI。
    // 在主线程中调用 UI 窗口的 showPlayerProcessSec 槽函数
    QMetaObject::invokeMethod(playerCtx->playerWindow,"showPlayerProcessSec",
                              Qt::QueuedConnection,Q_ARG(int,curSec));
}
