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
        text: qsTr("Signup")
        font.pixelSize: 30
        horizontalAlignment: Text.AlignHCenter
        clip: true
        anchors.horizontalCenter: parent.horizontalCenter
        font.family: "Verdana"
        anchors.horizontalCenterOffset: 27
        scale: 1
    }

    TextEdit {
        id: login_edit
        y: 490
        width: 372
        height: 53
        text: qsTr("enter login")
        font.pixelSize: 30
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.family: "Verdana"
        anchors.horizontalCenterOffset: 27
    }

    TextEdit {
        id: password_edit
        y: 566
        width: 372
        height: 51
        text: qsTr("enter password")
        font.pixelSize: 30
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.family: "Verdana"
        anchors.horizontalCenterOffset: 27
        font.styleName: "Condensed Regular"
    }

    Button {
        id: signup_btn
        x: 845
        y: 774
        width: 285
        height: 72
        text: qsTr("Signup")
        font.pointSize: 30
        font.family: "Verdana"
        checkable: false
    }

    Button {
        id: login_btn
        x: 845
        y: 900
        width: 285
        height: 72
        text: qsTr("Login")
        font.pointSize: 30
        font.family: "Verdana"
        checkable: false
    }

    Text {
        id: signup_description
        x: 845
        y: 859
        width: 285
        height: 57
        color: "#0a7ea7"
        text: qsTr("Already have an accaunt?")
        font.pixelSize: 27
        horizontalAlignment: Text.AlignHCenter
        styleColor: "#000000"
        font.weight: Font.Light
    }
}
