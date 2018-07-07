import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtQuick.Window 2.3
Item {
    width: 280
    height: 80
    property alias background: background
    Rectangle {
        id: background
        anchors.fill: parent

        Label {
            id: label
            x: 35
            y: 8
            text: qsTr("火绒安全")
            font.pixelSize: 16
        }

        Label {
            id: label1
            x: 35
            y: 54
            text: qsTr("正在保护您的电脑")
            font.pixelSize: 12
        }

        Label {
            id: label2
            x: 240
            y: 8
            text: qsTr("天")
            font.pointSize: 8
        }

        Label {
            id: label3
            x: 204
            y: 33
            text: qsTr("96")
            font.pixelSize: 40
        }
    }
}
