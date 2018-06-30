import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import "../"

Pane {
    id: pane
    width: 400
    height: 60
    property alias fontAwesome5FreeIcon1: fontAwesome5FreeIcon1
    property alias display: display
    property alias iconName: fontAwesome5FreeIcon.name
    property alias displayText: display.text

    FontAwesome5FreeIcon {
        id: fontAwesome5FreeIcon
        color: "#aaaaaa"
        font.pixelSize: 30
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
    }

    Label {
        id: display
        color: "#2b2626"
        text: qsTr("Label")
        font.pointSize: 14
        anchors.left: parent.left
        anchors.leftMargin: 100
        anchors.verticalCenter: parent.verticalCenter
    }

    FontAwesome5FreeIcon {
        id: fontAwesome5FreeIcon1
        name: "chevron-right"
        anchors.right: parent.right
        anchors.rightMargin: 30
        anchors.verticalCenter: parent.verticalCenter
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
    }
}
