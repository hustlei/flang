# 介绍

flang是一种简洁、现代、高效，没有虚拟机没有GC的静态编译型语言。

flang寓意 fast, future, further。
flang是一种以实用高效为设计理念的多范式语言，所有的抽象都是基于
“数据+操作+接口+消息”为中心的，具有过程式、面向对象、函数式、
面向并发以及面向数据的语言特征。

flang语言具有类型自动推导，类型方法自动静态分发，必要时动态分发，
类型实例存储位置（栈或堆）自动优化等特性，在语法上尽量简单，在实现上尽量高效。
同时提供编译器标记，为高级优化提供操作空间。

## Hello World
按照约定俗成的惯例，我们先从“Hello, World”程序着手介绍这一编程语言。
下面是flang版的hello world程序代码：

~~~flang
domain flang.example.hello
use sys.*

func main(){
    println("hello world!")
}
~~~

C# 源文件的扩展名通常是.f。假定“Hello, World”程序存储在文件hello.f中，
可以使用下面的命令行编译这个程序：

~~~shell
flang hello.cs -o hello      #flang compile hello.cs的简写
~~~

使用`flang run hello.cs`可以直接编译运行程序。

hello world由一个domain语句、一个use语句、一个main函数组成：

+ domain语句为域声明。domain将代码分隔到不同的逻辑空间内。
+ use语句将指定域下的成员引用到本地。
+ func main() 定义主函数。
+ println为sys域内的函数调用。

## 程序结构

flang源码最后编译链接为模块，模块可以是库或可执行程序。
模块源码由一个或多个源文件组成。
源文件由域声明、域引用、函数定义、类型定义、特性（trait）定义、注释、预处理指令
等组成。flang不支持全局变量定义。

flang可执行程序必须包含一个main函数。flang库模块必须至少包含公开的类型定义、
公开的特性定义或者公开的函数定义中的一个。

~~~flang
domain flang.example.intro

pub sum(a:Int, b:Int):Int
{
    return a+b
}
pub type Animal
{
    var name:Str;
    func setName(name:Str)
    {
        self.name = name
    }
}
~~~

> 源文件中domain语句不可缺少，每个代码文件第一句非注释代码必须是domain
>
> main函数不需要用pub声明。

## 变量和常用类型

flang支持非常丰富的类型，并且原生支持部分复杂类型。
包括Nil类型，布尔类型，数值类型，字符类型、数组、枚举、自定义类型等。

Nil空类型仅有一个值nil。

Bool布尔类型仅有两个值true和false。

数值类型支持8为、16为、32位、64位甚至无限精度整数，以及16、32、64、128位浮点数。
但是建议一般程序把：8位整形Byte，目标机型位数整形Int，目标机型位数浮点型Float，
高精度128位浮点数Decimal，目标机型位数复数Complex作为常用类型。
Char，Str，String分别为字符、字符串、可变字符串类型。

flang中用var关键字定义变量。用let关键字定义常量。
变量类型通过变量名后跟:指明变量类型。
变量类型可以省略，编译器会通过变量赋值自动推断类型。

~~~flang
var a:Int = 1
var s:Char = 'a'
var a = 1  //Int类型变量
let pi = 3.14  //Float类型常量
let pi = 3.14159  //标识符pi绑定为新的值
~~~

let定义的常量为常量不可变更。
重复用let定义pi实际上是标识符pi重新绑定在一个新的常量，原来的3.14常量已被丢弃。

数组类型可以使用方括号快速初始化，并且可以通过方括号下标取得数组的元素。

~~~flang
var arr1 = [1, 2, 3]  //一维Int类型数组，长度为3
var arr2 = [1, 2.5; 3, 4.5; 4, 5] //二维Float类型数组，形状为3x2
var arr3 = [[1, 2], [1, 2, 3]]  //Int类型锯齿形数组，也就是数组的数组。

//var arr1:Int[] = [1 ,2, 3]
//var arr2:Int[,] = [1, 2.5; 3, 4.5; 4, 5]
//var arr3:Int[][] = [[1, 2], [1, 2, 3]]

let a = arr1[0] //数组的第一个元素
let b = arr2[0,1]
arr3[0][1] = 2
~~~

Char类型为一个Unicode字符，32位。
Str类型为一个utf-8编码字符串。

~~~flang
let c = 'a'  //字符变量
let s = "a string"  //字符串变量
let s = s+" for print!\n"  //字符串合并
~~~

> Str字符串不可变，合并操作实际上是创建了一个新字符串。

List和String分别为可变长度数组和可变长度字符串。

~~~flang
var str1:String = "abc"
str1.append("defg")
var list1:List = {1, 2, 3}
list1.append(4)  //{1,2,3,4}
list1.remove(0)  //{2,3,4}
list1.insert(0,0)  //{0,2,3,4}
~~~


序列切片可以引用部分序列的元素。数组、字符串均为可索引的序列。
切片语法如下：

~~~flang
var a = [1, 2, 3, 4, 5]
let slice1 = a[0..2]  //引用第0至第2个元素，不含第2个元素
let slice1 = a[0..]   //引用从0至最后一个元素
let slice1 = a[..]  //引用所有元素
let slice1 = a[0...2]  //引用第0至第2个元素，含第2个元素
~~~

> 切片并没有复制引用的元素，仅仅是记录了引用元素的起始位置。

元组也是一种元素序列，但是元组的元素不能修改，并且元组可以有不同类型元素。
元组的创建使用小括号。元组同样通过方括号下标访问。

~~~flang
let tup1 = (1, 2, 3, 4, 5 )
var tup2 = (1, "a", "b", "c", "d")  //同样不能修改
let tup3 = (50,)  //只有一个元素的元组
println(tup1[2])
let tup4 = tup1 + tup3  //同Str，元组运算实际上是新建元组
~~~

字典是一种可变长度，可修改的键值对无序序列。

字典的每个键值 key=>value 对用冒号 : 分割，每个键值对之间用逗号分割，
整个字典包括在花括号{}中。键必须是唯一的，如果重复，则后面的键值对会替换前面的。
可以通过key作为下标的方式访问字典。

~~~
var d = {'a':1, 'b':2}
let a = d['a']   //a值为1
d['b'] = 3  //修改'b':2为'b':3
d['c'] = 4  //增加元素
d.remove('b')  //删除元素
~~~

> 字典为哈希表，访问复杂度永远为O(1)

枚举类型是由整型数值类型的一组命名常量定义的值类型。
枚举的字面含义是指列出有穷集合中的所有元素。比季节、表示周几的变量。


~~~flang
enum Season
{
    Spring,
    Summer,
    Autumn,
    Winter
}

//也可以指定类型和数值
enum Days: Byte
{
    Monday    = 1,
    Tuesday   = 2,
    Wednesday = 4,
    Thursday  = 8,
    Friday    = 16,
    Saturday  = 32,
    Sunday    = 64
}

let today = Days.Monday  //today实际上只占用一个Byte的内存空间。
~~~

> 每个枚举实例实际上只是指定其中的一个元素，只占用一个整数的内存空间。
          ffffffffff          ffffffffff          ffffffffff          ffffffffff          ffffffffff          ffffffffff
		                                                                     80               99                 120

## 函数


## 运算符及流程控制

## 自定义类型


## 特性

## 访问权限和标记

## 注释

## 预处理指令