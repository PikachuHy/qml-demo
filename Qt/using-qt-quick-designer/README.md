# Using Qt Quick Designer

参考视频：[Introduction to Qt – UI Design {tutorial}](https://www.youtube.com/watch?v=0Po3tE9yUcU)

## 主要功能

- 显示一个预定宠物的界面，可以输入宠物的名字，选择宠物的类型和年限
- 点击预定按钮后，弹出对话框，显示预定宠物的信息，点击确定后退出程序

## 源码

### Page3.qml

```qml
import QtQuick 2.11
import QtQuick.Dialogs 1.2
Page3Form {
    comboBox.model: ["Dog", "Fish", "Cat", "Bird"]
    button.onClicked: {
        var msg = "Ordering: " + textField.text + "\r\n"
        msg = msg + "Your " + Math.round(dial.value) + " years old " + comboBox.currentText
        messageDialog.text = msg
        messageDialog.open()
    }
    dial.onValueChanged: {
        progressBar.value = dial.value
        label1.text = Math.round(progressBar.value) + " years old"
    }
    MessageDialog{
        id: messageDialog
        title: qsTr("Hello World")
        text: ""
        onAccepted: Qt.quit()
    }
}

```

### Page3Form.ui.qml

```qml
import QtQuick 2.11
import QtQuick.Controls 2.4

Page {
    width: 600
    height: 400
    property alias label1: label1
    property alias progressBar: progressBar
    property alias dial: dial
    property alias button: button
    property alias comboBox: comboBox
    property alias textField: textField

    header: Label {
        text: qsTr("Page 3")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    Row {
        id: row
        anchors.leftMargin: 0
        spacing: 25
        padding: 20
        anchors.fill: parent

        Column {
            id: column
            width: 200
            height: 400
            spacing: 10

            Label {
                id: label
                text: qsTr("Enter a name")
            }

            TextField {
                id: textField
            }

            ComboBox {
                id: comboBox
            }

            Button {
                id: button
                text: qsTr("Order")
            }
        }

        Column {
            id: column1
            width: 200
            height: 400
            spacing: 10

            Dial {
                id: dial
                to: 20
                from: 1
                value: 1
            }

            ProgressBar {
                id: progressBar
                to: 20
                from: 1
                value: 1
            }

            Label {
                id: label1
                text: qsTr("1 years old")
            }
        }
    }
}

```

### main.qml

```qml
import QtQuick 2.11
import QtQuick.Controls 2.4

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Using Qt Quick Designer")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page1Form {
        }

        Page2Form {
        }
        Page3 {
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton {
            text: qsTr("Page 1")
        }
        TabButton {
            text: qsTr("Page 2")
        }
        TabButton {
            text: qsTr("Page 3")
        }
    }
}

```

## 截图

### 最后的运行效果

![image](http://oh913j3dl.bkt.clouddn.com//qml/using_qt_quick_designer/0.gif)

### 自己做的时候留下的部分截图

![image](http://oh913j3dl.bkt.clouddn.com//qml/using_qt_quick_designer/0.png)

## 思考与总结

在做这部分时，有几个特别不好的地方

- 如果控件拖错位置，修改后，需要一些时间才能在正确位置显示

我开始还以为自己拖的时候把x,y写死了，看源代码后，发现没有问题，后面不知道怎么，又正常显示了。这期间我并没有改变代码什么的。

- 在Qt Quick Designer中修改了属性什么的，会有缓存，运行时运行的是之前的代码，需要清理项目，然后重新构建才能运行正确

我实在想不出为什么改了代码，moc编译器怎么识别不了，非得自己手动清理项目，然后再次构建才能运行正确。这是一个非常不友好的问题。记得之前用Vue的时候，修改都是自动刷新到界面，现在每次都得手动清理，运行一次，非常麻烦。

- 大部分的数值都是写死了的，比如Column的高度，不是像html的div一样撑开，非常不习惯，而且我看到这些线，非常不舒服

![image](http://oh913j3dl.bkt.clouddn.com//qml/using_qt_quick_designer/-1.png)

这些线总让我觉得怪怪的