import QtQuick 2.11
MyButtonForm {
    id: control
    property string normalTextColor
    property string hoverTextColor
    property string pressedTextColor
    property string normalBackgroundColor
    property string hoverBackgroundColor
    property string pressedBackgroundColor

    onHoveredChanged: {
        textColor = hovered? hoverTextColor: normalTextColor
        backgroundColor = hovered? hoverBackgroundColor: normalBackgroundColor
    }
    onPressedChanged: {
        textColor = pressed? pressedTextColor: normalTextColor
        backgroundColor = pressed? pressedBackgroundColor: normalBackgroundColor
    }
    mouseArea.onClicked: {
        control.clicked()
    }

    onTextColorChanged: {
        normalTextColor = textColor
        hoverTextColor = textColor
        pressedBackgroundColor = textColor
    }
    onBackgroundColorChanged: {
        normalBackgroundColor = backgroundColor
        hoverBackgroundColor = backgroundColor
        pressedBackgroundColor = backgroundColor
    }

    function checkIfNullOrEmpty(value){
        return value===null || value===""
    }
    function checkNormalTextColor(){
        if(checkIfNullOrEmpty(normalTextColor)){
            normalTextColor="black"
            hoverTextColor="black"
            pressedTextColor="black"
        }
        if(checkIfNullOrEmpty(hoverTextColor)){
            hoverTextColor=normalTextColor
        }
        if(checkIfNullOrEmpty(pressedBackgroundColor)){
            pressedTextColor=normalTextColor
        }

    }
    function checkNormalBackgroundColor(){
        if(checkIfNullOrEmpty(normalBackgroundColor)){
            normalBackgroundColor="white"
            hoverBackgroundColor="white"
            pressedBackgroundColor="white"
        }
        if(checkIfNullOrEmpty(hoverBackgroundColor)){
            hoverBackgroundColor=normalBackgroundColor
        }
        if(checkIfNullOrEmpty(pressedBackgroundColor)){
            pressedBackgroundColor=normalBackgroundColor
        }
    }

    Component.onCompleted: {
        checkNormalTextColor()
        checkNormalBackgroundColor()
        control.textColor = normalTextColor
        control.backgroundColor = normalBackgroundColor

//        console.log("backgroundcolor: normal-"+normalBackgroundColor+", hover-"+hoverBackgroundColor+", pressed-"+pressedBackgroundColor)
    }

}
