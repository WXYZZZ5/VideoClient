#ifndef FFPAUSEEVENT_H
#define FFPAUSEEVENT_H

#include"ffevent.h"

/**
 * @brief 暂停/恢复播放事件
 *
 * 同时暂停音频渲染器和视频渲染器（音视频同步暂停）。
 */
class FFPauseEvent : public FFEvent
{
public:
    FFPauseEvent(FFPlayerContext* playerCtx);
    virtual ~FFPauseEvent()override;

    virtual void work() override;
};

#endif // FFPAUSEEVENT_H
