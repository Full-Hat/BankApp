//
// Created by Full-Hat on 08/12/2023.
//

#pragma once

#include "backend/Api.hpp"

#include <QObject>

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
};

class CreditsArray : public QObject {
Q_OBJECT

protected:

    Q_PROPERTY(QList<QObject*> cards READ getCredits)
    QList<std::shared_ptr<Credit>> backend_cards;

    Q_PROPERTY(QString currentCreditNumber READ getCreditNumber WRITE setCreditNumber)
    QString currentCreditNumber;

    QList<std::shared_ptr<Credit>> history;

public:
    using QML_MapList = QList<QMap<QString, QString>>;

    CreditsArray(QObject *parent = nullptr);

    [[nodiscard]]
    QString getCreditNumber() const { return currentCreditNumber; };
    void setCreditNumber(const QString &cardNumber) { currentCreditNumber = cardNumber; };

    // Iterated through array to get pointers, need to be cached
    [[nodiscard]]
    QList<QObject*> getCredits();

    std::shared_ptr<Credit> getByNum(QString number);

public slots:
    void onCreditsChanged(QList<QObject*> credits, bool saveCurrent);
    void onCurrentCreditUpdate(const QString& newNumber);

signals:
    void showWarning(QString message);

protected:
    mutable backend::Api m_backend;
};
