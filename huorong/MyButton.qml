import QtQuick 2.4

MyButtonForm {
    property string normalColor: "#FFA924"
    property string hoverColor: "#FF9600"
    property string pressedColor: "#FCA53B"
    onHoveredChanged: {
       backgroundColor = hovered? hoverColor: normalColor
    }
    onPressedChanged: {
        backgroundColor = pressed? pressedColor: normalColor
    }

    backgroundColor: normalColor

}
