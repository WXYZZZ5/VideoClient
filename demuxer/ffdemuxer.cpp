#include "ffdemuxer.h"
#include "queue/ffapacketqueue.h"
#include "queue/ffvpacketqueue.h"
#include <iostream>

// seek 时的偏移量：前后各 100000 微秒（即 0.1 秒）的余量
#define SEEK_OFFSET 100000
#define SEEK_OFFSET 100000

FFDemuxer::FFDemuxer()
    :seekPts(0),seekFlag(false),demuxerEOF(false)
{}

FFDemuxer::~FFDemuxer() {
    close();
}


void FFDemuxer::init(const std::string &url_, FFAPacketQueue *aPktQueue_, FFVPacketQueue *vPktQueue_)
{
    url = url_;
    aPktQueue = aPktQueue_;
    vPktQueue = vPktQueue_;

    initDemuxer();
}



int FFDemuxer::demux()
{
    //分配一个AVPacket并初始化
    AVPacket* packet = av_packet_alloc();
    av_init_packet(packet);

    //从格式上下文中读取一个包
    int ret = av_read_frame(fmtCtx,packet);

    if(ret < 0){
        //已读到文件末尾
        if(ret == AVERROR_EOF){
            /* 此时解封装线程即将退出，但还有解码线程在等待数据。为了让解码线程也知道“没有更多输入了”，
             * 需要向音频队列和视频队列各放入一个 空包（nullptr）。
             * 解码线程从队列中取到空包后，就知道流已经结束，可以退出解码循环或做收尾工作（比如刷新剩余帧、渲染最后一帧等）。
             */
            aPktQueue->enqueueNull();
            vPktQueue->enqueueNull();
            std::cout<<"AVERROR_EOF"<<std::endl;

            //记录下“已经EOF（end of file）”状态
            /* 这个标志在 seek 函数中被检查：
             * 如果用户在 EOF 后还想跳转回去，就需要先重新初始化解封装器（相当于重新弄打开文件）
             *（因为原来的 fmtCtx 已经处于结束状态，无法再 seek）。
             */
            demuxerEOF.store(true,std::memory_order_release);
            return 1;
        }
        else{
            printError(ret);
            avformat_close_input(&fmtCtx);
            av_packet_free(&packet);
            return -1;
        }
    }

    //进行跳转操作
    if(seekFlag.load(std::memory_order_acquire)){
        /* 丢弃上面解出来的包
         * 原因：用户要跳转到新位置，这个包就作废了。
         * 如果不释放，后续这个包被放入队列，会导致新旧数据混在一起，造成画面声音错乱的情况
         */
        av_packet_unref(packet); //释放内部缓冲区
        av_packet_free(&packet); //释放包本身

        /*avformat_seek_file 函数允许你指定一个 允许的区间 [minPts, maxPts]，
         * 它会在这个区间内寻找一个合适的 关键帧（key frame） 作为跳转点。
         * 最终跳转的位置不一定正好是 seekPts，但会是最接近的、可以独立解码的帧。
         */
        int64_t minPts = seekPts - SEEK_OFFSET * AV_TIME_BASE;
        int64_t maxPts = seekPts + SEEK_OFFSET * AV_TIME_BASE;
        minPts = FFMIN(FFMAX(minPts, 0), fmtCtx->duration);
        maxPts = FFMIN(maxPts, fmtCtx->duration);
        // stream_index：这里传 -1，表示在所有流中寻找合适的关键帧（通常音视频需要同步跳转）。
        avformat_seek_file(fmtCtx,-1,minPts,seekPts,maxPts,0);

        /* 解码器内部可能缓存了之前解码出的几帧数据（比如 B 帧参考、音频解码缓冲区）。
         * 如果不通知解码器“清空缓存”，那么 seek 后解码出来的第一帧可能会和旧数据混合，出现“花屏”或“音画不同步”。
         */
        vPktQueue->enqueueFlush();
        aPktQueue->enqueueFlush();

        //表示本次 seek 请求已经处理完成，后续 demux 调用将不再进入这个分支
        seekFlag.store(false,std::memory_order_release);
        return 0;
    }

    // 正常情况：根据 packet 的流索引分发到对应的队列
    if(packet->stream_index == aStream->index){
        aPktQueue->enqueue(packet);
    }
    else if(packet->stream_index == vStream->index){
        vPktQueue->enqueue(packet);
    }

    av_packet_free(&packet);

    return 0;
}

void FFDemuxer::seek(int64_t seekSec) {
    //如果已经处于EOF状态，则重新打开文件
    if(demuxerEOF.load(std::memory_order_acquire)){
        close(); //关闭当前上下文
        init(url,aPktQueue,vPktQueue); //重新初始化
        demuxerEOF.store(false,std::memory_order_release); //重置EOF状态
    }

    seekPts = seekSec * AV_TIME_BASE; //将事件转换为AV_TIME_BASE单位的时间戳
    seekFlag.store(true); //设置请求标志，demux 线程会检查并执行 seek
}

AVStream *FFDemuxer::getAStream()
{
    return aStream;
}

AVStream *FFDemuxer::getVStream()
{
    return vStream;
}

void FFDemuxer::wakeAllThread()
{
    vPktQueue->wakeAllThread();
    aPktQueue->wakeAllThread();
}

void FFDemuxer::close()
{
    if (fmtCtx) {
        avformat_close_input(&fmtCtx);
    }
}

void FFDemuxer::printError(int ret)
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

void FFDemuxer::initDemuxer()
{
    avformat_network_init(); // 初始化网络组件（支持网络流）

     // 设置解封装线程数：CPU 核数的一半（至少 1）
    int cores = av_cpu_count() >> 1; // >>1 表示右移一位，即除以 2
    /* av_dict_set 是把键值对 "threads" -> "4"（举例）设置到 AVDictionary* opts 中，
     * 告诉 FFmpeg 底层可以启用多少个线程来辅助解封装,随后 avformat_open_input 会消费这些选项。
     */
    av_dict_set(&opts,"threads",std::to_string(cores).c_str(),0); //多线程解复用

    //打开媒体文件
    int ret = avformat_open_input(&fmtCtx,url.c_str(),nullptr,&opts);
    if(ret < 0){
        avformat_close_input(&fmtCtx);
        printError(ret);
        return;
    }

    // 读取一部分数据并分析，获取流信息
    /*调用 avformat_open_input 后，AVFormatContext 里的 streams 数组已经被创建，但很多字段还是空的
     *
     * avformat_find_stream_info 的任务就是读取一小段文件内容，实际解码少量帧，从而填充每个流的真实参数。
     * 如果不调用这个函数，直接去读取 AVPacket，那么 AVStream 的很多字段（codecpar 中的参数）可能仍然是未填充的或不完整的，导致后续解码失败。
     */
    ret = avformat_find_stream_info(fmtCtx,nullptr);
    if(ret < 0){
        avformat_close_input(&fmtCtx);
        printError(ret);
        return;
    }

    // 遍历所有流，找出音频流和视频流
    for(size_t i = 0;i< fmtCtx->nb_streams; ++i){
        AVStream* stream = fmtCtx->streams[i];
        AVCodecParameters*codecPar = stream->codecpar;

        if(codecPar->codec_type == AVMEDIA_TYPE_AUDIO){
            aStream = stream;
            aTimeBase = stream->time_base;
        }
        else if(codecPar->codec_type == AVMEDIA_TYPE_VIDEO){
            vStream = stream;
            vTimeBase = stream->time_base;
        }
    }
}


