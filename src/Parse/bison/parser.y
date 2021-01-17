/* 语法分析器源码 */

%{
#include <string>
#include "../../AST/ast.hpp"
NBlock* astroot; /* the top level root node of AST */

extern int yylex();
void yyerror(const char* s);
%}


/* 将yylval定义为union数据类型，union成员和%uion内部声明相同。
   在flex源码中，可以通过yylval.string形式存储token的值。
   用yylval联合内的成员名称，可以通过%type指令为语法规则指定数据类型
*/
%union {
    NBlock* block;
    Node* node;
    NIdentifier* ident;
    
    std::string* string;
    int token;
}
/* 定义token，<>中表示数据（好像没有起作用），引用union内变量名 */
%token <string> IDENTIFIER INTEGER
%token <token> ADD SUB MUL DIV ASSIGN EOL
/* 定义语法规则数据类型，与union中的变量名对应 */
%type <block> program stmts
%type <node> stmt expr term
%type <ident> ident
/*%start program*/

%left ADD SUB
%left MUL DIV

%%
program: stmts { astroot = $1;}

stmts:
  stmt { $$ = new NBlock(); $$->nodes.push_back($1);}
| stmts stmt { $1->nodes.push_back($2); }
;

stmt:
  ident ASSIGN expr EOL { $$ = new NAssignment(*$1, *$3); printf(">");}
| expr EOL {$$ = $1; printf(">");}
;

expr:
  term
| expr ADD term { $$ = new NBinaryOperate(*$1, $2, *$3); }
| expr SUB term { $$ = new NBinaryOperate(*$1, $2, *$3); }
| expr MUL term { $$ = new NBinaryOperate(*$1, $2, *$3); }
| expr DIV term { $$ = new NBinaryOperate(*$1, $2, *$3); }
;

term:
  ident { $$ = $1; }
| INTEGER { $$ = new NInteger(std::stoi(*$1));  delete $1;}
;

ident:
  IDENTIFIER { $$ = new NIdentifier(*$1); delete $1;}
;
  

;
%%


void yyerror(const char* s) { std::printf("Error: %s\n", s); std::exit(1);}