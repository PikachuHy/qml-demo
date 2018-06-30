import QtQuick 2.0

Rectangle {
    id: root
    property bool debug: true
    anchors.fill: parent
    color: "#00000000"
    border.color: "#000"
    border.width: 1
    visible: debug

    Text {
        id: propText
        text: root.width + " * " + root.height
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
    }
}
