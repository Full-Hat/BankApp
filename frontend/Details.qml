import QtQuick 2.15
import QtQuick.Controls

Popup {
    id: detailsPopup

    property var balance: 0.0
    property string cvv: ""
    property string date: ""
    property string localText: ""
    property string number: ""

    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    focus: true
    height: 300
    modal: true
    width: 300
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    Rectangle {
        anchors.fill: parent
        color: "#f0f0f0"
        radius: 10

        Column {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            spacing: 20

            Grid {
                anchors.horizontalCenter: parent.horizontalCenter
                columns: 2
                spacing: 10

                Text {
                    font.pixelSize: 16
                    horizontalAlignment: Text.AlignRight
                    text: "Number"
                }
                TextEdit {
                    font.pixelSize: 16
                    horizontalAlignment: Text.AlignLeft
                    text: number
                    readOnly: true
                    selectByMouse: true
                }
                Text {
                    font.pixelSize: 16
                    horizontalAlignment: Text.AlignRight
                    text: "Date"
                }
                Text {
                    font.pixelSize: 16
                    horizontalAlignment: Text.AlignLeft
                    text: date
                }
                Text {
                    font.pixelSize: 16
                    horizontalAlignment: Text.AlignRight
                    text: "cvv"
                }
                Text {
                    font.pixelSize: 16
                    horizontalAlignment: Text.AlignLeft
                    text: cvv
                }
                Text {
                    font.pixelSize: 16
                    horizontalAlignment: Text.AlignRight
                    text: "Balance"
                }
                Text {
                    font.pixelSize: 16
                    horizontalAlignment: Text.AlignRight
                    text: balance.toString()
                }
            }
            Button {
                id: okButton
                anchors.horizontalCenter: parent.horizontalCenter
                text: "OK"

                onClicked: detailsPopup.close()
            }
        }
    }
}
