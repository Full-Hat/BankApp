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
        TabButton {
            text: qsTr("Credits")
        }
        TabButton {
            text: qsTr("Documents")
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
            // Add more ListElements here for more cards
        }

        ListModel {
            id: billListModel
            // Add more ListElements here for more cards
        }

        ListModel {
            id: creditListModel
        }

        ListModel {
            id: documentListModel
        }

        Item {
            width: parent.width
            height: parent.height

            Loader {
                id: cards
                source: "qrc:/main/frontend/CardsView.qml"

                anchors.horizontalCenter: parent.horizontalCenter

                onLoaded: {
                    CtrCards.onUpdate()
                }
            }
        }
        Item {
            // Bills
            width: parent.width
            height: parent.height

            Loader {
                id: bills
                source: "qrc:/main/frontend/BillsView.qml"

                anchors.horizontalCenter: parent.horizontalCenter
                onLoaded: {
                    CtrBills.onUpdate()
                }
            }
        }
        Item {
            // Credits
            width: parent.width
            height: parent.height

            Loader {
                id: credits
                source: "qrc:/main/frontend/CreditsView.qml"

                anchors.horizontalCenter: parent.horizontalCenter
                onLoaded: {
                    CtrCredits.onUpdate()
                }
            }
        }
        Item {
            // Documents
            // Credits
            width: parent.width
            height: parent.height

            Loader {
                id: documents
                source: "qrc:/main/frontend/DocumentsView.qml"

                anchors.horizontalCenter: parent.horizontalCenter
                onLoaded: {
                    CtrDocuments.onUpdate(4, 2023)
                }
            }
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

    Loader {
        id: get_credentials
        width: 300
        height: 300
        anchors.horizontalCenter: parent.horizontalCenter
        y: parent.height * 0.5
        source: "qrc:/main/frontend/GetCredentials.qml"
    }

    Loader {
        id: warning

        anchors.horizontalCenter: parent.horizontalCenter
        height: 300
        source: "qrc:/main/frontend/PopUpWarning.qml"
        width: 300
        y: parent.height * 0.5
    }
}
