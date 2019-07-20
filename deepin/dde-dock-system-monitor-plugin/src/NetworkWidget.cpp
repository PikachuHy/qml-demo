//
// Created by pikachu on 7/20/19.
//

#include "NetworkWidget.h"
#include "widget/DoubleIcon.h"
#include "widget/DoubleLabel.h"
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
void getNetworkBandWidth(
        unsigned long long int &receiveBytes,
        unsigned long long int &sendBytes) {
    char *buf;
    static int bufsize;
    FILE *devfd;

    buf = (char *) calloc(255, 1);
    bufsize = 255;
    devfd = fopen("/proc/net/dev", "r");

    // Ignore the first two lines of the file.
    fgets(buf, bufsize, devfd);
    fgets(buf, bufsize, devfd);

    receiveBytes = 0;
    sendBytes = 0;

    while (fgets(buf, bufsize, devfd)) {
        unsigned long long int rBytes, sBytes;
        char *line = strdup(buf);

        char *dev;
        dev = strtok(line, ":");

        // Filter lo (virtual network device).
        if (QString::fromStdString(dev).trimmed() != "lo") {
            sscanf(buf + strlen(dev) + 2, "%llu %*d %*d %*d %*d %*d %*d %*d %llu", &rBytes, &sBytes);

            receiveBytes += rBytes;
            sendBytes += sBytes;
        }

        free(line);
    }

    fclose(devfd);
    free(buf);
}

NetworkWidget::NetworkWidget(QWidget *parent) : QWidget(parent) {
    setStyleSheet("QLabel {font-size: 8px;}");
    setFixedWidth(48);
    auto uploadIcon = new DoubleIcon(":/right_top.svg");
    auto downloadIcon = new DoubleIcon(":/left_down.svg");
    m_upload = new DoubleLabel("0KiB");
    m_download = new DoubleLabel("0KiB");
    auto hbox1 = new QHBoxLayout();
    hbox1->setContentsMargins(0,0,0,0);
    hbox1->setSpacing(0);
    auto hbox2 = new QHBoxLayout();
    hbox2->setContentsMargins(0,0,0,0);
    hbox2->setSpacing(0);
    hbox1->addWidget(uploadIcon, 0, Qt::AlignVCenter | Qt::AlignLeft);
    hbox1->addWidget(m_upload, 0, Qt::AlignVCenter | Qt::AlignRight);
    hbox2->addWidget(downloadIcon, 0, Qt::AlignVCenter | Qt::AlignLeft);
    hbox2->addWidget(m_download, 0, Qt::AlignVCenter | Qt::AlignRight);
    auto vbox = new QVBoxLayout();
    vbox->setSpacing(0);
    vbox->setContentsMargins(0,0,0,0);
    vbox->addStretch(1);
    vbox->addLayout(hbox1);
    vbox->addLayout(hbox2);
    vbox->addStretch(1);
    setLayout(vbox);
}
QString formatSpeed(int speed) {
    if (speed == 0) {
        return "0KiB";
    }
    if (speed < 1024) {
        return QString("%1KiB").arg(speed);
    }
    if (speed < 1024 * 1024) {
        speed = speed / 1024;
        return QString("%1MB").arg(speed);
    }
    speed = speed / 1024 / 1024;
    return QString("%1GB").arg(speed);
}
void NetworkWidget::updateInfo() {
    auto updateSeconds = 1;
    unsigned long long currentDownloadBytes = 0;
    unsigned long long currentUploadBytes = 0;
    getNetworkBandWidth(currentDownloadBytes, currentUploadBytes);
    auto downloadSpeed = (currentDownloadBytes - prevDownloadBytes) / 1024.0 /updateSeconds;
    auto uploadSpeed = (currentUploadBytes - prevUploadBytes) / 1024.0 / updateSeconds;
    int download = downloadSpeed;
    int upload = uploadSpeed;
    if (prevUploadBytes != 0) {
        m_upload->setText(formatSpeed(upload));
    }
    if (prevDownloadBytes != 0) {
        m_download->setText(formatSpeed(download));
    }
    prevDownloadBytes = currentDownloadBytes;
    prevUploadBytes = currentUploadBytes;
}
