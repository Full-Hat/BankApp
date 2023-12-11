import QtQuick 6.6
import QtQuick.Controls 6.6
import QtQuick.Layouts

Rectangle {
    id: rectangle
    width: main_stack_view.width
    height: main_stack_view.height
    color: "#ffffff"

    Rectangle {
        id: sidebar
        width: 150
        height: parent.height
        border.width: 1
        border.color: "#909090"

        anchors.top: parent.top
        anchors.topMargin: 3

        // Anchored to the left edge of the parent rectangle with a 30-pixel offset
        anchors.left: parent.left
        anchors.leftMargin: 3

        // Anchored to the bottom edge of the parent rectangle with a 40-pixel offset
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 3

        Column {
            width: parent.width

            Rectangle {
                color: "transparent"
                width: 1
                height: 5
            }

            Image {
                source: "images/logo.jpeg"
                width: 100
                height: 100
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 100
            }

            Button {
                text: "Cards"
                width: parent.width
                onClicked: {
                    stackLayout.currentIndex = 0
                }
            }

            Button {
                text: "Accounts"
                width: parent.width
                onClicked: {
                    stackLayout.currentIndex = 1
                }
            }

            Button {
                text: "Credits"
                width: parent.width
                onClicked: {
                    stackLayout.currentIndex = 2
                }
            }

            Button {
                text: "Documents"
                width: parent.width
                onClicked: {
                    stackLayout.currentIndex = 3
                }
            }
        }
    }

    Rectangle {
        id: windows
        x: sidebar.width
        width: 1920 - sidebar.width - sidebar.leftMargin * 2
        height: parent.height
        anchors.horizontalCenter: parent.horizontalCenter

        Column {
            anchors.fill: parent
            spacing: 10

            StackLayout {
                id: stackLayout
                y: windows.y + 30
                width: parent.width / 9
                anchors.horizontalCenter: parent.horizontalCenter
                currentIndex: 0

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
        }

        Loader {
            id: get_credentials
            anchors.horizontalCenter: parent.horizontalCenter
            y: parent.height * 0.5
            source: "qrc:/main/frontend/GetCredentials.qml"
            onLoaded: {
                item.x = windows.x - 400
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
        onLoaded: {
            item.x = windows.x - 250
        }
    }
    //
    //
    // Loader {
    //     id: warning
    //
    //     anchors.horizontalCenter: parent.horizontalCenter
    //     height: 300
    //     source: "qrc:/main/frontend/PopUpWarning.qml"
    //     width: 300
    //     y: parent.height * 0.5
    // }
}
