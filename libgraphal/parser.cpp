
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parser.y"

/*
 *      Copyright 2009 Michal Turek <http://woq.nipax.cz/>
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

/* bison -v -d -o parser.cpp parser.y */

#include <cassert>
#include "general.h"
#include "lexan.h"
#include "context.h"

#include "node.h"
#include "nodebinaryadd.h"
#include "nodebinaryand.h"
#include "nodebinaryass.h"
#include "nodebinaryassadd.h"
#include "nodebinaryasssub.h"
#include "nodebinaryassmult.h"
#include "nodebinaryassdiv.h"
#include "nodebinaryassmod.h"
#include "nodebinaryassref.h"
#include "nodebinarydiv.h"
#include "nodebinaryeq.h"
#include "nodebinaryge.h"
#include "nodebinarygt.h"
#include "nodebinaryle.h"
#include "nodebinarylt.h"
#include "nodebinarymod.h"
#include "nodebinarymult.h"
#include "nodebinaryne.h"
#include "nodebinaryor.h"
#include "nodebinarysub.h"
#include "nodebinaryindex.h"
#include "nodebinarymember.h"
#include "nodeblock.h"
#include "nodecondition.h"
#include "nodeemptycommand.h"
#include "nodefunctioncall.h"
#include "nodefunctionscript.h"
#include "nodeloop.h"
#include "nodeforeach.h"
#include "nodeunarynot.h"
#include "nodeunaryreturn.h"
#include "nodeunarysub.h"
#include "nodeunaryincpre.h"
#include "nodeunaryincpost.h"
#include "nodeunarydecpre.h"
#include "nodeunarydecpost.h"
#include "nodevalue.h"
#include "nodejumpbreak.h"
#include "nodejumpcontinue.h"
#include "nodeglobal.h"

#include "valuebool.h"
#include "valueedge.h"
#include "valuefloat.h"
#include "valuegraph.h"
#include "valueint.h"
#include "valuenull.h"
#include "valuestring.h"
#include "valuestruct.h"
#include "valuevertex.h"
#include "valueidentifier.h"

#include "logger.h"
#include "codeposition.h"
#include "nodeposition.h"

#define FILE last_column
#define LINE last_line

// Ja su ale prasatko :-)
static Lexan* g_lexan = NULL;

int yylex(void);
void yyerror(char const *msg);


/* Line 189 of yacc.c  */
#line 168 "parser.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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

/* Line 214 of yacc.c  */
#line 96 "parser.y"

	int     int_val;
	float   float_val;
	string* string_val;
	Node*   node;
	NodeBlock* nodeblock;
	list<identifier>* list_ids;



/* Line 214 of yacc.c  */
#line 249 "parser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

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


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 274 "parser.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   377

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  82
/* YYNRULES -- Number of states.  */
#define YYNSTATES  160

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   289

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    43,     2,     2,     2,    46,     2,     2,
      35,    36,    44,    41,    40,    42,    39,    45,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    50,    52,
      47,    51,    48,    49,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    37,     2,    38,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    53,     2,    54,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    13,    15,    17,
      21,    23,    28,    32,    37,    41,    47,    54,    57,    60,
      62,    66,    68,    71,    74,    77,    80,    83,    85,    89,
      93,    97,    99,   103,   107,   109,   113,   117,   121,   125,
     127,   131,   135,   137,   141,   143,   147,   149,   155,   157,
     161,   165,   169,   173,   177,   181,   185,   187,   189,   191,
     197,   205,   211,   218,   226,   234,   237,   240,   243,   247,
     251,   253,   256,   259,   263,   265,   268,   274,   279,   282,
     284,   288,   289
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      76,     0,    -1,    28,    -1,    29,    -1,    30,    -1,    31,
      -1,    32,    -1,    33,    -1,    34,    -1,    35,    68,    36,
      -1,    56,    -1,    57,    37,    68,    38,    -1,    32,    35,
      36,    -1,    32,    35,    58,    36,    -1,    57,    39,    32,
      -1,    57,    39,    32,    35,    36,    -1,    57,    39,    32,
      35,    58,    36,    -1,    57,    19,    -1,    57,    20,    -1,
      67,    -1,    58,    40,    67,    -1,    57,    -1,    19,    59,
      -1,    20,    59,    -1,    41,    59,    -1,    42,    59,    -1,
      43,    59,    -1,    59,    -1,    60,    44,    59,    -1,    60,
      45,    59,    -1,    60,    46,    59,    -1,    60,    -1,    61,
      41,    60,    -1,    61,    42,    60,    -1,    61,    -1,    62,
      47,    61,    -1,    62,    48,    61,    -1,    62,    23,    61,
      -1,    62,    24,    61,    -1,    62,    -1,    63,    21,    62,
      -1,    63,    22,    62,    -1,    63,    -1,    64,    26,    63,
      -1,    64,    -1,    65,    25,    64,    -1,    65,    -1,    65,
      49,    68,    50,    66,    -1,    66,    -1,    59,    51,    67,
      -1,    59,    16,    67,    -1,    59,    15,    67,    -1,    59,
      14,    67,    -1,    59,    17,    67,    -1,    59,    18,    67,
      -1,    59,    27,    67,    -1,    67,    -1,    71,    -1,    70,
      -1,     6,    35,    68,    36,    69,    -1,     6,    35,    68,
      36,    69,     7,    69,    -1,     8,    35,    68,    36,    69,
      -1,     9,    35,    70,    70,    36,    69,    -1,     9,    35,
      70,    70,    68,    36,    69,    -1,    10,    35,    32,    52,
      68,    36,    69,    -1,    11,    52,    -1,    12,    52,    -1,
       5,    52,    -1,     5,    68,    52,    -1,    13,    32,    52,
      -1,    52,    -1,    68,    52,    -1,    53,    54,    -1,    53,
      72,    54,    -1,    69,    -1,    72,    69,    -1,    74,    35,
      75,    36,    71,    -1,    74,    35,    36,    71,    -1,     4,
      32,    -1,    32,    -1,    75,    40,    32,    -1,    -1,    76,
      73,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   164,   164,   165,   166,   167,   168,   169,   170,   171,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   187,
     188,   192,   193,   194,   195,   196,   197,   201,   202,   203,
     204,   208,   209,   210,   214,   215,   216,   217,   218,   222,
     223,   224,   228,   229,   233,   234,   238,   239,   243,   244,
     245,   246,   247,   248,   249,   250,   254,   258,   259,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     275,   276,   280,   281,   285,   286,   290,   291,   295,   299,
     300,   303,   305
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LEX_ERROR", "LEX_FUNCTION",
  "LEX_RETURN", "LEX_IF", "LEX_ELSE", "LEX_WHILE", "LEX_FOR",
  "LEX_FOREACH", "LEX_BREAK", "LEX_CONTINUE", "LEX_GLOBAL",
  "LEX_MOD_ASSIGN", "LEX_DIV_ASSIGN", "LEX_MUL_ASSIGN", "LEX_ADD_ASSIGN",
  "LEX_SUB_ASSIGN", "LEX_INC_OP", "LEX_DEC_OP", "LEX_EQ_OP", "LEX_NE_OP",
  "LEX_LE_OP", "LEX_GE_OP", "LEX_OR_OP", "LEX_AND_OP", "LEX_REF_ASSIGN",
  "LEX_NULL", "LEX_TRUE", "LEX_FALSE", "LEX_INT", "LEX_IDENTIFIER",
  "LEX_FLOAT", "LEX_STRING", "'('", "')'", "'['", "']'", "'.'", "','",
  "'+'", "'-'", "'!'", "'*'", "'/'", "'%'", "'<'", "'>'", "'?'", "':'",
  "'='", "';'", "'{'", "'}'", "$accept", "primary_expression",
  "postfix_expression", "argument_expression_list", "unary_expression",
  "multiplicative_expression", "additive_expression",
  "relational_expression", "equality_expression", "logical_and_expression",
  "logical_or_expression", "conditional_expression",
  "assignment_expression", "expression", "statement",
  "expression_statement", "compound_statement", "block_item_list",
  "function_definition", "function_and_name", "parameter_list", "start", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,    40,    41,    91,    93,    46,
      44,    43,    45,    33,    42,    47,    37,    60,    62,    63,
      58,    61,    59,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    55,    56,    56,    56,    56,    56,    56,    56,    56,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    58,
      58,    59,    59,    59,    59,    59,    59,    60,    60,    60,
      60,    61,    61,    61,    62,    62,    62,    62,    62,    63,
      63,    63,    64,    64,    65,    65,    66,    66,    67,    67,
      67,    67,    67,    67,    67,    67,    68,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      70,    70,    71,    71,    72,    72,    73,    73,    74,    75,
      75,    76,    76
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     4,     3,     4,     3,     5,     6,     2,     2,     1,
       3,     1,     2,     2,     2,     2,     2,     1,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     1,     3,     1,     5,     1,     3,
       3,     3,     3,     3,     3,     3,     1,     1,     1,     5,
       7,     5,     6,     7,     7,     2,     2,     2,     3,     3,
       1,     2,     2,     3,     1,     2,     5,     4,     2,     1,
       3,     0,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      81,     0,     1,     0,    82,     0,    78,     0,    79,     0,
       0,     0,    77,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     2,     3,     4,     5,     6,
       7,     8,     0,     0,     0,     0,    70,    72,    10,    21,
      27,    31,    34,    39,    42,    44,    46,    48,    56,     0,
      74,    58,    57,     0,    76,    80,    67,     0,     0,     0,
       0,     0,    65,    66,     0,    22,    23,     0,     0,    24,
      25,    26,    17,    18,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    71,    73,    75,
      68,     0,     0,     0,     0,    69,    12,     0,    19,     9,
       0,    14,    52,    51,    50,    53,    54,    55,    49,    28,
      29,    30,    27,    32,    33,    37,    38,    35,    36,    40,
      41,    43,    45,     0,     0,     0,     0,     0,    13,     0,
      11,     0,     0,    59,    61,     0,     0,     0,    20,    15,
       0,    47,     0,    62,     0,     0,    16,    60,    63,    64
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    38,    39,   107,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,     4,     5,
      10,     1
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -68
static const yytype_int16 yypact[] =
{
     -68,    32,   -68,   -10,   -68,   -25,   -68,     1,   -68,   -18,
      -2,   104,   -68,   -18,     9,   230,    19,    25,    52,    56,
      -6,    40,    62,   334,   334,   -68,   -68,   -68,   -68,    58,
     -68,   -68,   334,   334,   334,   334,   -68,   -68,   -68,    11,
      -9,    34,    16,    -8,    61,    70,    -4,   -68,   -68,    45,
     -68,   -68,   -68,   154,   -68,   -68,   -68,    46,   334,   334,
     255,    67,   -68,   -68,    48,   -68,   -68,   280,    65,   -68,
     -68,   -68,   -68,   -68,   334,    71,   334,   334,   334,   334,
     334,   334,   334,   334,   334,   334,   334,   334,   334,   334,
     334,   334,   334,   334,   334,   334,   334,   -68,   -68,   -68,
     -68,    72,    75,   255,    54,   -68,   -68,    13,   -68,   -68,
      69,    83,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,
     -68,   -68,   -68,    34,    34,    16,    16,    16,    16,    -8,
      -8,    61,    70,    76,   204,   204,   298,   334,   -68,   334,
     -68,   316,   334,   112,   -68,   204,    89,    91,   -68,   -68,
      15,   -68,   204,   -68,   204,   204,   -68,   -68,   -68,   -68
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -68,   -68,   -68,   -13,   -22,   -67,   -14,    -3,    35,    36,
     -68,   -12,   -53,   -15,   -50,   -56,    43,   -68,   -68,   -68,
     -68,   -68
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      57,    65,    66,    99,   103,    76,    77,    78,    79,    80,
       7,    69,    70,    71,   108,    88,    89,    68,    81,   123,
     124,    95,     6,   112,   113,   114,   115,   116,   117,   118,
      72,    73,     2,     8,    13,    11,     3,     9,    14,    90,
      91,    55,    82,   101,   102,    96,    62,   136,    74,   138,
      75,   156,    12,   139,    58,   139,    54,    86,    87,   110,
      59,   119,   120,   121,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   125,   126,   127,   128,    83,    84,
      85,   133,    92,    93,   143,   144,   148,    60,   108,   129,
     130,    61,    63,    67,    64,   153,    94,    97,   100,   104,
     105,   109,   157,   111,   158,   159,   137,   140,   134,    15,
      16,   135,    17,    18,    19,    20,    21,    22,   141,   152,
     122,   146,   147,    23,    24,   154,   142,   155,   150,   131,
     151,   132,    25,    26,    27,    28,    29,    30,    31,    32,
       0,     0,     0,     0,     0,    33,    34,    35,     0,     0,
       0,     0,     0,     0,     0,     0,    36,    11,    37,    15,
      16,     0,    17,    18,    19,    20,    21,    22,     0,     0,
       0,     0,     0,    23,    24,     0,     0,     0,     0,     0,
       0,     0,    25,    26,    27,    28,    29,    30,    31,    32,
       0,     0,     0,     0,     0,    33,    34,    35,     0,     0,
       0,     0,     0,     0,     0,     0,    36,    11,    98,    15,
      16,     0,    17,    18,    19,    20,    21,    22,     0,     0,
       0,     0,     0,    23,    24,     0,     0,     0,     0,     0,
       0,     0,    25,    26,    27,    28,    29,    30,    31,    32,
       0,     0,     0,     0,     0,    33,    34,    35,     0,    23,
      24,     0,     0,     0,     0,     0,    36,    11,    25,    26,
      27,    28,    29,    30,    31,    32,     0,     0,     0,     0,
       0,    33,    34,    35,    23,    24,     0,     0,     0,     0,
       0,     0,    56,    25,    26,    27,    28,    29,    30,    31,
      32,     0,     0,     0,     0,     0,    33,    34,    35,    23,
      24,     0,     0,     0,     0,     0,     0,    36,    25,    26,
      27,    28,    29,    30,    31,    32,   106,    23,    24,     0,
       0,    33,    34,    35,     0,     0,    25,    26,    27,    28,
      29,    30,    31,    32,   145,    23,    24,     0,     0,    33,
      34,    35,     0,     0,    25,    26,    27,    28,    29,    30,
      31,    32,   149,    23,    24,     0,     0,    33,    34,    35,
       0,     0,    25,    26,    27,    28,    29,    30,    31,    32,
       0,     0,     0,     0,     0,    33,    34,    35
};

static const yytype_int16 yycheck[] =
{
      15,    23,    24,    53,    60,    14,    15,    16,    17,    18,
      35,    33,    34,    35,    67,    23,    24,    32,    27,    86,
      87,    25,    32,    76,    77,    78,    79,    80,    81,    82,
      19,    20,     0,    32,    36,    53,     4,    36,    40,    47,
      48,    32,    51,    58,    59,    49,    52,   103,    37,    36,
      39,    36,     9,    40,    35,    40,    13,    41,    42,    74,
      35,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    88,    89,    90,    91,    44,    45,
      46,    96,    21,    22,   134,   135,   139,    35,   141,    92,
      93,    35,    52,    35,    32,   145,    26,    52,    52,    32,
      52,    36,   152,    32,   154,   155,    52,    38,    36,     5,
       6,    36,     8,     9,    10,    11,    12,    13,    35,     7,
     142,   136,   137,    19,    20,    36,    50,    36,   141,    94,
     142,    95,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    52,    53,    54,     5,
       6,    -1,     8,     9,    10,    11,    12,    13,    -1,    -1,
      -1,    -1,    -1,    19,    20,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    52,    53,    54,     5,
       6,    -1,     8,     9,    10,    11,    12,    13,    -1,    -1,
      -1,    -1,    -1,    19,    20,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    41,    42,    43,    -1,    19,
      20,    -1,    -1,    -1,    -1,    -1,    52,    53,    28,    29,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      -1,    41,    42,    43,    19,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    52,    28,    29,    30,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    -1,    -1,    41,    42,    43,    19,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    52,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    19,    20,    -1,
      -1,    41,    42,    43,    -1,    -1,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    19,    20,    -1,    -1,    41,
      42,    43,    -1,    -1,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    19,    20,    -1,    -1,    41,    42,    43,
      -1,    -1,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    41,    42,    43
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    76,     0,     4,    73,    74,    32,    35,    32,    36,
      75,    53,    71,    36,    40,     5,     6,     8,     9,    10,
      11,    12,    13,    19,    20,    28,    29,    30,    31,    32,
      33,    34,    35,    41,    42,    43,    52,    54,    56,    57,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    71,    32,    52,    68,    35,    35,
      35,    35,    52,    52,    32,    59,    59,    35,    68,    59,
      59,    59,    19,    20,    37,    39,    14,    15,    16,    17,
      18,    27,    51,    44,    45,    46,    41,    42,    23,    24,
      47,    48,    21,    22,    26,    25,    49,    52,    54,    69,
      52,    68,    68,    70,    32,    52,    36,    58,    67,    36,
      68,    32,    67,    67,    67,    67,    67,    67,    67,    59,
      59,    59,    59,    60,    60,    61,    61,    61,    61,    62,
      62,    63,    64,    68,    36,    36,    70,    52,    36,    40,
      38,    35,    50,    69,    69,    36,    68,    68,    67,    36,
      58,    66,     7,    69,    36,    36,    36,    69,    69,    69
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {
      case 56: /* "primary_expression" */

/* Line 1000 of yacc.c  */
#line 140 "parser.y"
	{ delete ((yyvaluep->node)); };

/* Line 1000 of yacc.c  */
#line 1372 "parser.cpp"
	break;
      case 57: /* "postfix_expression" */

/* Line 1000 of yacc.c  */
#line 140 "parser.y"
	{ delete ((yyvaluep->node)); };

/* Line 1000 of yacc.c  */
#line 1381 "parser.cpp"
	break;
      case 58: /* "argument_expression_list" */

/* Line 1000 of yacc.c  */
#line 145 "parser.y"
	{ delete ((yyvaluep->nodeblock)); };

/* Line 1000 of yacc.c  */
#line 1390 "parser.cpp"
	break;
      case 59: /* "unary_expression" */

/* Line 1000 of yacc.c  */
#line 140 "parser.y"
	{ delete ((yyvaluep->node)); };

/* Line 1000 of yacc.c  */
#line 1399 "parser.cpp"
	break;
      case 60: /* "multiplicative_expression" */

/* Line 1000 of yacc.c  */
#line 141 "parser.y"
	{ delete ((yyvaluep->node)); };

/* Line 1000 of yacc.c  */
#line 1408 "parser.cpp"
	break;
      case 61: /* "additive_expression" */

/* Line 1000 of yacc.c  */
#line 141 "parser.y"
	{ delete ((yyvaluep->node)); };

/* Line 1000 of yacc.c  */
#line 1417 "parser.cpp"
	break;
      case 62: /* "relational_expression" */

/* Line 1000 of yacc.c  */
#line 142 "parser.y"
	{ delete ((yyvaluep->node)); };

/* Line 1000 of yacc.c  */
#line 1426 "parser.cpp"
	break;
      case 63: /* "equality_expression" */

/* Line 1000 of yacc.c  */
#line 142 "parser.y"
	{ delete ((yyvaluep->node)); };

/* Line 1000 of yacc.c  */
#line 1435 "parser.cpp"
	break;
      case 64: /* "logical_and_expression" */

/* Line 1000 of yacc.c  */
#line 142 "parser.y"
	{ delete ((yyvaluep->node)); };

/* Line 1000 of yacc.c  */
#line 1444 "parser.cpp"
	break;
      case 65: /* "logical_or_expression" */

/* Line 1000 of yacc.c  */
#line 143 "parser.y"
	{ delete ((yyvaluep->node)); };

/* Line 1000 of yacc.c  */
#line 1453 "parser.cpp"
	break;
      case 66: /* "conditional_expression" */

/* Line 1000 of yacc.c  */
#line 143 "parser.y"
	{ delete ((yyvaluep->node)); };

/* Line 1000 of yacc.c  */
#line 1462 "parser.cpp"
	break;
      case 67: /* "assignment_expression" */

/* Line 1000 of yacc.c  */
#line 143 "parser.y"
	{ delete ((yyvaluep->node)); };

/* Line 1000 of yacc.c  */
#line 1471 "parser.cpp"
	break;
      case 68: /* "expression" */

/* Line 1000 of yacc.c  */
#line 141 "parser.y"
	{ delete ((yyvaluep->node)); };

/* Line 1000 of yacc.c  */
#line 1480 "parser.cpp"
	break;
      case 69: /* "statement" */

/* Line 1000 of yacc.c  */
#line 144 "parser.y"
	{ delete ((yyvaluep->node)); };

/* Line 1000 of yacc.c  */
#line 1489 "parser.cpp"
	break;
      case 70: /* "expression_statement" */

/* Line 1000 of yacc.c  */
#line 144 "parser.y"
	{ delete ((yyvaluep->node)); };

/* Line 1000 of yacc.c  */
#line 1498 "parser.cpp"
	break;
      case 71: /* "compound_statement" */

/* Line 1000 of yacc.c  */
#line 144 "parser.y"
	{ delete ((yyvaluep->node)); };

/* Line 1000 of yacc.c  */
#line 1507 "parser.cpp"
	break;
      case 72: /* "block_item_list" */

/* Line 1000 of yacc.c  */
#line 145 "parser.y"
	{ delete ((yyvaluep->nodeblock)); };

/* Line 1000 of yacc.c  */
#line 1516 "parser.cpp"
	break;
      case 75: /* "parameter_list" */

/* Line 1000 of yacc.c  */
#line 146 "parser.y"
	{ delete ((yyvaluep->list_ids)); };

/* Line 1000 of yacc.c  */
#line 1525 "parser.cpp"
	break;

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[2];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 164 "parser.y"
    { (yyval.node) = new NodeValue(VALUENULL); ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 165 "parser.y"
    { (yyval.node) = new NodeValue(VALUEBOOL_TRUE); ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 166 "parser.y"
    { (yyval.node) = new NodeValue(VALUEBOOL_FALSE); ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 167 "parser.y"
    { (yyval.node) = new NodeValue(new ValueInt((yyvsp[(1) - (1)].int_val))); ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 168 "parser.y"
    { (yyval.node) = new NodeValue(new ValueIdentifier((yyvsp[(1) - (1)].int_val))); ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 169 "parser.y"
    { (yyval.node) = new NodeValue(new ValueFloat((yyvsp[(1) - (1)].float_val))); ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 170 "parser.y"
    { (yyval.node) = new NodeValue(new ValueString(*(yyvsp[(1) - (1)].string_val))); ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 171 "parser.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 175 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 176 "parser.y"
    { (yyval.node) = new NodeBinaryIndex((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node)); ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 177 "parser.y"
    { (yyval.node) = new NodeFunctionCall((yyvsp[(1) - (3)].int_val), new NodeBlock, new CodePosition((yylsp[(1) - (3)]).FILE, (yylsp[(1) - (3)]).LINE)); ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 178 "parser.y"
    { (yyval.node) = new NodeFunctionCall((yyvsp[(1) - (4)].int_val), (yyvsp[(3) - (4)].nodeblock), new CodePosition((yylsp[(1) - (4)]).FILE, (yylsp[(1) - (4)]).LINE)); ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 179 "parser.y"
    { (yyval.node) = new NodeBinaryMember((yyvsp[(1) - (3)].node), new NodeValue(new ValueIdentifier((yyvsp[(3) - (3)].int_val)))); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 180 "parser.y"
    { (yyval.node) = new NodeFunctionCall((yyvsp[(3) - (5)].int_val), new NodeBlock((yyvsp[(1) - (5)].node)), new CodePosition((yylsp[(3) - (5)]).FILE, (yylsp[(3) - (5)]).LINE)); ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 181 "parser.y"
    { (yyvsp[(5) - (6)].nodeblock)->pushCommandToFront((yyvsp[(1) - (6)].node)); (yyval.node) = new NodeFunctionCall((yyvsp[(3) - (6)].int_val), (yyvsp[(5) - (6)].nodeblock), new CodePosition((yylsp[(3) - (6)]).FILE, (yylsp[(3) - (6)]).LINE)); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 182 "parser.y"
    { (yyval.node) = new NodeUnaryIncPost((yyvsp[(1) - (2)].node)); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 183 "parser.y"
    { (yyval.node) = new NodeUnaryDecPost((yyvsp[(1) - (2)].node)); ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 187 "parser.y"
    { (yyval.nodeblock) = new NodeBlock((yyvsp[(1) - (1)].node)); ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 188 "parser.y"
    { (yyvsp[(1) - (3)].nodeblock)->pushCommandToBack((yyvsp[(3) - (3)].node)); (yyval.nodeblock) = (yyvsp[(1) - (3)].nodeblock); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 192 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 193 "parser.y"
    { (yyval.node) = new NodeUnaryIncPre((yyvsp[(2) - (2)].node)); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 194 "parser.y"
    { (yyval.node) = new NodeUnaryDecPre((yyvsp[(2) - (2)].node)); ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 195 "parser.y"
    { (yyval.node) = (yyvsp[(2) - (2)].node); ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 196 "parser.y"
    { (yyval.node) = new NodeUnarySub((yyvsp[(2) - (2)].node)); ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 197 "parser.y"
    { (yyval.node) = new NodeUnaryNot((yyvsp[(2) - (2)].node)); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 201 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 202 "parser.y"
    { (yyval.node) = new NodeBinaryMult((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 203 "parser.y"
    { (yyval.node) = new NodeBinaryDiv((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 204 "parser.y"
    { (yyval.node) = new NodeBinaryMod((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 208 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 209 "parser.y"
    { (yyval.node) = new NodeBinaryAdd((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 210 "parser.y"
    { (yyval.node) = new NodeBinarySub((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 214 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 215 "parser.y"
    { (yyval.node) = new NodeBinaryLt((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 216 "parser.y"
    { (yyval.node) = new NodeBinaryGt((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 217 "parser.y"
    { (yyval.node) = new NodeBinaryLe((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 218 "parser.y"
    { (yyval.node) = new NodeBinaryGe((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 222 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 223 "parser.y"
    { (yyval.node) = new NodeBinaryEq((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 224 "parser.y"
    { (yyval.node) = new NodeBinaryNe((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 228 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 229 "parser.y"
    { (yyval.node) = new NodeBinaryAnd((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 233 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 234 "parser.y"
    { (yyval.node) = new NodeBinaryOr((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 238 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 239 "parser.y"
    { (yyval.node) = new NodeCondition((yyvsp[(1) - (5)].node), (yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node)); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 243 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 244 "parser.y"
    { (yyval.node) = new NodeBinaryAss((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 245 "parser.y"
    { (yyval.node) = new NodeBinaryAssMult((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 246 "parser.y"
    { (yyval.node) = new NodeBinaryAssDiv((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 247 "parser.y"
    { (yyval.node) = new NodeBinaryAssMod((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 248 "parser.y"
    { (yyval.node) = new NodeBinaryAssAdd((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 249 "parser.y"
    { (yyval.node) = new NodeBinaryAssSub((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 250 "parser.y"
    { (yyval.node) = new NodeBinaryAssRef((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 254 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 258 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 259 "parser.y"
    { (yyval.node) = new NodePosition((yyvsp[(1) - (1)].node), new CodePosition((yylsp[(1) - (1)]).FILE, (yylsp[(1) - (1)]).LINE)); ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 261 "parser.y"
    { (yyval.node) = new NodeCondition(new NodePosition((yyvsp[(3) - (5)].node), new CodePosition((yylsp[(3) - (5)]).FILE, (yylsp[(3) - (5)]).LINE)), (yyvsp[(5) - (5)].node), new NodeEmptyCommand); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 262 "parser.y"
    { (yyval.node) = new NodeCondition(new NodePosition((yyvsp[(3) - (7)].node), new CodePosition((yylsp[(3) - (7)]).FILE, (yylsp[(3) - (7)]).LINE)), (yyvsp[(5) - (7)].node), (yyvsp[(7) - (7)].node)); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 263 "parser.y"
    { (yyval.node) = new NodeLoop(new NodeEmptyCommand, new NodePosition((yyvsp[(3) - (5)].node), new CodePosition((yylsp[(3) - (5)]).FILE, (yylsp[(3) - (5)]).LINE)), new NodeEmptyCommand, (yyvsp[(5) - (5)].node)); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 264 "parser.y"
    { (yyval.node) = new NodeLoop((yyvsp[(3) - (6)].node), new NodePosition((yyvsp[(4) - (6)].node), new CodePosition((yylsp[(4) - (6)]).FILE, (yylsp[(4) - (6)]).LINE)), new NodeEmptyCommand, (yyvsp[(6) - (6)].node)); ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 265 "parser.y"
    { (yyval.node) = new NodeLoop((yyvsp[(3) - (7)].node), new NodePosition((yyvsp[(4) - (7)].node), new CodePosition((yylsp[(4) - (7)]).FILE, (yylsp[(4) - (7)]).LINE)), (yyvsp[(5) - (7)].node), (yyvsp[(7) - (7)].node)); ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 266 "parser.y"
    { (yyval.node) = new NodeForeach((yyvsp[(3) - (7)].int_val), new NodePosition((yyvsp[(5) - (7)].node), new CodePosition((yylsp[(5) - (7)]).FILE, (yylsp[(5) - (7)]).LINE)), (yyvsp[(7) - (7)].node)); ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 267 "parser.y"
    { (yyval.node) = new NodePosition(new NodeJumpBreak, new CodePosition((yylsp[(2) - (2)]).FILE, (yylsp[(2) - (2)]).LINE)); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 268 "parser.y"
    { (yyval.node) = new NodePosition(new NodeJumpContinue, new CodePosition((yylsp[(2) - (2)]).FILE, (yylsp[(2) - (2)]).LINE)); ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 269 "parser.y"
    { (yyval.node) = new NodePosition(new NodeUnaryReturn(new NodeEmptyCommand), new CodePosition((yylsp[(2) - (2)]).FILE, (yylsp[(2) - (2)]).LINE)); ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 270 "parser.y"
    { (yyval.node) = new NodePosition(new NodeUnaryReturn((yyvsp[(2) - (3)].node)), new CodePosition((yylsp[(3) - (3)]).FILE, (yylsp[(3) - (3)]).LINE)); ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 271 "parser.y"
    { (yyval.node) = new NodePosition(new NodeGlobal((yyvsp[(2) - (3)].int_val)), new CodePosition((yylsp[(3) - (3)]).FILE, (yylsp[(3) - (3)]).LINE)); ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 275 "parser.y"
    { (yyval.node) = new NodeEmptyCommand; ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 276 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 280 "parser.y"
    { (yyval.node) = new NodeEmptyCommand; ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 281 "parser.y"
    { (yyval.node) = (yyvsp[(2) - (3)].nodeblock); ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 285 "parser.y"
    { (yyval.nodeblock) = new NodeBlock((yyvsp[(1) - (1)].node)); ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 286 "parser.y"
    { (yyvsp[(1) - (2)].nodeblock)->pushCommandToBack((yyvsp[(2) - (2)].node)); (yyval.nodeblock) = (yyvsp[(1) - (2)].nodeblock); ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 290 "parser.y"
    { CONTEXT.addFunction(new NodeFunctionScript((yyvsp[(1) - (5)].int_val), (yyvsp[(3) - (5)].list_ids), (yyvsp[(5) - (5)].node), new CodePosition((yylsp[(1) - (5)]).FILE, (yylsp[(1) - (5)]).LINE))); ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 291 "parser.y"
    { CONTEXT.addFunction(new NodeFunctionScript((yyvsp[(1) - (4)].int_val), new list<identifier>, (yyvsp[(4) - (4)].node), new CodePosition((yylsp[(1) - (4)]).FILE, (yylsp[(1) - (4)]).LINE))); ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 295 "parser.y"
    { g_lexan->setCurrentlyProcessedFunction((yyvsp[(2) - (2)].int_val)); (yyval.int_val) = (yyvsp[(2) - (2)].int_val); ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 299 "parser.y"
    { (yyval.list_ids) = new list<identifier>; (yyval.list_ids)->push_back((yyvsp[(1) - (1)].int_val)); ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 300 "parser.y"
    { (yyvsp[(1) - (3)].list_ids)->push_back((yyvsp[(3) - (3)].int_val)); (yyval.list_ids) = (yyvsp[(1) - (3)].list_ids); ;}
    break;



/* Line 1455 of yacc.c  */
#line 2410 "parser.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 307 "parser.y"


int yylex(void)
{
	assert(g_lexan != NULL);
	int tok = g_lexan->nextToken();

	yylloc.FILE = g_lexan->getFile();
	yylloc.LINE = g_lexan->getLine();

	switch(tok)
	{
	case LEX_INT:
		yylval.int_val = g_lexan->getInt();
		break;
	case LEX_IDENTIFIER:
		yylval.int_val = g_lexan->getIdentifier();
		break;
	case LEX_FLOAT:
		yylval.float_val = g_lexan->getFloat();
		break;
	case LEX_STRING:
		yylval.string_val = &g_lexan->getString();
		break;
	default:
		break;
	}

	return tok;
}

void yyerror(char const *msg)
{
	stringstream ss;
	ss << ID2STR(g_lexan->getFile()) << ":" << g_lexan->getLine();
	ERR_PP(ss.str(), msg);
}

int parseCode(const string& str)
{
	int ret = 0;
	g_lexan = new Lexan(STR2ID(str));

	try
	{
		ret = yyparse();
	}
	catch(...)
	{
		delete g_lexan;
		g_lexan = NULL;
		throw;
	}

	delete g_lexan;
	g_lexan = NULL;

	return ret;
}

