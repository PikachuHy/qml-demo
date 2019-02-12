# Java Web 开发基础设施

为了方便从头快速开发，把经常用的类库放在一起，作为一个基础工程，以后新项目只需要基于这个工程去去修改，好好专注业务。

核心基础设施

core包下

BaseObject类
使用FastJson重写toString
所有的POJO类继承这个类，方便调试

BaseController类
提供一些方便的方法返回数据给前端
所有的Controller继承这个类

Response类
封装http Response，参考http响应码
所有的Controller返回这个类

GlobalExceptionHandler类
全局错误处理
所有的Runtime异常在这里处理