#include "configurationwidget.h"
#include "ui_configurationwidget.h"

ConfigurationWidget::ConfigurationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigurationWidget)
{
    ui->setupUi(this);
    setQSS();
    setSilder();
    setFixedSize(QSize(600,400));
    ui->configLabel->setAlignment(Qt::AlignCenter);
}

ConfigurationWidget::~ConfigurationWidget()
{
    delete ui;
}

//初始化正常
void ConfigurationWidget::initConfiguration()
{
    ui->contrastHorizontalSlider->setValue(50);
    ui->lightHorizontalSlider->setValue(50);
    ui->saturationHorizontalSlider->setValue(50);
    ui->gassianCheckBox->setChecked(false);
    ui->fullScreenCheckBox->setChecked(false);
    ui->denoiseCheckBox->setChecked(false);
    ui->horizontalCheckBox->setChecked(false);
    ui->verticalCheckBox->setChecked(false);
    ui->grayCheckBox->setChecked(false);

}

void ConfigurationWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setPen(Qt::black);
    painter.setBrush(Qt::NoBrush);

    QRect rect = this->rect();
    int offset = 5;
    QRect innerRect(rect.x() + offset, rect.y() + offset, rect.width() - 2 * offset, rect.height() - 2 * offset);
    painter.drawRect(innerRect);

    QWidget::paintEvent(event);
}

//设置QSS
void ConfigurationWidget::setQSS()
{

    ui->configLabel->setStyleSheet(configurationStyle::labelStytle);

    ui->lightLabel->setStyleSheet(configurationStyle::smallLabelStytle);
    ui->contrastLabel->setStyleSheet(configurationStyle::smallLabelStytle);
    ui->saturationLabel->setStyleSheet(configurationStyle::smallLabelStytle);

    ui->grayCheckBox->setStyleSheet(configurationStyle::checkBoxStyle);
    ui->gassianCheckBox->setStyleSheet(configurationStyle::checkBoxStyle);
    ui->denoiseCheckBox->setStyleSheet(configurationStyle::checkBoxStyle);
    ui->verticalCheckBox->setStyleSheet(configurationStyle::checkBoxStyle);
    ui->horizontalCheckBox->setStyleSheet(configurationStyle::checkBoxStyle);
    ui->fullScreenCheckBox->setStyleSheet(configurationStyle::checkBoxStyle);

    ui->contrastHorizontalSlider->setStyleSheet(configurationStyle::sliderStyle);
    ui->lightHorizontalSlider->setStyleSheet(configurationStyle::sliderStyle);
    ui->saturationHorizontalSlider->setStyleSheet(configurationStyle::sliderStyle);

}

void ConfigurationWidget::setSilder()
{
    ui->contrastHorizontalSlider->setRange(0,100);
    ui->contrastHorizontalSlider->setValue(50);

    ui->lightHorizontalSlider->setRange(0,100);
    ui->lightHorizontalSlider->setValue(50);

    ui->saturationHorizontalSlider->setRange(0,100);
    ui->saturationHorizontalSlider->setValue(50);
}

//改变亮度
void ConfigurationWidget::on_lightHorizontalSlider_valueChanged(int value)
{
    emit _lightHorizontalSlider_valueChanged(value);
}

//饱和度
void ConfigurationWidget::on_saturationHorizontalSlider_valueChanged(int value)
{
    emit _saturationHorizontalSlider_valueChanged(value);
}

//对比度
void ConfigurationWidget::on_contrastHorizontalSlider_valueChanged(int value)
{
    emit _contrastHorizontalSlider_valueChanged(value);
}


//高斯模糊
void ConfigurationWidget::on_gassianCheckBox_toggled(bool checked)
{
    emit _gassianCheckBox_toggled(checked);
}

//全屏
void ConfigurationWidget::on_fullScreenCheckBox_toggled(bool checked)
{
    emit _fullScreenCheckBox_toggled(checked);
}

//垂直翻转
void ConfigurationWidget::on_verticalCheckBox_toggled(bool checked)
{
    emit _verticalCheckBox_toggled(checked);
}

void ConfigurationWidget::on_horizontalCheckBox_toggled(bool checked)
{
    emit _horizontalCheckBox_toggle(checked);
}

void ConfigurationWidget::on_grayCheckBox_toggled(bool checked)
{
    emit _grayCheckBox_toggled(checked);
}

void ConfigurationWidget::on_denoiseCheckBox_toggled(bool checked)
{
    emit _denoiseCheckBox_toggled(checked);
}
