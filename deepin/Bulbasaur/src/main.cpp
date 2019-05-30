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
#ifdef Q_OS_LINUX
#include <DApplication>
#include <DLog>
#include <DWidgetUtil>
DWIDGET_USE_NAMESPACE
DCORE_USE_NAMESPACE
using Application = DApplication;
#else
#include <QApplication>
using Application = QApplication;
#endif
QString getQssContent(const QString &filePath)
{
    QFile file(filePath);
    QString qss;

    if (file.open(QIODevice::ReadOnly)) {
        qss = file.readAll();
    }

    return qss;
}
int main(int argc, char *argv[])
{
#ifdef Q_OS_LINUX
    DLogManager::registerFileAppender();
    DLogManager::registerConsoleAppender();
    Application::loadDXcbPlugin();
    const char *descriptionText = QT_TRANSLATE_NOOP("MainWindow", "A disk consumption analyzing tool, which sorts folders according to their physical occupied sizes. ");

    const QString acknowledgementLink = "https://github.com/PikachuHy/bulbasaur";

#endif
    Application app(argc, argv);

    qRegisterMetaType<QVector<int>>();

    Application::setAttribute(Qt::AA_UseHighDpiPixmaps);
#ifdef Q_OS_LINUX
    if (app.setSingleInstance("bulbasaur")) {
        app.loadTranslator();

        Application::setOrganizationName("pikachu");
        Application::setApplicationName("bulbasaur");
        Application::setApplicationVersion(DApplication::buildVersion("1.0"));

        app.setProductIcon(QIcon(":/icon/icon.png"));
        app.setProductName(DApplication::translate("MainWindow", "Bulbasaur"));
        app.setApplicationDescription(DApplication::translate("MainWindow", descriptionText) + "\n");
        app.setApplicationAcknowledgementPage(acknowledgementLink);

        app.setTheme("light");
        Application::setWindowIcon(QIcon(":/icon/icon.png"));
        MainWindow window;

        QObject::connect(&app, &DApplication::newInstanceStarted, &window, &MainWindow::activateWindow);

        Dtk::Widget::moveToCenter(&window);
        window.show();
        window.setStyleSheet(getQssContent(":/qss/style.qss"));

        return Application::exec();
    }
    return 0;
#else
    MainWindow window;
    window.show();
    window.setStyleSheet(getQssContent(":/qss/style.qss"));

    return app.exec();
#endif
}
