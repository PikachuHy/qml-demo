#include "stdafx.h"
#include "Setting.h"
#include <QtWidgets>
#include <QSettings>
// 配置文件中的KEY
static QString MAINWINDOW_SIZE = "MainWindow/size";
static QString MAINWINDOW_GEOMETRY = "MainWindow/geometry";
static QString MAINWINDOW_FULLSCREEN = "MainWindow/fullscreen";
static QString MAINWINDOW_MAXIMIZED = "MainWindow/maximized";
static QString DATA_UPLOAD_IMAGE_URL_LIST = "data/upload_image_url_list";
static QString CONFIG_AUTO_UPLOAD_SCREENSHOT = "config/auto_upload/screenshot";
static QString CONFIG_AUTO_UPLOAD_IMAGE_FILE = "config/auto_upload/image_file";
static QString CONFIG_COPY_LINK_TYPE = "config/link/type";
// 复制链接类型
static int COPY_LINK_TYPE_URL = 1;
static int COPY_LINK_TYPE_HTML = 2;
static int COPY_LINK_TYPE_MarkDown = 3;
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

QStringList Setting::getUploadImageUrlList()
{
	return m_settings->value(DATA_UPLOAD_IMAGE_URL_LIST).toStringList();
}

bool Setting::isAutoUploadScreenshot()
{
	return m_settings->value(CONFIG_AUTO_UPLOAD_SCREENSHOT).toBool();
}

bool Setting::isAutoUploadImageFile()
{
	return m_settings->value(CONFIG_AUTO_UPLOAD_IMAGE_FILE).toBool();
}

bool Setting::copyLinkTypeIsURL()
{
	return getCopyLinkType() == COPY_LINK_TYPE_URL;
}

bool Setting::copyLinkTypeIsHTML()
{
	return getCopyLinkType() == COPY_LINK_TYPE_HTML;
}

bool Setting::copyLinkTypeIsMarkDown()
{
	auto type = getCopyLinkType();
	if (type == 0)
	{
		// 默认是MarkDown
		setCopyLinkTypeIsMarkDown();
	}
	return getCopyLinkType() == COPY_LINK_TYPE_MarkDown;
}

int Setting::getCopyLinkType()
{
	return m_settings->value(CONFIG_COPY_LINK_TYPE).toInt();
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

void Setting::addUploadImageUrl(QString url)
{
	auto urlList = getUploadImageUrlList();
	urlList.append(url);

	m_settings->setValue(DATA_UPLOAD_IMAGE_URL_LIST, urlList);
	m_settings->sync();
	emit newUrl(url);
}

void Setting::setAutoUploadScreenshot(bool flag)
{
	m_settings->setValue(CONFIG_AUTO_UPLOAD_SCREENSHOT, flag);
	m_settings->sync();
}

void Setting::setAutoUploadImageFile(bool flag)
{
	m_settings->setValue(CONFIG_AUTO_UPLOAD_IMAGE_FILE, flag);
	m_settings->sync();
}

void Setting::setCopyLinkTypeIsURL()
{
	m_settings->setValue(CONFIG_COPY_LINK_TYPE, COPY_LINK_TYPE_URL);
	m_settings->sync();
}

void Setting::setCopyLinkTypeIsHTML()
{
	m_settings->setValue(CONFIG_COPY_LINK_TYPE, COPY_LINK_TYPE_HTML);
	m_settings->sync();
}

void Setting::setCopyLinkTypeIsMarkDown()
{
	m_settings->setValue(CONFIG_COPY_LINK_TYPE, COPY_LINK_TYPE_MarkDown);
	m_settings->sync();
}

