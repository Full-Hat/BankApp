//
// Created by System Administrator on 11/30/23.
//

#pragma once

#include <QtNetwork>
#include <QApplication>

namespace backend {

//QNetworkRequest GetDefaultHeader(QString &url) {
//    return {};
//}

class Api : public QObject {
    Q_OBJECT
public:
    Api();
    void testConnection();

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

    struct resp_accounts_add {
        uint16_t code;
    };

    [[nodiscard]]
    resp_accounts_add AccountsAdd(const QString &token, const QString &name);

    struct resp_accounts_remove {
        uint16_t code;
    };

    [[nodiscard]]
    resp_accounts_remove AccountsRemove(const QString &number, const QString &token);

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

    struct resp_cards_add {
        uint16_t code;
    };

    [[nodiscard]]
    resp_cards_add CardsAdd(const QString &token);

    struct resp_cards_details_get {
        uint16_t code;
        QString number;
        QString date;
        QString cvv;
        uint32_t value;
    };

    [[nodiscard]]
    resp_cards_details_get CardsGetDetails(const QString &id, const QString &token);

    struct resp_cards_remove {
        uint16_t code;
    };

    [[nodiscard]]
    resp_cards_remove CardsRemove(const QString &number, const QString &token);

protected:
    QNetworkAccessManager *m_manager;

    QString m_url_base = "http://localhost/api/";
    uint16_t m_port = 80;
};

} // backend
