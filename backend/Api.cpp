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
    req.setUrl(QUrl(m_url_base + "register/begin"));
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
    req.setUrl(QUrl(m_url_base + "register/confirm"));
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

Api::resp_login_beg Api::LoginBegin(const QString &login, const QString &password) {
    Api::resp_login_beg result;

    QNetworkRequest req;
    req.setUrl(QUrl(m_url_base + "login/begin"));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    req.setRawHeader("Accept", "*/*");

    QJsonObject json;
    json["login"] = login;
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

Api::resp_login_confirm Api::LoginConfirm(const QString &login, const QString &code) {
    Api::resp_login_confirm result;

    QNetworkRequest req;
    req.setUrl(QUrl(m_url_base + "login/confirm"));
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

    backend::Api::resp_accounts_get Api::AccountsGet(const QString &token) {
        resp_accounts_get result;

        QNetworkRequest req;
        req.setUrl(QUrl(m_url_base + "accounts"));
        req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        req.setRawHeader("Accept", "*/*");
        req.setRawHeader("Authorization", QByteArray((QString("Bearer ") + token).toStdString().data()));

        QNetworkReply *reply = m_manager->get(req);

        QEventLoop loop;
        QObject::connect(m_manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
        loop.exec();

        result.code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();

        auto json = QJsonDocument::fromJson(reply->readAll());
        QJsonArray jsonArray = json.array();

        for(int i = 0; i < jsonArray.size(); i++) {
            QJsonObject jsonObject = jsonArray[i].toObject();
            resp_accounts_get::data data;
            data.number = jsonObject["identifier"].toString();
            data.name = jsonObject["name"].toString();
            data.value = jsonObject["balance"].toInt();
            data.isBlocked = jsonObject["isBlocked"].toBool();

            result.datas.push_back(data);
        }

        // parse accounts;

        return result;
    }

    Api::resp_accounts_add Api::AccountsAdd(const QString &token, const QString &name) {
        Api::resp_accounts_add result;

        QNetworkRequest req;
        req.setUrl(QUrl(m_url_base + "accounts"));
        req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        req.setRawHeader("Accept", "*/*");
        req.setRawHeader("Authorization", QByteArray((QString("Bearer ") + token).toStdString().data()));

        QJsonObject json;
        json["name"] = name;
        json["currency"] = "USD";
        QNetworkReply *reply = m_manager->post(req, QJsonDocument(json).toJson());

        QEventLoop loop;
        QObject::connect(m_manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
        loop.exec();

        result.code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();

        return result;
    }

    Api::resp_accounts_remove Api::AccountsRemove(const QString &number, const QString &token) {
        Api::resp_accounts_remove result;

        QNetworkRequest req;
        req.setUrl(QUrl(m_url_base + "accounts/" + number));
        req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        req.setRawHeader("Accept", "*/*");
        req.setRawHeader("Authorization", QByteArray((QString("Bearer ") + token).toStdString().data()));

        QNetworkReply *reply = m_manager->deleteResource(req);

        QEventLoop loop;
        QObject::connect(m_manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
        loop.exec();

        result.code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();

        return result;
    }

    Api::resp_cards_get Api::CardsGet(const QString &token) {
        Api::resp_cards_get result;

        QNetworkRequest req;
        req.setUrl(QUrl(m_url_base + "cards"));
        req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        req.setRawHeader("Accept", "*/*");
        req.setRawHeader("Authorization", QByteArray((QString("Bearer ") + token).toStdString().data()));

        QNetworkReply *reply = m_manager->get(req);

        QEventLoop loop;
        QObject::connect(m_manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
        loop.exec();

        result.code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();

        auto json = QJsonDocument::fromJson(reply->readAll());
        QJsonArray jsonArray = json.array();

        for(auto && i : jsonArray) {
            QJsonObject jsonObject = i.toObject();
            resp_cards_get::data data;
            data.number = jsonObject["lastFourDigits"].toString();
            data.id = jsonObject["hashId"].toString();
            data.date = jsonObject["validityPeriod"].toString();
            data.isBlocked = jsonObject["isBlocked"].toBool();

            result.datas.push_back(data);
        }

        return result;
    }

    Api::resp_cards_add Api::CardsAdd(const QString &token) {
        Api::resp_cards_add result;
        QNetworkRequest req;
        req.setUrl(QUrl(m_url_base + "cards"));
        req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        req.setRawHeader("Accept", "*/*");
        req.setRawHeader("Authorization", QByteArray((QString("Bearer ") + token).toStdString().data()));

        QJsonObject json;
        json["currency"] = "USD";
        QNetworkReply *reply = m_manager->post(req, QJsonDocument(json).toJson());

        QEventLoop loop;
        QObject::connect(m_manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
        loop.exec();

        result.code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();

        return result;
    }

    Api::resp_cards_details_get Api::CardsGetDetails(const QString &id, const QString &token) {
        Api::resp_cards_details_get result;

        QNetworkRequest req;
        req.setUrl(QUrl(m_url_base + "cards/" + id));
        req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        req.setRawHeader("Accept", "*/*");
        req.setRawHeader("Authorization", QByteArray((QString("Bearer ") + token).toStdString().data()));

        QNetworkReply *reply = m_manager->get(req);

        QEventLoop loop;
        QObject::connect(m_manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
        loop.exec();

        result.code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();

        auto json = QJsonDocument::fromJson(reply->readAll());
        QJsonArray jsonArray = json.array();

        QJsonObject jsonObject = json.object();
        resp_cards_details_get data;
        data.number = jsonObject["fullNumber"].toString();
        data.date = jsonObject["validityPeriod"].toString();
        data.cvv = jsonObject["cvv"].toString();
        data.value = jsonObject["balance"].toInt();

        return result;
    }

    Api::resp_cards_remove Api::CardsRemove(const QString &id, const QString &token) {
        Api::resp_cards_remove result;

        QNetworkRequest req;
        req.setUrl(QUrl(m_url_base + "cards/" + id));
        req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        req.setRawHeader("Accept", "*/*");
        req.setRawHeader("Authorization", QByteArray((QString("Bearer ") + token).toStdString().data()));

        QNetworkReply *reply = m_manager->deleteResource(req);

        QEventLoop loop;
        QObject::connect(m_manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
        loop.exec();

        result.code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();
        return result;
    }

    // Получение кредита процент срок
    // Выплата кредита

} // backend