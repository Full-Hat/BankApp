import QtQuick 2.15
import QtQuick.Controls 2.15

Dialog {
   id: dialog
   title: "Account creation"
   standardButtons: Dialog.Ok | Dialog.Cancel

   width: 500
   height: 120

   property var ok: null
   property var no: null

    Row {
       width: parent.width
        y: parent.y - 20
        ComboBox {
            id: currencyComboBox
            width: 100
            model: currencyModel
            textRole: "currency"

            onActivated: {

            }

            Component.onCompleted: {
                CtrUtils.onCurrencyUpdate()
            }
        }
        TextField {
            id: textInput
            width: 300
            placeholderText: qsTr("enter name here")
            font.pixelSize: 12
            font.family: "Verdana"
        }
    }
    ListModel {
        id: currencyModel
    }

   onAccepted: {
       console.log("User input: ")
       ok(textInput.text, currencyComboBox.currentText)
       textInput.text = ""
   }

   onRejected: {
        console.log("User rejected")
        no(textInput.text, currencyComboBox.currentText)
        textInput.text = ""
   }

   Connections {
       function onCurrencyUpdateSignal(objs) {
           console.log("Received currency update signal")
           currencyModel.clear()

           for (var i = 0; i < objs.length; ++i) {
               currencyModel.append({ "currency": objs[i].currency })
           }
       }
       target: CtrUtils
   }
}
