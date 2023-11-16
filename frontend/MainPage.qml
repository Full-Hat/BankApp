import QtQuick 6.6
import QtQuick.Controls 6.6
import QtQuick.Layouts

Rectangle {
    id: rectangle
    width: main_stack_view.width
    height: main_stack_view.height
    color: "#ffffff"

    TabBar {
        id: tabBar
        width: parent.width
        height: parent.height

        TabButton {
            id: button
            text: qsTr("Cards")
        }
        TabButton {
            text: qsTr("Account")
        }
    }

    StackLayout {
        id: stackLayout
        width: parent.width / 9
        height: (parent.height - button.height) / 10
        anchors.horizontalCenter: parent.horizontalCenter
        y: button.height
        currentIndex: tabBar.currentIndex

        ListModel {
            id: cardListModel
            ListElement {
                cardId: "1"
                cardNumber: "** 3456"
                balance: "1000"
                isBlocked: false
            }
            ListElement {
                cardId: "2"
                cardNumber: "** 3456"
                balance: "1000"
                isBlocked: false
            }
            // Add more ListElements here for more cards
        }

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
                    delegate: Card {}
                }
                onCurrentIndexChanged: {
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
                 text: "Block"
                 width: 150
                 onClicked: {
                    console.log("Block button clicked")
                    cardListModel.get(cardsView.currentIndex).isBlocked =
                        !cardListModel.get(cardsView.currentIndex).isBlocked
                 }

             }

             Button {
                 text: "History"
                 width: 150
                 onClicked: {
                    main_stack_view.push("History.qml")
                    console.log("History button clicked")
                 }
             }

             Button {
                text: "Remove card"
                width: 150
                onClicked: console.log("Delete card button")
            }

            Button {
                text: "Add card"
                width: 150
                onClicked: console.log("Add card button")
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
        Column {
            // Bills
        }
        Column {
            // Kredits
        }
        Column {
            // Documents
        }
    }

    Loader {
        id: get_string
        width: 300
        height: 300
        anchors.horizontalCenter: parent.horizontalCenter
        y: parent.height * 0.5
        source: "qrc:/main/frontend/GetString.qml"
    }
}
