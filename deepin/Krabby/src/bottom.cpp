#include "bottom.h"
#include "ui_bottom.h"

Bottom::Bottom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Bottom)
{
    ui->setupUi(this);
    setFixedHeight(50);

    // Reset
    updateTime("00:00:00");
    updateSpeed(0);
    updateAccuracy(100);
    updateProgress(0);
}

Bottom::~Bottom()
{
    delete ui;
}

void Bottom::updateTime(QString time)
{
    ui->labelTime->setText(time);
}

void Bottom::updateSpeed(int speed)
{
    ui->labelSpeed->setText(tr("%1 w/m").arg(speed));
}

void Bottom::updateProgress(int progress)
{
    ui->labelProgress->setText(tr("%1 %").arg(progress));
}

void Bottom::updateAccuracy(int accuracy)
{
    ui->labelAccuracy->setText(tr("%1 %").arg(accuracy));
}
