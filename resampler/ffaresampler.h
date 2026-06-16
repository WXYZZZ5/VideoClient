#ifndef FFARESAMPLER_H
#define FFARESAMPLER_H

extern "C"{
#include"libavformat/avformat.h"
#include "libswresample/swresample.h"   // FFmpeg 音频重采样库（SwrContext）
#include "libavutil/channel_layout.h"   // 声道布局相关函数
}
#include<iostream>


struct FFAudioPars;

/**
 * @brief 音频重采样器类
 *
 * 职责：
 * 1. 根据源音频参数（sample rate, channel layout, sample format）和
 *    目标音频参数，初始化 SwrContext（FFmpeg 重采样上下文）。
 * 2. 提供 resample() 函数，将输入 AVFrame 中的音频数据转换为目标格式，
 *    并输出一个新的 AVFrame。
 * 3. 管理重采样过程中所需的内存分配和释放。
 */
class FFAResampler{
public:
    explicit FFAResampler();
    ~FFAResampler();

    void init(FFAudioPars*src ,FFAudioPars* dst);

    /**
    * @brief 执行音频重采样
    * @param srcFrame 原始音频帧（通常是解码器输出）
    * @param dstFrame 输出参数，指向新分配的转换后的帧
    */
    void resample(AVFrame* srcFrame,AVFrame** dstFrame);

private:
    void initSwr();
    AVFrame* allocFrame(FFAudioPars* aPars,int nbSamples,AVFrame* srcFrame);
    void printError(int ret);

private:
    SwrContext* swrCtx = nullptr;   // FFmpeg 重采样上下文
    FFAudioPars* srcPars = nullptr; // 源参数
    FFAudioPars* dstPars = nullptr; // 目标参数
};

#endif // FFARESAMPLER_H
