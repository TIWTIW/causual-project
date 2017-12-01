/****************************************************************************
** Meta object code from reading C++ file 'client.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../test_client/client.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Client_t {
    QByteArrayData data[21];
    char stringdata0[452];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Client_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Client_t qt_meta_stringdata_Client = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Client"
QT_MOC_LITERAL(1, 7, 28), // "on_pushButtonConnect_clicked"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 31), // "on_pushButtonDisconnect_clicked"
QT_MOC_LITERAL(4, 69, 26), // "on_pushButtonClear_clicked"
QT_MOC_LITERAL(5, 96, 32), // "on_pushButtonControlMode_clicked"
QT_MOC_LITERAL(6, 129, 30), // "on_pushButtonNeedImage_clicked"
QT_MOC_LITERAL(7, 160, 15), // "ClientConnected"
QT_MOC_LITERAL(8, 176, 18), // "ClientDisconnected"
QT_MOC_LITERAL(9, 195, 17), // "ClientSocketError"
QT_MOC_LITERAL(10, 213, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(11, 242, 1), // "e"
QT_MOC_LITERAL(12, 244, 14), // "ClientRecvData"
QT_MOC_LITERAL(13, 259, 14), // "ClientSendData"
QT_MOC_LITERAL(14, 274, 5), // "bytes"
QT_MOC_LITERAL(15, 280, 30), // "on_pushButtonSelfClean_clicked"
QT_MOC_LITERAL(16, 311, 28), // "on_pushButtonNoImage_clicked"
QT_MOC_LITERAL(17, 340, 28), // "on_pushButtonForward_clicked"
QT_MOC_LITERAL(18, 369, 25), // "on_pushButtonLeft_clicked"
QT_MOC_LITERAL(19, 395, 26), // "on_pushButtonRight_clicked"
QT_MOC_LITERAL(20, 422, 29) // "on_pushButtonBackward_clicked"

    },
    "Client\0on_pushButtonConnect_clicked\0"
    "\0on_pushButtonDisconnect_clicked\0"
    "on_pushButtonClear_clicked\0"
    "on_pushButtonControlMode_clicked\0"
    "on_pushButtonNeedImage_clicked\0"
    "ClientConnected\0ClientDisconnected\0"
    "ClientSocketError\0QAbstractSocket::SocketError\0"
    "e\0ClientRecvData\0ClientSendData\0bytes\0"
    "on_pushButtonSelfClean_clicked\0"
    "on_pushButtonNoImage_clicked\0"
    "on_pushButtonForward_clicked\0"
    "on_pushButtonLeft_clicked\0"
    "on_pushButtonRight_clicked\0"
    "on_pushButtonBackward_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Client[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08 /* Private */,
       3,    0,   95,    2, 0x08 /* Private */,
       4,    0,   96,    2, 0x08 /* Private */,
       5,    0,   97,    2, 0x08 /* Private */,
       6,    0,   98,    2, 0x08 /* Private */,
       7,    0,   99,    2, 0x08 /* Private */,
       8,    0,  100,    2, 0x08 /* Private */,
       9,    1,  101,    2, 0x08 /* Private */,
      12,    0,  104,    2, 0x08 /* Private */,
      13,    1,  105,    2, 0x08 /* Private */,
      15,    0,  108,    2, 0x08 /* Private */,
      16,    0,  109,    2, 0x08 /* Private */,
      17,    0,  110,    2, 0x08 /* Private */,
      18,    0,  111,    2, 0x08 /* Private */,
      19,    0,  112,    2, 0x08 /* Private */,
      20,    0,  113,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Client *_t = static_cast<Client *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButtonConnect_clicked(); break;
        case 1: _t->on_pushButtonDisconnect_clicked(); break;
        case 2: _t->on_pushButtonClear_clicked(); break;
        case 3: _t->on_pushButtonControlMode_clicked(); break;
        case 4: _t->on_pushButtonNeedImage_clicked(); break;
        case 5: _t->ClientConnected(); break;
        case 6: _t->ClientDisconnected(); break;
        case 7: _t->ClientSocketError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 8: _t->ClientRecvData(); break;
        case 9: _t->ClientSendData((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 10: _t->on_pushButtonSelfClean_clicked(); break;
        case 11: _t->on_pushButtonNoImage_clicked(); break;
        case 12: _t->on_pushButtonForward_clicked(); break;
        case 13: _t->on_pushButtonLeft_clicked(); break;
        case 14: _t->on_pushButtonRight_clicked(); break;
        case 15: _t->on_pushButtonBackward_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
}

const QMetaObject Client::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Client.data,
      qt_meta_data_Client,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Client::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Client.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
