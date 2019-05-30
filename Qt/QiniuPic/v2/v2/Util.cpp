#include "stdafx.h"
#include "Util.h"
using namespace Util;

QString Util::getQrcIconPath(QString name, QString color, int size)
{
	return QString(":/icon/%1_%2_%3x%3.png")
	.arg(name)
	.arg(color)
	.arg(size);
}

bool Util::isPicture(QString filepath)
{
	QMimeDatabase db;
	QMimeType mime = db.mimeTypeForFile(filepath);
	qDebug() << "mime: " << filepath << mime.name();
	return mime.name().startsWith("image/");
}

bool Util::isPointInRect(QPoint point, QRect rect)
{
	return point.x() > rect.x()
		&& point.y() > rect.y()
		&& point.x() < rect.x() + rect.width()
		&& point.y() < rect.y() + rect.height();
}
