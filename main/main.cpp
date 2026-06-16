#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QAudioOutput>
#include <QBuffer>
#include<QMetaType>
#include"queue/ffvpacketqueue.h"
#include"render/ffarender.h"
#include"render/ffvrender.h"
#include"queue/ffapacketqueue.h"
#include"decoder/ffvdecoder.h"
#include"thread/ffdemuxerthread.h"
#include"demuxer/ffdemuxer.h"
#include"thread/ffadecoderthread.h"
#include"thread/ffvdecoderthread.h"
#include"queue/ffaframequeue.h"
#include"queue/ffvframequeue.h"
#include"player/ffplayercontext.h"
#include"ui/ffplayerwindow.h"
#include"event/ffeventloop.h"
#include"queue/ffeventqueue.h"
#include"thread/ffthreadpool.h"

//注册类型
void registerType(){
    qRegisterMetaType<int64_t>("int64_t");
    qRegisterMetaType<uint8_t*>("uint8_t*");
    qRegisterMetaType<AVFrame*>("AVFrame*");
}

static FFARender* aRender= nullptr;
static FFVRender* vRender = nullptr;

static FFADecoder* aDecoder = nullptr;
static FFVDecoder* vDecoder = nullptr;

static FFADecoderThread* aDecoderThread = nullptr;
static FFVDecoderThread* vDecoderThread = nullptr;

static FFAPacketQueue* aPktQueue = nullptr;
static FFVPacketQueue* vPktQueue = nullptr;

static FFAFrameQueue* aFrmQueue = nullptr;
static FFVFrameQueue* vFrmQueue = nullptr;

static FFDemuxerThread* demuxerThread = nullptr;
static FFDemuxer* demuxer = nullptr;

static FFPlayerWindow* playerWindow = nullptr;

static FFPlayerContext* playerCtx = nullptr;

static FFEventLoop* evLoop = nullptr;
static FFThreadPool* threPool = nullptr;

void util(){
    aRender = new FFARender();
    vRender = new FFVRender();

    aDecoder = new FFADecoder();
    vDecoder = new FFVDecoder();

    aDecoderThread = new FFADecoderThread();
    vDecoderThread = new FFVDecoderThread();

    aPktQueue = new FFAPacketQueue();
    vPktQueue = new FFVPacketQueue();

    aFrmQueue = new FFAFrameQueue();
    vFrmQueue = new FFVFrameQueue();

    demuxer = new FFDemuxer();
    demuxerThread = new FFDemuxerThread();

    playerWindow = new FFPlayerWindow();
    playerCtx = new FFPlayerContext();

    evLoop = new FFEventLoop();

    threPool = new FFThreadPool();
    threPool->init(4);
    evLoop->init(&FFEventQueue::getInstance(),threPool);

    playerCtx->demuxer = demuxer;
    playerCtx->demuxerThread = demuxerThread;

    playerCtx->aDecoderThread = aDecoderThread;
    playerCtx->aDecoder = aDecoder;

    playerCtx->vDecoderThread = vDecoderThread;
    playerCtx->vDecoder = vDecoder;

    playerCtx->aRender = aRender;
    playerCtx->vRender = vRender;

    playerCtx->aPktQueue = aPktQueue;
    playerCtx->vPktQueue = vPktQueue;

    playerCtx->aFrmQueue = aFrmQueue;
    playerCtx->vFrmQueue = vFrmQueue;

    playerCtx->playerWindow = playerWindow;


    playerWindow->init(playerCtx);

    evLoop->start();

    registerType();
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QIcon icon(":/picture/logo.png");
    a.setWindowIcon(icon);
    util();
    playerWindow->show();


    return a.exec();
}
