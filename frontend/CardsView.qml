import QtQuick 6.6
import QtQuick.Controls 6.6
import QtQuick.Layouts

Column {
    // Cards
    id: cards

    spacing: 100
    anchors.verticalCenterOffset: 1000
    anchors.topMargin: 150

    SwipeView {
        id: cardsView
        width: 300
        height: 150
        anchors.horizontalCenter: parent.horizontalCenter
        Repeater {
            model: cardListModel
            delegate: Card {
                opacity: 0.0

                Behavior on opacity {
                    NumberAnimation { duration: 500 }
                }
            }
        }
        onCurrentIndexChanged: {
           for (var i = 0; i < count; i++) {
               var item = itemAt(i);
               if (i === currentIndex) {
                   item.opacity = 1.0;
               } else if (i === currentIndex - 1 || i === currentIndex + 1) {
                   item.opacity = 0.0;
               }
               else {
                   item.opacity = 0.0;
               }
           }
           console.log(cardListModel.get(currentIndex).cardId)
           CtrCards.onCardChoosed(cardListModel.get(currentIndex).cardId)
       }
    }

    Text {
        id: text_cards_title
        text: "Your -^- Cards"
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 23
    }

    Grid {
     columns: 2
     spacing: 10
     anchors.horizontalCenter: parent.horizontalCenter

     Button {
         id: transfer_card
         text: "Transfer to Card"
         width: 150
         onClicked: {
            console.log("Transfer to Card button clicked")
            get_string.item.ok = function (str) { CtrCards.onTransfer(str) }
            get_string.item.no = function (str) {  }
            get_string.item.open()
         }
     }

     Button {
         id: tramsfer_bill
         text: "Transfer to Bill"
         width: 150
         onClicked: {
            console.log("Transfer to Bill button clicked")
            get_string.item.ok = function (str) { CtrCards.onTransfer(str) }
            get_string.item.no = function (str) {  }
            get_string.item.open()
         }
     }

     Button {
         id: block
         text: "Block"
         width: 150
         onClicked: {
            console.log("Block button clicked")
            cardListModel.get(cardsView.currentIndex).isBlocked =
                !cardListModel.get(cardsView.currentIndex).isBlocked
         }

     }

     Button {
         id: history
         text: "History"
         width: 150
         onClicked: {
            main_stack_view.push("History.qml")
            console.log("History button clicked")
         }
     }

     Button {
        id: remove
        text: "Remove card"
        width: 150
        onClicked: {
            if (cardsView.count - 1 === 0) {
                transfer_card.enabled = false
                tramsfer_bill.enabled = false
                block.enabled = false
                history.enabled = false
                remove.enabled = false
            }

            else if (cardListModel.currentIndex === 1 || (typeof el === 'undefined')) {
                cardsView.currentIndex = cardsView.count - 1;
            }

            console.log("Delete card button")
            console.log(cardListModel.currentIndex)
            cardListModel.remove(cardsView.currentIndex)
        }
    }

    Button {
        id: add
        text: "Add card"
        width: 150
        onClicked: {
            transfer_card.enabled = true
            tramsfer_bill.enabled = true
            block.enabled = true
            history.enabled = true
            remove.enabled = true

            console.log("Add card button")
            cardListModel.append({"cardId": "", "cardNumber": "", "balance": "", "isBlocked": false})
            cardsView.currentIndex = cardListModel.count - 1
        }
    }
    }

    Connections {
        target: CtrCards
        function onAddCard(id, number, balance, is_blocked) {
            cardListModel.append({"cardId": id, "cardNumber": number, "balance": balance, "isBlocked": is_blocked})
        }
        function onRemoveCard(id) {
            for (var i = 0; i < cardListModel.count; ++i) {
               if (cardListModel.get(i).id === id) {
                   cardListModel.remove(i);
                   break;
               }
           }
        }
    }
}
