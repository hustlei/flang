compiler structure


+ fronteend //前端从源代码生成抽象语法树
    + lexer(source -> token) //lexical analysis词法分析生成符号表
    + parser(token -> ast)   //syntactic analysis语法分析生成初级语法树
    + sematic(ast -> conformance ast) //semantic analysis 语义分析生成合规语法树
    + static analyzer //程序静态分析，检查程序错误
    + codegen(ast -> IR)  //语法树生成平台无关中间代码
+ optimizer //优化IR
+ backend   //


