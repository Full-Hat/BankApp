//
// Created by System Administrator on 11/9/23.
//

#include <iostream>

#include "Login.h"

void Login::OnLogin(const QString& Login, const QString& Password) {
    std::cout << "User try to login login [" << Login.toStdString() <<
        "] password [" << Password.toStdString() << "]" << std::endl;
}
