//
// Created by System Administrator on 11/30/23.
//

#include "Api.hpp"

#include <iostream>
#include <sstream>

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

    Post req;
    req.SetUrl(m_url_base + "register/begin");

    req.m_json["login"] = login;
    req.m_json["email"] = email;
    req.m_json["password"] = password;

    auto reply = req.send();

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

    Post req;
    req.SetUrl(m_url_base + "register/confirm");

    req.m_json["login"] = login;
    req.m_json["code"] = code;

    auto reply = req.send();

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

    Post req;
    req.SetUrl(m_url_base + "login/begin");

    req.m_json["login"] = login;
    req.m_json["password"] = password;

    auto reply = req.send();

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

    Post req;
    req.SetUrl(m_url_base + "login/confirm");

    QJsonObject json;
    json["login"] = login;
    json["code"] = code;

    auto reply = req.send();

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

        Get req;
        req.SetUrl(m_url_base + "accounts");
        req.m_request.setRawHeader("Authorization", QByteArray((QString("Bearer ") + token).toStdString().data()));

        auto reply = req.send();
        CheckForError(*reply);

        result.code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();

        auto json = QJsonDocument::fromJson(reply->readAll());
        QJsonArray jsonArray = json.array();

        // parse accounts;
        for(int i = 0; i < jsonArray.size(); i++) {
            QJsonObject jsonObject = jsonArray[i].toObject();
            resp_accounts_get::data data;
            data.number = jsonObject["identifier"].toString();
            data.name = jsonObject["name"].toString();
            data.value = jsonObject["balance"].toDouble();
            data.isBlocked = jsonObject["isBlocked"].toBool();
            data.currency = jsonObject["currency"].toString();

            result.datas.push_back(data);
        }

        return result;
    }

    uint16_t Api::AccountsAdd(const QString &token, const QString &name, const QString &currency) {
        Post req;
        req.SetUrl(m_url_base + "accounts");
        req.m_request.setRawHeader("Authorization", QByteArray((QString("Bearer ") + token).toStdString().data()));

        req.m_json["name"] = name;
        req.m_json["currency"] = currency;

        auto reply = req.send();

        CheckForError(*reply);

        return reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();
    }

    uint16_t Api::AccountsRemove(const QString &number, const QString &token) {
        Delete req;
        req.SetUrl(m_url_base + "accounts/" + number);
        req.m_request.setRawHeader("Authorization", QByteArray((QString("Bearer ") + token).toStdString().data()));

        auto reply = req.send();
        CheckForError(*reply);

        return reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();
    }

    Api::resp_cards_get Api::CardsGet(const QString &token) {
        Api::resp_cards_get result;

        Get req;
        req.SetUrl(m_url_base + "cards");
        req.m_request.setRawHeader("Authorization", QByteArray((QString("Bearer ") + token).toStdString().data()));

        auto reply = req.send();
        CheckForError(*reply);

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

    uint16_t Api::CardsAdd(const QString &token, QString currency) {
        Post req;
        req.SetUrl(m_url_base + "cards");
        req.m_request.setRawHeader("Authorization", QByteArray((QString("Bearer ") + token).toStdString().data()));

        req.m_json["currency"] = currency;

        auto reply = req.send();
        CheckForError(*reply);

        return reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();
    }

    Api::resp_cards_details_get Api::CardsGetDetails(const QString &id, const QString &token) {
        Api::resp_cards_details_get result;

        Get req;
        req.SetUrl(m_url_base + "cards/" + id);
        req.m_request.setRawHeader("Authorization", QByteArray((QString("Bearer ") + token).toStdString().data()));

        auto reply = req.send();
        CheckForError(*reply);

        result.code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();

        auto json = QJsonDocument::fromJson(reply->readAll());
        QJsonArray jsonArray = json.array();

        QJsonObject jsonObject = json.object();
        result.number = jsonObject["number"].toString();
        result.date = jsonObject["validityPeriod"].toString();
        result.cvv = jsonObject["cvv"].toString();
        result.value = jsonObject["balance"].toDouble();

        return result;
    }

    uint16_t Api::CardsRemove(const QString &number, const QString &token) {
        Delete req;
        req.SetUrl(m_url_base + "cards/" + number);
        req.m_request.setRawHeader("Authorization", QByteArray((QString("Bearer ") + token).toStdString().data()));

        auto reply = req.send();
        CheckForError(*reply);

        return reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();
    }

    uint16_t Api::AccountBlock(const QString &id, const QString &token) {
        Put req;
        req.SetUrl(m_url_base + "accounts/flip-block-state/" + id);
        req.m_request.setRawHeader("Authorization", QByteArray((QString("Bearer ") + token).toStdString().data()));

        auto reply = req.send();
        CheckForError(*reply);

        return reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();
    }

    uint16_t Api::CardsBlock(const QString &id, const QString &token) {
        Put req;
        req.SetUrl(m_url_base + "cards/flip-block-state/" + id);
        req.m_request.setRawHeader("Authorization", QByteArray((QString("Bearer ") + token).toStdString().data()));

        auto reply = req.send();
        CheckForError(*reply);

        return reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();
    }

    uint16_t Api::TransferAccountToAccount(const QString &source, const QString &target, double value, const QString &token) {
        Post req;
        req.SetUrl(m_url_base + "transactions/account-to-account");
        req.m_request.setRawHeader("Authorization", QByteArray((QString("Bearer ") + token).toStdString().data()));

        req.m_json["from"] = source;
        req.m_json["to"] = target;
        std::stringstream str;
        str << std::fixed << std::setprecision(2) << value;
        req.m_json["value"] = QString::fromStdString(str.str());

        auto reply = req.send();
        CheckForError(*reply);

        return reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();
    }

    Api::resp_history Api::History(const QString &token) {
        Api::resp_history result;

        Get req;
        req.SetUrl(m_url_base + "history");
        req.m_request.setRawHeader("Authorization", QByteArray((QString("Bearer ") + token).toStdString().data()));

        auto reply = req.send();
        CheckForError(*reply);

        result.code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();

        auto json = QJsonDocument::fromJson(reply->readAll());
        QJsonArray array = json.array();
        for(auto && i : array) {
            auto jsonObject = i.toObject();
            Api::resp_history::data res;
            res.date = jsonObject["dateTime"].toString("Undefined");
            res.target = jsonObject["to"].toString("Undefined");
            res.source = jsonObject["from"].toString("Undefined");
            res.value = jsonObject["value"].toDouble(0.0);
            result.datas.push_back(res);
        }

        return result;
    }

    uint16_t Api::TransferCardToAccount(const QString &source, const QString &target, double value, const QString &token) {
        Post req;
        req.SetUrl(m_url_base + "transactions/card-to-account");
        req.m_request.setRawHeader("Authorization", QByteArray((QString("Bearer ") + token).toStdString().data()));

        req.m_json["from"] = source;
        req.m_json["to"] = target;
        std::stringstream str;
        str << std::fixed << std::setprecision(2) << value;
        req.m_json["value"] = QString::fromStdString(str.str());

        auto reply = req.send();
        CheckForError(*reply);

        return reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();
    }

    uint16_t Api::TransferCardToCard(const QString &source, const QString &target, double value, const QString &token) {
        Post req;
        req.SetUrl(m_url_base + "transactions/card-to-card");
        req.m_request.setRawHeader("Authorization", QByteArray((QString("Bearer ") + token).toStdString().data()));

        req.m_json["from"] = source;
        req.m_json["to"] = target;
        std::stringstream str;
        str << std::fixed << std::setprecision(2) << value;
        req.m_json["value"] = QString::fromStdString(str.str());

        auto reply = req.send();
        CheckForError(*reply);

        return reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();
    }

    void Api::CheckForError(QNetworkReply &reply) {
        if (reply.attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt() != 200) {
            m_last_error = QJsonDocument::fromJson(reply.readAll())["error"].toString();
            if (m_last_error == "") {
                m_last_error = "Connection error";
            }
        }
    }

    QString Api::getLastError() const {
        if (!m_last_error.contains('_')) {
            return m_last_error;
        }
        QStringList words = m_last_error.split('_');

        // Convert the first character of each word to lowercase
        for (int i = 0; i < words.size(); ++i) {
            words[i] = words[i].toLower();
        }
        return words.join(' ');
    }

    Api::resp_credits_offerings_get Api::CreditsOfferingsGet(const QString &token) {
        Api::resp_credits_offerings_get result;

        Get req;
        req.SetUrl(m_url_base + "credits/offerings");
        req.m_request.setRawHeader("Authorization", QByteArray((QString("Bearer ") + token).toStdString().data()));

        auto reply = req.send();
        CheckForError(*reply);

        result.code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();

        auto json = QJsonDocument::fromJson(reply->readAll());
        QJsonArray array = json.array();
        for(auto && i : array) {
            auto jsonObject = i.toObject();
            Api::resp_credits_offerings_get::data res;
            res.years = jsonObject["years"].toInt(0);
            res.interestRate = jsonObject["interestRate"].toDouble(0.0);
            result.datas.push_back(res);
        }

        return result;
    }

    Api::resp_credits_get Api::CreditsGet(const QString &token) {
        Api::resp_credits_get result;

        Get req;
        req.SetUrl(m_url_base + "credits");
        req.m_request.setRawHeader("Authorization", QByteArray((QString("Bearer ") + token).toStdString().data()));

        auto reply = req.send();
        CheckForError(*reply);

        result.code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();

        auto json = QJsonDocument::fromJson(reply->readAll());
        QJsonArray array = json.array();
        for(auto && i : array) {
            auto jsonObject = i.toObject();
            Api::resp_credits_get::data res;
            res.hashId = jsonObject["hashId"].toString();
            res.startDate = jsonObject["startDate"].toString();
            res.years = jsonObject["years"].toInt();
            res.interestRate = jsonObject["interestRate"].toDouble();
            res.bodySum = jsonObject["bodySum"].toDouble();
            res.nextPaymentDate = jsonObject["nextPaymentDate"].toString();
            res.nextPaymentSum = jsonObject["nextPaymentSum"].toDouble();
            res.alreadyPaidSum = jsonObject["alreadyPaidSum"].toDouble();
            result.datas.push_back(res);
        }
        CheckForError(*reply);

        return result;
    }

    uint16_t Api::AddCredit(const QString &token, double sum, uint16_t years, QString name) {
        Post req;
        req.SetUrl(m_url_base + "credits");
        req.m_request.setRawHeader("Authorization", QByteArray((QString("Bearer ") + token).toStdString().data()));

        std::stringstream str;
        str << std::fixed << std::setprecision(2) << sum;
        req.m_json["sum"] = QString::fromStdString(str.str());
        req.m_json["accountIdentifier"] = name;
        req.m_json["years"] = years;

        auto reply = req.send();
        CheckForError(*reply);

        QString temp = reply->readAll();
        if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt() == 200 &&
                temp.contains("false")) {
            m_last_error = "Rejected by bank";
            return 500;
        }

        return reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();
    }

    uint16_t Api::PayCredit(const QString &token, const QString &creditHashId, const QString &from) {
        Post req;
        req.SetUrl(m_url_base + "credits/pay");
        req.m_request.setRawHeader("Authorization", QByteArray((QString("Bearer ") + token).toStdString().data()));

        req.m_json["creditHashId"] = creditHashId;
        req.m_json["from"] = from;

        auto reply = req.send();
        CheckForError(*reply);

        return reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();
    }

    Api::resp_documents_get Api::GetDocuments(const QString &token, uint16_t quarter, uint16_t year) {
        resp_documents_get result;

        Get req;
        req.m_request.setRawHeader("Authorization", QByteArray((QString("Bearer ") + token).toStdString().data()));

        QUrl url(m_url_base + "tax-documents");
        QUrlQuery query;

        query.addQueryItem("quarter", QString::number(quarter));
        query.addQueryItem("year", QString::number(year));

        url.setQuery(query);

        req.m_request.setUrl(url);

        auto reply = req.send();
        CheckForError(*reply);

        qDebug() << req.m_request.url();

        result.code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();

        auto json = QJsonDocument::fromJson(reply->readAll());
        for (auto el : json.array()) {
            resp_documents_get::data res;
            auto json = el.toObject();
            res.hashId = json["hashId"].toString();
            res.sum = json["sum"].toInt();
            res.date = json["date"].toString();
            res.kind = json["kind"].toString();
            result.datas.push_back(res);
        }

        return result;
    }

    Api::resp_documents_post Api::PostDocuments(const QString &token, double sum, std::tm date, DocumentKind documentKind) {
        resp_documents_post result;

        Post req;

        std::stringstream date_str;
        date_str << std::put_time(&date, "%Y-%m-%d");

        QString document_kind;
        switch (documentKind) {
            case DocumentKind::ActOfWorkPerformed:
                document_kind = "ActOfWorkPerformed";
                break;
            case DocumentKind::Declaration:
                document_kind = "Declaration";
                break;
            default:
                document_kind = "Error";
        }

        std::stringstream str;
        str << std::fixed << std::setprecision(2) << sum;

        req.SetUrl(m_url_base + "tax-documents");
        req.m_request.setRawHeader("Authorization", QByteArray((QString("Bearer ") + token).toStdString().data()));

        req.m_json["sum"] = QString::fromStdString(str.str());
        req.m_json["date"] = QString::fromStdString(date_str.str());
        req.m_json["documentKind"] = document_kind;

        auto reply = req.send();
        CheckForError(*reply);

        auto json = QJsonDocument::fromJson(reply->readAll());
        result.hashId = json["hashId"].toString();

        result.code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();

        return result;
    }

    uint16_t Api::SendDocument(const QString &token, QString documentHashId, QString filePath) {
        Post req(1);

        req.SetUrl(m_url_base + "tax-documents/upload/" + documentHashId);
        req.m_request.setRawHeader("Authorization", QByteArray((QString("Bearer ") + token).toStdString().data()));

        QHttpMultiPart* multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
        QFile* file = new QFile(QUrl(filePath).toLocalFile());
        if (!file->open(QIODevice::ReadOnly)) {
            qDebug() << "Could not open file!";
            throw std::runtime_error("Can't open filem" + file->errorString().toStdString() + " " + filePath.toStdString());
        }

        QHttpPart filePart;
        filePart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"file\"; filename=\"" + QFileInfo(file->fileName()).fileName() + "\"");
        filePart.setBodyDevice(file);

        multiPart->append(filePart);

        QList<QByteArray> headerList = req.m_request.rawHeaderList();
                foreach(QByteArray head, headerList) {
                qDebug() << head << ":" << req.m_request.rawHeader(head);
            }

        qDebug() << documentHashId;
        qDebug() << filePath;

        auto reply = req.m_manager->post(req.m_request, multiPart);
        QEventLoop loop;
        QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        //QTimer::singleShot(1000, &loop, &QEventLoop::quit);
        loop.exec();

        qDebug() << "send document complete";

        CheckForError(*reply);

        return reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();
        return 200;
    }

    Api::file Api::GetDocument(const QString &token, QString hash) {
        file result;

        Get req;

        req.SetUrl(m_url_base + "tax-documents/download/" + hash);
        req.m_request.setRawHeader("Authorization", QByteArray((QString("Bearer ") + token).toStdString().data()));

        auto reply = req.send();
        CheckForError(*reply);

        QString downloadsPath = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);

        //u"attachment; filename=detailed.pdf; filename*=UTF-8''detailed.pdf"
        auto file_name = QString(reply->rawHeader("content-disposition"));
        QRegularExpression regex("filename=(.*);");
        QRegularExpressionMatch match = regex.match(file_name);
        file_name = match.captured(1);
        QFile file(downloadsPath + "/" + file_name);

        QString filename;
        int i = 1;
        while (file.exists()) {
            QFileInfo inf(file_name);

            filename = QString(downloadsPath + "/" + inf.baseName() + "%1." + inf.suffix()).arg(i);
            file.setFileName(filename);
            ++i;
        }
        if (!file.open(QIODevice::WriteOnly)) {
            qDebug() << "Could not open file!";
            throw std::runtime_error("Can't open file" + file.errorString().toStdString() + file_name.toStdString());
        }

        // Write the response data to the file
        file.write(reply->readAll());

        result.file = reply->rawHeader("content-disposition");
        result.code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();

        return result;
    }

    uint16_t Api::RemoveDocument(const QString &token, const QString &hash) {
        Delete req;
        req.SetUrl(m_url_base + "tax-documents/" + hash);
        req.m_request.setRawHeader("Authorization", QByteArray((QString("Bearer ") + token).toStdString().data()));

        auto reply = req.send();
        CheckForError(*reply);

        return reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();
    }

    Api::resp_currencies Api::GetCurrencies(const QString &token) {
        resp_currencies result;

        Get req;
        req.m_request.setRawHeader("Authorization", QByteArray((QString("Bearer ") + token).toStdString().data()));

        QUrl url(m_url_base + "currencies/list");

        req.m_request.setUrl(url);

        auto reply = req.send();
        CheckForError(*reply);

        qDebug() << req.m_request.url();

        result.code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();

        auto json = QJsonDocument::fromJson(reply->readAll());
        auto &res = result.currencies;
        for (auto el : json.array()) {
            res.push_back(el.toString());
        }

        return result;
    }



    // Получение кредита процент срок
    // Выплата кредита
} // backend