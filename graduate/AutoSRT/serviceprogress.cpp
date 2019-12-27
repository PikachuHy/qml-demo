#include "serviceprogress.h"
#include <QtWidgets>
ServiceProgress::ServiceProgress(QWidget *parent) : QDialog(parent)
{
    progressBar = new QProgressBar();
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    tips = new QLabel(tr("Initializing ..."));
    auto layout = new QVBoxLayout(this);
    layout->addWidget(progressBar);
    layout->addWidget(tips);
}

void ServiceProgress::setProgress(int progress) {
    progressBar->setValue(progress);
}

void ServiceProgress::setTips(QString text) {
    tips->setText(text);
}

void ServiceProgress::progressInc() {
    this->progressBar->setValue(this->progressBar->value()+1);
}
