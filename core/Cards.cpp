//
// Created by System Administrator on 11/13/23.
//

#include "Cards.hpp"

#include <iostream>

//void CardsArray::onCardChoosed(QString id) {
//    int current_id = id.toInt();
//
//}
//
//void CardsArray::onTransfer(QString target_number) {
//    std::cout << "Transfer from card to card from " <<
//        currentCardNumber.toStdString() <<
//        " to " << target_number.toStdString() << std::endl;
//}

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

CardsArray::CardsArray(QObject *parent) : QObject(parent) {
    Card *newCard = new Card(QString("** 3456"), 1000, false);
    backend_cards.push_back(std::shared_ptr<Card>(newCard));
    newCard = new Card(QString("** 23w"), 1000, false);
    backend_cards.push_back(std::shared_ptr<Card>(newCard));

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
