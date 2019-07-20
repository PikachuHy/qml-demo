//
// Created by pikachu on 7/20/19.
//

#include "DoubleIcon.h"

DoubleIcon::DoubleIcon(QString iconPath, QWidget *parent)
        : QLabel(parent) {
//    setFixedSize(10, 10);
    setPixmap(QPixmap(iconPath));
}
