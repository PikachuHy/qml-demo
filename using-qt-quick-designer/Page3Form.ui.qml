import QtQuick 2.11
import QtQuick.Controls 2.4

Page {
    width: 600
    height: 400
    property alias label1: label1
    property alias progressBar: progressBar
    property alias dial: dial
    property alias button: button
    property alias comboBox: comboBox
    property alias textField: textField

    header: Label {
        text: qsTr("Page 3")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    Row {
        id: row
        anchors.leftMargin: 0
        spacing: 25
        padding: 20
        anchors.fill: parent

        Column {
            id: column
            width: 200
            height: 400
            spacing: 10

            Label {
                id: label
                text: qsTr("Enter a name")
            }

            TextField {
                id: textField
            }

            ComboBox {
                id: comboBox
            }

            Button {
                id: button
                text: qsTr("Order")
            }
        }

        Column {
            id: column1
            width: 200
            height: 400
            spacing: 10

            Dial {
                id: dial
                to: 20
                from: 1
                value: 1
            }

            ProgressBar {
                id: progressBar
                to: 20
                from: 1
                value: 1
            }

            Label {
                id: label1
                text: qsTr("1 years old")
            }
        }
    }
}
