#ifndef DYNOBJECT_H
#define DYNOBJECT_H

#include <QObject>
#include <QtDebug>
#include <private/qmetaobjectbuilder_p.h>

class AbsObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int test READ test MEMBER m_test)

public:
    AbsObject(QObject *parent) : QObject(parent), m_name("TOTO") {}

    QString name() const
    {
        return m_name;
    }

    int test() const {
        return m_test;
    }

public slots:
    void setName(QString name)
    {
        if (m_name == name)
            return;

        m_name = name;
        emit nameChanged(name);
    }

signals:
    void nameChanged(QString name);

private:
    QString m_name;
    int m_test = 1234;
};


class DynObject : public AbsObject
{
    //Q_OBJECT  // Don't add it!
    //Q_PROPERTY(int toto READ toto WRITE setToto NOTIFY totoChanged)   // Re-creating this "by hand"

public:
    explicit DynObject(QObject *parent = 0);

    ~DynObject() {
        free(m_metaObject); // No delete??
        //delete m_metaObject;
    }

    virtual const QMetaObject *metaObject() const override {
        return m_metaObject;
    }

    int toto() const
    {
        qDebug() << "toto() =" << m_toto;
        return m_toto;
    }

//signals:

    // Based on moc
    void totoChanged(int _t1) {
        void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
        QMetaObject::activate(this, metaObject(), 0, _a);
    }

//public slots:
    void setToto(int toto)
    {
        qDebug() << "setToto(" << toto << ")";
        if (m_toto == toto)
            return;

        m_toto = toto;
        emit totoChanged(toto);
    }

private:
    // Based on moc
    void property_metacall(QMetaObject::Call _c, int _id, void **_a);

    // qt_metacast is needed for qobject_cast
    //virtual void *qt_metacast(const char *);

    // Based on moc
    // call: Type of operation
    // id: Method or property index
    // args: Operation specific arguments
    virtual int qt_metacall(QMetaObject::Call call, int id, void ** args) override;

    QMetaObject *m_metaObject = nullptr;

    int m_toto = 42;
};

#endif // DYNOBJECT_H
