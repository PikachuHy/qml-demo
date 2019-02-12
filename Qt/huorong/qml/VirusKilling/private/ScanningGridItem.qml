import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtQuick.Window 2.3
import "../../components"
import controller 1.0
Item {
    width: 230
    height: 190
    property alias imageSource: image.source
    property alias scanning: scanning.visible
    property alias title: title.text

    Rectangle {
        id: rectangle
        color: "#f8f8f8"
        anchors.fill: parent
        Image{
            id:image
            width: 100
            height: 100
            source: ""
            anchors.centerIn: parent
        }

        Label {
            id: title
            text: qsTr("系统修复")
            font.pixelSize: 24
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: image.bottom
            anchors.topMargin: 0
        }

        Label {
            id: scanning
            text: qsTr("扫描中...")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: image.bottom
            anchors.topMargin: 26
        }

    }
}
