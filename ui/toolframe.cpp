#include "toolframe.h"
#include "ui_toolframe.h"

toolFrame::toolFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::toolFrame)
{
   ui->setupUi(this);
    connect(ui->nextBtn, &QPushButton::clicked, this, &toolFrame::on_nextBtn_clicked);
    connect(ui->prevBtn, &QPushButton::clicked, this, &toolFrame::on_prevBtn_clicked);
   setQSS();
    pauseStatus =false;
}



void toolFrame::setVolumeSliderValue(int value)
{
    ui->volumeHorizontalSlider->setValue(value);
}

void toolFrame::setPauseBtnStatus(bool status)
{

    this->pauseStatus = status;
    if(pauseStatus){
        ui->pauseBtn->setStyleSheet(toolFrameStyle::playButtonStytle);
    }
    else{
        ui->pauseBtn->setStyleSheet(toolFrameStyle::pauseButtonStytle);
    }
}

void toolFrame::setPauseBtnStyle()
{

    pauseStatus^=1;

    if(pauseStatus){
        ui->pauseBtn->setStyleSheet(toolFrameStyle::playButtonStytle);
    }
    else{
        ui->pauseBtn->setStyleSheet(toolFrameStyle::pauseButtonStytle);
    }
}



int toolFrame::getVolumeSliderValue()
{
    return ui->volumeHorizontalSlider->value();
}

QString toolFrame::getPauseBtnText()
{
    return ui->pauseBtn->text();
}

void toolFrame::hideConfigurationBtn()
{
    //    ui->configBtn->hide();
}

void toolFrame::setScaleIndex(int index)
{
    scaleIndex = index;
    //    ui->scaleButton->setText(scaleStr[scaleIndex]);
}

void toolFrame::setSpeedIndex(int index)
{
    speedIndex = index;
    ui->speedButton->setText(speedStr[speedIndex]);
}

void toolFrame::setFullScreenChecked(bool checked)
{
    ui->fullScreenCheckBox->setChecked(checked);
}

void toolFrame::setFullScreenEnable(bool enable)
{
    ui->fullScreenCheckBox->setEnabled(enable);
}

bool toolFrame::fullScreenChecked()
{
    return ui->fullScreenCheckBox->isChecked();
}


//初始化音量滑动条
void toolFrame::initVolumeSlider()
{
    ui->volumeHorizontalSlider->setRange(0,100);
    ui->volumeHorizontalSlider->setSingleStep(1);
    ui->volumeHorizontalSlider->setValue(80);
    ui->volumeHorizontalSlider->setPageStep(10);
}

void toolFrame::setVolumSliderEnable(bool status)
{
    ui->volumeHorizontalSlider->setEnabled(status);
}


toolFrame::~toolFrame()
{
    delete ui;
}

void toolFrame::setQSS()
{
    this->setStyleSheet(toolFrameStyle::frameStytle);
    ui->pauseBtn->setStyleSheet(toolFrameStyle::pauseButtonStytle);
    ui->videoListBtn->setStyleSheet(toolFrameStyle::videoListButtonStytle);
    ui->nextBtn->setStyleSheet(toolFrameStyle::nextButtonStytle);
    ui->prevBtn->setStyleSheet(toolFrameStyle::prevButtonStytle);
    //    ui->configBtn->setStyleSheet(toolFrameStyle::configButtonStytle);
    ui->volumeLabel->setStyleSheet(toolFrameStyle::voulmeLabelStytle);
    ui->speedLabel->setStyleSheet(toolFrameStyle::speedLabelStytle);
    //    ui->videoScaleLabel->setStyleSheet(toolFrameStyle::scaleLabelStytle);
    ui->speedButton->setStyleSheet(toolFrameStyle::buttonStytle);
    //    ui->scaleButton->setStyleSheet(toolFrameStyle::buttonStytle);
    ui->volumeHorizontalSlider->setStyleSheet(toolFrameStyle::volumeSliderStyle);
    ui->fullScreenCheckBox->setStyleSheet(nativeWidgetStyle::checkBoxStyle);
}




void toolFrame::on_pauseBtn_clicked()
{
    emit _pauseBtn_clicked(pauseStatus);
}

void toolFrame::on_volumeHorizontalSlider_valueChanged(int value)
{
    emit _volumeHorizontalSlider_valueChanged(value);
}


void toolFrame::on_nextBtn_clicked()
{
    emit _nextBtn_clicked();
}

void toolFrame::on_prevBtn_clicked()
{
    emit _prevBtn_clicked();
}




void toolFrame::on_speedButton_clicked()
{
    speedIndex =   (++speedIndex) %=5;
    ui->speedButton->setText(speedStr[speedIndex]);
    emit speedButtonClicked(speedIndex);

}

void toolFrame::on_fullScreenCheckBox_toggled(bool checked)
{
    emit fullScreenCheckBox_toggled(checked);
}

void toolFrame::on_screenShotCheckBox_toggled(bool checked)
{
    emit screenShotCheckBox_toggled(checked);
}
