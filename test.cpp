//
// Created by Full-Hat on 11/12/2023.
//

#include "core/Bills.hpp"
#include "core/Cards.hpp"

#include "gtest/gtest.h"
#include "test_api.hpp"


class Bills_t : public Bills {
public:
    void testGetBills() {
        m_backend = new TestApi();

        // Bills -> objects convertation
        auto bills = getBills();
        ASSERT_EQ(bills.size(), 2);
        auto el = bills[0];
        {
            Bill *bill = dynamic_cast<Bill*>(el);
            ASSERT_NE(bill, nullptr);
            ASSERT_STREQ(bill->getNumber().toStdString().data(), "number");
            ASSERT_EQ(bill->getValue(), 1.0);
            ASSERT_STREQ(bill->getName().toStdString().data(), "name");
            ASSERT_EQ(bill->getIsBlocked(), true);
        }
        el = bills[1];
        {
            Bill *bill = dynamic_cast<Bill*>(el);
            ASSERT_NE(bill, nullptr);
            ASSERT_STREQ(bill->getNumber().toStdString().data(), "name1");
            ASSERT_EQ(bill->getValue(), 2.0);
            ASSERT_STREQ(bill->getName().toStdString().data(), "Number1");
            ASSERT_EQ(bill->getIsBlocked(), true);
        }

        // Objs finding
        auto obj = getByNum(((Bill*)el)->getNumber());
        ASSERT_EQ(obj->getName(), ((Bill*)el)->getName());
    }
};

TEST(Bill, empty_init) {
    Bills bills;
    auto res = bills.getBills();
    ASSERT_EQ(res.size(), 0);
}

TEST(Bill, init) {
    Bills_t bills;
    bills.testGetBills();
}

class Cards_t : public CardsArray {
public:
    void testGetCards() {
        m_backend = new TestApi();

        // cards -> objects convertation
        auto cards = getCards();
        ASSERT_EQ(cards.size(), 2);
        auto el = cards[0];
        {
            Card *card = dynamic_cast<Card*>(el);
            ASSERT_NE(card, nullptr);
            ASSERT_STREQ(card->getNumber().toStdString().data(), "number");
        }
        el = cards[1];
        {
            Card *card = dynamic_cast<Card*>(el);
            ASSERT_NE(card, nullptr);
            ASSERT_STREQ(card->getNumber().toStdString().data(), "name1");
        }

        // Objs finding
        auto obj = getByNum(((Card*)el)->getNumber());
        ASSERT_STREQ(obj->getId().toStdString().data(), ((Card*)el)->getNumber().toStdString().data());
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
