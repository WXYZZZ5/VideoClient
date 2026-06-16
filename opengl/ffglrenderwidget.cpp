#include "ffglrenderwidget.h"
#include<QMouseEvent>

// 顶点数据（位置(x,y) + 纹理坐标(u,v)）
// 每个顶点有 4 个 float：前两个是位置（范围 -1 到 1，-1 是屏幕底部/左边，1 是顶部/右边），后两个是纹理坐标（0-1）。
const QVector<float> FFGLRenderWidget::vertices = {
    -1.0f,  1.0f,  0.0f, 0.0f,  // 顶点0：左上
    -1.0f, -1.0f,  0.0f, 1.0f,  // 顶点1：左下
    1.0f, -1.0f,  1.0f, 1.0f,  // 顶点2：右下
    1.0f,  1.0f,  1.0f, 0.0f   // 顶点3：右上
};

// 索引数据：以 TRIANGLE_FAN 方式绘制四个顶点（0-1-2-3）
const QVector<unsigned int> FFGLRenderWidget::indices = {0, 1, 2, 3};

FFGLRenderWidget::FFGLRenderWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    // 设置最小尺寸，避免窗口过小
    setMinimumSize(400,300);
}

FFGLRenderWidget::~FFGLRenderWidget()
{
    // 析构前必须确保 OpenGL 上下文当前，否则释放资源会出错
    makeCurrent();
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vboVertice);
    glDeleteBuffers(1, &ebo);
    glDeleteTextures(1, &yTexture);
    glDeleteTextures(1, &uTexture);
    glDeleteTextures(1, &vTexture);
    doneCurrent();
}

void FFGLRenderWidget::setAspect(float aspect_)
{
    aspect = aspect_;
}

/*上传一个 1x1 的黑色 YUV 像素（Y=0, U=128, V=128），
 * 然后更新纹理并重绘，使画面变黑。
 */
void FFGLRenderWidget::setBlackScreen()
{
    makeCurrent();

    // 配置纹理参数并初始化为黑色YUV数据
    uint8_t yData = 0;    // Y分量全0
    uint8_t uData = 128;  // U分量全128
    uint8_t vData = 128;  // V分量全128

    // 初始化Y纹理
    glBindTexture(GL_TEXTURE_2D, yTexture); // 将纹理激活到当前纹理单元,后续的纹理操作都会作用于这个绑定的纹理
    /*GL_TEXTURE_2D：目标纹理类型
     * 0：mipmap 级别（0 为主纹理）
     * GL_RED：内部格式，表示 GPU 内部存储为单红色通道（实际存储亮度值）
     * 1, 1：纹理宽度和高度（1x1 像素）
     * 0：边框（必须为 0）
     * GL_RED：输入数据格式（也是单通道）
     * GL_UNSIGNED_BYTE：输入数据类型（每个分量 0~255）
     * &yData：指向一个字节的指针（存储值 0）
     */
    // 上传数据，将 CPU 内存中的 1 个字节的数据（Y 分量 0）上传到 GPU 纹理中。类似地，U 和 V 纹理分别上传 128 和 128
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 1, 1, 0, GL_RED, GL_UNSIGNED_BYTE, &yData);
    // 过滤方式：GL_LINEAR 表示双线性滤波。当纹理被放大（如 1x1 纹理铺满全屏）时，采样点会取纹理中相邻像素的加权平均值。
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // 包裹模式：GL_CLAMP_TO_EDGE 表示当纹理坐标超出 [0,1] 范围时，使用边缘像素的颜色,这避免了边界出现重复或黑色缝隙
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // 初始化U纹理
    glBindTexture(GL_TEXTURE_2D, uTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 1, 1, 0, GL_RED, GL_UNSIGNED_BYTE, &uData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // 初始化V纹理
    glBindTexture(GL_TEXTURE_2D, vTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 1, 1, 0, GL_RED, GL_UNSIGNED_BYTE, &vData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // 触发重绘
    update();

    doneCurrent();
}

void FFGLRenderWidget::initializeGL()
{
    initializeOpenGLFunctions();          // 加载 OpenGL 函数指针
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 清除颜色为黑色

    // 初始化缓冲对象 创建 VAO、VBO、EBO
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vboVertice);
    glGenBuffers(1, &ebo);

    // 绑定 VAO（开始记录状态）
    glBindVertexArray(vao);

    /**
     * glBindBuffer 用来将指定的缓冲区对象绑定到某个目标槽位，
     * 比如 GL_ARRAY_BUFFER 表示顶点属性缓冲，GL_ELEMENT_ARRAY_BUFFER 表示索引缓冲。
     *
     *glBufferData 则负责实际分配显存并上传数据。
     *它的参数包括：目标类型、数据字节数、源数据指针以及使用模式(提示 GPU 如何使用这些数据)。
     *这里用了 GL_STATIC_DRAW，因为顶点和索引数据在加载后不会改变，适合静态绘制
     */
    // 上传顶点数据到 VBO
    glBindBuffer(GL_ARRAY_BUFFER, vboVertice);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // 上传索引数据到 EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // 配置顶点属性指针（这一步是关键）

    /**
     * index：属性位置，0 对应 a_pos位置，1 对应 a_texCoord纹理坐标。
     * size：每个属性有几个分量，2 表示 x,y。
     * type：数据类型，GL_FLOAT。
     * normalized：是否归一化，GL_FALSE。
     * stride：相邻顶点之间的字节偏移，这里是 4 * sizeof(float) = 16，即每个顶点占 16 字节。
     * pointer：该属性在顶点数据中的起始偏移量。对于位置，偏移 0；对于纹理坐标，偏移 2 * sizeof(float) = 8（因为前两个 float 是位置）。
     */
    // 位置属性 (location = 0)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0); // 设置数据来源和格式
    glEnableVertexAttribArray(0);// 启用该属性
    // 纹理坐标属性 (location = 1)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 解绑 VAO（状态记录完毕）
    glBindVertexArray(0);

    // 初始化纹理
    glGenTextures(1, &yTexture);
    glGenTextures(1, &uTexture);
    glGenTextures(1, &vTexture);

    // 初始绑定为黑屏 避免显示乱码
    // 配置纹理参数并初始化为黑色YUV数据
    uint8_t yData = 0;    // Y分量全0
    uint8_t uData = 128;  // U分量全128
    uint8_t vData = 128;  // V分量全128

    // 初始化Y纹理
    glBindTexture(GL_TEXTURE_2D, yTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 1, 1, 0, GL_RED, GL_UNSIGNED_BYTE, &yData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // 初始化U纹理
    glBindTexture(GL_TEXTURE_2D, uTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 1, 1, 0, GL_RED, GL_UNSIGNED_BYTE, &uData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // 初始化V纹理
    glBindTexture(GL_TEXTURE_2D, vTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 1, 1, 0, GL_RED, GL_UNSIGNED_BYTE, &vData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // 加载并编译着色器（顶点着色器 + 片段着色器）
    if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaderSource/source.vert") ||
            !shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaderSource/source.frag") ||
            !shaderProgram.link())
    {
        qCritical() << "Shader error:" << shaderProgram.log();
    }
}
void FFGLRenderWidget::paintGL()
{
    // 每一帧绘制前，必须清除上一帧的内容，否则会出现“残影”或画面叠加
    glClear(GL_COLOR_BUFFER_BIT);  // 清除颜色缓冲
    shaderProgram.bind();          // 使用着色器程序

    // 定义 OpenGL 渲染的目标区域
    glViewport(viewportX, viewportY, viewportWidth, viewportHeight);


    glActiveTexture(GL_TEXTURE0);           // 选择当前激活的纹理单元
    glBindTexture(GL_TEXTURE_2D, yTexture); // 将某个纹理对象绑定到当前激活的纹理单元上
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, uTexture);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, vTexture);

    // 告诉着色器程序，uniform 变量 yTexture 对应纹理单元 0，uTexture 对应单元 1，vTexture 对应单元 2
    shaderProgram.setUniformValue("yTexture", 0);
    shaderProgram.setUniformValue("uTexture", 1);
    shaderProgram.setUniformValue("vTexture", 2);

    // 绘制四边形（使用 TRIANGLE_FAN 和索引）
    glBindVertexArray(vao); // 绑定预先设置好的顶点数组对象（VAO）
    // 执行图元绘制
    // 绘制一个“扇形”，第一个顶点作为公共顶点，后面每两个顶点与第一个组成三角形。
    // 对于四个顶点，会生成两个三角形（0-1-2 和 0-2-3），正好铺满一个矩形
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0); // 解绑 VAO，避免后续其他 OpenGL 操作错误地修改它

    // 解除当前着色器程序，恢复到无着色器状态 可以避免意外的状态污染
    shaderProgram.release();
}

void FFGLRenderWidget::resizeGL(int w, int h)
{
    // 比较 currentAspect 与 targetAspect，决定黑边出现在水平方向（左右）还是垂直方向（上下）
    const float targetAspect = aspect;  // 视频宽高比
    const float currentAspect = static_cast<float>(w) / h;

    // 窗口过宽，左右加黑边
    if (currentAspect > targetAspect) {
        /**
         * 为了保证画面比例正确，视口宽度 = 高度 × 视频宽高比。
         * 因为 targetAspect = 视频宽/视频高，所以 宽度 = 高度 × (宽/高)。
         * 这样计算出的宽度 ≤ 窗口宽度（因为
         * currentAspect > targetAspect 意味着 w/h > targetAspect → w > h * targetAspect），
         * 因此有多余的水平空间用于黑边。
         */
        viewportWidth = static_cast<int>(h * targetAspect);
        viewportHeight = h; // 视口的高度等于窗口的高度，即画面在垂直方向占满
        viewportX = (w - viewportWidth) / 2; // 水平居中,总空白宽度 = 窗口宽度 - 视口宽度，除以 2 得到左边距
        viewportY = 0; // 垂直方向无需偏移（视口已填满高度）
    }
    // 窗口过高，上下加黑边
    else {
        viewportWidth = w; // 视口宽度等于窗口宽度，水平占满
        viewportHeight = static_cast<int>(w / targetAspect);
        viewportX = 0;
        viewportY = (h - viewportHeight) / 2; // 垂直居中。总空白高度 = 窗口高度 - 视口高度，除以 2 得到上边距
    }
}

void FFGLRenderWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        emit mouseDoubleClick();
    }

    QOpenGLWidget::mouseDoubleClickEvent(event);
}

void FFGLRenderWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        emit mouseClick();
    }

    QOpenGLWidget::mousePressEvent(event);
}


void FFGLRenderWidget::setYUVData(uint8_t *yData, uint8_t *uData, uint8_t *vData, int width, int height) {
    makeCurrent();

    // 上传Y分量
    glBindTexture(GL_TEXTURE_2D, yTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, yData);


    // 上传UV分量（宽高各减半）
    // 在 YUV420 格式中，色度平面（U 和 V）的采样率是亮度平面的一半（水平方向和垂直方向各减半）。
    // 因此，U 和 V 平面的尺寸分别是 width/2 × height/2。这是 YUV420P 的标准定义。
    int uvWidth = width / 2;
    int uvHeight = height / 2;
    // 绑定目标纹理
    glBindTexture(GL_TEXTURE_2D, uTexture);
    // 分配纹理内存并上传数据
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, uvWidth, uvHeight, 0, GL_RED, GL_UNSIGNED_BYTE, uData);
    glBindTexture(GL_TEXTURE_2D, vTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, uvWidth, uvHeight, 0, GL_RED, GL_UNSIGNED_BYTE, vData);

    update(); // 触发重绘 paintGL()
    doneCurrent();
}
