/* -*- Mode: C++; indent-tabs-mode: nil; tab-width: 4 -*-
 * -*- coding: utf-8 -*-
 *
 * Copyright (C) 2018 ~ 2018 PikachuHy
 *
 *
 * Author:     PikachuHy <pikachuhy@163.com>
 * Maintainer: PikachuHy <pikachuhy@163.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "mainwindow.h"
#include "filetreemodel.h"
#include "filetreeview.h"
#include <QDir>
#include <QDebug>
#include <QThreadPool>
#include <QtConcurrent>
#include <QFileSystemModel>
#include <QHeaderView>
#ifdef Q_OS_LINUX
#include "toolbar.h"
#include <DTitlebar>
DWIDGET_USE_NAMESPACE
#endif
FileNode traversal(QString parentPath, FileTreeModel* model);

FileNode handleFile(QString filename, FileTreeModel* model) {
    FileNode fileNode(filename);
    QFileInfo fileInfo(filename);
    if (fileInfo.isDir()) {
        return traversal(filename, model);
    } else {
        fileNode.size = fileInfo.size();
        fileNode.type = FileNode::FILE;
//        qDebug() << filename << formatFileSize(fileInfo.size());
        model->addNode(fileNode);
        return fileNode;
    }
}
FileNode traversal(QString parentPath, FileTreeModel* model)
{
    QDir dir(parentPath);
    auto files = dir.entryList(QDir::NoDotAndDotDot | QDir::AllEntries, QDir::DirsFirst);
    FileNode fileNode(parentPath);
    fileNode.type = FileNode::DIR;
    model->addNode(fileNode);
    for(auto file: files) {
        QString filename = QString("%1/%2").arg(parentPath).arg(file);
        if(QFileInfo(filename).isSymLink()) continue;
        auto node = handleFile(filename, model);
        fileNode.size += node.size;
        if (node.type == FileNode::DIR) {
            fileNode.folders ++;
        } else {
            fileNode.files ++;
        }
        model->updateNode(fileNode);
    }
//    qDebug () << parentPath << formatFileSize(total);
    return fileNode;
}

MainWindow::MainWindow(QWidget *parent)
    : MyMainWindow(parent)
{
    setMinimumSize(QSize(1200, 800));
#ifdef Q_OS_LINUX
    auto toolBar = new ToolBar();
    titlebar()->setCustomWidget(toolBar, Qt::AlignVCenter, false);
#endif
    QString homePath = QDir::homePath();
    model = new FileTreeModel(this);
    view = new FileTreeView(this);
    view->setModel(model);
    setCentralWidget(view);
    view->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    view->header()->setSectionResizeMode(2, QHeaderView::Stretch);
    view->header()->setSectionResizeMode(3, QHeaderView::Stretch);
    view->header()->setSectionResizeMode(4, QHeaderView::Stretch);
    view->header()->setSectionResizeMode(5, QHeaderView::Stretch);
    view->header()->resizeSection(6, 120);
    future = QtConcurrent::run(traversal, homePath, model);
#ifdef Q_OS_LINUX
    connect(toolBar, &ToolBar::newPath, [this](QString path){
        future.cancel();
        model->clear();
        future = QtConcurrent::run(traversal, path, model);
    });
#endif
}

MainWindow::~MainWindow()
{

}
