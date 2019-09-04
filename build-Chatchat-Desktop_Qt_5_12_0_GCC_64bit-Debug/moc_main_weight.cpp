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
    QByteArrayData data[16];
    char stringdata0[234];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Main_Weight_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Main_Weight_t qt_meta_stringdata_Main_Weight = {
    {
QT_MOC_LITERAL(0, 0, 11), // "Main_Weight"
QT_MOC_LITERAL(1, 12, 10), // "log_signal"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 15), // "create_Chatroom"
QT_MOC_LITERAL(4, 40, 3), // "uID"
QT_MOC_LITERAL(5, 44, 12), // "hand_message"
QT_MOC_LITERAL(6, 57, 19), // "create_Chatroom_whz"
QT_MOC_LITERAL(7, 77, 13), // "create_addfri"
QT_MOC_LITERAL(8, 91, 11), // "create_info"
QT_MOC_LITERAL(9, 103, 17), // "change_main_photo"
QT_MOC_LITERAL(10, 121, 18), // "change_description"
QT_MOC_LITERAL(11, 140, 11), // "change_name"
QT_MOC_LITERAL(12, 152, 24), // "on_clicked_Friend_Button"
QT_MOC_LITERAL(13, 177, 25), // "on_clicked_Message_Button"
QT_MOC_LITERAL(14, 203, 23), // "on_clicked_group_button"
QT_MOC_LITERAL(15, 227, 6) // "log_in"

    },
    "Main_Weight\0log_signal\0\0create_Chatroom\0"
    "uID\0hand_message\0create_Chatroom_whz\0"
    "create_addfri\0create_info\0change_main_photo\0"
    "change_description\0change_name\0"
    "on_clicked_Friend_Button\0"
    "on_clicked_Message_Button\0"
    "on_clicked_group_button\0log_in"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Main_Weight[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   82,    2, 0x0a /* Public */,
       5,    0,   85,    2, 0x0a /* Public */,
       6,    0,   86,    2, 0x0a /* Public */,
       7,    0,   87,    2, 0x0a /* Public */,
       8,    0,   88,    2, 0x0a /* Public */,
       9,    1,   89,    2, 0x0a /* Public */,
      10,    1,   92,    2, 0x0a /* Public */,
      11,    1,   95,    2, 0x0a /* Public */,
      12,    0,   98,    2, 0x08 /* Private */,
      13,    0,   99,    2, 0x08 /* Private */,
      14,    0,  100,    2, 0x08 /* Private */,
      15,    0,  101,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
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
        case 0: _t->log_signal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->create_Chatroom((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->hand_message(); break;
        case 3: _t->create_Chatroom_whz(); break;
        case 4: _t->create_addfri(); break;
        case 5: _t->create_info(); break;
        case 6: _t->change_main_photo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->change_description((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->change_name((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->on_clicked_Friend_Button(); break;
        case 10: _t->on_clicked_Message_Button(); break;
        case 11: _t->on_clicked_group_button(); break;
        case 12: _t->log_in(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Main_Weight::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Main_Weight::log_signal)) {
                *result = 0;
                return;
            }
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
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void Main_Weight::log_signal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
