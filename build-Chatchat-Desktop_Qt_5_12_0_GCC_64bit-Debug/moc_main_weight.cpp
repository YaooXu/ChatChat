/****************************************************************************
** Meta object code from reading C++ file 'main_weight.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Client/main_weight.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_weight.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Main_Weight_t {
    QByteArrayData data[8];
    char stringdata0[117];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Main_Weight_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Main_Weight_t qt_meta_stringdata_Main_Weight = {
    {
QT_MOC_LITERAL(0, 0, 11), // "Main_Weight"
QT_MOC_LITERAL(1, 12, 15), // "create_Chatroom"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 3), // "uID"
QT_MOC_LITERAL(4, 33, 12), // "hand_message"
QT_MOC_LITERAL(5, 46, 19), // "create_Chatroom_whz"
QT_MOC_LITERAL(6, 66, 24), // "on_clicked_Friend_Button"
QT_MOC_LITERAL(7, 91, 25) // "on_clicked_Message_Button"

    },
    "Main_Weight\0create_Chatroom\0\0uID\0"
    "hand_message\0create_Chatroom_whz\0"
    "on_clicked_Friend_Button\0"
    "on_clicked_Message_Button"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Main_Weight[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       4,    0,   42,    2, 0x0a /* Public */,
       5,    0,   43,    2, 0x0a /* Public */,
       6,    0,   44,    2, 0x08 /* Private */,
       7,    0,   45,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Main_Weight::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Main_Weight *_t = static_cast<Main_Weight *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->create_Chatroom((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->hand_message(); break;
        case 2: _t->create_Chatroom_whz(); break;
        case 3: _t->on_clicked_Friend_Button(); break;
        case 4: _t->on_clicked_Message_Button(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Main_Weight::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Main_Weight.data,
    qt_meta_data_Main_Weight,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Main_Weight::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Main_Weight::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Main_Weight.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Main_Weight::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
