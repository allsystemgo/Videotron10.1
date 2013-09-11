/****************************************************************************
** Meta object code from reading C++ file 'Videotron.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/Videotron.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Videotron.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Videotron[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      43,   37,   10,   10, 0x08,

 // methods: signature, parameters, type, tag, flags
      75,   10,   10,   10, 0x02,
     108,   99,   94,   10, 0x02,
     140,  129,   10,   10, 0x02,
     203,  179,  171,   10, 0x02,
     254,  232,   10,   10, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_Videotron[] = {
    "Videotron\0\0onSystemLanguageChanged()\0"
    "reply\0requestFinished(QNetworkReply*)\0"
    "initiateRequests()\0bool\0userName\0"
    "isAvailable(QString)\0title,body\0"
    "showInfoToast(QString,QString)\0QString\0"
    "objectName,defaultValue\0"
    "getValueFor(QString,QString)\0"
    "objectName,inputValue\0"
    "saveValueFor(QString,QString)\0"
};

void Videotron::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Videotron *_t = static_cast<Videotron *>(_o);
        switch (_id) {
        case 0: _t->onSystemLanguageChanged(); break;
        case 1: _t->requestFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 2: _t->initiateRequests(); break;
        case 3: { bool _r = _t->isAvailable((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: _t->showInfoToast((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: { QString _r = _t->getValueFor((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 6: _t->saveValueFor((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Videotron::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Videotron::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Videotron,
      qt_meta_data_Videotron, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Videotron::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Videotron::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Videotron::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Videotron))
        return static_cast<void*>(const_cast< Videotron*>(this));
    return QObject::qt_metacast(_clname);
}

int Videotron::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
