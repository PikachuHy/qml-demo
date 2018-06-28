import QtQuick 2.11

BackgroundForm {
    property Circle target: null
    focus: true

    Keys.onPressed: {
        if(event.key === Qt.Key_Plus || event.key === Qt.Key_Equal){
            target.width += 10
            target.visible = true
        }
        if(event.key === Qt.Key_Minus || event.key === Qt.Key_Underscore){
            if(target.width>0){
                target.width -= 10
                target.visible = true
            }else{
                target.visible = false
            }

        }
        if(event.key === Qt.Key_Escape){
            target.width = 200
        }
    }
}
