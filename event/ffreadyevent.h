#ifndef FFREADYEVENT_H
#define FFREADYEVENT_H

#include"ffevent.h"

/**
 * @brief 播放器准备就绪事件（音频或视频首次获取到参数后触发）
 *
 * 将总时长和视频宽高比传递给 UI，用于初始化进度条范围和窗口比例。
 */
class FFReadyEvent : public FFEvent
{
public:
    FFReadyEvent(FFPlayerContext* playerCtx,int totalSec_,float aspect_);
    virtual ~FFReadyEvent() override;

    virtual void work()override;

private:
    int totalSec;   // 总时长（秒）
    float aspect = 0;   // 视频宽高比（宽/高）
};

#endif // FFREADYEVENT_H
