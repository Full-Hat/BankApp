//
// Created by System Administrator on 11/10/23.
//
#pragma once

#include <QString>

class User
{
private:
    QString Login;

    QString Token;

public:
    Q_PROPERTY(QString login READ GetLogin WRITE SetLogin)
    Q_PROPERTY(QString token READ GetToken WRITE SetToken)

    [[nodiscard]] QString GetLogin() const { return Login; }
    void SetLogin(const QString &NewLogin) { Login = NewLogin; }

    [[nodiscard]] QString GetToken() const { return Token; }
    void SetToken(const QString &NewToken) { Token = NewToken; }
};

class CurrentUser
{
protected:
    static User user;
public:
    static User& Get() { return user; }
};
