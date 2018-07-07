import QtQuick 2.4
import QtQuick.Controls 2.4
import "./components"

TabItemForm {
    property string activeColor: "#FBA92D"
    property string hoverColor: "#FBA92D"
    property string normalColor: "#666"
    property bool active: false
    signal clicked()
    displayColor: normalColor
    icon.color: normalColor
    onActiveChanged: {
        leftside.color = active? activeColor : "white"
        displayColor = active? activeColor: normalColor
        icon.color = active?activeColor:normalColor
    }

    mouseArea.onEntered: {
        displayColor = hoverColor
        icon.color = hoverColor
    }
    mouseArea.onExited: {
        if(!active){
            displayColor = normalColor
            icon.color = normalColor
        }

    }
    mouseArea.onClicked: {
        active = true
        clicked()
    }

}
