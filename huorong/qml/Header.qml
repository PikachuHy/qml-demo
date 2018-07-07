import QtQuick 2.11
import "./components"
HeaderForm {
    property string title: ""
    property point clickPos: "0,0"
    signal positionChanged(point delta)
    mouseArea.onPressed: {
        clickPos  = Qt.point(mouse.x,mouse.y)
    }
    mouseArea.onPositionChanged:{
        var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
        positionChanged(delta)
    }
    onTitleChanged: {
        titleText = title
    }
}
