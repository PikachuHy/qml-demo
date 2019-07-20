//
// Created by pikachu on 7/20/19.
//

#include "DoubleLabel.h"
#include <QPainter>
DoubleLabel::DoubleLabel(QString text, QWidget *parent) : QLabel(parent) {
    int size = 12;
    setFixedHeight(size);
    setText(text);
}

void DoubleLabel::paintEvent(QPaintEvent *event) {
#ifdef DEBUG
    QPainter painter(this);
    QPen pen(Qt::black, 5, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    painter.drawRect(0, 0, this->width(), this->height());
#endif
    QLabel::paintEvent(event);
}
