#include "mainwindow.h"
#include "systemtray.h"
#include "setting.h"
#include "ui_mainwindow.h"
#include <QActionGroup>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 程序配置
    m_setting = new Setting(this);
    // 系统托盘
    m_tray = new SystemTray(this);
    m_tray->setContextMenu(ui->menuTray);
    // 不显示MenuBar
    ui->menuBar->hide();
    // 显示主要使用QML
    setCentralWidget(ui->quickWidget);
    ui->quickWidget->setSource(QUrl("file:///C:/Users/pikachu/Documents/QiniuPic/qml/Demo.qml"));
    // 复制链接时，只能选择一种类型进行复制
    QActionGroup* group = new QActionGroup(this);
    group->addAction(ui->actionURL);
    group->addAction(ui->actionHTML);
    group->addAction(ui->actionMarkDown);

    // 信号槽
    connect(ui->actionExit, &QAction::triggered, qApp, &QApplication::exit);

    // 读取GUI设置
    setGeometry(m_setting->getMainWindowGeometry());
    if (m_setting->isMainWindowFullScreen()) {
        showFullScreen();
    } else if (m_setting->isMainWindowMaximized()) {
        showMaximized();
    }
    else {
        show();
    }
}

MainWindow::~MainWindow()
{
    // 保存GUI设置
    m_setting->setMainWindowFullScreen(isFullScreen());
    m_setting->setMainWindowMaximized(isMaximized());
    if (isFullScreen() || isMaximized()) {
        // 好像啥也不用做
    }else {
        m_setting->setMainWindowGeometry(geometry());
    }

    // 释放资源
    delete ui;
}
