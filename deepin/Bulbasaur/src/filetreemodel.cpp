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

#include "filetreemodel.h"
#include "fileitem.h"
#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <QFileIconProvider>
#ifdef Q_OS_LINUX
#include <fcntl.h>
#include <sys/stat.h>
#endif
FileTreeModel::FileTreeModel(QObject *parent)
    : QStandardItemModel(parent)
{
    header << tr("Name") << tr("Size") << tr("Allocated")
           << tr("Files") << tr("Folders") << tr("% of Parent")
           << tr("Last Modified") << tr("Owner");
    setHorizontalHeaderLabels(header);
    QFileIconProvider provider;
    folderIcon = provider.icon(QFileIconProvider::Folder);
    fileIcon = provider.icon(QFileIconProvider::File);
}

void FileTreeModel::updateNode(FileNode node)
{
    auto item = map[node.filepath];
    if(!item) return;
    FileItem* iter = item;
    auto master = static_cast<FileItemMaster*>(iter);
    master->node = node;
    master->setData(node.filename, Qt::DisplayRole);
    iter = master->next;
    quint64 oldsize = iter->data(Qt::UserRole).toULongLong();
    quint64 newsize = node.size;
    if (newsize == oldsize) return;
    iter->setData(node.getSize(), Qt::DisplayRole);
    iter->setData(node.size, Qt::UserRole);
    iter = iter->next;

    if (node.type == FileNode::DIR) {
        iter = iter->next;
        iter->setData(node.files, Qt::DisplayRole);

        iter = iter->next;
        iter->setData(node.folders, Qt::DisplayRole);

    }

    iter = iter->next;

    iter = iter->next;
    iter->setData(node.lastModified, Qt::DisplayRole);

    iter = iter->next;
    iter->setData(node.owner, Qt::DisplayRole);


    if (item->parent()) {
        auto master = static_cast<FileItemMaster *>(item->parent());
        auto newNode = master->node;
        newNode.size = newNode.size - oldsize + newsize;
        updateNode(newNode);
        for(int i = 0; i < item->rowCount(); i++) {
            auto child = static_cast<FileItemMaster *>(item->child(i));
            updatePercent(child->node);
        }
    } else {

    }
}

void FileTreeModel::clear()
{
    while(rowCount()!=0) {
        removeRow(0);
    }
    map.clear();
}

void FileTreeModel::addNode(FileNode node) {
    auto row = buildRow(node);
    auto item = parentPath(node.filepath);
    if (item) {
        item->appendRow(row);
    } else {
        appendRow(row);

    }
    map[node.filepath] = static_cast<FileItem *>(row[0]);
    if (item) {
        for(int i = 0; i < item->rowCount(); i++) {
            auto child = static_cast<FileItemMaster *>(item->child(i));
            updatePercent(child->node);
        }
    }
}

QList<QStandardItem *> FileTreeModel::buildRow(FileNode& node) {
    QList<QStandardItem*> row;
    auto nameItem = new FileItemMaster(node.type == FileNode::DIR ? folderIcon : fileIcon, node.filename);
    nameItem->node = node;
    auto sizeItem = new FileItemSlave(node.getSize());
    sizeItem->setData(node.size, Qt::UserRole);
    FileItem* filesItem = new FileItem();
    FileItem* allocatedItem = new FileItem();
    FileItem* foldersItem = new FileItem();
    if (node.type == FileNode::DIR) {
        filesItem = new FileItemSlave(node.files);
        foldersItem = new FileItemSlave(node.folders);
    } else {
#ifdef Q_OS_LINUX
        struct stat    buf;
        stat(node.filepath.toStdString().c_str(), &buf);
        quint64 allocatedSize = buf.st_blksize * buf.st_blocks / 8 ;
        allocatedItem->setData(QString("%1 KiB").arg(allocatedSize / 1024), Qt::DisplayRole);
        allocatedItem->setData(allocatedSize, Qt::UserRole);
#endif
    }
    row << nameItem                              // Name
        << sizeItem                              // Size
        << allocatedItem                         // Allocated
        << filesItem                             // Files
        << foldersItem                           // Folders
        << new FileItem()                        // % of Parent
        << new FileItemSlave(node.lastModified)  // Last Modified
        << new FileItemSlave(node.owner)         // Owner
            ;
    for(int i = 0; i < row.size() - 1; i++) {
        (static_cast<FileItem*>(row[i]))->next = static_cast<FileItem*>(row[i+1]);
    }
    return row;
}

FileItem *FileTreeModel::parentPath(QString path) {
    QFileInfo fileInfo(path);
    auto parentPath = fileInfo.absoluteDir().absolutePath();
    auto item = map[parentPath];
    return item;
}

void FileTreeModel::updatePercent(FileNode &node)
{
    auto item = map[node.filepath];
    if(!item) return;
    if (item->parent()) {
        auto master = static_cast<FileItemMaster *>(item->parent());
        // find percent item
        auto percentItem = item->next->next->next->next->next;
        auto parentSize = master->node.size;
        if (parentSize != 0) {
            auto percent = 100.0 * node.size / parentSize;
            percentItem->setData(QString("%1 %").arg(QString::number(percent, 'f', 2)), Qt::DisplayRole);
        }
    }
}
