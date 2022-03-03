简体中文 | [English](README.en.md)

#  flang

flang的目标是设计一个兼具脚本语言的优点，但是又能够非常高效运行，工程友好的编程语言。

**目的是更好的服务于现代工业，契合科学研究和工业需求。**
未来的工业领域一定是与程序密不可分的，程序将不仅仅是程序员专有的，还将是各个领域的工具。
程序未来必定是像matlab、labview那样对各领域人员友好的，并且通过编译优化达到c语言那样的效率。


flang基本定位：

+ 可以解释执行、AOT运行，也可以编译为机器码运行。可作为编译语言、可作为脚本。可以先编译后运行，也可以热加载运行代码。
+ 无虚拟机、无GC，不支持指针，采用引用计数(ARC)等方法自动回收堆内存。
+ 静态类型，支持类型推导和泛型。但是提供dynamic动态类型支持，用于特殊情况。
+ 语法简洁。但是可以通过标记（类似C#的Attribute特性，rust的Attribute属性）指定内存及编译特点，进一步提供高级功能优化性能。
+ 能够方面方便的调用C、C++等语言编制的模块。采用类似swig的方式生成接口。

> + 像python一样，代码简洁，开发速度快，同时方便科研和生产，贯彻编程语言为人服务的目标。
> + 像C++、rust一样，抽象成本极低，运行速度快，发布体积小。
> + 像swift、go一样，拥有类型推导，异常处理，对象分配内存自动回收，异步并发等现代语言特性

+ 语法设计以**易用性**为重要要求。语言实现以**效率高**为重要要求。

## flang 语言主要特点

1. 编译型语言(支持二进制编译、AOT，也可以解释运行)
    + 编译型语言，可直接编译为二进制机器码。支持预编译为二进制字节码。
    + 支持AOT和解释方式运行。
        + repl解释器\[独立安装组件\]，可以供学习、研究用。
        + AOT编译器，可内嵌到其他应用\[独立安装组件\]，作为内嵌脚本。在作为服务器端应用时，方便热更新代码。
    + 无虚拟机、无运行时、核心语言小
2. 数据类型
	+ 静态类型（提供dynamic类型支持，方便后期绑定等特殊应用）
	+ 类C的弱类型，数值计算可以自动转换类型。其他类型为强类型。
    + 提供精确计算及无限制精度整数支持。
	+ 原生支持Unicode，默认使用UTF-8编码。
	+ 原生支持高级数据结构，如List, Dict等
	+ 支持泛型
	+ 支持类型推导
3. 语法
    + 尽可能简化语法的情况下，增强功能。贯彻编程语言为人服务的宗旨。
	+ 零成本抽象(静态分发、动态分发、虚表结合优化)
        - 所有程序最终转换为“数据+算法+接口+消息”的组合，(兼顾面向对象、函数式、面向数据、并发编程等)
        - 尽可能的由编译器实现静态分发，必要的情况下采用动态分发方式(也可以用标记自行指定)
4. 内存管理
	+ 无GC、无指针、无运行时
	+ 安全的堆操作，数据对象自动释放堆内存（采用引用计数方法（ARC）回收堆内存）
5. 原生的异常处理
6. 原生异步、并发设计
7. 语言互操作
    + 支持内嵌llvm ir
	+ 用类似swig的方式调用C、C++、rust等模块。用类似lua一样的小模块与动态语言交互。
8. 跨平台
    + 操作系统api包装成类似python的sys, os模块，简洁、通用、方便
    + ui，图像等系统高耦合操作：采用统一的dsl+样式库(类似html+css的方式)。
9. 一定程度的支持反射

## 语言设计

+ [语法设计](doc/specification/中文/目录.md)

flang helloworld代码示例：

~~~
# coding: uft8

use core.prelude

func main(){
  println("hello, world!") 
}
~~~


flang源代码通常有以下三部分组成：

+ 编译器指令或标记（#开头）
+ 外部模块引用（use 外部包）
+ 函数、类型、类型别名或特性定义

> `use core.prelude`：引用core包中最常用的模块或函数，prelude是个关键字，并非引入prelude模块，而是引入core模块中被指定为最常用的一组函数或模块，有点类似通配符`*`。
> main函数是程序入口函数，一个包只能包含一个main函数。main函数默认为pub(public)类型，不需要显式声明。
> 所有的语句，包括编译器指令，外部模块引用都可以用分号表示结束。但是语句独立一行时，可以省略分号。
> flang采用注释，多行用`/* ... */`，单行用`//`，文档注释以`/**`或`///`开头。

flang可以像脚本代码一样使用，即函数外可以编写顶级语句，从而省略main函数声明。

```
# /usr/bin/env flang
# coding: uft8

println("hello, world!") 
```

> 一个包中的多个源文件模块内，只有一个源文件可以使用顶级语句。且顶级语句和main函数不同同时出现在一个包中。

## flang编译器命令

+ 源代码文件编译
    - `flang hello.f`：以脚本方式运行
    - `flang run hello.f`：编译并运行
    - `flang compile hello.f``：编译单个文件
        + 参数 -i -b -s -c 分别表示输出IR、二进制IR、汇编、目标文件。
        可以组合，比如：`-ibc`
+ 交互模式
    - `flang`, or `flang shell` or `flang repl`运行交互式解释器环境
    - `flang play`：运行playground
    - `flang notebook`：运行类似jupyter的交互笔记本
+ 源文件编辑辅助
    - `flang fmt`: or `flang format`格式化源文件
    - `flang doc`:生成文档
+ 源代码组织管理
    - `flang init`:创建一个工程(proj)，proj中包含一个包(pkg)，pkg中含有一个helloworld源代码模块。
    - `flang new pkgname`:在当前proj中增加一个包。
        +`flang new --bin pkgname`:表示目标位二进制执行程序。
        +`flang new --lib pkgname`:则表示库 。
    - `flang dep`:依赖管理
        + `falng dep where`: 显示依赖所在文件夹。
        + `flang dep cache`: 下载依赖到本机。
        + `flang dep config`: 依赖缓存位置等设置。
        + `flang dep update`: 更新依赖，(如果项目依赖设置中指定了最大版本，则最多更新到最大版本)。
        + `flang dep build`: 编译依赖。
        + `flang dep clean`: 清除依赖编译的文件。
        + `flang dep list`: 显示依赖列表
        + `flang dep graph`: 树状显示依赖列表
        + `flang dep verify`: 检测依赖包自下载之后是否被改动过。
        + `flang dep help`: 显示帮助
+ 工程模块编译运行
    - `flang check`:语法检查
    - `flang build`:编译当前模块mod或者项目proj。
        + `flang build --release`: or `-r`编译发布版。默认为--debug
        + `flang build --release --arch:i386 --os:win`交叉编译
    - `flang run`:编译并运行当前模块或项目
    - `flang clean`:清除生成的目标文件
    - `flang test`:编译运行当前模块或项目的测试代码
    - `flang bench`:运行基准测试
+ llvm输出
	- `flang llvm --ast hello.f`:  输出抽象语法树
	- `flang llvm --ir hello.f`: or `-i` 输出ir代码
	- `flang llvm --ir -O3 hello.f -o hello.ll`: 输出ir代码，3级优化
	- `flang llvm --bc hello.f`: or `-b` 输出bitcode（二进制的ir代码）
	- `flang llvm --asm hello.f`: or `-s` 输出汇编代码
+ 安装包辅助命令
    - `flang pkg dirname -o instpkg`: 根据dirname文件夹内容创建instpkg安装包
+ 辅助命令
    - `flang version`：显示版本信息。or `flang ver`
    - `flang update`:升级flang编译器。
    - `flang help`：显示帮助
	- `flang -###`: 打印后续命令执行细节，不执行，-###可以在命令任意位置。如`flang llvm --ast hello.f -###`

 
## 主要参考语言

Python, Rust, Go, Swift, C#, C, C++, Julia, Lua

## 后记

希望能够设计一个语法简洁，功能强大，性能也不错的新语言。
即使最后没有实现也不要紧，欢迎各位大佬萌新一起出谋划策。
