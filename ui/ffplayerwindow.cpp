#include "ffplayerwindow.h"
#include "ui_ffplayerwindow.h"
#include"clientstylesheet.h"
#include"event/ffseekevent.h"
#include"thread/ffdemuxerthread.h"
#include"player/ffplayercontext.h"
#include"queue/ffeventqueue.h"
#include"render/ffarender.h"
#include"render/ffvrender.h"
#include"event/ffpauseevent.h"
#include"event/ffvolumeevent.h"
#include"event/ffstartevent.h"
#include"event/ffendevent.h"
#include"event/ffspeedevent.h"
#include <QSettings>
#include <QFile>


FFPlayerWindow::FFPlayerWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FFPlayerWindow),
    videoListModel(new QStandardItemModel(this))
{
    ui->setupUi(this);
    ui->videoListView->setModel(videoListModel);
    ui->_toolFrame->hideConfigurationBtn();
    initPlayer();
}

void FFPlayerWindow::initStyle(){
    ui->processSlider->setStyleSheet(configurationStyle::sliderStyle);
    ui->timeLabel->setStyleSheet(configurationStyle::smallLabelStytle);
    ui->addVideoBtn->setStyleSheet(nativeWidgetStyle::addVideoStyle);
    ui->deleteVideoBtn->setStyleSheet(nativeWidgetStyle::deleteVideoStyle);
    ui->videoListLabel->setStyleSheet(nativeWidgetStyle::labelStytle);
    ui->onListTabel->setStyleSheet(nativeWidgetStyle::onListLabelStyle);
    ui->videoListView->setStyleSheet(nativeWidgetStyle::listViewStyle);
    ui->videoListFrame->setStyleSheet(nativeWidgetStyle::frameStytle);
}

void FFPlayerWindow::connectSignals()
{
    connect(ui->glWidget,&FFGLRenderWidget::mouseDoubleClick,this,&FFPlayerWindow::fullScreen);
    connect(ui->glWidget,&FFGLRenderWidget::mouseClick,this,&FFPlayerWindow::sendPauseEvent);
    connect(ui->processSlider,&clickedHorizontalSlider::videoSliderChange,this,&FFPlayerWindow::sendSeekEvent);

    connect(ui->_toolFrame,&toolFrame::_pauseBtn_clicked,this,&FFPlayerWindow::sendPauseEvent);
    connect(ui->_toolFrame,&toolFrame::_volumeHorizontalSlider_valueChanged,this,&FFPlayerWindow::sendVolumeEvent);
    connect(ui->_toolFrame,&toolFrame::speedButtonClicked,this,&FFPlayerWindow::sendSpeedEvent);
    connect(ui->_toolFrame,&toolFrame::_nextBtn_clicked,this,&FFPlayerWindow::onNextBtn_clicked);
    connect(ui->_toolFrame,&toolFrame::_prevBtn_clicked,this,&FFPlayerWindow::onPrevBtn_clicked);

    connect(ui->_toolFrame,&toolFrame::fullScreenCheckBox_toggled,this,&FFPlayerWindow::onFullScreen);
}

void FFPlayerWindow::changeUIState(QWidget* widget)
{
    widget->setEnabled(false);

    QTimer::singleShot(100,[widget](){
        widget->setEnabled(true);
    });
}
FFPlayerWindow::~FFPlayerWindow()
{
    savePlaylist();
    if(playerCtx){
        delete playerCtx;
        playerCtx = nullptr;
    }
    delete ui;
}

void FFPlayerWindow::sendSpeedEvent(int index)
{
    static float speed[] = { 1.0f,1.25f,1.5f,2.0f,0.5f };
    FFEvent* speedEv = new FFSpeedEvent(playerCtx,speed[index]);
    evQueue->enqueue(speedEv);
    changeUIState(ui->_toolFrame);
}

void FFPlayerWindow::init(FFPlayerContext *playerCtx_)
{
    playerCtx = playerCtx_;
    evQueue = &FFEventQueue::getInstance();
}

void FFPlayerWindow::renderYUV(uint8_t*yBuf,uint8_t*uBuf,uint8_t*vBuf,int width,int height)
{
    //    auto start = std::chrono::high_resolution_clock::now();
    ui->glWidget->setYUVData(yBuf, uBuf, vBuf, width,height);
    //    auto end = std::chrono::high_resolution_clock::now();
    //    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    //    std::cout << "Render duration: " << duration << "us" << std::endl;

    delete[] yBuf;
    delete[] uBuf;
    delete[] vBuf;
}

void FFPlayerWindow::showPlayerProcessSec(int curSec_)
{

    curSec = curSec_;
    int hourCur = curSec / 3600;
    int minuteCur = (curSec % 3600) / 60;
    int secondCur = curSec % 60;


    QString curTime = QString("%1:%2:%3 / %4:%5:%6")
            .arg(hourCur, 2, 10, QChar('0'))
            .arg(minuteCur, 2, 10, QChar('0'))
            .arg(secondCur, 2, 10, QChar('0'))
            .arg(totalH, 2, 10, QChar('0'))
            .arg(totalM, 2, 10, QChar('0'))
            .arg(totalS, 2, 10, QChar('0'));

    ui->timeLabel->setText(curTime);

    if(!sliderStop){ //防止进度条鬼畜
        ui->processSlider->setValue(curSec);
    }
}

void FFPlayerWindow::initPlayerTotalSec(int totalSec_,float aspect)
{
    if(++readyCount == 2){
        totalSec = totalSec_;

        totalH = totalSec / 3600;
        totalM = (totalSec % 3600) / 60;
        totalS = totalSec % 60;

        QString totalTime = QString("%1:%2:%3 / %4:%5:%6")
                .arg(0, 2, 10, QChar('0'))
                .arg(0, 2, 10, QChar('0'))
                .arg(0, 2, 10, QChar('0'))
                .arg(totalH, 2, 10, QChar('0'))
                .arg(totalM, 2, 10, QChar('0'))
                .arg(totalS, 2, 10, QChar('0'));
        ui->timeLabel->setText(totalTime);
        ui->processSlider->setSliderRange(0,totalSec);

        ui->_toolFrame->setPauseBtnStatus(false);
        ui->_toolFrame->setVolumeSliderValue(80);
        readyCount= 0;
        ui->_toolFrame->setSpeedIndex(0);
    }

    if(aspect != -1){
        setAspect(aspect);
    }
}

void FFPlayerWindow::initVolumeSlider(){
    ui->_toolFrame->initVolumeSlider();
}
void FFPlayerWindow::sendVolumeEvent(int value){
    double volume = value * 1.0  / 100;
    FFEvent* volumeEv = new FFVolumeEvent(playerCtx,volume);
    evQueue->enqueue(volumeEv);
}

void FFPlayerWindow::setItemFocus(QStandardItem *item, bool status)
{
    QModelIndex targetIndex = videoListModel->indexFromItem(item);
    QItemSelectionModel *selectionModel = ui->videoListView->selectionModel();
    if(status){
        selectionModel->select(targetIndex, QItemSelectionModel::Select);
    }
    else{
        selectionModel->select(targetIndex, QItemSelectionModel::Deselect);
    }
}

void FFPlayerWindow::banSlider()
{
    static QTimer timer;
    if(timer.isActive()){
        timer.stop();
    }
    timer.start(1000);
    sliderStop = true;

    connect(&timer,&QTimer::timeout,this,[this](){ sliderStop = false; });
}



//打开文件按钮
void FFPlayerWindow::on_addVideoBtn_clicked() {
    QString filePath = QFileDialog::getOpenFileName( this,"选择视频文件",QDir::homePath(), "视频文件 (*.mp4 *.avi *.mkv *.mov *.ts)");
    if (filePath.isEmpty()) {
        return;
    }

    //文件添加到List里面
    bool status = addNewVideoToList(filePath);

    //相同视频文件
    if(status){
    }
}

void FFPlayerWindow::onFullScreen(bool checked)
{
    if(checked){ //全屏
        showFullScreen();
        ui->_toolFrame->hide();
        ui->videoListFrame->hide();
        ui->processFrame_->hide();
    }
    else{ //恢复默认大小
        showNormal();
        ui->_toolFrame->show();
        ui->processFrame_->show();
        setCursor(Qt::ArrowCursor);

    }
    changeUIState(ui->_toolFrame);
}

void FFPlayerWindow::on_videoListBtn_clicked() {
    if (ui->videoListFrame->isVisible()) {
        ui->videoListFrame->hide();
    } else {
        ui->videoListFrame->show();
    }
    changeUIState(ui->videoListFrame);
}
void FFPlayerWindow::onPlayerEnd()
{
    playerEnd = true;
}

void FFPlayerWindow::setAspect(float aspect)
{
    ui->glWidget->setAspect(aspect);
}

void FFPlayerWindow::setBlackScreen()
{
    ui->glWidget->setBlackScreen();
}

void FFPlayerWindow::keyPressEvent(QKeyEvent *event)
{
    int sliderValue;
    int volumeValue;
    switch(event->key()){
    case Qt::Key_Escape:
        ui->_toolFrame->setFullScreenChecked(false);
        break;
    case Qt::Key_F:
       ui->_toolFrame->setFullScreenChecked(true);
        break;
    case Qt::Key_Space:
        sendPauseEvent();
        break;
    case Qt::Key_Left:
        sliderValue = std::max(0,ui->processSlider->value() - 15);
        ui->processSlider->setValue(sliderValue);
        sendSeekEvent(sliderValue);
        banSlider();
        break;
    case Qt::Key_Right:
        sliderValue = std::min(totalSec,ui->processSlider->value() + 15);
        ui->processSlider->setValue(sliderValue);
        sendSeekEvent(sliderValue);
        banSlider();
        break;
    case Qt::Key_Down:
        volumeValue = std::max(0,ui->_toolFrame->getVolumeSliderValue() - 10);
        sendVolumeEvent(volumeValue);
        ui->_toolFrame->setVolumeSliderValue(volumeValue);
        break;
    case Qt::Key_Up:
        volumeValue = std::min(100,ui->_toolFrame->getVolumeSliderValue() + 10);
        sendVolumeEvent(volumeValue);
        ui->_toolFrame->setVolumeSliderValue(volumeValue);
        break;
    default:
        QWidget::keyPressEvent(event);
        break;
    }
}

void FFPlayerWindow::adjustVideo(int offset)
{
    QString currentFilePath = QString::fromStdString(url);

    // 遍历Hash表，找到对应Item的索引
    QModelIndex currentIndex;
    for(auto it = itemHashTable.begin(); it != itemHashTable.end(); ++it){
        if(it.value() == currentFilePath){
            currentIndex = videoListModel->indexFromItem(it.key());
            break;
        }
    }

    // 当前索引是否有效
    if(!currentIndex.isValid()) return;

    // 获取下一个索引
    QModelIndex nextIndex = videoListModel->index(currentIndex.row() + offset, currentIndex.column());

    // 下一个索引是否有效
    if(!nextIndex.isValid()) return;

    // 获得播放路径
    QStandardItem* adjustedItem = videoListModel->itemFromIndex(nextIndex);
    QString nextFilePath = itemHashTable[adjustedItem];

    sendStartEvent(nextFilePath.toStdString());

    // 取消所有项的 focus
    QItemSelectionModel *selectionModel = ui->videoListView->selectionModel();
    selectionModel->clearSelection();

    // 设置切换后的项为 focus 状态
    setItemFocus(adjustedItem, true);
}
//下一集
void FFPlayerWindow::onNextBtn_clicked()
{
    adjustVideo(1);
}

//上一集
void FFPlayerWindow::onPrevBtn_clicked()
{
    adjustVideo(-1);

}
void FFPlayerWindow::sendStartEvent(const std::string &url_)
{
    url = url_;
    FFEvent* startEv = new FFStartEvent(playerCtx,url);
    evQueue->enqueue(startEv);
    setOnListLabel(QString::fromStdString(url).section("/",-1));
}

void FFPlayerWindow::sendEndEvent()
{
    url.clear();
    FFEvent* endEv = new FFEndEvent(playerCtx);
    evQueue->enqueue(endEv);
}

void FFPlayerWindow::mouseMoveEvent(QMouseEvent *event)
{
    bool flag = checkOnFrame();
    if(flag){
        QWidget::mouseMoveEvent(event);
    }
    else{
        onMouseMoved();
        QWidget::mouseMoveEvent(event);
    }
}

void FFPlayerWindow::fullScreen()
{
    if(!ui->_toolFrame->fullScreenChecked()){ //全屏
        showFullScreen();
        ui->_toolFrame->hide();
        ui->videoListFrame->hide();
        ui->processFrame_->hide();
        ui->_toolFrame->setFullScreenChecked(true);
    }
    else{ //恢复默认大小
        showNormal();
        ui->_toolFrame->show();
        ui->processFrame_->show();
        ui->_toolFrame->setFullScreenChecked(false);
    }
    changeUIState(ui->_toolFrame);
}

void FFPlayerWindow::sendSeekEvent(int value)
{
    if(playerEnd){
        return;
    }
    curSec = value;
    FFEvent* seekEv = new FFSeekEvent(playerCtx,value);
    evQueue->enqueue(seekEv);

    ui->processSlider->setValue(value);
    changeUIState(ui->processSlider);
}

void FFPlayerWindow::sendPauseEvent()
{
    FFEvent* pauseEv = new FFPauseEvent(playerCtx);
    evQueue->enqueue(pauseEv);

    changePauseUI();
}

void FFPlayerWindow::initPlayer()
{
    setMinimumSize(1200,800);
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);


    initStyle();
    initVolumeSlider();
    connectSignals();
    loadPlaylist();
}

void FFPlayerWindow::changePauseUI()
{
    ui->_toolFrame->setPauseBtnStyle();

    changeUIState(ui->_toolFrame);
    changeUIState(ui->glWidget);
}

bool FFPlayerWindow::addNewVideoToList(const QString& filePath)
{
    if(videoList.contains(filePath)){ //已存在
        return false;
    }

    QString fileName = filePath.section("/",-1);

    QStandardItem* item = new QStandardItem(fileName);
    item->setEditable(false);

    videoList.push_back(filePath);
    itemHashTable.insert(item,filePath);

    //添加到模型
    videoListModel->appendRow(item);

    //一开始加进来的时候,，设置选择状态
    if(videoList.size() == 1){
        setItemFocus(item,true);
    }
    savePlaylist();
    return true;
}


void FFPlayerWindow::onMouseMoved()
{

    if(fullScreenTimer.isActive()){
        fullScreenTimer.stop();
    }
    fullScreenTimer.start(3000);
    setFullScreenState(true);

    connect(&fullScreenTimer,&QTimer::timeout,this,[this](){
        if(!checkOnFrame()){
            setFullScreenState(false);
        }
    });
}

void FFPlayerWindow::setFullScreenState(bool flag)
{
    if(ui->_toolFrame->fullScreenChecked()){
        ui->processFrame_->setVisible(flag);
        ui->_toolFrame->setVisible(flag);
//        ui->videoListView->setVisible(flag);

        setCursor(flag? Qt::ArrowCursor:Qt::BlankCursor);
    }

}

bool FFPlayerWindow::checkOnFrame()
{
    QPoint pos = ui->_toolFrame->mapFromGlobal(QCursor::pos());
    if (pos.x() >= 0 && pos.y() >= 0 && pos.x() < ui->_toolFrame->width() && pos.y() < ui->_toolFrame->height()) {
        return true;
    }
    pos = ui->processFrame_->mapFromGlobal(QCursor::pos());
    if (pos.x() >= 0 && pos.y() >= 0 && pos.x() < ui->processFrame_->width() && pos.y() < ui->processFrame_->height()) {
        return true;
    }
    pos = ui->videoListView->mapFromGlobal(QCursor::pos());
    if (pos.x() >= 0 && pos.y() >= 0 && pos.x() < ui->videoListView->width() && pos.y() < ui->videoListView->height()) {
        return true;
    }

    return false;
}

void FFPlayerWindow::setOnListLabel(const QString &text)
{
    ui->onListTabel->setText("正在播放:" + text);
}

void FFPlayerWindow::on_videoListView_doubleClicked(const QModelIndex &index){
    QStandardItem *item = videoListModel->itemFromIndex(index);
    QString selectedPath = itemHashTable[item];

    //    std::cerr<<"on_videoListView_doubleClicked"<<std::endl;
    std::string url = selectedPath.toStdString();
    sendStartEvent(url);


}
void FFPlayerWindow::removeVideoFromList(QStandardItem* item)
{
    if(item ==nullptr){
        qDebug()<<"itme不存在，为nullptr!";
        return;
    }

    //从容器中删除
    QString filePath = itemHashTable[item];
    for(auto it = videoList.begin();it!=videoList.end();it++){
        if(*it == filePath){
            videoList.erase(it);
            break;
        }
    }
    for(auto it = itemHashTable.begin();it!=itemHashTable.end();it++){
        if(*it == filePath){
            itemHashTable.erase(it);
            break;
        }
    }

    //从videoListView中删除
    QModelIndex index = videoListModel->indexFromItem(item);
    if(index.isValid()){
        videoListModel->removeRow(index.row());
    }
    else{
        qWarning()<<"无法删除，Item无效！";
        return;
    }

}

void FFPlayerWindow::on_deleteVideoBtn_clicked()
{
    QItemSelectionModel *selectionModel = ui->videoListView->selectionModel();
    QModelIndexList selectedIndexs = selectionModel->selectedIndexes();

    for(const QModelIndex&index : selectedIndexs){
        QStandardItem *item = videoListModel->itemFromIndex(index);
        QString selecedPath = itemHashTable[item];

        if(url == selecedPath.toStdString()){
            setOnListLabel("无");
            sendEndEvent();
        }
        removeVideoFromList(item);
    }
    savePlaylist();
}

void FFPlayerWindow::savePlaylist()
{
    QSettings settings("VideoClient", "VideoClient");
    settings.beginGroup("Playlist");
    settings.setValue("count", videoList.size());
    for (int i = 0; i < videoList.size(); i++) {
        settings.setValue(QString("file_%1").arg(i), videoList[i]);
    }
    settings.setValue("currentPlaying", QString::fromStdString(url));
    settings.endGroup();
}

void FFPlayerWindow::loadPlaylist()
{
    QSettings settings("VideoClient", "VideoClient");
    settings.beginGroup("Playlist");
    int count = settings.value("count", 0).toInt();
    for (int i = 0; i < count; i++) {
        QString filePath = settings.value(QString("file_%1").arg(i)).toString();
        if (QFile::exists(filePath)) {
            addNewVideoToList(filePath);
        }
    }
    QString currentFilePath = settings.value("currentPlaying").toString();
    if (!currentFilePath.isEmpty() && QFile::exists(currentFilePath)) {
        url = currentFilePath.toStdString();
        for (auto it = itemHashTable.begin(); it != itemHashTable.end(); ++it) {
            if (it.value() == currentFilePath) {
                setItemFocus(it.key(), true);
                setOnListLabel(currentFilePath.section("/", -1));
                break;
            }
        }
    }
    settings.endGroup();
}