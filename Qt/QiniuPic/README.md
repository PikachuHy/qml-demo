# 七牛图床

### 功能

#### 1. 拖拽图片上传

- [ ] 拖拽到任务栏图标上传

详细描述：

- [ ] 有图片拖拽到任务栏程序图标时，图标变成上传的图标
	
- [ ] 上传过程中，用圆做为图标，圆的填充角度百分比为上传进度百分比

- [ ] 一次性上传多张图片。图片上传后的顺序，和上传前选择的顺序一致。

参考图：

![pic](https://ww4.sinaimg.cn/large/006tKfTcgy1fewqw208xmg30j60aske8.gif)

![pic](https://ww2.sinaimg.cn/large/006tKfTcgy1fewqweqbdrg3078014mxs.gif)

 #### 2. 使用服务上传图片

详细描述：

- [ ] 选中图片上点击右键，选择使用QiniuPic上传

- [ ] 选中图片，然后按下`Ctrl+U`，即可自动上传

  - [ ] 可以自由设定上传快捷键

特殊要求：

即使QiniuPic未运行，系统也要自动启动QiniuPic并自动上传

参考图：

![pic](https://ww4.sinaimg.cn/large/006tKfTcgy1fewqvt4svyg30j60asay7.gif)

#### 3. 复制图片后上传

详细描述：

- [ ] 当检测到剪贴板有图片时，自动上传图片
  - [ ] 可关闭自动上传，该为手动按`Ctrl+Shift+U`上传

参考图：

![pic](https://ww2.sinaimg.cn/large/006tKfTcgy1fewqvevds5g30j60as7rz.gif)

### 设置

- 可选的上传前压缩图片，支持`jpg`,`png`,`gif`

- 可选的上传后播放声音
- 可选的图床（当前仅支持七牛）
- 可选的链接，可以选择复制`URL`，`HTML`，`MarkDown`格式
- 可选的保存上传记录

![pic](https://ps.toolinbox.net/trluz.png)

