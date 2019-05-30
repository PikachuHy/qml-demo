#include "stdafx.h"
#include "MainWindow.h"
#include "QiniuPicApplication.h"

int main(int argc, char *argv[])
{
	QiniuPicApplication a(argc, argv);
	MainWindow w;
	return a.exec();
}
