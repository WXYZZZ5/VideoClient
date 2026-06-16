#include "picturegenerator.h"

pictureGenerator::pictureGenerator()
{

}

//裁剪图片为圆角
QPixmap pictureGenerator::roundedPixmap(const QPixmap &pixmap, int radius)
{
    QPixmap rounded(pixmap.size());
    rounded.fill(Qt::transparent);

    QPainter painter(&rounded);
    painter.setRenderHint(QPainter::Antialiasing);

    QPainterPath path;
    path.addRoundedRect(pixmap.rect(), radius, radius);
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, pixmap);

    return rounded;
}


