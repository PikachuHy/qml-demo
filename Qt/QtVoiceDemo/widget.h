#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QAudioEncoderSettings>
#include <QAudioProbe>
#include <QAudioRecorder>
#include <QDate>
#include <QDebug>
#include <QDir>
#include <QFont>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QStandardPaths>
#include <QTime>
#include <QUrl>
#include <QVBoxLayout>
#include <QApplication>
#include <QMediaPlayer>
#include <QTimer>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButtonRecord_clicked();

    void on_pushButtonPause_clicked();

    void on_pushButtonStop_clicked();

    void on_pushButtonPlay_clicked();

    void on_pushButtonQuit_clicked();

private:
    Ui::Widget *ui;
    QAudioProbe *audioProbe;
    QAudioRecorder *audioRecorder;
    QMediaPlayer *audioPlayer;

    QString m_location;

    QTimer *m_timer;
    int m_time;
};

#endif // WIDGET_H
