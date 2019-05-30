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
	// 使用QLabel显示图片
	QLabel label(&viewer);
	label.setPixmap(pixmap);
	QVBoxLayout layout;
	layout.addWidget(&label);
	viewer.setLayout(&layout);

	// 显示在屏幕中央

	//获取可用桌面大小
	QList<QScreen*> screenList = QApplication::screens();
	if (screenList.isEmpty()) {
		qCritical() << "no screen to show widget";
		return;
	}
	// 目前只考虑一个屏幕的情况
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
	// 设置标题
	setWindowTitle(tr("View Image"));
	// 去掉问号，只保留关闭
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

}


ImageViewer::~ImageViewer()
{
}
