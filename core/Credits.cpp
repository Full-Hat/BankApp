//
// Created by Full-Hat on 08/12/2023.
//

#include "Credits.hpp"

#include "core/User.hpp"

#include <iostream>

Credit::Credit(QString hashId, QString date, int years, double interstrait, double bodySum, double sum,
                 double payedSum, QObject *parent) {
    this->hashId = hashId;
    this->date = date;
    this->years = years;
    this->interstrait = interstrait;
    this->bodySum = bodySum;
    this->sum = sum;
    this->payedSum = payedSum;
}

Credit::Credit(int years, double interstrait, QObject *parent) : QObject(parent) {
    this->years = years;
    this->interstrait = interstrait;
}

Credit::Credit(QObject *parent) : QObject(parent) {
}

QList<QObject *> Credits::getCredits() {
    auto res = m_backend.CreditsGet(CurrentUser::Get().GetToken());
    if (res.code != 200) {
        return {};
    }
    backend_cards.clear();
    for(const auto& data : res.datas) {
        std::shared_ptr<Credit> bill = std::make_shared<Credit>(
                data.hashId,
                data.nextPaymentDate,
                data.years,
                data.interestRate,
                data.bodySum,
                data.alreadyPaidSum,
                data.nextPaymentSum
                );
        backend_cards.append(bill);
    }

    QList<QObject *> qmlCards(backend_cards.size());
    for (int i = 0; i < backend_cards.size(); ++i) {
        qmlCards[i] = static_cast<QObject*>(backend_cards[i].get());
    }

    return qmlCards;
}

//std::shared_ptr<Credit> Credits::getByNum(QString number) {
//    return std::shared_ptr<Credit>();
//}

void Credits::onCurrentCreditUpdate(const QString &newNumber) {
    this->currentCreditNumber = newNumber;
}

void Credits::onAddCredit(double sum, uint16_t years, QString name) {
    if (years == 0) {
        emit showWarning("Wrong values");
        return;
    }

    std::cout << sum << " " << years << std::endl;
    auto code = m_backend.AddCredit(CurrentUser::Get().GetToken(), sum, years, name);

    if (code != 200) {
        emit showWarning(m_backend.getLastError());
        return;
    }

    emit creditsChanged(getCredits(), false);
    emit showOk();
}

void Credits::UpdateInteresRatesEvent() {
    auto offs = m_backend.CreditsOfferingsGet(CurrentUser::Get().GetToken());
    if (offs.code != 200) {
        emit showWarning(m_backend.getLastError());
        return;
    }

    auto &datas = offs.datas;
    using structure_t = backend::Api::resp_credits_offerings_get;
    std::sort(datas.begin(), datas.end(), [](const structure_t::data& a, const structure_t::data& b) {
        return a.interestRate < b.interestRate;
    });

    auto last = std::unique(datas.begin(), datas.end(), [](const structure_t::data& a, const structure_t::data& b) {
        return a.interestRate == b.interestRate;
    });

    datas.erase(last, datas.end());

    percent.clear();
    percent.reserve(offs.datas.size());
    for (auto & data : offs.datas) {
        percent.push_back(std::make_shared<Credit>(data.years, data.interestRate));
    }

    QList<QObject*> objs;
    objs.reserve(percent.size());
    for (auto &el : percent) {
        std::cout << "AAA" << el->getInterstrait() << std::endl;
        objs.push_back(el.get());
    }

    emit updateInterestRates(objs);
}

void Credits::onUpdateDatesEvent() {
    auto offs = m_backend.CreditsOfferingsGet(CurrentUser::Get().GetToken());
    if (offs.code != 200) {
        emit showWarning(m_backend.getLastError());
        return;
    }

    auto &datas = offs.datas;
    using structure_t = backend::Api::resp_credits_offerings_get;
    std::sort(datas.begin(), datas.end(), [](const structure_t::data& a, const structure_t::data& b) {
        return a.years < b.years;
    });

    auto last = std::unique(datas.begin(), datas.end(), [](const structure_t::data& a, const structure_t::data& b) {
        return a.years == b.years;
    });

    datas.erase(last, datas.end());

    years.reserve(offs.datas.size());
    for (auto & data : offs.datas) {
        years.push_back(std::make_shared<Credit>(data.years, data.interestRate));
    }

    QList<QObject*> objs;
    objs.reserve(years.size());
    for (auto &el : years) {
        objs.push_back(el.get());
    }

    emit updateDates(objs);
}

void Credits::onUpdate() {
    UpdateInteresRatesEvent();
    emit creditsChanged(getCredits(), false);
    emit updateBills(bills.getBills());
}

void Credits::onPay(QString from) {
    auto res = m_backend.PayCredit(CurrentUser::Get().GetToken(), currentCreditNumber, from);
    if (res != 200) {
        emit showWarning(m_backend.getLastError());
        return;
    }

    emit creditsChanged(getCredits(), true);
    emit showOk();
}
