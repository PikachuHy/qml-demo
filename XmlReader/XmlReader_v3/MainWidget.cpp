//
// Created by pikachu on 17-5-29.
//

#include <iostream>
#include "MainWidget.h"
QLayout* getCentralLayout(QWidget* widget){
    QHBoxLayout *qhBoxLayout = new QHBoxLayout;
//    qhBoxLayout.addS
}
MainWidget::MainWidget(QWidget *parent) : QWidget(parent) {
    qDebug()<<"MainWidget Created";

    this->setGeometry(100,100,800,600);

    QWidget *firstPageWidget = new QWidget;
    QWidget *secondPageWidget = new QWidget;
    QWidget *thirdPageWidget = new QWidget;

    QPushButton* qPushButton = new QPushButton("打开XML文件",firstPageWidget);

    treeWidget = new QTreeWidget;
    treeWidget->setColumnCount(2);
    {
        auto layout = new QHBoxLayout;
        layout->addWidget(treeWidget);
        secondPageWidget->setLayout(layout);
    }
    stackedWidget = new QStackedWidget;
    stackedWidget->addWidget(firstPageWidget);
    stackedWidget->addWidget(secondPageWidget);
    stackedWidget->addWidget(thirdPageWidget);

    connect(qPushButton,&QPushButton::clicked,[this,&secondPageWidget]{
        qDebug()<<"Set Current Widget to secondPageWidget";
        auto filename = QFileDialog::getOpenFileName(this, ("Open XML"), dir,
                                                      ("XML File (*.xml)"));
        qDebug()<<filename;
        if (filename.isEmpty()){

        } else{
            this->stackedWidget->setCurrentIndex(1);
            this->parseXml(filename);
        }
    });
    stackedWidget->setCurrentIndex(0);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(stackedWidget);
    setLayout(layout);
}

void MainWidget::parseXml(QString filename) {
    QDomDocument doc("mydocument");
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)){
        qDebug()<<"!file.open(QIODevice::ReadOnly)";
        return ;
    }
    if (!doc.setContent(&file)) {
        file.close();
        qDebug()<<"!doc.setContent(&file)";
        return ;
    }
    file.close();
    QDomElement docElem = doc.documentElement();
    auto item = new QTreeWidgetItem(this->treeWidget);
    item->setData(0,0,docElem.tagName());
    std::cout<<qPrintable(docElem.tagName())<<std::endl;
    readElement(docElem,1,item);
}

void MainWidget::readElement(QDomElement &docElem, int tab, QTreeWidgetItem *item) {
    QDomNode n = docElem.firstChild();
    if (n.isText()){
        std::cout<<"\t"<<qPrintable(n.toText().data())<<std::endl;
        item->setData(1,0,n.toText().data());
    } else{
        std::cout<<std::endl;
        while(!n.isNull()) {
            QDomElement e = n.toElement();
            if(!e.isNull()) {
                for (int i = 0; i < tab; ++i) {
                    std::cout<<"\t";
                }
                QTreeWidgetItem* subItem = nullptr;
                if (item!= nullptr){
                    subItem = new QTreeWidgetItem(item);
                    subItem->setData(0,0,e.tagName());
                }
                std::cout<<qPrintable(e.tagName());
                readElement(e,tab+1,subItem);
            }
            n = n.nextSibling();
        }
    }

}
