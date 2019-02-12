# Qt Quick Controls

参考视频：[Introduction to Qt – Intro to Qt Quick Controls {tutorial}](https://www.youtube.com/watch?v=uuhmSZxK1mk)

## 主要功能

- 做一个经典的编辑器界面
- 一个文件菜单，包含新建、打开、保存
- 一个工具栏，包含新建、打开、保存

## 源码

### main.qml

```qml
import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Qt Quick Controls")

    Action{
        id:actionNew
        text: qsTr("&New")
        shortcut: StandardKey.New
        icon.source: "qrc:/baseline_fiber_new_black_18dp.png"
        onTriggered: {
            area.placeholderText = "To do - New"
        }
    }
    Action{
        id:actionOpen
        text: qsTr("&Open")
        shortcut: StandardKey.Open
        icon.source: "qrc:/baseline_folder_open_black_18dp.png"
        onTriggered: {
            area.placeholderText = "To do - Open"
        }
    }
    Action{
        id:actionSave
        text: qsTr("&Save")
        shortcut: StandardKey.Save
        icon.source: "qrc:/baseline_save_black_18dp.png"
        onTriggered: {
            area.placeholderText = "To do - Save"
        }
    }
    menuBar: MenuBar{
        Menu{
            title: "File"
            MenuItem{action: actionNew}
            MenuItem{action: actionOpen}
            MenuItem{action: actionSave}
        }
    }
    header: ToolBar{
        RowLayout{
            ToolButton{action: actionNew}
            ToolButton{action: actionOpen}
            ToolButton{action: actionSave}
        }
    }
    TextArea{
        id: area
        anchors.fill: parent
    }
}

```



## 截图

### 最后的运行效果

![image](http://oh913j3dl.bkt.clouddn.com//qml/qt_quick_controls/0.gif)

### 自己做的时候留下的部分截图

![image](http://oh913j3dl.bkt.clouddn.com//qml/qt_quick_controls/0.png)

## 思考与总结

这是一个完全没有办法拖控件的Demo，所有的东西都是手敲的。不光如此，视频中的Action图标根本出不来，我最后是从 https://material.io/tools/icons/ 上下载了几个图标挂上去的。

视频的后面展示了其他的几个控件，其实就是把几个新建的空工程跑了一遍。