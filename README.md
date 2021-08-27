简体中文 | [English](README.en.md)

#  flang

目的是设计一个兼具python的简洁易用、C++的高效、且没有虚拟机没有GC的静态编译型语言。

## flang目标

+ **简洁**（像python一样，代码简洁）语法简洁，开发速度快，贯彻编程语言为人服务的目标
+ **高效**（像C++一样零成本抽象）运行速度快，发布体积小，且原生支持并行
+ **现代**（像rust、swift一样，拥有类型推导，异常处理，对象分配内存自动回收，异步并发等现代语言特性）


> （不追求rust那样的安全性，但要像Swift一样，适当牺牲运行效率，换来代码安全易用）不支持指针，无GC但通过引用计数等方法释放内存

## flang 语言主要特点

1. 免费开源，基于Apache License，闭源软件也可以免费使用
2. 编译型语言
    + 无虚拟机、无运行时、核心语言小
    + 提供交互式repl解释器\[可选模块\]，供学习，做计算器用。\[独立选装组件\]
    + 提供可内嵌的小型AOT解释器(为应用提供内嵌扩展脚本解决方案）\[独立选装组件\]
3. 数据类型
	+ 静态类型（但是提供dynamic类型支持，用于ActiveX调用后期绑定等，建议少用）
	+ 类C的弱类型，数值计算可以自动转换类型。其他类型为强类型。
	+ 原生支持Unicode，默认使用UTF-8
	+ 原生支持高级数据结构，如List, Dic等
	+ 支持泛型
	+ 支持类型推导
4. 语法
    + 尽可能简化语法的情况下，增强功能
	+ 零成本抽象，所有程序最终转换为“数据+算法+接口+消息”的组合，尽可能的由编译器实现静态分发，必要的情况下采用动态分发方式
5. 内存管理
	+ 无GC、无指针
	+ 安全的堆操作，自动释放堆内存（采用引用计数方法（ARC）回收堆内存）
6. 原生的异常处理
7. 原生异步、并发设计
8. 与其他语言交互
	+ 支持与C语言直接交互
	+ 考虑设计独立模块或引擎（像lua一样小巧，适当损失性能）与其他语言交互，保持语言自身的简洁与纯净

## 语言设计

+ [语法设计](doc/specification/中文/目录.md)

## flang编译器命令

+ 源代码文件编译
    - `flang compile hello.f`:编译单个文件
        * 参数 -i -b -s -c 分别表示输出IR、二进制IR、汇编、目标文件。可以组合，比如：`-ibc`
        * `flang hello.f`:同`flang compile hello.f`
    - `flang run hello.f`:编译单个文件并运行
+ 源文件编辑辅助
    - `flang fmt`: or `flang format`格式化源文件
    - `flang check`:语法检查
    - `flang doc`:生成文档
+ 源代码组织管理
    - `flang init`:创建一个proj，proj中包含一个mod，mod中含有一个helloworld源代码。
    - `flang new modname`:在当前proj中增加一个mod。
        * `flang new --bin modname`:表示目标位二进制执行程序。
        * `flang new --lib modname`:则表示库 
    - `flang dep`:依赖管理
        * `falng dep where`:显示依赖所在文件夹。
        * `flang dep cache`: or `flang dep get` 下载依赖到本机。
            + `flang dep get` or `flang dep download`相同
        * `flang dep config`:依赖缓存位置设置。
        * `flang dep update`:更新依赖，(如果项目依赖设置中指定了最大版本，则最多更新到最大版本)。
        * `flang dep build`:编译依赖。
        * `flang dep clean`:清除依赖编译的文件。
        * `flang dep list`:显示依赖列表
        * `flang dep graph`:树状显示依赖列表
        * `flang dep verify`:检测依赖包自下载之后是否被改动过。
        * `flang dep help`:显示帮助
+ 工程模块编译运行
    - `flang build`:编译当前模块mod或者项目proj。
        * `flang build --release`: or `-r`编译发布版。默认为--debug
        * `flang build --release --arch:i386 --os:win`交叉编译
    - `flang run`:编译并运行当前模块或项目
    - `flang clean`:清除生成的目标文件
    - `flang test`:编译运行当前模块或项目的测试代码
    - `flang bench`:运行基准测试
+ 交互模式
    - `flang play`:运行playground
    - `flang shell`: or `flang repl`运行交互式解释器环境
+ llvm输出
	- `flang llvm --ast hello.f`:  输出抽象语法树
	- `flang llvm --ir hello.f`: or `-i` 输出ir代码
	- `flang llvm --ir -O3 hello.f -o hello.ll`: 输出ir代码，3级优化
	- `flang llvm --bc hello.f`: or `-b` 输出bitcode（二进制的ir代码）
	- `flang llvm --asm hello.f`: or `-s` 输出汇编代码
+ 辅助命令
    - `flang version`：显示版本信息。or `flang ver`
    - `flang update`:升级flang编译器。
    - `flang help`：显示帮助
	- `flang -###`: 打印后续命令执行细节，不执行，-###可以在命令任意位置。如`flang llvm --ast hello.f -###`

 
## 主要参考语言

C, C++, C#, Go, Swift, Rust, Scala, Python, Julia, Lua, Perl

## 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request

## 后记

希望能够设计一个语法简洁，易学易用，性能也不错的以用户为中心的新语言，欢迎各位大佬萌新一起出谋划策。
