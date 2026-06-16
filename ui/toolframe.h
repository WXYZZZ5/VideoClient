#ifndef TOOLFRAME_H
#define TOOLFRAME_H

#include <QFrame>
#include<QDebug>
#include<QEvent>

#include"clientstylesheet.h"

namespace Ui {
class toolFrame;
}

class toolFrame : public QFrame
{
    Q_OBJECT

signals:
    void _volumeHorizontalSlider_valueChanged(int value);
    void _pauseBtn_clicked(bool pauseStatus);
    void _nextBtn_clicked();
    void _prevBtn_clicked();
    void _configBtn_clicked();
    void scaleButtonClicked(int index);
    void speedButtonClicked(int index);
    void fullScreenCheckBox_toggled(bool checked);
    void screenShotCheckBox_toggled(bool checked);
public:
    explicit toolFrame(QWidget *parent = nullptr);
    ~toolFrame()override;

    void initVolumeSlider();
    void setVolumSliderEnable(bool status);
    void setVolumeSliderValue(int value);
    void setPauseBtnStatus(bool status);
    void setPauseBtnStyle();
    int getVolumeSliderValue();
    QString getPauseBtnText();
    void hideConfigurationBtn();
    void setScaleIndex(int index);
    void setSpeedIndex(int index);

    void setFullScreenChecked(bool enable);
    void setScreenShotChecked(bool enable);

    void setFullScreenEnable(bool checked);
    void setScreenShotEnable(bool checked);

    void setScreenShotText(QString str);
    bool fullScreenChecked();

private slots:
    void on_pauseBtn_clicked();
    void on_volumeHorizontalSlider_valueChanged(int value);
    void on_nextBtn_clicked();
    void on_prevBtn_clicked();

    void on_speedButton_clicked();

    void on_fullScreenCheckBox_toggled(bool checked);

    void on_screenShotCheckBox_toggled(bool checked);

private:
    Ui::toolFrame *ui;
    int scaleIndex = 0;
    int speedIndex = 0;
    QString speedStr[5] = {"1.0","1.25","1.5","2.0","0.5"};
private:
    void setQSS();
    bool pauseStatus;

};

#endif // TOOLFRAME_H
