#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "ToDoModel.h"
#include "ToDoList.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    qmlRegisterType<ToDoModel>("ToDo",1,0,"ToDoModel");
    qmlRegisterUncreatableType<ToDoList>("ToDo",1,0,"ToDoList",
        QStringLiteral("ToDoList should not be created in QMl"));
    ToDoList toDoList;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("toDoList",&toDoList);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
