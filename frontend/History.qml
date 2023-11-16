import QtQuick 2.12
import QtQuick.Controls 2.12

Page {
 id: transactionHistoryPage
 title: "Transaction History"

 ScrollView {
 id: transactionScrollView
 anchors.fill: parent

 ListView {
     id: transactionListView
     anchors.fill: parent
     model: ListModel {
         ListElement { source: "forum.qt.io"; target: "Target 1"; value: "Value 1" }
         ListElement { source: "doc.qt.io"; target: "Target 2"; value: "Value 2" }
         // Add more transactions here
     }
     delegate: Rectangle {
         width: transactionListView.width
         height: 50
         color: index % 2 === 0 ? "white" : "lightgray" // Alternate row colors

         Row {
            width: parent.width
            spacing: 10
            y: parent.height / 2 - 10

            Column {
               width: parent.width / 3
               Text {
                text: model.source
                anchors.horizontalCenter: parent.horizontalCenter
                verticalAlignment: Text.AlignVCenter
               }
            }

            Column {
               width: parent.width / 3
               Text {
                text: model.target
                anchors.horizontalCenter: parent.horizontalCenter
                verticalAlignment: Text.AlignVCenter
               }
            }

            Column {
               width: parent.width / 3
               Text {
                text: model.value
                anchors.horizontalCenter: parent.horizontalCenter
                verticalAlignment: Text.AlignVCenter
               }
            }
         }
     }
 }
 }

 Button {
 id: exitButton
 text: "Exit"
 anchors.bottom: parent.bottom
 anchors.horizontalCenter: parent.horizontalCenter
 width: 200
 height: 50
 onClicked: {
   main_stack_view.pop()
 }
 }
}
