#-------------------------------------------------
#
# Project created by QtCreator 2025-01-19T19:52:26
#
#-------------------------------------------------

QT       += core gui
QT       +=network
QT       += multimedia



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoClient
TEMPLATE = app



# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.

DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += \
    main\main.cpp \
    clock/globalclock.cpp \
    ui/toolframe.cpp \
    ui/configurationwidget.cpp \
    ui/clickedhorizontalslider.cpp \
    thread/ffthread.cpp \
    queue/ffaframequeue.cpp \
    demuxer/ffdemuxer.cpp \
    decoder/ffadecoder.cpp \
    decoder/ffvdecoder.cpp \
    queue/ffvframequeue.cpp \
    queue/ffapacketqueue.cpp \
    queue/ffvpacketqueue.cpp \
    thread/ffadecoderthread.cpp \
    thread/ffvdecoderthread.cpp \
    event/ffeventloop.cpp \
    thread/ffthreadpool.cpp \
    queue/ffeventqueue.cpp \
    event/ffevent.cpp \
    opengl/ffglrenderwidget.cpp \
    timer/fftimer.cpp \
    resampler/ffaresampler.cpp \
    resampler/ffvresampler.cpp \
    thread/ffdemuxerthread.cpp \
    render/ffarender.cpp \
    render/ffvrender.cpp \
    ui/ffplayerwindow.cpp \
    event/ffprocessevent.cpp \
    event/ffreadyevent.cpp \
    event/ffendevent.cpp \
    event/ffseekevent.cpp \
    event/ffpauseevent.cpp \
    event/ffvolumeevent.cpp \
    event/ffstartevent.cpp \
    sonic/sonic.cpp \
    event/ffspeedevent.cpp

HEADERS += \
    clock/globalclock.h \
    ui/toolframe.h \
    ui/configurationwidget.h \
    tools/clientstylesheet.h \
    ui/clickedhorizontalslider.h \
    thread/ffthread.h \
    queue/ffaframequeue.h \
    demuxer/ffdemuxer.h \
    decoder/ffadecoder.h \
    decoder/ffvdecoder.h \
    queue/ffvframequeue.h \
    queue/ffapacketqueue.h \
    queue/ffvpacketqueue.h \
    thread/ffadecoderthread.h \
    thread/ffvdecoderthread.h \
    queue/ffpacket.h \
    event/ffeventloop.h \
    thread/ffthreadpool.h \
    queue/ffeventqueue.h \
    event/ffevent.h \
    opengl/ffglrenderwidget.h \
    timer/fftimer.h \
    resampler/ffaresampler.h \
    resampler/ffvresampler.h \
    thread/ffdemuxerthread.h \
    render/ffvrender.h \
    render/ffarender.h \
    ui/ffplayerwindow.h \
    player/ffplayercontext.h \
    event/ffprocessevent.h \
    event/ffreadyevent.h \
    event/ffendevent.h \
    event/ffseekevent.h \
    event/ffpauseevent.h \
    event/ffvolumeevent.h \
    event/ffstartevent.h \
    sonic/sonic.h \
    event/ffspeedevent.h

FORMS += \
    ui/toolframe.ui \
    ui/configurationwidget.ui \
    ui/ffplayerwindow.ui

INCLUDEPATH +=  $$PWD/include \
                $$PWD/ui \
                $$PWD/tools \
                $$PWD/clock


#Windows
win32
{
    LIBS+= \
    -L$$PWD/lib

    LIBS+= \
        -lavcodec \
        -lavdevice \
        -lavfilter \
        -lavformat  \
        -lavutil \
        -lpostproc \
        -lswresample \
        -lswscale \


    LIBS+=$$PWD\lib\libopencv_*.a

    LIBS += -lOpengl32 \
              -lglu32
}

#Linux
unix
{

    LIBS+=\
        -L/usr/local/lib

    LIBS+=\
        -lavcodec \
        -lavdevice \
        -lavfilter \
        -lavformat  \
        -lavutil \
        -lpostproc \
        -lswresample \
        -lswscale

}


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    image.qrc

DISTFILES +=

