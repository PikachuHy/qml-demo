#pragma once
#include <qobject.h>
class QiniuUploadManager :
	public QObject
{
public:
	QiniuUploadManager();
	~QiniuUploadManager();
	void upload(QString filepath);
	void uploadImage(QImage image);
	void uploadUrlList(QList<QUrl> urlList);
private:
	QString calCopyText(QString url);
};

