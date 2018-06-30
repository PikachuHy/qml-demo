import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

Item {
    width: 750
    height: 500
    property alias arrowButton: arrowButton
    property alias listView: listView

    Rectangle {
        id: rectangle
        color: "#ffffff"
        anchors.fill: parent

        AnimatedImage {
            id: animated
            x: 352
            y: 0
            width: 398
            height: 412
            z: 0
            source: "qrc:/image/animation.gif"
        }
        Column {
            id: column
            width: 262
            height: 423
            anchors.left: parent.left
            anchors.leftMargin: 50
            spacing: 0

            Label {
                id: label
                color: "#696969"
                text: qsTr("火绒正在保护您的电脑")
                font.bold: true
                font.family: "Tahoma"
                font.pointSize: 24
            }

            RowLayout {
                id: rowLayout
                width: 107
                height: 100
                spacing: 10

                Label {
                    id: label1
                    color: "#808080"
                    text: qsTr("已保护")
                    font.pointSize: 16
                }

                Label {
                    id: label2
                    color: "#008000"
                    text: qsTr("87")
                    font.pointSize: 16
                }

                Label {
                    id: label3
                    color: "#808080"
                    text: qsTr("天")
                    font.pointSize: 16
                }
            }

            Item {
                id: column2
                width: 200
                height: 400

                Row {
                    id: row
                    width: 100
                    height: 70
                    spacing: 0

                    MyButton {
                        id: quickKillingButton
                        width: 175
                        height: 70
                        font.pointSize: 16
                        displayColor: "#ffffff"
                        displayText: qsTr("快速查杀")
                    }

                    ArrowButton {
                        id: arrowButton
                        width: 50
                        height: 70
                        Layout.fillHeight: false
                    }
                }

                KillingListView {
                    id: listView
                    z: -1
                }
            }
        }

        MyButton {
            id: securityButton
            x: 571
            y: 418
            width: 100
            height: 50
            anchors.right: parent.right
            anchors.rightMargin: 50
            anchors.verticalCenter: tag.verticalCenter
            normalColor: "#ffffff"
            hoverColor: "#ffffff"
            backgroundColor: "#ffffff"
            displayColor: "#ff9600"
            displayText: qsTr("信任区")
            flat: true
        }

        MyButton {
            id: isolateButton
            x: 408
            y: 418
            width: 100
            height: 50
            font.pointSize: 9
            anchors.right: securityButton.left
            anchors.rightMargin: 50
            anchors.verticalCenter: tag.verticalCenter
            hoverColor: "#ffffff"
            normalColor: "#ffffff"
            backgroundColor: "#ffffff"
            displayColor: "#ff9600"
            displayText: qsTr("隔离区")
            flat: true
        }

        Label {
            id: tag
            color: "#787878"
            text: qsTr("版本：4.0.65.3 病毒库：2018-06-28 15:45")
            font.bold: true
            Layout.rowSpan: 3
            Layout.fillHeight: false
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 50
        }
    }
}
