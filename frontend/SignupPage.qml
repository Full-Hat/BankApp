import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    width: parent.width
    height: parent.height

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
        scale: 1
    }

    TextField {
        id: login_edit
        y: 490
        width: 372
        height: 53
        text: qsTr("enter login")
        font.pixelSize: 30
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.family: "Verdana"
    }

    TextField {
        id: password_edit
        y: 566
        width: 372
        height: 51
        text: qsTr("enter password")
        font.pixelSize: 30
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.family: "Verdana"
        font.styleName: "Condensed Regular"
    }

    Button {
        id: signup_btn
        x: 845
        y: 774
        width: 285
        height: 72
        anchors.horizontalCenter: parent.horizontalCenter
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
        anchors.horizontalCenter: parent.horizontalCenter
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
        anchors.horizontalCenter: parent.horizontalCenter
        text: qsTr("Already have an accaunt?")
        font.pixelSize: 27
        horizontalAlignment: Text.AlignHCenter
        styleColor: "#000000"
        font.weight: Font.Light
    }
}
