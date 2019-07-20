//
// Created by pikachu on 7/20/19.
//

#include "SingleLabel.h"

SingleLabel::SingleLabel(QString text, QWidget *parent): QLabel(parent) {
    setFixedSize(16 * 3, 16);
    setText(text);
}
