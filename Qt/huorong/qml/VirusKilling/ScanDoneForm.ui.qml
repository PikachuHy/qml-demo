import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import "../components"
import "./private"

Item {
    id: item1
    width: 750
    height: 500
    property alias doneButton: doneButton

    Image {
        id: image
        x: 343
        y: 45
        width: 394
        height: 455
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        source: "../../image/background2.png"
    }
    Column {
        id: column
        anchors.fill: parent

        Label {
            id: label
            height: 80
            color: "#666666"
            text: qsTr("您的电脑没有风险项目")
            font.pixelSize: 32
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        GridLayout {
            id: grid
            width: 400
            height: 150
            columnSpacing: 20
            rows: 2
            columns: 2
            ScanDoneGridItem {
                iconName: "file"
                title: "扫描对象"
                value: "518个"
            }
            ScanDoneGridItem {
                iconName: "clock"
                title: "总计用时"
                value: "00:00:03"
            }
            ScanDoneGridItem {
                iconName: "exclamation-circle"
                title: "发现风险"
                value: "0个"
            }
            ScanDoneGridItem {
                iconName: "check"
                title: "处理完成"
                value: "0个"
            }
        }
        MyButton {
            id: doneButton
            width: 180
            height: 70

            normalTextColor: "white"
            normalBackgroundColor: "#ffa924"
            hoverBackgroundColor: "#ff9600"

            text: "完成"
            textSize: 32
        }
    }
}
