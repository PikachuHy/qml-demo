//
// Created by pikachu on 7/20/19.
//

#include "DoubleIcon.h"
#include <QImage>
#include <QPainter>
#include <DHiDPIHelper>
DWIDGET_USE_NAMESPACE
DoubleIcon::DoubleIcon(QString iconPath, QWidget *parent)
        : QLabel(parent) {
    int size = 10;
    auto pixmap = DHiDPIHelper::loadNxPixmap(iconPath).scaled(QSize(size, size) * devicePixelRatioF(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    setPixmap(pixmap);
}

void DoubleIcon::paintEvent(QPaintEvent *event) {
#ifdef DEBUG
    QPainter painter(this);
    QPen pen(Qt::red, 5, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    painter.drawRect(0, 0, this->width(), this->height());
#endif
    QLabel::paintEvent(event);
}
