#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class QMediaPlayer;
class QTimer;
class Setting;
class TypeWidget : public QWidget
{
    Q_OBJECT

public:
    TypeWidget(QWidget *parent = 0);
    ~TypeWidget();


    // QWidget interface
    void keyReleaseEvent(QKeyEvent *event) override;
public slots:
    void reset();
    void resetText(QString text);
    void pause();
protected:
    void paintEvent(QPaintEvent *event) override;
signals:
    void updateTime(QString time);
    void updateSpeed(int speed);
    void updateProgress(int progress);
    void updateAccuracy(int accuracy);
private:
    void drawWrongChar(QPainter &painter, int x, int y, int w, QString targetCh, QString inputCh);
    void drawCorrectChar(QPainter &painter, int x, int y, int w, QString chStr);
    void drawCursor(QPainter &painter, int x, int y);
    void nextPageJudge();
    int countWrongCh();
    void playAudio();
    int calAccuracy();
    int calSpeed();
    QString formatTime();
    QString prehanlde(QString text);
private slots:
    void finishTest();
private:
    QString m_text;
    QString m_input;
    QStringList m_pageText;
    int m_eachLineCharCount;
    int m_fontWidth;
    int m_lineHeight;
    bool m_cursorShow;
    int m_pageNum;
    int m_eachPageLineCount;
    int m_time;
    int m_inputTotal;
    int m_textTotal;
    int m_prevWrongCount;
    bool m_start;
    bool m_finish;

    QMediaPlayer *m_audioPlayer;
    QTimer *m_timer;
    Setting *m_setting;
};

#endif // WIDGET_H
