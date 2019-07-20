//
// Created by pikachu on 7/20/19.
//

#ifndef SYSTEM_MONITER_CPUWIDGET_H
#define SYSTEM_MONITER_CPUWIDGET_H

#include <QWidget>
class QLabel;
class QTimer;
class CpuWidget : public QWidget{
Q_OBJECT
public:
    explicit CpuWidget(QWidget *parent = nullptr);
    void updateInfo();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QLabel *m_cpu;
    unsigned long long prevWorkCpuTime = 0;
    unsigned long long prevTotalCpuTime = 0;
};


#endif //SYSTEM_MONITER_CPUWIDGET_H
