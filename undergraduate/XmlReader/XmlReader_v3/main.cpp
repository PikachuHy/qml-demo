/**
 * 本程序为一个xml阅读器
 *
 * 2017年5月29日
 * 完成基本的解析功能，采用的解析方式是DOM
 */
#include <QtCore/QXmlStreamReader>
#include <QtWidgets/QApplication>
#include "MainWidget.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    MainWidget mainWidget;
    mainWidget.show();

    return app.exec();
}