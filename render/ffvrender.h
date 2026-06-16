#ifndef FFVRENDER_H
#define FFVRENDER_H

#include"decoder/ffvdecoder.h"
#include<chrono>
#include<atomic>
extern "C"{
#include"libavformat/avformat.h"
}

class FFTimer;
class FFVFrameQueue;
class FFPlayerWindow;
class FFPlayerContext;

/**
 * @brief 视频渲染控制器（外壳类）
 *
 * 职责：
 * - 创建并管理 FFTimer 对象。
 * - 将外部的播放控制请求（开始、停止、暂停、速度等）转发给 FFTimer。
 * - 不负责具体的图像渲染，渲染由 FFGLRenderWidget 完成。
 */
class FFVRender
{
public:
    FFVRender();
    ~FFVRender();

    void init(FFVDecoder* vDecoder_, FFVFrameQueue* frmQueue_,FFPlayerWindow* playerWindow_);
    void start();
    void stop();
    void seek();
    void pause();
    void wait();
    void close();
    void setSpeed(float speed);

    void wakeAllThread();
private:
    void initTimer();

private:
    FFVDecoder* vDecoder = nullptr;   // 视频解码器（用于获取帧率等参数）
    FFVFrameQueue* frmQueue = nullptr;// 视频帧队列（解码线程产出的帧）
    FFPlayerWindow* playerWindow = nullptr; // 播放器窗口（用于传递渲染数据）

    FFTimer* timer = nullptr;   // 同步定时器（核心同步逻辑）

};

#endif // FFVRENDER_H
