import QtQuick 2.15
import QtQuick.Controls 2.15

Dialog {
    id: credentials

    property var no: null
    property var ok: null

    height: 240
    standardButtons: Dialog.Ok | Dialog.Cancel
    title: "Enter a string"
    width: 500

    onAccepted: {
        console.log("User input: " + Number(textInput.text).toString());
        console.log("User input: " + textInput.text);
        ok(additionalInput.text, Number(textInput.text.replace(",", ".")));
        textInput.text = "";
        additionalInput.text = "";
    }
    onRejected: {
        console.log("User rejected");
        no(additionalInput.text, parseFloat(textInput.text));
        textInput.text = "";
        additionalInput.text = "";
    }

    TextField {
        id: additionalInput

        anchors.horizontalCenter: parent.horizontalCenter
        font.family: "Verdana"
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
        placeholderText: qsTr("enter additional input here")
        width: parent.width
    }
    TextField {
        id: textInput

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: additionalInput.bottom
        anchors.topMargin: 20
        font.family: "Verdana"
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
        placeholderText: qsTr("enter here")
        width: parent.width

        validator: DoubleValidator {
            bottom: 0.01
            decimals: 2
            notation: DoubleValidator.StandardNotation
            top: Infinity
        }
    }
}
