/* 词法分析源码 */

%{
#include "../../AST/ast.hpp"  //parser.hpp需要ast.hpp内的定义
#include "../../Parse/cpp/parser.hpp"// parser.hpp是bison编译parser.y生成的头文件，内含token声明和yylval声明。

#define TOKEN_WITHVAL(t)  yylval.string = new std::string(yytext, yyleng);return t; 
#define TOKEN(t)    yylval.token = t;return t;
%}

%option noyywrap
/*//只能处理一个文件，noyywrap可以不需要链接fl库。c++不能连接fl库*/

%%
[0-9]+ { yylval.string = new std::string(yytext, yyleng);return INTEGER; }
[a-zA-Z]+ { TOKEN_WITHVAL(IDENTIFIER) }
"=" { return TOKEN(ASSIGN); }
"+" { return TOKEN(ADD); }
"-" { return TOKEN(SUB); }
"*" { return TOKEN(MUL); }
"/" { return TOKEN(DIV); }
[\r]|[\n]|[\r\n] { return TOKEN(EOL); }
%%

