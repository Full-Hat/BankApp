//
// Created by System Administrator on 11/13/23.
//

#include "Bills.hpp"

#include <iostream>

std::shared_ptr<Bill> Bills::getByNum(QString number) {
    auto res = std::ranges::find_if(backend_bills, [&](const std::shared_ptr<Bill> &el) { return el->getNumber() == number; });
    if (res == backend_bills.cend()) {
        throw std::invalid_argument("Wrong bill number");
    }

    return *res;
}

QList<QObject *> Bills::getBills() {
    QList<QObject *> qmlBills(backend_bills.size());
    for (int i = 0; i < backend_bills.size(); ++i) {
        qmlBills[i] = static_cast<QObject*>(backend_bills[i].get());
    }

    return qmlBills;
}

void Bills::onCurrentBillUpdate(const QString newNumber) {
    std::cout << "[backend] " << "change bill to " << newNumber.toStdString() << std::endl;
    this->currentBillNumber = newNumber;
}

void Bills::onBillTransfer(const QString &target) {
    std::cout << "[backend] Transfer from bill to bill from " <<
              currentBillNumber.toStdString() <<
              " to " << target.toStdString() << std::endl;
    emit billsChanged(getBills(), true);
}

void Bills::onBlocked(bool block) {
    std::cout << "[backend] " << (block ? "Block" : "Unblock") << " bill " <<
              currentBillNumber.toStdString() << std::endl;
    this->getByNum(currentBillNumber)->setIsBlocked(block);
    emit billsChanged(getBills(), true);
}

void Bills::onHistory(const QString &target) {
    std::cout << "[backend] Bill history requested bill " << target.toStdString() << std::endl;

    emit updateHistory(getHistory(target));
}

Bills::Bills(QObject *parent) : QObject(parent) {
    Bill *newBill = new Bill(QString("** 3456"), 1000, false);
    backend_bills.push_back(std::shared_ptr<Bill>(newBill));
    newBill = new Bill(QString("** 23w"), 1000, false);
    backend_bills.push_back(std::shared_ptr<Bill>(newBill));

    History *newHistory = new History;
    newHistory->source = "forum.qt.io";
    newHistory->target = "Target 1";
    newHistory->value = 10;
    history.push_back(std::shared_ptr<History>(newHistory));

    newBill = backend_bills[0].get();
    std::cout << "ejfowopef" << ((Bill*)getBills()[0])->getNumber().toStdString() << std::endl;
}

void Bills::printBills() {
    auto bills = getBills();
    std::cout << "Bill data: " << std::endl;
    for (QObject* el : bills)
    {
        Bill *bill = static_cast<Bill*>(el);
        std::cout << "Number " << bill->getNumber().toStdString() << std::endl;
    }
    std::cout << "~~~" << std::endl;
}

QList<QObject *> Bills::getHistory(const QString &target) const {
    QList<QObject*> history;
    history.reserve(this->history.size());

    for (auto el : this->history) {
        history.push_back(el.get());
    }

    return history;
}

void Bills::onRemoveBill(const QString &target) {
    std::cout << "[backend] " << "bill removed bill " << target.toStdString() << std::endl;
    std::ranges::remove_if(backend_bills, [&](std::shared_ptr<Bill> el) { return el->getNumber() == target; });
    backend_bills.pop_back();

    emit billsChanged(getBills(), false);
}

void Bills::onAddBill() {
    std::cout << "[backend] " << "bill added" << std::endl;
    backend_bills.push_back(std::make_shared<Bill>("** jief", 10, false));
    emit billsChanged(getBills(), false);
}
