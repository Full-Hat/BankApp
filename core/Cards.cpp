//
// Created by System Administrator on 11/13/23.
//

#include "Cards.hpp"

#include <iostream>

std::shared_ptr<Card> CardsArray::getByNum(QString number) {
    auto res = std::ranges::find_if(backend_cards, [&](const std::shared_ptr<Card> &el) { return el->getNumber() == number; });
    if (res == backend_cards.end()) {
        throw std::invalid_argument("Wrong card number");
    }

    return *res;
}

QList<QObject *> CardsArray::getCards() {
    auto res = m_backend.CardsGet(CurrentUser::Get().GetToken());
    if (res.code != 200) {
        return {};
    }
    backend_cards.clear();
    for(const auto& data : res.datas) {
        std::shared_ptr<Card> bill = std::make_shared<Card>(data.id, data.number, data.date, data.isBlocked);
        backend_cards.append(bill);
    }

    QList<QObject *> qmlCards(backend_cards.size());
    for (int i = 0; i < backend_cards.size(); ++i) {
        qmlCards[i] = static_cast<QObject*>(backend_cards[i].get());
    }

    return qmlCards;
}

void CardsArray::onCurrentCardUpdate(const QString& newNumber) {
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

    auto code = m_backend.CardsBlock(this->getByNum(currentCardNumber)->getId(), CurrentUser::Get().GetToken());
    assert(code == 200);

    emit cardsCardsChanged(getCards(), true);
}

void CardsArray::onHistory(const QString &target) {
    std::cout << "[backend] Card history requested card " << target.toStdString() << std::endl;

    emit updateHistory(getHistory(target));
}

CardsArray::CardsArray(QObject *parent) : QObject(parent) {
    auto *newHistory = new History;
    newHistory->source = "forum.qt.io";
    newHistory->target = "Target 1";
    newHistory->value = 10;
    history.push_back(std::shared_ptr<History>(newHistory));
}

void CardsArray::onUpdate() {
    emit cardsCardsChanged(getCards(), false);
}

void CardsArray::printCards() {
    auto cards = getCards();
    std::cout << "Card data: " << std::endl;
    for (QObject* el : cards)
    {
        Card *card = dynamic_cast<Card*>(el);
        std::cout << "Number " << card->getNumber().toStdString() << std::endl;
    }
    std::cout << "~~~" << std::endl;
}

QList<QObject *> CardsArray::getHistory(const QString &target) {
    auto res = m_backend.History(CurrentUser::Get().GetToken());
    assert(res.code == 200);

    history.clear();
    for (auto el : res.datas) {
        auto res = m_backend.CardsGetDetails(getByNum(currentCardNumber)->getId(), CurrentUser::Get().GetToken());
        // Check filter
        if (el.source != res.number && el.target != res.number) {
            continue;
        }

        history.push_back(std::make_shared<History>());
        auto &row = history.last();
        row->source = el.source;
        row->target = el.target;
        row->value = el.value;
        row->date = el.date;
    }

    QList<QObject*> history_obj;
    history_obj.reserve(this->history.size());

    for (const auto& el : this->history) {
        history_obj.push_back(el.get());
    }

    return history_obj;
}

void CardsArray::onRemoveCard(const QString &target) {
    std::cout << "[backend] " << "card removed card " << target.toStdString() << std::endl;

    auto id = std::find_if(backend_cards.begin(), backend_cards.end(), [&](const std::shared_ptr<Card> &c) {
        return c->getNumber() == target;
    })->get()->getId();
    auto code = m_backend.CardsRemove(id, CurrentUser::Get().GetToken());
    assert(code == 200);

    emit cardsCardsChanged(getCards(), false);
}

void CardsArray::onAddCard() {
    std::cout << "[backend] " << "card added" << std::endl;
    m_backend.CardsAdd(CurrentUser::Get().GetToken());
    emit cardsCardsChanged(getCards(), false);
}

void CardsArray::onDetails() {
    auto id = this->getByNum(currentCardNumber)->getId();
    auto result = m_backend.CardsGetDetails(id, CurrentUser::Get().GetToken());

    emit cardsDetails(result.code, result.number, result.date, result.cvv, result.value);
}
