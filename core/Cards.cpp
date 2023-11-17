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

//Card &CardsArray::getByNum(QString number) {
//    const auto &&res = std::ranges::find_if(cards, [&](const Card &el) { return el.getNumber() == number; });
//    if (res == cards.cend()) {
//        throw std::invalid_argument("Wrong card number");
//    }
//
//    return *res;
//}
//
QList<QObject *> CardsArray::getCards() {
    QList<QObject *> qmlCards(backend_cards.size());
    for (int i = 0; i < qmlCards.size(); ++i) {
        qmlCards[i] = static_cast<QObject*>(*backend_cards[i].get());
    }

    return qmlCards;
}

void CardsArray::onCurrentCardUpdate(const QString newNumber) {
    std::cout << "[backend] " << "change card to " << newNumber.toStdString() << std::endl;
    this->currentCardNumber = newNumber;
}

void CardsArray::onTransfer(const QString &target) {
    std::cout << "[backend] Transfer from card to card from " <<
        currentCardNumber.toStdString() <<
        " to " << target.toStdString() << std::endl;
}
