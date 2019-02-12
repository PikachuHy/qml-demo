import QtQuick 2.4

IconButton {
    iconName: "times"
    hoverBackgroundColor: "#F26223"
    pressedColor: "#DF4C0B"
    mouseArea.onClicked: Qt.quit()
}
