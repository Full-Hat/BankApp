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
        height: (parent.height - button.height) / 10 - 20
        anchors.horizontalCenter: parent.horizontalCenter
        y: button.height + 20
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
                cardNumber: "** 23w"
                balance: "1000"
                isBlocked: false
            }
            // Add more ListElements here for more cards
        }

        Item {
            width: parent.width
            height: parent.height

            Loader {
                id: cards
                source: "qrc:/main/frontend/CardsView.qml"

                anchors.horizontalCenter: parent.horizontalCenter
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
