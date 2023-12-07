//
// Created by System Administrator on 11/9/23.
//

#include <iostream>

#include "Login.hpp"

#include "User.hpp"

void Login::OnLogin(const QString& Login, const QString& Password) {
    std::cout << "User try to login login [" << Login.toStdString() <<
        "] password [" << Password.toStdString() << "]" << std::endl;

    auto res = m_backend.LoginBegin(Login, Password);
    if (res.error_code != 200) {
        emit loginFailed(res.error_message);
        return;
    }

    CurrentUser::Get().SetLogin(Login);
    // 200 -> Go to code entering
    emit loginCorrect();
    // code -> !correct -> error -> correct -> login
    // !200 -> error message
}

void LoginCode::OnLogin(const QString &Code) {
    std::cout << "User try to login code [" << Code.toStdString() << "]" << std::endl;

    auto res = m_backend.LoginConfirm(CurrentUser::Get().GetLogin(), Code);
    if (res.error_code != 200) {
        emit loginFailed(res.error_message);
        return;
    }

    CurrentUser::Get().SetToken(res.token);
    std::cout << "Token " << CurrentUser::Get().GetToken().toStdString() << std::endl;
    emit loginCorrect();
}
