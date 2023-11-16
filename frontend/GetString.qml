import QtQuick 2.15
import QtQuick.Controls 2.15

Dialog {
   id: dialog
   title: "Enter a string"
   standardButtons: Dialog.Ok | Dialog.Cancel

   width: 500
   height: 100

   property var ok: null
   property var no: null

   TextField {
       id: textInput
       width: parent.width
       placeholderText: qsTr("enter here")
       font.pixelSize: 12
       horizontalAlignment: Text.AlignHCenter
       font.family: "Verdana"
       anchors.horizontalCenter: parent.horizontalCenter
   }

   onAccepted: {
       console.log("User input: ")
       ok(textInput.text)
       textInput.text = ""
   }

   onRejected: {
        console.log("User rejected")
        no(textInput.text)
        textInput.text = ""
   }
}
