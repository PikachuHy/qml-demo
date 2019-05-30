import QtQuick 2.4
import "ResourceManager.js" as Rcm

DemoForm {
    side.onCurrentItemChanged: {
        console.log("current item: " + side.currentItem)
        titleText = side.currentItem
        switch (side.currentItem) {
        case "图片上传":
            loader.source = "PictureUpload.qml"
            break
        case "图片管理":
            loader.source = "PhotoManage.qml"
            break
        case "七牛配置":
            loader.source = "QiniuConfig.qml"
            break
        default:

        }
    }
    Loader {
        id: loader
        anchors.fill: container
    }
    Component.onCompleted: {
        side.currentItem = "图片管理"
    }
}
