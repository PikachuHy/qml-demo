import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import "../components"
Pane {
    id: root
    width: 300
    height: 250
    property alias title: title.text
    property alias iconName: icon1.name
    property alias model: listView.model
    onModelChanged: {
        height = model.count * 55 + 50
        listView.height = model.count * 55
    }

    Rectangle {
        id: rectangle
        color: "#ffffff"
        anchors.fill: parent

//        Debug{anchors.fill: parent;debug: true}
        RowLayout{
//            height: listView.model.size * 50
            anchors.fill: parent
            MaterialIcon{
                id: icon1
                name: "security"
                color: "#dddddd"
                font.pixelSize: 60
                fontSizeMode: Text.FixedSize
                lineHeight: 1
                size: 60
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            }
            Column{
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                Pane{
                    id: rectangle1
                    width: 200
                    height: 40
                    Label{
                        id: title
                        text: "病毒防御"
                        color: "orange"
                        font.pointSize: 14
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    MaterialIcon{
                        id: icon2
                        name: "keyboard_arrow_right"
                        color: "#eee"
                        font.pixelSize: 25
                        anchors.right: parent.right
                        anchors.rightMargin: 10
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    onHoveredChanged: {
                        title.color = hovered? Qt.lighter("orange"):"orange"
                        icon2.color = hovered? Qt.lighter("orange"):"#666"
                    }
                    Rectangle{
                        width: parent.width
                        height: 2
                        border.color: "#eee"
                        border.width: 1

                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: -10
                    }
                }

                ListView{
                    id: listView
                    width: 200
                    height: 100
                    interactive: false
//                    Debug{anchors.fill: parent;debug: true}
                    delegate: BlockItem{
                        text: name
                        checked: model.checked
                    }
                    model: ListModel{
                        ListElement{
                            name:"name"
                            checked:true
                        }
                    }
                }
            }
        }
    }
}
