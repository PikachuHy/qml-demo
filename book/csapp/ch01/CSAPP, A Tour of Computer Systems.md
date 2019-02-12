# CSAPP, A Tour of Computer Systems

## Note

### Information Is Bits + Context

我们写的`hello.c` (source file)

```c
#include <stdio.h>

int main(){
    printf("hello, world\n");
    return 0;
}
```

计算机里的`hello.c` (ASCII representation)

![img](http://cdn.pikachu.net.cn//book/csapp/ch01/1.png)

### Programs Are Translated by Other Programs into Different Forms

![img](http://cdn.pikachu.net.cn//book/csapp/ch01/2.png)

- Preprocessing phase
- Compilation phase
- Assembly phase
- Linking phase

### It Pays to Understand How Compilation System Work

reasons:

- Optimizing program performance
- Understanding link-time errors
- Avoiding secrity holes

### Processors Read and Interpret Instructions Stored in Memory

#### Hardware Orgnization of a System

- Buses
- I/O Devices
- Main Memory
- Processor

### Caches Matter

- A system spends a lot of

time moving information from one place to another. 

- Application programmers who are aware of cache memories can exploit them to improve the performance of their programs by an order of magnitude.     



速度差异

提升性能

### Storage Devices Form a Hierarchy

![img](http://cdn.pikachu.net.cn//book/csapp/ch01/3.png)



### The Operating System Manages the Hardware

![img](http://cdn.pikachu.net.cn//book/csapp/ch01/4.png)

操作系统是管理硬件的，为了管好硬件，做了一些抽象

- Processes
- Threads
- Virtual Memory
- Files

### System Communicate with Other Systems Using Networks

得益于抽象

From the point of view of an individual system, the network can be viewed as just another I/O device.

### Important Themes

#### Amdahl's Law

$$
T_{new} =  (1 - \alpha)T_{old} + (\alpha T_{old})/k \\
= T_{old}[(1-\alpha)+\alpha/k]
$$

$$
S = \frac{1}{(1-\alpha)+\alpha/k}
$$

#### Concurrency and Parallelism

- Thread-Level Concurrency
- Instruction-Level Parallelism
- Single-Instructio, Multiple-Data (SIMD) Parallelism

#### The Importance of Abstractions in Computer Systems

![img](http://cdn.pikachu.net.cn//book/csapp/ch01/5.png)

### Summary

没啥好抄的。。。

## 思考（不定期补充）

- 什么是超线程(Hyperthreading)

> Hyperthreading, sometimes called simultaneous multi-threading, is a technique that allows a single CPU to execute multiple flows of control.     

超线程技术就是利用特殊的硬件指令，把一个物理内核模拟成两个逻辑内核，让单个处理器都能使用线程级并行计算，进而兼容多线程操作系统和软件，减少了CPU的闲置时间，提高了CPU的运行速度。采用超线程即是可在同一时间里，应用程序可以使用芯片的不同部分。 

- 为什么`C/C++`很难做模块化(module)

目前只知道js模块化已经在应用了，java的模块化虽然出来了，但是基本没有用，主要原因是可能是JDK未做模块化，而java本身模块化做得不错。C++的模块化也一直在关注，好像没什么进展。听说一部分原因是要兼容`c`和宏。*Programs Are Translated by Other Programs into Different Forms* 中第一步就是预处理（文本替换），严重拖慢速度，C++模块化的一个要求就是要处理这里的速度问题。

- 优化是怎么做到的

在AI大行其道的时代（还有挖矿），提升速度是非常重要的。以前听说过`SIMD`优化，不知道什么意思，以为很厉害很厉害的。那么优化最后是不是尽量利用硬件指令，调整一些数字以利用缓存（如CPU的L1 cache的某个大小）