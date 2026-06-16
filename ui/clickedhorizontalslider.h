#ifndef CLICKEDHORIZONTALSLIDER_H
#define CLICKEDHORIZONTALSLIDER_H

#include<QSlider>
#include<QMouseEvent>
#include<QDebug>
#include<QObject>

class clickedHorizontalSlider : public QSlider
{
    Q_OBJECT

signals:
    void videoSliderChange(int64_t value);

public:
    clickedHorizontalSlider(QWidget* parent = nullptr);
    void setSliderRange(int min,int max);
    bool isSliderSelected();
    void setSliderSelected(bool status);

protected:
   void mousePressEvent(QMouseEvent*event)override;
   void mouseReleaseEvent(QMouseEvent*event) override;


private:
    QPoint pressPos;
    bool sliderSelected;
};

#endif // CLICKEDHORIZONTALSLIDER_H
