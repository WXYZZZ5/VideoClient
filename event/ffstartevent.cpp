#include "ffstartevent.h"

FFStartEvent::FFStartEvent(FFPlayerContext* playerCtx, const std::string& url_)
    : FFEvent(playerCtx), url(url_)
{
    // 从上下文中提取所有组件指针
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

void FFStartEvent::work()
{
    stopAll();   // 先完全停止当前播放（如果有）
    initAll();   // 重新初始化所有组件
    startAll();  // 启动线程开始播放
}

void FFStartEvent::stopAll()
{
    // 与 FFEndEvent::work() 逻辑完全相同
    demuxerThread->stop();
    demuxerThread->wakeAllThread();
    demuxerThread->wait();
    demuxerThread->close();

    std::cerr<<"demuxerThread stop!"<<std::endl;

    aRender->wakeAllThread();
    vRender->wakeAllThread();

    aDecoderThread->stop();
    aDecoderThread->wait();
    aDecoderThread->close();

    std::cerr<<"aDecoderThread stop!"<<std::endl;
    vDecoderThread->stop();
    vDecoderThread->wait();
    vDecoderThread->close();
    std::cerr<<"vDecoderThread stop!"<<std::endl;

    aPktQueue->close();
    vPktQueue->close();
    std::cerr<<"aPktQueue stop!"<<std::endl;

    aFrmQueue->close();
    vFrmQueue->close();
    std::cerr<<"aFrmQueue stop!"<<std::endl;

    aRender->stop();
    aRender->wait();
    aRender->close();
    std::cerr<<"aRender stop!"<<std::endl;

    vRender->stop();
    vRender->wait();
    vRender->close();
    std::cerr<<"vRender stop!"<<std::endl;
}

void FFStartEvent::initAll()
{
    // 重新初始化解封装器（传入新 URL）
    demuxer->init(url, aPktQueue, vPktQueue);
    demuxerThread->init(demuxer);

    // 初始化音频解码器（从解封装器获取音频流）
    aDecoder->init(demuxer->getAStream(), aFrmQueue);
    aDecoderThread->init(aDecoder, aPktQueue);

    // 初始化视频解码器
    vDecoder->init(demuxer->getVStream(), vFrmQueue);
    vDecoderThread->init(vDecoder, vPktQueue);

    // 初始化渲染器（传入帧队列和解码器指针）
    aRender->init(aFrmQueue, aDecoder, playerWindow);
    vRender->init(vDecoder, vFrmQueue, playerWindow);
}

void FFStartEvent::startAll()
{
    // 启动所有队列（重置停止标志）
    aPktQueue->start();
    vPktQueue->start();

    aFrmQueue->start();
    vFrmQueue->start();

    // 启动线程
    demuxerThread->start();

    vDecoderThread->start();
    aDecoderThread->start();

    vRender->start();
    vRender->wakeAllThread();

    aRender->start();
    aRender->wakeAllThread();
}
