#include <QApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QtDebug>
#include <QFile>
#include <QLabel>
#include <QIcon>
#include "SystemTrayIcon.h"
#include "FontIconDatabase.h"
int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/icon/icon.png"));
    FontIconDatabase::init();
    QQmlApplicationEngine engine;
    qmlRegisterType<FontIconDatabase>("DB",1,0,"DB");
    engine.load(QUrl(QStringLiteral("../huorong/qml/main.qml")));
    if (engine.rootObjects().isEmpty()){

        qDebug()<<"QQmlApplicationEngine is Empty";
        return -1;
    }
//    SystemTrayIcon icon(&engine);
//    icon.show();
    return app.exec();
}
