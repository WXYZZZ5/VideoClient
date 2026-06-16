/****************************************************************************
** Meta object code from reading C++ file 'ffplayerwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../ui/ffplayerwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ffplayerwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FFPlayerWindow_t {
    QByteArrayData data[40];
    char stringdata0[509];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FFPlayerWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FFPlayerWindow_t qt_meta_stringdata_FFPlayerWindow = {
    {
QT_MOC_LITERAL(0, 0, 14), // "FFPlayerWindow"
QT_MOC_LITERAL(1, 15, 9), // "renderYUV"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 8), // "uint8_t*"
QT_MOC_LITERAL(4, 35, 4), // "yBuf"
QT_MOC_LITERAL(5, 40, 4), // "uBuf"
QT_MOC_LITERAL(6, 45, 4), // "vBuf"
QT_MOC_LITERAL(7, 50, 5), // "width"
QT_MOC_LITERAL(8, 56, 6), // "height"
QT_MOC_LITERAL(9, 63, 20), // "showPlayerProcessSec"
QT_MOC_LITERAL(10, 84, 7), // "curSec_"
QT_MOC_LITERAL(11, 92, 18), // "initPlayerTotalSec"
QT_MOC_LITERAL(12, 111, 9), // "totalSec_"
QT_MOC_LITERAL(13, 121, 6), // "aspect"
QT_MOC_LITERAL(14, 128, 11), // "onPlayerEnd"
QT_MOC_LITERAL(15, 140, 9), // "setAspect"
QT_MOC_LITERAL(16, 150, 14), // "setBlackScreen"
QT_MOC_LITERAL(17, 165, 10), // "fullScreen"
QT_MOC_LITERAL(18, 176, 13), // "sendSeekEvent"
QT_MOC_LITERAL(19, 190, 5), // "value"
QT_MOC_LITERAL(20, 196, 14), // "sendPauseEvent"
QT_MOC_LITERAL(21, 211, 10), // "initPlayer"
QT_MOC_LITERAL(22, 222, 17), // "addNewVideoToList"
QT_MOC_LITERAL(23, 240, 8), // "filePath"
QT_MOC_LITERAL(24, 249, 23), // "on_videoListBtn_clicked"
QT_MOC_LITERAL(25, 273, 22), // "on_addVideoBtn_clicked"
QT_MOC_LITERAL(26, 296, 15), // "sendVolumeEvent"
QT_MOC_LITERAL(27, 312, 12), // "onMouseMoved"
QT_MOC_LITERAL(28, 325, 18), // "setFullScreenState"
QT_MOC_LITERAL(29, 344, 4), // "flag"
QT_MOC_LITERAL(30, 349, 12), // "checkOnFrame"
QT_MOC_LITERAL(31, 362, 30), // "on_videoListView_doubleClicked"
QT_MOC_LITERAL(32, 393, 11), // "QModelIndex"
QT_MOC_LITERAL(33, 405, 5), // "index"
QT_MOC_LITERAL(34, 411, 17), // "onNextBtn_clicked"
QT_MOC_LITERAL(35, 429, 17), // "onPrevBtn_clicked"
QT_MOC_LITERAL(36, 447, 25), // "on_deleteVideoBtn_clicked"
QT_MOC_LITERAL(37, 473, 14), // "sendSpeedEvent"
QT_MOC_LITERAL(38, 488, 12), // "onFullScreen"
QT_MOC_LITERAL(39, 501, 7) // "checked"

    },
    "FFPlayerWindow\0renderYUV\0\0uint8_t*\0"
    "yBuf\0uBuf\0vBuf\0width\0height\0"
    "showPlayerProcessSec\0curSec_\0"
    "initPlayerTotalSec\0totalSec_\0aspect\0"
    "onPlayerEnd\0setAspect\0setBlackScreen\0"
    "fullScreen\0sendSeekEvent\0value\0"
    "sendPauseEvent\0initPlayer\0addNewVideoToList\0"
    "filePath\0on_videoListBtn_clicked\0"
    "on_addVideoBtn_clicked\0sendVolumeEvent\0"
    "onMouseMoved\0setFullScreenState\0flag\0"
    "checkOnFrame\0on_videoListView_doubleClicked\0"
    "QModelIndex\0index\0onNextBtn_clicked\0"
    "onPrevBtn_clicked\0on_deleteVideoBtn_clicked\0"
    "sendSpeedEvent\0onFullScreen\0checked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FFPlayerWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    5,  129,    2, 0x0a /* Public */,
       9,    1,  140,    2, 0x0a /* Public */,
      11,    2,  143,    2, 0x0a /* Public */,
      14,    0,  148,    2, 0x0a /* Public */,
      15,    1,  149,    2, 0x0a /* Public */,
      16,    0,  152,    2, 0x0a /* Public */,
      17,    0,  153,    2, 0x08 /* Private */,
      18,    1,  154,    2, 0x08 /* Private */,
      20,    0,  157,    2, 0x08 /* Private */,
      21,    0,  158,    2, 0x08 /* Private */,
      22,    1,  159,    2, 0x08 /* Private */,
      24,    0,  162,    2, 0x08 /* Private */,
      25,    0,  163,    2, 0x08 /* Private */,
      26,    1,  164,    2, 0x08 /* Private */,
      27,    0,  167,    2, 0x08 /* Private */,
      28,    1,  168,    2, 0x08 /* Private */,
      30,    0,  171,    2, 0x08 /* Private */,
      31,    1,  172,    2, 0x08 /* Private */,
      34,    0,  175,    2, 0x08 /* Private */,
      35,    0,  176,    2, 0x08 /* Private */,
      36,    0,  177,    2, 0x08 /* Private */,
      37,    1,  178,    2, 0x08 /* Private */,
      38,    1,  181,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3, QMetaType::Int, QMetaType::Int,    4,    5,    6,    7,    8,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::Float,   12,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QString,   23,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   29,
    QMetaType::Bool,
    QMetaType::Void, 0x80000000 | 32,   33,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   33,
    QMetaType::Void, QMetaType::Bool,   39,

       0        // eod
};

void FFPlayerWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FFPlayerWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->renderYUV((*reinterpret_cast< uint8_t*(*)>(_a[1])),(*reinterpret_cast< uint8_t*(*)>(_a[2])),(*reinterpret_cast< uint8_t*(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 1: _t->showPlayerProcessSec((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->initPlayerTotalSec((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 3: _t->onPlayerEnd(); break;
        case 4: _t->setAspect((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->setBlackScreen(); break;
        case 6: _t->fullScreen(); break;
        case 7: _t->sendSeekEvent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->sendPauseEvent(); break;
        case 9: _t->initPlayer(); break;
        case 10: { bool _r = _t->addNewVideoToList((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 11: _t->on_videoListBtn_clicked(); break;
        case 12: _t->on_addVideoBtn_clicked(); break;
        case 13: _t->sendVolumeEvent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->onMouseMoved(); break;
        case 15: _t->setFullScreenState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: { bool _r = _t->checkOnFrame();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 17: _t->on_videoListView_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 18: _t->onNextBtn_clicked(); break;
        case 19: _t->onPrevBtn_clicked(); break;
        case 20: _t->on_deleteVideoBtn_clicked(); break;
        case 21: _t->sendSpeedEvent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->onFullScreen((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject FFPlayerWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_FFPlayerWindow.data,
    qt_meta_data_FFPlayerWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FFPlayerWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FFPlayerWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FFPlayerWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int FFPlayerWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 23;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
