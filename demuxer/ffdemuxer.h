#ifndef FFDEMUXER_H
#define FFDEMUXER_H

#include<string>
#include<iostream>
#include<atomic>
extern "C" {
#include <libavformat/avformat.h>
#include<libavutil/cpu.h>
}

class FFVPacketQueue;
class FFAPacketQueue;

/**
 * @brief 解封装（Demuxer）类
 *
 * 负责打开媒体文件或网络流，读取音视频包（AVPacket），
 * 将音频包和视频包分别放入对应的队列中供后续解码和播放。
 * 支持 seek（跳转）操作，并在文件结束时通知队列。
 */
class FFDemuxer {
public:
    explicit FFDemuxer();
    FFDemuxer(const FFDemuxer&) = delete;
    FFDemuxer& operator=(const FFDemuxer&) = delete;
    ~FFDemuxer();

    /**
     * @brief 初始化解封装器
     * @param url 媒体文件路径或网络流地址
     * @param aPktQueue_ 音频包队列指针
     * @param vPktQueue_ 视频包队列指针
     */
    void init(std::string const& url,FFAPacketQueue* aPktQueue_,FFVPacketQueue* vPktQueue_);

    /**
     * @brief 解封装一帧数据（一个 AVPacket）
     * @return 0 表示成功，1 表示遇到文件尾，-1 表示发生错误
     */
    int demux();

    /**
     * @brief 设置跳转到指定时间点（秒）
     * @param seekSec 目标时间（秒）
     */
    void seek(int64_t seekSec);

    //获取音频流（AVStream）对象
    AVStream* getAStream();
    //获取视频流（AVStream）对象
    AVStream* getVStream();
    //唤醒可能阻塞在队列上的解码线程（当解封装线程需要退出时）
    void wakeAllThread();
    //关闭解封装器，释放资源
    void close();

private:
    void printError(int ret);

    // 实际执行打开文件、查找流信息、选择音视频流的内部初始化函数
    void initDemuxer();
private:
    std::string url;                    // 媒体资源地址

    AVFormatContext* fmtCtx = nullptr;  // FFmpeg 格式上下文，核心结构体
    AVDictionary* opts = nullptr;       // 解封装选项（如线程数）
    AVStream* aStream = nullptr;        // 音频流
    AVStream* vStream = nullptr;        // 视频流

    FFAPacketQueue* aPktQueue = nullptr; // 音频包队列
    FFVPacketQueue* vPktQueue = nullptr; // 视频包队列

    AVRational aTimeBase;                // 音频流时间基
    AVRational vTimeBase;                // 视频流时间基

    int64_t seekPts;                     // seek 目标时间戳（基于 AV_TIME_BASE 单位）
    std::atomic<bool> seekFlag;          // 是否需要进行 seek 操作
    std::atomic<bool> demuxerEOF;        // 文件是否已读完

};

#endif // FF_DEMUXER_H
