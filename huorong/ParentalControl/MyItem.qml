import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import "../"
MyItemForm {
    implicitWidth: 400
    implicitHeight: 75
    display.color: "orange"
    fontAwesome5FreeIcon1.color: "#aaa"
    onHoveredChanged: {
        display.color = hovered?Qt.lighter("orange"):"orange"
        fontAwesome5FreeIcon1.color  = hovered?"orange":"#aaa"
    }
}
