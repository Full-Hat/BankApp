//
// Created by System Administrator on 11/10/23.
//

#pragma once

#include <QObject>

class Signup : public QObject {
    Q_OBJECT

public slots:
    void OnSignup(QString Login, QString Password);

signals:
    void signupCorrect();
    void signupFailed(const QString &description);
};
