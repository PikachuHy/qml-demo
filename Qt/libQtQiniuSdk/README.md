# Qiniu Resource Storage SDK for Qt/C++

[![Qiniu Logo](http://devtools.qiniu.com/qiniu-logo.jpg)](http://qiniu.com/)
目标是
> 此 Qt/C++ SDK 适用于 兼容c++11标准的C++编译器，基于七牛云存储官方API构建。使用此 SDK 构建您的网络应用程序，能让您以非常便捷地方式将数据安全地存储到七牛云存储上。无论您的网络应用是一个网站程序，还是包括从云端（服务端程序）到终端（手持设备应用）的架构的服务或应用，通过七牛云存储及其 SDK，都能让您应用程序的终端用户高速上传和下载，同时也让您的服务端更加轻盈。

## 实现进度

- 文件直传

参考博客：[实现七牛云Qt SDK文件直传部分](https://blog.csdn.net/qq_32768743/article/details/87307822)

## 使用

参考代码：demo目录下的代码

## TODO

- [ ] 删除文件

## 已知问题

- 偶尔出现bad token

```json
{"error":"bad token"}
```

重试一次就好了

## 贡献代码

1. Fork
2. 创建您的特性分支 (`git checkout -b my-new-feature`)
3. 提交您的改动 (`git commit -am 'Added some feature'`)
4. 将您的修改记录提交到远程 `git` 仓库 (`git push origin my-new-feature`)
5. 然后到 github 网站的该 `git` 远程仓库的 `my-new-feature` 分支下发起 Pull Request

