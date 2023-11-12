//
// Created by System Administrator on 11/10/23.
//

#include "Signup.hpp"

#include <iostream>

void Signup::OnSignup(QString Login, QString Password) {
    std::cout << "User try to signup login [" << Login.toStdString() << "] password [" <<
        Password.toStdString() << "]" << std::endl;

    emit signupCorrect();
}
