#include "ffpauseevent.h"

FFPauseEvent::FFPauseEvent(FFPlayerContext *playerCtx)
    :FFEvent (playerCtx)
{

}

FFPauseEvent::~FFPauseEvent()
{

}

void FFPauseEvent::work()
{
    playerCtx->aRender->pause();
    playerCtx->vRender->pause();
}


