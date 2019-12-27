#include "uploadmanager.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QHttpMultiPart>
QINIU_BEGIN_NAMESPACE
QHttpPart buildPart(QString key, QByteArray value){
    QHttpPart part;
    part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(QString("form-data; name=\"%1\"").arg(key)));
    part.setBody(value);
    return part;
}
QHttpMultiPart* getBody(QString resourceKey, QString token, QByteArray fileData)
{
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    multiPart->append(buildPart("key", resourceKey.toLatin1()));
    multiPart->append(buildPart("token", token.toLatin1()));
    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(QString("form-data; name=\"file\"; filename=\"file1.png\"")));
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant(QString("application/octet-stream")));
    filePart.setRawHeader(QString("Content-Transfer-Encoding").toLatin1(), QString("binary").toLatin1());
    filePart.setBody(fileData);
    multiPart->append(filePart);
    return multiPart;
}

UploadManager::UploadManager(QObject *parent):
    QObject(parent)
{
    m_manager = new QNetworkAccessManager();
    connect(m_manager, &QNetworkAccessManager::finished, [=](QNetworkReply *reply){
        QByteArray result = reply->readAll();
        qDebug ().noquote() << result;
        emit uploadFinished(result);
        this->deleteLater();
    });
}

void UploadManager::put(QByteArray fileData, QString key, QString token)
{
    QString url = "http://up.qiniu.com";
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    QHttpMultiPart* multiPart = getBody(key, token, fileData);
    m_manager->post(request, multiPart);
}

QINIU_END_NAMESPACE