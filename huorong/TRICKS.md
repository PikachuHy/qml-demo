# TRICKS

Window去掉边框

```
flags:Qt.FramelessWindowHint
```

Menu去掉边框

```qml
        background: Rectangle {
                implicitWidth: 200
                implicitHeight: 200
                border.color: "#fff"
            }
```

改变Button的背景

```qml
background: Rectangle {
                color: "#FFA924"
            }
```

自定义组件，图像无法正确预览

如何最小化，直接不可见

手型

```
cursorShape: Qt.PointingHandCursor
```

ColumnLayout会改变大小，Colunm不会

加载字体出错

实现拖拽

= ： 傻傻分不清

一个字符串代码一个unicode码

```javascript
    function convertStringToUnicode(text){
        var str = "\\u" + text
        var jsonstr = '{"ustr":"'+str+'"}'
        var obj = JSON.parse(jsonstr)
        return obj.ustr
    }
```

在c++控制某个qml组件显示

基于Qt Quick Control 2 去重新绘制自己需要的控件

让listview无法拖动

```
interactive: false
```

ListModel中的元素个数居然是count

qml中的继承，就是继承跟对象的属性

QtCreator开始蹦

最顶层的窗口怎么做阴影