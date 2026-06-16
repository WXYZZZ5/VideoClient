#ifndef FFPACKET_H
#define FFPACKET_H

#endif // FFPACKET_H

extern "C"{
#include"libavformat/avformat.h"
}

// NORMAL: 普通音视频数据包
// FLUSH:  清空解码器缓存的特殊包（seek 时使用）
// NULLP:  表示流结束的空包（EOF 时使用）
enum type{ NORMAL, FLUSH, NULLP };

struct FFPacket
{
    AVPacket packet;   // FFmpeg 数据包（包含压缩的音视频数据）
    size_t serial;     // 序列号，每次 FLUSH 后递增，用于丢弃旧周期的包
    uint8_t type;      // 包类型：NORMAL / FLUSH / NULLP
};
