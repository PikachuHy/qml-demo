import QtQuick 2.11
import QtQuick.Controls 2.4
Button {
    id: root
    property alias color: icon.color
    property alias size: icon.size
    implicitWidth: 40
    implicitHeight: 40
    flat: true
    contentItem:  FontAwesome5FreeIcon {
        id: icon
        property bool pressed: false
        name: "toggle-off"
        onPressedChanged: {
            icon.name = pressed? "toggle-on":"toggle-off"
        }
    }
    MouseArea{
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onPressed: {
            console.log("press")
            icon.pressed=!icon.pressed
        }
    }

}
