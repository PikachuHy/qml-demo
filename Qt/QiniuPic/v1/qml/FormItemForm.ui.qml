import QtQuick 2.4
import QtQuick.Controls 2.3

Item {
    id: element1
    width: 200
    height: 60

    Text {
        id: element
        text: qsTr("表单标签")
        font.family: "Times New Roman"
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 16
    }

    TextField {
        y: 40
        height: 30
        text: qsTr("Text Edit")
        anchors.left: element.right
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.verticalCenter: parent.verticalCenter
        font.family: "Times New Roman"
        font.pixelSize: 16
    }
}

/*##^## Designer {
    D{i:2;anchors_width:80;anchors_x:112}
}
 ##^##*/
