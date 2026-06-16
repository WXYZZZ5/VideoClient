# VideoClient

基于 FFmpeg + Qt5 + OpenGL 的跨平台视频播放器，支持本地文件播放、多线程解码、音视频同步、变速播放及播放列表管理。

## 项目结构

| 目录 | 职责 |
|------|------|
| `ui/` | Qt UI 界面（主窗口、工具栏、配置面板）|
| `player/` | 播放器上下文（`FFPlayerContext`，聚合所有组件指针）|
| `event/` | 事件系统（命令模式：开始、暂停、Seek、音量、变速、结束等事件）|
| `thread/` | 线程封装及线程池 |
| `queue/` | 线程安全队列（音频/视频包队列、音频/视频帧队列、事件队列）|
| `demuxer/` | 解封装模块（`FFDemuxer`）|
| `decoder/` | 解码器（音频 `FFADecoder`、视频 `FFVDecoder`）|
| `render/` | 渲染器（音频 `FFARender`、视频 `FFVRender` + 同步定时器 `FFTimer`）|
| `opengl/` | 基于 OpenGL 的 YUV 渲染组件（`FFGLRenderWidget`）|
| `clock/` | 全局音频时钟（用于音视频同步）|
| `resampler/` | 音频重采样与视频像素格式转换 |
| `sonic/` | Sonic 变速库（保持音调的变速播放）|
| `timer/` | 音视频同步定时器（以音频时钟为主时钟）|
| `tools/` | 工具类（`clientstylesheet.h` 集中管理全局样式表）|
| `shaderSource/` | OpenGL 着色器源码（YUV → RGB 转换）|
| `picture/` | 界面图标资源 |
| `lib/` | 预编译第三方库（FFmpeg、OpenCV）|
| `include/` | 第三方库头文件（FFmpeg、OpenCV）|
| `bin/` | 运行时依赖（DLL 文件）|
| `main/` | 程序入口（`main.cpp`）|

## 功能特性

| 功能 | 说明 |
|------|------|
| 本地文件播放 | 支持多种音视频格式（通过 FFmpeg 解码）|
| 播放列表管理 | 添加/删除视频文件，保存/加载播放列表（`QSettings`）|
| 上一集/下一集 | 在列表内快速切换视频 |
| 暂停/恢复 | 点击画面或暂停按钮 |
| 进度拖拽 | 拖动进度条实现精确 Seek |
| 音量调节 | 滑块控制音量（0%–100%）|
| 变速播放 | 支持 0.5×、1.0×、1.25×、1.5×、2.0× 倍速，保持原音调 |
| 全屏模式 | 双击画面进入/退出全屏，鼠标悬停显示控制栏 |
| 音视频同步 | 以音频时钟为主时钟，动态调整视频帧渲染间隔 |
| OpenGL 渲染 | 通过 QOpenGLWidget 着色器将 YUV420P 实时转换为 RGB 输出 |

## 系统要求

- Windows 7+ / Linux
- Qt 5.15（核心、GUI、Widgets、Multimedia、Network 模块）
- C++14 编译器（MinGW 64-bit / GCC / MSVC）
- FFmpeg 4.x 开发库（libavcodec、libavformat、libavutil、libswresample、libswscale 等）
- OpenGL（运行时，系统自带）
- Sonic（源码已包含在项目内，无需额外安装）

## 依赖安装

### Windows（MinGW 64-bit）

**1. 安装 Qt 5.15**

从 [Qt 官方安装器](https://www.qt.io/download) 安装 Qt 5.15.2，选择组件：
- Qt 5.15.2 → MinGW 64-bit
- Qt 5.15.2 → Qt Multimedia

**2. 安装 FFmpeg 开发库**

从 [gyan.dev](https://www.gyan.dev/ffmpeg/builds/) 下载 FFmpeg **Dev** 版本，解压后将 `include/` 和 `lib/` 目录分别拷贝到项目 `include/` 和 `lib/` 目录下。

### Linux（Ubuntu / Debian）

```bash
# Qt 5
sudo apt install qtbase5-dev qtmultimedia5-dev

# FFmpeg
sudo apt install libavcodec-dev libavformat-dev libavutil-dev \
                 libswresample-dev libswscale-dev libavdevice-dev \
                 libavfilter-dev libpostproc-dev

# OpenGL
sudo apt install libglu1-mesa-dev

# OpenCV（可选）
sudo apt install libopencv-dev
```

## 编译步骤

### 方式一：Qt Creator（推荐）

```bash
1. 打开 Qt Creator
2. 文件 → 打开文件或项目 → 选择 VideoClient.pro
3. 选择构建套件（Kit）：Desktop Qt 5.15.2 MinGW 64-bit
4. 点击"构建"（或 Ctrl+B）
5. 运行（Ctrl+R）
```

### 方式二：命令行

```bash
# 进入项目目录
cd D:\0_work\code\project-video3.0\VideoClient

# 生成 Makefile
E:\Qt\5.15.2\mingw81_64\bin\qmake.exe VideoClient.pro -spec win32-g++ "CONFIG+=debug"

# 编译
E:\Qt\Tools\mingw810_64\bin\mingw32-make.exe -j4

# 运行前需将运行时 DLL 放入 bin/ 目录或 PATH：
# bin/ 需包含 FFmpeg 的 DLL（avcodec-*.dll、avformat-*.dll 等）
# 以及 Qt 运行时（Qt5Core.dll、Qt5Widgets.dll、Qt5Multimedia.dll 等）

# 运行
bin\VideoClient.exe
```

## 架构概述

```
┌─────────────────────────────────────────────────────────┐
│                    FFPlayerWindow (UI)                   │
│  ┌─────────────┐  ┌──────────────┐  ┌───────────────┐  │
│  │ FFGLRender   │  │ processFrame │  │   toolFrame    │  │
│  │ Widget (Open │  │ (进度条)     │  │ (控制栏)      │  │
│  │ GL 渲染)     │  │              │  │               │  │
│  └──────┬───────┘  └──────────────┘  └───────┬───────┘  │
└─────────┼────────────────────────────────────┼──────────┘
          │                                    │
          │     ┌──────────────────────┐       │
          │     │    FFEventLoop        │       │
          │     │  (事件循环·消费者线程) │       │
          │     └──────────┬───────────┘       │
          │                │                   │
          │     ┌──────────▼───────────┐       │
          │     │   FFThreadPool        │       │
          │     │   (线程池·执行事件)    │       │
          │     └──────────────────────┘       │
          │                                    │
┌─────────▼────────────────────────────────────▼──────────┐
│                   FFPlayerContext                        │
│  ┌──────────┐  ┌──────────┐  ┌──────────┐  ┌─────────┐ │
│  │ FFDemuxer│  │ FFADec   │  │ FFVDec   │  │FFARender│ │
│  │ Thread   │  │ oderThr  │  │ oderThr  │  │(音频)   │ │
│  │ (解封装)  │  │ (音频解码)│  │ (视频解码)│  │         │ │
│  └────┬─────┘  └────┬─────┘  └────┬─────┘  └────┬────┘ │
│       │             │             │             │      │
│  ┌────▼─────┐  ┌────▼─────┐  ┌────▼─────┐  ┌────▼────┐ │
│  │FFVPktQueue│  │FFAPktQueue│  │FFVfrmQueue│  │FFAfrm   │ │
│  │(视频包队列)│  │(音频包队列)│  │(视频帧队列)│  │Queue    │ │
│  └──────────┘  └──────────┘  └──────────┘  └─────────┘ │
│             ┌──────────┐  ┌──────────┐                  │
│             │ FFTimer   │  │ Sonic    │                  │
│             │(音视频同步)│  │(变速库)  │                  │
│             └──────────┘  └──────────┘                  │
└──────────────────────────────────────────────────────────┘
```

### 数据流

```
文件 → [Demuxer] → 音视频包 → [Decoder] → 解码帧 → [Renderer] → 输出
                              ↓              ↓
                      FFVPktQueue      FFVfrmQueue → FFTimer → GL渲染
                      FFAPktQueue      FFAfrmQueue → FFARender → 声卡
```

### 事件驱动控制

采用**命令模式**（Command Pattern），所有播放控制操作（开始、暂停、Seek、音量、变速）都封装为事件对象，通过队列 + 线程池异步执行，避免阻塞 UI 线程：

```
UI 点击 → emit 信号 → FFPlayerWindow 创建事件 → enqueue
                                                   ↓
                               FFEventLoop 取出事件 → ThreadPool 执行 work()
```

### 音视频同步策略

- 以**音频时钟**为基准（`globalClock` 单例）
- 视频定时器（`FFTimer`）从视频帧队列取帧，计算 PTS 与音频时钟差值
- 差值过大时动态调整渲染间隔或主动丢帧
- Seek 时发送 FLUSH 包清空解码器缓存与队列

## 常见问题

| 问题 | 排查方向 |
|------|----------|
| 编译报错找不到 FFmpeg 头文件 | 检查 `include/` 目录下的 FFmpeg 头文件是否完整 |
| 运行时报缺少 DLL | 运行的时候，需要将bin目录下的所有dll拷贝到build路径下的debug或release |

## 许可证

Sonic 库基于 Apache 2.0 许可证，见 `sonic/sonic.h`。
项目其他部分仅供学习参考。
