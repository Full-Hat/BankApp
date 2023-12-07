//
// Created by System Administrator on 11/10/23.
//

#include "Signup.hpp"

#include <iostream>

#include "core/User.hpp"

void Signup::OnSignup(QString Login, QString Password, QString Email) {
    std::cout << "User try to signup login [" << Login.toStdString() << "] password [" <<
        Password.toStdString() << "]" << std::endl;

    auto res = m_backend.RegisterBegin(Login, Email, Password);
    if (res.error_code != 200) {
        emit signupFailed(res.error_message);
        return;
    }

    CurrentUser::Get().SetLogin(Login);
    // 200 -> Go to code entering
    emit signupCorrect();
    // code -> !correct -> error -> correct -> login
    // !200 -> error message
}

void SignupCode::OnSignup(const QString &Code) {
    std::cout << "User try to login code [" << Code.toStdString() << "]" << std::endl;

    auto res = m_backend.RegisterConfirm(CurrentUser::Get().GetLogin(), Code);
    if (res.error_code != 200) {
        emit signupFailed(res.error_message);
        return;
    }

    CurrentUser::Get().SetToken(res.token);
    std::cout << "Token " << CurrentUser::Get().GetToken().toStdString() << std::endl;
    emit signupCorrect();
}
