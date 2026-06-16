#include"ffvdecoder.h"
#include"queue/ffvframequeue.h"
#include"resampler/ffvresampler.h"

FFVDecoder::FFVDecoder()
    :m_stop(false){

}

FFVDecoder::~FFVDecoder()
{
    close();
}

void FFVDecoder::init(AVStream *stream_,FFVFrameQueue* frmQueue_)
{
    stream = stream_;
    frmQueue = frmQueue_;

    // 根据流的编码 ID 查找解码器
    AVCodec* codec = avcodec_find_decoder(stream->codecpar->codec_id);
    if(codec == nullptr){
        std::cerr<<"找不到视频解码器"<<std::endl;
        return;
    }

    // 分配解码器上下文
    codecCtx = avcodec_alloc_context3(codec);
    if(codecCtx== nullptr){
        std::cerr<<"分配解码器上下文失败"<<std::endl;
        avcodec_free_context(&codecCtx);
        return;
    }

    // 将流参数复制到解码器上下文中
    int ret = avcodec_parameters_to_context(codecCtx,stream->codecpar);
    if(ret < 0)
    {
        printError(ret);
        avcodec_free_context(&codecCtx);
        return;
    }

    // 设置多线程解码（可选，但能显著提升速度）
    // thread_type = 0x01 表示 FF_THREAD_FRAME（帧级并行）
    // thread_count = CPU 核数的一半（避免过多线程争抢）
    codecCtx->thread_type = 0x01;
    codecCtx->thread_count = av_cpu_count() >> 1;

    // 显式设置帧率，避免 codecCtx->framerate 为 {0,0}
    // FFmpeg 的 avcodec_open2 不会自动设置 framerate
    //（因为 codecCtx->stream 为空指针），导致后续计算帧间隔时
    // av_q2d(0/0)=NaN → standardInterval=INT_MIN → 定时器失控。
    if (codecCtx->framerate.num <= 0 || codecCtx->framerate.den <= 0) {
        codecCtx->framerate = stream->r_frame_rate;
    }

    // 打开解码器
    ret = avcodec_open2(codecCtx,codec,nullptr);
    if(ret < 0)
    {
        printError(ret);
        avcodec_free_context(&codecCtx);
        return;
    }

}

void FFVDecoder::flushDecoder()
{
    // 清空解码器内部的所有缓冲区
    avcodec_flush_buffers(codecCtx);
}

int FFVDecoder::getTotalSec()
{
    // stream->duration 是流的总时长（以 time_base 为单位）
    // av_q2d 将 AVRational 转换为 double
    return static_cast<int>(stream->duration * av_q2d(stream->time_base));
}

FFVideoPars* FFVDecoder::getVideoPars()
{
    return swsvPars;
}

void FFVDecoder::enqueueNull()
{
    frmQueue->enqueueNull();
}

void FFVDecoder::wakeAllThread()
{
    frmQueue->wakeAllThread();
}

void FFVDecoder::stop()
{
    m_stop = true;
}

void FFVDecoder::flushQueue()
{
    frmQueue->flushQueue();
}

void FFVDecoder::close()
{
    if(codecCtx){
        avcodec_free_context(&codecCtx);
    }
    if(vPars){
        delete vPars;
        vPars = nullptr;
    }
    if(resampler){
        delete resampler;
        resampler = nullptr;
    }
    if(swsvPars){
        delete swsvPars;
        swsvPars = nullptr;
    }
}

void FFVDecoder::initResampler()
{
    resampler->init(vPars,swsvPars);
}

void FFVDecoder::initVideoPars(AVFrame *frame)
{
    // 原始参数
    vPars->timeBase = stream->time_base;
    vPars->pixFmtEnum = codecCtx->pix_fmt;       // 解码器输出的像素格式（如 YUV444P、NV12 等）
    vPars->frameRate = codecCtx->framerate;      // 帧率
    vPars->width = frame->width;
    vPars->height = frame->height;

    // 目标参数：复制原始参数，但强制像素格式为 YUV420P（最常用、兼容性最好）
    memcpy(swsvPars,vPars,sizeof(FFVideoPars));
    swsvPars->pixFmtEnum = AV_PIX_FMT_YUV420P;
}

void FFVDecoder::decode(AVPacket *packet)
{
    // 将压缩数据包发送给解码器
    int ret = avcodec_send_packet(codecCtx,packet);
    if(ret < 0 && ret != AVERROR(EAGAIN)){
        printError(ret);
        avcodec_free_context(&codecCtx);
        return;
    }

    // 分配一个空的 AVFrame 结构体，用于存放解码后的原始帧
    AVFrame* frame = av_frame_alloc();
    // 循环取帧，直到解码器暂时没有更多输出
    while(ret >= 0){
        ret = avcodec_receive_frame(codecCtx,frame);

        if(ret < 0){
            if(ret == AVERROR_EOF){
                break; // 解码器已无数据，正常结束
            }
            else if(ret == AVERROR(EAGAIN)){
                continue; // 需要更多输入，跳出循环（等待下一个 packet）
            }
            else{
                printError(ret);
                av_frame_free(&frame);
                avcodec_free_context(&codecCtx);
                return;
            }
        }
        else{
            // 如果是第一次解码出帧，则初始化参数结构体
            if(vPars == nullptr){
                vPars = new FFVideoPars();
                swsvPars = new FFVideoPars();

                initVideoPars(frame); // 从当前帧提取参数
                // 如果原始像素格式不是目标 YUV420P，则创建转换器
                if(vPars->pixFmtEnum != swsvPars->pixFmtEnum){
                    resampler = new FFVResampler();
                    initResampler();
                }
            }

            if(resampler){
                AVFrame* swsFrame = nullptr;
                resampler->resample(frame,&swsFrame);
                av_frame_unref(frame);
                // 线程停止情况：
                if(m_stop.load(std::memory_order_acquire)){
                    av_frame_unref(swsFrame);
                    av_frame_free(&swsFrame);
                    m_stop.store(false,std::memory_order_release);
                    break;
                }
                else{
                    // 正常情况：将转换后的帧克隆一份放入帧队列
                    // 为什么用 av_frame_clone？因为队列可能跨线程使用，队列内部需要一份独立的拷贝。
                    // 克隆后，当前 swsFrame 就可以释放了。
                    frmQueue->enqueue(av_frame_clone(swsFrame));
                    av_frame_free(&swsFrame);
                    av_frame_unref(swsFrame);
                }
            }
             // 无需格式转换的情况（解码器输出已经是 YUV420P）
            else{
                if(m_stop.load(std::memory_order_acquire)){
                    av_frame_unref(frame);
                    m_stop.store(false,std::memory_order_release);
                    break;
                }
                else{
                    // 同样需要克隆后入队，因为原始 frame 后续会被释放
                    frmQueue->enqueue(av_frame_clone(frame));
                    av_frame_unref(frame);
                    //                    std::cerr<<"decoder eunqueue!"<<std::endl;
                }
            }
        }
    }
    av_frame_free(&frame);
}

void FFVDecoder::printError(int ret)
{
    char errorBuffer[AV_ERROR_MAX_STRING_SIZE];
    int res = av_strerror(ret,errorBuffer,sizeof errorBuffer);
    if(res < 0){
        std::cerr << "Unknow Error!"<<std::endl;
    }
    else{
        std::cerr<<"Error:"<<errorBuffer<<std::endl;
    }

}
