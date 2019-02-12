# miniJVM 

实现一个简单的Java虚拟机。

## 主要工作
Class文件的装载
-	支持简单的classpath的设置
-	从文件系统读取一个文件，形成字节数组
-	验证该文件的魔数

解析常量池

解析字段和方法

基于访问者模式实现javap

基于命令模式实现对字节码指令的执行

更详细的介绍见：[miniJVM的设计与实现](https://github.com/PikachuHy/miniJVM/blob/master/doc/miniJVM%E7%9A%84%E8%AE%BE%E8%AE%A1%E4%B8%8E%E5%AE%9E%E7%8E%B0.md)
或者去我[CSDN Blog](https://blog.csdn.net/qq_32768743/article/details/79691354)
## 参考

1. 《深入理解Java虚拟机:JVM高级特性与最佳实践》第2版

2. 码农翻身 微信公众号

## *说明*
由于编译器等原因，测试用例只能用附带的class才能通过。用自己编译的class文件，常量池等内容顺序会不一样，无法通过测试。

感谢码农翻身做的基础工作

感谢[wangPengch](https://github.com/wangPengch)对我的支持
