import QtQuick 2.12
import QtQuick.Controls 2.12

Page {
    id: transactionHistoryPage

    title: "Transaction History"

    ScrollView {
        id: transactionScrollView

        anchors.fill: parent

        ListView {
            id: transactionListView

            anchors.fill: parent

            delegate: Rectangle {
                color: index % 2 === 0 ? "white" : "lightgray" // Alternate row colors

                height: 50
                width: transactionListView.width

                Row {
                    spacing: 10
                    width: parent.width
                    y: parent.height / 2 - 10

                    Column {
                        width: parent.width / 4

                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: model.source
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                    Column {
                        width: parent.width / 4

                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: model.target
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                    Column {
                        width: parent.width / 4

                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: model.value
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                    Column {
                        width: parent.width / 4

                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: model.date
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                }
            }
            model: ListModel {
                id: listModel

                // Add more transactions here
            }
        }
        Connections {
            function onUpdateHistory(history) {
                if (history.length === 0) {
                    popUp.item.localText = "There are no transactions";
                    popUp.item.header = "Hmm..";
                    popUp.item.event = function () {
                        main_stack_view.pop();
                    };
                    popUp.item.open();
                    return;
                }
                console.log(history.length);
                console.log("Value is " + history[0].value);
                listModel.clear();
                for (var i = 0; i < history.length; i++) {
                    listModel.append({
                            "source": history[i].source,
                            "target": history[i].target,
                            "value": String(history[i].value),
                            "date": history[i].date
                        });
                    console.log(history[i].source);
                }
            }

            target: CtrCards
        }
        Connections {
            function onUpdateHistory(history) {
                console.log(history.length);
                listModel.clear();
                for (var i = 0; i < history.length; i++) {
                    listModel.append({
                            "source": history[i].source,
                            "target": history[i].target,
                            "value": String(history[i].value),
                            "date": history[i].date
                        });
                    console.log(history[i].source);
                }
            }

            target: CtrBills
        }
    }
    Button {
        id: exitButton

        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        height: 50
        text: "Exit"
        width: 200

        onClicked: {
            main_stack_view.pop();
        }
    }
    Loader {
        id: popUp

        anchors.horizontalCenter: parent.horizontalCenter
        source: "qrc:/main/frontend/PopUpInfo.qml"
        y: parent.height * 0.5
    }
}
