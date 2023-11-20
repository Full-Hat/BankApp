//
// Created by System Administrator on 11/13/23.
//

#include "Cards.hpp"

#include <iostream>

std::shared_ptr<Card> CardsArray::getByNum(QString number) {
    auto res = std::ranges::find_if(backend_cards, [&](const std::shared_ptr<Card> &el) { return el->getNumber() == number; });
    if (res == backend_cards.cend()) {
        throw std::invalid_argument("Wrong card number");
    }

    return *res;
}

QList<QObject *> CardsArray::getCards() {
    QList<QObject *> qmlCards(backend_cards.size());
    for (int i = 0; i < backend_cards.size(); ++i) {
        qmlCards[i] = static_cast<QObject*>(backend_cards[i].get());
    }

    return qmlCards;
}

void CardsArray::onCurrentCardUpdate(const QString newNumber) {
    std::cout << "[backend] " << "change card to " << newNumber.toStdString() << std::endl;
    this->currentCardNumber = newNumber;
}

void CardsArray::onCardTransfer(const QString &target) {
    std::cout << "[backend] Transfer from card to card from " <<
        currentCardNumber.toStdString() <<
        " to " << target.toStdString() << std::endl;
    emit cardsCardsChanged(getCards(), true);
}

void CardsArray::onBillTransfer(const QString &target) {
    std::cout << "[backend] Transfer from card to bill from " <<
              currentCardNumber.toStdString() <<
              " to " << target.toStdString() << std::endl;
    emit cardsCardsChanged(getCards(), true);
}

void CardsArray::onBlocked(bool block) {
    std::cout << "[backend] " << (block ? "Block" : "Unblock") << " card " <<
        currentCardNumber.toStdString() << std::endl;
    this->getByNum(currentCardNumber)->setIsBlocked(block);
    emit cardsCardsChanged(getCards(), true);
}

void CardsArray::onHistory(const QString &target) {
    std::cout << "[backend] Card history requested card " << target.toStdString() << std::endl;

    emit updateHistory(getHistory(target));
}

CardsArray::CardsArray(QObject *parent) : QObject(parent) {
    Card *newCard = new Card(QString("** 3456"), 1000, false);
    backend_cards.push_back(std::shared_ptr<Card>(newCard));
    newCard = new Card(QString("** 23w"), 1000, false);
    backend_cards.push_back(std::shared_ptr<Card>(newCard));

    History *newHistory = new History;
    newHistory->source = "forum.qt.io";
    newHistory->target = "Target 1";
    newHistory->value = 10;
    history.push_back(std::shared_ptr<History>(newHistory));

    newCard = backend_cards[0].get();
    std::cout << "ejfowopef" << ((Card*)getCards()[0])->getNumber().toStdString() << std::endl;
}

void CardsArray::onUpdate() {
    emit cardsCardsChanged(getCards(), false);
}

void CardsArray::printCards() {
    auto cards = getCards();
    std::cout << "Card data: " << std::endl;
    for (QObject* el : cards)
    {
        Card *card = static_cast<Card*>(el);
        std::cout << "Number " << card->getNumber().toStdString() << std::endl;
    }
    std::cout << "~~~" << std::endl;
}

QList<QObject *> CardsArray::getHistory(const QString &target) const {
    QList<QObject*> history;
    history.reserve(this->history.size());

    for (auto el : this->history) {
        history.push_back(el.get());
    }

    return history;
}
