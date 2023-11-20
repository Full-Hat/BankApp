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

/*!
 * @brief Manage one card instance
 *
 * number -- number of the card & id
 * value -- current balance
 * isBlocked -- is it enabled for editing
 */
class Card : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString number READ getNumber WRITE setNumber)
    QString number;
    Q_PROPERTY(size_t value READ getValue WRITE setValue)
    size_t value;
    Q_PROPERTY(bool isBlocked READ getIsBlocked WRITE setIsBlocked)
    bool isBlocked;

public:
    Card(QString number, size_t  value, bool isBlocked = false) {
        this->number = number;
        this->value = value;
        this->isBlocked = isBlocked;
    }

    [[nodiscard]]
    QString getNumber() const { return number; };
    void setNumber(QString number) { this->number = number; };

    [[nodiscard]]
    size_t getValue() const { return value; };
    void setValue(size_t value) { this->value = value; };

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
    QList<QObject*> getHistory(const QString &target) const;

    void printCards();

    std::shared_ptr<Card> getByNum(QString number);

public slots:
    void onCurrentCardUpdate(const QString newNumber);

    void onCardTransfer(const QString &target);
    void onBillTransfer(const QString &target);
    void onBlocked(bool isBlocked);

    void onHistory(const QString &target);

    void onRemoveCard(const QString &target);
    void onAddCard();

    void onUpdate();
signals:
    void cardsCardsChanged(QList<QObject*> cards, bool saveCurrent);
    void updateHistory(QList<QObject*> history);
};
