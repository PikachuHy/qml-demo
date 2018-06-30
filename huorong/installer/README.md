# 使用Qt Installer Framework制作安装包

## 步骤

### 制作安装包的步骤：

- 去官网下载[Qt Installer Framework](http://download.qt.io/official_releases/qt-installer-framework/)的安装包并安装（已经安装的请跳过这步）
- 使用windeployqt.exe集齐所需依赖
- 使用binarycreator.exe创建安装包

## 具体操作流程：

### 安装Qt Installer Framework

下载地址：http://download.qt.io/official_releases/qt-installer-framework/

![image](http://oh913j3dl.bkt.clouddn.com//qml/huorong/installer/0.png)
![image](http://oh913j3dl.bkt.clouddn.com//qml/huorong/installer/1.png)
![image](http://oh913j3dl.bkt.clouddn.com//qml/huorong/installer/2.png)
![image](http://oh913j3dl.bkt.clouddn.com//qml/huorong/installer/3.png)

## 搜集依赖

- 使用Release模式构建项目
![image](http://oh913j3dl.bkt.clouddn.com//qml/huorong/installer/4.png)
![image](http://oh913j3dl.bkt.clouddn.com//qml/huorong/installer/5.png)
- 在release目录下删掉不必要的文件
![image](http://oh913j3dl.bkt.clouddn.com//qml/huorong/installer/6.png)
- 运行windeployqt.exe命令

```
[windeployqt.exe路径] --release --qml --qmldir [qml源码路径] [exe文件路径]
```

![gif](http://oh913j3dl.bkt.clouddn.com//qml/huorong/installer/0.gif)





如在我的环境下是

```
D:\Qt\Qt5.11.0\5.11.0\mingw53_32\bin\windeployqt.exe --release --qml --qmldir D:\src\qml\huorong\ huorong.exe
```

- 手动拷贝其他的dll

我使用的是mingw53_32，需要拷贝以下文件

libgcc_s_dw2-1.dll libstdc++-6.dll libwinpthread-1.dll

![image](http://oh913j3dl.bkt.clouddn.com//qml/huorong/installer/9.png)

### 创建安装包

- 将上面搜集的依赖拷贝到`installer\packages\cn.net.pikachu.huorong\data`文件夹下
![image](http://oh913j3dl.bkt.clouddn.com//qml/huorong/installer/7.png)
- 运行binarycreator.exe命令

```
[binarycreator.exe路径] -c [config.xml路径] -p [packages路径] [生成的安装程序exe文件名] -v
```

![image](http://oh913j3dl.bkt.clouddn.com//qml/huorong/installer/8.png)

如在我的环境下是

```
D:\Qt\QtIFW-3.0.4\bin\binarycreator.exe -c installer/config/config.xml -p installer/packages huorong_install.exe -v
```

## 最后的演示效果

![gif](http://oh913j3dl.bkt.clouddn.com//qml/huorong/installer/2.gif)

## 思考与总结

如果Qt提供一键生成安装包就好了，何必这么麻烦呢？应该可以把这些操作用脚本写好，然后集成到QtCreator中。

# 附：

## 配置文件

### config.xml

```
<?xml version="1.0" encoding="UTF-8"?>
<Installer>
    <Name>火绒安全软件</Name>
    <Version>0.1.0</Version>
    <Title>火绒安全软件</Title>
    <Publisher>大黄老鼠</Publisher>
    <!-- Directory name is used in component.xml -->
    <StartMenuDir>pikachu</StartMenuDir>
    <TargetDir>@HomeDir@/pikachu/huorong</TargetDir>
</Installer>

```

### package.xml

```
<?xml version="1.0" encoding="UTF-8"?>
<Package>
    <DisplayName>火绒安全软件</DisplayName>
    <Description>可执行文件</Description>
    <Version>0.1.0-1</Version>
    <ReleaseDate>2018-07-01</ReleaseDate>
    <Default>true</Default>
    <Script>installscript.qs</Script>
    <ForcedInstallation>true</ForcedInstallation>
</Package>

```
### installscript.qs

```
/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the FOO module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

function Component()
{
    // default constructor
}

Component.prototype.createOperations = function()
{
    // call default implementation to actually install README.txt!
    component.createOperations();

    if (systemInfo.productType === "windows") {
        component.addOperation("CreateShortcut", "@TargetDir@/huorong.exe", "@StartMenuDir@/火绒安全软件.lnk",
            "workingDirectory=@TargetDir@", "iconPath=%SystemRoot%/system32/SHELL32.dll",
            "iconId=2", "description=Open README file");
        component.addOperation("CreateShortcut", "@TargetDir@/huorong.exe", "@HomeDir@/Desktop/火绒安全软件.lnk");

        component.addOperation("CreateShortcut", "@TargetDir@/maintenancetool.exe", "@StartMenuDir@/更新或卸载 火绒安全软件.lnk");
    }
}

```

