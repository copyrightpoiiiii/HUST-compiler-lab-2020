%{
#include "parser.tab.h"
#include "string.h"
#include "def.h"
int yycolumn=1;
#define YY_USER_ACTION    	yylloc.first_line=yylloc.last_line=yylineno; \
	yylloc.first_column=yycolumn;	yylloc.last_column=yycolumn+yyleng-1; yycolumn+=yyleng;
typedef union {
	int    type_int;
	float  type_float;
    char   type_char;
    char   type_string[2010];
	char   type_id[32];
	struct ASTNode *ptr;
} YYLVAL;
char string_buf[2010]; /* to assemble string constants */
char *string_buf_ptr;
#define YYSTYPE YYLVAL
int strLen;
int isNull;
%}
%option yylineno

id   [A-Za-z][A-Za-z0-9]* 
char 	\'[0-9a-zA-Z]\' 
int    [0-9]+|(0[xX][0-9a-fA-f]+)
float  ([0-9]*\.[0-9]+)|([0-9]+\.)


%x ROW_COMMENT BLOCK_COMMENT String
%%

"//"            {BEGIN ROW_COMMENT;}
<ROW_COMMENT>[^\n] {}
<ROW_COMMENT>\n {BEGIN INITIAL;yycolumn=1;}
"/*"           {BEGIN BLOCK_COMMENT;}
<BLOCK_COMMENT>\n {yycolumn=1;}
<BLOCK_COMMENT><<EOF>> {
    printf("Error type B :find EOF in block comment \"%s\"\n\t at Line %d\n",yytext,yylineno);
  BEGIN INITIAL;
}
<BLOCK_COMMENT>"*/" {BEGIN INITIAL;}
<BLOCK_COMMENT>. ;

{int}        {if(yytext[1]=='x'||yytext[1]=='X'){
                    int i=2,ans=0;
                    while(1){
                        if(yytext[i]>='0'&&yytext[i]<='9'){
                            ans*=16;
                            ans+=yytext[i]-'0';
                            i++;
                        }
                        else if(yytext[i]>='a'&&yytext[i]<='f'){
                            ans*=16;
                            ans+=yytext[i]-'a'+10;
                            i++;
                        }
                        else if(yytext[i]>='A'&&yytext[i]<='F'){
                            ans*=16;
                            ans+=yytext[i]-'A'+10;
                            i++;
                        }
                        else break;
                    }
                    yylval.type_int=ans;
                }
                else yylval.type_int=atoi(yytext); return INT;}
{float}      {yylval.type_float=atof(yytext); return FLOAT;}
{char}		 {yylval.type_char=yytext[1]; return CHAR;}
"string"     {strcpy(yylval.type_id,  yytext);return TYPE;}	
"char" 		 {strcpy(yylval.type_id,  yytext);return TYPE;}	
"int"        {strcpy(yylval.type_id,  yytext);return TYPE;}
"float"      {strcpy(yylval.type_id,  yytext);return TYPE;}
"return"     {return RETURN;}
"if"         {return IF;}
"else"       {return ELSE;}
"while"      {return WHILE;}
"for"        {return FOR;}
"break"      {return BREAK;}
"struct"     {return STRUCT;}
"continue"   {return CONTINUE;}

{id}       {strcpy(yylval.type_id,  yytext); return ID;/*由于关键字的形式也符合标识符的规则，所以把关键字的处理全部放在标识符的前面，优先识别*/}
";"			{return SEMI;}
","			{return COMMA;}
">"|"<"|">="|"<="|"=="|"!=" {strcpy(yylval.type_id, yytext);;return RELOP;}
"="			{return ASSIGNOP;}
"+"			{return PLUS;}
"-"			{return MINUS;}
"*"			{return STAR;}
"/"			{return DIV;}
"++"		{return DPLUS;}
"--"		{return DMINUS;}
"+="		{return ADDASSIGN;}
"-="		{return MINUSASSIGN;}
"*="		{return STARASSIGN;}
"/="		{return DIVASSIGN;}
"&&"        {return AND;}
"||"        {return OR;}
"!"			{return NOT;}
"("			{return LP;}
")"			{return RP;}
"{"			{return LC;}
"}"			{return RC;}
"["         {return LB;}
"]"         {return RB;}
"\."         {return DOT;}
[\n]           {yycolumn=1;}   
[ \r\t]          {}   


\"              {
        BEGIN (String);
        strLen = 0;
        memset(string_buf,0,sizeof(string_buf));
        isNull = 0;
}

<String>\"      {
        BEGIN (INITIAL);
        if(isNull){
          strLen = 0;
          memset(string_buf,0,sizeof(string_buf));
          return 0;  
        }
        string_buf[strLen]='\0';
        strcpy(yylval.type_string,string_buf);
        strLen = 0;
        memset(string_buf,0,sizeof(string_buf));
        return (STR_CONST);
}

<String>(\0|\\\0) {
        printf("Line %d:\\0 in Sting",yylineno);
        isNull = 1;
}

<String><<EOF>>  {
        printf("Line %d:Incomplete string",yylineno);
        BEGIN INITIAL;
        strLen = 0;
        memset(string_buf,0,sizeof(string_buf));
        return 0;
}

<String>\n  {
        yylineno=1;
        printf("Line %d:Incomplete string",yylineno);
        BEGIN INITIAL;
        strLen = 0;
        memset(string_buf,0,sizeof(string_buf));
        return 0;
}

<String>\\\n      {
        yylineno=1;
}

<String>\\.       {
        if(strLen >= 2000){
            printf("Line %d:String length too long",yylineno);
            BEGIN INITIAL;
            strLen = 0;
            memset(string_buf,0,sizeof(string_buf));
            return 0;
        }
        switch (yytext[1]) {
            case '\"' : 
                string_buf[strLen++]  = '\"'  ;
                break;
            case '\\' : 
                string_buf[strLen++]  = '\\'  ;
                break;
            case 'b' : 
                string_buf[strLen++]  = '\b'  ;
                break;
            case '\f' : 
                string_buf[strLen++]  = '\f'  ;
                break;
            case 'n' : 
                string_buf[strLen++]  = '\n'  ;
                break;
            case 't' : 
                string_buf[strLen++]  = '\t'  ;
                break;
            default :
                string_buf[strLen++]  = yytext[1]  ;
        }
}

<String>.         {
        if(strLen >= 2000){
            printf("Line %d:String length too long",yylineno);
            strLen = 0;
            memset(string_buf,0,sizeof(string_buf));
            return 0;
        }
        string_buf[strLen++] = yytext[0]  ;
}

.			{printf("Error type A :Mysterious character \"%s\"\n\t at Line %d\n",yytext,yylineno);}

%%

/* 和bison联用时，不需要这部分
void main()
{
yylex();
return 0;
}

*/
int yywrap()
{
return 1;
}
