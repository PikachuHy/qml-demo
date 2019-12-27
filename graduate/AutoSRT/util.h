//
// Created by PikachuHy on 2019/12/19.
//

#ifndef SOA_SERVICE_COMPOSITION_UTIL_H
#define SOA_SERVICE_COMPOSITION_UTIL_H

#include <QString>
namespace util {
    QString formatTime(long time);
    QByteArray hmac_sha1(const QString &key, const QString &secret);
    std::string urlEncode(const std::string& str);
    std::string getCurrentSystemTime();
};


#endif //SOA_SERVICE_COMPOSITION_UTIL_H
