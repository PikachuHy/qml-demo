#include "uploadpolicy.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>
QINIU_USE_NAMESPACE
QString UploadPolicy::toJSON()
{
    QString scope = QString("%1:%2").arg(m_bucket).arg(m_key);
    int deadline = QDateTime::currentDateTime().toTime_t() + 3600;;
    // 必须保持这个顺序才对
    return QString("{\"scope\":\"%1\",\"deadline\":%2}").arg(scope).arg(deadline);
}

void UploadPolicy::setBucket(const QString &bucket)
{
    m_bucket = bucket;
}

void UploadPolicy::setKey(const QString &key)
{
    m_key = key;
}
