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
            Text {
                id: hashIdField
                text: hashId
            }

            Text {
                id: fileField
                text: file
            }

            Text {
                id: dateField
                text: date
            }

            Text {
                id: sumField
                text: sum
            }

            Text {
                id: kindField
                text: kind
            }
        }
    }

    Text {
        id: text_documents_title1

        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 23
        horizontalAlignment: Text.AlignHCenter
        text: "Your -^- Declaration"
    }

    Row {
        TextField {
            id: yearField
            placeholderText: "Enter year"
            validator: IntValidator { bottom: 2023; top: 9999 }
        }
        TextField {
            id: quarterField
            placeholderText: "Enter quarter"
            validator: IntValidator { bottom: 1; top: 4 }
        }
        Button {
            text: "Update period"
            onClicked: {
                CtrDocuments.onUpdate(parseInt(quarterField.text), parseInt(yearField.text))
            }
        }
    }

    Row {
        TextField {
            id: dateInput
            placeholderText: "(yyyy-MM-dd)"
            validator: RegularExpressionValidator {
                regularExpression: /^(19|20)\d\d[-](0[1-9]|1[012])[-](0[1-9]|[12][0-9]|3[01])$/
            }
            onTextChanged: {
                var date = Date.fromLocaleString(Qt.locale(), text, "yyyy-MM-dd")
                console.log("Entered date: " + date.toLocaleDateString(Qt.locale()))
            }
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

            text: "Add declaration"
            width: 150

            onClicked: {
                console.log("Add document button")
                fileDialog.ok = function (path) {
                    CtrDocuments.onAddDeclaration(Number(sumData.text.replace(",", ".")), dateInput.text, path)
                }
                fileDialog.open()
            }
        }
    }

    Grid {
        anchors.horizontalCenter: parent.horizontalCenter
        columns: 2
        spacing: 10

        Button {
            id: remove_declaration

            text: "Remove declaration"
            width: 150

            onClicked: {
                CtrDocuments.onDeleteFile(hashId)
            }
        }

        Button {
            id: download_declaration

            text: "Download declaration"
            width: 150

            onClicked: {
                console.log("Add document button")
                CtrDocuments.onDownloadFile(documentsViewItem.hashId)
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
        text: "Your -^- Documents"
    }

    Row {
        TextField {
            id: dateInput1
            placeholderText: "(yyyy-MM-dd)"
            validator: RegularExpressionValidator {
                regularExpression: /^(19|20)\d\d[-](0[1-9]|1[012])[-](0[1-9]|[12][0-9]|3[01])$/
            }
            onTextChanged: {
                var date = Date.fromLocaleString(Qt.locale(), text, "yyyy-MM-dd")
                console.log("Entered date: " + date.toLocaleDateString(Qt.locale()))
            }
        }

        TextField {
            id: sumData1
            placeholderText: "sum > 10";
            validator: DoubleValidator {
                bottom: 0.01
                decimals: 2
                notation: DoubleValidator.StandardNotation
                top: Infinity
            }
        }

        Button {
            id: add_declaration1

            text: "Add act"
            width: 150

            onClicked: {
                console.log("Add document button")
                fileDialog.ok = function (path) {
                    console.log(Number(sumData1.text.replace(",", ".")) + " << Number")
                    CtrDocuments.onAddActOfWorkPerformed(Number(sumData1.text.replace(",", ".")), dateInput1.text, path)
                }
                fileDialog.open()
            }
        }
    }

    Grid {
        anchors.horizontalCenter: parent.horizontalCenter
        columns: 2
        spacing: 10

        Button {
            id: add

            text: "Remove"
            width: 150

            onClicked: {
                CtrDocuments.onDeleteFile(CtrDocuments.onCurrentDocumentUpdate(documentListModel.get(documents.currentIndex).hashId))
            }
        }

        Button {
            id: download

            text: "Download"
            width: 150

            onClicked: {
                console.log("Add document button")
                CtrDocuments.onDownloadFile()
            }
        }
    }

    Connections {
        function onDocumentsChanged(documents, declaration, saveCurrent) {
            console.log("onDocumentsChanged")
            let modelSize = documentListModel.count;
            let currentIndex = documentsView.currentIndex;

            // Reset model
            documentListModel.clear();
            for (var i = 0; i < documents.length; i++) {
                var document = documents[i];
                documentListModel.append({
                    "hashId" : document.hashId,
                    "file" : document.file,
                    "date" : document.date,
                    "sum" : document.sum,
                    "kind" : document.kindStr,
                });
            }
            if (declaration !== null) {
                declaration_loaded = true
                hashId = declaration.hashId
                file = declaration.file
                date = declaration.date
                sum = declaration.sum
                kind = declaration.kindStr
            }
            else {
                declaration_loaded = false
            }

            console.log("documents count " + documentListModel.count)

            // Try to save current index
            if (saveCurrent) {
                documentsView.currentIndex = currentIndex;
            }

            // If model is empty
            if (documentListModel.count === 0) {
                documentsView.currentIndex = 0;
            }
            if (modelSize === 0) {
                documentsView.currentIndex = 0;
            } else

                // Else
            if (documentListModel.count < modelSize) {
                documentsView.currentIndex = cardListModel.count - 1;
            }

            // Force update
            if (documentsView.currentIndex === 0) {
                documentsView.currentIndex = 1;
                documentsView.currentIndex = 0;
            }
        }
        function onShowWarning(message) {
            popUp.item.localText = message;
            popUp.item.open();
        }
        function onShowOk() {
            popUpInfo.item.localText = "it works"
            popUpInfo.item.open()
        }

        function onCloseDialog() {
            console.log("Called on close");
            fileDialog.close()
        }

        target: CtrDocuments
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
    FileDialog {
        id: fileDialog

        property var ok

        title: "Please choose a file"
        onAccepted: {
            ok(fileDialog.currentFile)
        }
    }
}
