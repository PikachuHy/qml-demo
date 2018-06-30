import QtQuick 2.4

Item {
    width: 40
    height: 40
    property alias icon: icon
    property alias iconName: icon.name
    property alias mouseArea: mouseArea
    property alias backgroundColor: background.color

    Rectangle {
        id: background
        color: "#ffffff"
        anchors.fill: parent

        MouseArea {
            id: mouseArea
            hoverEnabled: true
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
        }

        FontAwesome5FreeIcon {
            id: icon
            width: 20
            height: 20
            size: 20
            anchors.centerIn: parent
        }
    }
}
