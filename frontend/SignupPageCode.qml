import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt5Compat.GraphicalEffects

Rectangle {
    id: signup_page_code
    width: main_stack_view.width
    height: main_stack_view.height

    color: "white"

    Text {
        id: page_description
        y: 158
        width: 564
        height: 97
        text: qsTr("Signup")
        font.pixelSize: 30
        horizontalAlignment: Text.AlignHCenter
        font.family: "Verdana"
        anchors.horizontalCenter: parent.horizontalCenter
    }

    TextField {
        id: code_edit
        y: 490
        width: 372
        height: 53
        placeholderText: qsTr("enter code")
        font.pixelSize: 30
        horizontalAlignment: Text.AlignHCenter
        font.family: "Verdana"
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Button {
        id: login_btn
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
            CtrSignupCode.OnSignup(code_edit.text)
        }
    }

    Button {
        id: back_btn
        x: 845
        y: 852
        width: 285
        height: 69
        anchors.horizontalCenter: parent.horizontalCenter
        text: qsTr("Back")
        font.family: "Verdana"
        font.pointSize: 30
        onClicked: {
            main_stack_view.pop()
        }
    }

    Connections {
        target: CtrSignupCode
        function onSignupCorrect() {
            // Open main page
            main_stack_view.replace("MainPage.qml")
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
}
