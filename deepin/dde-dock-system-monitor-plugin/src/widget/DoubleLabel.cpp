//
// Created by pikachu on 7/20/19.
//

#include "DoubleLabel.h"

DoubleLabel::DoubleLabel(QString text, QWidget *parent) : QLabel(parent) {
    int size = 12;
    setFixedSize(size * 3, size);
    auto f = font();
    f.setPixelSize(size);
    setFont(f);
    setText(text);
}
