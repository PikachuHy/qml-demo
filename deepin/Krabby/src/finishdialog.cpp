#include "finishdialog.h"
#include "ui_finishdialog.h"

FinishDialog::FinishDialog(int score, QString time, int words, int speed, int accuracy, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FinishDialog)
{
    ui->setupUi(this);
    ui->labelScore->setText(tr("%1 w/m").arg(score));
    ui->labelTime->setText(time);
    ui->labelWords->setText(tr("%1 w").arg(words));
    ui->labelSpeed->setText(tr("%1 w/m").arg(speed));
    ui->labelAccuracy->setText(tr("%1 %").arg(accuracy));
}

FinishDialog::~FinishDialog()
{
    delete ui;
}
