/****************************************************************************
** Meta object code from reading C++ file 'QSVideoRenderer.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../inc/vstream/QSVideoRenderer.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QSVideoRenderer.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_rtx__gui__QSVideoRenderer_t {
    QByteArrayData data[3];
    char stringdata[40];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_rtx__gui__QSVideoRenderer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_rtx__gui__QSVideoRenderer_t qt_meta_stringdata_rtx__gui__QSVideoRenderer = {
    {
QT_MOC_LITERAL(0, 0, 25), // "tuum::gui::QSVideoRenderer"
QT_MOC_LITERAL(1, 26, 12), // "imageChanged"
QT_MOC_LITERAL(2, 39, 0) // ""

    },
    "tuum::gui::QSVideoRenderer\0imageChanged\0"
    ""
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_rtx__gui__QSVideoRenderer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void tuum::gui::QSVideoRenderer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QSVideoRenderer *_t = static_cast<QSVideoRenderer *>(_o);
        switch (_id) {
        case 0: _t->imageChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QSVideoRenderer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QSVideoRenderer::imageChanged)) {
                *result = 0;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject tuum::gui::QSVideoRenderer::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_rtx__gui__QSVideoRenderer.data,
      qt_meta_data_rtx__gui__QSVideoRenderer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *tuum::gui::QSVideoRenderer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tuum::gui::QSVideoRenderer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_rtx__gui__QSVideoRenderer.stringdata))
        return static_cast<void*>(const_cast< QSVideoRenderer*>(this));
    return QThread::qt_metacast(_clname);
}

int tuum::gui::QSVideoRenderer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void tuum::gui::QSVideoRenderer::imageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
