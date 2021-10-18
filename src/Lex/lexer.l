/* 词法分析源码 */
/* 用relex把lexer.l生成lexer.cpp*/

/***Definitions***/
%top{
#include "../AST/ast.hpp"    //parser.hpp需要ast.hpp内的定义
#include "../Parse/parser.hpp"    // parser.hpp是bison编译parser.y生成的头文件，内含token声明和yylval声明。
%}

%class{
int level = 0;
}

//definitions section (inclde options and definitions)
%option noyywrap
%option unicode
%option dotall
// main
/*//只能处理一个文件，noyywrap可以不需要链接fl库。c++不能连接fl库*/

D				[0-9]
H				[0-9a-fA-F]
NEWLINE	[\n\r\u{0085}\u{2028}\u{2029}]|\r\n
BLANK		[\p{Zs}\t\v\f]
IM 			j
ID_START	[\p{Lu}\p{Ll}\p{Lt}\p{Lo}\p{Nl}_]
ID_END		[\p{Lu}\p{Ll}\p{Lt}\p{Lo}\p{Nl}_\p{Lm}\p{Nd}\p{Mn}\p{Mc}\{Sk}\p{Pc}\p{Cf}]

/***Rules***/
%%
{D}+					{ yylval.string->assign(str()); return INTEGER; }
domain					{ yylval.string->assign(str()); return domain; }
"/*"(.|\n)*?"*/"        { yylval.string->assign(str()); return COMMENT; }
{ID_START}{ID_END}*		{ yylval.string->assign(str()); return IDENTIFIER; }
"="					    { return yylval.token = ASSIGN; }
"+"					    { return yylval.token = ADD; }
"-"						{ return yylval.token = SUB; }
"*"					    { return yylval.token = MUL; }
"/"						{ return yylval.token = DIV; }
<<EOF>> 		        { return yylval.token = EOF; }
%%
/***User code***/

//int main() {return Lexer().lex();}
