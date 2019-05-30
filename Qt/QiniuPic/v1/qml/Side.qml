import QtQuick 2.0
import "ResourceManager.js" as Rcm
Item {
    property var arr: []
    property string currentItem: ""
    width: 200
    height: 600
    Column{
        SideItem{
            id: pictureUpload
            titleText: "图片上传"
            imageSource: Rcm.getIcon("up-load_1296db_64x64.png")
            onClicked: {
                handleClick(this)
            }
        }
        SideItem{
            id: photoManage
            titleText: "图片管理"
            imageSource: Rcm.getIcon("photo_1296db_64x64.png")
            onClicked: {
                handleClick(this)
            }
        }
        SideItem{
            id: qiniuConfig
            titleText: "七牛配置"
            imageSource: Rcm.getIcon("setting_1296db_64x64.png")
            onClicked: {
                handleClick(this)
            }
        }
    }
    Component.onCompleted: {
        arr = [pictureUpload, photoManage, qiniuConfig]
        handleClick(arr[0])
    }
    // 处理侧边栏项点击事件
    function handleClick(id) {
        clearSelected()
        // 仅当前点击项设为选中
        id.selected = true
        currentItem = id.titleText
    }
    // 清空所有的选中情况
    function clearSelected() {
        for(var i = 0; i < arr.length; i++) {
            arr[i].selected = false
        }
    }
}
