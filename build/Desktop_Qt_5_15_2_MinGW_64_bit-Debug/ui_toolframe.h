/********************************************************************************
** Form generated from reading UI file 'toolframe.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOOLFRAME_H
#define UI_TOOLFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_toolFrame
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QCheckBox *fullScreenCheckBox;
    QLabel *speedLabel;
    QPushButton *speedButton;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *prevBtn;
    QPushButton *pauseBtn;
    QPushButton *nextBtn;
    QSpacerItem *horizontalSpacer_2;
    QLabel *volumeLabel;
    QSlider *volumeHorizontalSlider;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *videoListBtn;

    void setupUi(QFrame *toolFrame)
    {
        if (toolFrame->objectName().isEmpty())
            toolFrame->setObjectName(QString::fromUtf8("toolFrame"));
        toolFrame->resize(1112, 83);
        horizontalLayout = new QHBoxLayout(toolFrame);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        fullScreenCheckBox = new QCheckBox(toolFrame);
        fullScreenCheckBox->setObjectName(QString::fromUtf8("fullScreenCheckBox"));

        horizontalLayout->addWidget(fullScreenCheckBox);

        speedLabel = new QLabel(toolFrame);
        speedLabel->setObjectName(QString::fromUtf8("speedLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(speedLabel->sizePolicy().hasHeightForWidth());
        speedLabel->setSizePolicy(sizePolicy);
        speedLabel->setMinimumSize(QSize(50, 0));
        speedLabel->setMaximumSize(QSize(16777215, 60));

        horizontalLayout->addWidget(speedLabel);

        speedButton = new QPushButton(toolFrame);
        speedButton->setObjectName(QString::fromUtf8("speedButton"));
        speedButton->setMinimumSize(QSize(100, 20));
        speedButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(speedButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        prevBtn = new QPushButton(toolFrame);
        prevBtn->setObjectName(QString::fromUtf8("prevBtn"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(prevBtn->sizePolicy().hasHeightForWidth());
        prevBtn->setSizePolicy(sizePolicy1);
        prevBtn->setMinimumSize(QSize(50, 50));
        prevBtn->setMaximumSize(QSize(70, 16777215));
        prevBtn->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(prevBtn);

        pauseBtn = new QPushButton(toolFrame);
        pauseBtn->setObjectName(QString::fromUtf8("pauseBtn"));
        sizePolicy1.setHeightForWidth(pauseBtn->sizePolicy().hasHeightForWidth());
        pauseBtn->setSizePolicy(sizePolicy1);
        pauseBtn->setMinimumSize(QSize(50, 50));
        pauseBtn->setMaximumSize(QSize(70, 16777215));
        pauseBtn->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(pauseBtn);

        nextBtn = new QPushButton(toolFrame);
        nextBtn->setObjectName(QString::fromUtf8("nextBtn"));
        sizePolicy.setHeightForWidth(nextBtn->sizePolicy().hasHeightForWidth());
        nextBtn->setSizePolicy(sizePolicy);
        nextBtn->setMinimumSize(QSize(50, 50));
        nextBtn->setMaximumSize(QSize(70, 16777215));
        nextBtn->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(nextBtn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        volumeLabel = new QLabel(toolFrame);
        volumeLabel->setObjectName(QString::fromUtf8("volumeLabel"));
        sizePolicy1.setHeightForWidth(volumeLabel->sizePolicy().hasHeightForWidth());
        volumeLabel->setSizePolicy(sizePolicy1);
        volumeLabel->setMinimumSize(QSize(70, 50));

        horizontalLayout->addWidget(volumeLabel);

        volumeHorizontalSlider = new QSlider(toolFrame);
        volumeHorizontalSlider->setObjectName(QString::fromUtf8("volumeHorizontalSlider"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(volumeHorizontalSlider->sizePolicy().hasHeightForWidth());
        volumeHorizontalSlider->setSizePolicy(sizePolicy2);
        volumeHorizontalSlider->setMinimumSize(QSize(100, 0));
        volumeHorizontalSlider->setCursor(QCursor(Qt::PointingHandCursor));
        volumeHorizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(volumeHorizontalSlider);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        videoListBtn = new QPushButton(toolFrame);
        videoListBtn->setObjectName(QString::fromUtf8("videoListBtn"));
        sizePolicy1.setHeightForWidth(videoListBtn->sizePolicy().hasHeightForWidth());
        videoListBtn->setSizePolicy(sizePolicy1);
        videoListBtn->setMinimumSize(QSize(70, 60));
        videoListBtn->setMaximumSize(QSize(16777215, 16777215));
        videoListBtn->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(videoListBtn);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(2, 1);
        horizontalLayout->setStretch(3, 1);
        horizontalLayout->setStretch(4, 4);
        horizontalLayout->setStretch(5, 3);
        horizontalLayout->setStretch(6, 3);
        horizontalLayout->setStretch(7, 3);
        horizontalLayout->setStretch(8, 2);
        horizontalLayout->setStretch(9, 1);
        horizontalLayout->setStretch(10, 2);
        horizontalLayout->setStretch(11, 1);
        horizontalLayout->setStretch(12, 1);

        retranslateUi(toolFrame);

        QMetaObject::connectSlotsByName(toolFrame);
    } // setupUi

    void retranslateUi(QFrame *toolFrame)
    {
        toolFrame->setWindowTitle(QCoreApplication::translate("toolFrame", "Frame", nullptr));
        fullScreenCheckBox->setText(QCoreApplication::translate("toolFrame", "\345\205\250\345\261\217", nullptr));
        speedLabel->setText(QString());
        speedButton->setText(QCoreApplication::translate("toolFrame", "1.0", nullptr));
        prevBtn->setText(QString());
        pauseBtn->setText(QString());
        nextBtn->setText(QString());
        volumeLabel->setText(QString());
        videoListBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class toolFrame: public Ui_toolFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOOLFRAME_H
