#include "stdafx.h"
#include "ImageViewer.h"


void ImageViewer::showImage(QString filepath)
{
	QPixmap pixmap(filepath);
	if (pixmap.isNull())
	{
		qDebug() << "image is null" << filepath;
		return;
	}
	ImageViewer viewer;
	// ʹ��QLabel��ʾͼƬ
	QLabel label(&viewer);
	label.setPixmap(pixmap);
	QVBoxLayout layout;
	layout.addWidget(&label);
	viewer.setLayout(&layout);

	// ��ʾ����Ļ����

	//��ȡ���������С
	QList<QScreen*> screenList = QApplication::screens();
	if (screenList.isEmpty()) {
		qCritical() << "no screen to show widget";
		return;
	}
	// Ŀǰֻ����һ����Ļ�����
	QSize deskSize = screenList[0]->availableSize();

	int w = pixmap.width();
	int h = pixmap.height();
	int x = (deskSize.width() - w) / 2;
	int y = (deskSize.height() - h) / 2;
	viewer.setGeometry(x, y, w, h);
	viewer.exec();
}

ImageViewer::ImageViewer()
{
	// ���ñ���
	setWindowTitle(tr("View Image"));
	// ȥ���ʺţ�ֻ�����ر�
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

}


ImageViewer::~ImageViewer()
{
}
