import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import "./components"
ApplicationWindow {
    id: window
    visible: true
    width: 105
    height: 53
    color: "#00000000"
    flags: Qt.FramelessWindowHint
    background:Rectangle{
        anchors.fill: parent
        color: "#35383C"
        radius: 5
    }

    RowLayout{
        width: parent.width
        height: parent.height / 2
        Rectangle{
            width: 3
        }

        MaterialIcon{
            name: "arrow_upward"
            color: "orange"
            size: 16
        }

        Label{
            text: "0.0 KB/s"
            color: "orange"
        }
    }
    RowLayout{
        width: parent.width
        height: parent.height / 2
        anchors.bottom: parent.bottom
        Rectangle{
            width: 3
        }
        MaterialIcon{
            name: "arrow_downward"
            color: "green"
            size: 16
        }
        Label{
            text: "0.0 KB/s"
            color: "green"
        }
    }
    MouseArea{
        property point clickPos: "0,0"
        anchors.fill: parent

        onPressed: {
            clickPos  = Qt.point(mouse.x,mouse.y)
        }
        onPositionChanged:{
            var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
            window.x += delta.x
            window.y += delta.y
        }
    }
}
