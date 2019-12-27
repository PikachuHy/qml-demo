//
// Created by PikachuHy on 2019/12/19.
//

#ifndef SOA_SERVICE_COMPOSITION_HTTP_H
#define SOA_SERVICE_COMPOSITION_HTTP_H

#include <QString>
#include <QNetworkReply>
namespace http {
    void get(const QUrl & url, std::function<void(QNetworkReply*)> f);
    void post(const QUrl & url, const QByteArray &body, std::function<void(QNetworkReply*)> f);
};


#endif //SOA_SERVICE_COMPOSITION_HTTP_H
