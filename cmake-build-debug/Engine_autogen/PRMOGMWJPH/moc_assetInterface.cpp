/****************************************************************************
** Meta object code from reading C++ file 'assetInterface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/core/assetInterface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'assetInterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AssetInterface_t {
    QByteArrayData data[9];
    char stringdata0[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AssetInterface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AssetInterface_t qt_meta_stringdata_AssetInterface = {
    {
QT_MOC_LITERAL(0, 0, 14), // "AssetInterface"
QT_MOC_LITERAL(1, 15, 21), // "propertiesHaveChanged"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 21), // "objectIsToBeDestroyed"
QT_MOC_LITERAL(4, 60, 12), // "destroyAsset"
QT_MOC_LITERAL(5, 73, 11), // "scaleEdited"
QT_MOC_LITERAL(6, 85, 3), // "val"
QT_MOC_LITERAL(7, 89, 14), // "positionEdited"
QT_MOC_LITERAL(8, 104, 14) // "rotationEdited"

    },
    "AssetInterface\0propertiesHaveChanged\0"
    "\0objectIsToBeDestroyed\0destroyAsset\0"
    "scaleEdited\0val\0positionEdited\0"
    "rotationEdited"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AssetInterface[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   46,    2, 0x0a /* Public */,
       5,    1,   47,    2, 0x0a /* Public */,
       7,    1,   50,    2, 0x0a /* Public */,
       8,    1,   53,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void, QMetaType::Double,    6,

       0        // eod
};

void AssetInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AssetInterface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->propertiesHaveChanged(); break;
        case 1: _t->objectIsToBeDestroyed(); break;
        case 2: _t->destroyAsset(); break;
        case 3: _t->scaleEdited((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->positionEdited((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->rotationEdited((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AssetInterface::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AssetInterface::propertiesHaveChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AssetInterface::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AssetInterface::objectIsToBeDestroyed)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AssetInterface::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_AssetInterface.data,
    qt_meta_data_AssetInterface,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AssetInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AssetInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AssetInterface.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int AssetInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void AssetInterface::propertiesHaveChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void AssetInterface::objectIsToBeDestroyed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
