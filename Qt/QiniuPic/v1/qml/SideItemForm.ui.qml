import QtQuick 2.4
import QtGraphicalEffects 1.0

Item {
    id: root
    width: 200
    height: 100
    property alias rectangleVisible: rectangle.visible
    property alias titleColor: title.color
    property alias imageSource: image.source
    property alias titleText: title.text
    property alias mouseArea: mouseArea
    property alias image: image

    Image {
        id: image
        x: 16
        y: 18
        width: 64
        height: 64
        anchors.left: parent.left
        anchors.leftMargin: 16
        anchors.verticalCenter: parent.verticalCenter
        source: "../icon/up-load_1296db_64x64.png"
        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: title
        x: 96
        y: 40
        text: qsTr("图片上传")
        font.family: "Times New Roman"
        anchors.left: parent.left
        anchors.leftMargin: 96
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 16
    }

    MouseArea {
        id: mouseArea
        hoverEnabled: true
        anchors.fill: parent
    }

    Rectangle {
        id: rectangle
        width: 5
        height: root.height - 40
        color: "#1296db"
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 10
    }
}






/*##^## Designer {
    D{i:2;anchors_x:16}
}
 ##^##*/
