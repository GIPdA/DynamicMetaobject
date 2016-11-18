#include "DynObject.h"

DynObject::DynObject(QObject *parent) : AbsObject(parent)
{
    QMetaObjectBuilder b;

    // Just as an example:
    // If you want to add meta objects in several steps (like with some methods),
    //  add the meta object to the builder first.
    if (m_metaObject) b.addMetaObject(m_metaObject);

    b.setClassName("DynObject");
    b.setSuperClass(&AbsObject::staticMetaObject);

    // Add a signal (create signals before methods and slots!)
    QMetaMethodBuilder s = b.addSignal("totoChanged(int)");

    // Add a method
    b.addMethod("setToto(int)", "void");    // Skippable, but used here in main.qml

    // Add a property (needs a signal before)
    // The notify signal is needed on the QML side for value update
    QMetaPropertyBuilder p = b.addProperty("toto", "int");
    p.setWritable(true);
    p.setNotifySignal(s);


    // Once the object is used in QML, any modification to the meta object
    //  will not be reflected on the QML side without destroying and recreating the QML object.
    m_metaObject = b.toMetaObject();
}


void DynObject::property_metacall(QMetaObject::Call _c, int _id, void** _a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DynObject *_t = this;
        qDebug("InvokeMetaMethod %d", _id);
        switch (_id) {
        case 0: _t->totoChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setToto((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        qDebug("IndexOfMethod");
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DynObject::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DynObject::totoChanged)) {
                *result = 0;
                return;
            }
        }
    }

    else if (_c == QMetaObject::ReadProperty) {
        qDebug("ReadProperty %d", _id);
        DynObject *_t = this;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->toto(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        qDebug("WriteProperty %d", _id);
        DynObject *_t = this;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setToto(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
        qDebug("ResetProperty %d", _id);
    }
}


int DynObject::qt_metacall(QMetaObject::Call call, int id, void** args)
{
    qDebug("qt_metacall: %d", id);

    // Call base class first
    id = AbsObject::qt_metacall(call, id, args);

    if (id < 0)
        return id;

    if (call == QMetaObject::InvokeMetaMethod) {
        qDebug("qt_metacall::InvokeMetaMethod %d", id);
        if (id < 2) // Number of meta methods, 2 here (totoChanged, setToto)
            property_metacall(call, id, args);
        id -= 2; // Number of meta methods
    } else if (call == QMetaObject::RegisterMethodArgumentMetaType) {
        qDebug("qt_metacall::RegisterMethodArgumentMetaType %d", id);
        if (id < 2) // Number of meta methods
            *reinterpret_cast<int*>(args[0]) = -1;
        id -= 2; // Number of meta methods
    }

    else if (call == QMetaObject::ReadProperty || call == QMetaObject::WriteProperty
             || call == QMetaObject::ResetProperty || call == QMetaObject::RegisterPropertyMetaType) {
        property_metacall(call, id, args);
        id -= 1;    // Number of properties (only one here)
    } else if (call == QMetaObject::QueryPropertyDesignable) {
        id -= 1;    // Same
    } else if (call == QMetaObject::QueryPropertyScriptable) {
        id -= 1;    // ...
    } else if (call == QMetaObject::QueryPropertyStored) {
        id -= 1;
    } else if (call == QMetaObject::QueryPropertyEditable) {
        id -= 1;
    } else if (call == QMetaObject::QueryPropertyUser) {
        id -= 1;
    }

    return id;
}
