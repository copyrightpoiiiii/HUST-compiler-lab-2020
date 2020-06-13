/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     CHAR = 259,
     STR_CONST = 260,
     ID = 261,
     RELOP = 262,
     TYPE = 263,
     ARRAY = 264,
     STRUCT = 265,
     FLOAT = 266,
     LB = 267,
     RB = 268,
     LP = 269,
     RP = 270,
     LC = 271,
     RC = 272,
     SEMI = 273,
     COMMA = 274,
     DPLUS = 275,
     DMINUS = 276,
     ADDASSIGN = 277,
     MINUSASSIGN = 278,
     STARASSIGN = 279,
     DIVASSIGN = 280,
     DOT = 281,
     PLUS = 282,
     MINUS = 283,
     STAR = 284,
     DIV = 285,
     ASSIGNOP = 286,
     AND = 287,
     OR = 288,
     NOT = 289,
     IF = 290,
     ELSE = 291,
     WHILE = 292,
     RETURN = 293,
     FOR = 294,
     SWITCH = 295,
     CASE = 296,
     COLON = 297,
     DEFAULT = 298,
     CALC_LIST = 299,
     FOREXP = 300,
     BOOL = 301,
     EXT_DEF_LIST = 302,
     EXT_VAR_DEF = 303,
     FUNC_DEF = 304,
     FUNC_DEC = 305,
     EXT_DEC_LIST = 306,
     PARAM_LIST = 307,
     STRUCT_DEF = 308,
     PARAM_DEC = 309,
     VAR_DEF = 310,
     DEC_LIST = 311,
     DEF_LIST = 312,
     COMP_STM = 313,
     STM_LIST = 314,
     EXP_STMT = 315,
     IF_THEN = 316,
     IF_THEN_ELSE = 317,
     FUNC_CALL = 318,
     ARGS = 319,
     FUNCTION = 320,
     PARAM = 321,
     ARG = 322,
     ARRAY_CALL = 323,
     STRUCT_CALL = 324,
     VAR_CALL = 325,
     BREAK = 326,
     CONTINUE = 327,
     CALL = 328,
     LABEL = 329,
     GOTO = 330,
     JLT = 331,
     JLE = 332,
     JGT = 333,
     JGE = 334,
     EQ = 335,
     NEQ = 336,
     UMINUS = 337,
     LOWER_THAN_FH = 338,
     LOWER_THEN_ELSE = 339,
     ARRAY_FIRST = 340
   };
#endif
/* Tokens.  */
#define INT 258
#define CHAR 259
#define STR_CONST 260
#define ID 261
#define RELOP 262
#define TYPE 263
#define ARRAY 264
#define STRUCT 265
#define FLOAT 266
#define LB 267
#define RB 268
#define LP 269
#define RP 270
#define LC 271
#define RC 272
#define SEMI 273
#define COMMA 274
#define DPLUS 275
#define DMINUS 276
#define ADDASSIGN 277
#define MINUSASSIGN 278
#define STARASSIGN 279
#define DIVASSIGN 280
#define DOT 281
#define PLUS 282
#define MINUS 283
#define STAR 284
#define DIV 285
#define ASSIGNOP 286
#define AND 287
#define OR 288
#define NOT 289
#define IF 290
#define ELSE 291
#define WHILE 292
#define RETURN 293
#define FOR 294
#define SWITCH 295
#define CASE 296
#define COLON 297
#define DEFAULT 298
#define CALC_LIST 299
#define FOREXP 300
#define BOOL 301
#define EXT_DEF_LIST 302
#define EXT_VAR_DEF 303
#define FUNC_DEF 304
#define FUNC_DEC 305
#define EXT_DEC_LIST 306
#define PARAM_LIST 307
#define STRUCT_DEF 308
#define PARAM_DEC 309
#define VAR_DEF 310
#define DEC_LIST 311
#define DEF_LIST 312
#define COMP_STM 313
#define STM_LIST 314
#define EXP_STMT 315
#define IF_THEN 316
#define IF_THEN_ELSE 317
#define FUNC_CALL 318
#define ARGS 319
#define FUNCTION 320
#define PARAM 321
#define ARG 322
#define ARRAY_CALL 323
#define STRUCT_CALL 324
#define VAR_CALL 325
#define BREAK 326
#define CONTINUE 327
#define CALL 328
#define LABEL 329
#define GOTO 330
#define JLT 331
#define JLE 332
#define JGT 333
#define JGE 334
#define EQ 335
#define NEQ 336
#define UMINUS 337
#define LOWER_THAN_FH 338
#define LOWER_THEN_ELSE 339
#define ARRAY_FIRST 340




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 15 "parser.y"
{
	int    type_int;
	float  type_float;
    char   type_char;
    char   type_string[2010];
	char   type_id[32];
	struct ASTNode *ptr;
}
/* Line 1529 of yacc.c.  */
#line 228 "parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;
