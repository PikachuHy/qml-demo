//
// Created by pikachu on 7/20/19.
//

#ifndef SYSTEM_MONITER_SYSTEMMONITORWIDGET_H
#define SYSTEM_MONITER_SYSTEMMONITORWIDGET_H

#include <QWidget>
class QTimer;
class SystemMonitorWidget : public QWidget{
    Q_OBJECT
public:
    explicit SystemMonitorWidget(QWidget* parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

private:
    QTimer *m_timer;
};


#endif //SYSTEM_MONITER_SYSTEMMONITORWIDGET_H
