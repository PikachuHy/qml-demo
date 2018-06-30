import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
MenuItem {
    id: menuItem
    property alias  iconName: icon.name
    onHoveredChanged: {
        display.color = hovered? "orange" : "#000"
        icon.color = hovered? "orange" : "gray"
    }
    contentItem: RowLayout{
        MaterialIcon{
            id: icon
            name:"access_alarm"
            color: "gray"
        }
        Text {
            color: "#000"
            id: display
            text: menuItem.text
        }
    }
}
