import QtQuick 2.15
import Qt5Compat.GraphicalEffects

Rectangle {
    id: documentItem

    height: 200
    width: 300

    BorderImage {
        id: documentImage

        property bool adapt: true
        property bool rounded: true

        anchors.fill: parent
        layer.enabled: rounded
        source: "images/card_background.png"

        layer.effect: OpacityMask {
            maskSource: Item {
                height: documentImage.height
                width: documentImage.width

                Rectangle {
                    anchors.centerIn: parent
                    height: documentImage.adapt ? documentImage.height : width
                    radius: 20
                    width: documentImage.adapt ? documentImage.width : Math.min(documentImage.width, documentImage.height)
                }
            }
        }

        Column {
            anchors.centerIn: parent
            spacing: 3
            Text {
                id: hashIdField
                text: hashId
                color: "white"
            }

            Text {
                id: fileField
                text: file
                color: "white"
            }

            Text {
                id: dateField
                text: date
                color: "white"
            }

            Text {
                id: sumField
                text: sum
                color: "white"
            }

            Text {
                id: kindField
                text: kind
                color: "white"
            }
        }
    }
}
