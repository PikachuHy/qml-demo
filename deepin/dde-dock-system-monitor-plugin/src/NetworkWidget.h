//
// Created by pikachu on 7/20/19.
//

#ifndef SYSTEM_MONITER_NETWORKWIDGET_H
#define SYSTEM_MONITER_NETWORKWIDGET_H

#include <QWidget>
class QLabel;
class NetworkWidget : public QWidget {
public:
    explicit NetworkWidget(QWidget *parent = nullptr);
    void updateInfo();
private:
    unsigned long long prevDownloadBytes = 0;
    unsigned long long prevUploadBytes = 0;
    QLabel *m_download;
    QLabel *m_upload;
};


#endif //SYSTEM_MONITER_NETWORKWIDGET_H
