# CSAPP, Machine-Level Representation

用高级语言编写的程序可以在很多不同的机器上编译和执行，而汇编代码则是与特定机器密切相关的。

1. 历史观点
摩尔定律，芯片上的晶体管数量每年都会翻一番。

2. 程序编码
```shell
gcc -Og -o p p1.c p2.c
```
程序计数器(PC)
整数计数器
条件码寄存器
向量寄存器
```shell
gcc -Og pc mstore.c
```
机器执行的程序只是一个字节序列，它是一系列指令的编码。
```shell
objdump -d mstore.o
gcc -Og -o prog main.c mstore.c
objdump -d prog
gcc -Og -S mstore
```

3. 数据格式

| C声明  | Intel数据类型 | 汇编代码后缀 | 大小(字节) |
| ------ | ------------- | ------------ | ---------- |
| char   | 字节          | b            | 1          |
| short  | 字            | w            | 2          |
| int    | 双字          | l            | 4          |
| long   | 四字          | q            | 8          |
| char*  | 四字          | q            | 8          |
| float  | 单精度        | s            | 4          |
| double | 双精度        | l            | 8          |

4. 访问信息

操作符(operand) 立即数(immediate) 寄存器(register) 内存引用

5. 算术和逻辑操作

6. 控制
7. 过程
8. 数组分配和访问
9. 异质的数据结构
10. 在机器级程序中将控制与数据结合起来
11. 浮点代码



## 思考（不定期补充）

