#include "settingdialog.h"
#include "setting.h"
#include "ui_settingdialog.h"
#include <QtWidgets>
SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
    m_setting = new Setting();
    ui->checkBoxKeyboardAudio->setChecked(m_setting->keyboardAudio());
    ui->pushButtonCorrectCharColor->setColor(m_setting->correctCharColor());
    ui->pushButtonWrongCharColor->setColor(m_setting->wrongCharColor());
    ui->pushButtonUntypedCharColor->setColor(m_setting->untypedCharColor());
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_pushButtonCorrectCharColor_clicked()
{
    auto color = QColorDialog::getColor(
                m_setting->correctCharColor(),
                this,
                tr("Select Correct Char Color")
                );
    if (color.isValid()) {
        m_setting->setCorrectCharColor(color);
    }
    updateColorButton();
}

void SettingDialog::on_pushButtonWrongCharColor_clicked()
{
    auto color = QColorDialog::getColor(
                m_setting->wrongCharColor(),
                this,
                tr("Select Wrong Char Color")
                );
    if (color.isValid()) {
        m_setting->setWrongCharColor(color);
    }
    updateColorButton();
}

void SettingDialog::on_pushButtonUntypedCharColor_clicked()
{
    auto color = QColorDialog::getColor(
                m_setting->untypedCharColor(),
                this,
                tr("Select Untyped Char Color")
                );
    if (color.isValid()) {
        m_setting->setUntypedCharColor(color);
    }
    updateColorButton();
}

void SettingDialog::on_pushButtonRestoreDefaultSetting_clicked()
{
    m_setting->setKeyboardAudio(true);
    m_setting->setCorrectCharColor(QColor(Qt::gray));
    m_setting->setWrongCharColor(QColor(Qt::red));
    m_setting->setUntypedCharColor(QColor(Qt::black));
    updateColorButton();
}

void SettingDialog::updateColorButton()
{
    ui->pushButtonCorrectCharColor->setColor(m_setting->correctCharColor());
    ui->pushButtonWrongCharColor->setColor(m_setting->wrongCharColor());
    ui->pushButtonUntypedCharColor->setColor(m_setting->untypedCharColor());
}

void SettingDialog::on_checkBoxKeyboardAudio_stateChanged(int state)
{
    if (state == Qt::Unchecked) {
        m_setting->setKeyboardAudio(false);
    }
    if (state == Qt::Checked) {
        m_setting->setKeyboardAudio(true);
    }
}
