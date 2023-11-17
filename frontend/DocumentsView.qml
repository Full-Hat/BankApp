import QtQuick 2.12
import QtQuick.Controls 2.5

Column {
    id: documents_view
    spacing: 10
    anchors.horizontalCenter: parent.horizontalCenter

    property string declaration_number: "10"

    Row {
        Text {
            text: "Declaration " + declaration_number
        }
        Text {
            text: "Value " + "10"
        }
        Button {
            text: "Update document"
        }
    }
    Row {
        Text {
            text: "Acts"
        }
        Text {
            text: "Total value " + "10"
        }
        Button {
            text: "Add act"
        }
    }
    ListView {

    }
    Row {
        spacing: 10

        Text {
            text: "Год"
        }

        TextField {
            placeholderText: "2024"
            validator: IntValidator {}
        }

        Text {
            text: "Квартал"
        }

        TextField {
            placeholderText: "3"
            validator: IntValidator {}
        }
    }
}
