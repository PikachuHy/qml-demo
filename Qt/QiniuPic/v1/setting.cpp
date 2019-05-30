#include "setting.h"
#include <QtWidgets>
#include <QSettings>
static QString MAINWINDOW_SIZE = "MainWindow/size";
static QString MAINWINDOW_GEOMETRY = "MainWindow/geometry";
static QString MAINWINDOW_FULLSCREEN = "MainWindow/fullscreen";
static QString MAINWINDOW_MAXIMIZED = "MainWindow/maximized";
Setting::Setting(QObject *parent) : QObject(parent)
{
    m_settings = new QSettings(this);
}

QSize Setting::getMainWindowSize()
{
    QSize size = m_settings->value(MAINWINDOW_SIZE).toSize();
    if (size.isEmpty()) {
        return QSize(400, 400);
    }
    return size;
}

QRect Setting::getMainWindowGeometry()
{
    QRect rect = m_settings->value(MAINWINDOW_GEOMETRY).toRect();
    if (rect.isEmpty()) {
        //获取可用桌面大小
        QList<QScreen*> screenList = QApplication::screens();
        if (screenList.isEmpty()) {
            return QRect(0, 0, 400, 400);
        }
        // 目前只考虑一个屏幕的情况
        QSize deskSize = screenList[0]->availableSize();
        int x = (deskSize.width() - 400) / 2;
        int y = (deskSize.height() - 400) / 2;
        return QRect(x, y, 400, 400);
    }
    return rect;
}

bool Setting::isMainWindowFullScreen()
{
    return m_settings->value(MAINWINDOW_FULLSCREEN).toBool();
}

bool Setting::isMainWindowMaximized()
{
    return m_settings->value(MAINWINDOW_MAXIMIZED).toBool();
}

void Setting::setMainWindowSize(QSize size)
{
    m_settings->setValue(MAINWINDOW_SIZE, size);
    m_settings->sync();
}

void Setting::setMainWindowGeometry(QRect rect)
{
    m_settings->setValue(MAINWINDOW_GEOMETRY, rect);
    m_settings->sync();

}

void Setting::setMainWindowFullScreen(bool flag)
{
    m_settings->setValue(MAINWINDOW_FULLSCREEN, flag);
    m_settings->sync();
}

void Setting::setMainWindowMaximized(bool flag)
{
    m_settings->setValue(MAINWINDOW_MAXIMIZED, flag);
    m_settings->sync();
}
