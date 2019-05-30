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
	QStringList getUploadImageUrlList();
	bool isAutoUploadScreenshot();
	bool isAutoUploadImageFile();
	bool copyLinkTypeIsURL();
	bool copyLinkTypeIsHTML();
	bool copyLinkTypeIsMarkDown();
signals:
	void newUrl(QString url);
public slots:
    void setMainWindowSize(QSize size);
    void setMainWindowGeometry(QRect rect);
    void setMainWindowFullScreen(bool flag);
    void setMainWindowMaximized(bool flag);
	void addUploadImageUrl(QString url);
	void setAutoUploadScreenshot(bool flag);
	void setAutoUploadImageFile(bool flag);
	void setCopyLinkTypeIsURL();
	void setCopyLinkTypeIsHTML();
	void setCopyLinkTypeIsMarkDown();
private:
    QSettings* m_settings;
private:
	int getCopyLinkType();
};

#endif // SETTING_H
