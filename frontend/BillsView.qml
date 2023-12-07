import QtQuick 6.6
import QtQuick.Controls 6.6
import QtQuick.Layouts

Column {
    // Bills
    id: bills

    spacing: 100
    anchors.verticalCenterOffset: 1000
    anchors.topMargin: 150

    SwipeView {
        id: billsView
        width: 300
        height: 150
        anchors.horizontalCenter: parent.horizontalCenter
        Repeater {
            model: billListModel
            delegate: Bill {
                opacity: 0.0

                Behavior on opacity {
                    NumberAnimation { duration: 500 }
                }
            }
        }
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
               }
               else {
                   item.opacity = 0.0;
               }
           }
           CtrBills.onCurrentBillUpdate(billListModel.get(currentIndex).billNumber)
       }
    }

    Text {
        id: text_bills_title
        text: "Your -^- Bills"
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 23
    }

    Grid {
     columns: 2
     spacing: 10
     anchors.horizontalCenter: parent.horizontalCenter

     Button {
         id: transfer_bill
         text: "Transfer to Bill"
         width: 150
         onClicked: {
            get_string.item.ok = function (str) { CtrBills.onBillTransfer(str) }
            get_string.item.no = function (str) {  }
            get_string.item.open()
         }
     }

     Button {
         id: block
         text: "Block"
         width: 150
         onClicked: {
            console.log("Block button clicked")
            CtrBills.onBlocked(!billListModel.get(billsView.currentIndex).isBlocked)
         }

     }

     Button {
         id: history
         text: "History"
         width: 150
         onClicked: {
            main_stack_view.push("History.qml")
            CtrBills.onHistory(billListModel.get(billsView.currentIndex).billNumber)
            console.log("History button clicked")
         }
     }

     Button {
        id: remove
        text: "Remove bill"
        width: 150
        onClicked: {
            if (billsView.count - 1 === 0) {
                transfer_bill.enabled = false
                block.enabled = false
                history.enabled = false
                remove.enabled = false
            }

            CtrBills.onRemoveBill(billListModel.get(billsView.currentIndex).billNumber)

            console.log("Delete bill button")
        }
    }

    Button {
        id: add
        text: "Add bill"
        width: 150
        onClicked: {
            transfer_bill.enabled = true
            block.enabled = true
            history.enabled = true
            remove.enabled = true

            get_string.item.ok = function (str) {
                console.log("Add bill button")
                CtrBills.onAddBill(str)
                billsView.currentIndex = billListModel.count - 1
            }
            get_string.item.no = function (str) {  }
            get_string.item.open()
        }
    }
    }

    Connections {
        target: CtrBills
        function onBillsChanged(bills, saveCurrent) {
            var index = billListModel.count
            var currentIndex = billsView.currentIndex
            billListModel.clear()
            for (var i = 0; i < bills.length; i++) {
                var bill = bills[i];
                billListModel.append({"billNumber": bill.number,
                                     "balance": String(bill.value),
                                     "isBlocked": bill.isBlocked});
            }
            if (saveCurrent) {
                billsView.currentIndex = currentIndex
                return
            }
            if (billListModel.count < index) {
                console.log("Update count - 1")
                billsView.currentIndex = billListModel.count - 1
            }
            else if (index === 0) {
                billsView.currentIndex = 0
            }
            else {
                console.log("Update index - 1")
                billsView.currentIndex = index - 1
            }
            console.log("Index " + billsView.currentIndex)
        }
    }
}
