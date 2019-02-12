# 火绒安全软件

基于Qt 5.11，以QML为主开发的火绒安全软件界面。

该Demo作为我最近学习QML的一个综合考验，尽量多的还原火绒的界面和操作方式，以及呈现的效果。

## 选择做火绒安全软件的理由

火绒目前是我电脑里的常驻软件，自从发现火绒这款很不错的软件后，就替代了360作为电脑里主力的安全软件。最近闲着，于是重新学学QML。之前虽然有接触，但是大多写了一个Hello World以后就扔掉了，没有什么实际价值。很久很久以前，我看到Qt吧有大佬用Qt做了360的界面，于是产生了用QML做火绒的界面的想法，作为对自己的一个小小的挑战。

## 火绒安全软件界面分析

火绒的界面整体上非常干净和清爽，界面的风格也是符合现在的潮流。

### 整体界面分析

![image](http://oh913j3dl.bkt.clouddn.com//qml/huorong/0.png)

![image](http://oh913j3dl.bkt.clouddn.com//qml/huorong/0.svg)

整体上可以看作Header, Navigation, Content 三个部分组成

- Header

Header主要展示火绒的logo，当前界面提示，还有右边3个跟窗口相关的按钮：菜单，最小化窗口，关闭窗口。

- Navigation

Navigation主要展示病毒查杀，防护中心，家长控制，扩展工具四个部分，类似TabBar。

- Content

### 病毒查杀

![image](https://www.huorong.cn/assets/v5/images/personPage/checking.png)

![image](http://oh913j3dl.bkt.clouddn.com//qml/huorong/1.png)

![image](http://oh913j3dl.bkt.clouddn.com//qml/huorong/1.svg)

这个界面难在快速查杀那个地方的一个动画，非常不好调试，很难和火绒调得一样顺畅。

### 防护中心

![image](https://www.huorong.cn/assets/v5/images/personPage/fence.png)

![image](http://oh913j3dl.bkt.clouddn.com//qml/huorong/2.png)

### 家长控制

![image](https://www.huorong.cn/assets/v5/images/personPage/control.png)

![image](http://oh913j3dl.bkt.clouddn.com//qml/huorong/3.png)

### 扩展工具

![image](https://www.huorong.cn/assets/v5/images/personPage/expand.png)

![image](http://oh913j3dl.bkt.clouddn.com//qml/huorong/4.png)

![image](http://oh913j3dl.bkt.clouddn.com//qml/huorong/4.svg)

## 最终呈现的效果

### v0.1.0

![image](http://oh913j3dl.bkt.clouddn.com//qml/huorong/0.gif)

## 思考与总结

目前的这4个界面，我做了3天，其中画了不少时间找图标，和测量控件大小。为了图标这个事情，我还特地做了一个字体图标的组件，它可以根据名称直接显示图标，就好像在web中使用一样，非常有用。目前这个控件支持了Material Icons和Font Awesome两种字体。如果需要支持新的字体的话，只需要添加一个名称到Unicode码的映射即可。在做这个界面的时候，我看到一个视频——[QML + Sketch](https://www.youtube.com/watch?v=WFtRMoRkK7c)，在这个演示视频中，做界面的速度非常快，自己和他比，别人是火箭，我就是乌龟。在这个视频里，我了解到了一个设计图的重要意义，尤其是非常精密和详细的图纸，对于快速实现，帮助巨大。

QML做界面有一个特点就是它的容器不是撑开的，之前做web的时候，每次使用div都是靠内容撑开，在QML中这样不行，需要自己去计算每一项的大小。这一点让我很不适应，常常忘记去计算，导致布局出现各种问题。QML会强制我去思考把界面（ui.qml）和逻辑（普通的.qml）分离，考虑如何抽象一个公共的组件，如何让组件重用。后来每次造新组件，我总会同时建立这两个文件，一个方便在Qt Quick Designer中预览和拖拽控件，另一个写一些简单的逻辑，完成界面展示的一些其他需求。

在制作过程中，我自己造了很多组件，比如IconButton，Switch。它们中有的有着共同的逻辑，只是展示不一样，我想把这些共同的东西抽象出来，代码更简洁。在所有的界面中，我觉得最困难的就是那个导航的组件。导航组件不仅仅是展示，还需要动态切换右边的内容。我一直弄不清楚，如何去实现这样的一个功能。QML的example中有一个例子是用TabBar+SwipeView实现的，目前我用很丑陋的方式实现了类似的功能，非常麻烦，后面我希望能写一个更优秀的组件代替目前的。

Qt Quick Control 2是一个很难说的东西，我不熟悉，在使用过程中，大部分的控件都是自己从头做的，很少使用Qt Quick Control 2提供的，一方面是我对这些控件的特性不了解，另一方面是原本提供的控件都很丑，难以完成我的任务。事实上，它提供的控件也很少，可直接修改的东西不多，还得自己去造。对于Qt Quick Control 2这组控件，将是我下一步需要了解的，并对现有的组件进行重构。不过，那是以后的事情了。现在还是专注于把所有的界面做好吧。

调试在QML中是一个比较麻烦的事情，我不能像web那样，在运行时获取每个组件的大小。所以，我写了一个Debug组件，可以看到组件的范围和大小，实现的原理也很简单。如果QML也能像web一样，在运行的时候，可以看到组件的范围和大小，会方便很多。按理说，同是树的结构，应该是有相关的调试工具的，可能我没有找到吧！

实际的开发中，总会遇到这样那样的问题，我把那些东西写在了一个叫TRICKS.md的文件中，比较的乱。要是有相似的经历的话，看到乱糟糟的这些东西，也会有些感触的。

总的来说，第一个版本的火绒就到此为止。QML相对于用Qt/C++去写界面，的的确确要快许多，自由度也大一些，相对也简单一些。倒是我认为最重要的是，首先得有一份漂亮并精细的设计图。有了设计图，无论用什么去实现，都会有了非常明确的目标和方向，也就不会看重用什么去实现，也不会陷于到某些坑中。

## 未来展望

用QML做界面是非常棒的，是有效率的。想要发挥QML的巨大威力，还有很长的路要走。

在下一版中，我的计划是

- 最重要的

把火绒剩下的界面做完

- 持续要做的

组件抽象和封装

- 具体可能做的事项

1. Navigation重构
2. 最顶层的窗口加阴影
3. Navigation左边的动画，当点击其他的项时，需要一个过渡动画，不能直接过去
4. 模拟运行的C++后端