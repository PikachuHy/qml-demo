#ifndef UPLOADPOLICY_H
#define UPLOADPOLICY_H

#include "qiniu_global.h"
#include <QObject>

QINIU_BEGIN_NAMESPACE
struct UploadPolicy
{
public:
    QString toJSON();

    void setBucket(const QString &bucket);

    void setKey(const QString &key);

private:

    QString m_bucket;
    QString m_key;
};
QINIU_END_NAMESPACE
#endif // UPLOADPOLICY_H
