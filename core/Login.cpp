//
// Created by System Administrator on 11/9/23.
//

#include <iostream>

#include "Login.h"

#include "User.hpp"

void Login::OnLogin(const QString& Login, const QString& Password) {
    std::cout << "User try to login login [" << Login.toStdString() <<
        "] password [" << Password.toStdString() << "]" << std::endl;

    CurrentUser::Get().SetLogin(Login);
}

void LoginCode::OnLogin(const QString &Code) {
    std::cout << "User try to login code [" << Code.toStdString() << "]" << std::endl;

    if (std::rand()) {
        LoginCorrect();
    }
    else {
        LoginFailed(QString::fromStdString(std::to_string(std::rand())));
    }
}
