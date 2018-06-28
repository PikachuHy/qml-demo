import QtQuick 2.11
import QtQuick.Controls 2.4

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("To Do List")

    ToDoList{
        anchors.centerIn: parent
    }
}
