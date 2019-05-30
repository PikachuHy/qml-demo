#ifndef SETTING_H
#define SETTING_H
#include <QtCore>
class QSettings;
class Setting : public QObject
{
    Q_OBJECT
public:
    explicit Setting(QObject *parent = nullptr);
    QSize getMainWindowSize();
    QRect getMainWindowGeometry();
    bool isMainWindowFullScreen();
    bool isMainWindowMaximized();
signals:

public slots:
    void setMainWindowSize(QSize size);
    void setMainWindowGeometry(QRect rect);
    void setMainWindowFullScreen(bool flag);
    void setMainWindowMaximized(bool flag);
private:
    QSettings* m_settings;
};

#endif // SETTING_H
