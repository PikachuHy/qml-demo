#pragma once
#include <qapplication.h>
#if defined(qApp)
#undef qApp
#endif
#define qApp (static_cast<QiniuPicApplication *>(QCoreApplication::instance()))
class Setting;
class QiniuPicApplication :
	public QApplication
{
public:
	QiniuPicApplication(int & argc, char ** argv);
	~QiniuPicApplication();


	Setting* setting();
private:
	Setting* m_setting;
};

