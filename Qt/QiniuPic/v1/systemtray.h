#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QObject>
#include <QSystemTrayIcon>
class SystemTray :public QSystemTrayIcon
{
public:
    SystemTray(QObject *parent = nullptr);
};

#endif // SYSTEMTRAY_H
