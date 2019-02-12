import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import "../components"
import "./private"

Item {
    width: 700
    height: 500
    property alias stopButton: stopButton
    property alias pauseButton: pauseButton
    property alias highSpeedButton: highSpeedButton
    property alias normalButton: normalButton

    Column {
        id: column
        spacing: 10
        anchors.fill: parent

        Row {
            id: row
            height: 50
            spacing: 20
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0

            Label {
                id: label
                width: 450
                height: 40
                text: qsTr("C:\\Windows\\SYSTEM32\\samsrv.dll")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 24
            }
            MyButton {
                id: pauseButton
                width: 100
                height: 40
                text: "暂停"
                checkable: true
                normalTextColor: "white"
                normalBackgroundColor: "#ffa924"
                hoverBackgroundColor: "#ff9600"
            }
            MyButton {
                id: stopButton
                width: 100
                height: 40
                text: "停止"
                normalTextColor: "orange"
                normalBackgroundColor: "white"
            }
        }

        ProgressBar {
            id: progressBar
            to: 100
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            value: 20
        }

        RowLayout {
            id: row1
            height: 50
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0

            Rectangle {
                id: rectangle
                width: 112
                height: 27
                color: "#00000000"
                radius: 3
                Layout.preferredWidth: -1
                border.color: "#bda184"
                border.width: 1
                Row {
                    height: 25
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    MyButton {
                        id: normalButton
                        width: 55
                        height: parent.height
                        text: "常规"
                        normalBackgroundColor: "#bda184"
                        normalTextColor: "white"
                        checkable: true
                        checked: true
                    }
                    MyButton {
                        id: highSpeedButton
                        height: parent.height
                        width: 55
                        text: "高速"
                        normalBackgroundColor: "white"
                        normalTextColor: "#bda184"
                        checkable: true
                        checked: false
                    }
                }
            }

            CheckBox {
                id: checkBox
                text: qsTr("查杀完成后自动关机")
                Layout.fillWidth: true
            }

            Label {
                id: label1
                text: qsTr("已用时间：00:00:10")
            }
        }
        Grid {
            spacing: 5
            rows: 2
            columns: 3
            ScanningGridItem {
                imageSource: "qrc:/image/scanning/1.png"
                title: "系统修复"
                scanning: true
            }
            ScanningGridItem {
                imageSource: "qrc:/image/scanning/2.png"
                title: "系统进程"
                scanning: false
            }
            ScanningGridItem {
                imageSource: "qrc:/image/scanning/3.png"
                title: "启动项"
                scanning: false
            }
            ScanningGridItem {
                imageSource: "qrc:/image/scanning/4.png"
                title: "服务与驱动"
                scanning: false
            }
            ScanningGridItem {
                imageSource: "qrc:/image/scanning/5.png"
                title: "浏览器插件"
                scanning: false
            }
            ScanningGridItem {
                imageSource: "qrc:/image/scanning/6.png"
                title: "系统关键位置"
                scanning: false
            }
        }
    }
}
