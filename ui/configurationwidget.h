#ifndef CONFIGURATIONWIDGET_H
#define CONFIGURATIONWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

#include"clientstylesheet.h"

namespace Ui {
class ConfigurationWidget;
}

class ConfigurationWidget : public QWidget
{
    Q_OBJECT

signals:
    void _lightHorizontalSlider_valueChanged(float value);
    void _saturationHorizontalSlider_valueChanged(float value);
    void _contrastHorizontalSlider_valueChanged(float value);
    void _gassianCheckBox_toggled(bool checkedFlag);
    void _fullScreenCheckBox_toggled(bool checked);
    void  _verticalCheckBox_toggled(bool checked);
    void _horizontalCheckBox_toggle(bool checked);
    void _denoiseCheckBox_toggled(bool checked);
    void _grayCheckBox_toggled(bool checked);

public:
    explicit ConfigurationWidget(QWidget *parent = nullptr);
    ~ConfigurationWidget();

    void initConfiguration();
protected:
    void paintEvent(QPaintEvent*event);

private slots:
    void on_lightHorizontalSlider_valueChanged(int value);
    void on_saturationHorizontalSlider_valueChanged(int value);
    void on_contrastHorizontalSlider_valueChanged(int value);
    void on_gassianCheckBox_toggled(bool checked);
    void on_fullScreenCheckBox_toggled(bool checked);
    void on_verticalCheckBox_toggled(bool checked);
    void on_horizontalCheckBox_toggled(bool checked);
    void on_grayCheckBox_toggled(bool checked);
    void on_denoiseCheckBox_toggled(bool checked);

private:
    Ui::ConfigurationWidget *ui;

private:
    void setQSS();
    void setSilder();
};

#endif // CONFIGURATIONWIDGET_H
