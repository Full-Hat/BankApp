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
    auto res = m_backend.AccountsGet(CurrentUser::Get().GetToken());
    if (res.code != 200) {
        return {};
    }
    backend_bills.clear();
    for(const auto& data : res.datas) {
        std::shared_ptr<Bill> bill = std::make_shared<Bill>(data.number, data.value, data.isBlocked);
        backend_bills.append(bill);
    }

    // to Bills QList<std::shared_ptr<Bill>>
    //std::cout << res.code << std::endl;
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

    auto code = m_backend.TransferAccountToAccount(currentBillNumber, target, 1, CurrentUser::Get().GetToken());
    assert(code == 200);

    emit billsChanged(getBills(), true);
}

void Bills::onBlocked(bool block) {
    std::cout << "[backend] " << (block ? "Block" : "Unblock") << " bill " <<
              currentBillNumber.toStdString() << std::endl;

    auto code = m_backend.AccountBlock(this->getByNum(currentBillNumber)->getNumber(), CurrentUser::Get().GetToken());
    assert(code == 200);

    emit billsChanged(getBills(), true);
}

void Bills::onHistory(const QString &target) {
    std::cout << "[backend] Bill history requested bill " << target.toStdString() << std::endl;

    emit updateHistory(getHistory(target));
}

Bills::Bills(QObject *parent) : QObject(parent) {
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

    auto code = m_backend.AccountsRemove(target, CurrentUser::Get().GetToken());
    assert(code == 200);

    emit billsChanged(getBills(), false);
}

void Bills::onAddBill(const QString &name) {
    std::cout << "[backend] " << "bill added" << std::endl;
    m_backend.AccountsAdd(CurrentUser::Get().GetToken(), name);
    emit billsChanged(getBills(), false);
}

void Bills::onUpdate() {
    emit billsChanged(getBills(), false);
}
