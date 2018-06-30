import QtQuick 2.0

IconButton {
    normalBackgroundColor: "#FB9A24"
    hoverBackgroundColor: "#FCA53B"
    property string normalIconName: "chevron-down"
    property string pressedIconName: "chevron-up"
    iconName: normalIconName
    icon.color: "white"
    onPressedChanged: {
        iconName = pressed? pressedIconName: normalIconName
    }
}
