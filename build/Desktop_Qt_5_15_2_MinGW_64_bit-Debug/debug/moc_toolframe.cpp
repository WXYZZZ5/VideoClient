/****************************************************************************
** Meta object code from reading C++ file 'toolframe.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../ui/toolframe.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'toolframe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_toolFrame_t {
    QByteArrayData data[22];
    char stringdata0[423];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_toolFrame_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_toolFrame_t qt_meta_stringdata_toolFrame = {
    {
QT_MOC_LITERAL(0, 0, 9), // "toolFrame"
QT_MOC_LITERAL(1, 10, 36), // "_volumeHorizontalSlider_value..."
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 5), // "value"
QT_MOC_LITERAL(4, 54, 17), // "_pauseBtn_clicked"
QT_MOC_LITERAL(5, 72, 11), // "pauseStatus"
QT_MOC_LITERAL(6, 84, 16), // "_nextBtn_clicked"
QT_MOC_LITERAL(7, 101, 16), // "_prevBtn_clicked"
QT_MOC_LITERAL(8, 118, 18), // "_configBtn_clicked"
QT_MOC_LITERAL(9, 137, 18), // "scaleButtonClicked"
QT_MOC_LITERAL(10, 156, 5), // "index"
QT_MOC_LITERAL(11, 162, 18), // "speedButtonClicked"
QT_MOC_LITERAL(12, 181, 26), // "fullScreenCheckBox_toggled"
QT_MOC_LITERAL(13, 208, 7), // "checked"
QT_MOC_LITERAL(14, 216, 26), // "screenShotCheckBox_toggled"
QT_MOC_LITERAL(15, 243, 19), // "on_pauseBtn_clicked"
QT_MOC_LITERAL(16, 263, 38), // "on_volumeHorizontalSlider_val..."
QT_MOC_LITERAL(17, 302, 18), // "on_nextBtn_clicked"
QT_MOC_LITERAL(18, 321, 18), // "on_prevBtn_clicked"
QT_MOC_LITERAL(19, 340, 22), // "on_speedButton_clicked"
QT_MOC_LITERAL(20, 363, 29), // "on_fullScreenCheckBox_toggled"
QT_MOC_LITERAL(21, 393, 29) // "on_screenShotCheckBox_toggled"

    },
    "toolFrame\0_volumeHorizontalSlider_valueChanged\0"
    "\0value\0_pauseBtn_clicked\0pauseStatus\0"
    "_nextBtn_clicked\0_prevBtn_clicked\0"
    "_configBtn_clicked\0scaleButtonClicked\0"
    "index\0speedButtonClicked\0"
    "fullScreenCheckBox_toggled\0checked\0"
    "screenShotCheckBox_toggled\0"
    "on_pauseBtn_clicked\0"
    "on_volumeHorizontalSlider_valueChanged\0"
    "on_nextBtn_clicked\0on_prevBtn_clicked\0"
    "on_speedButton_clicked\0"
    "on_fullScreenCheckBox_toggled\0"
    "on_screenShotCheckBox_toggled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_toolFrame[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       4,    1,   97,    2, 0x06 /* Public */,
       6,    0,  100,    2, 0x06 /* Public */,
       7,    0,  101,    2, 0x06 /* Public */,
       8,    0,  102,    2, 0x06 /* Public */,
       9,    1,  103,    2, 0x06 /* Public */,
      11,    1,  106,    2, 0x06 /* Public */,
      12,    1,  109,    2, 0x06 /* Public */,
      14,    1,  112,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    0,  115,    2, 0x08 /* Private */,
      16,    1,  116,    2, 0x08 /* Private */,
      17,    0,  119,    2, 0x08 /* Private */,
      18,    0,  120,    2, 0x08 /* Private */,
      19,    0,  121,    2, 0x08 /* Private */,
      20,    1,  122,    2, 0x08 /* Private */,
      21,    1,  125,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void, QMetaType::Bool,   13,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void, QMetaType::Bool,   13,

       0        // eod
};

void toolFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<toolFrame *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->_volumeHorizontalSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->_pauseBtn_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->_nextBtn_clicked(); break;
        case 3: _t->_prevBtn_clicked(); break;
        case 4: _t->_configBtn_clicked(); break;
        case 5: _t->scaleButtonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->speedButtonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->fullScreenCheckBox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->screenShotCheckBox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_pauseBtn_clicked(); break;
        case 10: _t->on_volumeHorizontalSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_nextBtn_clicked(); break;
        case 12: _t->on_prevBtn_clicked(); break;
        case 13: _t->on_speedButton_clicked(); break;
        case 14: _t->on_fullScreenCheckBox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->on_screenShotCheckBox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (toolFrame::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&toolFrame::_volumeHorizontalSlider_valueChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (toolFrame::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&toolFrame::_pauseBtn_clicked)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (toolFrame::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&toolFrame::_nextBtn_clicked)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (toolFrame::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&toolFrame::_prevBtn_clicked)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (toolFrame::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&toolFrame::_configBtn_clicked)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (toolFrame::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&toolFrame::scaleButtonClicked)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (toolFrame::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&toolFrame::speedButtonClicked)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (toolFrame::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&toolFrame::fullScreenCheckBox_toggled)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (toolFrame::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&toolFrame::screenShotCheckBox_toggled)) {
                *result = 8;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject toolFrame::staticMetaObject = { {
    QMetaObject::SuperData::link<QFrame::staticMetaObject>(),
    qt_meta_stringdata_toolFrame.data,
    qt_meta_data_toolFrame,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *toolFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *toolFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_toolFrame.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int toolFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void toolFrame::_volumeHorizontalSlider_valueChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void toolFrame::_pauseBtn_clicked(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void toolFrame::_nextBtn_clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void toolFrame::_prevBtn_clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void toolFrame::_configBtn_clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void toolFrame::scaleButtonClicked(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void toolFrame::speedButtonClicked(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void toolFrame::fullScreenCheckBox_toggled(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void toolFrame::screenShotCheckBox_toggled(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
