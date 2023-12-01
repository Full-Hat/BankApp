//
// Created by System Administrator on 11/30/23.
//

#include "Api.hpp"

#include <iostream>

namespace backend {

void Api::testConnection() {
    QNetworkRequest req;
    req.setUrl(QUrl("http://localhost/api/register/confirm"));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    req.setRawHeader("Accept", "*/*");
    std::cout << "Check connection" << std::endl;

    QJsonObject json;
    json["login"] = "FullHat";
    //json["email"] = "crazythtplay@gmail.com";
    //json["password"] = "NotPassword";
    json["code"] = "57055";

    QNetworkReply *reply = m_manager->post(req, QJsonDocument(json).toJson());

    QEventLoop loop;
    QObject::connect(m_manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
    loop.exec();

    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    std::cout << "CODE " << statusCode << std::endl;
    auto doc = QJsonDocument::fromJson(reply->readAll());
    std::cout << "TOKEN " << doc["token"].toString().toStdString() << std::endl;
    std::cout << "MESSAGE" << "" << std::endl;
}

Api::Api() {
    m_manager = new QNetworkAccessManager(this);
}

Api::resp_register_beg Api::RegisterBegin(const QString &login, const QString &email, const QString &password) {
    Api::resp_register_beg result;

    QNetworkRequest req;
    req.setUrl(QUrl(m_url_base + "begin"));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    req.setRawHeader("Accept", "*/*");

    QJsonObject json;
    json["login"] = login;
    json["email"] = email;
    json["password"] = password;

    QNetworkReply *reply = m_manager->post(req, QJsonDocument(json).toJson());

    QEventLoop loop;
    QObject::connect(m_manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
    loop.exec();

    result.error_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();
    auto doc = QJsonDocument::fromJson(reply->readAll());
    switch (result.error_code) {
        case 200:
            break;
        case 500:
            result.error_message = "Unknown error";
            break;
        default:
            result.error_message = doc["error"].toString();
            break;
    }

    return result;
}

Api::resp_register_confirm Api::RegisterConfirm(const QString &login, const QString &code) {
    Api::resp_register_confirm result;

    QNetworkRequest req;
    req.setUrl(QUrl(m_url_base + "confirm"));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    req.setRawHeader("Accept", "*/*");

    QJsonObject json;
    json["login"] = login;
    json["code"] = code;

    QNetworkReply *reply = m_manager->post(req, QJsonDocument(json).toJson());

    QEventLoop loop;
    QObject::connect(m_manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
    loop.exec();

    result.error_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();
    auto doc = QJsonDocument::fromJson(reply->readAll());
    switch (result.error_code) {
        case 200:
            result.token = doc["token"].toString();
            break;
        case 500:
            result.error_message = "Unknown error";
            break;
        default:
            result.error_message = doc["error"].toString();
            break;
    }

    return result;
}

} // backend