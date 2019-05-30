import QtQuick 2.4
import QtQuick.Controls 2.3

Item {
    id: element
    width: 1000
    height: 600
    property alias titleText: title.text
    property alias container: container
    property alias side: side

    Side {
        id: side
    }

    Item {
        id: container
        anchors.left: side.right
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
    }

    Text {
        id: title
        text: qsTr("图片上传")
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.horizontalCenter: container.horizontalCenter
        font.family: "Times New Roman"
        font.pixelSize: 24
    }
}












/*##^## Designer {
    D{i:1;anchors_height:200;anchors_width:200;anchors_x:59;anchors_y:164}
}
 ##^##*/
