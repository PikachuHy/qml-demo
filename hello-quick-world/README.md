# Hello Quick World

参考视频：[Getting started with Qt: Hello Quick World](https://www.youtube.com/watch?v=nepoVgVvWEI)

我的环境是Qt5.11，跟视频中的差别还是有一些的。

## 源码

建好工程后，修改源代码

### hello-quick-world.pro

```
QT += quick
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

```

### main.cpp

```c++
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

```

上面两个文件是不需要修改的

主要修改的代码在qml文件里

### main.qml

```qml
import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.2

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Button {
        id: button
        text: qsTr("Push Me")
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: {
            label.text = qsTr("Hello Qt")
        }
    }

    Label {
        id: label
        text: qsTr("Hello World")
        anchors.horizontalCenter: button.horizontalCenter
    }
}

```

## 截图

### 最后的运行效果

![image](http://oh913j3dl.bkt.clouddn.com//qml/hello_quick_world/0.gif)

### 自己做的时候留下的部分截图

![image](http://oh913j3dl.bkt.clouddn.com//qml/hello_quick_world/0.png)
![image](http://oh913j3dl.bkt.clouddn.com//qml/hello_quick_world/1.png)
![image](http://oh913j3dl.bkt.clouddn.com//qml/hello_quick_world/2.png)
![image](http://oh913j3dl.bkt.clouddn.com//qml/hello_quick_world/3.png)
![image](http://oh913j3dl.bkt.clouddn.com//qml/hello_quick_world/4.png)
![image](http://oh913j3dl.bkt.clouddn.com//qml/hello_quick_world/5.png)
![image](http://oh913j3dl.bkt.clouddn.com//qml/hello_quick_world/6.png)
![image](http://oh913j3dl.bkt.clouddn.com//qml/hello_quick_world/7.png)
![image](http://oh913j3dl.bkt.clouddn.com//qml/hello_quick_world/8.png)

## 思考与总结

qml的hello world我写过很多遍了，现在要我解释每一行代码后面的含义，我还真说不上来。重新试一试qml，是想着能不能在接下来空闲的一段时间，做一个类似火绒的界面出来。火绒现在是我电脑里必备的一款软件，记得之前有同学用Qt/qml做过360的一个界面，现在Qt都发展到5.11，是时候更新一把。