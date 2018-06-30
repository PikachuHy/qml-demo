#include "SystemTrayIcon.h"
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlProperty>
#include <QDebug>
SystemTrayIcon::SystemTrayIcon(QQmlApplicationEngine *engine):m_engine(engine)
{
    this->setIcon(QIcon(":/icon/icon.png"));
    connect(this,&QSystemTrayIcon::activated,this,&SystemTrayIcon::onActivated);
}

void SystemTrayIcon::onActivated(QSystemTrayIcon::ActivationReason reason)
{
    Q_UNUSED(reason)
    qDebug()<<"void SystemTrayIcon::onActivated(QSystemTrayIcon::ActivationReason reason)";
    auto window = m_engine->rootObjects().first();
    window->setProperty("visible",true);
}
