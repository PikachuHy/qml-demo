// 获取图标资源，如果是qrc，那么Qt设计器无法正常显示
function getIcon(icon) {
    var useQrc = false
    if (useQrc) {
        return "qrc:/icon/"+icon
    } else {
        return "../icon/"+icon
    }
}
