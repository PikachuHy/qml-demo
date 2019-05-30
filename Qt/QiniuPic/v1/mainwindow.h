#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class SystemTray;
class Setting;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    SystemTray* m_tray;
    Setting* m_setting;
};

#endif // MAINWINDOW_H
