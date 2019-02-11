//
// Created by pikachu on 17-5-29.
//

#ifndef XMLREADER_MAINWIDGET_H
#define XMLREADER_MAINWIDGET_H


#include <QtWidgets/QWidget>
#include <QtXml/QDomElement>

#include <netinet/in.h>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QDebug>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QTreeWidget>
class MainWidget : public QWidget {
public:
    MainWidget(QWidget *parent = 0);

private:
    const char *const dir = "/home/pikachu/Documents/src/c++/study/XmlReader";
    QTreeWidget *treeWidget;
    QStackedWidget *stackedWidget;
    void parseXml(QString filename);
    void readElement(QDomElement& docElem, int tab, QTreeWidgetItem* item = nullptr);
};


#endif //XMLREADER_MAINWIDGET_H
