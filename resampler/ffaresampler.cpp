#include"ffaresampler.h"
#include"decoder/ffadecoder.h"


FFAResampler::FFAResampler()
{

}

FFAResampler::~FFAResampler()
{
    if(swrCtx){
        swr_free(&swrCtx);
    }
    if(srcPars){
        delete srcPars;
        srcPars = nullptr;
    }
    if(dstPars){
        delete dstPars;
        dstPars = nullptr;
    }

}

void FFAResampler::init(FFAudioPars *src_, FFAudioPars *dst_)
{
    // 深拷贝参数结构体，避免外部修改影响内部状态
    srcPars = new FFAudioPars();
    memcpy(srcPars,src_,sizeof(FFAudioPars));

    dstPars = new FFAudioPars();
    memcpy(dstPars,dst_,sizeof(FFAudioPars));

    // 创建并初始化 SwrContext
    initSwr();
}

void FFAResampler::resample(AVFrame *srcFrame, AVFrame **dstFrame)
{
    // 计算输出所需的最大样本数（基于当前输入样本数和重采样参数）
    int maxNbSamples = swr_get_out_samples(swrCtx, srcFrame->nb_samples);

    // 分配目标帧（内部会根据 maxNbSamples 分配缓冲区）
    *dstFrame = allocFrame(dstPars,maxNbSamples,srcFrame);
    if (!*dstFrame) {
        std::cerr << "allocFrame failed!" << std::endl;
        return;
    }

    // 执行重采样：将 srcFrame 的数据转换到 (*dstFrame)->data 中
    int samples = swr_convert(
        swrCtx,
        (*dstFrame)->data,          // 输出数据指针数组
        maxNbSamples,               // 输出缓冲区大小（样本数）
        (const uint8_t**)srcFrame->data, // 输入数据
        srcFrame->nb_samples        // 输入样本数
    );

    if (samples < 0) {
        printError(samples);
        swr_free(&swrCtx);
        return;
    }

    // if (!*dstFrame) {
    //     std::cerr << "av_frame_alloc error!" << std::endl;
    //     return;
    // }

}

void FFAResampler::initSwr()
{
    // 创建并设置重采样上下文参数（swr_alloc_set_opts 会分配上下文并设置选项）
    swrCtx = swr_alloc_set_opts(swrCtx,
                                // 输出参数
                                av_get_default_channel_layout(dstPars->nbChannels),
                                dstPars->aFormatEnum,
                                dstPars->sampleRate,
                                // 输入参数
                                av_get_default_channel_layout(srcPars->nbChannels),
                                srcPars->aFormatEnum,
                                srcPars->sampleRate,
                                0,   // 日志级别，0 表示默认
                                nullptr); // 额外选项

    if(!swrCtx){
        std::cerr << "initSwr error!" << std::endl;
        return;
    }

    // 初始化重采样器（分配内部缓冲区）
    int ret = swr_init(swrCtx);
    if(ret < 0 ){
        printError(ret);
        swr_free(&swrCtx);
        return;
    }

}

AVFrame* FFAResampler::allocFrame(FFAudioPars* aPars,int nbSamples,AVFrame* srcFrame)
{
    AVFrame* frame = av_frame_alloc();
    frame->format = aPars->aFormatEnum;
    frame->channels = aPars->nbChannels;
    frame->sample_rate = aPars->sampleRate;
    frame->channel_layout = av_get_default_channel_layout(aPars->nbChannels);
    frame->nb_samples = nbSamples;

    frame->pts = srcFrame->pts;

    // 分配数据缓冲区
    int ret = av_frame_get_buffer(frame,0);
    if(ret < 0){
        printError(ret);
        av_frame_unref(frame);
        return nullptr;
    }


    return frame;
}

void FFAResampler::printError(int ret){
    char errorBuffer[AV_ERROR_MAX_STRING_SIZE];
    int res = av_strerror(ret,errorBuffer,sizeof errorBuffer);
    if(res < 0){
        std::cerr << "Unknow Error!" << std::endl;
    }
    else{
        std::cerr << "Error:" << errorBuffer << std::endl;
    }
}


