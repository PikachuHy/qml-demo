#include "widget.h"
#include "ui_widget.h"
#include <QTimer>
QString formatMillisecond(int millisecond)
{
    if (millisecond / 1000 < 3600) {
        // At least need return 1 seconds.
        return QDateTime::fromTime_t(std::max(1, millisecond / 1000)).toUTC().toString("mm:ss");
    } else {
        return QDateTime::fromTime_t(millisecond / 1000).toUTC().toString("hh:mm:ss");
    }
}
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_location = "/tmp/t.wav";
    m_time = 0;
    audioRecorder = new QAudioRecorder(this);
    qDebug() << "support codecs:" << audioRecorder->supportedAudioCodecs();
    qDebug() << "support containers:" << audioRecorder->supportedContainers();

    QAudioEncoderSettings audioSettings;
    audioSettings.setQuality(QMultimedia::HighQuality);

#if QT_VERSION >= QT_VERSION_CHECK(5, 9, 0)
    audioRecorder->setAudioSettings(audioSettings);
    audioRecorder->setContainerFormat("audio/x-wav");
#else
    audioSettings.setCodec("audio/PCM");
    audioRecorder->setAudioSettings(audioSettings);
    audioRecorder->setContainerFormat("wav");
#endif

    audioProbe = new QAudioProbe(this);
    audioProbe->setSource(audioRecorder);
    audioPlayer = new QMediaPlayer();

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, [=]() {
        m_time += 1000;
        auto str = tr("录音时间: %1").arg(formatMillisecond(m_time));
        qDebug()<<str <<m_time;
        ui->labelTime->setText(str);
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonRecord_clicked()
{

    qDebug() << "开始录音";
    audioRecorder->setOutputLocation(m_location);
    audioRecorder->record();
    m_timer->stop();
    m_timer->start(1000);
}

void Widget::on_pushButtonPause_clicked()
{
    m_timer->stop();
    qDebug() << "暂停录音";
    audioRecorder->pause();
}

void Widget::on_pushButtonStop_clicked()
{
    qDebug()<<"停止录音";
    audioRecorder->stop();
    m_timer->stop();
}

void Widget::on_pushButtonPlay_clicked()
{
    qDebug () << "播放录音";

    audioPlayer->setMedia(QUrl::fromLocalFile(m_location));
    audioPlayer->play();
}

void Widget::on_pushButtonQuit_clicked()
{
    qApp->quit();
}
