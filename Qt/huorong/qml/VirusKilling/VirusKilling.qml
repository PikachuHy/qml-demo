import QtQuick 2.11
import controller 1.0
VirusKillingForm {
    property real listViewY
    arrowButton.onClicked: {
        if(arrowButton.pressed){
            listView.y = 0
            listView.visible = true
            animation.running = true
        }else{
            listView.visible = false
        }
    }
    PropertyAnimation {
        id: animation
        target: listView
        property: "y"
        to: 75
        duration: 1000
        easing.type: Easing.OutExpo
    }
    Component.onCompleted: {
        listView.visible = false
    }
    quickKillingButton.onClicked: {
        QmlController.stackView.push('Scanning.qml')
        QmlController.header.title = "正在快速扫描"
    }
}
