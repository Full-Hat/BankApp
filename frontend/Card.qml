import QtQuick 2.15
import Qt5Compat.GraphicalEffects

Rectangle {
    id: cardItem
    width: 300
    height: 200

    Timer {
        id: timer
        interval: 5 // Delay in milliseconds
        onTriggered: opacity = 0.5
    }

    BorderImage {
        id: cardImage
        anchors.fill: parent
        source: "images/card_background.png"

        property bool rounded: true
        property bool adapt: true

        layer.enabled: rounded
        layer.effect: OpacityMask {
            maskSource: Item {
                width: cardImage.width
                height: cardImage.height
                Rectangle {
                    anchors.centerIn: parent
                    width: cardImage.adapt ? cardImage.width : Math.min(cardImage.width, cardImage.height)
                    height: cardImage.adapt ? cardImage.height : width
                    radius: 20
                }
            }
        }

        Text {
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -20
            text: cardNumber
            color: "white"
        }

        Text {
            anchors.centerIn: parent
            anchors.verticalCenterOffset: 20
            text: "Balance: " + balance
            color: "white"
        }

        Text {
            anchors.centerIn: parent
            anchors.verticalCenterOffset: 20
            text: ""
            color: "white"
        }
    }

    Rectangle {
        id: blockedOverlay
        anchors.fill: parent
        color: "white"
        opacity: isBlocked ? 0.5 : 0

        property bool rounded: true
        property bool adapt: true

        layer.enabled: rounded
        layer.effect: OpacityMask {
            maskSource: Item {
                width: cardImage.width
                height: cardImage.height
                Rectangle {
                    anchors.centerIn: parent
                    width: cardImage.adapt ? cardImage.width : Math.min(cardImage.width, cardImage.height)
                    height: cardImage.adapt ? cardImage.height : width
                    radius: 20
                }
            }
        }


    }

//    Connections {
//        target: CtrCards
//
//    }
}
