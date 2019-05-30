import QtQuick 2.4
import QtGraphicalEffects 1.12

SideItemForm {
    property bool selected: false
    signal clicked()
    Colorize {
        id: colorize
        visible: true
        anchors.fill: image
        source: image
        hue: 0
        saturation: 0
        lightness: 0
    }
    mouseArea.onClicked: {
        console.log("click: " + titleText)
        clicked()
    }

    onSelectedChanged: {
        colorize.visible = !selected
        titleColor = selected ? "#1296db" : "#000000"
        rectangleVisible = selected
    }
    Component.objectName: {
        rectangleVisible = false
    }
}
