import QtQuick 2.11
import QtQuick.Controls 2.4

Button {
    id: button
    width: 400
    height: 200
    property alias textSize: button.font.pixelSize
    property alias textColor: display.color
    property alias backgroundColor: background.color
    text: "Button"
    property alias mouseArea: mouseArea
    background: Rectangle {
        id: background
    }
    contentItem: Label {
        id: display
        font: button.font
        text: button.text
        color: "#ffffff"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    MouseArea {
        id: mouseArea
        hoverEnabled: true
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
    }
}
