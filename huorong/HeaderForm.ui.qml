import QtQuick 2.11
import QtQuick.Controls 2.4

Item {
    id: item1
    width: 400
    height: 100
    property alias titleText: title.text
    property alias mouseArea: mouseArea
    property alias menuButton: menuButton
    property alias minimizeButton: minimizeButton

    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }
    Rectangle {
        id: rectangle
        height: 100
        color: "#ffffff"
        anchors.fill: parent

        Image {
            id: image
            y: 50
            anchors.left: parent.left
            anchors.leftMargin: 8
            anchors.verticalCenter: parent.verticalCenter
            source: "image/logo.png"
        }

        Text {
            id: title
            color: "#666666"
            text: qsTr("家长控制")
            anchors.left: image.right
            anchors.leftMargin: 50
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 32
        }
    }

    Row {
        id: row
        width: 200
        spacing: 10
        layoutDirection: Qt.RightToLeft
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0

        CloseButton {
            id: closeButton
            z: 1
        }

        MinimizeButton {
            id: minimizeButton
        }

        MenuButton {
            id: menuButton
        }
    }
}
