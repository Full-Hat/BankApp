//
// Created by System Administrator on 11/13/23.
//

#pragma once

#include <QObject>
#include <QList>
#include <QMap>
#include <QQmlListProperty>
#include <QQmlPropertyMap>

#include <ranges>
#include <algorithm>
#include <vector>
#include <exception>
#include <memory>

#include "History.hpp"
#include "backend/Api.hpp"
#include "User.hpp"

/*!
 * @brief Manage one card instance
 *
 * number -- number of the card & id
 * value -- current balance
 * isBlocked -- is it enabled for editing
 */
class Card : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString id READ getId WRITE setId)
    QString id;
    Q_PROPERTY(QString number READ getNumber WRITE setNumber)
    QString number;
    Q_PROPERTY(QString date READ getDate WRITE setDate)
    QString date;
    Q_PROPERTY(bool isBlocked READ getIsBlocked WRITE setIsBlocked)
    bool isBlocked;

    // Write

public:
    Card(QString id, QString number, QString date, bool isBlocked = false) {
        this->id = id;
        this->number = number;
        this->date = date;
        this->isBlocked = isBlocked;
    }

    [[nodiscard]]
    QString getId() const { return id; }
    void setId(const QString &value) { id = value; }

    [[nodiscard]]
    QString getNumber() const { return number; };
    void setNumber(QString number) { this->number = number; };

    [[nodiscard]]
    QString getDate() const { return date; }
    void setDate(const QString &value) { date = value; }

    [[nodiscard]]
    bool getIsBlocked() const { return isBlocked; };
    void setIsBlocked(bool isBlocked) { this->isBlocked = isBlocked; };
};

class CardsArray : public QObject {
    Q_OBJECT

protected:

    Q_PROPERTY(QList<QObject*> cards READ getCards)
    QList<std::shared_ptr<Card>> backend_cards;

    Q_PROPERTY(QString currentCardNumber READ getCardNumber WRITE setCardNumber)
    QString currentCardNumber;

    QList<std::shared_ptr<History>> history;

public:
    using QML_MapList = QList<QMap<QString, QString>>;

    CardsArray(QObject *parent = nullptr);

    [[nodiscard]]
    QString getCardNumber() const { return currentCardNumber; };
    void setCardNumber(const QString &cardNumber) { currentCardNumber = cardNumber; };

    // Iterated through array to get pointers, need to be cached
    [[nodiscard]]
    QList<QObject*> getCards();

    Q_INVOKABLE
    [[nodiscard]]
    QList<QObject*> getHistory(const QString &target);

    void printCards();

    std::shared_ptr<Card> getByNum(QString number);

public slots:
    void onCurrentCardUpdate(const QString& newNumber);

    void onCardTransfer(const QString &target, double value);
    void onBillTransfer(const QString &target, double value);
    void onBlocked(bool isBlocked);

    void onDetails();

    void onHistory(const QString &target);

    void onRemoveCard(const QString &target);
    void onAddCard();

    void onUpdate();
signals:
    void cardsCardsChanged(QList<QObject*> cards, bool saveCurrent);
    void updateHistory(QList<QObject*> history);
    void cardsDetails(uint16_t code, QString number, QString date, QString cvv, uint32_t value);

protected:
    mutable backend::Api m_backend;
};
