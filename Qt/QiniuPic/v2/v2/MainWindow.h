#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
namespace Ui {
	class MainWindow;
}

class Side;
class SystemTray;
class Setting;
class PicUpload;
class QStackedLayout;
class QiniuSetting;
class MainWindow : public QMainWindow
{
private:
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

private:
	Ui::MainWindow ui;
	Side* m_side;
	SystemTray* m_tray;
	Setting* m_setting;
	QStackedLayout * m_stack;
	PicUpload* m_picUpload;
	QiniuSetting* m_qiniuSetting;
private slots:
	void onClipboardDataChange();
};
