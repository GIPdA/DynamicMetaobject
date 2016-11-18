#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "DynObject.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    DynObject *dyn = new DynObject;

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("dyn", dyn);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
