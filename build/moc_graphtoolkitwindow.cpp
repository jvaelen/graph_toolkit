/****************************************************************************
** Meta object code from reading C++ file 'graphtoolkitwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/observer/GUI/graphtoolkitwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graphtoolkitwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GraphToolKitWindow_t {
    QByteArrayData data[23];
    char stringdata[365];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_GraphToolKitWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_GraphToolKitWindow_t qt_meta_stringdata_GraphToolKitWindow = {
    {
QT_MOC_LITERAL(0, 0, 18),
QT_MOC_LITERAL(1, 19, 10),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 13),
QT_MOC_LITERAL(4, 45, 5),
QT_MOC_LITERAL(5, 51, 20),
QT_MOC_LITERAL(6, 72, 9),
QT_MOC_LITERAL(7, 82, 9),
QT_MOC_LITERAL(8, 92, 15),
QT_MOC_LITERAL(9, 108, 18),
QT_MOC_LITERAL(10, 127, 14),
QT_MOC_LITERAL(11, 142, 17),
QT_MOC_LITERAL(12, 160, 35),
QT_MOC_LITERAL(13, 196, 34),
QT_MOC_LITERAL(14, 231, 11),
QT_MOC_LITERAL(15, 243, 10),
QT_MOC_LITERAL(16, 254, 14),
QT_MOC_LITERAL(17, 269, 17),
QT_MOC_LITERAL(18, 287, 14),
QT_MOC_LITERAL(19, 302, 13),
QT_MOC_LITERAL(20, 316, 13),
QT_MOC_LITERAL(21, 330, 16),
QT_MOC_LITERAL(22, 347, 16)
    },
    "GraphToolKitWindow\0closeGraph\0\0"
    "setFocusGraph\0index\0changeFocusGraphType\0"
    "openGraph\0saveGraph\0doDrawingNormal\0"
    "doDrawingIterative\0doTheoryNormal\0"
    "doTheoryIterative\0startIterativeGraphDrawingAlgorithm\0"
    "startIterativeGraphTheoryAlgorithm\0"
    "randomGraph\0undoAction\0createNewGraph\0"
    "makeGraphComplete\0changeSettings\0"
    "exportAsImage\0stopAlgorithm\0"
    "setDefaultColors\0aboutApplication\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GraphToolKitWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  114,    2, 0x08,
       3,    1,  115,    2, 0x08,
       5,    0,  118,    2, 0x08,
       6,    0,  119,    2, 0x08,
       7,    0,  120,    2, 0x08,
       8,    0,  121,    2, 0x08,
       9,    0,  122,    2, 0x08,
      10,    0,  123,    2, 0x08,
      11,    0,  124,    2, 0x08,
      12,    0,  125,    2, 0x08,
      13,    0,  126,    2, 0x08,
      14,    0,  127,    2, 0x08,
      15,    0,  128,    2, 0x08,
      16,    0,  129,    2, 0x08,
      17,    0,  130,    2, 0x08,
      18,    0,  131,    2, 0x08,
      19,    0,  132,    2, 0x08,
      20,    0,  133,    2, 0x08,
      21,    0,  134,    2, 0x08,
      22,    0,  135,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GraphToolKitWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GraphToolKitWindow *_t = static_cast<GraphToolKitWindow *>(_o);
        switch (_id) {
        case 0: _t->closeGraph(); break;
        case 1: _t->setFocusGraph((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->changeFocusGraphType(); break;
        case 3: _t->openGraph(); break;
        case 4: _t->saveGraph(); break;
        case 5: _t->doDrawingNormal(); break;
        case 6: _t->doDrawingIterative(); break;
        case 7: _t->doTheoryNormal(); break;
        case 8: _t->doTheoryIterative(); break;
        case 9: _t->startIterativeGraphDrawingAlgorithm(); break;
        case 10: _t->startIterativeGraphTheoryAlgorithm(); break;
        case 11: _t->randomGraph(); break;
        case 12: _t->undoAction(); break;
        case 13: _t->createNewGraph(); break;
        case 14: _t->makeGraphComplete(); break;
        case 15: _t->changeSettings(); break;
        case 16: _t->exportAsImage(); break;
        case 17: _t->stopAlgorithm(); break;
        case 18: _t->setDefaultColors(); break;
        case 19: _t->aboutApplication(); break;
        default: ;
        }
    }
}

const QMetaObject GraphToolKitWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_GraphToolKitWindow.data,
      qt_meta_data_GraphToolKitWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *GraphToolKitWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GraphToolKitWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GraphToolKitWindow.stringdata))
        return static_cast<void*>(const_cast< GraphToolKitWindow*>(this));
    if (!strcmp(_clname, "Observer"))
        return static_cast< Observer*>(const_cast< GraphToolKitWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int GraphToolKitWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 20;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
