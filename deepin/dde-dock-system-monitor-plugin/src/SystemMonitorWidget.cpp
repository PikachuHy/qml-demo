//
// Created by pikachu on 7/20/19.
//

#include "SystemMonitorWidget.h"
#include "CpuWidget.h"
#include "MemoryWidget.h"
#include "NetworkWidget.h"
#include <QMouseEvent>
#include <QProcess>
#include <QHBoxLayout>
#include <QTimer>
#include <QPainter>
SystemMonitorWidget::SystemMonitorWidget(QWidget* parent): QWidget(parent) {
    auto hbox = new QHBoxLayout();
    auto cpu = new CpuWidget();
    auto memory = new MemoryWidget();
    auto network = new NetworkWidget();
    hbox->addWidget(cpu);
    hbox->addWidget(memory);
    hbox->addWidget(network);
    setLayout(hbox);
    m_timer = new QTimer();
    m_timer->setInterval(1000);
    connect(m_timer, &QTimer::timeout, cpu, &CpuWidget::updateInfo);
    connect(m_timer, &QTimer::timeout, memory, &MemoryWidget::updateInfo);
    connect(m_timer, &QTimer::timeout, network, &NetworkWidget::updateInfo);
    m_timer->start();
}

void SystemMonitorWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QProcess::startDetached("deepin-system-monitor");
    }
}

void SystemMonitorWidget::paintEvent(QPaintEvent *event) {
#ifdef DEBUG
    QPainter painter(this);
    QPen pen(Qt::green, 5, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    painter.drawRect(0, 0, this->width(), this->height());
#endif
    QWidget::paintEvent(event);
}

