//
// Created by PikachuHy on 2019/12/19.
//

#include "http.h"
#include <QNetworkAccessManager>
#include <QDebug>
namespace http {
    void get(const QUrl &url, std::function<void(QNetworkReply *)> f) {
        qDebug().noquote() << "GET" << url.toString();
        QNetworkRequest request;
        auto naManager = new QNetworkAccessManager();
        QObject::connect(naManager, &QNetworkAccessManager::finished, f);
        QObject::connect(naManager, &QNetworkAccessManager::finished, naManager, &QNetworkAccessManager::deleteLater);
        request.setUrl(url);
        naManager->get(request);
    }

    void post(const QUrl &url, const QByteArray &body, std::function<void(QNetworkReply *)> f) {
        qDebug().noquote() << "POST" << url.toString();
        QNetworkRequest request;
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded;charset=utf-8");
        auto naManager = new QNetworkAccessManager();
        QObject::connect(naManager, &QNetworkAccessManager::finished, f);
        QObject::connect(naManager, &QNetworkAccessManager::finished, naManager, &QNetworkAccessManager::deleteLater);
        request.setUrl(url);
        naManager->post(request, body);
    }
}