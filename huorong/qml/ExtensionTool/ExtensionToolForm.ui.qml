import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

import "../"
import "../components"

Item {
    width: 750
    height: 520
    property alias toolItem: toolItem

    Grid {
        id: grid
        flow: Grid.TopToBottom
        spacing: 10
        rows: 4
        columns: 2
        anchors.fill: parent
        ToolItem {
            id: toolItem
            iconSource: "qrc:/image/tool/1.png"
            name:"火绒剑"
            description: "专业人士使用的安全分析工具"
        }
        ToolItem {
            iconSource: "qrc:/image/tool/2.png"
            name:"右键管理"
            description: "管理文件、桌面、IE的右键菜单"
        }
        ToolItem {
            iconSource: "qrc:/image/tool/3.png"
            name:"文件粉碎"
            description: "强制删除或彻底粉碎文件"
        }
        ToolItem {
            iconSource: "qrc:/image/tool/4.png"
            name:"启动项管理"
            description: "轻松管理开机启动项目"
        }
        ToolItem {
            iconSource: "qrc:/image/tool/5.png"
            name:"漏洞修复"
            description: "扫描修复系统漏洞"
        }
        ToolItem {
            iconSource: "qrc:/image/tool/6.png"
            name:"垃圾清理"
            description: "全面清理系统垃圾"
        }
        ToolItem {
            iconSource: "qrc:/image/tool/7.png"
            name:"弹窗拦截"
            description: "拦截电脑程序的各类骚扰弹窗"
        }
        ToolItem {
            iconSource: "qrc:/image/tool/8.png"
            name:"网络流量"
            description: "管理网络流量情况"
        }
    }
}
