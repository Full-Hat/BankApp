//
// Created by System Administrator on 11/9/23.
//

#ifndef BANKAPP_LOGIN_H
#define BANKAPP_LOGIN_H

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

#endif //BANKAPP_LOGIN_H
