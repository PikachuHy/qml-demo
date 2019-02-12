import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtQuick.Window 2.3
import "../../components"
Item {
    width: 180
    height: 40
    property alias iconName: icon.name
    property alias title: title.text
    property alias value: value.text

    Rectangle{
        anchors.fill: parent
        RowLayout{
            anchors.fill: parent
            Rectangle{
                width: 40
                height: 40
                FontAwesome5FreeIcon{
                    id:icon
                    color: "#aaaaaa"
                    anchors.centerIn: parent
                }
            }

            Label{
                id:title
                width: 100
                text: "扫描对象"
                Layout.fillWidth: true
                verticalAlignment: Text.AlignVCenter
            }
            Label{
                id:value
                text: "518个"
            }
        }
    }
}
