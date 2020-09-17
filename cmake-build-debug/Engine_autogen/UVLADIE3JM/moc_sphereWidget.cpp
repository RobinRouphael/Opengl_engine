/****************************************************************************
** Meta object code from reading C++ file 'sphereWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/sphereWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sphereWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SphereWidget_t {
    QByteArrayData data[6];
    char stringdata0[58];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SphereWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SphereWidget_t qt_meta_stringdata_SphereWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "SphereWidget"
QT_MOC_LITERAL(1, 13, 12), // "stacksEdited"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 3), // "val"
QT_MOC_LITERAL(4, 31, 13), // "sectorsEdited"
QT_MOC_LITERAL(5, 45, 12) // "radiusEdited"

    },
    "SphereWidget\0stacksEdited\0\0val\0"
    "sectorsEdited\0radiusEdited"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SphereWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       4,    1,   32,    2, 0x0a /* Public */,
       5,    1,   35,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Double,    3,

       0        // eod
};

void SphereWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SphereWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stacksEdited((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sectorsEdited((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->radiusEdited((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SphereWidget::staticMetaObject = { {
    &AssetInterface::staticMetaObject,
    qt_meta_stringdata_SphereWidget.data,
    qt_meta_data_SphereWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SphereWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SphereWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SphereWidget.stringdata0))
        return static_cast<void*>(this);
    return AssetInterface::qt_metacast(_clname);
}

int SphereWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AssetInterface::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
