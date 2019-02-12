#ifndef SYSTEMTRAYICON_H
#define SYSTEMTRAYICON_H

#include <QSystemTrayIcon>
class QQmlApplicationEngine;
class SystemTrayIcon : public QSystemTrayIcon
{
public:
    SystemTrayIcon(QQmlApplicationEngine* engine);
private slots:
    void onActivated(QSystemTrayIcon::ActivationReason reason);
private:
    QQmlApplicationEngine* m_engine;
};

#endif // SYSTEMTRAYICON_H
