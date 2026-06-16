#ifndef FFSPEEDEVENT_H
#define FFSPEEDEVENT_H

#include"ffevent.h"

/**
 * @brief 变速播放事件
 *
 * 同时设置音频渲染器和视频渲染器的播放速度。
 */
class FFSpeedEvent : public FFEvent
{
public:
    FFSpeedEvent(FFPlayerContext* playerCtx,float speed_);

    virtual void work();
private:
    float speed;
};

#endif // FFSPEEDEVENT_H
