
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
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 20 "flash.y"
/*************************************************************************
					Compiler for the Flash language
***************************************************************************/
/*=========================================================================
	C Libraries, Symbol Table, Code Generator & other C code
=========================================================================*/
#include<memory.h>

#include <stdio.h>
/* For I/O																*/
#include <stdlib.h>
/* For malloc here and in symbol table									*/
#include <string.h>
/* For strcmp in symbol table											*/
#include "ST.h"
/* Symbol Table															*/
#include "SM.h"
/* Stack Machine														*/
#include "CG.h"
/* Code Generator														*/
#include "queue.h"
/* For formal parameters and arguments type check						*/
#define YYDEBUG 1
/* For Debugging														*/
int errors;
extern int yylineno;
/* Error Count*/
/*-------------------------------------------------------------------------
				The following supports a block structure
-------------------------------------------------------------------------*/
int fun_offset = 0;
int arg_offset = 0; 
int block_offset = 0;
int block_in()
{
  block_offset = block_offset + 1;
}
int reset_block()
{
  block_offset = 0;
}
/*-------------------------------------------------------------------------
				The following support backpatching
-------------------------------------------------------------------------*/
struct lbs
/* Labels for data, if and while*/
{
	int for_goto;
	int for_jmp_false;
};
struct lbs * newlblrec() /*      Allocate space for the labels			*/
{
	return (struct lbs *) malloc(sizeof(struct lbs));
}
/*-------------------------------------------------------------------------
				Install identifier & check if previously defined.
-------------------------------------------------------------------------*/
install ( char *sym_name ,int type, int block)
{
	symrec *s;
	s = getsym (sym_name);
	if (s == 0) {
		s = putsym (sym_name,type, block);
		//printf("%s, %d\n",s->name,s->block_offset);
	}
	else if (s->block_offset == 0) {
		yyerror( strcat(sym_name, " is alredy defined in the outer block") );
	}
	else if (s->block_offset != block){
		s = putsym (sym_name,type, block);
		//printf("%s, %d\n",s->name,s->block_offset);
	}
	else { errors++;
		yyerror( strcat(sym_name, " is already defined") );
	}
}
/*-------------------------------------------------------------------------
				If identifier is defined, generate code
-------------------------------------------------------------------------*/
context_check( enum code_ops operation, char *sym_name ,int type)
{   symrec *identifier;
	identifier = getsym( sym_name );
	if ( identifier == 0 ) { 
		errors++;
		yyerror( strcat(sym_name," is an undeclared identifier") );
		}
	else if (type != -1 && identifier->type != type) {
		yyerror( strcat(sym_name," type error!") );
		}
	else gen_code_bool_str( operation, sym_name );
}

context_check_fun( enum code_ops operation, char *sym_name ,int type)		
{   symrec *identifier;		
	identifier = getsym( sym_name );
	fun_offset = identifier->block_offset;		
	if ( identifier == 0 ) { 		
		errors++;		
		yyerror( strcat(sym_name," is an undeclared identifier") );	
		}		
	else if (type != -1 && identifier->type != type) {		
		yyerror( strcat(sym_name," type error!") );	
		}		
	else gen_fun( operation, identifier->name );		
}

argument_check(char* sym_name, int arg)
{
	
	symrec *identifier;		
	identifier = getsym( sym_name );
	int n = identifier->type; 
	char * checker = as[fun_offset-1].q.element[arg_offset-1];
	if ( identifier == 0 ) { 
		errors++;
		yyerror( strcat(sym_name," is an undeclared identifier") );
		}
	else {
			if ( !strcmp(checker,"PARA_INT")  &&	identifier->type != 1 )
				yyerror( strcat(sym_name," parameter type mismatch!") );
			else if (!strcmp(checker,"PARA_BOOL")  &&	identifier->type != 0 )
				yyerror( strcat(sym_name," parameter type mismatch!") );
			else if (!strcmp(checker,"PARA_STR")  &&	identifier->type != 2 )
				yyerror( strcat(sym_name," parameter type mismatch!") );
			}
	gen_code_bool_str( ARG, sym_name );
}	

/*=========================================================================
							SEMANTIC RECORDS
=========================================================================*/


/* Line 189 of yacc.c  */
#line 207 "flash.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
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
     STRING = 258,
     BOOLEAN = 259,
     NUMBER = 260,
     IDENTIFIER = 261,
     IF = 262,
     WHILE = 263,
     SKIP = 264,
     THEN = 265,
     ELSE = 266,
     FI = 267,
     DO = 268,
     END = 269,
     INTEGER = 270,
     READ = 271,
     WRITE = 272,
     LET = 273,
     IN = 274,
     BOOLE = 275,
     STR = 276,
     STACK = 277,
     ASSGNOP = 278,
     LEQ = 279,
     GEQ = 280,
     ONTO = 281,
     OUTFROM = 282,
     FUN = 283,
     END_FUN = 284,
     RETURN = 285,
     CALL = 286
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union 
/* Line 214 of yacc.c  */
#line 152 "flash.y"
semrec
{

/* Line 214 of yacc.c  */
#line 153 "flash.y"

int	intval;								/* Integer value */
char *id;								/* Identifiers	*/
struct lbs *lbls;						/* For backpatching	*/
char *boolval;	
char *strval;						



/* Line 214 of yacc.c  */
#line 287 "flash.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 299 "flash.tab.c"

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
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   277

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  92
/* YYNRULES -- Number of states.  */
#define YYNSTATES  165

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    46,     2,     2,    38,     2,
      41,    42,    34,    33,    43,    32,    48,    35,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    40,
      44,    39,    45,     2,    47,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    36,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    37,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,    12,    13,    16,    18,    22,    27,
      31,    36,    40,    45,    48,    52,    53,    56,    57,    67,
      68,    71,    73,    76,    80,    83,    87,    90,    94,    95,
      98,    99,   103,   104,   108,   109,   113,   114,   118,   119,
     122,   126,   128,   134,   139,   142,   143,   150,   151,   160,
     163,   167,   171,   174,   178,   182,   186,   190,   194,   197,
     198,   199,   200,   211,   212,   213,   221,   222,   223,   224,
     235,   236,   237,   245,   247,   249,   253,   257,   261,   265,
     269,   273,   277,   281,   285,   289,   293,   297,   301,   303,
     305,   307,   309
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      50,     0,    -1,    -1,    18,    52,    54,    19,    51,    64,
      14,    -1,    -1,    52,    53,    -1,     9,    -1,    15,    61,
       6,    -1,    15,    61,     6,    40,    -1,    20,    62,     6,
      -1,    20,    62,     6,    40,    -1,    20,    63,     6,    -1,
      21,    63,     6,    40,    -1,    22,     6,    -1,    22,     6,
      40,    -1,    -1,    54,    55,    -1,    -1,    28,     6,    56,
      41,    57,    42,    52,    64,    29,    -1,    -1,    57,    58,
      -1,     9,    -1,    15,     6,    -1,    15,     6,    40,    -1,
      20,     6,    -1,    20,     6,    40,    -1,    21,     6,    -1,
      21,     6,    40,    -1,    -1,    60,     6,    -1,    -1,    60,
       6,    43,    -1,    -1,    61,     6,    43,    -1,    -1,    62,
       6,    43,    -1,    -1,    63,     6,    43,    -1,    -1,    64,
      65,    -1,    64,    65,    40,    -1,     9,    -1,     6,    26,
      44,    78,    45,    -1,     6,    23,     6,    27,    -1,    30,
      78,    -1,    -1,    31,     6,    66,    41,    59,    42,    -1,
      -1,     6,    23,    31,     6,    67,    41,    59,    42,    -1,
      16,     6,    -1,    16,    46,     6,    -1,    16,    47,     6,
      -1,    17,    78,    -1,    17,    46,    79,    -1,    17,    47,
      80,    -1,     6,    23,    78,    -1,     6,    23,    79,    -1,
       6,    23,    80,    -1,     7,    80,    -1,    -1,    -1,    -1,
       7,    78,    68,    10,    64,    69,    11,    70,    64,    12,
      -1,    -1,    -1,     8,    71,    78,    72,    13,    64,    14,
      -1,    -1,    -1,    -1,     7,    79,    73,    10,    64,    74,
      11,    75,    64,    12,    -1,    -1,    -1,     8,    76,    79,
      77,    13,    64,    14,    -1,     5,    -1,     6,    -1,    78,
      44,    78,    -1,    78,    39,    78,    -1,    78,    45,    78,
      -1,    78,    25,    78,    -1,    78,    24,    78,    -1,    78,
      33,    78,    -1,    78,    32,    78,    -1,    78,    34,    78,
      -1,    78,    35,    78,    -1,    78,    36,    78,    -1,    78,
      37,    78,    -1,    78,    38,    78,    -1,    41,    78,    42,
      -1,     4,    -1,     6,    -1,     3,    -1,     6,    -1,    80,
      48,    80,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   188,   188,   185,   193,   194,   196,   197,   201,   206,
     210,   215,   219,   224,   228,   234,   235,   238,   237,   252,
     253,   255,   256,   260,   267,   271,   278,   282,   290,   291,
     297,   298,   305,   306,   312,   313,   319,   320,   326,   327,
     331,   334,   335,   339,   344,   349,   348,   359,   358,   369,
     373,   377,   381,   385,   389,   393,   397,   401,   408,   413,
     418,   422,   412,   431,   436,   430,   451,   456,   460,   450,
     469,   474,   468,   485,   486,   487,   488,   489,   490,   491,
     492,   493,   494,   495,   496,   497,   498,   499,   501,   502,
     504,   505,   506
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "STRING", "BOOLEAN", "NUMBER",
  "IDENTIFIER", "IF", "WHILE", "SKIP", "THEN", "ELSE", "FI", "DO", "END",
  "INTEGER", "READ", "WRITE", "LET", "IN", "BOOLE", "STR", "STACK",
  "ASSGNOP", "LEQ", "GEQ", "ONTO", "OUTFROM", "FUN", "END_FUN", "RETURN",
  "CALL", "'-'", "'+'", "'*'", "'/'", "'^'", "'|'", "'&'", "'='", "';'",
  "'('", "')'", "','", "'<'", "'>'", "'#'", "'@'", "'.'", "$accept",
  "program", "$@1", "declaration", "declarations", "functions", "fun",
  "$@2", "parameter", "parameters", "arguments", "argument", "id_seqi",
  "id_seqb", "id_seqs", "commands", "command", "$@3", "$@4", "$@5", "$@6",
  "$@7", "$@8", "$@9", "$@10", "$@11", "$@12", "$@13", "$@14", "exp_int",
  "exp_bol", "exp_str", 0
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
     285,   286,    45,    43,    42,    47,    94,   124,    38,    61,
      59,    40,    41,    44,    60,    62,    35,    64,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    51,    50,    52,    52,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    54,    54,    56,    55,    57,
      57,    58,    58,    58,    58,    58,    58,    58,    59,    59,
      60,    60,    61,    61,    62,    62,    63,    63,    64,    64,
      64,    65,    65,    65,    65,    66,    65,    67,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    68,
      69,    70,    65,    71,    72,    65,    73,    74,    75,    65,
      76,    77,    65,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    79,    79,
      80,    80,    80
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     7,     0,     2,     1,     3,     4,     3,
       4,     3,     4,     2,     3,     0,     2,     0,     9,     0,
       2,     1,     2,     3,     2,     3,     2,     3,     0,     2,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     2,
       3,     1,     5,     4,     2,     0,     6,     0,     8,     2,
       3,     3,     2,     3,     3,     3,     3,     3,     2,     0,
       0,     0,    10,     0,     0,     7,     0,     0,     0,    10,
       0,     0,     7,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       1,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     4,     0,    15,     1,     6,    32,    34,    36,     0,
       5,     0,     0,     0,     0,     0,    13,     2,     0,    16,
       7,     9,    11,     0,    14,    38,    17,     8,    33,    10,
      35,    37,    12,     0,     0,     0,     0,    63,    41,     3,
       0,     0,     0,     0,    39,    19,     0,     0,    90,    88,
      73,    91,     0,    59,    66,    58,     0,     0,    49,     0,
       0,    74,     0,     0,    52,    44,    45,    40,     0,    74,
       0,    55,    56,    57,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    64,    89,    71,    50,    51,    53,    91,    54,     0,
      21,     0,     0,     0,     4,    20,    43,    47,     0,    87,
      79,    78,    81,    80,    82,    83,    84,    85,    86,    76,
      75,    77,    38,    38,    92,     0,     0,    28,    22,    24,
      26,    38,     0,    42,    60,    67,    38,    38,     0,     0,
      23,    25,    27,     0,    28,     0,     0,     0,     0,    46,
      29,    18,     0,    61,    68,    65,    72,    31,    48,    38,
      38,     0,     0,    62,    69
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    25,     3,    10,    11,    19,    34,    68,   105,
     138,   139,    12,    13,    14,    33,    44,    99,   132,    88,
     145,   159,    56,   125,    89,   146,   160,    57,   126,   121,
      54,    55
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -67
static const yytype_int16 yypact[] =
{
      -9,   -67,    15,   255,   -67,   -67,   -67,   -67,   -67,    29,
     -67,    49,    30,    56,    68,    76,    24,   -67,    85,   -67,
     -32,   -21,     9,    -6,   -67,   -67,   -67,   -67,   -67,   -67,
     -67,   -67,   -67,    95,    39,    46,    22,    88,   -67,   -67,
       8,    12,    25,    91,    70,   -67,    -2,    77,   -67,   -67,
     -67,    51,    25,   181,   -67,    72,    25,    17,   -67,   116,
     117,   -67,    17,   111,   181,   181,   -67,   -67,    58,    33,
     118,   181,   -67,    72,    25,   159,    25,    25,    25,    25,
      25,    25,    25,    25,    25,    25,    25,    25,   130,   134,
     111,   181,   -67,   -67,   -67,   -67,   -67,   -67,    72,    86,
     -67,   146,   148,   155,   -67,   -67,   -67,   -67,   197,   -67,
     181,   181,   213,   213,   229,   229,   229,    74,    74,   -12,
     181,   181,   -67,   -67,    72,   166,   167,   162,   142,   149,
     150,   255,   140,    25,   169,   169,   -67,   -67,   128,   196,
     -67,   -67,   -67,    99,   162,   198,   199,   125,   129,   -67,
     164,   -67,   170,   -67,   -67,   -67,   -67,   -67,   -67,   -67,
     -67,   141,   157,   -67,   -67
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -67,   -67,   -67,   104,   -67,   -67,   -67,   -67,   -67,   -67,
      67,   -67,   -67,   -67,   215,   -66,   -67,   -67,   -67,   -67,
     -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,   -36,
     105,   -39
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -92
static const yytype_int16 yytable[] =
{
      53,    48,    49,    50,    69,    64,    65,    73,    27,     1,
      71,    28,    76,    77,    58,     4,    75,    50,    61,    29,
      91,    49,    30,    92,    98,    48,    49,    50,    51,    70,
      50,    61,    86,    87,    32,    16,    20,    31,   108,    52,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   124,    31,    52,    59,    60,   134,   135,    62,    63,
     106,   -74,    21,    52,    24,   143,    52,   100,    17,    46,
     147,   148,    47,   101,    22,   -74,   -74,    18,   102,   103,
      45,   -91,    23,   -74,   -74,   -74,   -74,   -74,   -74,   -74,
     -74,    26,   -70,   161,   162,   -74,   -74,    66,    76,    77,
     104,    35,    36,    37,    38,    35,    36,    37,    38,    39,
      67,    40,    41,    85,    48,    40,    41,    97,    86,    87,
      90,    74,    94,    95,   107,    42,    43,   127,   151,    42,
      43,    35,    36,    37,    38,    35,    36,    37,    38,   155,
     122,    40,    41,   156,   123,    40,    41,    35,    36,    37,
      38,    72,   128,   163,   129,    42,    43,    40,    41,    42,
      43,   130,    93,    35,    36,    37,    38,    96,   -30,   164,
     149,    42,    43,    40,    41,    35,    36,    37,    38,   136,
     137,   144,   140,    76,    77,    40,    41,    42,    43,   141,
     142,    78,    79,    80,    81,    82,    83,    84,    85,    42,
      43,   109,   150,    86,    87,    76,    77,   157,   131,   153,
     154,   152,   158,    78,    79,    80,    81,    82,    83,    84,
      85,    76,    77,    15,     0,    86,    87,     0,     0,    78,
      79,    80,    81,    82,    83,    84,    85,    76,    77,     0,
       0,    86,   133,     0,     0,     0,     0,    80,    81,    82,
      83,    84,    85,    76,    77,     0,     0,    86,    87,     0,
       0,     0,     0,     0,     5,    82,    83,    84,    85,     0,
       6,     0,     0,    86,    87,     7,     8,     9
};

static const yytype_int16 yycheck[] =
{
      36,     3,     4,     5,     6,    41,    42,    46,    40,    18,
      46,    43,    24,    25,     6,     0,    52,     5,     6,    40,
      56,     4,    43,     6,    63,     3,     4,     5,     6,    31,
       5,     6,    44,    45,    40,     6,     6,    43,    74,    41,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    90,    43,    41,    46,    47,   122,   123,    46,    47,
      27,    10,     6,    41,    40,   131,    41,     9,    19,    23,
     136,   137,    26,    15,     6,    24,    25,    28,    20,    21,
      41,    48,     6,    32,    33,    34,    35,    36,    37,    38,
      39,     6,     4,   159,   160,    44,    45,     6,    24,    25,
      42,     6,     7,     8,     9,     6,     7,     8,     9,    14,
      40,    16,    17,    39,     3,    16,    17,     6,    44,    45,
      48,    44,     6,     6,     6,    30,    31,    41,    29,    30,
      31,     6,     7,     8,     9,     6,     7,     8,     9,    14,
      10,    16,    17,    14,    10,    16,    17,     6,     7,     8,
       9,    46,     6,    12,     6,    30,    31,    16,    17,    30,
      31,     6,    57,     6,     7,     8,     9,    62,     6,    12,
      42,    30,    31,    16,    17,     6,     7,     8,     9,    13,
      13,    41,    40,    24,    25,    16,    17,    30,    31,    40,
      40,    32,    33,    34,    35,    36,    37,    38,    39,    30,
      31,    42,     6,    44,    45,    24,    25,    43,   104,    11,
      11,   144,    42,    32,    33,    34,    35,    36,    37,    38,
      39,    24,    25,     8,    -1,    44,    45,    -1,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    24,    25,    -1,
      -1,    44,    45,    -1,    -1,    -1,    -1,    34,    35,    36,
      37,    38,    39,    24,    25,    -1,    -1,    44,    45,    -1,
      -1,    -1,    -1,    -1,     9,    36,    37,    38,    39,    -1,
      15,    -1,    -1,    44,    45,    20,    21,    22
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    18,    50,    52,     0,     9,    15,    20,    21,    22,
      53,    54,    61,    62,    63,    63,     6,    19,    28,    55,
       6,     6,     6,     6,    40,    51,     6,    40,    43,    40,
      43,    43,    40,    64,    56,     6,     7,     8,     9,    14,
      16,    17,    30,    31,    65,    41,    23,    26,     3,     4,
       5,     6,    41,    78,    79,    80,    71,    76,     6,    46,
      47,     6,    46,    47,    78,    78,     6,    40,    57,     6,
      31,    78,    79,    80,    44,    78,    24,    25,    32,    33,
      34,    35,    36,    37,    38,    39,    44,    45,    68,    73,
      48,    78,     6,    79,     6,     6,    79,     6,    80,    66,
       9,    15,    20,    21,    42,    58,    27,     6,    78,    42,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    10,    10,    80,    72,    77,    41,     6,     6,
       6,    52,    67,    45,    64,    64,    13,    13,    59,    60,
      40,    40,    40,    64,    41,    69,    74,    64,    64,    42,
       6,    29,    59,    11,    11,    14,    14,    43,    42,    70,
      75,    64,    64,    12,    12
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
		  Type, Value); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
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
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

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

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
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

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

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
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 188 "flash.y"
    {	gen_code( DATA, data_location() - 1 );
					reset_block();								;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 191 "flash.y"
    {	gen_code( HALT, 0 ); YYACCEPT;				;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 198 "flash.y"
    {
		yyerror("Missing semicolon ';' ");
	;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 202 "flash.y"
    {	
		install( (yyvsp[(3) - (4)].id) , 1, block_offset);  
		gen_code_def(DEF, (yyvsp[(3) - (4)].id), "0");
	;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 207 "flash.y"
    {
		yyerror("Missing semicolon ';' ");
	;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 211 "flash.y"
    {	
		install( (yyvsp[(3) - (4)].id) , 0, block_offset);  
		gen_code_def(DEF, (yyvsp[(3) - (4)].id), "true");
	;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 216 "flash.y"
    {
		yyerror("Missing semicolon ';' ");
	;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 220 "flash.y"
    {	
		install( (yyvsp[(3) - (4)].id) , 2, block_offset);  
		gen_code_def(DEF, (yyvsp[(3) - (4)].id), "str");
	;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 225 "flash.y"
    {
		yyerror("Missing semicolon ';' ");
	;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 229 "flash.y"
    { 
		install((yyvsp[(2) - (3)].id), 4, block_offset); 
		gen_code_def(DEF, (yyvsp[(2) - (3)].id), "stk");  
	;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 238 "flash.y"
    { 
		block_in(); 						/*	increment block scope  */
		gen_fun( FUN_INIT, (yyvsp[(2) - (2)].id)); 
		install((yyvsp[(2) - (2)].id), 3, block_offset); 
		activate((yyvsp[(2) - (2)].id), block_offset);
	;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 248 "flash.y"
    { 
    	gen_code( FUN_EN, 0);
    ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 257 "flash.y"
    {
		yyerror("Missing semicolon ';' ");
	;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 261 "flash.y"
    {	
		install( (yyvsp[(2) - (3)].id) , 1, block_offset );
		context_check(PARA_INT , (yyvsp[(2) - (3)].id), -1);
		add_para_to_as(block_offset,"PARA_INT");
		//printf("argi : %d\n",fun_offset);					
	;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 268 "flash.y"
    {
		yyerror("Missing semicolon ';' ");
	;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 272 "flash.y"
    {	
		install( (yyvsp[(2) - (3)].id) , 0, block_offset );
		context_check(PARA_BOOL , (yyvsp[(2) - (3)].id), -1);	
		add_para_to_as(block_offset,"PARA_BOOL");	
		//printf("argb : %d\n",fun_offset)	;			
	;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 279 "flash.y"
    {
		yyerror("Missing semicolon ';' ");
	;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 283 "flash.y"
    {	
		install( (yyvsp[(2) - (3)].id) , 2, block_offset );
		context_check(PARA_STR , (yyvsp[(2) - (3)].id), -1);
		add_para_to_as(block_offset,"PARA_STR");
		//printf("args : %d\n",fun_offset)		;				
	;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 292 "flash.y"
    { 
		arg_offset++;
		argument_check((yyvsp[(2) - (2)].id),arg_offset);				
	;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 299 "flash.y"
    {	
		arg_offset++;	
		argument_check((yyvsp[(2) - (3)].id),arg_offset);			
	;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 307 "flash.y"
    {	
		install( (yyvsp[(2) - (3)].id) , 1, block_offset); 
		gen_code_def(DEF, (yyvsp[(2) - (3)].id) ,"0");			
	;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 314 "flash.y"
    {	
		install( (yyvsp[(2) - (3)].id) , 0, block_offset);
		gen_code_def(DEF, (yyvsp[(2) - (3)].id), "true");			
	;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 321 "flash.y"
    {	
		install( (yyvsp[(2) - (3)].id) , 2, block_offset);
		gen_code_def(DEF, (yyvsp[(2) - (3)].id) ,"str");			
	;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 328 "flash.y"
    {
		yyerror("Missing semicolon ';' ");
	;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 336 "flash.y"
    { 
		context_check(ADDSTK, (yyvsp[(1) - (5)].id), 4);      
	;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 340 "flash.y"
    { 
		context_check(REMSTK, (yyvsp[(3) - (4)].id), 4); 
		context_check(STORE, (yyvsp[(1) - (4)].id) , 1);     
	;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 345 "flash.y"
    { 
		gen_code(POP, 0); 						
	;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 349 "flash.y"
    { 
		context_check_fun(FUN_CALL, (yyvsp[(2) - (2)].id), 3);		
	;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 353 "flash.y"
    {
		if(arg_offset != as[fun_offset-1].q.count)
		yyerror( " Number of parameters don't match!");
		arg_offset = 0;		
	;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 359 "flash.y"
    { 
		context_check_fun(FUN_CALL, (yyvsp[(4) - (4)].id), 3);		
	;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 363 "flash.y"
    {
		if(arg_offset != as[fun_offset-1].q.count)
		yyerror( " Number of parameters don't match!");
		arg_offset = 0;
		context_check( STORE, (yyvsp[(1) - (8)].id) , 1);		
	;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 370 "flash.y"
    {    
		context_check( READ_INT, (yyvsp[(2) - (2)].id) , 1);				
	;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 374 "flash.y"
    {    
		context_check( READ_BOL, (yyvsp[(3) - (3)].id) , 0);			
	;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 378 "flash.y"
    {    
		context_check( READ_STR, (yyvsp[(3) - (3)].id) , 2);			
	;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 382 "flash.y"
    {	
		gen_code( WRITE_INT, 1 );							
	;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 386 "flash.y"
    {	
		gen_code( WRITE_BOL, 0 );						
	;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 390 "flash.y"
    {	
		gen_code( WRITE_STR, 2 );						
	;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 394 "flash.y"
    { 
		context_check( STORE, (yyvsp[(1) - (3)].id) , 1);   		
	;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 398 "flash.y"
    { 
		context_check( STORE, (yyvsp[(1) - (3)].id) , 0);   		
	;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 402 "flash.y"
    { 
		context_check( STORE, (yyvsp[(1) - (3)].id) , 2);   		
	;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 409 "flash.y"
    {
		yyerror("IF does not support String types, maybe next release! ");
	;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 413 "flash.y"
    {	
		(yyvsp[(1) - (2)].lbls) = (struct lbs *) newlblrec();
		(yyvsp[(1) - (2)].lbls)->for_jmp_false = reserve_loc(); 					
	;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 418 "flash.y"
    { 
		(yyvsp[(1) - (5)].lbls)->for_goto = reserve_loc(); 					
	;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 422 "flash.y"
    {
		back_patch( (yyvsp[(1) - (7)].lbls)->for_jmp_false, JMP_FALSE,gen_label() ); 								
	;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 427 "flash.y"
    { 
	  	back_patch( (yyvsp[(1) - (10)].lbls)->for_goto, GOTO, gen_label() ); 		
	;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 431 "flash.y"
    { 
		(yyvsp[(1) - (1)].lbls) = (struct lbs *) newlblrec();
		(yyvsp[(1) - (1)].lbls)->for_goto = gen_label(); 							
	;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 436 "flash.y"
    { 
		(yyvsp[(1) - (3)].lbls)->for_jmp_false = reserve_loc();					
	;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 442 "flash.y"
    { 
		gen_code( GOTO, (yyvsp[(1) - (7)].lbls)->for_goto );
		back_patch( (yyvsp[(1) - (7)].lbls)->for_jmp_false, JMP_FALSE, gen_label());
	;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 451 "flash.y"
    {	
		(yyvsp[(1) - (2)].lbls) = (struct lbs *) newlblrec();
		(yyvsp[(1) - (2)].lbls)->for_jmp_false = reserve_loc(); 					
	;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 456 "flash.y"
    {
		(yyvsp[(1) - (5)].lbls)->for_goto = reserve_loc(); 					
	;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 460 "flash.y"
    { 
		back_patch( (yyvsp[(1) - (7)].lbls)->for_jmp_false, JMP_FALSE, gen_label() ); 								
	;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 465 "flash.y"
    { 
		back_patch( (yyvsp[(1) - (10)].lbls)->for_goto, GOTO, gen_label() ); 		
	;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 469 "flash.y"
    { 
		(yyvsp[(1) - (1)].lbls) = (struct lbs *) newlblrec();
		(yyvsp[(1) - (1)].lbls)->for_goto = gen_label(); 							
	;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 474 "flash.y"
    { 
		(yyvsp[(1) - (3)].lbls)->for_jmp_false = reserve_loc();			
	;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 480 "flash.y"
    { 
		gen_code( GOTO, (yyvsp[(1) - (7)].lbls)->for_goto );
		back_patch( (yyvsp[(1) - (7)].lbls)->for_jmp_false,JMP_FALSE,gen_label() );	
	;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 485 "flash.y"
    { gen_code( LD_INT, (yyvsp[(1) - (1)].intval) );							;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 486 "flash.y"
    { context_check( LD_VAR, (yyvsp[(1) - (1)].id) , 1);					;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 487 "flash.y"
    { gen_code( LT, 0 );								;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 488 "flash.y"
    { gen_code( EQ, 0 );								;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 489 "flash.y"
    { gen_code( GT, 0 );								;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 490 "flash.y"
    { gen_code( GTEQ, 0 );								;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 491 "flash.y"
    { gen_code( LTEQ, 0 );								;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 492 "flash.y"
    { gen_code( ADD, 0 );								;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 493 "flash.y"
    { gen_code( SUB, 0 );								;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 494 "flash.y"
    { gen_code( MULT, 0 );								;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 495 "flash.y"
    { gen_code( DIV, 0 );								;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 496 "flash.y"
    { gen_code( PWR, 0 );								;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 497 "flash.y"
    { gen_code( OR, 0 );								;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 498 "flash.y"
    { gen_code( AND, 0 );								;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 501 "flash.y"
    { gen_code_bool_str( LD_BOL, (yyvsp[(1) - (1)].boolval) );					;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 502 "flash.y"
    { context_check( LD_VAR, (yyvsp[(1) - (1)].id) ,0);					;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 504 "flash.y"
    { gen_code_bool_str( LD_STR, (yyvsp[(1) - (1)].strval) );					;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 505 "flash.y"
    { context_check( LD_VAR, (yyvsp[(1) - (1)].id) ,2);					;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 506 "flash.y"
    { gen_code(ADD_STR, 0);								;}
    break;



/* Line 1455 of yacc.c  */
#line 2325 "flash.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

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
		      yytoken, &yylval);
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


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
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
#line 508 "flash.y"

/*=========================================================================
MAIN
=========================================================================*/
main( int argc, char *argv[] )
{   extern FILE *yyin;
	++argv; --argc;
	
	if (argv[0] == NULL || strstr(argv[0], ".fl") == NULL) {
		printf ( "Input file is not a Flash file \n" );
		exit(1);
	}
	
	yyin = fopen( argv[0], "r" );
	
	/*yydebug = 1;*/
	errors = 0;
	yyparse ();
	printf ( "Parse Completed\n" );
	if ( errors == 0 )
	{	
		char *outFile = malloc(strlen(argv[0])+strlen(".cls")+1);
		strcpy(outFile, argv[0]);
		strcat(outFile, ".cls");
		FILE *fp = fopen(outFile,"w+");
		print_code (fp);
		fclose(fp);
	}
}
/*=========================================================================
YYERROR
=========================================================================*/
yyerror ( char *s ) /* Called by yyparse on error */
{
errors++;
printf ("Line : %d -- Error in Semantics : %s \n", yylineno, s);
exit(1);
}
/**************************** End Grammar File ***************************/

