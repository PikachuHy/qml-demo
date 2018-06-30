import QtQuick 2.4
import QtQuick.Controls 2.4

Item {
    id: item1
    width: 240
    height: 70
    property alias icon: icon
    property alias iconName: icon.name
    property alias leftside: leftside
    property alias mouseArea: mouseArea
    property alias displayColor: display.color
    property alias displayText: display.text

    Rectangle {
        id: rectangle
        color: "#ffffff"
        anchors.fill: parent

        MouseArea {
            id: mouseArea
            hoverEnabled: true
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
        }

        Rectangle {
            id: leftside
            width: 5
            color: "#ffffff"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
        }

        Label {
            id: display
            y: 28
            text: qsTr("Label")
            anchors.left: parent.left
            anchors.leftMargin: 100
            font.pixelSize: 20
            anchors.verticalCenter: parent.verticalCenter
        }

        MaterialIcon {
            id: icon
            width: 40
            height: 40
            anchors.left: parent.left
            anchors.leftMargin: 40
            size: 40
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
