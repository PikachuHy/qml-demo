#include "systemtray.h"

SystemTray::SystemTray(QObject *parent): QSystemTrayIcon (parent)
{
    setIcon(QIcon(":/icon/qiniu_32x32.png"));
}
