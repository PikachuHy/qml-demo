import QtQuick 2.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

Item {
    width: 400
    height: 400

    Column {
        height: 200
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top

        FormItem {
            Layout.fillWidth: true
        }
        FormItem {
            Layout.fillWidth: true
        }
        FormItem {
            Layout.fillWidth: true
        }
        FormItem {
            Layout.fillWidth: true
        }
        FormItem {
            Layout.fillWidth: true
        }
        FormItem {
            Layout.fillWidth: true
        }
    }
}
