//
// Created by System Administrator on 11/13/23.
//

#pragma once

#include <QObject>

class Cards : public QObject {
    Q_OBJECT

public slots:
    void onCardChoosed(QString id);

    void onTransfer(QString target_number);

    //void onBlocked();
signals:
    void addCard(int id);
    void removeCard(int id);
};
