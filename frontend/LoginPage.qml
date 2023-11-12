import QtQuick 6.5
import QtQuick.Window 6.5
import QtQuick.Controls 2.12

Rectangle {
    id: rectangle
    width: main_stack_view.width
    height: main_stack_view.height

    Text {
        id: page_description
        y: 158
        width: 564
        height: 97
        text: "Login"
        font.pixelSize: 30
        horizontalAlignment: Text.AlignHCenter
        font.family: "Verdana"
        anchors.horizontalCenter: parent.horizontalCenter
        scale: 1
    }

    TextField {
        id: login_edit
        y: 490
        width: 372
        height: 53
        placeholderText: "enter login"
        font.pixelSize: 30
        horizontalAlignment: Text.AlignHCenter
        font.family: "Verdana"
        anchors.horizontalCenter: parent.horizontalCenter
    }

    TextField {
        id: password_edit
        y: 566
        width: 372
        height: 51
        placeholderText: "enter password"
        font.pixelSize: 30
        horizontalAlignment: Text.AlignHCenter
        font.family: "Verdana"
        anchors.horizontalCenter: parent.horizontalCenter
        font.styleName: "Condensed Regular"
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
        anchors.horizontalCenter: parent.horizontalCenter
        checkable: false
        onClicked: {
            CtrLogin.OnLogin(login_edit.text, password_edit.text)
        }
    }

    Button {
        id: signup_btn
        x: 845
        y: 900
        width: 285
        height: 72
        text: qsTr("Signup")
        font.pointSize: 30
        font.family: "Verdana"
        anchors.horizontalCenter: parent.horizontalCenter
        checkable: false
        onClicked: {
            main_stack_view.replace("SignupPage.qml")
        }
    }

    Text {
        id: signup_description
        x: 845
        y: 859
        width: 285
        height: 57
        color: "#0a7ea7"
        text: qsTr("Don't have an accaunt?")
        font.pixelSize: 27
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.weight: Font.Light
        styleColor: "#000000"
    }

    Connections {
        target: CtrLogin
        function onLoginCorrect() {
            main_stack_view.push("LoginPageCode.qml")
        }
        function onLoginFailed(description) {
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
}
