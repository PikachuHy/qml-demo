import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import Qt.labs.platform 1.0
import QtQuick.Window 2.3
//import "../components"
import "./items"
Window{
    id:root
    signal activated();
    SystemTrayIcon {
        iconSource: "qrc:/icon/icon.png"
        visible: true
        tooltip:"火绒安全防护中心\n版本号：4.0.65.12\n病毒库：2018-07-07 16:22"
        onActivated: {
            if(reason===SystemTrayIcon.Context){
                console.log("x:"+x+", y:"+y)
                contextMenu.visible=true
                contextMenu.x = x
                contextMenu.y = y
            }
            root.activated();
        }
    }
    ContextMenu{
        id:contextMenu
    }
}

