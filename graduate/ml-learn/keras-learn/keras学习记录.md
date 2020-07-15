# keras学习记录

学习资源：https://www.bilibili.com/video/BV1TW411Y7HU

## 拟合一次函数

代码见：https://github.com/PikachuHy/Oak-Pokemon-Research-Lab/blob/master/graduate/ml-learn/keras-learn/keras_1.py

输入

![image-20200715150622074](C:\Users\pikachu\AppData\Roaming\Typora\typora-user-images\image-20200715150622074.png)

输出

![image-20200715150633244](C:\Users\pikachu\AppData\Roaming\Typora\typora-user-images\image-20200715150633244.png)

代码中出现的问题

```python
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'
```

表示只允许出现ERROR以上级别的日志

![在这里插入图片描述](https://img-blog.csdnimg.cn/2018122710310486.png)

![在这里插入图片描述](https://img-blog.csdnimg.cn/20181227104509390.png)

这里参考：https://blog.csdn.net/qq_40549291/article/details/85274581

但是，它只能控制cpp部分的日志，它不能控制python的日志，如

```shell
WARNING:tensorflow:From /root/anaconda3/envs/ncc/lib/python3.6/site-packages/keras/backend/tensorflow_backend.py:66: The name tf.get_default_graph is deprecated. Please use tf.compat.v1.get_default_graph instead.

/tmp/keras-learn/keras_1.py:21: UserWarning: Update your `Dense` call to the Keras 2 API: `Dense(input_dim=1, units=1)`
  model.add(Dense(output_dim=1, input_dim=1))
WARNING:tensorflow:From /root/anaconda3/envs/ncc/lib/python3.6/site-packages/keras/backend/tensorflow_backend.py:541: The name tf.placeholder is deprecated. Please use tf.compat.v1.placeholder instead.

WARNING:tensorflow:From /root/anaconda3/envs/ncc/lib/python3.6/site-packages/keras/backend/tensorflow_backend.py:4432: The name tf.random_uniform is deprecated. Please use tf.random.uniform instead.

WARNING:tensorflow:From /root/anaconda3/envs/ncc/lib/python3.6/site-packages/keras/optimizers.py:793: The name tf.train.Optimizer is deprecated. Please use tf.compat.v1.train.Optimizer instead.

WARNING:tensorflow:From /root/anaconda3/envs/ncc/lib/python3.6/site-packages/keras/backend/tensorflow_backend.py:1033: The name tf.assign_add is deprecated. Please use tf.compat.v1.assign_add instead.

WARNING:tensorflow:From /root/anaconda3/envs/ncc/lib/python3.6/site-packages/keras/backend/tensorflow_backend.py:1020: The name tf.assign is deprecated. Please use tf.compat.v1.assign instead.

```

可以通过

```python
import tensorflow as tf

tf.logging.set_verbosity(tf.logging.ERROR)
```

消除python代码部分的warning日志

然后是兼容代码，去掉其他的warning

```python
import tensorflow.compat.v1 as tf
Dense(units=1, input_dim=1)
```

`Dense`的`output_dim`改`units`

```python
np.random.normal(0, 0.05, (200,))
```

是从高斯分布中采样200个，返回数据是(200,)的ndarray

```python
plt.scatter(X_test, Y_test)
plt.plot(X_test, Y_pred)
```

`scatter`是画散点图，`plot`是画直线

## mnist图片分类

出现warning

```python
UserWarning: The `nb_epoch` argument in `fit` has been renamed `epochs`.
  model.fit(X_train, y_train, nb_epoch=2, batch_size=32)
```

将

```python
model.fit(X_train, y_train, nb_epoch=2, batch_size=32)
```

改为

```python
model.fit(X_train, y_train, epochs=2, batch_size=32)
```

即可消除warning

```python
X_train = X_train.reshape(X_train.shape[0], -1) / 255
```

将`(60000, 28, 28)`转成`(60000, 28 * 28)`，然后再把数值控制在0到1

```python
y_train = np_utils.to_categorical(y_train, num_classes=10)
```

就是将索引变成one-hot编码

`Dense`其实就是全连接层FC,  
$$
y=a*x+b
$$
Relu

![img](https://bkimg.cdn.bcebos.com/pic/d788d43f8794a4c25b5e4dd902f41bd5ac6e39c6?x-bce-process=image/resize,m_lfit,w_268,limit_1/format,f_jpg)
$$
f(x)=max(0, x)
$$
categorical_crossentropy是多分类的交叉熵损失，具体细节后面再学

我决定比较神奇的是

```python
metrics=['accuracy']
```

传入这个指标就可以直接算出来，比较方便

## TODO

- mse
- sgd
- categorical_crossentropy
- RMSprop
- softmax