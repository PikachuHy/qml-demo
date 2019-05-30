#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QObject>
#include <QSystemTrayIcon>
class SystemTray :public QSystemTrayIcon
{
public:
    SystemTray(QObject *parent = nullptr);

protected:
    bool event(QEvent* event) override;
};

#endif // SYSTEMTRAY_H
