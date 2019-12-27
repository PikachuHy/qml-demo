#ifndef SERVICEPROGRESS_H
#define SERVICEPROGRESS_H

#include <QWidget>
#include <QProgressBar>
#include <QLabel>
#include <QDialog>
class ServiceProgress : public QDialog
{
    Q_OBJECT

public:
    explicit ServiceProgress(QWidget *parent = nullptr);
public slots:
    void setProgress(int percentage);
    void setTips(QString text);

    void progressInc();
signals:
private:
    QProgressBar *progressBar;
    QLabel *tips;
};

#endif // SERVICEPROGRESS_H
