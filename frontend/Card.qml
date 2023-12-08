import QtQuick 2.15
import Qt5Compat.GraphicalEffects

Rectangle {
    id: cardItem

    height: 200
    width: 300

    Timer {
        id: timer

        interval: 5 // Delay in milliseconds

        onTriggered: opacity = 0.5
    }
    BorderImage {
        id: cardImage

        property bool adapt: true
        property bool rounded: true

        anchors.fill: parent
        layer.enabled: rounded
        source: "images/card_background.png"

        layer.effect: OpacityMask {
            maskSource: Item {
                height: cardImage.height
                width: cardImage.width

                Rectangle {
                    anchors.centerIn: parent
                    height: cardImage.adapt ? cardImage.height : width
                    radius: 20
                    width: cardImage.adapt ? cardImage.width : Math.min(cardImage.width, cardImage.height)
                }
            }
        }

        Column {
            anchors.centerIn: parent
            spacing: 10
            Text {
                color: "white"
                text: cardNumber
            }
            Text {
                color: "white"
                text: date
            }
        }
    }
    Rectangle {
        id: blockedOverlay

        property bool adapt: true
        property bool rounded: true

        anchors.fill: parent
        color: "white"
        layer.enabled: rounded
        opacity: isBlocked ? 0.5 : 0

        layer.effect: OpacityMask {
            maskSource: Item {
                height: cardImage.height
                width: cardImage.width

                Rectangle {
                    anchors.centerIn: parent
                    height: cardImage.adapt ? cardImage.height : width
                    radius: 20
                    width: cardImage.adapt ? cardImage.width : Math.min(cardImage.width, cardImage.height)
                }
            }
        }
    }

    //    Connections {
    //        target: CtrCards
    //
    //    }
}
