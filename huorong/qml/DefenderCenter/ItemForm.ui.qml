import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

import "../"
import "../components"

Item {
    width: 225
    height: 45
    property alias fonticon: fontAwesome5FreeIcon
    property alias display: display
    property alias iconMouseArea: iconMouseArea
    property alias textMouseArea: textMouseArea
    property alias fontAwesome5FreeIconName: fontAwesome5FreeIcon.name
    property alias displayText: display.text

    Rectangle {
        id: background
        color: "#ffffff"
        anchors.fill: parent

        Label {
            id: display
            x: 14
            text: qsTr("Label")
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            font.pointSize: 10

            MouseArea {
                id: textMouseArea
                hoverEnabled: true
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
            }
        }

        FontAwesome5FreeIcon {
            id: fontAwesome5FreeIcon
            width: 30
            color: "#6ab03b"
            size: 30
            font.pixelSize: 16
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            MouseArea {
                id: iconMouseArea
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
            }
        }
    }
}
