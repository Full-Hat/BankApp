import QtQuick 2.12
import QtQuick.Controls 2.5

Column {
    spacing: 10
    anchors.horizontalCenter: parent.horizontalCenter

    property string value: "10"
    Text {
        text: "Погашение"
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Text {
        text: "Общая сумма долга " + value
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }

    ListView {
        model: ListModel {
            ListElement { source: "jqwowqd"; target: "okqwdok"; value: "qwdk" }
        }

        delegate: Rectangle {
            width: parent.width
            height: 50
            color: index % 2 === 0 ? "white" : "lightgray" // Alternate row colors

            Row {
                width: parent.width
                spacing: 10
                y: parent.height / 2 - 10

                Column {
                   width: parent.width / 3
                   Text {
                        text: model.source
                        horizontalAlignment: Text.AlignHCenter
                   }
                }

                Column {
                   width: parent.width / 3
                   Text {
                        text: model.target
                        horizontalAlignment: Text.AlignHCenter
                   }
                }

                Column {
                   width: parent.width / 3
                   Text {
                        text: model.value
                        horizontalAlignment: Text.AlignHCenter
                   }
                }
            }
       }
    }

    Text {
        text: "Получение нового"
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Button {
        text: "Получить новый"
        onClicked: {
            // Add your code here
        }
    }
}
