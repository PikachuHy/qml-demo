#include "mainwindow.h"
#include "serviceprogress.h"
#include <QApplication>
#include <QPushButton>
#include <QDebug>
#include <string>
#include <map>
#include <iostream>
#include <QtCore>
#include <QtWidgets>
#include <QtQiniu>
#include "util.h"
#include "http.h"

using std::string;
using std::vector;
using std::map;
using std::string;
using std::pair;
string genQueryStringWithSign(
        const string & method,
        const map<string,string> & param,
        const string & accessKeySecret) {
    string queryString;
    for(const auto &[k, v]: param) {
        queryString
        .append("&")
        .append(util::urlEncode(k))
        .append("=")
        .append(util::urlEncode(v));
    }
    queryString = queryString.substr(1);
    string strSign;
    strSign
    .append(method)
    .append("&")
    .append(util::urlEncode("/"))
    .append("&")
    .append(util::urlEncode(queryString));

    string signature = util::hmac_sha1(
            QString::fromStdString(strSign),
            QString::fromStdString(accessKeySecret + "&"))
                    .toStdString();
    string queryStringWithSign = "Signature=" + util::urlEncode(signature) + "&" + queryString;
    return queryStringWithSign;
}
// Token
string genTokenRequestParam(const string &AccessKeyId, const string &AccessKeySecret) {
    map<string, string> m;
    m["AccessKeyId"] = AccessKeyId;
    m["Action"] = "CreateToken";
    m["Version"] = "2019-02-28";
    m["Timestamp"] = util::getCurrentSystemTime();
    m["Format"] = "JSON";
    m["RegionId"] = "cn-shanghai";
    m["SignatureMethod"] = "HMAC-SHA1";
    m["SignatureVersion"] = "1.0";
    m["SignatureNonce"] = "b924c8c3-6d03-4c5d-ad36-d984d3116788";
    return genQueryStringWithSign("GET", m, AccessKeySecret);
}

// Submit Task
pair<string, string> genSubmitTaskRequestParam(
        const string &AccessKeyId,
        const string &AccessKeySecret,
        const string &AppKey,
        const string &url) {
    map<string, string> m;
    m["AccessKeyId"] = AccessKeyId;
    m["Action"] = "SubmitTask";
    m["Version"] = "2018-08-17";
    m["Timestamp"] = util::getCurrentSystemTime();
//    m["Timestamp"]="2019-12-17T01:50:16Z";
    m["Format"] = "JSON";
    m["RegionId"] = "cn-shanghai";
    m["SignatureMethod"] = "HMAC-SHA1";
    m["SignatureVersion"] = "1.0";
//    m["SignatureNonce"]="ce41cb44-5e64-4fb0-808a-e2994d437756";
    m["SignatureNonce"] = QUuid::createUuid().toString().toStdString();

    m["Task"] = R"({"appkey":")" + AppKey + R"(","file_link":")" + url + "\"}";
    std::cout << m["Task"] << std::endl;
    return {genQueryStringWithSign("POST", m, AccessKeySecret), m["Task"]};
}

// Test Get Task Result
string genGetTaskResultRequestParam(
        const string &AccessKeyId,
        const string &AccessKeySecret,
        const string &TaskId) {
    map<string, string> m;
    m["AccessKeyId"] = AccessKeyId;
    m["Action"] = "GetTaskResult";
    m["TaskId"] = TaskId;
    m["Version"] = "2018-08-17";
    m["Timestamp"] = util::getCurrentSystemTime();
//    m["Timestamp"]="2019-12-17T03:24:47Z";
    m["Format"] = "JSON";
    m["RegionId"] = "cn-shanghai";
    m["SignatureMethod"] = "HMAC-SHA1";
    m["SignatureVersion"] = "1.0";
//    m["SignatureNonce"]="2aa27764-6769-413b-959a-d6ae9ae88225";
    m["SignatureNonce"] = QUuid::createUuid().toString().toStdString();
    return genQueryStringWithSign("GET", m, AccessKeySecret);
}

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    qiniuConfig.accessKey = "<access key>";
    qiniuConfig.secretKey = "<secret key>";
    qiniuConfig.bucket = "<bucket name>";
    qiniuConfig.prefix = "<domain>";
    aliyunConfig.accessKeyId = "<access key id>";
    aliyunConfig.accessKeySecret = "<access key secret>";
    aliyunConfig.appKey = "<appkey>";
    aliyunConfig.filetransPrefix = "http://filetrans.cn-shanghai.aliyuncs.com/?";
    aliyunConfig.nlsMetaPrefix = "http://nls-meta.cn-shanghai.aliyuncs.com/?";
    auth = std::make_unique<Qiniu::Auth>(qiniuConfig.accessKey, qiniuConfig.secretKey);

//    sentences = initSentence();
    stackedWidget = new QStackedWidget();
    videoWidget = new PreviewWidget();
    videoWidget->show();
    tableWidget = new QTableWidget();
    tableWidget->setColumnCount(3);
    tableWidget->setRowCount(sentences.size());
    QStringList headers;
    headers << tr("BeginTime") << tr("EndTime") << tr("Text");
    tableWidget->setHorizontalHeaderLabels(headers);
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->installEventFilter(this);

    connect(tableWidget, &QTableWidget::cellChanged, [=](int row, int col) {
        sentences[row].text = tableWidget->item(row, col)->text();
    });
    updateTableWidget();
    exportSrtBtn = new QPushButton(tr("Export Srt"));
    connect(exportSrtBtn, &QPushButton::clicked, [=](){
        auto filepath = QFileDialog::getSaveFileName(
                this,
                tr("Choose save file path"),
                QDir::homePath()+"/default.srt",
                "SubRip Text (*.srt)"
                );
        if (filepath.isEmpty()) return;
        exportSrt(filepath);
    });
    auto w = new QWidget();
    auto layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(5);
    layout->addWidget(exportSrtBtn);
    layout->addWidget(videoWidget);
    layout->addWidget(tableWidget);
    w->setLayout(layout);
//    stackedWidget->addWidget(w);
    videoInputWidget = new VideoInputWidget();
//    stackedWidget->addWidget(videoInputWidget);
//    stackedWidget->setCurrentWidget(videoInputWidget);
    setCentralWidget(w);
    connect(videoInputWidget, &VideoInputWidget::receiveVideoFile,
            videoWidget, &PreviewWidget::setPreviewVideoFile);
    connect(videoInputWidget, &VideoInputWidget::receiveVideoFile, [=](QString filename) {
        videoInputWidget->close();

        const QRect screenGeometry = QApplication::desktop()->screenGeometry(this);
        auto center_x = (screenGeometry.width() - this->width()) / 2;
        auto center_y = (screenGeometry.height() - this->height()) / 2;
        move(center_x, center_y);
//        stackedWidget->setCurrentWidget(w);
        this->show();
        auto ret = QMessageBox::question(
                this,
                tr("Check If Request Aliyun Service"),
                tr("Would you like to use Aliyun Service to auto generate SRT?"));
        if (ret == QMessageBox::Yes) {
            doService(filename);
        } else {
            QMessageBox::information(this, "", "The feature is under developing.");
            qApp->exit();
        }
    });
    videoInputWidget->show();
    resize(1920, 1080);
}

void MainWindow::updateTableWidget() {
    qDebug() << __func__;
    // 这个会把Header也清理掉
//    this->tableWidget->clear();
    this->tableWidget->setRowCount(this->sentences.size());
    for (int i = 0; i < sentences.size(); ++i) {
        QList<QTableWidgetItem *> items;
        items << new QTableWidgetItem(util::formatTime(sentences[i].beginTime));
        items << new QTableWidgetItem(util::formatTime(sentences[i].endTime));
        items << new QTableWidgetItem(sentences[i].text);
        for (int col = 0; col < items.size() - 1; ++col) {
            items[col]->setFlags(items[col]->flags() & (~Qt::ItemIsEditable));
        }
        for (int col = 0; col < items.size(); ++col) {
            tableWidget->setItem(i, col, items[col]);
        }
    }
}

MainWindow::~MainWindow() {
}

void MainWindow::requestFinished(QNetworkReply *reply) {
    if (httpResponseCommonHandle(reply)) {
        qDebug() << "HTTP Response ERROR";
        qApp->exit(1);
    } else {
        // 获取返回内容
        const QByteArray &resBody = reply->readAll();
        qDebug().noquote().nospace() << resBody;
    };
}

void MainWindow::parseSubmitTaskRes(const QByteArray &body) {
    QJsonDocument jsonDocument = QJsonDocument::fromJson(body);
    QJsonObject jsonObject = jsonDocument.object();
    this->taskId = jsonObject["TaskId"].toString().toStdString();
    std::cout << "Get TaskId " << this->taskId << std::endl;
    this->progressDialog->setProgress(80);
    this->progressDialog->setTips(tr("Get task result..."));
    this->getTaskResult();
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
    if (watched == this->tableWidget) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Space) {
                auto row = this->tableWidget->currentRow();
                this->videoWidget->play(
                        sentences[row].beginTime,
                        sentences[row].endTime,
                        sentences[row].text);
                return true;
            }
        }
    }
    return QObject::eventFilter(watched, event);
}

void MainWindow::doService(QString filename) {
    progressDialog = new ServiceProgress(this);
    progressDialog->show();
    auto ret = checkFfmpeg();
    auto[eaRet, filepath] = extractAudio(filename);
    uploadAudioFile(filepath);
}

bool MainWindow::checkFfmpeg() {
    qDebug() << __func__;
    progressDialog->setProgress(5);
    progressDialog->setTips(tr("Checking ffmpeg..."));
    QProcess p;
    QStringList args;
    args << "-version";
    p.start(ffmpegCmd, args);
    p.waitForFinished();
    auto err = p.readAllStandardError();
    if (!err.isEmpty()) {
        QMessageBox::information(this, "", "Please install ffmpeg first!!!");
        qApp->quit();
    }
    return false;
}

QString createTmpfile() {
    QString tmpfile = QUuid::createUuid().toString();
    while (tmpfile.contains("-")) {
        tmpfile = tmpfile.replace("-", "");
    }
    tmpfile = tmpfile.replace("{", "");
    tmpfile = tmpfile.replace("}", "");
    return tmpfile;
}

std::pair<bool, QString> MainWindow::extractAudio(const QString &filename) {
    qDebug() << __func__;
    progressDialog->setProgress(20);
    progressDialog->setTips(tr("Extracting audio..."));
    QString tmpfile = createTmpfile();
    tmpfile = "/tmp/" + tmpfile + ".wav";
    QProcess p;
    QStringList args;
    args << "-i";
    args << filename;
    args << "-ac";
    args << "1";
    args << "-ar";
    args << "16000";
    args << tmpfile;
    qDebug() << ffmpegCmd << args;
    p.start(ffmpegCmd, args);
    p.waitForFinished();
    auto err = p.readAllStandardError();
    // TODO: 出错怎么办？
    qDebug().noquote().nospace() << err;
//    if (!err.isEmpty()) {
//        qDebug() << err;
//        QMessageBox::critical(this, tr("Extract Audio ERROR"), err);
//        qApp->quit();
//    }
    return {true, tmpfile};
}

QByteArray getFileData(QString filepath) {
    QFile file(filepath);
    auto ret = file.open(QIODevice::ReadOnly);
    if (!ret) {
        qDebug() << "ERROR: " << filepath << " is not exist.";
        exit(1);
    }
    QByteArray fdata = file.readAll();
    file.close();
    return fdata;
}

QJsonObject parseJsonObject(QByteArray resBody) {
    QJsonDocument jsonDocument = QJsonDocument::fromJson(resBody);
    return jsonDocument.object();
}

void MainWindow::uploadAudioFile(QString filename) {
    qDebug() << __func__;
    progressDialog->setProgress(30);
    progressDialog->setTips(tr("Uploading audio file..."));
    QString key = QString("autosrt/%1.wav").arg(QFileInfo(filename).baseName());
    qDebug() << "upload filepath: " << key;
    auto manager = new Qiniu::UploadManager();
    QString bucket = qiniuConfig.bucket;
    auto token = auth->getUploadToken(bucket, key);
    manager->put(getFileData(filename), key, token);
    connect(manager, &Qiniu::UploadManager::uploadFinished, [=](QByteArray resBody) {
        auto o = parseJsonObject(resBody);
        if (o["error"].isNull()) {
            qDebug() << "file upload success";
            QString url = QString("%1/%2").arg(qiniuConfig.prefix).arg(key);
            this->progressDialog->setTips(tr("Submit Task ..."));
            this->progressDialog->setProgress(50);
            submitTask(url);
        } else {
            qDebug() << "file upload error:" << resBody;
            qApp->exit(1);
        }
    });
}

void MainWindow::submitTask(QString audioUrl) {
    string fileurl = audioUrl.toStdString();
    auto[ret, json] = genSubmitTaskRequestParam(
            aliyunConfig.accessKeyId,
            aliyunConfig.accessKeySecret,
            aliyunConfig.appKey, fileurl);
    QString url = QString::fromStdString(aliyunConfig.filetransPrefix + ret);
    QByteArray postData;
    postData.append(QString::fromStdString("Task=" + util::urlEncode(json)));
    http::post(QUrl(url), postData, [=](QNetworkReply *reply) {
        auto resBody = reply->readAll();
        if (!httpResponseCommonHandle(reply)) {
            qDebug() << "Submit task ERROR";
            qDebug().nospace().noquote() << resBody;
            QMessageBox::critical(this, "", resBody);
            qApp->exit(1);
        } else {
            parseSubmitTaskRes(resBody);
        }
    });
}

void MainWindow::getTaskResult() {
    string ret = genGetTaskResultRequestParam(
            aliyunConfig.accessKeyId,
            aliyunConfig.accessKeySecret,
            this->taskId);
    QString url = QString::fromStdString(aliyunConfig.filetransPrefix + ret);
    http::get(QUrl::fromEncoded(url.toLocal8Bit()), [=](QNetworkReply *reply) {
        auto resBody = reply->readAll();
        if (!httpResponseCommonHandle(reply)) {
            qDebug() << "Get Task Result ERROR";
            qDebug().nospace().noquote() << resBody;
            QString msg = resBody.isEmpty() ? reply->errorString() : resBody;
            QMessageBox::critical(this, "", msg);
            qApp->exit(1);
        } else {
            parseGetTaskResultRes(resBody);
        }
    });
}

void MainWindow::getToken() {
    string ret = genTokenRequestParam(
            aliyunConfig.accessKeyId,
            aliyunConfig.accessKeySecret);
    QString url = QString::fromStdString(aliyunConfig.nlsMetaPrefix + ret);
    http::get(QUrl(url), [=](QNetworkReply *reply) {
        this->requestFinished(reply);
    });
}

void MainWindow::parseGetTaskResultRes(const QByteArray &body) {
    auto o = parseJsonObject(body);
    // {"TaskId":"","RequestId":"","StatusText":"QUEUEING","StatusCode":21050002}
    const QString &statusText = o["StatusText"].toString();
    if (statusText == "QUEUEING" || statusText == "RUNNING") {
        qDebug().noquote() << body;
        this->progressDialog->progressInc();
        QTimer::singleShot(4000, [this]() {
            this->getTaskResult();
        });
    } else if (statusText == "FILE_403_FORBIDDEN") {
        qDebug() << body;
        qDebug() << "Audio file can not visited!";
        qApp->exit(1);
    } else if (statusText == "SUCCESS") {
        qDebug() << "Task success";
        this->sentences.clear();
        auto ret = o["Result"].toObject();
        qDebug().noquote().nospace() << o["Result"].toString();
        QJsonArray jsonArray = ret["Sentences"].toArray();
        for (int i = 0; i < jsonArray.size(); ++i) {
            sentences.emplace_back(Sentence::fromJSON(jsonArray[i].toObject()));
        }
        this->progressDialog->setProgress(100);
        this->progressDialog->setTips(tr("Finished"));
        this->updateTableWidget();
        QTimer::singleShot(1000, [=]() {
            this->progressDialog->close();
        });
    } else {
        qDebug() << body;
        qApp->exit(1);
    }
}

bool MainWindow::httpResponseCommonHandle(QNetworkReply *reply) {
    // 获取http状态码
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if (statusCode.isValid())
        qDebug() << "status code=" << statusCode.toInt();

    QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
    if (reason.isValid())
        qDebug() << "reason=" << reason.toString();

    QNetworkReply::NetworkError err = reply->error();
    if (err != QNetworkReply::NoError) {
        qDebug().noquote() << "Failed: " << reply->errorString();
        QString s = reply->readAll();
        QJsonDocument jsonDocument = QJsonDocument::fromJson(s.toLatin1());
        QJsonObject jsonObject = jsonDocument.object();
        qDebug() << "Message" << jsonObject["Message"].toString();
        qDebug() << "Code" << jsonObject["Code"].toString();
        return false;
    }
    return true;
}

void MainWindow::exportSrt(QString filepath) {
    QString sb;
    for (int i = 0; i < this->sentences.size(); ++i) {
        sb.append(QString::number(i+1))
        .append("\n")
        .append(util::formatTime(sentences[i].beginTime))
        .append(" --> ")
        .append(util::formatTime(sentences[i].endTime))
        .append("\n")
        .append(sentences[i].text)
        .append("\n")
        .append("\n");
    }
    QFile file(filepath);
    bool ret = file.open(QIODevice::WriteOnly);
    if (!ret) {
        QMessageBox::critical(
                this,
                "",
                tr("Cannot open file %1").arg(filepath)
                );
        return;
    }
    file.write(sb.toLocal8Bit());
    file.flush();
    file.close();
    QMessageBox::information(
            this,
            "",
            tr("Srt export success!!!")
            );
}
