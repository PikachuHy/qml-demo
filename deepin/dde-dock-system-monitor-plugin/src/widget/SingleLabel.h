//
// Created by pikachu on 7/20/19.
//

#ifndef SYSTEM_MONITER_SINGLELABEL_H
#define SYSTEM_MONITER_SINGLELABEL_H

#include <QLabel>
class SingleLabel: public QLabel {
Q_OBJECT
public:
    explicit SingleLabel(QString text, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};


#endif //SYSTEM_MONITER_SINGLELABEL_H
