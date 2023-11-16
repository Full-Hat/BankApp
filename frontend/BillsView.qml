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
           console.log(billListModel.get(currentIndex).billId)
           CtrBills.onBillChoosed(billListModel.get(currentIndex).billId)
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
            console.log("Transfer to Bill button clicked")
            get_string.item.ok = function (str) { CtrBills.onTransfer(str) }
            get_string.item.no = function (str) {  }
            get_string.item.open()
         }
     }

     Button {
         id: tramsfer_bill
         text: "Transfer to Bill"
         width: 150
         onClicked: {
            console.log("Transfer to Bill button clicked")
            get_string.item.ok = function (str) { CtrBills.onTransfer(str) }
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
            billListModel.get(billsView.currentIndex).isBlocked =
                !billListModel.get(billsView.currentIndex).isBlocked
         }

     }

     Button {
         id: history
         text: "History"
         width: 150
         onClicked: {
            main_stack_view.push("History.qml")
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
                tramsfer_bill.enabled = false
                block.enabled = false
                history.enabled = false
                remove.enabled = false
            }

            else if (billListModel.currentIndex === 1 || (typeof el === 'undefined')) {
                billsView.currentIndex = billsView.count - 1;
            }

            console.log("Delete bill button")
            console.log(billListModel.currentIndex)
            billListModel.remove(billsView.currentIndex)
        }
    }

    Button {
        id: add
        text: "Add bill"
        width: 150
        onClicked: {
            transfer_bill.enabled = true
            tramsfer_bill.enabled = true
            block.enabled = true
            history.enabled = true
            remove.enabled = true

            console.log("Add bill button")
            billListModel.append({"billId": "", "billNumber": "", "balance": "", "isBlocked": false})
            billsView.currentIndex = billListModel.count - 1
        }
    }
    }

    Connections {
        target: CtrBills
        function onAddBill(id, number, balance, is_blocked) {
            billListModel.append({"billId": id, "billNumber": number, "balance": balance, "isBlocked": is_blocked})
        }
        function onRemoveBill(id) {
            for (var i = 0; i < billListModel.count; ++i) {
               if (billListModel.get(i).id === id) {
                   billListModel.remove(i);
                   break;
               }
           }
        }
    }
}
