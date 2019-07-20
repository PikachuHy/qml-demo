//
// Created by pikachu on 7/20/19.
//

#include "SingleLabel.h"
#include <QPainter>
SingleLabel::SingleLabel(QString text, QWidget *parent): QLabel(parent) {
//    setFixedSize(16 * 3, 16);
    setText(text);
}

void SingleLabel::paintEvent(QPaintEvent *event) {
#ifdef DEBUG
    QPainter painter(this);
    QPen pen(Qt::black, 5, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    painter.drawRect(0, 0, this->width(), this->height());
#endif
    QLabel::paintEvent(event);
}
