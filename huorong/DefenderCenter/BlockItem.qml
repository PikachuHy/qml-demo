import QtQuick 2.11

ItemForm {
    property string text: ""
    property bool checked: false
    fontAwesome5FreeIconName:"toggle-off"
    onTextChanged: {
        displayText = text
    }
    onCheckedChanged: {
        fontAwesome5FreeIconName = checked?"toggle-on":"toggle-off"
    }
    textMouseArea.onEntered: {
        display.color = "orange"
    }
    textMouseArea.onExited: {
        display.color = "#000"
    }
    iconMouseArea.onClicked: {
        checked = !checked
    }

}
