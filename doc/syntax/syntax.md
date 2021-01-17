flang语法设计

# 数据类型

+ 静态数据类型
    - 编译期确定类型，支持类型推导。
    - 提供动态类型支持(像C#一样可以定义动态类型用于特殊应用，如Activex后绑定等）
+ 所有数据类型均有基础方法。
    - 所有数值类型均继承自Num
	- 所有数组均继承自Array
	- 所有字典继承自Map
	- 所有类继承自Object
	- 所有函数继承自Function
    - 所有类型均继承自Type，通过Type可以获取类型信息
+ 弱类型(数值计算时，低精度类型自动向高精度类型转换)


内置类型

+ 布尔
    + True
    + False
+ 数字
    + 整数
	    + Bit
        + Int, Int8, Int16, Int32, Int64, Int128
        + Uint, Uint8, Uint16, Uint32, Uint64, Uint128
    + 浮点数
        + single, double, decimal
+ 文本
    + string
+ 数组
+ 元组、向量、列表、队列
+ 集合
+ 字典
+ 枚举
+ 


