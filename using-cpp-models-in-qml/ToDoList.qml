import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import ToDo 1.0
ColumnLayout{
    Frame {
        Layout.fillWidth: true
        ListView{
            id:listView
            implicitWidth: 300
            implicitHeight: 300
            anchors.fill: parent
            clip: true

            model: ToDoModel{
                list:toDoList
            }

            delegate: RowLayout{
                width: listView.width
                CheckBox{
                    checked: model.done
                    onCheckedChanged: model.done = checked
                }
                TextField{
                    Layout.fillWidth: true
                    text: model.description
                    onEditingFinished: model.description = text
                }
            }
        }
    }
    RowLayout{
        Button{
            text:qsTr("Add new item")
            onClicked: toDoList.appendItem()
            Layout.fillWidth: true
        }
        Button{
            text:qsTr("Remove complete items")
            onClicked: toDoList.removeCompletedItem()
            Layout.fillWidth: true
        }
    }
}
