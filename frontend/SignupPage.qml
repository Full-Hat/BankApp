import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: rectangle_signup
    width: main_stack_view.width
    height: main_stack_view.height

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
        placeholderText: qsTr("enter login")
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
        placeholderText: qsTr("enter password")
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
        onClicked: {
            CtrSignup.OnSignup(login_edit.text, password_edit.text)
        }
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
        onClicked: {
            main_stack_view.replace("LoginPage.qml")
        }
    }

    Connections {
        target: CtrSignup
        function onSignupCorrect() {
            popUpOk.item.localText = "Verify account and login!"
            popUpOk.item.open()
        }
        function onSignupFailed(description) {
            popUp.item.localText = description
            popUp.item.open()
        }
    }

    Loader {
        id: popUp
        anchors.horizontalCenter: parent.horizontalCenter
        y: parent.height * 0.5
        source: "qrc:/main/frontend/PopUpWarning.qml"
    }

    Loader {
        id: popUpOk
        anchors.horizontalCenter: parent.horizontalCenter
        y: parent.height * 0.5
        source: "qrc:/main/frontend/PopUpInfo.qml"
    }
}
