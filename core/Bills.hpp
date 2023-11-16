//
// Created by System Administrator on 11/16/23.
//

#pragma once

#include <QObject>

class Bills : public QObject{
    Q_OBJECT

public slots:
    void onBillChoosed(QString id);

    void onTransfer(QString target_number);

    //void onBlocked();
signals:
    void addBill(int id);
    void removeBill(int id);
};
