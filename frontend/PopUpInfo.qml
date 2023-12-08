import QtQuick 2.15
import QtQuick.Controls 2.15

Popup {
    id: warningPopup
    width: 300
    height: 150
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2
    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    property string localText: ""
    property string header: "Good!"
    property var event: function() {}

    onClosed: {
        // Add your code here that should be executed when the Popup is closed
        event()
    }

    Rectangle {
        anchors.fill: parent
        color: "#f0f0f0"
        radius: 10

        Column {
            anchors.centerIn: parent
            spacing: 20

            Text {
                id: warningTitle
                text: header
                font.pixelSize: 24
                color: "#333333"
                anchors.horizontalCenter: parent.horizontalCenter
                horizontalAlignment: Text.AlignHCenter
                font.bold: true
            }

            Text {
                id: warningText
                text: warningPopup.localText
                font.pixelSize: 16
                color: "#333333"
                anchors.horizontalCenter: parent.horizontalCenter
                horizontalAlignment: Text.AlignHCenter
            }

            Button {
                id: okButton
                text: "OK"
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: warningPopup.close()
            }
        }
    }
}
