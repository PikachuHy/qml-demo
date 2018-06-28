import QtQuick 2.11

Item {
    width: 200
    height: 200
    property alias buttonColor: button.color
    property alias displayText: display.text

    Rectangle {
        id: button
        width: 200
        height: 200
        color: "#ff0000"
        radius: width * 0.5
        anchors.fill: parent

        Text {
            id: display
            x: 176
            y: 194
            text: qsTr("Hello Qt")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.family: "Times New Roman"
            font.pixelSize: 24
        }
    }
}
