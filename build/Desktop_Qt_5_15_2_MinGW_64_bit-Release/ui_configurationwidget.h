/********************************************************************************
** Form generated from reading UI file 'configurationwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGURATIONWIDGET_H
#define UI_CONFIGURATIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigurationWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *configLabel;
    QSpacerItem *horizontalSpacer_2;
    QGridLayout *gridLayout_2;
    QCheckBox *grayCheckBox;
    QCheckBox *denoiseCheckBox;
    QCheckBox *gassianCheckBox;
    QCheckBox *fullScreenCheckBox;
    QCheckBox *verticalCheckBox;
    QCheckBox *horizontalCheckBox;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_5;
    QLabel *lightLabel;
    QSlider *lightHorizontalSlider;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *saturationLabel;
    QSlider *saturationHorizontalSlider;
    QSpacerItem *horizontalSpacer_3;
    QLabel *contrastLabel;
    QSlider *contrastHorizontalSlider;

    void setupUi(QWidget *ConfigurationWidget)
    {
        if (ConfigurationWidget->objectName().isEmpty())
            ConfigurationWidget->setObjectName(QString::fromUtf8("ConfigurationWidget"));
        ConfigurationWidget->resize(382, 352);
        verticalLayout = new QVBoxLayout(ConfigurationWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(80, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        configLabel = new QLabel(ConfigurationWidget);
        configLabel->setObjectName(QString::fromUtf8("configLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(configLabel->sizePolicy().hasHeightForWidth());
        configLabel->setSizePolicy(sizePolicy);
        configLabel->setMaximumSize(QSize(16777215, 100));

        horizontalLayout->addWidget(configLabel);

        horizontalSpacer_2 = new QSpacerItem(80, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        grayCheckBox = new QCheckBox(ConfigurationWidget);
        grayCheckBox->setObjectName(QString::fromUtf8("grayCheckBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(grayCheckBox->sizePolicy().hasHeightForWidth());
        grayCheckBox->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(grayCheckBox, 0, 0, 1, 1);

        denoiseCheckBox = new QCheckBox(ConfigurationWidget);
        denoiseCheckBox->setObjectName(QString::fromUtf8("denoiseCheckBox"));
        sizePolicy1.setHeightForWidth(denoiseCheckBox->sizePolicy().hasHeightForWidth());
        denoiseCheckBox->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(denoiseCheckBox, 0, 1, 1, 1);

        gassianCheckBox = new QCheckBox(ConfigurationWidget);
        gassianCheckBox->setObjectName(QString::fromUtf8("gassianCheckBox"));
        sizePolicy1.setHeightForWidth(gassianCheckBox->sizePolicy().hasHeightForWidth());
        gassianCheckBox->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(gassianCheckBox, 0, 2, 1, 1);

        fullScreenCheckBox = new QCheckBox(ConfigurationWidget);
        fullScreenCheckBox->setObjectName(QString::fromUtf8("fullScreenCheckBox"));
        sizePolicy1.setHeightForWidth(fullScreenCheckBox->sizePolicy().hasHeightForWidth());
        fullScreenCheckBox->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(fullScreenCheckBox, 1, 2, 1, 1);

        verticalCheckBox = new QCheckBox(ConfigurationWidget);
        verticalCheckBox->setObjectName(QString::fromUtf8("verticalCheckBox"));
        sizePolicy1.setHeightForWidth(verticalCheckBox->sizePolicy().hasHeightForWidth());
        verticalCheckBox->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(verticalCheckBox, 1, 1, 1, 1);

        horizontalCheckBox = new QCheckBox(ConfigurationWidget);
        horizontalCheckBox->setObjectName(QString::fromUtf8("horizontalCheckBox"));
        sizePolicy1.setHeightForWidth(horizontalCheckBox->sizePolicy().hasHeightForWidth());
        horizontalCheckBox->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(horizontalCheckBox, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_5 = new QSpacerItem(80, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        lightLabel = new QLabel(ConfigurationWidget);
        lightLabel->setObjectName(QString::fromUtf8("lightLabel"));

        horizontalLayout_5->addWidget(lightLabel);

        lightHorizontalSlider = new QSlider(ConfigurationWidget);
        lightHorizontalSlider->setObjectName(QString::fromUtf8("lightHorizontalSlider"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lightHorizontalSlider->sizePolicy().hasHeightForWidth());
        lightHorizontalSlider->setSizePolicy(sizePolicy2);
        lightHorizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(lightHorizontalSlider);

        horizontalSpacer_4 = new QSpacerItem(80, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        horizontalLayout_5->setStretch(1, 1);
        horizontalLayout_5->setStretch(2, 2);

        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        saturationLabel = new QLabel(ConfigurationWidget);
        saturationLabel->setObjectName(QString::fromUtf8("saturationLabel"));

        horizontalLayout_2->addWidget(saturationLabel);

        saturationHorizontalSlider = new QSlider(ConfigurationWidget);
        saturationHorizontalSlider->setObjectName(QString::fromUtf8("saturationHorizontalSlider"));
        sizePolicy2.setHeightForWidth(saturationHorizontalSlider->sizePolicy().hasHeightForWidth());
        saturationHorizontalSlider->setSizePolicy(sizePolicy2);
        saturationHorizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(saturationHorizontalSlider);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        contrastLabel = new QLabel(ConfigurationWidget);
        contrastLabel->setObjectName(QString::fromUtf8("contrastLabel"));

        horizontalLayout_2->addWidget(contrastLabel);

        contrastHorizontalSlider = new QSlider(ConfigurationWidget);
        contrastHorizontalSlider->setObjectName(QString::fromUtf8("contrastHorizontalSlider"));
        sizePolicy2.setHeightForWidth(contrastHorizontalSlider->sizePolicy().hasHeightForWidth());
        contrastHorizontalSlider->setSizePolicy(sizePolicy2);
        contrastHorizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(contrastHorizontalSlider);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 5);
        verticalLayout->setStretch(2, 5);
        verticalLayout->setStretch(3, 5);

        retranslateUi(ConfigurationWidget);

        QMetaObject::connectSlotsByName(ConfigurationWidget);
    } // setupUi

    void retranslateUi(QWidget *ConfigurationWidget)
    {
        ConfigurationWidget->setWindowTitle(QCoreApplication::translate("ConfigurationWidget", "Form", nullptr));
        configLabel->setText(QCoreApplication::translate("ConfigurationWidget", "\350\256\276\347\275\256", nullptr));
        grayCheckBox->setText(QCoreApplication::translate("ConfigurationWidget", "\347\201\260\345\272\246\345\233\276", nullptr));
        denoiseCheckBox->setText(QCoreApplication::translate("ConfigurationWidget", "\345\233\276\345\203\217\345\216\273\345\231\252", nullptr));
        gassianCheckBox->setText(QCoreApplication::translate("ConfigurationWidget", "\351\253\230\346\226\257\346\250\241\347\263\212", nullptr));
        fullScreenCheckBox->setText(QCoreApplication::translate("ConfigurationWidget", "\346\273\241\345\261\217", nullptr));
        verticalCheckBox->setText(QCoreApplication::translate("ConfigurationWidget", "\345\236\202\347\233\264\347\277\273\350\275\254", nullptr));
        horizontalCheckBox->setText(QCoreApplication::translate("ConfigurationWidget", "\346\260\264\345\271\263\347\277\273\350\275\254", nullptr));
        lightLabel->setText(QCoreApplication::translate("ConfigurationWidget", "\344\272\256\345\272\246", nullptr));
        saturationLabel->setText(QCoreApplication::translate("ConfigurationWidget", "\351\245\261\345\222\214\345\272\246", nullptr));
        contrastLabel->setText(QCoreApplication::translate("ConfigurationWidget", "\345\257\271\346\257\224\345\272\246", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfigurationWidget: public Ui_ConfigurationWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGURATIONWIDGET_H
