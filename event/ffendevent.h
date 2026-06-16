#ifndef FFEndEvent_H
#define FFEndEvent_H

#include"ffevent.h"

/**
 * @brief 播放结束事件（正常播放完毕或主动停止时触发）
 *
 * 职责：按照严格顺序停止所有播放器组件并释放资源。
 * 顺序很重要：先停止生产者（解封装线程），再停止解码线程，最后停止渲染线程。
 * 最后通过 Qt 信号槽清空画面（黑屏）。
 */
class FFEndEvent : public FFEvent
{
public:
    FFEndEvent(FFPlayerContext* playerCtx);
    virtual ~FFEndEvent() override;

    virtual void work() override;

private:
    FFDemuxerThread* demuxerThread;
    FFVDecoderThread* vDecoderThread;
    FFADecoderThread* aDecoderThread;
    FFARender* aRender;
    FFVRender* vRender;
    FFDemuxer* demuxer;
    FFADecoder* aDecoder;
    FFVDecoder* vDecoder;
    FFAPacketQueue* aPktQueue;
    FFVPacketQueue* vPktQueue;
    FFAFrameQueue* aFrmQueue;
    FFVFrameQueue* vFrmQueue;
    FFPlayerWindow* playerWindow;
};

#endif // FFEndEvent_H
