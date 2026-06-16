#ifndef FFVOLUMEEVENT_H
#define FFVOLUMEEVENT_H

#include"ffevent.h"

/**
 * @brief 音量调节事件
 *
 * 设置音频渲染器的音量（0.0 ~ 1.0）。
 */
class FFVolumeEvent : public FFEvent
{
public:
    FFVolumeEvent(FFPlayerContext* playerCtx,double volume_);

    virtual void work()override;

private:
    double volume;
};

#endif // FFVOLUMEEVENT_H
