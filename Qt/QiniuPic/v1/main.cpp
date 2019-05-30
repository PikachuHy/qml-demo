#include "mainwindow.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setOrganizationName("PikachuHy");
    QApplication::setOrganizationDomain("pikachu.net.cn");
    QApplication::setApplicationName("七牛图床");
    MainWindow w;

    return a.exec();
}
