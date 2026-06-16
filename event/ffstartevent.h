#ifndef FFSTARTEVENT_H
#define FFSTARTEVENT_H

#include "ffevent.h"

// 前置声明相关类，避免头文件循环包含问题
class FFDemuxerThread;
class FFVDecoderThread;
class FFADecoderThread;
class FFARender;
class FFVRender;
class FFDemuxer;
class FFADecoder;
class FFVDecoder;
class FFAPacketQueue;
class FFVPacketQueue;
class FFAFrameQueue;
class FFVFrameQueue;
class FFPlayerWindow;

/**
 * @brief 启动播放事件（打开新文件）
 *
 * 职责：
 * 1. 停止所有现有组件（如果已经在播放）。
 * 2. 使用新 URL 重新初始化所有组件（解封装、解码器、队列、渲染器）。
 * 3. 启动所有线程。
 *
 * 这样设计可以在不重建播放器对象的情况下切换文件。
 */
class FFStartEvent : public FFEvent
{
public:
    FFStartEvent(FFPlayerContext* playerCtx, const std::string& url);

    virtual void work() override;

private:
    void stopAll();   // 停止所有组件并等待
    void initAll();   // 重新初始化所有组件
    void startAll();  // 启动所有线程

    // 存储所有组件的指针（从 context 中提取）
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

    std::string url; // 要打开的文件路径或流地址
};

#endif // FFSTARTEVENT_H
