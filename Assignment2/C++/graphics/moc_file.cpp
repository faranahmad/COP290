/****************************************************************************
** Meta object code from reading C++ file 'file.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "file.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'file.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_file_t {
    QByteArrayData data[16];
    char stringdata[324];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_file_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_file_t qt_meta_stringdata_file = {
    {
QT_MOC_LITERAL(0, 0, 4),
QT_MOC_LITERAL(1, 5, 22),
QT_MOC_LITERAL(2, 28, 0),
QT_MOC_LITERAL(3, 29, 19),
QT_MOC_LITERAL(4, 49, 21),
QT_MOC_LITERAL(5, 71, 16),
QT_MOC_LITERAL(6, 88, 30),
QT_MOC_LITERAL(7, 119, 26),
QT_MOC_LITERAL(8, 146, 10),
QT_MOC_LITERAL(9, 157, 27),
QT_MOC_LITERAL(10, 185, 23),
QT_MOC_LITERAL(11, 209, 17),
QT_MOC_LITERAL(12, 227, 25),
QT_MOC_LITERAL(13, 253, 26),
QT_MOC_LITERAL(14, 280, 26),
QT_MOC_LITERAL(15, 307, 15)
    },
    "file\0on_movetodrive_clicked\0\0"
    "on_openfile_clicked\0on_deletefile_clicked\0"
    "on_share_clicked\0on_AddFileInClientSide_clicked\0"
    "on_OpenFileInDrive_clicked\0makechange\0"
    "on_GoingBackInDrive_clicked\0"
    "on_GetFromDrive_clicked\0on_logout_clicked\0"
    "on_changepassword_clicked\0"
    "on_DeleteFromDrive_clicked\0"
    "on_ViewSharedFiles_clicked\0on_sync_clicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_file[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08,
       3,    0,   85,    2, 0x08,
       4,    0,   86,    2, 0x08,
       5,    0,   87,    2, 0x08,
       6,    0,   88,    2, 0x08,
       7,    0,   89,    2, 0x08,
       8,    0,   90,    2, 0x08,
       9,    0,   91,    2, 0x08,
      10,    0,   92,    2, 0x08,
      11,    0,   93,    2, 0x08,
      12,    0,   94,    2, 0x08,
      13,    0,   95,    2, 0x08,
      14,    0,   96,    2, 0x08,
      15,    0,   97,    2, 0x08,

 // slots: parameters
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

void file::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        file *_t = static_cast<file *>(_o);
        switch (_id) {
        case 0: _t->on_movetodrive_clicked(); break;
        case 1: _t->on_openfile_clicked(); break;
        case 2: _t->on_deletefile_clicked(); break;
        case 3: _t->on_share_clicked(); break;
        case 4: _t->on_AddFileInClientSide_clicked(); break;
        case 5: _t->on_OpenFileInDrive_clicked(); break;
        case 6: _t->makechange(); break;
        case 7: _t->on_GoingBackInDrive_clicked(); break;
        case 8: _t->on_GetFromDrive_clicked(); break;
        case 9: _t->on_logout_clicked(); break;
        case 10: _t->on_changepassword_clicked(); break;
        case 11: _t->on_DeleteFromDrive_clicked(); break;
        case 12: _t->on_ViewSharedFiles_clicked(); break;
        case 13: _t->on_sync_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject file::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_file.data,
      qt_meta_data_file,  qt_static_metacall, 0, 0}
};


const QMetaObject *file::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *file::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_file.stringdata))
        return static_cast<void*>(const_cast< file*>(this));
    return QDialog::qt_metacast(_clname);
}

int file::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
