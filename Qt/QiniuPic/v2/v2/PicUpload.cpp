#include "stdafx.h"
#include "PicUpload.h"
#include "UploadArea.h"
#include "QiniuUploadManager.h"
#include "QiniuPicApplication.h"
#include "Setting.h"
PicUpload::PicUpload(QWidget* parent) : QWidget(parent)
{
	m_uploadArea = new UploadArea(this);
	auto vBox = new QVBoxLayout();
	vBox->addWidget(m_uploadArea);
	m_recentList = new QListWidget(this);
	
	vBox->addWidget(m_recentList, 1);
	setLayout(vBox);

	// �����ϴ��������¼�
	connect(m_uploadArea, &UploadArea::click, [=]()
	{
		QString filename = QFileDialog::getOpenFileName(this, tr("Choose upload image file"), QDir::homePath(), "image files(*.png *.jpg *.gif *.jpeg *.bmp)");
		if (filename.isEmpty())
		{
			qDebug() << "give up choose image file";
		} else
		{
			QiniuUploadManager manager;
			manager.upload(filename);
		}
	});
	// �����µ�ͼƬ�ϴ�ʱ����ʾ���б���
	auto setting = qApp->setting();
	connect(setting, &Setting::newUrl, [=](QString url)
	{
		m_recentList->addItem(url);
	});
}


PicUpload::~PicUpload()
{
}
