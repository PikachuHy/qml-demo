import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import "../"
Item {
    id: root
    implicitWidth:  30
    implicitHeight:  30

    DropShadow {
        id: dropShadow
        anchors.fill: root
        verticalOffset: 1
        radius: 4
        samples: 8
        color: "#80000000"
        source: shadow
        visible: true
    }
    Rectangle {
        id: iconBackground
        width: 20
        height: 20
        color: "#43991f"
        radius: 10
        z: 0
        anchors.centerIn: parent
        visible: true
    }

    FontAwesome5FreeIcon {
        id: downloadIcon
        color: "#ffffff"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        size: 30
        font.pixelSize: 14
        name: "arrow-alt-circle-down"
        visible: true
        z: 1
        anchors.centerIn: parent
    }


    Rectangle {
        id: shadow
        width: parent.width - 1
        height: parent.height - 1
        anchors.centerIn: parent
        color: "#00000000"
        border.color: "#eee"
        radius: parent.width / 2
        visible: false
    }
}
