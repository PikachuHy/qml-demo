//
// Created by pikachu on 7/20/19.
//

#ifndef SYSTEM_MONITER_MEMORYWIDGET_H
#define SYSTEM_MONITER_MEMORYWIDGET_H

#include <QWidget>
class QLabel;
class MemoryWidget: public QWidget {
public:
    explicit MemoryWidget(QWidget *parent = nullptr);
    void updateInfo();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QLabel *m_memory;
};


#endif //SYSTEM_MONITER_MEMORYWIDGET_H
