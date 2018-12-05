/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

/*
    treemodel.cpp

    Provides a simple tree model to show how to create and use hierarchical
    models.
*/

#include "treeitem.h"
#include "treemodel.h"

#include <QStringList>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QtConcurrent>

//! [0]
TreeModel::TreeModel(const QString&, QObject *parent)
    : QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    rootData << "Name" << "Size";
    rootItem = new TreeItem(rootData);
    connect(this, &TreeModel::addItem, this, &TreeModel::on_addItem, Qt::ConnectionType::QueuedConnection);
//    connect(this, &TreeModel::addItem, this, &TreeModel::on_addItem, Qt::ConnectionType::DirectConnection);
    setupModelData();
}
//! [0]

//! [1]
TreeModel::~TreeModel()
{
    delete rootItem;
}
//! [1]

//! [2]
int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

void TreeModel::add(TreeItem *item, TreeItem *parentItem)
{
    if (multhread) {
        addItem(item, parentItem);
    } else {
        on_addItem(item, parentItem);
    }
}

void TreeModel::on_addItem(TreeItem *item, TreeItem *parentItem)
{
    qDebug()<<"add item"<<item<<parentItem<<item->data(0);
//    lock.lockForWrite();
    QModelIndex parentIndex;
    if (!parentItem) {
        parentIndex = QModelIndex();
    } else {
        parentIndex = createIndex(parentItem->row(), 0, parentItem);
    }
    beginInsertRows(parentIndex, parentItem->childCount(), parentItem->childCount() + 1);
    qDebug()<<parentIndex<<parentIndex.data();
    parentItem->appendChild(item);
    endInsertRows();
//    lock.unlock();
}

//! [2]

//! [3]
QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    lock.lockForRead();
    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    QVariant result = item->data(index.column());
    lock.unlock();
    return result;
}
//! [3]

//! [4]
Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index);
}
//! [4]

//! [5]
QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    lock.lockForRead();
    QVariant result = QVariant();
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole){
        result = rootItem->data(section);
    }
    lock.unlock();
    return QVariant();
}
//! [5]

//! [6]
QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent)
            const
{
    QModelIndex result = QModelIndex();
    lock.lockForRead();
    if (!hasIndex(row, column, parent)) {
        lock.unlock();
        return result;
    }

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem) {
        result = createIndex(row, column, childItem);
    }
    lock.unlock();
    return result;
}
//! [6]

//! [7]
QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parentItem();

    if (parentItem == rootItem || !parentItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}
//! [7]

//! [8]
int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}
//! [8]

void traversal(QString parentPath, TreeItem* parentItem, TreeModel* model);

void handleFile(QString filename, TreeItem* parentItem, TreeModel* model) {
    QFileInfo fileInfo(filename);
    if (fileInfo.isDir()) {
        QList<QVariant> list;
        list << fileInfo.fileName() << "";
        TreeItem* item = new TreeItem(list , parentItem);
        model->add(item, parentItem);
        return traversal(filename, item, model);
    } else {
        QList<QVariant> list;
        list << fileInfo.fileName() << fileInfo.size();
        TreeItem* item = new TreeItem(list, parentItem);
        model->add(item, parentItem);
    }
}
void traversal(QString parentPath, TreeItem* parentItem, TreeModel* model)
{
    QDir dir(parentPath);
    auto files = dir.entryList(QDir::NoDotAndDotDot | QDir::AllEntries, QDir::DirsFirst);
    for(auto file: files) {
        QString filename = QString("%1/%2").arg(parentPath).arg(file);
        if(QFileInfo(filename).isSymLink()) continue;
        handleFile(filename, parentItem, model);
    }
}
void TreeModel::setupModelData()
{
    QString path = "/home/pikachu/Documents";
    QFileInfo fileInfo(path);
    QList<QVariant> list;
    list << fileInfo.fileName() << "";
    TreeItem* item = new TreeItem(list , rootItem);
    on_addItem(item, rootItem);
    QtConcurrent::run(traversal, path, item, this);
//    traversal(path, item, this);
}

