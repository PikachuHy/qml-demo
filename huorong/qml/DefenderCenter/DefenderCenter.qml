import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import "../"
import "../components"
import controller 1.0
Item {
    width: 750
    height: 600
    Flow{
        flow: Flow.TopToBottom
        anchors.fill: parent
        anchors.margins: 4
        spacing: 10
        Block{
            title: "病毒防御"
            iconName:"security"
            model: ListModel{
                ListElement{
                    name:"文件实时监控"
                    checked:false
                }
                ListElement{
                    name:"恶意行为监控"
                    checked:true
                }
                ListElement{
                    name:"U盘保护"
                    checked:true
                }
                ListElement{
                    name:"下载保护"
                    checked:true
                }
            }
        }
        Block{
            title: "系统防御"
            iconName: "border_all"
            model: ListModel{
                ListElement{
                    name:"系统加固"
                    checked:true
                }
                ListElement{
                    name:"自定义防护"
                    checked:true
                }
                ListElement{
                    name:"软件安装拦截"
                    checked:true
                }
                ListElement{
                    name:"浏览器保护"
                    checked: false
                }
            }
        }
        Block{
            title: "网络防御"
            iconName: "network_wifi"
            model: ListModel{
                ListElement{
                    name:"黑客入侵拦截"
                    checked:true
                }
                ListElement{
                    name:"对外攻击检测"
                    checked:true
                }
                ListElement{
                    name:"网购保护"
                    checked:true
                }
                ListElement{
                    name:"恶意网站拦截"
                    checked:true
                }
                ListElement{
                    name:"IP协议控制"
                    checked:true
                }
                ListElement{
                    name:"联网控制"
                    checked:false
                }
            }
        }
    }
}
