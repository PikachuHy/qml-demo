//
// Created by pikachu on 7/20/19.
//

#ifndef SYSTEM_MONITER_DOUBLELABEL_H
#define SYSTEM_MONITER_DOUBLELABEL_H

#include <QLabel>
class DoubleLabel: public QLabel {
Q_OBJECT
public:
    explicit DoubleLabel(QString text, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};


#endif //SYSTEM_MONITER_DOUBLELABEL_H
