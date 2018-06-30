import QtQuick 2.4

import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

ListView {
    id: listView
    width: 225
    height: 160
    delegate: KillingListItem {
        width: listView.width
        height: 55
        normalBackgroundColor: "#FFA924"
        hoverBackgroundColor: "#FB9A24"
        displayText: name
    }
    model: ListModel {
        ListElement {
            name: "全盘查杀"
        }

        ListElement {
            name: "自定义查杀"
        }
    }
}
