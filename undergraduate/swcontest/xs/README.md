# 形声-Sirius

形声 以形作声

## 项目简介

形声是一款基于深度学习技术通过动作识别为舞蹈视频自动添加匹配的背景音乐的人工智能app。它能够通过对输入的舞蹈视频进行分析，通过对人物舞蹈姿态的检测，结合相应的背景音乐进行学习。在训练结束后，可以通过用户上传的任意舞蹈动作生成独一无二的背景音乐，对视频进行合成，并呈现给用户，以使得用户轻松地把一段枯燥的视频变得有声有色。

## 项目目录结构

```
xs
├── client
├── midi
└── xsnet
```
说明
1. xs为项目主目录，该目录下存放client,xsnet,midi共3个文件夹和其他常用的数据处理脚本
2. client为安卓源码目录
3. xsnet为自己编写的深度学习部分代码

项目主目录下文件用途说明

| 文件名                              | 用途               |
| -------------------------------- | ---------------- |
| convert_to_dataset.py            | 将节点信息转换为数据集，不带标签 |
| convert_to_dataset_with_label.py | 将节点信息转换为数据集，带标签  |
| extract_all.py                   | 从视频中提取帧          |
| extract_pose.py                  | 从帧中提取节点信息        |

xsnet目录下主要文件用途说明

| 文件名         | 用途           |
| ----------- | ------------ |
| datasets.py | 为深度学习训练提供数据集 |
| model.py    | 为深度学习提供模型    |
| train.py    | 为深度学习提供训练代码  |
| server.py   | 对外提供web服务的代码 |

midi目录下主要文件用途说明

| 文件名                   | 用途                                       |
| --------------------- | ---------------------------------------- |
| MidiFileAnalysis.py   | 将midi文本文件解析成二维数组，每行代表一个记录，包括音调，发声位置，关闭位置，发声音量，关闭音量。使用音符组合序列生成midi文本文件。 |
| DataBaseInit.py       | 将包含midi信息的二维数组中的音符组合提取到database.txt中，并标记，把midi二维数组转化为标签序列。依据database.txt将音符组合标签序列转化为音符组合序列。 |
| DriveMidConversion.py | 提供从midi文件中提取音符组合标签序列的方法，提供将音符组合标签序列反向生成midi文本文件的接口。提供将midi音乐文件转化为midi文本文件的接口。 |
| midi.config           | 记录midi音乐的标识                              |
| database.txt          | 记录音符组合的标签                                |

补充说明，在该目录下还有两个子目录，它们的作用分别是：　


| 文件夹     | 用途           |
| ------- | ------------ |
| midiSrc | 用于存储midi音乐文件 |
| midiTxt | 用于存储midi文本文件 |

## 训练

### 前置要求

需要安装OpenPose和ffmpeg。深度学习框架Chainer。

可以去GitHub下载，编译安装。

[OpenPose GitHub](https://github.com/CMU-Perceptual-Computing-Lab/openpose)

[ffmpeg GitHub](https://github.com/FFmpeg/FFmpeg)

[chainer GitHub](https://github.com/PikachuHy/chainer.git) 我自己的地址

### 数据准备

本网络采用xs-7作为数据集，在开始训练前需要下载数据集。我将数据集存放在google driver上，因为第三协议，暂不能公开数据集。等过了有效期，再说。

数据集下载完毕后，需要使用主目录下的脚本进行帧提取，节点信息提取。

```shell
python extract_all.py
python extract_pose.py
```

最后将数据变为xsnet需要的形式

如果需要带标签

```
python convert_to_dataset_with_label.py
```

不带标签

```
python convert_to_dataset.py
```

### 开始训练

```
cd xsnet 
python train.py
```

在Tesla P100环境下，训练大概12个小时，可以得到一个比较好的模型。

### 测试

启动服务器

```
bash run_server.sh
```

然后上传视频文件即可。

## 相关论文

我们实现主要的论文依据

### seq2seq方面

Cho K, Van Merriënboer B, Gulcehre C, et al. Learning phrase representations using RNN encoder-decoder for statistical machine translation[J]. arXiv preprint arXiv:1406.1078, 2014.

Sutskever I, Vinyals O, Le Q V. Sequence to sequence learning with neural networks[C]//Advances in neural information processing systems. 2014: 3104-3112.

Bahdanau D, Cho K, Bengio Y. Neural machine translation by jointly learning to align and translate[J]. arXiv preprint arXiv:1409.0473, 2014.

Jean S, Cho K, Memisevic R, et al. On using very large target vocabulary for neural machine translation[J]. arXiv preprint arXiv:1412.2007, 2014.

\2015. A Neural Conversational Model[J]. Computer Science

Vinyals O, Bengio S, Kudlur M. Order matters: Sequence to sequence for sets[J]. arXiv preprint arXiv:1511.06391, 2015.

### OpenPose方面

Cao Z, Simon T, Wei S E, et al. Realtime multi-person 2d pose estimation using part affinity fields[C]//CVPR. 2017, 1(2): 7.
Wei S E, Ramakrishna V, Kanade T, et al. Convolutional pose machines[C]//Proceedings of the IEEE Conference on Computer Vision and Pattern Recognition. 2016: 4724-4732.

Simon T, Joo H, Matthews I, et al. Hand keypoint detection in single images using multiview bootstrapping[C]//The IEEE Conference on Computer Vision and Pattern Recognition (CVPR). 2017, 2.

=============================================================

### 网络底层的论文依据

LeCun Y, Boser B, Denker J S, et al. Backpropagation applied to handwritten zip code recognition[J]. Neural computation, 1989, 1(4): 541-551.
LeCun Y, Bottou L, Bengio Y, et al. Gradient-based learning applied to document recognition[J]. Proceedings of the IEEE, 1998, 86(11): 2278-2324.

Hochreiter S, Schmidhuber J. Long short-term memory[J]. Neural computation, 1997, 9(8): 1735-1780.



## 相关仓库

[Chainer_Realtime_Multi-Person_Pose_Estimation](https://github.com/PikachuHy/Chainer_Realtime_Multi-Person_Pose_Estimation)
[OpenPose](https://github.com/CMU-Perceptual-Computing-Lab/openpose)

seq2seq

## 相关开发人员

根据规定，暂不公开，等过了有效期。