//
// Created by System Administrator on 11/10/23.
//

#pragma once

#include <QObject>
#include <QtTest/QSignalSpy>

#include <type_traits>

#include "backend/Api.hpp"

//template<backend_t Backend = backend::Api>
class Signup : public QObject {
    Q_OBJECT

public:
    Signup() = default;

public slots:
    void OnSignup(QString Login, QString Password, QString Email);

signals:
    void signupCorrect();
    void signupFailed(const QString &description);

protected:
    backend::Api m_backend;
};

class SignupCode : public QObject {
Q_OBJECT

public slots:
    void OnSignup(const QString& Code);

signals:
    void signupCorrect();
    void signupFailed(QString description);

protected:
    backend::Api m_backend;
};
