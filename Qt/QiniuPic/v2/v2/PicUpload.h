#pragma once
#include <qwidget.h>
class UploadArea;
class QListWidget;
class PicUpload :
	public QWidget
{
public:
	PicUpload(QWidget* parent = nullptr);
	~PicUpload();
private:
	UploadArea* m_uploadArea;
	QListWidget* m_recentList;
};

