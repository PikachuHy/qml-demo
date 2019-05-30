#include "stdafx.h"
#include "QiniuPicApplication.h"
#include "Setting.h"
QiniuPicApplication::QiniuPicApplication(int & argc, char ** argv)
	:QApplication(argc, argv)
{
	setOrganizationName("PikachuHy");
	setOrganizationDomain("pikachu.net.cn");
	setApplicationName("QiniuPic");
	m_setting = new Setting(this);
}


QiniuPicApplication::~QiniuPicApplication()
{
}

Setting* QiniuPicApplication::setting()
{
	return m_setting;
}
