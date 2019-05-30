import QtQuick 2.4
import QtQuick.Controls 2.3

Item {
    id: element1
    width: 1000
    height: 600
    property alias uploadArea: uploadArea

    UploadArea {
        id: uploadArea
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
    }

    Row {
        id: row
        height: 100
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: uploadArea.bottom
        anchors.topMargin: 10

        Text {
            id: link
            text: qsTr("![mark](http://cdn.pikachu.net.cn//book/csapp/ch01/1.png)")
            font.italic: true
            font.family: "Times New Roman"
            font.pixelSize: 24
        }

        Button {
            id: button
            text: qsTr("复制链接")
        }
    }
}









/*##^## Designer {
    D{i:2;anchors_width:200}
}
 ##^##*/
