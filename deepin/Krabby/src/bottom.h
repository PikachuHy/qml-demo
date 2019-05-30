#ifndef BOTTOM_H
#define BOTTOM_H

#include <QWidget>

namespace Ui {
class Bottom;
}

class Bottom : public QWidget
{
    Q_OBJECT

public:
    explicit Bottom(QWidget *parent = 0);
    ~Bottom();
public slots:
    void updateTime(QString time);
    void updateSpeed(int speed);
    void updateProgress(int progress);
    void updateAccuracy(int accuracy);
private:
    Ui::Bottom *ui;
};

#endif // BOTTOM_H
