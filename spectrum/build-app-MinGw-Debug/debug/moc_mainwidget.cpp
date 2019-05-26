/****************************************************************************
** Meta object code from reading C++ file 'mainwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../app/mainwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWidget_t {
    QByteArrayData data[29];
    char stringdata0[364];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWidget_t qt_meta_stringdata_MainWidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWidget"
QT_MOC_LITERAL(1, 11, 12), // "stateChanged"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 12), // "QAudio::Mode"
QT_MOC_LITERAL(4, 38, 4), // "mode"
QT_MOC_LITERAL(5, 43, 13), // "QAudio::State"
QT_MOC_LITERAL(6, 57, 5), // "state"
QT_MOC_LITERAL(7, 63, 13), // "formatChanged"
QT_MOC_LITERAL(8, 77, 12), // "QAudioFormat"
QT_MOC_LITERAL(9, 90, 6), // "format"
QT_MOC_LITERAL(10, 97, 15), // "spectrumChanged"
QT_MOC_LITERAL(11, 113, 8), // "position"
QT_MOC_LITERAL(12, 122, 6), // "length"
QT_MOC_LITERAL(13, 129, 17), // "FrequencySpectrum"
QT_MOC_LITERAL(14, 147, 8), // "spectrum"
QT_MOC_LITERAL(15, 156, 11), // "infoMessage"
QT_MOC_LITERAL(16, 168, 7), // "message"
QT_MOC_LITERAL(17, 176, 9), // "timeoutMs"
QT_MOC_LITERAL(18, 186, 12), // "errorMessage"
QT_MOC_LITERAL(19, 199, 7), // "heading"
QT_MOC_LITERAL(20, 207, 6), // "detail"
QT_MOC_LITERAL(21, 214, 20), // "audioPositionChanged"
QT_MOC_LITERAL(22, 235, 19), // "bufferLengthChanged"
QT_MOC_LITERAL(23, 255, 14), // "showFileDialog"
QT_MOC_LITERAL(24, 270, 18), // "showSettingsDialog"
QT_MOC_LITERAL(25, 289, 23), // "showToneGeneratorDialog"
QT_MOC_LITERAL(26, 313, 16), // "initializeRecord"
QT_MOC_LITERAL(27, 330, 14), // "updateModeMenu"
QT_MOC_LITERAL(28, 345, 18) // "updateButtonStates"

    },
    "MainWidget\0stateChanged\0\0QAudio::Mode\0"
    "mode\0QAudio::State\0state\0formatChanged\0"
    "QAudioFormat\0format\0spectrumChanged\0"
    "position\0length\0FrequencySpectrum\0"
    "spectrum\0infoMessage\0message\0timeoutMs\0"
    "errorMessage\0heading\0detail\0"
    "audioPositionChanged\0bufferLengthChanged\0"
    "showFileDialog\0showSettingsDialog\0"
    "showToneGeneratorDialog\0initializeRecord\0"
    "updateModeMenu\0updateButtonStates"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   79,    2, 0x0a /* Public */,
       7,    1,   84,    2, 0x0a /* Public */,
      10,    3,   87,    2, 0x0a /* Public */,
      15,    2,   94,    2, 0x0a /* Public */,
      18,    2,   99,    2, 0x0a /* Public */,
      21,    1,  104,    2, 0x0a /* Public */,
      22,    1,  107,    2, 0x0a /* Public */,
      23,    0,  110,    2, 0x08 /* Private */,
      24,    0,  111,    2, 0x08 /* Private */,
      25,    0,  112,    2, 0x08 /* Private */,
      26,    0,  113,    2, 0x08 /* Private */,
      27,    0,  114,    2, 0x08 /* Private */,
      28,    0,  115,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong, 0x80000000 | 13,   11,   12,   14,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   16,   17,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   19,   20,
    QMetaType::Void, QMetaType::LongLong,   11,
    QMetaType::Void, QMetaType::LongLong,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWidget *_t = static_cast<MainWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stateChanged((*reinterpret_cast< QAudio::Mode(*)>(_a[1])),(*reinterpret_cast< QAudio::State(*)>(_a[2]))); break;
        case 1: _t->formatChanged((*reinterpret_cast< const QAudioFormat(*)>(_a[1]))); break;
        case 2: _t->spectrumChanged((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< const FrequencySpectrum(*)>(_a[3]))); break;
        case 3: _t->infoMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->errorMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->audioPositionChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 6: _t->bufferLengthChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 7: _t->showFileDialog(); break;
        case 8: _t->showSettingsDialog(); break;
        case 9: _t->showToneGeneratorDialog(); break;
        case 10: _t->initializeRecord(); break;
        case 11: _t->updateModeMenu(); break;
        case 12: _t->updateButtonStates(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAudio::Mode >(); break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAudio::State >(); break;
            }
            break;
        }
    }
}

const QMetaObject MainWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainWidget.data,
      qt_meta_data_MainWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWidget.stringdata0))
        return static_cast<void*>(const_cast< MainWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
