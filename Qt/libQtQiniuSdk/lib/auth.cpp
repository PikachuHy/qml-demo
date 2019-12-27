#include "auth.h"
#include "uploadpolicy.h"
#include <QCryptographicHash>

#include "util.h"
#include "qiniu_global.h"
#include <QDebug>
QINIU_USE_NAMESPACE
using namespace Util;


Auth::Auth(QString accessKey, QString secretKey):
    m_accessKey(accessKey), m_secretKey(secretKey)
{

}

QString Auth::getUploadToken(QString bucket, QString key)
{
    UploadPolicy policy;
    policy.setBucket(bucket);
    policy.setKey(key);

    QString putPolicy = policy.toJSON();
    QString encodePutPolicy = putPolicy.toLatin1().toBase64();
    encodePutPolicy = urlSafe(encodePutPolicy);
    QByteArray sign = hmacSha1(encodePutPolicy, m_secretKey);
    // 这一步不能省，完成类型转换
    QString encodeSign = sign;
    encodeSign = urlSafe(encodeSign);
    QString uploadToken = QString("%1:%2:%3")
            .arg(m_accessKey)
            .arg(encodeSign)
            .arg(encodePutPolicy);
    return uploadToken;
}