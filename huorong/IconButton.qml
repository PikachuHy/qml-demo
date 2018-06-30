import QtQuick 2.4

IconButtonForm {
    property string hoverBackgroundColor: "white"
    property string normalBackgroundColor: "white"
    property string pressedColor: "#FCA53B"
    property bool pressed: false

    backgroundColor: normalBackgroundColor
    signal clicked()
    mouseArea.onEntered: {
        backgroundColor = hoverBackgroundColor
    }
    mouseArea.onExited: {
        backgroundColor = normalBackgroundColor
    }
    mouseArea.onPressed: {
        backgroundColor = pressedColor
        pressed = !pressed
    }

    mouseArea.onClicked: {
        clicked()
    }
}
