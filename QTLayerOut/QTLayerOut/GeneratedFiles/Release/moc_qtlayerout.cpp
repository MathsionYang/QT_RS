/****************************************************************************
** Meta object code from reading C++ file 'qtlayerout.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qtlayerout.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtlayerout.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QTLayerOut_t {
    QByteArrayData data[17];
    char stringdata0[250];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QTLayerOut_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QTLayerOut_t qt_meta_stringdata_QTLayerOut = {
    {
QT_MOC_LITERAL(0, 0, 10), // "QTLayerOut"
QT_MOC_LITERAL(1, 11, 9), // "File_open"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(4, 44, 32), // "on_treeWidget_currentItemChanged"
QT_MOC_LITERAL(5, 77, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(6, 94, 7), // "current"
QT_MOC_LITERAL(7, 102, 8), // "previous"
QT_MOC_LITERAL(8, 111, 24), // "on_radioButton_2_clicked"
QT_MOC_LITERAL(9, 136, 22), // "on_radioButton_clicked"
QT_MOC_LITERAL(10, 159, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(11, 183, 6), // "IniImg"
QT_MOC_LITERAL(12, 190, 15), // "itemPressedSlot"
QT_MOC_LITERAL(13, 206, 8), // "testSlot"
QT_MOC_LITERAL(14, 215, 15), // "mousePressEvent"
QT_MOC_LITERAL(15, 231, 12), // "QMouseEvent*"
QT_MOC_LITERAL(16, 244, 5) // "event"

    },
    "QTLayerOut\0File_open\0\0on_pushButton_clicked\0"
    "on_treeWidget_currentItemChanged\0"
    "QTreeWidgetItem*\0current\0previous\0"
    "on_radioButton_2_clicked\0"
    "on_radioButton_clicked\0on_pushButton_2_clicked\0"
    "IniImg\0itemPressedSlot\0testSlot\0"
    "mousePressEvent\0QMouseEvent*\0event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QTLayerOut[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    2,   66,    2, 0x08 /* Private */,
       8,    0,   71,    2, 0x08 /* Private */,
       9,    0,   72,    2, 0x08 /* Private */,
      10,    0,   73,    2, 0x08 /* Private */,
      11,    0,   74,    2, 0x08 /* Private */,
      12,    2,   75,    2, 0x08 /* Private */,
      13,    0,   80,    2, 0x08 /* Private */,
      14,    1,   81,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 5,    6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15,   16,

       0        // eod
};

void QTLayerOut::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QTLayerOut *_t = static_cast<QTLayerOut *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->File_open(); break;
        case 1: _t->on_pushButton_clicked(); break;
        case 2: _t->on_treeWidget_currentItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 3: _t->on_radioButton_2_clicked(); break;
        case 4: _t->on_radioButton_clicked(); break;
        case 5: _t->on_pushButton_2_clicked(); break;
        case 6: _t->IniImg(); break;
        case 7: _t->itemPressedSlot((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->testSlot(); break;
        case 9: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QTLayerOut::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_QTLayerOut.data,
      qt_meta_data_QTLayerOut,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QTLayerOut::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QTLayerOut::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QTLayerOut.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int QTLayerOut::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
