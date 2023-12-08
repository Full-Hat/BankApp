import QtQuick 6.6
import QtQuick.Controls 6.6
import QtQuick.Layouts

Column {
    // Credits
    id: credits

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
            console.log("Current index " + currentIndex);
            CtrCredits.onCurrentKreditUpdate(creditListModel.get(currentIndex).creditNumber);
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
    Grid {
        anchors.horizontalCenter: parent.horizontalCenter
        columns: 2
        spacing: 10
        
        Button {
            id: add

            text: "Add credit"
            width: 150

            onClicked: {
                get_string.item.ok = function (str) {
                    console.log("Add credit button");
                    CtrCredits.onAddKredit(str);
                    creditsView.currentIndex = creditListModel.count - 1;
                };
                get_string.item.no = function (str) {};
                get_string.item.open();
            }
        }
    }
    Connections {
        function onCreditsChanged(credits, saveCurrent) {
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

            // Try to save current index
            if (saveCurrent) {
                creditsView.currentIndex = currentIndex;
            }

            // If model is empty
            if (creditListModel.count === 0) {
                disableButtons();
                creditsView.currentIndex = 0;
            } else {
                enableButtons();
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
            console.log("Index " + creditsView.currentIndex);
        }
        function onShowWarning(message) {
            popUp.item.localText = message;
            popUp.item.open();
        }

        target: CtrCredits
    }
    Loader {
        id: popUp

        anchors.horizontalCenter: parent.horizontalCenter
        source: "qrc:/main/frontend/PopUpWarning.qml"
        y: parent.height * 0.5
    }
}
