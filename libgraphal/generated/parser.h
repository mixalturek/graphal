
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     LEX_ERROR = 258,
     LEX_FUNCTION = 259,
     LEX_RETURN = 260,
     LEX_IF = 261,
     LEX_ELSE = 262,
     LEX_WHILE = 263,
     LEX_FOR = 264,
     LEX_FOREACH = 265,
     LEX_BREAK = 266,
     LEX_CONTINUE = 267,
     LEX_GLOBAL = 268,
     LEX_MOD_ASSIGN = 269,
     LEX_DIV_ASSIGN = 270,
     LEX_MUL_ASSIGN = 271,
     LEX_ADD_ASSIGN = 272,
     LEX_SUB_ASSIGN = 273,
     LEX_INC_OP = 274,
     LEX_DEC_OP = 275,
     LEX_EQ_OP = 276,
     LEX_NE_OP = 277,
     LEX_LE_OP = 278,
     LEX_GE_OP = 279,
     LEX_OR_OP = 280,
     LEX_AND_OP = 281,
     LEX_REF_ASSIGN = 282,
     LEX_NULL = 283,
     LEX_TRUE = 284,
     LEX_FALSE = 285,
     LEX_INT = 286,
     LEX_IDENTIFIER = 287,
     LEX_FLOAT = 288,
     LEX_STRING = 289
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 97 "parser.y"

	int     int_val;
	float   float_val;
	string* string_val;
	Node*   node;
	NodeBlock* nodeblock;
	list<identifier>* list_ids;



/* Line 1676 of yacc.c  */
#line 97 "generated/parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
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

