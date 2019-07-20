//
// Created by pikachu on 7/20/19.
//

#include "MemoryWidget.h"
#include "widget/SingleLabel.h"
#include "widget/SingleIcon.h"
#include <QLabel>
#include <QHBoxLayout>
#include <proc/sysinfo.h>
#include <QPainter>
MemoryWidget::MemoryWidget(QWidget *parent)
: QWidget(parent) {
    auto hbox = new QHBoxLayout();
    auto icon = new SingleIcon(":/icon_memory_dark.svg");
    m_memory = new SingleLabel("---");
    hbox->addWidget(icon);
    hbox->addWidget(m_memory);
    setLayout(hbox);
}

void MemoryWidget::updateInfo() {
    meminfo();
    auto memoryPercent = (kb_main_total - kb_main_available) * 100.0 / kb_main_total;
    auto swapPercent = kb_swap_used * 100.0 / kb_swap_total;
    int memory = memoryPercent;
    if (memory == 0) {
        m_memory->setText("---");
    }else if (memory < 10) {
        m_memory->setText(QString("0%1%").arg(memory));
    } else {
        m_memory->setText(QString("%1%").arg(memory));
    }
}

void MemoryWidget::paintEvent(QPaintEvent *event) {
#ifdef DEBUG
    QPainter painter(this);
    QPen pen(Qt::yellow, 5, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    painter.drawRect(0, 0, this->width(), this->height());
#endif
    QWidget::paintEvent(event);
}
