#include "ffvolumeevent.h"

FFVolumeEvent::FFVolumeEvent(FFPlayerContext *playerCtx,double volume_)
    :FFEvent (playerCtx),volume(volume_)
{

}

void FFVolumeEvent::work()
{
    playerCtx->aRender->setVolume(volume);
}
