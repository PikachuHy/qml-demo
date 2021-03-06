#ifndef UPLOADMANAGER_H
#define UPLOADMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>

#include "qiniu_global.h"
QINIU_BEGIN_NAMESPACE
class UploadManager: public QObject
{
    Q_OBJECT
public:
    explicit UploadManager(QObject* parent = nullptr);
    void put(QByteArray fileData, QString key, QString token);
    signals:
    void uploadFinished(QByteArray retBody);
private:
    QNetworkAccessManager* m_manager;

};

QINIU_END_NAMESPACE
#endif // UPLOADMANAGER_H
