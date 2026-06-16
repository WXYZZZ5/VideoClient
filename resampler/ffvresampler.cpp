#include "ffvresampler.h"
#include"decoder/ffvdecoder.h"

FFVResampler::FFVResampler()
{

}

FFVResampler::~FFVResampler()
{
    if(swsCtx){
        sws_freeContext(swsCtx);
    }
    if(srcPars){
        delete srcPars;
        srcPars = nullptr;
    }
    if(dstPars){
        delete dstPars;
        dstPars = nullptr;
    }
    if(vBuffer){
        av_freep(&vBuffer);
        vBuffer = nullptr;
    }

}

void FFVResampler::init(FFVideoPars *srcPars_, FFVideoPars *dstPars_)
{
    // 深拷贝参数
    srcPars = new FFVideoPars();
    memcpy(srcPars,srcPars_,sizeof(FFVideoPars));

    dstPars = new FFVideoPars();
    memcpy(dstPars,dstPars_,sizeof(FFVideoPars));

    // 初始化SwsContext
    initSws();
}

void FFVResampler::resample(AVFrame *srcFrame, AVFrame **dstFrame)
{
    // 分配目标帧（allocFrame），内部会复用 vBuffer 来存储图像数据。
    *dstFrame = allocFrame(dstPars,srcFrame);
    if(dstFrame == nullptr){
        return;
    }

    // 执行图像转换
    sws_scale(swsCtx,
              srcFrame->data,        // 输入数据指针数组
              srcFrame->linesize,    // 输入行步长
              0,                     // 起始行
              srcFrame->height,      // 输入高度
              (*dstFrame)->data,     // 输出数据指针数组
              (*dstFrame)->linesize); // 输出行步长
}

AVFrame* FFVResampler::allocFrame(FFVideoPars* vPars,AVFrame* srcFrame)
{
    AVFrame* frame = av_frame_alloc();

    // 计算存储一帧图像所需的最小缓冲区大小（考虑对齐）
    int bufSize = av_image_get_buffer_size(vPars->pixFmtEnum,vPars->width,vPars->height,1);
    // 当前缓冲区不够大，重新分配
    if(bufSize > maxbufSize){
        maxbufSize = bufSize;
        if(vBuffer){
            av_freep(&vBuffer);
        }
        vBuffer = static_cast<uint8_t*>(av_mallocz(bufSize));
        if(!bufSize){
            av_frame_free(&frame);
            std::cerr << "malloc vBuffer error!" << std::endl;
            return nullptr;
        }
    }

    // 使用 av_image_fill_arrays 将 vBuffer 与 frame->data/linesize 关联起来
    // 这样 frame 的数据实际指向 vBuffer，不再单独分配缓冲区。
    int ret = av_image_fill_arrays(frame->data,frame->linesize,vBuffer,
                                   vPars->pixFmtEnum,vPars->width,vPars->height,1);

    if(ret < 0){
        printError(ret);
        av_frame_free(&frame);
        return nullptr;
    }

    frame->width = vPars->width;
    frame->height = vPars->height;
    frame->format = vPars->pixFmtEnum;
    frame->pts = srcFrame->pts; // 保留源帧的时间戳

    return frame;
}

void FFVResampler::initSws()
{
    swsCtx = sws_getContext(srcPars->width, srcPars->height, srcPars->pixFmtEnum,
                            dstPars->width, dstPars->height, dstPars->pixFmtEnum,
                            SWS_BILINEAR,   // 缩放算法（质量与性能平衡）
                            nullptr,        // 源滤波器
                            nullptr,        // 目标滤波器
                            nullptr);       // 参数表
    if(!swsCtx){
        std::cerr << "sws_getContext error!" << std::endl;
        return;
    }

}

void FFVResampler::printError(int ret)
{
    char errorBuffer[AV_ERROR_MAX_STRING_SIZE];
    int res = av_strerror(ret,errorBuffer,sizeof errorBuffer);
    if(res < 0){
        std::cerr << "Unknow Error!" << std::endl;
    }
    else{
        std::cerr << "Error:" << errorBuffer << std::endl;
    }
}
