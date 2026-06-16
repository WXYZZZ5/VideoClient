#include "clickedhorizontalslider.h"

clickedHorizontalSlider::clickedHorizontalSlider(QWidget *parent)
    :QSlider(parent)
{
    setSingleStep(1);
    setPageStep(0);
    setValue(0); //初始大小
    setRange(0,100); //初始范围

    sliderSelected = false;
}

//设置范围
void clickedHorizontalSlider::setSliderRange(int min, int max)
{
    setRange(min,max);
}

//获取滑块选择状态
bool clickedHorizontalSlider::isSliderSelected()
{
    return this->sliderSelected;
}

//设置滑块状态
void clickedHorizontalSlider::setSliderSelected(bool status)
{
    this->sliderSelected = status;
}

//鼠标按下
void clickedHorizontalSlider::mousePressEvent(QMouseEvent *event)
{
    //左键按下
    if(event->button() == Qt::LeftButton){
        pressPos = event->pos(); //坐标
        sliderSelected = true;
    }

    QSlider::mousePressEvent(event);
}

//鼠标释放
void clickedHorizontalSlider::mouseReleaseEvent(QMouseEvent *event)
{
    //左键放开
    if(event->button() == Qt::LeftButton){
        int value = static_cast<int>(1.0 * event->pos().x() / width() * maximum());  //获得位置对应的值
        emit videoSliderChange(value);
    }

    QSlider::mouseReleaseEvent(event);

}












