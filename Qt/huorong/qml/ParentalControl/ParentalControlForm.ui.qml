import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

import "../components"
import controller 1.0

Item {
    width: 750
    height: 520
    property alias switch1: switch1

    Pane {
        id: pane
        anchors.fill: parent

        ColumnLayout {
            id: columnLayout
            width: 409
            height: 397
            spacing: 20

            Label {
                id: label
                color: "#666666"
                text: qsTr("管理该计算机使用网络和程序的方式和时间")
                font.pixelSize: 26
            }

            Label {
                id: label1
                color: "#aaa"
                text: qsTr("将此计算机设置为适合家人使用的情况")
                font.pixelSize: 18
            }


            Column {
                id: column
                width: 200
                height: 400
                spacing: 10
                MyItem {
                    iconName: "wifi"
                    displayText: "上网时段控制"
                }
                SeparationLine {
                }
                MyItem {
                    iconName: "briefcase"
                    displayText: "程序执行控制"
                }
                SeparationLine {
                }
                MyItem {
                    iconName: "file"
                    displayText: "网站内容控制"
                }
                SeparationLine {
                }
                MyItem {
                    iconName: "lock"
                    displayText: "设备使用控制"
                }
            }
        }

        Image {
            id: image
            x: 401
            y: 37
            width: 332
            height: 459
            sourceSize.height: 459
            sourceSize.width: 332
            source: "qrc:/image/background.png"
        }

        MySwitch {
            id: switch1
            color: "#bbbbbb"
            z: 1
            size: 40
            anchors.right: parent.right
            anchors.rightMargin: 50
            anchors.top: parent.top
            anchors.topMargin: 20
        }
    }
}
