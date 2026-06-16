/********************************************************************************
** Form generated from reading UI file 'ffplayerwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FFPLAYERWINDOW_H
#define UI_FFPLAYERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "clickedhorizontalslider.h"
#include "opengl/ffglrenderwidget.h"
#include "toolframe.h"

QT_BEGIN_NAMESPACE

class Ui_FFPlayerWindow
{
public:
    QHBoxLayout *horizontalLayout_11;
    QVBoxLayout *verticalLayout_4;
    FFGLRenderWidget *glWidget;
    QFrame *processFrame_;
    QHBoxLayout *horizontalLayout_10;
    clickedHorizontalSlider *processSlider;
    QLabel *timeLabel;
    toolFrame *_toolFrame;
    QFrame *videoListFrame;
    QVBoxLayout *verticalLayout_3;
    QLabel *videoListLabel;
    QLabel *onListTabel;
    QListView *videoListView;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *addVideoBtn;
    QPushButton *deleteVideoBtn;

    void setupUi(QWidget *FFPlayerWindow)
    {
        if (FFPlayerWindow->objectName().isEmpty())
            FFPlayerWindow->setObjectName(QString::fromUtf8("FFPlayerWindow"));
        FFPlayerWindow->resize(1044, 755);
        horizontalLayout_11 = new QHBoxLayout(FFPlayerWindow);
        horizontalLayout_11->setSpacing(0);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        glWidget = new FFGLRenderWidget(FFPlayerWindow);
        glWidget->setObjectName(QString::fromUtf8("glWidget"));
        glWidget->setMouseTracking(true);

        verticalLayout_4->addWidget(glWidget);

        processFrame_ = new QFrame(FFPlayerWindow);
        processFrame_->setObjectName(QString::fromUtf8("processFrame_"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(processFrame_->sizePolicy().hasHeightForWidth());
        processFrame_->setSizePolicy(sizePolicy);
        processFrame_->setMouseTracking(true);
        processFrame_->setFrameShape(QFrame::StyledPanel);
        processFrame_->setFrameShadow(QFrame::Raised);
        horizontalLayout_10 = new QHBoxLayout(processFrame_);
        horizontalLayout_10->setSpacing(0);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        processSlider = new clickedHorizontalSlider(processFrame_);
        processSlider->setObjectName(QString::fromUtf8("processSlider"));
        sizePolicy.setHeightForWidth(processSlider->sizePolicy().hasHeightForWidth());
        processSlider->setSizePolicy(sizePolicy);
        processSlider->setCursor(QCursor(Qt::PointingHandCursor));
        processSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_10->addWidget(processSlider);

        timeLabel = new QLabel(processFrame_);
        timeLabel->setObjectName(QString::fromUtf8("timeLabel"));
        sizePolicy.setHeightForWidth(timeLabel->sizePolicy().hasHeightForWidth());
        timeLabel->setSizePolicy(sizePolicy);

        horizontalLayout_10->addWidget(timeLabel);

        horizontalLayout_10->setStretch(0, 100);

        verticalLayout_4->addWidget(processFrame_);

        _toolFrame = new toolFrame(FFPlayerWindow);
        _toolFrame->setObjectName(QString::fromUtf8("_toolFrame"));
        _toolFrame->setMouseTracking(true);
        _toolFrame->setFrameShape(QFrame::StyledPanel);
        _toolFrame->setFrameShadow(QFrame::Raised);

        verticalLayout_4->addWidget(_toolFrame);

        verticalLayout_4->setStretch(0, 100);
        verticalLayout_4->setStretch(1, 1);
        verticalLayout_4->setStretch(2, 1);

        horizontalLayout_11->addLayout(verticalLayout_4);

        videoListFrame = new QFrame(FFPlayerWindow);
        videoListFrame->setObjectName(QString::fromUtf8("videoListFrame"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(videoListFrame->sizePolicy().hasHeightForWidth());
        videoListFrame->setSizePolicy(sizePolicy1);
        videoListFrame->setMaximumSize(QSize(300, 16777215));
        videoListFrame->setMouseTracking(true);
        videoListFrame->setFrameShape(QFrame::StyledPanel);
        videoListFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(videoListFrame);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        videoListLabel = new QLabel(videoListFrame);
        videoListLabel->setObjectName(QString::fromUtf8("videoListLabel"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(videoListLabel->sizePolicy().hasHeightForWidth());
        videoListLabel->setSizePolicy(sizePolicy2);
        videoListLabel->setMinimumSize(QSize(0, 0));
        QFont font;
        font.setPointSize(20);
        videoListLabel->setFont(font);
        videoListLabel->setMouseTracking(true);

        verticalLayout_3->addWidget(videoListLabel);

        onListTabel = new QLabel(videoListFrame);
        onListTabel->setObjectName(QString::fromUtf8("onListTabel"));
        sizePolicy2.setHeightForWidth(onListTabel->sizePolicy().hasHeightForWidth());
        onListTabel->setSizePolicy(sizePolicy2);
        onListTabel->setMouseTracking(true);

        verticalLayout_3->addWidget(onListTabel);

        videoListView = new QListView(videoListFrame);
        videoListView->setObjectName(QString::fromUtf8("videoListView"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(videoListView->sizePolicy().hasHeightForWidth());
        videoListView->setSizePolicy(sizePolicy3);
        videoListView->setMinimumSize(QSize(200, 0));
        videoListView->setMouseTracking(true);

        verticalLayout_3->addWidget(videoListView);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(4);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(4, 4, 4, 4);
        addVideoBtn = new QPushButton(videoListFrame);
        addVideoBtn->setObjectName(QString::fromUtf8("addVideoBtn"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(addVideoBtn->sizePolicy().hasHeightForWidth());
        addVideoBtn->setSizePolicy(sizePolicy4);
        addVideoBtn->setMinimumSize(QSize(80, 50));
        addVideoBtn->setMaximumSize(QSize(16777215, 16777215));
        addVideoBtn->setCursor(QCursor(Qt::PointingHandCursor));
        addVideoBtn->setMouseTracking(true);

        horizontalLayout_7->addWidget(addVideoBtn);

        deleteVideoBtn = new QPushButton(videoListFrame);
        deleteVideoBtn->setObjectName(QString::fromUtf8("deleteVideoBtn"));
        sizePolicy4.setHeightForWidth(deleteVideoBtn->sizePolicy().hasHeightForWidth());
        deleteVideoBtn->setSizePolicy(sizePolicy4);
        deleteVideoBtn->setMinimumSize(QSize(80, 50));
        deleteVideoBtn->setMaximumSize(QSize(16777215, 16777215));
        deleteVideoBtn->setCursor(QCursor(Qt::PointingHandCursor));
        deleteVideoBtn->setMouseTracking(true);

        horizontalLayout_7->addWidget(deleteVideoBtn);

        horizontalLayout_7->setStretch(0, 1);
        horizontalLayout_7->setStretch(1, 1);

        verticalLayout_3->addLayout(horizontalLayout_7);

        verticalLayout_3->setStretch(0, 1);
        verticalLayout_3->setStretch(1, 1);
        verticalLayout_3->setStretch(2, 10);
        verticalLayout_3->setStretch(3, 1);

        horizontalLayout_11->addWidget(videoListFrame);

        horizontalLayout_11->setStretch(0, 10);
        horizontalLayout_11->setStretch(1, 1);

        retranslateUi(FFPlayerWindow);

        QMetaObject::connectSlotsByName(FFPlayerWindow);
    } // setupUi

    void retranslateUi(QWidget *FFPlayerWindow)
    {
        FFPlayerWindow->setWindowTitle(QCoreApplication::translate("FFPlayerWindow", "FFPlayerWindow", nullptr));
        timeLabel->setText(QCoreApplication::translate("FFPlayerWindow", "00:00:00", nullptr));
        videoListLabel->setText(QCoreApplication::translate("FFPlayerWindow", "\346\222\255\346\224\276\345\210\227\350\241\250", nullptr));
        onListTabel->setText(QCoreApplication::translate("FFPlayerWindow", "\346\255\243\345\234\250\346\222\255\346\224\276\357\274\232\346\227\240", nullptr));
        addVideoBtn->setText(QString());
        deleteVideoBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FFPlayerWindow: public Ui_FFPlayerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FFPLAYERWINDOW_H
