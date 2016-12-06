/****************************************************************************
** Meta object code from reading C++ file 'facedetector.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../FaceDR/facedetector.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'facedetector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FaceDetector_t {
    QByteArrayData data[5];
    char stringdata0[54];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FaceDetector_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FaceDetector_t qt_meta_stringdata_FaceDetector = {
    {
QT_MOC_LITERAL(0, 0, 12), // "FaceDetector"
QT_MOC_LITERAL(1, 13, 12), // "capture_done"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 15), // "capture_allDone"
QT_MOC_LITERAL(4, 43, 10) // "match_done"

    },
    "FaceDetector\0capture_done\0\0capture_allDone\0"
    "match_done"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FaceDetector[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    0,   30,    2, 0x06 /* Public */,
       4,    0,   31,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FaceDetector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FaceDetector *_t = static_cast<FaceDetector *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->capture_done(); break;
        case 1: _t->capture_allDone(); break;
        case 2: _t->match_done(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FaceDetector::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FaceDetector::capture_done)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (FaceDetector::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FaceDetector::capture_allDone)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (FaceDetector::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FaceDetector::match_done)) {
                *result = 2;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject FaceDetector::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_FaceDetector.data,
      qt_meta_data_FaceDetector,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FaceDetector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FaceDetector::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FaceDetector.stringdata0))
        return static_cast<void*>(const_cast< FaceDetector*>(this));
    return QObject::qt_metacast(_clname);
}

int FaceDetector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void FaceDetector::capture_done()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void FaceDetector::capture_allDone()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void FaceDetector::match_done()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
