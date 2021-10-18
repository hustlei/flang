English | [简体中文](README.md)

#  flang

Try to design a modern language with efficient(like C++), simple(like python), 
easy to use(like swift) and glue characteristics.

+ **efficient** (like C) fast, and minimum release size
+ **simple** (like python) simple syntax, design for user
+ **easy-to-use** (like C#) 
+ **glue characteristics** (like lua) 
+ **mordern** (like rust、swift，with type prediction, exception handle, meta-programming, memery collection, sync、concurrent etc modern characteristics) 


>> Appropriately sacrifice the runtime efficiency to make the code safe and easy to use.
>> not support pointers, no GC，releases memory by ARC.

## flang features

1. Free Opensource，using Apache License
2.  compile language
    + no virtual machine, no runtime(auto release heap memery by ARC)
	+ concider two-level compilation to improve portability and flexibility. compile to intermediate code and translate it into machine code when installing
  	+ with repl for learning
    + with embedable jit engine, for script embeded in programs
3.  type
	+ static type(support dynamic type, for special use)
	+ weak type like C
    + native accurate calculations and unrestricted precision integer
    + native support Unicode, default use utf-8
	+ native advance data structure，such as list, vector, dict
	+ type prediction, generic type
4. grammer
    + light weight
	+ Zero-cost abstraction, all programs are finally converted into a combination
    of "data + algorithm + interface + message", and static distribution is achieved
    by the compiler as much as possible, and dynamic distribution is adopted when necessary
5. memery management
	+ no GC、no pointer、no runtime
	+ safety heap operation，automatic release heap memery by ARC
6. native exception handle
7. native asynchronous and concurrent design
8. interactive with other language
    + embed llvm ir
    + directly interactive with C
	+ considering independent translation module to interact with other languages to keep the language simple and pure
9. cross platform
    + using specific platform api
    + UI、graphics：using dsl standard library implemented like html5，qml，wpf

## language

+ [grammer design](doc/Specification/english/index.md)

flang helloworld example：

~~~
// helloworld.f
domain hello
use sys.*

pub func main(){
  println("hello, world!")
}
~~~


The source code usually consists of the following four parts:

+ Comment
+ Domain declaration
+ External domain reference
+ Function, type, type alias or characteristic definition 

## flang tools command

+ compile source file
    - `flang compile hello.f`: `or flang hello.f` compile single file
        + parameter -i -b -s -c means output IR, bitcode IR, assembly code, binary file.
        support combine mode, such as：`-ibc`
    - `flang run hello.f`: compile single file and run
+ source code edit assistant
    - `flang fmt`: or `flang format` format code
    - `flang check`:语法检查
    - `flang doc`:生成文档
+ 源代码组织管理
    - `flang init`:创建一个proj，proj中包含一个mod，mod中含有一个helloworld源代码。
    - `flang new modname`:在当前proj中增加一个mod。
        +`flang new --bin modname`:表示目标位二进制执行程序。
        +`flang new --lib modname`:则表示库 。
    - `flang dep`:依赖管理
        + `falng dep where`:显示依赖所在文件夹。
        + `flang dep cache`: or `flang dep get` or `flang dep download` 下载依赖到本机。
        + `flang dep config`:依赖缓存位置设置。
        + `flang dep update`:更新依赖，(如果项目依赖设置中指定了最大版本，则最多更新到最大版本)。
        + `flang dep build`:编译依赖。
        + `flang dep clean`:清除依赖编译的文件。
        + `flang dep list`:显示依赖列表
        + `flang dep graph`:树状显示依赖列表
        + `flang dep verify`:检测依赖包自下载之后是否被改动过。
        + `flang dep help`:显示帮助
+ 工程模块编译运行
    - `flang build`:编译当前模块mod或者项目proj。
        + `flang build --release`: or `-r`编译发布版。默认为--debug
        + `flang build --release --arch:i386 --os:win`交叉编译
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
+ 安装包辅助命令
    - `flang pkg dirname -o instpkg`: 根据dirname文件夹内容创建instpkg安装包
+ 辅助命令
    - `flang version`：显示版本信息。or `flang ver`
    - `flang update`:升级flang编译器。
    - `flang help`：显示帮助
	- `flang -###`: 打印后续命令执行细节，不执行，-###可以在命令任意位置。如`flang llvm --ast hello.f -###`

 
## main referance language

C, C++, C#, Go, Swift, Rust, Scala, Python, Julia, Lua
