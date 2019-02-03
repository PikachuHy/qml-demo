# NES 模拟器

nes文件头部

```text
文件头:
 0-3: string    "NES"<EOF>
   4: byte      以16384(0x4000)字节作为单位的PRG-ROM大小数量
   5: byte      以 8192(0x2000)字节作为单位的CHR-ROM大小数量
   6: bitfield  Flags 6
   7: bitfield  Flags 7
8-15: byte      保留用, 应该为0. 其实有些在用了, 目前不管

CHR-ROM - 角色只读存储器(用于图像显示, 暂且不谈)

Flags 6:
7       0
---------
NNNN FTBM

N: Mapper编号低4位
F: 4屏标志位. (如果该位被设置, 则忽略M标志)
T: Trainer标志位.  1表示 $7000-$71FF加载 Trainer
B: SRAM标志位 $6000-$7FFF拥有电池供电的SRAM.
M: 镜像标志位.  0 = 水平, 1 = 垂直.

Byte 7 (Flags 7):
7       0
---------
NNNN xxPV

N: Mapper编号高4位
P: Playchoice 10标志位. 被设置则表示为PC-10游戏
V: Vs. Unisystem标志位. 被设置则表示为Vs.  游戏
x: 未使用
```