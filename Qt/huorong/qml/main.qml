import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtQuick.Window 2.3
import "./components"
import "./SystemTray"
import controller 1.0
ApplicationWindow {
    id: window
    objectName: "window"
    visible: true
    width: 1000
    height: 650
    title: qsTr("huorong safe")
    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint
    onVisibleChanged: {
        if(visible){
            flags = flags | Qt.WindowStaysOnTopHint
            flags = flags & ~Qt.WindowStaysOnTopHint
        }
    }


    DropShadow {
        id: dropShadow
        anchors.fill: mask
        verticalOffset: 1
        radius: 4
        samples: 8
        color: "#80000000"
        source: mask
        visible: true
    }
    header: Header{
        id:myHeader
        width: window.width
        title: " "
        minimizeButton.onClicked: window.visible = false
        menuButton.onClicked: menu.popup()
        onPositionChanged: {
            window.x += delta.x
            window.y += delta.y
        }
    }
    Menu{
        id:menu
        background: Rectangle {
                implicitWidth: 200
                implicitHeight: 200
                border.color: "#fff"
            }

        MyMenuItem{
            text: qsTr("Settings")
            iconName: "settings"
        }
        MyMenuItem{
            text: qsTr("Safe Log")
            iconName: "description"
        }
        MyMenuItem{
            text: qsTr("Security/Isolate Region")
            iconName: "security"
        }
        MyMenuItem{
            text: qsTr("Check Update")
            iconName: "update"
        }
        MyMenuItem{
            text: qsTr("Feedback")
            iconName: "feedback"
        }
        MyMenuItem{
            text: qsTr("About Us")
            iconName: "info"
        }
    }

    Rectangle{
        id: rectangle
        anchors.fill: parent
        ColumnLayout{
            id:leftside
            width: 250
            height: parent.height - 100
            property int currentIndex: 0
            property var items: []
            TabItem{
                id: item0
                displayText: qsTr("病毒查杀")
                iconName: "flash_on"
                active: leftside.currentIndex == 0
                onClicked: {
                    stackView.clear()
                    stackView.push("VirusKilling/VirusKilling.qml")
                    header.title = ""
                    leftside.currentIndex = 0
                    changeActive()
                }
            }
            TabItem{
                id: item1
                displayText: qsTr("防护中心")
                iconName: "verified_user"
                active: leftside.currentIndex == 1
                onClicked: {
                    stackView.clear()
                    stackView.push("DefenderCenter/DefenderCenter.qml")
                    header.title = displayText
                    leftside.currentIndex = 1
                    changeActive()
                }
            }
            TabItem{
                id:item2
                displayText: qsTr("家长控制")
                iconName: "beach_access"
                active: leftside.currentIndex == 2
                onClicked: {
                    stackView.clear()
                    stackView.push("ParentalControl/ParentalControl.qml")
                    header.title = displayText
                    leftside.currentIndex = 2
                    changeActive()
                }
            }
            TabItem{
                id:item3
                displayText: qsTr("扩展工具");
                iconName: "widgets"
                active: leftside.currentIndex == 3
                onClicked: {
                    stackView.clear()
                    stackView.push("ExtensionTool/ExtensionTool.qml")
                    header.title = displayText
                    leftside.currentIndex = 3
                    changeActive()
                }
            }
        }
        StackView {
            id: stackView
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            initialItem: "VirusKilling/VirusKilling.qml"
//            initialItem: "DefenderCenter/DefenderCenter.qml"
//            initialItem: "qrc:/ParentalControl/ParentalControl.qml"
//            initialItem: "qrc:/ExtensionTool/ExtensionTool.qml"
//            initialItem: "VirusKilling/Scanning.qml"
            anchors.left: leftside.right
            popEnter: null
            popExit: null
            pushEnter: null
            pushExit: null
        }
    }
    Rectangle{
        id: mask
        color: "#eee"
        anchors.fill: parent
        visible: false
    }
//    MySystemTrayIcon{
//        onActivated: {
//                  window.show()
//                  window.raise()
//                  window.requestActivate()
//              }
//    }
    NetworkTrafficFloatingWindow{
        id: networkTrafficFloatingWindow
        x: Screen.width - width
        y: Screen.height / 2
    }
    function changeActive(){
        for(var i = 0;i<leftside.items.length;i++){
            leftside.items[i].active = false
        }
        leftside.items[leftside.currentIndex].active = true
    }
    Component.onCompleted: {
        leftside.items.push(item0)
        leftside.items.push(item1)
        leftside.items.push(item2)
        leftside.items.push(item3)
        QmlController.stackView = stackView
        QmlController.header = myHeader
//        console.log("stackView",QmlController.header,myHeader)
    }
}
