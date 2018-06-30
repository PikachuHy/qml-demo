import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import "../"

Item {
    id: item1
    width: 350
    height: 100
    property alias downloadIcon: downloadIcon
    property alias iconSource: image.source
    property alias name: label.text
    property alias description: label1.text
    property alias shadow: shadow
    property alias dropShadow: dropShadow

    DropShadow {
        id: dropShadow
        anchors.fill: pane
        verticalOffset: 3
        radius: 8.0
        samples: 16
        color: "#80000000"
        source: shadow
        visible: false
    }
    Pane {
        id: pane
        anchors.fill: parent

        Label {
            id: label
            y: 18
            color: "#666666"
            text: qsTr("火绒剑")
            anchors.left: parent.left
            anchors.leftMargin: 100
            font.pixelSize: 22
        }

        Label {
            id: label1
            y: 57
            color: "#aaaaaa"
            text: qsTr("专业人士使用的安全分析工具")
            anchors.left: parent.left
            anchors.leftMargin: 100
            font.pixelSize: 16
        }

        Image {
            id: image
            x: 110
            y: 25
            width: 80
            height: 80
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 10
            source: "qrc:/image/tool/1.png"
        }

        DownloadIcon {
            id: downloadIcon
            visible: false
            anchors.bottom: image.bottom
            anchors.bottomMargin: 0
            anchors.right: image.right
            anchors.rightMargin: 0
        }
    }

    Rectangle {
        id: shadow
        color: "#00000000"
        border.color: "#eee"
        anchors.fill: parent
        visible: false
    }
}
