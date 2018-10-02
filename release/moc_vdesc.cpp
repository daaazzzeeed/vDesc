/****************************************************************************
** Meta object code from reading C++ file 'vdesc.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../vDesc/src/vdesc.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vdesc.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_vDesc_t {
    QByteArrayData data[18];
    char stringdata0[296];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_vDesc_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_vDesc_t qt_meta_stringdata_vDesc = {
    {
QT_MOC_LITERAL(0, 0, 5), // "vDesc"
QT_MOC_LITERAL(1, 6, 15), // "onReplyFinished"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 14), // "QNetworkReply*"
QT_MOC_LITERAL(4, 38, 13), // "replyFinished"
QT_MOC_LITERAL(5, 52, 14), // "replyFinished2"
QT_MOC_LITERAL(6, 67, 14), // "replyFinished3"
QT_MOC_LITERAL(7, 82, 15), // "onReturnPressed"
QT_MOC_LITERAL(8, 98, 20), // "onChangeTokenClicked"
QT_MOC_LITERAL(9, 119, 19), // "onGetFriendsClicked"
QT_MOC_LITERAL(10, 139, 14), // "chooseIdOnline"
QT_MOC_LITERAL(11, 154, 8), // "chooseId"
QT_MOC_LITERAL(12, 163, 11), // "sendMessage"
QT_MOC_LITERAL(13, 175, 20), // "onGetMessagesClicked"
QT_MOC_LITERAL(14, 196, 26), // "onReplyForMessagesFinished"
QT_MOC_LITERAL(15, 223, 28), // "onReplyForSenderNameFinished"
QT_MOC_LITERAL(16, 252, 21), // "onDialogDoubleClicked"
QT_MOC_LITERAL(17, 274, 21) // "onCurrentDialogLoaded"

    },
    "vDesc\0onReplyFinished\0\0QNetworkReply*\0"
    "replyFinished\0replyFinished2\0"
    "replyFinished3\0onReturnPressed\0"
    "onChangeTokenClicked\0onGetFriendsClicked\0"
    "chooseIdOnline\0chooseId\0sendMessage\0"
    "onGetMessagesClicked\0onReplyForMessagesFinished\0"
    "onReplyForSenderNameFinished\0"
    "onDialogDoubleClicked\0onCurrentDialogLoaded"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_vDesc[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x08 /* Private */,
       4,    1,   92,    2, 0x08 /* Private */,
       5,    1,   95,    2, 0x08 /* Private */,
       6,    1,   98,    2, 0x08 /* Private */,
       7,    0,  101,    2, 0x08 /* Private */,
       8,    0,  102,    2, 0x08 /* Private */,
       9,    0,  103,    2, 0x08 /* Private */,
      10,    0,  104,    2, 0x08 /* Private */,
      11,    0,  105,    2, 0x08 /* Private */,
      12,    0,  106,    2, 0x08 /* Private */,
      13,    0,  107,    2, 0x08 /* Private */,
      14,    1,  108,    2, 0x08 /* Private */,
      15,    1,  111,    2, 0x08 /* Private */,
      16,    0,  114,    2, 0x08 /* Private */,
      17,    1,  115,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    2,

       0        // eod
};

void vDesc::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        vDesc *_t = static_cast<vDesc *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onReplyFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 1: _t->replyFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 2: _t->replyFinished2((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 3: _t->replyFinished3((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 4: _t->onReturnPressed(); break;
        case 5: _t->onChangeTokenClicked(); break;
        case 6: _t->onGetFriendsClicked(); break;
        case 7: _t->chooseIdOnline(); break;
        case 8: _t->chooseId(); break;
        case 9: _t->sendMessage(); break;
        case 10: _t->onGetMessagesClicked(); break;
        case 11: _t->onReplyForMessagesFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 12: _t->onReplyForSenderNameFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 13: _t->onDialogDoubleClicked(); break;
        case 14: _t->onCurrentDialogLoaded((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 14:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    }
}

const QMetaObject vDesc::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_vDesc.data,
      qt_meta_data_vDesc,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *vDesc::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *vDesc::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_vDesc.stringdata0))
        return static_cast<void*>(const_cast< vDesc*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int vDesc::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
