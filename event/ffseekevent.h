#ifndef FFSEEKEVENT_H
#define FFSEEKEVENT_H

#include"ffevent.h"

/**
 * @brief 跳转（seek）事件
 *
 * 通知解封装线程进行跳转。
 */
class FFSeekEvent : public FFEvent
{
public:
    FFSeekEvent(FFPlayerContext* playerCtx,int64_t seekSec_);

    virtual void work() override;

private:
    // 目标时间（秒）
    int64_t seekSec;
};

#endif // FFSEEKEVENT_H
