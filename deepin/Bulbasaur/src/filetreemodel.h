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

#ifndef FILETREEMODEL_H
#define FILETREEMODEL_H

#include <QStandardItemModel>
#include <QFileInfo>
#include <QDateTime>
class FileItem;
struct FileNode
{
    enum Type {FILE, DIR};
    QString filename;
    QString filepath;
    Type type;
    quint64 size = 0;
    int files = 0;
    int folders = 0;
    QString lastModified;
    QString owner;

    FileNode(){}
    FileNode(QString filepath) {
        this->filepath = filepath;
        const QFileInfo fileInfo = QFileInfo(filepath);
        this->filename = fileInfo.fileName();
        this->lastModified = fileInfo.lastModified().toString("yyyy年MM月dd日 ");
        this->owner = fileInfo.owner();
    }
    QString getSize() {
        return formatFileSize(size);
    }

private:
    QString formatFileSize(quint64 size) {
        if (size > 1024 * 0.8) {
            double kb = 1.0 * size / 1024;
            if (kb > 1024 * 0.8) {
                double mb = kb / 1024;
                if (mb > 1024 * 0.8) {
                    double gb = mb / 1024;
                    return QString("%1 GB").arg(QString::number(gb, 'f', 2));
                } else {
                    return QString("%1 MiB").arg(QString::number(mb, 'f', 2));
                }
            } else {
                return QString("%1 KiB").arg(QString::number(kb, 'f', 2));
            }
        } else {
            return QString("%1 bytes").arg(size);
        }
    }
};
class FileTreeModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit FileTreeModel(QObject *parent = nullptr);
    void addNode(FileNode node);
    void updateNode(FileNode node);
    void clear();
private:
    QStringList header;
    QMap<QString, FileItem*> map;
    QIcon folderIcon;
    QIcon fileIcon;
    QList<QStandardItem*> buildRow(FileNode& node);
    FileItem* parentPath(QString path);
    void updatePercent(FileNode& node);
};

#endif // FILETREEMODEL_H
