#ifndef FFPLAYERWINDOW_H
#define FFPLAYERWINDOW_H

#include <QWidget>
#include <iostream>
#include<QHash>
#include<QStandardItem>
#include<QFileDialog>
#include<QTimer>
#include<opencv2/opencv.hpp>
#include<QDateTime>
#include<QDir>


namespace Ui {
class FFPlayerWindow;
}

extern "C"{
#include"libavformat/avformat.h"
}
class FFGLRenderWidget;
class FFDemuxerThread;
class FFPlayerContext;
class FFARender;
class FFVRender;
class FFEventQueue;

class FFPlayerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit FFPlayerWindow(QWidget *parent = nullptr);
    ~FFPlayerWindow();

    void init(FFPlayerContext* playerCtx_);

public slots:
    void renderYUV(uint8_t *yBuf, uint8_t *uBuf, uint8_t *vBuf, int width, int height);
    void showPlayerProcessSec(int curSec_);
    void initPlayerTotalSec(int totalSec_,float aspect);
    void onPlayerEnd();
    void setAspect(float aspect);
    void setBlackScreen();

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event)override;

private slots:
    void fullScreen();
    void sendSeekEvent(int value);
    void sendPauseEvent();
    void initPlayer();

    bool addNewVideoToList(const QString &filePath);
    void on_videoListBtn_clicked();
    void on_addVideoBtn_clicked();
    void sendVolumeEvent(int value);

    void onMouseMoved();

    void setFullScreenState(bool flag);
    bool checkOnFrame();
    void on_videoListView_doubleClicked(const QModelIndex &index);

    void onNextBtn_clicked();
    void onPrevBtn_clicked();
    void on_deleteVideoBtn_clicked();
    void sendSpeedEvent(int index);

    void onFullScreen(bool checked);

private:
    void changePauseUI();
    void initStyle();
    void connectSignals();
    void changeUIState(QWidget* widget);
    void initVolumeSlider();
    void setItemFocus(QStandardItem *item,bool status);
    void banSlider();
    void setOnListLabel(const QString &text);
    void adjustVideo(int offset);

    void sendStartEvent(const std::string& url_);
    void sendEndEvent();
    void removeVideoFromList(QStandardItem *item);
    void savePlaylist();
    void loadPlaylist();

private:
    Ui::FFPlayerWindow *ui;
    FFPlayerContext* playerCtx = nullptr;
    FFEventQueue* evQueue;


    int totalSec = 0;
    int curSec = 0;

    int totalH = -1;
    int totalM = -1;
    int totalS = -1;

    int readyCount = 0;

    QList<QString> videoList;
    QHash<QStandardItem*,QString>itemHashTable; //存储Item路径
    QStandardItemModel* videoListModel;

    bool sliderStop = false;

    QTimer fullScreenTimer;
    bool playerEnd = false;
    std::string url;


};

#endif // FFPLAYERWINDOW_H
