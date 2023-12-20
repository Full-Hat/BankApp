//
// Created by Full-Hat on 20/12/2023.
//

#pragma once

#include <QObject>

#include "backend/Api.hpp"

class Bonus : public QObject {
Q_OBJECT

    Q_PROPERTY(QString currency READ getCurrency WRITE setCurrency)
    Q_PROPERTY(double sum READ getSum WRITE setSum)
public:
    QString currency;
    double sum;

    [[nodiscard]]
    QString getCurrency() const { return currency; }
    void setCurrency(const QString &newCurrency) { currency = newCurrency; }

    [[nodiscard]]
    double getSum() const { return sum; }
    void setSum(double newSum) { sum = newSum; }

    Bonus(const QString &initialCurrency = QString(), double initialSum = 0.0, QObject *parent = nullptr)
            : QObject(parent), currency(initialCurrency), sum(initialSum) {}
};

class BonusSecond : public QObject {
Q_OBJECT
    Q_PROPERTY(double sum READ getSum WRITE setSum)
    Q_PROPERTY(int day READ getDay WRITE setDay)
    Q_PROPERTY(QString account READ getAccount WRITE setAccount)
    Q_PROPERTY(double monthly_sum READ getMonthlySum WRITE setMonthlySum)

private:
    double sum;
    int day;
    QString account;
    double monthly_sum;

public:
    // Constructor with parameters
    BonusSecond(double initialSum = 0.0, int initialDay = 0, const QString& initialAccount = QString(), double initialMonthlySum = 0.0, QObject* parent = nullptr)
            : QObject(parent), sum(initialSum), day(initialDay), account(initialAccount), monthly_sum(initialMonthlySum) {}

    // Getters with [[nodiscard]]
    [[nodiscard]]
    double getSum() const { return sum; }

    [[nodiscard]]
    int getDay() const { return day; }

    [[nodiscard]]
    QString getAccount() const { return account; }

    [[nodiscard]]
    double getMonthlySum() const { return monthly_sum; }

    // Setters
    void setSum(double newSum) { sum = newSum; }
    void setDay(int newDay) { day = newDay; }
    void setAccount(const QString& newAccount) { account = newAccount; }
    void setMonthlySum(double newMonthlySum) { monthly_sum = newMonthlySum; }
};

class BonusView : public QObject {
Q_OBJECT

public:
    BonusView(QObject* parent = nullptr) : QObject(parent) {}

    // Using shared pointers for Bonus and BonusSecond
    using BonusPtr = std::shared_ptr<Bonus>;
    using BonusSecondPtr = std::shared_ptr<BonusSecond>;

    // Arrays of shared pointers
    BonusPtr bonusArray;
    QVector<BonusSecondPtr> bonusSecondArray;

public slots:
    // Slot to update the currency and emit the updateCurrency signal
    void onUpdateCurrency(const QString& newCurrency);
    void onAddBonus(QString currency, QString sum);
    void onBonusDecondAdd(double sum, int day, double amt, const QString& selectedBill);

    void onUpdate(QString currency = "USD");

signals:
    // Signal to show a warning message
    void showWarning(const QString& message);

    void bonusesChanges(QList<QObject*> objs, QObject *obj);

public:
    backend::Api m_backend;
};
