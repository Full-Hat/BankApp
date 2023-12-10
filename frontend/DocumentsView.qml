import QtQuick 6.6
import QtQuick.Controls 6.6
import QtQuick.Layouts
import QtQuick.Dialogs
import Qt5Compat.GraphicalEffects

Column {
    id: documentsViewItem

    anchors.topMargin: 150
    anchors.verticalCenterOffset: 1000
    spacing: 100

    Rectangle {
        width: 300
        height: 150
        border.color: "gray"
        border.width: 3
        radius: 20
        anchors.horizontalCenter: parent.horizontalCenter

        Text {
            text: "Hello world"
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

    Grid {
        anchors.horizontalCenter: parent.horizontalCenter
        columns: 2
        spacing: 10

        Button {
            id: add

            text: "Try"
            width: 150

            onClicked: {
                console.log("Add document button")
                fileDialog.open()
                CtrDocuments.onAddActOfWorkPerformed(1.1, "2023-12-09", "/Users/full-hat/Downloads/milan-vasek-island-finalb.jpg")
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
        function onDocumentsChanged(documents, saveCurrent) {
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
        title: "Please choose a file"
        onAccepted: {
            console.log("You chose: " + fileDialog.fileUrl)
        }
    }
}
