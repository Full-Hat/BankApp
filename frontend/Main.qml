import QtQuick 6.5
import QtQuick.Window 6.5
import QtQuick.Controls 6.5

Window {
    visible: true
    title: "BankApp"
    id: main_window
    width: 1920
    height: 1080

    color: "#c2c2c2"

    StackView {
        id: main_stack_view
        anchors.fill: parent
        //initialItem: "LoginPage.qml"
        initialItem: "MainPage.qml"

        anchors.horizontalCenter: parent.horizontalCenter
    }
}
