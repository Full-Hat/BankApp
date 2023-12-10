//
// Created by Full-Hat on 08/12/2023.
//

#pragma once

#include "backend/Api.hpp"
#include "core/Bills.hpp"

#include <QObject>
#include <memory>

class Credit : public QObject {
    Q_OBJECT

public:
    Q_PROPERTY(QString hashId READ getHashId WRITE setHashId)
    Q_PROPERTY(QString date READ getDate WRITE setDate)
    Q_PROPERTY(int years READ getYears WRITE setYears)
    Q_PROPERTY(double interstrait READ getInterstrait WRITE setInterstrait)
    Q_PROPERTY(double bodySum READ getBodySum WRITE setBodySum)
    Q_PROPERTY(double sum READ getSum WRITE setSum)
    Q_PROPERTY(double payedSum READ getPayedSum WRITE setPayedSum)

private:
    QString hashId;
    QString date;
    int years;
    double interstrait;
    double bodySum;
    double sum;
    double payedSum;

public:
    QString getHashId() const { return hashId; }
    void setHashId(const QString& value) { hashId = value; }
    QString getDate() const { return date; }
    void setDate(const QString& value) { date = value; }
    int getYears() const { return years; }
    void setYears(int value) { years = value; }
    double getInterstrait() const { return interstrait; }
    void setInterstrait(double value) { interstrait = value; }
    double getBodySum() const { return bodySum; }
    void setBodySum(double value) { bodySum = value; }
    double getSum() const { return sum; }
    void setSum(double value) { sum = value; }
    double getPayedSum() const { return payedSum; }
    void setPayedSum(double value) { payedSum = value; }

    Credit(QString hashId, QString date, int years, double interstrait, double bodySum, double sum, double payedSum, QObject* parent = nullptr);
    Credit(int years, double interstrait, QObject* parent = nullptr);
    Credit(QObject* parent = nullptr);
};

class Credits : public QObject {
Q_OBJECT

protected:

    Q_PROPERTY(QList<QObject*> credits READ getCredits)
    QList<std::shared_ptr<Credit>> backend_cards;

    Q_PROPERTY(QString currentCreditNumber READ getCreditNumber WRITE setCreditNumber)
    QString currentCreditNumber;

    QList<std::shared_ptr<Credit>> history;

public:
    using QML_MapList = QList<QMap<QString, QString>>;

    Credits(Bills &bill, QObject *parent = nullptr) : QObject(parent), bills(bill) {}

    [[nodiscard]]
    QString getCreditNumber() const { return currentCreditNumber; };
    void setCreditNumber(const QString &cardNumber) { currentCreditNumber = cardNumber; };

    // Iterated through array to get pointers, need to be cached
    [[nodiscard]]
    QList<QObject*> getCredits();

    //std::shared_ptr<Credit> getByNum(QString number);

    std::vector<std::shared_ptr<Credit>> percent;
    std::vector<std::shared_ptr<Credit>> years;
    Bills& bills;

    void UpdateInteresRatesEvent();

public slots:
    void onCurrentCreditUpdate(const QString& newNumber);

    void onAddCredit(double sum, uint16_t years);

    void onUpdateDatesEvent();

    void onUpdate();

    void onPay(QString from);

signals:
    void creditsChanged(QList<QObject*> credits, bool saveCurrent);
    void showWarning(QString message);
    void updateInterestRates(QList<QObject*> rates);
    void updateDates(QList<QObject*> dates);
    void showOk();
    void updateBills(QList<QObject*> bills);

protected:
    mutable backend::Api m_backend;
};
