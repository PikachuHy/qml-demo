#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class SettingDialog;
}
class Setting;
class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = 0);
    ~SettingDialog();

private slots:
    void on_pushButtonCorrectCharColor_clicked();

    void on_pushButtonWrongCharColor_clicked();

    void on_pushButtonUntypedCharColor_clicked();

    void on_pushButtonRestoreDefaultSetting_clicked();

    void on_checkBoxKeyboardAudio_stateChanged(int state);

private:
    void updateColorButton();
private:
    Ui::SettingDialog *ui;
    Setting *m_setting;
};

#endif // SETTINGDIALOG_H
