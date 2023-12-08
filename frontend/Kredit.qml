import QtQuick 2.15
import Qt5Compat.GraphicalEffects

Rectangle {
    id: creditItem

    height: 200
    width: 300

    Timer {
        id: timer

        interval: 5 // Delay in milliseconds

        onTriggered: opacity = 0.5
    }
    BorderImage {
        id: creditImage

        property bool adapt: true
        property bool rounded: true

        anchors.fill: parent
        layer.enabled: rounded
        source: "images/card_background.png"

        layer.effect: OpacityMask {
            maskSource: Item {
                height: creditImage.height
                width: creditImage.width

                Rectangle {
                    anchors.centerIn: parent
                    height: creditImage.adapt ? creditImage.height : width
                    radius: 20
                    width: creditImage.adapt ? creditImage.width : Math.min(creditImage.width, creditImage.height)
                }
            }
        }

        Column {
            anchors.centerIn: parent
            spacing: 10

            Text {
                text: creditId
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
                height: creditImage.height
                width: creditImage.width

                Rectangle {
                    anchors.centerIn: parent
                    height: creditImage.adapt ? creditImage.height : width
                    radius: 20
                    width: creditImage.adapt ? creditImage.width : Math.min(creditImage.width, creditImage.height)
                }
            }
        }
    }

    //    Connections {
    //        target: CtrCredits
    //
    //    }
}
