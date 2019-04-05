#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle(QString("Qt录音DEMO"));
    w.show();

    return a.exec();
}
