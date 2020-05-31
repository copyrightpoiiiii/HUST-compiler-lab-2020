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
     EXT_DEF_LIST = 301,
     EXT_VAR_DEF = 302,
     FUNC_DEF = 303,
     FUNC_DEC = 304,
     EXT_DEC_LIST = 305,
     PARAM_LIST = 306,
     STRUCT_DEF = 307,
     PARAM_DEC = 308,
     VAR_DEF = 309,
     DEC_LIST = 310,
     DEF_LIST = 311,
     COMP_STM = 312,
     STM_LIST = 313,
     EXP_STMT = 314,
     IF_THEN = 315,
     IF_THEN_ELSE = 316,
     FUNC_CALL = 317,
     ARGS = 318,
     FUNCTION = 319,
     PARAM = 320,
     ARG = 321,
     ARRAY_CALL = 322,
     STRUCT_CALL = 323,
     VAR_CALL = 324,
     BREAK = 325,
     CONTINUE = 326,
     UMINUS = 327,
     LOWER_THAN_FH = 328,
     LOWER_THEN_ELSE = 329,
     ARRAY_FIRST = 330
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
#define EXT_DEF_LIST 301
#define EXT_VAR_DEF 302
#define FUNC_DEF 303
#define FUNC_DEC 304
#define EXT_DEC_LIST 305
#define PARAM_LIST 306
#define STRUCT_DEF 307
#define PARAM_DEC 308
#define VAR_DEF 309
#define DEC_LIST 310
#define DEF_LIST 311
#define COMP_STM 312
#define STM_LIST 313
#define EXP_STMT 314
#define IF_THEN 315
#define IF_THEN_ELSE 316
#define FUNC_CALL 317
#define ARGS 318
#define FUNCTION 319
#define PARAM 320
#define ARG 321
#define ARRAY_CALL 322
#define STRUCT_CALL 323
#define VAR_CALL 324
#define BREAK 325
#define CONTINUE 326
#define UMINUS 327
#define LOWER_THAN_FH 328
#define LOWER_THEN_ELSE 329
#define ARRAY_FIRST 330




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
#line 208 "parser.tab.h"
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
