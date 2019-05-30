#include "stdafx.h"
#include "SystemTray.h"
#include "Util.h"
SystemTray::SystemTray(QObject *parent): QSystemTrayIcon (parent)
{
    setIcon(QIcon(":/icon/qiniu_32x32.png"));
	if (isSystemTrayAvailable())
	{
		qDebug() << "system tray available";
	} else
	{
		qDebug() << "system tray unavailable";
	}
	connect(this, &SystemTray::activated, [=](QSystemTrayIcon::ActivationReason reason)
	{
		qDebug() << "activated";
	});
}

bool SystemTray::event(QEvent* event)
{
	qDebug() << event;
	return QSystemTrayIcon::event(event);
}
