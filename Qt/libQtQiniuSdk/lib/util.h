#ifndef UTIL_H
#define UTIL_H
#include <QObject>
#include "qiniu_global.h"

QINIU_BEGIN_NAMESPACE
namespace Util {
QByteArray hmacSha1(const QString &key, const QString &secret);
    QString urlSafe(QString s);

}
QINIU_END_NAMESPACE

#endif // UTIL_H
