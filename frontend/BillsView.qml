import QtQuick 6.6
import QtQuick.Controls 6.6
import QtQuick.Layouts

Column {
    // Bills
    id: bills

    function disableButtons() {
        transfer_bill.enabled = false;
        block.enabled = false;
        history.enabled = false;
        remove.enabled = false;
    }
    function enableButtons() {
        transfer_bill.enabled = true;
        block.enabled = true;
        history.enabled = true;
        remove.enabled = true;
    }

    anchors.topMargin: 150
    anchors.verticalCenterOffset: 1000
    spacing: 100

    SwipeView {
        id: billsView

        anchors.horizontalCenter: parent.horizontalCenter
        height: 150
        width: 300

        onCurrentIndexChanged: {
            if (billListModel.count === 0) {
                return;
            }
            for (var i = 0; i < count; i++) {
                var item = itemAt(i);
                if (i === currentIndex) {
                    item.opacity = 1.0;
                } else if (i === currentIndex - 1 || i === currentIndex + 1) {
                    item.opacity = 0.0;
                } else {
                    item.opacity = 0.0;
                }
            }
            console.log("Current index " + currentIndex);
            CtrBills.onCurrentBillUpdate(billListModel.get(currentIndex).billNumber);
        }

        Repeater {
            model: billListModel

            delegate: Bill {
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
        id: text_bills_title

        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 23
        horizontalAlignment: Text.AlignHCenter
        text: "Your -^- Bills"
    }
    Grid {
        anchors.horizontalCenter: parent.horizontalCenter
        columns: 2
        spacing: 10

        Button {
            id: transfer_bill

            text: "Transfer to Bill"
            width: 150

            onClicked: {
                get_credentials.item.ok = function (str, value) {
                    CtrBills.onBillTransfer(str, value);
                };
                get_credentials.item.no = function (str, value) {};
                get_credentials.item.open();
            }
        }
        Button {
            id: block

            text: "Block"
            width: 150

            onClicked: {
                console.log("Block button clicked");
                CtrBills.onBlocked(!billListModel.get(billsView.currentIndex).isBlocked);
            }
        }
        Button {
            id: history

            text: "History"
            width: 150

            onClicked: {
                CtrBills.onHistory(billListModel.get(billsView.currentIndex).billNumber);
                console.log("History button clicked");
            }
        }
        Button {
            id: remove

            text: "Remove bill"
            width: 150

            onClicked: {
                if (billsView.count - 1 === 0) {
                    disableButtons();
                }
                CtrBills.onRemoveBill(billListModel.get(billsView.currentIndex).billNumber);
                console.log("Delete bill button");
            }
        }
        Button {
            id: add

            text: "Add bill"
            width: 150

            onClicked: {
                get_string.item.ok = function (str) {
                    console.log("Add bill button");
                    CtrBills.onAddBill(str);
                    billsView.currentIndex = billListModel.count - 1;
                };
                get_string.item.no = function (str) {};
                get_string.item.open();
            }
        }
    }
    Connections {
        function onBillsChanged(bills, saveCurrent) {
            let modelSize = billListModel.count;
            let currentIndex = billsView.currentIndex;

            // Reset model
            billListModel.clear();
            for (var i = 0; i < bills.length; i++) {
                var bill = bills[i];
                billListModel.append({
                        "billNumber": bill.number,
                        "balance": String(bill.value),
                        "isBlocked": bill.isBlocked,
                        "name": bill.name
                    });
            }

            // Try to save current index
            if (saveCurrent) {
                billsView.currentIndex = currentIndex;
            }

            // If model is empty
            if (billListModel.count === 0) {
                disableButtons();
                billsView.currentIndex = 0;
            }
            else {
                enableButtons();
            }
            if (modelSize === 0) {
                billsView.currentIndex = 0;
            } else

            // Else
            if (billListModel.count < modelSize) {
                billsView.currentIndex = cardListModel.count - 1;
            }

            // Force update
            if (billsView.currentIndex === 0) {
                billsView.currentIndex = 1;
                billsView.currentIndex = 0;
            }
            console.log("Index " + billsView.currentIndex);
        }
        function onShowWarning(message) {
            popUp.item.localText = message;
            popUp.item.open()
        }
        function onShowHistory() {
            main_stack_view.push("History.qml");
        }

        target: CtrBills
    }

    Loader {
        id: popUp

        anchors.horizontalCenter: parent.horizontalCenter
        source: "qrc:/main/frontend/PopUpWarning.qml"
        y: parent.height * 0.5
    }
}
