//
// Created by System Administrator on 11/10/23.
//
#pragma once

#include <QString>

class User
{
private:
    QString Login;

public:
    Q_PROPERTY(QString login READ GetLogin WRITE SetLogin)

    [[nodiscard]] QString GetLogin() const { return Login; }
    void SetLogin(const QString &NewLogin) { Login = NewLogin; }
};

class CurrentUser
{
protected:
    static User user;
public:
    static User& Get() { return user; }
};

User CurrentUser::user;
