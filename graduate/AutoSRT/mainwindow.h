#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <string>
#include <vector>
#include <QPushButton>
#include <QMediaPlayer>
#include <QListWidget>
#include <QTableWidget>
#include <QStackedWidget>
#include <QJsonObject>
#include "previewwidget.h"
#include "videoinputwidget.h"
#include "serviceprogress.h"
#include <auth.h>
struct AliyunConfig {
    std::string accessKeyId;
    std::string accessKeySecret;
    std::string appKey;
    std::string filetransPrefix;
    std::string nlsMetaPrefix;
};
struct QiniuConfig {
    QString accessKey;
    QString secretKey;
    QString bucket;
    QString prefix; // url前缀，含http(s)
};
struct Sentence {
    long beginTime;
    long endTime;
    QString text;
    static Sentence fromJSON(QJsonObject o) {
        Sentence ret;
        ret.beginTime = o["BeginTime"].toInt();
        ret.endTime = o["EndTime"].toInt();
        ret.text = o["Text"].toString();
        return ret;
    }
};
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();
    bool eventFilter(QObject *watched, QEvent *event) override;

public slots:
    void requestFinished(QNetworkReply *reply);
private:
    std::string taskId;
    PreviewWidget *videoWidget;
    VideoInputWidget *videoInputWidget;
    QTableWidget *tableWidget;
    QStackedWidget *stackedWidget;
    std::vector<Sentence> sentences;
    ServiceProgress *progressDialog;
    QString ffmpegCmd = "ffmpeg";
    std::unique_ptr<Qiniu::Auth> auth;
    AliyunConfig aliyunConfig;
    QiniuConfig qiniuConfig;
    QPushButton *exportSrtBtn;
private:
    void parseSubmitTaskRes(const QByteArray & body);
    void parseGetTaskResultRes(const QByteArray & body);

    void doService(QString filename);

    bool checkFfmpeg();

    std::pair<bool, QString> extractAudio(const QString& filename);

    void uploadAudioFile(QString filename);

    void submitTask(QString audioUrl);

    void getTaskResult();

    void getToken();

    bool httpResponseCommonHandle(QNetworkReply *reply);

    void updateTableWidget();

    void exportSrt(QString filepath);
};

#endif // MAINWINDOW_H
