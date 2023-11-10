import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    width: 1920
    height: 1080

    Text {
        id: page_description
        y: 158
        width: 564
        height: 97
        text: qsTr("Login")
        font.pixelSize: 30
        horizontalAlignment: Text.AlignHCenter
        scale: 1
        font.family: "Verdana"
        anchors.horizontalCenterOffset: 27
        anchors.horizontalCenter: parent.horizontalCenter
    }

    TextEdit {
        id: code_edit
        y: 490
        width: 372
        height: 53
        text: qsTr("enter code")
        font.pixelSize: 30
        horizontalAlignment: Text.AlignHCenter
        font.family: "Verdana"
        anchors.horizontalCenterOffset: 27
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Button {
        id: login_btn
        x: 845
        y: 774
        width: 285
        height: 72
        text: qsTr("Login")
        font.pointSize: 30
        font.family: "Verdana"
        checkable: false
    }

    Button {
        id: back_btn
        x: 845
        y: 852
        width: 285
        height: 69
        text: qsTr("Back")
        font.family: "Verdana"
        font.pointSize: 30
    }
}
