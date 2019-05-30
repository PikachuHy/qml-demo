#include "stdafx.h"
#include "MainWindow.h"
#include "Side.h"
#include "PicUpload.h"
#include "SystemTray.h"
#include "Setting.h"
#include "QiniuUploadManager.h"
#include "QiniuSetting.h"
#include "Util.h"
#include "QiniuPicApplication.h"
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	// ��������
	m_setting = qApp->setting();
	// ϵͳ����
	m_tray = new SystemTray(this);
	m_tray->setContextMenu(ui.menuTray);
	// ����ʾMenuBar
	ui.menuBar->hide();
	m_side = new Side(this);
	m_stack = new QStackedLayout(this);
	m_picUpload = new PicUpload(this);
	m_qiniuSetting = new QiniuSetting(this);
	m_stack->addWidget(m_picUpload);
	m_stack->addWidget(m_qiniuSetting);
	m_stack->setCurrentWidget(m_picUpload);
	QHBoxLayout* hBox = new QHBoxLayout();
	hBox->addWidget(m_side);
	QWidget *w = new QWidget(this);
	hBox->addLayout(m_stack, 1);
	w->setLayout(hBox);
	setCentralWidget(w);
	// ��������ʱ��ֻ��ѡ��һ�����ͽ��и���
	QActionGroup* group = new QActionGroup(this);
	group->addAction(ui.actionURL);
	group->addAction(ui.actionHTML);
	group->addAction(ui.actionMarkDown);
	// �������а�仯
	QClipboard *clipboard = QGuiApplication::clipboard();
// ��ȡ�û�������Ϣ
	ui.actionClipboard_Screenshot->setChecked(m_setting->isAutoUploadScreenshot());
	ui.actionCopy_Picture->setChecked(m_setting->isAutoUploadImageFile());
	ui.actionURL->setChecked(m_setting->copyLinkTypeIsURL());
	ui.actionHTML->setChecked(m_setting->copyLinkTypeIsHTML());
	ui.actionMarkDown->setChecked(m_setting->copyLinkTypeIsMarkDown());
	// ��ȡGUI����
	setGeometry(m_setting->getMainWindowGeometry());
	if (m_setting->isMainWindowFullScreen()) {
		showFullScreen();
	}
	else if (m_setting->isMainWindowMaximized()) {
		showMaximized();
	}
	else {
		show();
	}
	// �źŲ�
	connect(ui.actionClipboard_Screenshot, &QAction::triggered,
		m_setting, &Setting::setAutoUploadScreenshot);
	connect(ui.actionCopy_Picture, &QAction::triggered,
		m_setting, &Setting::setAutoUploadImageFile);
	connect(ui.actionURL, &QAction::triggered,
		m_setting, &Setting::setCopyLinkTypeIsURL);
	connect(ui.actionHTML, &QAction::triggered,
		m_setting, &Setting::setCopyLinkTypeIsHTML);
	connect(ui.actionMarkDown, &QAction::triggered,
		m_setting, &Setting::setCopyLinkTypeIsMarkDown);
	connect(ui.actionExit, &QAction::triggered, qApp, &QApplication::exit);
	connect(clipboard, &QClipboard::dataChanged, this, &MainWindow::onClipboardDataChange);
	connect(m_side, &Side::currentItemChange, [=](QString itemName)
	{
		qDebug() << "current item name" << itemName;
		if (itemName == QStringLiteral("ͼƬ�ϴ�"))
		{
			m_stack->setCurrentWidget(m_picUpload);
		}
		if (itemName == QStringLiteral("������"))
		{
			m_stack->setCurrentWidget(m_picUpload);
		}
		if (itemName == QStringLiteral("��ţ����"))
		{
			m_stack->setCurrentWidget(m_qiniuSetting);
		}
	});
}

MainWindow::~MainWindow()
{
	// ����GUI����
	m_setting->setMainWindowFullScreen(isFullScreen());
	m_setting->setMainWindowMaximized(isMaximized());
	if (isFullScreen() || isMaximized()) {
		// ����ɶҲ������
	}
	else {
		m_setting->setMainWindowGeometry(geometry());
	}
}

void MainWindow::onClipboardDataChange()
{
	QClipboard *clipboard = QGuiApplication::clipboard();
	const QMimeData *mimeData = clipboard->mimeData();
	if (m_setting->isAutoUploadScreenshot())
	{
	if (mimeData->hasImage()) {
		QImage image = qvariant_cast<QImage>(mimeData->imageData());
		QiniuUploadManager manager;
		manager.uploadImage(image);
	}
	}
	if (m_setting->isAutoUploadImageFile())
	{
	if (mimeData->hasUrls())
	{
		QiniuUploadManager manager;
		manager.uploadUrlList(mimeData->urls());
	}
	}
}
