//
// Created by pikachu on 7/20/19.
//

#include "NetworkWidget.h"
#include "widget/DoubleIcon.h"
#include "widget/DoubleLabel.h"
#include <QLabel>
#include <QGridLayout>
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
    auto uploadIcon = new DoubleIcon(":/right_top.svg");
    auto downloadIcon = new DoubleIcon(":/left_down.svg");
    m_upload = new DoubleLabel("---");
    m_download = new DoubleLabel("---");
    auto grid = new QGridLayout();
    grid->addWidget(uploadIcon, 0, 0);
    grid->addWidget(m_upload, 0, 1);
    grid->addWidget(downloadIcon, 1, 0);
    grid->addWidget(m_download, 1, 1);
    setLayout(grid);
}
QString formatSpeed(int speed) {
    if (speed == 0) {
        return "---";
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
