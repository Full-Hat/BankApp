import QtQuick 6.6
import QtQuick.Controls 6.6
import QtQuick.Layouts
import QtQuick.Dialogs
import Qt5Compat.GraphicalEffects

Column {
    id: documentsViewItem

    anchors.topMargin: 150
    anchors.verticalCenterOffset: 1000
    spacing: 10

    property bool declaration_loaded: false
    property string hashId
    property string file
    property string date
    property double sum
    property string kind

    Rectangle {
        width: 300
        height: 150
        border.color: declaration_loaded ? "gray" : "red"
        border.width: 3
        radius: 20
        anchors.horizontalCenter: parent.horizontalCenter

        Column {
            visible: declaration_loaded
            anchors.centerIn: parent
        }
    }

    Text {
        id: text_documents_title1

        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 23
        horizontalAlignment: Text.AlignHCenter
        text: "Your -^- Bonus"
    }

    Row {
        ComboBox {
            id: currencyComboBox
            width: 100
            model: currencyModelLocal
            textRole: "currency"

            onActivated: {
                var selectedCurrency = currencyComboBox.currentText;
                CtrBonus.onUpdateCurrency(selectedCurrency);
            }

            Component.onCompleted: {
                CtrUtils.onCurrencyUpdate()
            }
        }
        ListModel {
            id: currencyModelLocal
        }
        Connections {
            function onCurrencyUpdateSignal(objs) {
                console.log("Received currency update signal")
                currencyModelLocal.clear()

                for (var i = 0; i < objs.length; ++i) {
                    currencyModelLocal.append({ "currency": objs[i].currency })
                }
            }
            target: CtrUtils
        }
        TextField {
            id: sumData
            placeholderText: "sum > 10";
            validator: DoubleValidator {
                bottom: 0.01
                decimals: 2
                notation: DoubleValidator.StandardNotation
                top: Infinity
            }
        }
        Button {
            id: add_declaration

            text: "Add"
            width: 150

            onClicked: {
                CtrBonus.onAddBonus(currencyComboBox.currentText, sumData.text)
            }
        }
    }

    SwipeView {
        id: documentsView

        anchors.horizontalCenter: parent.horizontalCenter
        height: 150
        width: 300

        onCurrentIndexChanged: {
            if (documentListModel.count === 0) {
                return;
            }
            for (var i = 0; i < count; i++) {
                var item = itemAt(i);
                if (i === currentIndex) {
                    item.opacity = 1.0;
                } else {
                    item.opacity = 0.0;
                }
            }
            console.log("Current document index " + currentIndex);
            CtrDocuments.onCurrentDocumentUpdate(documentListModel.get(currentIndex).hashId);
        }

        Repeater {
            model: documentListModel

            delegate: Document {
                opacity: 0.0

                Behavior on opacity {
                    NumberAnimation {
                        duration: 500
                    }
                }
            }
        }
    }
    Text {
        id: text_documents_title

        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 23
        horizontalAlignment: Text.AlignHCenter
        text: "Your -^- Bonuses"
    }

    Row {
        TextField {
            id: totalSum
            placeholderText: "Total sum";
            validator: DoubleValidator {
                bottom: 0.01
                decimals: 2
                notation: DoubleValidator.StandardNotation
                top: Infinity
            }
        }
        TextField {
            id: dateInput1
            placeholderText: "day"
            inputMask: "D0"
            validator: IntValidator {
                bottom: 1
                top: 31
            }
        }
        TextField {
            id: amount
            placeholderText: "Amount";
            validator: DoubleValidator {
                bottom: 0.01
                decimals: 2
                notation: DoubleValidator.StandardNotation
                top: Infinity
            }
        }
        ComboBox {
            id: billsBox
            editable: false
            model: ListModel {
                id: billsModel
            }
        }
    }

    Grid {
        anchors.horizontalCenter: parent.horizontalCenter
        columns: 2
        spacing: 10

        Button {
            id: add

            text: "Add"
            width: 150

            onClicked: {
                var sum = parseFloat(totalSum.text)
                var day = parseInt(dateInput1.text)
                var amt = parseFloat(amount.text)
                var selectedBill = billsBox.currentText

                // Call the C++ function with the extracted values
                CtrBonus.onBonusDecondAdd(sum, day, amt, selectedBill)
            }
        }

        Button {
            id: download

            text: "Brake"
            width: 150

            onClicked: {
                console.log("Add document button")
            }
        }
    }

    Connections {
        // function onDocumentsChanged(documents, declaration, saveCurrent) {
        //     console.log("onDocumentsChanged")
        //     let modelSize = documentListModel.count;
        //     let currentIndex = documentsView.currentIndex;
        //
        //     // Reset model
        //     documentListModel.clear();
        //     for (var i = 0; i < documents.length; i++) {
        //         var document = documents[i];
        //         documentListModel.append({
        //             "hashId" : document.hashId,
        //             "file" : document.file,
        //             "date" : document.date,
        //             "sum" : document.sum,
        //             "kind" : document.kindStr,
        //         });
        //     }
        //     if (declaration !== null) {
        //         declaration_loaded = true
        //         hashId = declaration.hashId
        //         file = declaration.file
        //         date = declaration.date
        //         sum = declaration.sum
        //         kind = declaration.kindStr
        //     }
        //     else {
        //         declaration_loaded = false
        //     }
        //
        //     console.log("documents count " + documentListModel.count)
        //
        //     // Try to save current index
        //     if (saveCurrent) {
        //         documentsView.currentIndex = currentIndex;
        //     }
        //
        //     // If model is empty
        //     if (documentListModel.count === 0) {
        //         documentsView.currentIndex = 0;
        //     }
        //     if (modelSize === 0) {
        //         documentsView.currentIndex = 0;
        //     } else
        //
        //         // Else
        //     if (documentListModel.count < modelSize) {
        //         documentsView.currentIndex = cardListModel.count - 1;
        //     }
        //
        //     // Force update
        //     if (documentsView.currentIndex === 0) {
        //         documentsView.currentIndex = 1;
        //         documentsView.currentIndex = 0;
        //     }
        // }
        function onShowWarning(message) {
            popUp.item.localText = message;
            popUp.item.open();
        }
        // function onShowOk() {
        //     popUpInfo.item.localText = "it works"
        //     popUpInfo.item.open()
        // }
        //
        // function onCloseDialog() {
        //     console.log("Called on close");
        //     fileDialog.close()
        // }
        //
        target: CtrBonus
    }
    Loader {
        id: popUp

        anchors.horizontalCenter: parent.horizontalCenter
        source: "qrc:/main/frontend/PopUpWarning.qml"
        y: parent.height * 0.5
    }
    Loader {
        id: popUpInfo

        anchors.horizontalCenter: parent.horizontalCenter
        source: "qrc:/main/frontend/PopUpInfo.qml"
        y: parent.height * 0.5
    }
}
