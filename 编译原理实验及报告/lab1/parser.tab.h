/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CHAR = 258,
    INT = 259,
    ID = 260,
    STRING = 261,
    RELOP = 262,
    TYPE = 263,
    FLOAT = 264,
    STRUCT = 265,
    RETURN = 266,
    FOR = 267,
    SWITCH = 268,
    CASE = 269,
    COLON = 270,
    DEFAULT = 271,
    STRUCT_VISIT = 272,
    STRUCT_NEW = 273,
    STRUCT_DEC = 274,
    EXT_STRUCT_DEC = 275,
    CASE_STMT = 276,
    CASE_STMT_LIST = 277,
    DEFAULT_STMT = 278,
    FOR_DEC = 279,
    FOR_EXP1 = 280,
    FOR_EXP2 = 281,
    FOR_EXP3 = 282,
    DPLUS = 283,
    LP = 284,
    RP = 285,
    LC = 286,
    RC = 287,
    LB = 288,
    RB = 289,
    SEMI = 290,
    COMMA = 291,
    DOT = 292,
    PLUS = 293,
    MINUS = 294,
    STAR = 295,
    DIV = 296,
    MOD = 297,
    ASSIGNOP_MOD = 298,
    ASSIGNOP = 299,
    ASSIGNOP_MINUS = 300,
    ASSIGNOP_PLUS = 301,
    ASSIGNOP_DIV = 302,
    ASSIGNOP_STAR = 303,
    AND = 304,
    OR = 305,
    NOT = 306,
    AUTOPLUS = 307,
    AUTOMINUS = 308,
    IF = 309,
    ELSE = 310,
    WHILE = 311,
    BREAK = 312,
    CONTINUE = 313,
    EXT_DEF_LIST = 314,
    EXT_VAR_DEF = 315,
    FUNC_DEF = 316,
    FUNC_DEC = 317,
    EXT_DEC_LIST = 318,
    PARAM_LIST = 319,
    PARAM_DEC = 320,
    VAR_DEF = 321,
    DEC_LIST = 322,
    DEF_LIST = 323,
    COMP_STM = 324,
    STM_LIST = 325,
    EXP_STMT = 326,
    IF_THEN = 327,
    IF_THEN_ELSE = 328,
    FUNC_CALL = 329,
    ARGS = 330,
    FUNCTION = 331,
    PARAM = 332,
    ARG = 333,
    ARRAY_LIST = 334,
    UMINUS = 335,
    DMINUS = 336,
    LOWER_THEN_ELSE = 337
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 19 "parser.y" /* yacc.c:1909  */

	int    type_int;
    char   type_char;
	float  type_float;
	char   type_id[32];
	struct node *ptr;

#line 145 "parser.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
