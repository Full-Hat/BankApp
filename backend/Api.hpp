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

protected:
    QNetworkAccessManager *m_manager;

    QString m_url_base = "http://localhost/api/";
    uint16_t m_port = 80;
};

} // backend
