简体中文 | [English](README.en.md)

#  f-lang

## 介绍
尝试设计一个高效、简洁、易用、跨平台、具有胶水特性的现代语言。

## f-lang目标

+ **高效**（像C语言一样）运行速度快，发布体积小
+ **简洁**（像python一样）语法简洁，以用户为中心的设计，贯彻编程语言为人服务的目标
+ **易用**（像C#一样）
+ **跨平台可移植性高**（像java一样）
+ **胶水特性**（像lua一样）
+ **现代**（像rust、swift一样，拥有类型推导，异常处理，元编程，垃圾自动回收，异步、并发等现代语言特性）

## f-lang 语言基本定位

1.  编译型语言
	+ 但有repl解释器
	+ 为提高移植性和灵活性，考虑二级编译，即编译为中间码，安装时翻译为机器码
2.  运行时
	+ 无虚拟机
	+ 无运行时
	+ 但是与其他语言交互可考虑设计小的独立引擎
3.  类型
	+ 静态类型
	+ 类型推导
	+ 类C的弱类型
	+ 原生支持高级数据结构，如list, vector, dict
	+ 轻量级OO、FP
4.  内存管理
	+ 自动垃圾回收
	+ 无GC
	+ 无指针
    + 安全的堆操作
5.  原生的异常处理
6.  原生异步、并发
7.  与其他语言交互
	+ 考虑通过独立翻译模块与其他语言交互，保持语言自身的简洁与纯净
8.  特殊领域，考虑专用dsl设计
    + UI、图形图像等：类似html5，qml，wpf
    + network：
9. 元编程
	
## 语言设计

+ [语义设计](doc/semantic.md)
+ [语法设计](doc/syntax.md)
+ [语言实现](src/)


## 参考语言

1.  C
2.  C++
3.  lisp
4.  java
5.  object-c
6.  C#
7.  D
8.  Smalltalk
9.  swift
10. rust
11. python
12. Erlang
13. Haskell
14. nim
15. kotlin
16. Go
17. F#
18. julia
19. Scala
29. R
30. Ruby
31. perl
32. Typescript
33. Dart
34. Scheme
35. ML
36. Groovy
37. Clojure
38. Crystal
39. Elixir
40. Visual Basic
41. lua
42. Scratch


## 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request

## 后记

萌生设计一个新语言的想法，主要还是因为各种语言感觉对编程人员都不是那么友好，希望程序语言作为工具，能够以为用户为中心，对所有人员都更加友好。

> 无论f-lang最终能否实现，都是一个很好的尝试，希望有相同爱好的同学们一起加入出谋划策。

+ C,C++对非专业人员不太友好
+ python,matlab运行速度以及发布很难受，并且做出工业级的软件也更难
+ C#需要一个庞大的运行环境，并且使用C++的轮子很多时候还不如python方便
+ rust中的Rc<RefCell<BTreeMap<Entity,Box<dyn Layout>>>>这样的语法实在是不好阅读
+ swift倒是各方面都比较均衡的，个人比较喜欢的语言，但是主要服务于Mac OS
