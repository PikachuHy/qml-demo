# CSAPP, Representing and Manipulating Information

## Note

### Information Storage

测试大端小端的代码

```c
#include <stdio.h>
#include <string.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    size_t i;
    for(i=0; i<len; i++){
        printf(" %.2x", start[i]);
    }
    printf("\n");
}

void show_int(int x){
    show_bytes((byte_pointer) &x, sizeof(x));
}

void show_float(float x) {
    show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x) {
    show_bytes((byte_pointer) &x, sizeof(void *));
}
void test_show_bytes(int val) {
    int ival = val;
    float fval = (float) ival;
    int *pval = &ival;
    show_int(ival);
    show_float(fval);
    show_pointer(pval);
}
void inplace_swap(int *x, int *y) {
    *y = *x ^ *y;
    *x = *x ^ *y;
    *y = *x ^ *y;
}
void reverse_array(int a[], int cnt) {
    int first, last;
    for (first = 0, last = cnt - 1; first < last; first++, last--){
        inplace_swap(&a[first], &a[last]);
    }
}
void print_array(int* a, int cnt){
    for(int i=0;i<cnt;i++){
        printf("%d ", a[i]);
    }
    printf("\n");
}
int main() {
    printf("Hello, World!\n");
    test_show_bytes(12345);

    int val = 0x87654321;
    byte_pointer valp = (byte_pointer) &val;
    show_bytes(valp, 1);
    show_bytes(valp, 2);
    show_bytes(valp, 3);

    const char *s = "abcdef";
    show_bytes((byte_pointer) s, strlen(s));

    int a[] = {1,2,3,4};
    int b[] = {1,2,3,4,5};
    reverse_array(a,4);
    reverse_array(b,5);
    print_array(a,4);
    print_array(b,5);
    return 0;
}
```



### Integer Representation

- 公式比较难搞定，先放下
- Java在各种细节上定义得比较完善，这也许就是它的规范为什么会长那么多吧！
- 补码那里还没怎么弄明白
- 这一行编译不过，很奇怪

```c
printf("x = %" PRId32 ", y = %" PRIu64 "\n", x, y);
```

- `getpeername`缺陷的例子，有符号和无符号之间的转换着实危险
- 无符号数编码的定义

对向量$\vec{x}=[x_{w-1},x_{w-1},\dots ,x_0]$ :
$$
B2U_w(\vec{x}) \dot{=} \sum_{i=0}^{w-1}x_i2^i
$$

- 补码编码的定义

对向量$\vec{x}=[x_{w-1},x_{w-1},\dots ,x_0]$ :
$$
B2T_w(\vec{x})\dot{=}-x_{w-1}2^{w-1} + \sum_{i=0}^{w-2}x_i2^i
$$

- 反码(Ones' Complement)

$$
B2O_w(\vec{x})\dot{=}-x_{w-1}(2^{w-1}-1) + \sum_{i=0}^{w-2}x_i2^i
$$

- 原码(Sign-Magnitude)

$$
B2S_w(\vec{x})\dot{=}(-1)x_{w-1} ·  \sum_{i=0}^{w-2}x_i2^i
$$

- 补码转换为无符号数

对满足$TMin_w \le x \le TMax_w$的$x$有：
$$
T2U_w(x)=\left\{
\begin{aligned}
x + 2^w, x < 0 \\
x, x \ge 0 
\end{aligned}
\right.
$$
当一个有符号数映射为它相应的无符号数时，负数就被转换成打的正数，而非负数会保持不变。

- 无符号数转换为补码

对满足$0 \le u \le UMax_w$的$u$有：
$$
U2T_w(u)=\left\{
\begin{aligned}
u, u  \le  TMax_w \\
u - 2^w, u > TMax_w
\end{aligned}
\right.
$$

- `-1 < 0U`

什么时候需要无符号数? 位的集合，数字由字的数组表示

### Integer Arithmetic

- XDR库案例，想想以后每个乘法的地方都还要考虑一下是不是会溢出，心智负担很重啊
- 无符号数加法

$$
x +_w^u y=\left\{
\begin{aligned}
x + y,  &x + y  <  2^w  正常\\
x + y - 2^w, & 2^w \le x + y < 2^{w+1} 溢出
\end{aligned}
\right.
$$

- 无符号数求反

$$
-_w^u x=\left\{
\begin{aligned}
x,  &x = 0\\
2^w - x, & x > 0
\end{aligned}
\right.
$$

- 补码加法

$$
x +_w^t y=\left\{
\begin{aligned}
x + y - 2^w,  &2^{w-1} <  x + y\\
x + y,  &-2^{w-1} \le x + y  <  2^{w-1}  正常\\
x + y + 2^w, & x + y < -2^{w-1} 溢出
\end{aligned}
\right.
$$

- 补码的非

$$
-_w^t x=\left\{
\begin{aligned}
TMin_w,  &x = TMin_w\\
-x,& x > TMin_w
\end{aligned}
\right.
$$

- 无符号乘法

$$
x *_x^u = (x · y) mod 2^w
$$

- 补码乘法

对满足$TMin_w \le x, y \le TMax_w$  的$x$和$y$ 有：
$$
x *_x^u =U2T_w( (x · y) mod 2^w)
$$
用移位、加法和减法的组合来消除很多整数乘以常数的情况

计算机执行的“整数”运算实际上是一种模运算形式



### Floating Point

- Airiane 5案例，（复用的风险）
- IEEE浮点标准 $V=(-1)^s \times M \times 2^E$

符号，尾数、阶码

`-0.0`和`+0.0`在某些方面被认为是不同的，而在其他方面是相同的。

向偶舍入

### Summary

这一章的确公式和定义比较多，泛读一遍后，只记住了几个案例付出了惨痛的代价。下一周再精读一遍。

第二周

仔细看了整数各转换公式，感觉很多都是在处理溢出情况，尤其是作业题，各种转换，比如容易绕晕。还有怎么判溢出，有符号和无符号之间的转换底层位模式不变，是不是就是信息就是位+上下文的一个很好的例子呢？

## 思考（不定期补充）

- C/C++是不是永远没有稳定的ABI

大小端的问题就搞不定吧

- 由移位操作想到的，`System.out.println((int)(char)(byte)-1)`最后输出多少

65535。

- 很好奇这些数的计算，溢出了怎么处理
- 为什么都采用补码表示