/****************************************************************************
** Meta object code from reading C++ file 'DamageCounterUI.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../DamageCounterUI.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DamageCounterUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CDamageCounterUI_t {
    QByteArrayData data[18];
    char stringdata0[307];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CDamageCounterUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CDamageCounterUI_t qt_meta_stringdata_CDamageCounterUI = {
    {
QT_MOC_LITERAL(0, 0, 16), // "CDamageCounterUI"
QT_MOC_LITERAL(1, 17, 22), // "onDamageRecordsUpdated"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 25), // "onResetCurrentRaidClicked"
QT_MOC_LITERAL(4, 67, 22), // "onResetAllRaidsClicked"
QT_MOC_LITERAL(5, 90, 26), // "onExportCurrentRaidClicked"
QT_MOC_LITERAL(6, 117, 23), // "onExportAllRaidsClicked"
QT_MOC_LITERAL(7, 141, 15), // "onColumnResized"
QT_MOC_LITERAL(8, 157, 12), // "logicalIndex"
QT_MOC_LITERAL(9, 170, 7), // "oldSize"
QT_MOC_LITERAL(10, 178, 7), // "newSize"
QT_MOC_LITERAL(11, 186, 12), // "onTabChanged"
QT_MOC_LITERAL(12, 199, 5), // "index"
QT_MOC_LITERAL(13, 205, 15), // "onHeaderClicked"
QT_MOC_LITERAL(14, 221, 26), // "onWhitelistSettingsClicked"
QT_MOC_LITERAL(15, 248, 26), // "onActivateWhitelistClicked"
QT_MOC_LITERAL(16, 275, 18), // "onWhitelistChanged"
QT_MOC_LITERAL(17, 294, 12) // "newWhitelist"

    },
    "CDamageCounterUI\0onDamageRecordsUpdated\0"
    "\0onResetCurrentRaidClicked\0"
    "onResetAllRaidsClicked\0"
    "onExportCurrentRaidClicked\0"
    "onExportAllRaidsClicked\0onColumnResized\0"
    "logicalIndex\0oldSize\0newSize\0onTabChanged\0"
    "index\0onHeaderClicked\0onWhitelistSettingsClicked\0"
    "onActivateWhitelistClicked\0"
    "onWhitelistChanged\0newWhitelist"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CDamageCounterUI[] = {

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
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    3,   74,    2, 0x08 /* Private */,
      11,    1,   81,    2, 0x08 /* Private */,
      13,    1,   84,    2, 0x08 /* Private */,
      14,    0,   87,    2, 0x08 /* Private */,
      15,    0,   88,    2, 0x08 /* Private */,
      16,    1,   89,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    8,    9,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,   17,

       0        // eod
};

void CDamageCounterUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CDamageCounterUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onDamageRecordsUpdated(); break;
        case 1: _t->onResetCurrentRaidClicked(); break;
        case 2: _t->onResetAllRaidsClicked(); break;
        case 3: _t->onExportCurrentRaidClicked(); break;
        case 4: _t->onExportAllRaidsClicked(); break;
        case 5: _t->onColumnResized((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 6: _t->onTabChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->onHeaderClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->onWhitelistSettingsClicked(); break;
        case 9: _t->onActivateWhitelistClicked(); break;
        case 10: _t->onWhitelistChanged((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CDamageCounterUI::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CDamageCounterUI.data,
    qt_meta_data_CDamageCounterUI,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CDamageCounterUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CDamageCounterUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CDamageCounterUI.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CDamageCounterUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
