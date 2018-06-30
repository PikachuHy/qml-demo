import QtQuick 2.11
import "util.js" as Util
import DB 1.0
Text {
    id: icon
    property string name
    property url codepintsUrl
    property alias size: icon.font.pixelSize
    DB{id:db}
    onNameChanged: {
        var text = db.convertNameToText(name,font.family)
        icon.text = Util.convertStringToUnicode(text)
    }
}
