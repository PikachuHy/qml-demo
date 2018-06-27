import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.2

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Button {
        id: button
        text: qsTr("Push Me")
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: {
            label.text = qsTr("Hello Qt")
        }
    }

    Label {
        id: label
        text: qsTr("Hello World")
        anchors.horizontalCenter: button.horizontalCenter
    }
}
