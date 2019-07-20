//
// Created by pikachu on 7/20/19.
//

#ifndef SYSTEM_MONITER_SINGLEICON_H
#define SYSTEM_MONITER_SINGLEICON_H

#include <QLabel>
class SingleIcon: public QLabel {
    Q_OBJECT
public:
    explicit SingleIcon(QString iconPath, QWidget *parent = nullptr);
};


#endif //SYSTEM_MONITER_SINGLEICON_H
