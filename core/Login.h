//
// Created by System Administrator on 11/9/23.
//
#pragma once

#include <QObject>

class Login : public QObject {
    Q_OBJECT

public slots:
    // User try to login
    void OnLogin(const QString& Login, const QString& Password);

signals:
    // Responses for login operation
    void LoginCorrect();
    void LoginFailed(QString Description);
};

class LoginCode : public QObject {
    Q_OBJECT

public slots:
    void OnLogin(const QString& Code);

signals:
    void LoginCorrect();
    void LoginFailed(QString Description);
};
