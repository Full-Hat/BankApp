//
// Created by System Administrator on 11/30/23.
//

#pragma once

#include <QtNetwork>
#include <QApplication>

namespace backend {

class Api : public QObject {
    Q_OBJECT
public:
    Api();
    void testConnection();

    struct Request {
        Request() {
            m_manager = new QNetworkAccessManager;
            m_request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
            m_request.setRawHeader("Accept", "*/*");
            m_request.setTransferTimeout(100);
        }

        ~Request() {
            delete m_manager;
        }

        virtual QNetworkReply* send() = 0;
        void SetUrl(const QString &url) {
            m_request.setUrl(QUrl(url));
        }

        QNetworkRequest m_request;
        QNetworkAccessManager *m_manager;
        QJsonObject m_json;
    };

    struct Post : public Request {
        virtual QNetworkReply* send() override {
            QNetworkReply *reply = m_manager->post(m_request, QJsonDocument(m_json).toJson());

            QEventLoop loop;
            QObject::connect(m_manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
            loop.exec();

            return reply;
        }
    };

    struct Get : public Request {
        virtual QNetworkReply* send() override {
            QNetworkReply *reply = m_manager->get(m_request);

            QEventLoop loop;
            QObject::connect(m_manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
            loop.exec();

            return reply;
        }
    };

    struct Delete : public Request {
        virtual QNetworkReply* send() override {
            QNetworkReply *reply = m_manager->deleteResource(m_request);

            QEventLoop loop;
            QObject::connect(m_manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
            loop.exec();

            return reply;
        }
    };

    struct Put : public Request {
        virtual QNetworkReply* send() override {
            QNetworkReply *reply = m_manager->put(m_request, QJsonDocument(m_json).toJson());

            QEventLoop loop;
            QObject::connect(m_manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
            loop.exec();

            return reply;
        }
    };

    QNetworkRequest GetDefaultHeader();

    struct resp_register_beg {
        QString error_message;
        uint16_t error_code;
    };

    [[nodiscard]]
    resp_register_beg RegisterBegin(const QString &login, const QString &email, const QString &password);

    struct resp_register_confirm {
        QString error_message;
        uint16_t error_code;
        QString token;
    };

    resp_register_confirm RegisterConfirm(const QString &login, const QString &code);

    struct resp_login_beg {
        QString error_message;
        uint16_t error_code;
    };

    [[nodiscard]]
    resp_login_beg LoginBegin(const QString &login, const QString &password);

    struct resp_login_confirm {
        QString error_message;
        uint16_t error_code;
        QString token;
    };

    [[nodiscard]]
    resp_login_confirm LoginConfirm(const QString &login, const QString &code);

    struct resp_accounts_get {
        uint16_t code;

        struct data {
            QString name;
            QString number;
            size_t value;
            bool isBlocked;
        };
        std::vector<data> datas;
    };

    [[nodiscard]]
    resp_accounts_get AccountsGet(const QString &token);

    [[nodiscard]]
    uint16_t AccountsAdd(const QString &token, const QString &name);

    [[nodiscard]]
    uint16_t AccountsRemove(const QString &number, const QString &token);

    struct resp_cards_get {
        uint16_t code;

        struct data {
            QString id;
            QString number;
            QString date;
            bool isBlocked;
        };
        std::vector<data> datas;
    };

    [[nodiscard]]
    resp_cards_get CardsGet(const QString &token);

    [[nodiscard]]
    uint16_t CardsAdd(const QString &token);

    struct resp_cards_details_get {
        uint16_t code;
        QString number;
        QString date;
        QString cvv;
        uint32_t value;
    };

    [[nodiscard]]
    resp_cards_details_get CardsGetDetails(const QString &id, const QString &token);

    [[nodiscard]]
    uint16_t CardsRemove(const QString &number, const QString &token);

    [[nodiscard]]
    uint16_t AccountBlock(const QString &id, const QString &token);

    [[nodiscard]]
    uint16_t CardsBlock(const QString &id, const QString &token);

    [[nodiscard]]
    uint16_t TransferAccountToAccount(const QString &source, const QString &target, double value, const QString &token);

    [[nodiscard]]
    uint16_t TransferCardToAccount(const QString &source, const QString &target, double value, const QString &token);

    [[nodiscard]]
    uint16_t TransferCardToCard(const QString &source, const QString &target, double value, const QString &token);

    struct resp_history {
        uint16_t code;

        struct data {
            QString source;
            QString target;
            double value;
            QString date;
        };
        std::vector<data> datas;
    };

    [[nodiscard]]
    resp_history History(const QString &token);

protected:
    void CheckForError(QNetworkReply &reply);

protected:
    QNetworkAccessManager *m_manager;

    QString m_url_base = "http://localhost/api/";
    uint16_t m_port = 80;

    QString m_last_error = "";

public:
    const QString &getLastError() const;
};

} // backend
