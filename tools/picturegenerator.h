#ifndef PICTUREGENERATOR_H
#define PICTUREGENERATOR_H

#include<QPixmap>
#include<QPainter>

class pictureGenerator
{
public:
    pictureGenerator();


    static QPixmap roundedPixmap(const QPixmap &pixmap, int radius);

};

#endif // PICTUREGENERATOR_H
