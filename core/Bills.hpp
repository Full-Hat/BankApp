//
// Created by System Administrator on 11/16/23.
//

#pragma once

#include <QObject>

#include "History.hpp"
#include "backend/Api.hpp"
#include "User.hpp"

#define ApiObj backend::Api


/*!
 * @brief Manage one bill instance
 *
 * number -- number of the bill & id
 * value -- current balance
 * isBlocked -- is it enabled for editing
 */
class Bill : public QObject {
Q_OBJECT

    Q_PROPERTY(QString number READ getNumber WRITE setNumber)
    QString number;
    Q_PROPERTY(double value READ getValue WRITE setValue)
    double value;
    Q_PROPERTY(bool isBlocked READ getIsBlocked WRITE setIsBlocked)
    bool isBlocked;
    Q_PROPERTY(QString name READ getName WRITE setName)
    QString name;
    Q_PROPERTY(QString currency READ getCurrency WRITE setCurrency)
    QString currency;

public:
    Bill(QString number, double  value, QString name, QString currency, bool isBlocked = false) {
        this->number = number;
        this->value = value;
        this->name = name;
        this->currency = currency;
        this->isBlocked = isBlocked;
    }

    [[nodiscard]]
    QString getNumber() const { return number; };
    void setNumber(QString number) { this->number = number; };

    [[nodiscard]]
    double getValue() const { return value; };
    void setValue(double value) { this->value = value; };

    [[nodiscard]]
    bool getIsBlocked() const { return isBlocked; };
    void setIsBlocked(bool isBlocked) { this->isBlocked = isBlocked; };

    [[nodiscard]]
    QString getName() const { return name; };
    void setName(QString name) { this->name = name; };

    [[nodiscard]]
    QString getCurrency() const { return currency; }
    void setCurrency(const QString &currency) { this->currency = currency; }
};

class Bills : public QObject{
    Q_OBJECT

protected:

    Q_PROPERTY(QList<QObject*> bills READ getBills)
    QList<std::shared_ptr<Bill>> backend_bills;

    Q_PROPERTY(QString currentBillNumber READ getBillNumber WRITE setBillNumber)
    QString currentBillNumber;

    QList<std::shared_ptr<History>> history;

public:
    using QML_MapList = QList<QMap<QString, QString>>;

    Bills(QObject *parent = nullptr);

    [[nodiscard]]
    QString getBillNumber() const { return currentBillNumber; };
    void setBillNumber(const QString &BillNumber) { currentBillNumber = BillNumber; };

    // Iterated through array to get pointers, need to be cached
    [[nodiscard]]
    QList<QObject*> getBills();

    Q_INVOKABLE
    [[nodiscard]]
    QList<QObject*> getHistory(const QString &target);

    void printBills();

    std::shared_ptr<Bill> getByNum(QString number);

public slots:
    void onCurrentBillUpdate(const QString newNumber);

    void onBillTransfer(const QString &target, const double value);
    void onBlocked(bool isBlocked);

    void onHistory(const QString &target);

    void onRemoveBill(const QString &target);
    void onAddBill(const QString &name, const QString &currency);

    void onUpdate();
signals:
    void billsChanged(QList<QObject*> cards, bool saveCurrent);
    void updateHistory(QList<QObject*> history);
    void showWarning(QString message);
    void showHistory();
    void currencyUpdateSignal(QList<QObject*> objs);

protected:
    mutable ApiObj *m_backend = new backend::Api();
};
