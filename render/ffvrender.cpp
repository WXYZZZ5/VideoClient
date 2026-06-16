#include "ffvrender.h"
#include"timer/fftimer.h"
#include"queue/ffvframequeue.h"
#include"ui/ffplayerwindow.h"
#include"globalclock.h"
#include<QMetaObject>
#include<iomanip>
#include"event/ffreadyevent.h"
#include"queue/ffeventqueue.h"
#include"player/ffplayercontext.h"
#include"event/ffendevent.h"

FFVRender::FFVRender()
{

}

FFVRender::~FFVRender()
{
    if(timer){
        delete timer;
        timer = nullptr;
    }
}

void FFVRender::init(FFVDecoder *vDecoder_, FFVFrameQueue *frmQueue_, FFPlayerWindow *playerWindow_)
{
    vDecoder = vDecoder_;
    frmQueue = frmQueue_;
    playerWindow = playerWindow_;

    initTimer();
}


void FFVRender::start()
{
    if(timer)
        timer->start();
}

void FFVRender::stop()
{
    if(timer)
        timer->stop();
}

void FFVRender::seek()
{
    if(timer)
        timer->seek();
}

void FFVRender::pause()
{
    if(timer)
        timer->pause();
}

void FFVRender::wait()
{
    if(timer)
        timer->wait();
}

void FFVRender::close()
{
    if(timer){
        timer->close();
    }
}

void FFVRender::setSpeed(float speed)
{
    if(timer)
        timer->setSpeed(speed);
}

void FFVRender::wakeAllThread()
{
    if(timer){
        timer->wakeAllThread();
    }
}

void FFVRender::initTimer()
{
    timer = new FFTimer();
    timer->init(playerWindow,vDecoder,frmQueue,this);
}
