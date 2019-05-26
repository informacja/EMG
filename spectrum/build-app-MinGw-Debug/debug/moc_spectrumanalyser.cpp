/****************************************************************************
** Meta object code from reading C++ file 'spectrumanalyser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../app/spectrumanalyser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'spectrumanalyser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SpectrumAnalyserThread_t {
    QByteArrayData data[12];
    char stringdata0[164];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SpectrumAnalyserThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SpectrumAnalyserThread_t qt_meta_stringdata_SpectrumAnalyserThread = {
    {
QT_MOC_LITERAL(0, 0, 22), // "SpectrumAnalyserThread"
QT_MOC_LITERAL(1, 23, 19), // "calculationComplete"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 17), // "FrequencySpectrum"
QT_MOC_LITERAL(4, 62, 8), // "spectrum"
QT_MOC_LITERAL(5, 71, 17), // "setWindowFunction"
QT_MOC_LITERAL(6, 89, 14), // "WindowFunction"
QT_MOC_LITERAL(7, 104, 4), // "type"
QT_MOC_LITERAL(8, 109, 17), // "calculateSpectrum"
QT_MOC_LITERAL(9, 127, 6), // "buffer"
QT_MOC_LITERAL(10, 134, 14), // "inputFrequency"
QT_MOC_LITERAL(11, 149, 14) // "bytesPerSample"

    },
    "SpectrumAnalyserThread\0calculationComplete\0"
    "\0FrequencySpectrum\0spectrum\0"
    "setWindowFunction\0WindowFunction\0type\0"
    "calculateSpectrum\0buffer\0inputFrequency\0"
    "bytesPerSample"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SpectrumAnalyserThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   32,    2, 0x0a /* Public */,
       8,    3,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::Int, QMetaType::Int,    9,   10,   11,

       0        // eod
};

void SpectrumAnalyserThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SpectrumAnalyserThread *_t = static_cast<SpectrumAnalyserThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->calculationComplete((*reinterpret_cast< const FrequencySpectrum(*)>(_a[1]))); break;
        case 1: _t->setWindowFunction((*reinterpret_cast< WindowFunction(*)>(_a[1]))); break;
        case 2: _t->calculateSpectrum((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SpectrumAnalyserThread::*_t)(const FrequencySpectrum & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SpectrumAnalyserThread::calculationComplete)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject SpectrumAnalyserThread::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SpectrumAnalyserThread.data,
      qt_meta_data_SpectrumAnalyserThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SpectrumAnalyserThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SpectrumAnalyserThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SpectrumAnalyserThread.stringdata0))
        return static_cast<void*>(const_cast< SpectrumAnalyserThread*>(this));
    return QObject::qt_metacast(_clname);
}

int SpectrumAnalyserThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void SpectrumAnalyserThread::calculationComplete(const FrequencySpectrum & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_SpectrumAnalyser_t {
    QByteArrayData data[6];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SpectrumAnalyser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SpectrumAnalyser_t qt_meta_stringdata_SpectrumAnalyser = {
    {
QT_MOC_LITERAL(0, 0, 16), // "SpectrumAnalyser"
QT_MOC_LITERAL(1, 17, 15), // "spectrumChanged"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 17), // "FrequencySpectrum"
QT_MOC_LITERAL(4, 52, 8), // "spectrum"
QT_MOC_LITERAL(5, 61, 19) // "calculationComplete"

    },
    "SpectrumAnalyser\0spectrumChanged\0\0"
    "FrequencySpectrum\0spectrum\0"
    "calculationComplete"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SpectrumAnalyser[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   27,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void SpectrumAnalyser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SpectrumAnalyser *_t = static_cast<SpectrumAnalyser *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->spectrumChanged((*reinterpret_cast< const FrequencySpectrum(*)>(_a[1]))); break;
        case 1: _t->calculationComplete((*reinterpret_cast< const FrequencySpectrum(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SpectrumAnalyser::*_t)(const FrequencySpectrum & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SpectrumAnalyser::spectrumChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject SpectrumAnalyser::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SpectrumAnalyser.data,
      qt_meta_data_SpectrumAnalyser,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SpectrumAnalyser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SpectrumAnalyser::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SpectrumAnalyser.stringdata0))
        return static_cast<void*>(const_cast< SpectrumAnalyser*>(this));
    return QObject::qt_metacast(_clname);
}

int SpectrumAnalyser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void SpectrumAnalyser::spectrumChanged(const FrequencySpectrum & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
