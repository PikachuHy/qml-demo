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

如何发布Qt Quick Application

```
[windeployqt.exe路径] --release --qml --qmldir [qml源码路径] [exe文件路径]
```

例如: 

```
D:\src\qml\build-huorong-Desktop_Qt_5_11_0_MinGW_32bit-Release\release>D:\Qt\Qt5.11.0\5.11.0\mingw53_32\bin\windeployqt.exe --release --qml --qmldir D:\src\qml\huorong\ huorong.exe
```

参考： https://www.jianshu.com/p/ec6a505b1ab7

如何制作安装包

- 去官网下载[Qt Installer Framework](http://download.qt.io/official_releases/qt-installer-framework/)的安装包，安装好
- 复制examples\startmenu到一个目录下，修改相关的文件
- 使用binarycreator.exe创建安装包

```
[binarycreator.exe] -c [config.xml路径] -p [packages路径] [生成的安装程序exe文件名] -v
```

例如：

```
./binarycreator.exe -c huorong/config/config.xml -p huorong/packages my_install.exe -v
```

```
./binarycreator.exe --offline-only -c huorong/config/config.xml -p huorong/packages -t installerbase my_install
```

