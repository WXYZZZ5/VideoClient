#include "ffendevent.h"



FFEndEvent::FFEndEvent(FFPlayerContext *playerCtx)
    :FFEvent(playerCtx)
{
    demuxerThread = playerCtx->demuxerThread;
    vDecoderThread = playerCtx->vDecoderThread;
    aDecoderThread = playerCtx->aDecoderThread;
    aRender = playerCtx->aRender;
    vRender = playerCtx->vRender;
    demuxer = playerCtx->demuxer;
    aDecoder = playerCtx->aDecoder;
    vDecoder = playerCtx->vDecoder;
    aPktQueue = playerCtx->aPktQueue;
    vPktQueue = playerCtx->vPktQueue;
    aFrmQueue = playerCtx->aFrmQueue;
    vFrmQueue = playerCtx->vFrmQueue;
    playerWindow = playerCtx->playerWindow;
}

FFEndEvent::~FFEndEvent()
{

}

// 先停止生产者（解封装）可以避免新数据入队，解码线程处理完已有数据后自然停止。
// 使用 QMetaObject::invokeMethod 确保清屏在主线程执行（OpenGL 操作必须在主线程）
void FFEndEvent::work()
{
    // 1. 停止解封装线程（生产者）
    demuxerThread->stop();
    demuxerThread->wakeAllThread();   // 唤醒可能阻塞在队列上的线程
    demuxerThread->wait();            // 等待线程退出
    demuxerThread->close();           // 释放内部资源
    std::cerr << "demuxerThread stop!" << std::endl;

    // 2. 唤醒渲染线程（防止它们因等待队列而卡住）
    aRender->wakeAllThread();
    vRender->wakeAllThread();

    // 3. 停止解码线程（消费者）
    aDecoderThread->stop();
    aDecoderThread->wait();
    aDecoderThread->close();
    std::cerr << "aDecoderThread stop!" << std::endl;

    vDecoderThread->stop();
    vDecoderThread->wait();
    vDecoderThread->close();
    std::cerr << "vDecoderThread stop!" << std::endl;

    // 4. 关闭队列（释放所有未处理的数据包和帧）
    aPktQueue->close();
    vPktQueue->close();
    std::cerr << "aPktQueue stop!" << std::endl;

    aFrmQueue->close();
    vFrmQueue->close();
    std::cerr << "aFrmQueue stop!" << std::endl;

    // 5. 停止渲染线程（最后停止，确保画面显示完最后一帧）
    aRender->stop();
    aRender->wait();
    aRender->close();
    std::cerr << "aRender stop!" << std::endl;

    vRender->stop();
    vRender->wait();
    vRender->close();
    std::cerr << "vRender stop!" << std::endl;

    // 6. 最后通过 Qt 信号槽在主线程中清屏（显示黑屏）
    QMetaObject::invokeMethod(playerWindow, "setBlackScreen", Qt::QueuedConnection);
}
