#include "stdafx.h"
#include "Notify.h"
#include "ImageViewer.h"
#include "wintoastlib/wintoastlib.h"
using namespace WinToastLib;
class WinToastHandlerExample : public IWinToastHandler {
public:
	WinToastHandlerExample(QString filepath, QString url)
	{
		m_filepath = filepath;
		m_url = url;
	}
	// Public interfaces
	void toastActivated() const override
	{
		qDebug() << "toast activated";
	}
	void toastDismissed(WinToastDismissalReason state) const override
	{
		qDebug() << "toast dismissed" << state;
	}
	void toastFailed() const override
	{
		qDebug() << "toast failed";
	}

	void toastActivated(int actionIndex) const override
	{
		qDebug() << "toast activated" << actionIndex;
		switch(actionIndex)
		{
		case 0:
			{
			qDebug() << "copy url";
			auto clipboard = qApp->clipboard();
			clipboard->setText(m_url);
			}
			break;
		case 1:
			{
			qDebug() << "view image";
			ImageViewer::showImage(m_filepath);
			}
			break;
		default:
			break;
		}
	}
private:
	QString m_filepath;
	QString m_url;
};
Notify::Notify(QObject *parent) : QObject(parent)
{
}


Notify::~Notify()
{
}

void Notify::sendNotify(QString filepath, QString url)
{
	if (!WinToast::isCompatible()) {
		qDebug() << "Error, your system in not supported!" ;
		return;
	}
	auto tmp = qApp->applicationDisplayName().toStdWString();
	WinToast::instance()->setAppName(tmp);
	const auto aumi = WinToast::configureAUMI(L"PikachuHy", L"QiniuPic", L"windows version", L"20190224");
	WinToast::instance()->setAppUserModelId(aumi);
	if (!WinToast::instance()->initialize()) {
		qDebug() << "Error, could not initialize the lib!" ;
	}
	WinToastHandlerExample* handler = new WinToastHandlerExample(filepath, url);
	WinToastTemplate templ = WinToastTemplate(WinToastTemplate::ImageAndText02);
	templ.setTextField(L"文件上传", WinToastTemplate::FirstLine);
	tmp = url.toStdWString();
	templ.setTextField(tmp, WinToastTemplate::SecondLine);
	tmp = filepath.toStdWString();
	templ.setImagePath(tmp);
	templ.addAction(L"Copy URL");
	templ.addAction(L"View Image");
	if (!WinToast::instance()->showToast(templ, handler)) {
		qDebug() << "Error: Could not launch your toast notification!";
	}
}
