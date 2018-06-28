# QML Introduction

参考视频：[Introduction to Qt - Intro to QML {tutorial}](https://www.youtube.com/watch?v=GkzncJ71mm0)

## 主要功能

- 点击Sender，Receiver会变颜色，然后计数+1
- 按+-键，Sender和Receiver会变大变小，按Esc键会复原

## 源码

### Background.qml

```qml
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

```

### BackgroundForm.ui.qml

```qml
import QtQuick 2.11

Item {
    width: 400
    height: 400

    Rectangle {
        id: rectangle
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#80d5f6"
            }

            GradientStop {
                position: 1
                color: "#000000"
            }
        }
        anchors.fill: parent
    }
}

```

### Circle.qml

```qml
import QtQuick 2.11

CircleForm {
}

```

### CircleForm.ui.qml

```qml
import QtQuick 2.11

Item {
    width: 200
    height: 200
    property alias buttonColor: button.color
    property alias displayText: display.text

    Rectangle {
        id: button
        width: 200
        height: 200
        color: "#ff0000"
        radius: width * 0.5
        anchors.fill: parent

        Text {
            id: display
            x: 176
            y: 194
            text: qsTr("Hello Qt")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.family: "Times New Roman"
            font.pixelSize: 24
        }
    }
}

```

### Receiver.qml

```qml
import QtQuick 2.11
Circle {
    id: receiveButton

    function receive(value){
        displayText = value
        clicknotify.running = true
    }

    SequentialAnimation on buttonColor {
        id: clicknotify
        running: false


        ColorAnimation {
            from: "red"
            to: "blue"
            duration: 500
        }

        ColorAnimation {
            from: "blue"
            to: "red"
            duration: 500
        }
    }
}

```

### Sender.qml

```qml
import QtQuick 2.11

Circle {
    id: sendButton

    property int counter: 0
    property Receiver target: null

    signal send(string value)
    onTargetChanged: send.connect(target.receive)

    MouseArea{
        anchors.fill: parent

        onClicked: {
            counter++
            parent.send(counter)
        }

        onPressed: {
            parent.buttonColor = "green"
        }
        onReleased: {
            parent.buttonColor = "blue"
        }
    }
}

```

### main.qml

```qml
import QtQuick 2.11
import QtQuick.Window 2.11

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("QML Introduction")

    Background {
        id: background
        anchors.fill: parent
        target: sender
        Sender {
            id: sender
            y: 214
            displayText: "Sender"
            anchors.verticalCenterOffset: 0
            anchors.left: parent.left
            anchors.leftMargin: 50
            anchors.verticalCenter: parent.verticalCenter
            target: receiver
        }

        Receiver {
            id: receiver
            x: 532
            y: 240
            displayText: "Receiver"
            anchors.right: parent.right
            anchors.rightMargin: 50
            anchors.verticalCenter: parent.verticalCenter
            width: sender.width
            visible: sender.visible
        }
    }
}

```

## 截图

### 最后的运行效果

![image](http://oh913j3dl.bkt.clouddn.com//qml/qml_introduction/0.gif)

### 自己做的时候留下的部分截图

![image](http://oh913j3dl.bkt.clouddn.com//qml/qml_introduction/0.png)
![image](http://oh913j3dl.bkt.clouddn.com//qml/qml_introduction/1.png)
![image](http://oh913j3dl.bkt.clouddn.com//qml/qml_introduction/2.png)

## 思考与总结

我刚刚看到视频中做Background和Circle组件时，感到非常奇怪，为什么要用一个Item，而不直接使用Rectangle呢？后来看到，先把这两个组件做好，最后进行组装，特别好用。用js做的一些简单逻辑也非常方便。