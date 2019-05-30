#include "auth.h"
#include "uploadpolicy.h"
#include <QCryptographicHash>

#include "util.h"
#include "qiniu_global.h"
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
    QByteArray sign = hmacSha1(encodePutPolicy.toLatin1(), m_secretKey.toLatin1());
    // 这一步不能省，完成类型转换
    QString encodeSign = sign;
    QString uploadToken = QString("%1:%2:%3")
            .arg(m_accessKey)
            .arg(encodeSign)
            .arg(encodePutPolicy);

    return uploadToken;
}