//
// Created by pikachu on 7/20/19.
//

#ifndef SYSTEM_MONITER_DOUBLEICON_H
#define SYSTEM_MONITER_DOUBLEICON_H

#include <QLabel>
class DoubleIcon: public QLabel {
    Q_OBJECT
public:
    DoubleIcon(QString iconPath, QWidget *parent = nullptr);
};


#endif //SYSTEM_MONITER_DOUBLEICON_H
