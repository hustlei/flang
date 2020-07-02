English | [简体中文](README.md)

#  f-lang

## 介绍

Try to design a modern language with 
efficient, simple, 
easy to use, cross platform and glue characteristics.

## f-lang目标

+ **efficient** (like C) fast, and minimum publish volume
+ **simple** (like python) simple syntax, design for user
+ **easy-to-use** (like C#) 
+ **cross platform portable** (like java) 
+ **glue characteristics** (like lua) 
+ **mordern** (like rust、swift，with type prediction, exception handle, meta-programming, memery collection, sync、concurrent etc modern characteristics) 

## f-lang 语言基本定位

1.  compile language
	+ with repl
	+ concider two-level compilation to improve portability and flexibility. compile to intermediate code and translate it into machine code when installing
2.  runtime
	+ no virtual machine
	+ no runtime3.  type
	+ static type
	+ type prediction
	+ weak type like C
	+ native advance data structure，such as list, vector, dict
	+ light weight OO、FP
4.  memery operation
	+ automatic memery collection
	+ no GC
	+ no pintor
    + safety heap operation
5.  native exception handle
6.  native concurrent
7.  interactive with other language
	+ considering independent translation module to interact with other languages to keep the language simple and pure
8.  dsl for special domain
    + UI、graphics：like html5，qml，wpf
    + network：
9. meta-programming
	
## 语言设计

+ [semantic design](doc/semantic.md)
+ [syntax design](doc/syntax.md)
+ [f-lang implement](src/)


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
