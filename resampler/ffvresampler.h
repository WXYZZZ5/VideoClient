#ifndef FFVRESAMPLER_H
#define FFVRESAMPLER_H

extern "C"{
#include"libavformat/avformat.h"
#include"libswscale/swscale.h"
#include"libavutil/imgutils.h"
}

class FFVideoPars;

/**
 * @brief 视频图像转换器类
 *
 * 职责：
 * 1. 根据源视频参数（宽、高、像素格式）和目标参数（如 YUV420P），
 *    初始化 SwsContext（FFmpeg 图像转换上下文）。
 * 2. 提供 resample() 函数，将输入 AVFrame 中的图像数据转换为目标格式，
 *    并输出一个新的 AVFrame。
 * 3. 管理转换过程中所需的中间缓冲区（vBuffer），避免频繁分配大块内存。
 *
 * 注意：虽然类名中有 "Resampler"，但实际是图像缩放/格式转换，非音频重采样。
 */
class FFVResampler
{
public:
    FFVResampler();
    ~FFVResampler();

    void init(FFVideoPars* srcPars_, FFVideoPars* dstPars_);

    /**
    * @brief 执行图像转换
    * @param srcFrame 原始视频帧（解码器输出）
    * @param dstFrame 输出参数，指向新分配的转换后的帧（调用者负责释放）
    */
    void resample(AVFrame* srcFrame,AVFrame** dstFrame);
private:
    AVFrame* allocFrame(FFVideoPars* vPars,AVFrame* srcFrame);
    void initSws();
    void printError(int ret);

private:
    SwsContext* swsCtx = nullptr;   // FFmpeg 图像转换上下文
    FFVideoPars* srcPars = nullptr; // 源参数
    FFVideoPars* dstPars = nullptr; // 目标参数
    uint8_t* vBuffer = nullptr;     // 复用缓冲区（避免每次分配内存）
    int maxbufSize = -1;            // 当前 vBuffer 的大小（字节）

};

#endif // FFVRESAMPLER_H
