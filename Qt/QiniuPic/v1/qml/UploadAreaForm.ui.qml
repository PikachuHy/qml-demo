import QtQuick 2.4

Rectangle {
    id: rectangle
    width: 400
    height: 400
    color: "#ffffff"
    radius: 5
    border.width: 1
    border.color: "#000000"

    Image {
        id: image
        anchors.centerIn: parent
        fillMode: Image.PreserveAspectFit
        source: "../icon/up-load_1296db_64x64.png"
    }

    Text {
        id: element
        text: qsTr("将文件拖拽到此处，或者点击上传")
        font.family: "Times New Roman"
        anchors.top: image.bottom
        anchors.topMargin: 0
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 24
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }
}
