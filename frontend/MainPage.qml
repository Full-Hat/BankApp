import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

Rectangle {
    id: rectangle
    width: 1920
    height: 1080
    color: "#ffffff"

    TabBar {
        id: tabBar
        x: 0
        y: 0
        width: 1920
        height: 1080

        TabButton {
            text: qsTr("Cards")
        }
        TabButton {
            text: qsTr("Account")
        }

        StackLayout {
            id: stackLayout
            anchors.fill: parent
            currentIndex: parent.currentIndex

            Item {

            }
            Item {

            }
        }
    }
}
