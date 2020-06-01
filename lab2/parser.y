%error-verbose
%locations
%{
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "def.h"
extern int yylineno;
extern char *yytext;
extern FILE *yyin;
void yyerror(const char* fmt, ...);
void display(struct ASTNode *,int);
%}

%union {
	int    type_int;
	float  type_float;
    char   type_char;
    char   type_string[2010];
	char   type_id[32];
	struct ASTNode *ptr;
};

//  %type 定义非终结符的语义值类型
%type  <ptr> program ExtDefList ExtDef  Specifier ExtDecList FuncDec CompSt VarList VarDec ParamDec Stmt StmList DefList Def DecList Dec Exp Args STRUCTNAME  CALC FORExp CLACList//STRUCT_SPECIFER

//% token 定义终结符的语义值类型
%token <type_int> INT              /*指定INT的语义值是type_int，有词法分析得到的数值
*/
%token <type_char>CHAR
%token <type_string>STR_CONST
%token <type_id> ID  RELOP TYPE ARRAY STRUCT  /*指定ID,RELOP 的语义值是type_id，有词法分析得到的标识符字符串*/
%token <type_float> FLOAT          /*指定ID的语义值是type_id，有词法分析得到的标识符字符串*/

%token LB RB LP RP LC RC SEMI COMMA      /*用bison对该文件编译时，带参数-d，生成的.tab.h中给这些单词进行编码，可在lex.l中包含parser.tab.h使用这些单词种类码*/
%token DPLUS DMINUS ADDASSIGN MINUSASSIGN STARASSIGN DIVASSIGN DOT PLUS MINUS STAR DIV ASSIGNOP AND OR NOT IF ELSE WHILE RETURN FOR SWITCH CASE COLON DEFAULT CALC_LIST FOREXP
/*以下为接在上述token后依次编码的枚举常量，作为AST结点类型标记*/
%token BOOL EXT_DEF_LIST EXT_VAR_DEF FUNC_DEF FUNC_DEC EXT_DEC_LIST PARAM_LIST STRUCT_DEF PARAM_DEC VAR_DEF DEC_LIST DEF_LIST COMP_STM STM_LIST EXP_STMT IF_THEN IF_THEN_ELSE
%token FUNC_CALL ARGS FUNCTION PARAM ARG ARRAY_CALL STRUCT_CALL VAR_CALL BREAK CONTINUE CALL LABEL GOTO JLT JLE JGT JGE EQ NEQ

%right ASSIGNOP ADDASSIGN MINUSASSIGN STARASSIGN DIVASSIGN
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV
%right UMINUS NOT DPLUS DMINUS
%nonassoc LOWER_THAN_FH
%left DOT LP RP LB RB
%nonassoc LOWER_THEN_ELSE
%nonassoc ELSE
%left ARRAY_FIRST

%%

program: ExtDefList    { display($1,0);semantic_Analysis0($1);}     
         ; 
ExtDefList: {$$=NULL;}
          | ExtDef ExtDefList {$$=mknode(2,EXT_DEF_LIST,yylineno,$1,$2);}   
          ;  
ExtDef:   Specifier ExtDecList SEMI   {$$=mknode(2,EXT_VAR_DEF,yylineno,$1,$2);}   
         |Specifier FuncDec CompSt    {$$=mknode(3,FUNC_DEF,yylineno,$1,$2,$3);}         
         | error SEMI   {$$=NULL;}
         ;
Specifier:  TYPE    {$$=mknode(0,TYPE,yylineno);strcpy($$->type_id,$1);
if(!strcmp($1,"int"))$$->type=INT;
else if(!strcmp($1,"char"))$$->type=CHAR;
else if(!strcmp($1,"float"))$$->type=FLOAT;
} | STRUCT STRUCTNAME LC ExtDefList RC {
    $$=mknode(2,STRUCT_DEF,yylineno,$2,$4);
    $$->type=STRUCT;
}| STRUCT ID {
    $$=mknode(0,STRUCT_DEF,yylineno);strcpy($$->type_id,$2);
    $$->type=STRUCT;
}
           ;      
ExtDecList:  VarDec      {$$=$1;}      
           | VarDec COMMA ExtDecList {$$=mknode(2,EXT_DEC_LIST,yylineno,$1,$3);}
           ;  
STRUCTNAME: {$$=NULL;}|ID {$$=mknode(0,ID,yylineno);strcpy($$->type_id,$1);};
VarDec:  VarDec LB INT RB {$$=mknode(1,ARRAY,yylineno,$1);$$->size = $3;}|ID {$$=mknode(0,ID,yylineno);strcpy($$->type_id,$1);}
;
FuncDec: ID LP VarList RP   {$$=mknode(1,FUNC_DEC,yylineno,$3);strcpy($$->type_id,$1);}//函数名存放在$$->type_id
		|ID LP  RP   {$$=mknode(0,FUNC_DEC,yylineno);strcpy($$->type_id,$1);$$->ptr[0]=NULL;}
        ;  
VarList: ParamDec  {$$=mknode(1,PARAM_LIST,yylineno,$1);}
        | ParamDec COMMA  VarList  {$$=mknode(2,PARAM_LIST,yylineno,$1,$3);}
        ;
ParamDec: Specifier VarDec         {$$=mknode(2,PARAM_DEC,yylineno,$1,$2);}
         ;
CompSt: LC DefList StmList RC    {$$=mknode(2,COMP_STM,yylineno,$2,$3);}
       ;
StmList: {$$=NULL; }  
        | Stmt StmList  {$$=mknode(2,STM_LIST,yylineno,$1,$2);}
        ;
Stmt:   Exp SEMI    {$$=mknode(1,EXP_STMT,yylineno,$1);}
      | CompSt      {$$=$1;}      
      | RETURN Exp SEMI   {$$=mknode(1,RETURN,yylineno,$2);}
      | IF LP Exp RP Stmt %prec LOWER_THEN_ELSE   {$$=mknode(2,IF_THEN,yylineno,$3,$5);}
      | IF LP Exp RP Stmt ELSE Stmt   {$$=mknode(3,IF_THEN_ELSE,yylineno,$3,$5,$7);}
      | WHILE LP Exp RP Stmt {$$=mknode(2,WHILE,yylineno,$3,$5);}
      | FOR LP FORExp RP Stmt{
          $$ = mknode (2,FOR,yylineno,$3,$5);
      }
      ;
FORExp: CALC SEMI CALC SEMI CALC {
    $$ = mknode(3,FOREXP,yylineno,$1,$3,$5);
}
;
CALC:  {$$=NULL;}
      | CLACList {$$=$1;}
      ;
CLACList: Exp {$$=$1;}
      | Exp COMMA CLACList {$$=mknode(2,CALC_LIST,yylineno,$1,$3);}
      ; 
DefList: {$$=NULL; }
        | Def DefList {$$=mknode(2,DEF_LIST,yylineno,$1,$2);}
        ;
Def:    Specifier DecList SEMI {$$=mknode(2,VAR_DEF,yylineno,$1,$2);}
        ;
DecList: Dec  {$$=mknode(1,DEC_LIST,yylineno,$1);}
       | Dec COMMA DecList  {$$=mknode(2,DEC_LIST,yylineno,$1,$3);}
	   ;
Dec:     VarDec  {$$=$1;}
       | VarDec ASSIGNOP Exp  {$$=mknode(2,ASSIGNOP,yylineno,$1,$3);strcpy($$->type_id,"ASSIGNOP");}
       ;
Exp:    Exp ASSIGNOP Exp {$$=mknode(2,ASSIGNOP,yylineno,$1,$3);strcpy($$->type_id,"ASSIGNOP");}
      | Exp AND Exp   {$$=mknode(2,AND,yylineno,$1,$3);strcpy($$->type_id,"AND");}
      | Exp OR Exp    {$$=mknode(2,OR,yylineno,$1,$3);strcpy($$->type_id,"OR");}
      | Exp RELOP Exp {$$=mknode(2,RELOP,yylineno,$1,$3);strcpy($$->type_id,$2);}
      | Exp PLUS Exp  {$$=mknode(2,PLUS,yylineno,$1,$3);strcpy($$->type_id,"PLUS");}
      | Exp MINUS Exp {$$=mknode(2,MINUS,yylineno,$1,$3);strcpy($$->type_id,"MINUS");}
      | Exp STAR Exp  {$$=mknode(2,STAR,yylineno,$1,$3);strcpy($$->type_id,"STAR");}
      | Exp DIV Exp   {$$=mknode(2,DIV,yylineno,$1,$3);strcpy($$->type_id,"DIV");}
      | LP Exp RP     {$$=$2;}
      | MINUS Exp %prec UMINUS   {$$=mknode(1,UMINUS,yylineno,$2);strcpy($$->type_id,"UMINUS");}
      | NOT Exp       {$$=mknode(1,NOT,yylineno,$2);strcpy($$->type_id,"NOT");}
      | DPLUS  Exp    {$$=mknode(2,DPLUS,yylineno,NULL,$2);strcpy($$->type_id,"DPLUS");}
      | Exp DPLUS      {$$=mknode(1,DPLUS,yylineno,$1);strcpy($$->type_id,"DPLUS");}
      | DMINUS  Exp     {$$=mknode(2,DMINUS,yylineno,NULL,$2);strcpy($$->type_id,"DMINUS");}
      | Exp DMINUS      {$$=mknode(1,DMINUS,yylineno,$1);strcpy($$->type_id,"DMINUS");}
      | Exp ADDASSIGN Exp {$$=mknode(2,ADDASSIGN,yylineno,$1,$3);strcpy($$->type_id,"ADDASSIGN");}
      | Exp MINUSASSIGN Exp {$$=mknode(2,MINUSASSIGN,yylineno,$1,$3);strcpy($$->type_id,"MINUSASSIGN");}
      | Exp STARASSIGN Exp {$$=mknode(2,STARASSIGN,yylineno,$1,$3);strcpy($$->type_id,"STARASSIGN");}
      | Exp DIVASSIGN Exp {$$=mknode(2,DIVASSIGN,yylineno,$1,$3);strcpy($$->type_id,"DIVASSIGN");}
      | ID LP Args RP  {$$=mknode(1,FUNC_CALL,yylineno,$3);strcpy($$->type_id,$1);}
      | ID LP RP      {$$=mknode(0,FUNC_CALL,yylineno);strcpy($$->type_id,$1);}
      | Exp DOT Exp  %prec UMINUS {$$=mknode(2,STRUCT_CALL,yylineno,$1,$3);strcpy($$->type_id,"DOT");}
      | Exp LB Exp RB  {$$=mknode(2,ARRAY_CALL,yylineno,$1,$3);}
      | VarDec %prec ARRAY_FIRST         {$$=mknode(2,VAR_CALL,yylineno,$1);}
      //| ID {$$=mknode(0,ID,yylineno);strcpy($$->type_id,$1);}
      | INT %prec LOWER_THAN_FH          {$$=mknode(0,INT,yylineno);$$->type_int=$1;$$->type=INT;}
      | FLOAT %prec LOWER_THAN_FH        {$$=mknode(0,FLOAT,yylineno);$$->type_float=$1;$$->type=FLOAT;}
      | CHAR %prec LOWER_THAN_FH         {$$=mknode(0,CHAR,yylineno);$$->type_char=$1;$$->type=CHAR;}
      | STR_CONST %prec LOWER_THAN_FH {$$=mknode(0,STR_CONST,yylineno);strcpy($$->type_string,$1);$$->type=STR_CONST;}
      | BREAK         {$$=mknode(0,BREAK,yylineno);}
      | CONTINUE       {$$=mknode(0,CONTINUE,yylineno);}
      ;
Args:    Exp COMMA Args    {$$=mknode(2,ARGS,yylineno,$1,$3);}
       | Exp               {$$=mknode(1,ARGS,yylineno,$1);}
       ;
       
%%
#include<stdarg.h>
int main(int argc, char *argv[]){
	yyin=fopen(argv[1],"r");
	if (!yyin) return 0;
	yylineno=1;
	yyparse();
	return 0;
}

void yyerror(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "Grammar Error at Line %d Column %d: ", yylloc.first_line,yylloc.first_column);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, ".\n");
}