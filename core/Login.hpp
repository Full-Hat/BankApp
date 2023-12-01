//
// Created by System Administrator on 11/9/23.
//
#pragma once

#include <QObject>

#include "backend/Api.hpp"

class Login : public QObject {
    Q_OBJECT

public slots:
    // User try to login
    void OnLogin(const QString& Login, const QString& Password);

signals:
    // Responses for login operation
    void loginCorrect();
    void loginFailed(QString Description);

protected:
    backend::Api m_backend;
};

class LoginCode : public QObject {
    Q_OBJECT

public slots:
    void OnLogin(const QString& Code);

signals:
    void loginCorrect();
    void loginFailed(QString description);

protected:
    backend::Api m_backend;
};
