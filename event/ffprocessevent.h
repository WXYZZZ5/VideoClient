#ifndef FFPROCESSEVENT_H
#define FFPROCESSEVENT_H

#include"ffevent.h"

class FFPlayerWindow;

/**
 * @brief 播放进度事件（每秒触发）
 *
 * 将当前播放秒数传递给 UI 窗口，用于更新进度条滑块和当前时间显示。
 */
class FFProcessEvent : public FFEvent
{
public:
    FFProcessEvent(FFPlayerContext* playerCtx,int curSec_);
    virtual ~FFProcessEvent()override;

    virtual void work()override;

private:
    int curSec; // 当前播放位置（秒）
};

#endif // FFPROCESSEVENT_H
