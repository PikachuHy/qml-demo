#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include "xlsxdocument.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    treeWidget->setColumnCount(0);
    this->setCentralWidget(treeWidget);
    tableWidget->setGeometry(10,30,800,600);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionFile_triggered()
{
    //打开xml文件
    QString filePath=QFileDialog::getOpenFileName(0,"","","xml文件(*.xml)");
    if(filePath.isEmpty()){
        return;
    }
    docSource.Clear();
    docObject.Clear();
    tableWidget->close();
    treeWidget->clear();
    tableWidget->clear();
    list.clear();
    header.clear();
    if(!docSource.LoadFile(filePath.toStdString().data())){
        QMessageBox::information(0,"info",QFile(filePath).fileName()+"打开失败");
        return;
    }
    TiXmlNode* xmlRoot=docSource.RootElement();
    auto item=new QTreeWidgetItem(treeWidget);
    item->setText(0,xmlRoot->Value());
    auto newNode=new TiXmlElement(xmlRoot->Value());
    docObject.LinkEndChild(newNode);
    parseXml(xmlRoot,item,newNode);
    treeWidget->setColumnCount(2);
    if(!docObject.SaveFile("t.xml")){
        QMessageBox::information(0,"info","保存失败");
    }
    xmlRoot=docObject.RootElement();
    parseToForm(xmlRoot);
    qDebug()<<header;
    //用表格呈现
    tableWidget->setColumnCount(header.size());
    tableWidget->setRowCount(list.size());
    tableWidget->setHorizontalHeaderLabels(header);
    qDebug()<<header.size()<<list.size()<<list.at(0).size();
    for(int i=0;i<list.size();i++){
        for(int j=0;j<list.at(i).size();j++){
            auto item=new QTableWidgetItem(list.at(i).at(j));

            tableWidget->setItem(i,j,item);
        }
    }
    tableWidget->show();
}
void MainWindow::parseXml(TiXmlNode *parent, QTreeWidgetItem *itemParent,TiXmlNode* objectParent){
    TiXmlElement* e=parent->ToElement();
    if(e!=nullptr){
        for(TiXmlAttribute*attr=e->FirstAttribute();attr!=nullptr;attr=attr->Next()){
            auto item=new QTreeWidgetItem(itemParent);
            item->setText(0,attr->Name());
            item->setText(1,attr->Value());

//            构建新树
            auto newElem=new TiXmlElement(attr->Name());
            auto newText=new TiXmlText(attr->Value());
            objectParent->LinkEndChild(newElem);
            newElem->LinkEndChild(newText);

        }
    }
    for(auto node=parent->FirstChild();node!=nullptr;node=node->NextSibling()){
        if(node->Type()==TiXmlNode::NodeType::TINYXML_TEXT){
            auto newText=new TiXmlText(node->Value());
            objectParent->LinkEndChild(newText);
            itemParent->setText(1,node->Value());
        }else {
            auto item=new QTreeWidgetItem(itemParent);
            item->setText(0,node->Value());

            auto elem=new TiXmlElement(node->Value());
            objectParent->LinkEndChild(elem);
            parseXml(node,item,elem);
        }
    }
}
void MainWindow::parseToForm(TiXmlNode *parent){
    TiXmlHandle handle(parent);/*
    if(parent->FirstChild()!=nullptr && parent->FirstChild()-> Type()==TiXmlNode::TINYXML_TEXT){
        qDebug()<<header<<parent->Value();
        if(header.indexOf(QRegExp(parent->Value()))<0){
            header.append(parent->Value());
        }
    }*/
    bool add=false;
    if(handle.FirstChild().FirstChild().ToNode()!=nullptr && handle.FirstChild().FirstChild().ToNode()->Type()==TiXmlNode::TINYXML_TEXT){

        add=true;
    }
    QStringList l;
    for(auto node=parent->FirstChild();node!=nullptr;node=node->NextSibling()){
        if(add){
//            qDebug()<<node->Type()<<node->Value();
            parseToForm(node,l);
//            l<<node->Value();

        }else {
            parseToForm(node);
        }
    }
    if(add){
        list.append(l);
//        qDebug()<<l;
    }
}
void MainWindow::parseToForm(TiXmlNode *parent, QStringList &l){
//    l<<parent->Value();
    auto node=parent->FirstChild();
    if(node!=nullptr){
        l<<node->Value();
    }
    //表头
    if(header.indexOf(QRegExp(parent->Value()))<0){
        header.append(parent->Value());
    }
}
void MainWindow::exportToTxt(QString filepath){
    QFile file(filepath);
    bool ok=file.open(QIODevice::ReadWrite|QIODevice::Text);
    if(!ok){
        QMessageBox::information(0,"info","文件a.txt打开失败");
    }
    QTextStream out(&file);
    for(int i=0;i<header.size();i++){
        out<<header.at(i)<<"\t";
    }
    out<<endl;
    for(int i=0;i<list.size();i++){
        for(int j=0;j<list.at(i).size();j++){
            out<<list.at(i).at(j)<<"\t";
        }
        out<<endl;
    }
    file.close();
}
void MainWindow::exportToExcel(QString filepath){
    QXlsx::Document xlsx;
    for(int i=0;i<header.size();i++){
        xlsx.write(1,i+1,header.at(i));
    }
    for(int i=0;i<list.size();i++){
        for(int j=0;j<list.at(i).size();j++){
            xlsx.write(i+2,j+1,list.at(i).at(j));
        }
    }
    xlsx.saveAs(filepath);
}

void MainWindow::on_actionTxt_triggered()
{
    QString filePath= QFileDialog::getSaveFileName(0,tr("导出为txt文件"),"",tr("txt文件(*.txt)"));
    if(!filePath.isEmpty()){
        //导出为txt
        exportToTxt(filePath);
        QMessageBox::information(0,tr("info"),tr("导出文件")+filePath+tr("成功"));
    }

}

void MainWindow::on_actionExcel_triggered()
{
    QString filePath= QFileDialog::getSaveFileName(0,tr("导出为excel文件"),"",tr("excel文件(*.xlsx)"));
    if(!filePath.isEmpty()){
        //    导出为excel
            exportToExcel(filePath);
        QMessageBox::information(0,tr("info"),tr("导出文件")+filePath+tr("成功"));
    }

}
