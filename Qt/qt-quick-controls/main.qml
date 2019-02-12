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
