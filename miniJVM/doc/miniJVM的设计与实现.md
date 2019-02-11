# miniJVM的设计与实现

## 导语

miniJVM是为了理解Java虚拟机的运转机制而做的一个项目，是2017编程提高群第1季的大作业，由码农翻身提供技术上的咨询和服务。

## 主要工作

Class文件的装载
- 支持简单的classpath的设置
- 从文件系统读取一个文件，形成字节数组
- 验证该文件的魔数

解析常量池

解析字段和方法

基于访问者模式实现javap

基于命令模式实现对字节码指令的执行

## 设计
### JVM主体设计
![JVM主体设计](http://oh913j3dl.bkt.clouddn.com//jvm/MiniJVM.png)
### class file设计
![class file设计](http://oh913j3dl.bkt.clouddn.com//jvm/ClassFile.png)
### 常量池设计
![常量池设计](http://oh913j3dl.bkt.clouddn.com//jvm/ConstantInfo.png)
### 属性设计
![属性设计](http://oh913j3dl.bkt.clouddn.com//jvm/AttributeInfo.png)
### 字节码命令设计
![字节码命令设计](http://oh913j3dl.bkt.clouddn.com//jvm/ByteCodeCommand.png)

**注意：**原始设计由**码农翻身**提供，我根据自己的需要，稍稍做了修改，重新绘制了类图，主体还是跟码农翻身一样。

## 实现

全部采用Java语言实现，使用Intellij IDEA Ultimate 2017.3.5，JDK 1.8作为开发环境。代码托管在[GitHub —— miniJVM](https://github.com/PikachuHy/miniJVM) 。

### 常量池

#### 实现情况

| 常量类型                        | 值    | 是否实现 |
| --------------------------- | ---- | ---- |
| CONSTANT_Class              | 7    | ✓    |
| CONSTANT_Fieldref           | 9    | ✓    |
| CONSTANT_Methodref          | 10   | ✓    |
| CONSTANT_InterfaceMethodref | 11   | ✗    |
| CONSTANT_String             | 8    | ✓    |
| CONSTANT_Integer            | 3    | ✗    |
| CONSTANT_Float              | 4    | ✗    |
| CONSTANT_Long               | 5    | ✗    |
| CONSTANT_Double             | 6    | ✗    |
| CONSTANT_NameAndType        | 12   | ✓    |
| CONSTANT_Utf8               | 1    | ✓    |
| CONSTANT_MethodHandle       | 15   | ✗    |
| CONSTANT_MethodType         | 16   | ✗    |
| CONSTANT_InvokeDynamic      | 18   | ✗    |

#### 常见的常量池结构

```c
CONSTANT_Class_info {  
    u1 tag;  // 值为7
    u2 name_index; 
}
CONSTANT_Fieldref_info {       
    u1 tag;       //值为9
    u2 class_index;       
    u2 name_and_type_index; 
} 
CONSTANT_Utf8_info { 
    u1 tag;   //值为1
    u2 length;  
    u1 bytes[length]; 
}
CONSTANT_Methodref_info {    
    u1 tag;         //值为10
    u2 class_index;       
    u2 name_and_type_index; 
}
CONSTANT_String_info {  
    u1 tag;  
    u2 string_index; 
}
CONSTANT_NameAndType_info {  
    u1 tag;     //值为12
    u2 name_index;  
    u2 descriptor_index; 
}

```

### 属性

#### 实现情况
| 属性名                                  | Java SE | Class文件 | 是否实现 |
| ------------------------------------ | ------- | ------- | ---- |
| ConstantValue                        | 1.0.2   | 45.3    | ✓    |
| Code                                 | 1.0.2   | 45.3    | ✓    |
| StackMapTable                        | 6       | 50.0    | ✓    |
| Exceptions                           | 1.0.2   | 45.3    | ✗    |
| InnerClasses                         | 1.1     | 45.3    | ✗    |
| EnclosingMethod                      | 5.0     | 49.0    | ✗    |
| Synthetic                            | 1.1     | 45.3    | ✗    |
| Signature                            | 5.0     | 49.0    | ✗    |
| SourceFile                           | 1.0.2   | 45.3    | ✗    |
| SourceDebugExtension                 | 5.0     | 49.0    | ✗    |
| LineNumberTable                      | 1.0.2   | 45.3    | ✓    |
| LocalVariableTable                   | 1.0.2   | 45.3    | ✓    |
| LocalVariableTypeTable               | 5.0     | 49.0    | ✗    |
| Deprecated                           | 1.1     | 45.3    | ✗    |
| RuntimeVisibleAnnotations            | 5.0     | 49.0    | ✗    |
| RuntimeInvisibleAnnotations          | 5.0     | 49.0    | ✗    |
| RuntimeVisibleParameterAnnotations   | 5.0     | 49.0    | ✗    |
| RuntimeInvisibleParameterAnnotations | 5.0     | 49.0    | ✗    |
| AnnotationDefault                    | 5.0     | 49.0    | ✗    |
| BootstrapMethods                     | 7       | 51.0    | ✗    |

#### 几个实现的结构

```c
Code_attribute {  
  u2 attribute_name_index;  //指向常量池，应该是UTF8Info ,值为”Code”
  u4 attribute_length;             //属性长度， 不包括开始的6个字节
  u2 max_stack;                       // 操作数栈的最大深度（注：编译时已经确定）
  u2 max_locals;                      // 最大局部变量表个数
  u4 code_length;                    // 该方法的代码长度
  u1 code[code_length];         //真正的字节码
  u2 exception_table_length;    
  { 
        u2 start_pc;   
        u2 end_pc;   
        u2 handler_pc;   
        u2 catch_type;  
} exception_table[exception_table_length];  
  u2 attributes_count;  
  attribute_info attributes[attributes_count]; 
} 
LineNumberTable_attribute {  
     //指向常量池，一定得是“LineNumberTable”
	u2 attribute_name_index;  
     //当前属性的长度，不包括开始的 6 个字节
	u4 attribute_length;  
     //给出了下面 line_number_table[]数组的成员个数
	u2 line_number_table_length; 

	 { 
         //start_pc 项的值必须是 code[]数组的一个索引
         u2 start_pc;    
         // 源文件的行号
         u2 line_number; 
      }  line_number_table[line_number_table_length]; 
} 
LocalVariableTable_attribute {
  //对常量池的索引，必须是LocalVariableTable
  u2 attribute_name_index;  
   //属性的长度，不包括开始的 6 个字节
  u4 attribute_length;  
  //给出了下面 local_variable_table[]数组的成员的数量
  u2 local_variable_table_length;  

  { 
        u2 start_pc;     //局部变量的索引都在范围[start_pc, 
        u2 length;        // start_pc+length)中
        u2 name_index;  // 变量名索引  （在常量池中）
        u2 descriptor_index;   //变量描述索引（常量池中）
        u2 index;   //此局部变量在当前栈帧的局部变量表中的索引
   } local_variable_table[local_variable_table_length]; 
} 

```

### 字节码指令

目前支持的字节码指令很少，只有30多个，但是能够完成简单的分支，循环，多态。

```
aconst_null
iconst_m1
iconst_0 
iconst_1 
iconst_2 
iconst_3 
iconst_4 
iconst_5 
new
invokestatic 
invokespecial
invokevirtual
getfield 
putfield 
getstatic
ldc
dup
bipush 
aload_0
aload_1
aload_2
iload_1
iload_2
iload_3
return
ireturn
astore_1
if_icmpge
if_icmple 
goto
istore_1
istore_2
iadd
iinc
```

### 类加载器

实现对应用级类的加载，但未实现双亲委托模型

### 堆

miniJVM执行时，所有的数据都在堆上，但未实现垃圾回收

### 其他

异常，多线程等均未实现

### 设计模式

主要用到的设计模式有命令模式，访问者模式，单例模式，工厂模式，迭代器模式。

## 小结

通过本次miniJVM的实现，深深的体会到了优秀的设计对实现的好处。我的第一个版本miniJVM是由Qt/C++来实现的，最终失败了。除了Qt/C++本身在流上我处理得不好外，最开始设计的缺乏，导致后面的开发中出现了巨大的困难。当我在实现javap时，看到访问者模式的巧妙运用，不由得眼前一亮。当我在解析执行字节码指令时，看到命令模式的运用，再一次感到自己虽然学了24种设计模式，优点、缺点、经典类图熟于心，但是离在实践中灵活运用还有很长的距离。最后借用一句话共勉。

> 真正了不起的程序员对自己的程序的每一个字节都了如指掌

## 参考

《深入理解Java虚拟机:JVM高级特性与最佳实践》第2版

