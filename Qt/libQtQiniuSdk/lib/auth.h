#ifndef AUTH_H
#define AUTH_H

#include "qiniu_global.h"
#include <QObject>
QINIU_BEGIN_NAMESPACE
class Auth
{
public:
    Auth(QString accessKey, QString secretKey);
    QString getUploadToken(QString bucket, QString key);
private:
    QString m_accessKey;
    QString m_secretKey;
};
QINIU_END_NAMESPACE
#endif // AUTH_H
