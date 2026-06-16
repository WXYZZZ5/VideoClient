#ifndef FFGLRENDERWIDGET_H
#define FFGLRENDERWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QVector>
#include <QOpenGLTexture>
#include <QOpenGLFunctions_4_5_Core>

/**
 * @brief 基于 OpenGL 的 YUV 视频渲染控件
 *
 * 职责：
 * - 接收 YUV420P 数据（三个独立分量），上传到纹理。
 * - 使用着色器将 YUV 转换为 RGB 并绘制到窗口。
 * - 自动保持视频宽高比，添加黑边。
 * - 发出鼠标双击/单击信号供外部控制播放状态。
 *
 * 注意：该控件必须在主线程（Qt GUI 线程）中操作，通过信号槽接收数据。
 */
class FFGLRenderWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_5_Core
{
    Q_OBJECT

signals:
    void mouseDoubleClick();   // 用户双击信号（可用于切换全屏等）
    void mouseClick();         // 用户单击信号（可用于播放/暂停）

public:
    explicit FFGLRenderWidget(QWidget *parent = nullptr);
    ~FFGLRenderWidget() override;

    void setAspect(float aspect_);           // 设置视频宽高比（宽/高）
    void setBlackScreen();                   // 强制显示黑屏（用于停止时清空画面）

public slots:
    // 接收一帧 YUV 数据并渲染
    void setYUVData(uint8_t *yData, uint8_t *uData, uint8_t *vData, int width, int height);

protected:
    void initializeGL() override;         // 初始化 OpenGL 资源（VAO、VBO、EBO、纹理、着色器）
    void paintGL() override;              // 每帧绘制：绑定纹理，绘制四边形
    void resizeGL(int w, int h) override; // 窗口大小改变时重新计算视口（保持宽高比）
    void mouseDoubleClickEvent(QMouseEvent* event) override; // 双击事件
    void mousePressEvent(QMouseEvent* event) override;       // 单击事件

private:
    static const QVector<float> vertices;        // 顶点数据：位置 + 纹理坐标
    static const QVector<unsigned int> indices;  // 索引数据（用于 TRIANGLE_FAN）

    GLuint vao = 0, vboVertice = 0, ebo = 0;     // OpenGL 缓冲区对象
    GLuint yTexture;                             // Y 分量纹理（单通道，GL_RED）
    GLuint uTexture;                             // U 分量纹理
    GLuint vTexture;                             // V 分量纹理
    QOpenGLShaderProgram shaderProgram;          // 着色器程序（YUV->RGB）

    // 视口参数（用于保持宽高比）
    float aspect = 16.0f / 9;     // 当前视频宽高比（默认 16:9）
    int viewportX = 0;
    int viewportY = 0;
    int viewportWidth = 0;
    int viewportHeight = 0;
};

#endif // FFGLRENDERWIDGET_H
