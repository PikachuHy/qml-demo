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

#include "toolbar.h"
#include <QHBoxLayout>
#include <QLabel>
#include <DSearchEdit>
#include <QToolButton>
#include <QFileIconProvider>
#include <QPushButton>
#include <QFileDialog>
#include <QDebug>
DWIDGET_USE_NAMESPACE
ToolBar::ToolBar(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    QLabel *iconLabel = new QLabel;
    QImage iconImage(":/icon/icon.png");
    iconImage = iconImage.scaled(22, 22, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPixmap iconPixmap = QPixmap::fromImage(iconImage);
    iconLabel->setPixmap(iconPixmap);
    auto searchEdit = new DSearchEdit();
    searchEdit->setPlaceHolder(tr("search"));

    auto chooseFolder = new DImageButton(":/icon/ios-folder-outline.svg",
                                         ":/icon/ios-folder-open-outline.svg",
                                         ":/icon/ios-folder-open.svg");
    connect(chooseFolder, &DImageButton::clicked, [this](){
        auto path = QFileDialog::getExistingDirectory(nullptr, tr("Choose a folder"), QDir::homePath());
        if (!path.isEmpty()) {
            qDebug() << "new path" << path;
            emit newPath(path);
        }
    });

    layout->setMargin(0);
    layout->setSpacing(28);

    layout->addSpacing(5);
    layout->addWidget(iconLabel);
    layout->addWidget(chooseFolder);
    layout->addStretch();
    layout->addWidget(searchEdit);
    layout->addStretch();

    setFocusPolicy(Qt::ClickFocus);
    setLayout(layout);
}
