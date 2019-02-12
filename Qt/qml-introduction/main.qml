import QtQuick 2.11
import QtQuick.Window 2.11

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("QML Introduction")

    Background {
        id: background
        anchors.fill: parent
        target: sender
        Sender {
            id: sender
            y: 214
            displayText: "Sender"
            anchors.verticalCenterOffset: 0
            anchors.left: parent.left
            anchors.leftMargin: 50
            anchors.verticalCenter: parent.verticalCenter
            target: receiver
        }

        Receiver {
            id: receiver
            x: 532
            y: 240
            displayText: "Receiver"
            anchors.right: parent.right
            anchors.rightMargin: 50
            anchors.verticalCenter: parent.verticalCenter
            width: sender.width
            visible: sender.visible
        }
    }
}
