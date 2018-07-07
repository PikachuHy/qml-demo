import QtQuick 2.4
import QtQuick.Controls 2.4

Button {
    id: control
    width: 400
    height: 200
    text: "Button"
    property alias backgroundColor: background.color
    property alias displayText: display.text
    property alias displayColor: display.color
    background: Rectangle {
        id: background

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
        }
    }
    contentItem: Label {
        id: display
        //        text: control.text
        font: control.font
        color: "#262b28"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
}
