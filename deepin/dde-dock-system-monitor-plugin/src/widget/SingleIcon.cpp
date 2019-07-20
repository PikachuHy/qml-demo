//
// Created by pikachu on 7/20/19.
//

#include "SingleIcon.h"

SingleIcon::SingleIcon(QString iconPath, QWidget *parent)
        : QLabel(parent) {
//    setFixedSize(24, 24);
    setPixmap(QPixmap(iconPath));
}
