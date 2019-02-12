import QtQuick 2.11
import QtQuick.Controls 2.4
Item {
    width: 225
    height: 160
    focus: false
    property string hoverBackgroundColor
    property string normalBackgroundColor
    property alias displayText: display.text
    property alias displayBackgroundColor: displayBackground.color
    property alias backgroundColor: background.color
    property alias mouseArea: mouseArea
    onNormalBackgroundColorChanged: {
        displayBackgroundColor = normalBackgroundColor
        backgroundColor = normalBackgroundColor
    }


    Rectangle {
        id: background
        color: "#ffffff"
        anchors.fill: parent

        MouseArea {
            id: mouseArea
            hoverEnabled: true
            anchors.fill: parent
            onEntered: {
                displayBackgroundColor = hoverBackgroundColor
            }
            onExited: {
                displayBackgroundColor = normalBackgroundColor
            }
        }
    }

    Rectangle {
        id: displayBackground
        color: "#ffffff"
        anchors.bottomMargin: 5
        anchors.topMargin: 5
        anchors.fill: parent
    }
    Text {
        id: display
        color:"white"
        text: qsTr("Text")
        font.pixelSize: 24
        anchors.centerIn: parent
    }
}
