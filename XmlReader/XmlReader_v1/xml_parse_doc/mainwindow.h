#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "tinyxml/tinystr.h"
#include "tinyxml/tinyxml.h"
#include <QTableWidget>
#include <QTreeWidget>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionFile_triggered();

    void on_actionTxt_triggered();

    void on_actionExcel_triggered();

private:
    Ui::MainWindow *ui;
    TiXmlDocument docSource;
    TiXmlDocument docObject;
    QTableWidget* tableWidget=new QTableWidget();
    QTreeWidget* treeWidget=new QTreeWidget();
    //解析xml文件同时生成一颗新树
    void parseXml(TiXmlNode*parent, QTreeWidgetItem*itemParent, TiXmlNode *objectParent);
    //解析出表格
    void parseToForm(TiXmlNode*parent);
    void parseToForm(TiXmlNode*parent,QStringList& l);
    QStringList header;
    QList<QStringList> list;
    void exportToTxt(QString filepath);
    void exportToExcel(QString filepath);
};

#endif // MAINWINDOW_H
