import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import "../"

ToolItemForm {
    id:root
    MouseArea{
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onEntered: {
            root.shadow.visible = true
            root.dropShadow.visible = true
            downloadIcon.visible = true
        }
        onExited: {
            root.shadow.visible = false
            root.dropShadow.visible = false
            downloadIcon.visible = false
        }
    }
}
