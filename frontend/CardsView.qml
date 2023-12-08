import QtQuick 6.6
import QtQuick.Controls 6.6
import QtQuick.Layouts

Column {
    // Cards
    id: cards

    anchors.topMargin: 150
    anchors.verticalCenterOffset: 1000
    spacing: 100

    SwipeView {
        id: cardsView

        anchors.horizontalCenter: parent.horizontalCenter
        height: 150
        width: 300

        onCurrentIndexChanged: {
            if (cardListModel.count === 0) {
                return;
            }
            for (var i = 0; i < count; i++) {
                var item = itemAt(i);
                if (i === currentIndex) {
                    item.opacity = 1.0;
                } else if (i === currentIndex - 1 || i === currentIndex + 1) {
                    item.opacity = 0.0;
                } else {
                    item.opacity = 0.0;
                }
            }
            CtrCards.onCurrentCardUpdate(cardListModel.get(currentIndex).cardNumber);
        }

        Repeater {
            model: cardListModel

            delegate: Card {
                opacity: 0.0

                Behavior on opacity {
                    NumberAnimation {
                        duration: 500
                    }
                }
            }
        }
    }
    Text {
        id: text_cards_title

        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 23
        horizontalAlignment: Text.AlignHCenter
        text: "Your -^- Cards"
    }
    Grid {
        anchors.horizontalCenter: parent.horizontalCenter
        columns: 2
        spacing: 10

        Button {
            id: transfer_card

            text: "Transfer to Card"
            width: 150

            onClicked: {
                get_credentials.item.ok = function (str, value) {
                    CtrCards.onCardTransfer(str, value);
                };
                get_credentials.item.no = function (str, value) {};
                get_credentials.item.open();
            }
        }
        Button {
            id: tramsfer_bill

            text: "Transfer to Bill"
            width: 150

            onClicked: {
                get_credentials.item.ok = function (str) {
                    CtrCards.onBillTransfer(str);
                };
                get_credentials.item.no = function (str) {};
                get_credentials.item.open();
            }
        }
        Button {
            id: block

            text: "Block"
            width: 150

            onClicked: {
                console.log("Block button clicked");
                CtrCards.onBlocked(!cardListModel.get(cardsView.currentIndex).isBlocked);
            }
        }
        Button {
            id: history

            text: "History"
            width: 150

            onClicked: {
                main_stack_view.push("History.qml");
                CtrCards.onHistory(cardListModel.get(cardsView.currentIndex).cardNumber);
                console.log("History button clicked");
            }
        }
        Button {
            id: details

            text: "Details"
            width: 150

            onClicked: {
                CtrCards.onDetails()
            }
        }
        Button {
            id: remove

            text: "Remove card"
            width: 150

            onClicked: {
                if (cardsView.count - 1 === 0) {
                    transfer_card.enabled = false;
                    tramsfer_bill.enabled = false;
                    block.enabled = false;
                    history.enabled = false;
                    remove.enabled = false;
                }
                CtrCards.onRemoveCard(cardListModel.get(cardsView.currentIndex).cardNumber);
                console.log("Delete card button");
            }
        }
        Button {
            id: add

            text: "Add card"
            width: 150

            onClicked: {
                transfer_card.enabled = true;
                tramsfer_bill.enabled = true;
                block.enabled = true;
                history.enabled = true;
                remove.enabled = true;
                CtrCards.onAddCard();
                console.log("Add card button");
                cardsView.currentIndex = cardListModel.count - 1;
            }
        }
    }
    Connections {
        function onCardsCardsChanged(cards, saveCurrent) {
            var index = cardListModel.count;
            var currentIndex = cardsView.currentIndex;
            cardListModel.clear();
            for (var i = 0; i < cards.length; i++) {
                var card = cards[i];
                cardListModel.append({
                        "cardNumber": card.number,
                        "balance": String(card.value),
                        "isBlocked": card.isBlocked
                    });
            }
            if (saveCurrent) {
                cardsView.currentIndex = currentIndex;
                return;
            }
            if (cardListModel.count < index) {
                console.log("Update count - 1");
                cardsView.currentIndex = cardListModel.count - 1;
            } else if (index === 0) {
                cardsView.currentIndex = 0;
            } else {
                console.log("Update index - 1");
                cardsView.currentIndex = index - 1;
            }
            if (cardsView.currentIndex === 0) {
                cardsView.currentIndex = 1;
                cardsView.currentIndex = 0;
            }
                console.log("Index " + cardsView.currentIndex);
        }
        function onCardsDetails(code, number, date, cvv, value) {
            popUp.item.localText = number + " " + date + "\nCVV " + cvv + "\nBalance " + value.toString();
            popUp.item.open();
        }

        target: CtrCards
    }
    Loader {
        id: popUp

        anchors.horizontalCenter: parent.horizontalCenter
        source: "qrc:/main/frontend/PopUpInfo.qml"
        y: parent.height * 0.5
    }
}
