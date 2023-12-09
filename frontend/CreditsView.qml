import QtQuick 6.6
import QtQuick.Controls 6.6
import QtQuick.Layouts

Column {
    id: creditsViewItem

    anchors.topMargin: 150
    anchors.verticalCenterOffset: 1000
    spacing: 100

    SwipeView {
        id: creditsView

        anchors.horizontalCenter: parent.horizontalCenter
        height: 150
        width: 300

        onCurrentIndexChanged: {
            if (creditListModel.count === 0) {
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
            console.log("Current credit index " + currentIndex);
            CtrCredits.onCurrentCreditUpdate(creditListModel.get(currentIndex).hashId);
        }

        Repeater {
            model: creditListModel

            delegate: Credit {
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
        id: text_credits_title

        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 23
        horizontalAlignment: Text.AlignHCenter
        text: "Your -^- Credits"
    }

    Row {
        ComboBox {
            id: combo
            editable: false
            model: ListModel {
                id: model
            }

            onCurrentIndexChanged: {
                console.log("Choose" + currentIndex)
                if (currentIndex === 0) {
                    yearBox.enabled = false;
                    sumField.enabled = false;
                    yearBox.currentIndex = 0;
                }
                else {
                    yearBox.enabled = true;
                    CtrCredits.onUpdateDatesEvent();
                }
            }
        }
        ComboBox {
            id: yearBox
            editable: false
            enabled: false
            model: ListModel {
                id: yearModel
                //ListElement { text: "None" }
            }

            onCurrentIndexChanged: {
                console.log("Choose" + currentIndex + currentText)
                if (currentIndex === 0) {
                    sumField.enabled = false;
                }
                else {
                    sumField.enabled = true;
                }
            }
        }
        TextField {
            id: sumField
            placeholderText: "sum > 10";
            validator: DoubleValidator {
                bottom: 0.01
                decimals: 2
                notation: DoubleValidator.StandardNotation
                top: Infinity
            }
        }
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
                console.log("Add credit button" + yearBox.text + " " + parseInt(yearBox.currentText));
                CtrCredits.onAddCredit(Number(sumField.text), parseInt(yearBox.currentText));
            }
        }
    }

    Connections {
        function onCreditsChanged(credits, saveCurrent) {
            console.log("onCreditsChanged")
            let modelSize = creditListModel.count;
            let currentIndex = creditsView.currentIndex;

            // Reset model
            creditListModel.clear();
            for (var i = 0; i < credits.length; i++) {
                var credit = credits[i];
                creditListModel.append({
                        "hashId": credit.hashId,
                        "date": credit.date,
                        "years": credit.years,
                        "interstrait": credit.interstrait,
                        "bodySum": credit.bodySum,
                        "sum": credit.sum,
                        "payedSum": credit.payedSum
                    });
            }

            console.log("credits count " + creditListModel.count)

            // Try to save current index
            if (saveCurrent) {
                creditsView.currentIndex = currentIndex;
            }

            // If model is empty
            if (creditListModel.count === 0) {
                creditsView.currentIndex = 0;
            }
            if (modelSize === 0) {
                creditsView.currentIndex = 0;
            } else

            // Else
            if (creditListModel.count < modelSize) {
                creditsView.currentIndex = cardListModel.count - 1;
            }

            // Force update
            if (creditsView.currentIndex === 0) {
                creditsView.currentIndex = 1;
                creditsView.currentIndex = 0;
            }
        }
        function onShowWarning(message) {
            popUp.item.localText = message;
            popUp.item.open();
        }
        function onUpdateInterestRates(objs) {
            model.clear()
            model.append({"text": "None"})
            for (var i = 0; i < objs.length; i++) {
                var credit = objs[i];
                model.append({"text": credit.interstrait.toString()});
            }
            combo.currentIndex = 0
        }
        function onUpdateDates(objs) {
            yearModel.clear()
            yearModel.append({"text": "None"})
            for (var i = 0; i < objs.length; i++) {
                var credit = objs[i];
                yearModel.append({"text": credit.years.toString()});
            }
            yearBox.currentIndex = 0
        }
        function onShowOk() {
            popUpInfo.item.localText = "it works"
            popUpInfo.item.open()
        }

        target: CtrCredits
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
