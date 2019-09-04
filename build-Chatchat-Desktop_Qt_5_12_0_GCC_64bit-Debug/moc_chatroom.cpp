/****************************************************************************
** Meta object code from reading C++ file 'chatroom.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Client/chatroom.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chatroom.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Chatroom_t {
    QByteArrayData data[17];
    char stringdata0[307];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Chatroom_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Chatroom_t qt_meta_stringdata_Chatroom = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Chatroom"
QT_MOC_LITERAL(1, 9, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 34), // "on_fontComboBox_currentFontCh..."
QT_MOC_LITERAL(4, 67, 1), // "f"
QT_MOC_LITERAL(5, 69, 31), // "on_comboBox_currentIndexChanged"
QT_MOC_LITERAL(6, 101, 4), // "arg1"
QT_MOC_LITERAL(7, 106, 23), // "on_toolButton_1_clicked"
QT_MOC_LITERAL(8, 130, 7), // "checked"
QT_MOC_LITERAL(9, 138, 23), // "on_toolButton_2_clicked"
QT_MOC_LITERAL(10, 162, 23), // "on_toolButton_3_clicked"
QT_MOC_LITERAL(11, 186, 23), // "on_toolButton_4_clicked"
QT_MOC_LITERAL(12, 210, 25), // "on_lineEdit_returnPressed"
QT_MOC_LITERAL(13, 236, 27), // "on_send_file_Button_clicked"
QT_MOC_LITERAL(14, 264, 20), // "readPendingDatagrams"
QT_MOC_LITERAL(15, 285, 18), // "requser_send_files"
QT_MOC_LITERAL(16, 304, 2) // "fs"

    },
    "Chatroom\0on_pushButton_clicked\0\0"
    "on_fontComboBox_currentFontChanged\0f\0"
    "on_comboBox_currentIndexChanged\0arg1\0"
    "on_toolButton_1_clicked\0checked\0"
    "on_toolButton_2_clicked\0on_toolButton_3_clicked\0"
    "on_toolButton_4_clicked\0"
    "on_lineEdit_returnPressed\0"
    "on_send_file_Button_clicked\0"
    "readPendingDatagrams\0requser_send_files\0"
    "fs"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Chatroom[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x0a /* Public */,
       3,    1,   70,    2, 0x0a /* Public */,
       5,    1,   73,    2, 0x0a /* Public */,
       7,    1,   76,    2, 0x0a /* Public */,
       9,    1,   79,    2, 0x0a /* Public */,
      10,    1,   82,    2, 0x0a /* Public */,
      11,    0,   85,    2, 0x0a /* Public */,
      12,    0,   86,    2, 0x0a /* Public */,
      13,    0,   87,    2, 0x0a /* Public */,
      14,    0,   88,    2, 0x0a /* Public */,
      15,    1,   89,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QFont,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   16,

       0        // eod
};

void Chatroom::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Chatroom *_t = static_cast<Chatroom *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_clicked(); break;
        case 1: _t->on_fontComboBox_currentFontChanged((*reinterpret_cast< const QFont(*)>(_a[1]))); break;
        case 2: _t->on_comboBox_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_toolButton_1_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->on_toolButton_2_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_toolButton_3_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->on_toolButton_4_clicked(); break;
        case 7: _t->on_lineEdit_returnPressed(); break;
        case 8: _t->on_send_file_Button_clicked(); break;
        case 9: _t->readPendingDatagrams(); break;
        case 10: _t->requser_send_files((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Chatroom::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Chatroom.data,
    qt_meta_data_Chatroom,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Chatroom::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Chatroom::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Chatroom.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Chatroom::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
