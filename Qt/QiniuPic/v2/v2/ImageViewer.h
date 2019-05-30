#pragma once
#include <qdialog.h>
class ImageViewer :
	public QDialog
{
public:
	static void showImage(QString filepath);
private:
	ImageViewer();
	~ImageViewer();
};

