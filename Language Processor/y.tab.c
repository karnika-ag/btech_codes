/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "k_parse1.y" /* yacc.c:339  */

#include<stdio.h>
#include<stdlib.h>

#line 71 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


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
    INT = 258,
    FLOAT = 259,
    CHAR = 260,
    DOUBLE = 261,
    VOID = 262,
    LONG = 263,
    CONST = 264,
    TYPEDEF = 265,
    STRUCT = 266,
    BOOL = 267,
    FOR = 268,
    DO = 269,
    WHILE = 270,
    BREAK = 271,
    CONTINUE = 272,
    IF = 273,
    ELSE = 274,
    SWITCH = 275,
    CASE = 276,
    DEFAULT = 277,
    NUM = 278,
    ID = 279,
    MAIN = 280,
    DOT = 281,
    RETURN = 282,
    ADD = 283,
    SUB = 284,
    MUL = 285,
    DIV = 286,
    AE = 287,
    SE = 288,
    ME = 289,
    DE = 290,
    LE = 291,
    GE = 292,
    EE = 293,
    NE = 294,
    LT = 295,
    GT = 296,
    LO = 297,
    LA = 298,
    BO = 299,
    BA = 300,
    BXOR = 301,
    ASGN = 302,
    MOD = 303
  };
#endif
/* Tokens.  */
#define INT 258
#define FLOAT 259
#define CHAR 260
#define DOUBLE 261
#define VOID 262
#define LONG 263
#define CONST 264
#define TYPEDEF 265
#define STRUCT 266
#define BOOL 267
#define FOR 268
#define DO 269
#define WHILE 270
#define BREAK 271
#define CONTINUE 272
#define IF 273
#define ELSE 274
#define SWITCH 275
#define CASE 276
#define DEFAULT 277
#define NUM 278
#define ID 279
#define MAIN 280
#define DOT 281
#define RETURN 282
#define ADD 283
#define SUB 284
#define MUL 285
#define DIV 286
#define AE 287
#define SE 288
#define ME 289
#define DE 290
#define LE 291
#define GE 292
#define EE 293
#define NE 294
#define LT 295
#define GT 296
#define LO 297
#define LA 298
#define BO 299
#define BA 300
#define BXOR 301
#define ASGN 302
#define MOD 303

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 215 "y.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   156

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  72
/* YYNRULES -- Number of rules.  */
#define YYNRULES  116
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  183

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   304

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      51,    52,     2,     2,    55,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    56,    54,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    50,     2,    53,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    15,    15,    18,    20,    22,    23,    25,    26,    27,
      28,    28,    28,    30,    30,    32,    34,    36,    36,    38,
      38,    41,    41,    41,    44,    44,    44,    46,    46,    46,
      48,    48,    48,    50,    50,    52,    52,    53,    55,    57,
      60,    60,    60,    60,    62,    62,    62,    64,    66,    68,
      68,    70,    72,    72,    74,    74,    75,    77,    77,    78,
      78,    80,    80,    81,    83,    85,    85,    87,    88,    88,
      90,    92,    92,    94,    96,    96,    98,   100,   100,   102,
     104,   104,   105,   105,   106,   106,   107,   107,   108,   108,
     109,   109,   110,   112,   112,   113,   113,   114,   116,   116,
     117,   117,   118,   120,   120,   122,   124,   125,   126,   127,
     130,   131,   132,   133,   134,   135,   136
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "CHAR", "DOUBLE", "VOID",
  "LONG", "CONST", "TYPEDEF", "STRUCT", "BOOL", "FOR", "DO", "WHILE",
  "BREAK", "CONTINUE", "IF", "ELSE", "SWITCH", "CASE", "DEFAULT", "NUM",
  "ID", "MAIN", "DOT", "RETURN", "ADD", "SUB", "MUL", "DIV", "AE", "SE",
  "ME", "DE", "LE", "GE", "EE", "NE", "LT", "GT", "LO", "LA", "BO", "BA",
  "BXOR", "ASGN", "MOD", "\"else\"", "'{'", "'('", "')'", "'}'", "';'",
  "','", "':'", "$accept", "pgm", "block", "stmtlist", "stmt", "decl",
  "$@1", "varlist", "assignment", "$@2", "assgn1", "$@3", "$@4", "$@5",
  "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "ifelsestmt", "$@12",
  "elsestmt", "$@13", "ifelsebody", "forstmt", "$@14", "$@15", "$@16",
  "whilestmt", "$@17", "$@18", "whilebody", "switchstmt", "$@19",
  "switchbody", "switchcase", "$@20", "$@21", "breakstmt", "$@22", "$@23",
  "switchend", "$@24", "switcheval", "expr", "$@25", "expr2", "$@26",
  "expr3", "$@27", "expr4", "$@28", "expr5", "$@29", "expr6", "$@30",
  "$@31", "$@32", "$@33", "$@34", "$@35", "expr7", "$@36", "$@37", "expr8",
  "$@38", "$@39", "expr9", "$@40", "expr10", "data_type", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     123,    40,    41,   125,    59,    44,    58
};
# endif

#define YYPACT_NINF -154

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-154)))

#define YYTABLE_NINF -45

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     114,  -154,  -154,  -154,  -154,  -154,  -154,  -154,    29,    19,
    -154,    -1,     0,   -11,   -11,  -154,  -154,    14,     2,     3,
       4,  -154,  -154,  -154,     8,    11,  -154,  -154,  -154,    41,
    -154,  -154,    42,   -20,   -20,   -22,  -154,  -154,    17,    51,
      22,  -154,  -154,   -20,   -20,   -36,    34,    36,    35,    37,
      97,   -21,     6,  -154,    39,   -28,  -154,  -154,  -154,  -154,
    -154,  -154,   -20,  -154,    30,  -154,  -154,   -12,  -154,  -154,
    -154,  -154,  -154,  -154,  -154,  -154,  -154,  -154,  -154,  -154,
    -154,  -154,  -154,  -154,  -154,  -154,   -20,   -20,   -20,   -20,
     -20,    -7,    64,   -20,  -154,   -20,    66,   -20,   -20,   -20,
     -20,   -20,   -20,   -20,   -20,   -20,   -20,   -20,   -20,   -20,
     -20,   -20,    47,    56,    56,    56,    56,    56,  -154,  -154,
      56,    34,  -154,  -154,    70,    36,    35,    37,    97,   -21,
     -21,   -21,   -21,   -21,   -21,     6,     6,  -154,  -154,  -154,
      25,  -154,  -154,  -154,  -154,    66,    45,  -154,  -154,    79,
    -154,    52,  -154,  -154,  -154,  -154,    42,    66,  -154,    48,
    -154,  -154,  -154,    53,   -11,    55,   -11,    88,    94,   -11,
      95,  -154,  -154,  -154,  -154,  -154,    25,    59,    60,  -154,
    -154,    25,  -154
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   110,   111,   112,   113,   114,   115,   116,     0,     0,
       1,     0,     0,     0,     6,     2,     4,    44,     0,     0,
       0,    17,     3,     5,     0,     0,     9,    12,    10,     0,
      11,    13,     0,     0,     0,     0,     7,     8,     0,     0,
       0,   108,   107,     0,     0,     0,    67,    70,    73,    76,
      79,    92,    97,   102,   105,     0,    21,    24,    27,    30,
      19,    18,     0,    16,    14,    40,   109,     0,    65,    33,
      68,    71,    74,    77,    82,    86,    90,    88,    80,    84,
      93,    95,    98,   100,   103,    49,     0,     0,     0,     0,
       0,     0,     0,     0,   106,     0,    44,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    22,    25,    28,    31,    20,    45,    15,
      41,    66,    38,    39,    37,    69,    72,    75,    78,    83,
      87,    91,    89,    81,    85,    94,    96,    99,   101,   104,
      56,    23,    26,    29,    32,    44,     0,    35,    34,     0,
      54,     0,    51,    47,    48,    46,     0,    44,    52,     0,
      50,    42,    36,     0,     6,     0,     6,    64,    63,     0,
      59,    61,    55,    43,    57,    53,    56,     0,     0,    60,
      62,    56,    58
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -154,  -154,   -13,   101,   -94,  -154,  -154,  -154,   -31,  -154,
    -154,  -154,  -154,  -154,  -154,  -154,  -154,  -154,  -154,  -154,
    -154,  -154,  -154,  -154,   -34,  -154,  -154,  -154,  -154,  -154,
    -154,  -154,  -154,  -154,  -154,  -154,  -153,  -154,  -154,  -154,
    -154,  -154,  -154,  -154,   -42,   -29,  -154,    32,  -154,    31,
    -154,    33,  -154,    40,  -154,    43,  -154,  -154,  -154,  -154,
    -154,  -154,    44,  -154,  -154,   -59,  -154,  -154,   -68,  -154,
      86,   130
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     8,    16,   167,    23,    24,    39,    64,    25,    35,
      61,    90,    86,   141,    87,   142,    88,   143,    89,   144,
      26,    96,   148,   157,   124,    27,    93,   146,   165,    28,
      29,   145,   155,    30,   112,   151,   152,   163,   159,   175,
     178,   176,   172,   177,   168,    45,    95,    46,    97,    47,
      98,    48,    99,    49,   100,    50,   105,   101,   106,   102,
     104,   103,    51,   107,   108,    52,   109,   110,    53,   111,
      54,    31
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      15,    40,   123,    41,    42,    55,    68,    80,    81,    43,
      56,    57,    58,    59,    68,    67,    69,     1,     2,     3,
       4,     5,     6,   179,    85,    60,     7,    18,   182,    10,
      68,    44,    19,    91,    20,    68,    82,    83,    21,    14,
      94,   137,   138,   139,    11,   118,   149,   150,   135,   136,
      12,   154,    13,    32,    33,    34,    38,   113,   114,   115,
     116,   117,    36,   123,   120,    37,    21,    22,    62,     1,
       2,     3,     4,     5,     6,    63,    65,    70,     7,    18,
      71,    72,    73,   122,    19,    92,    20,    84,   119,   147,
      21,     1,     2,     3,     4,     5,     6,   140,    68,   156,
       7,    18,   158,   -44,   164,   160,    19,   169,    20,   166,
     171,   174,    21,   180,   181,    17,    14,     1,     2,     3,
       4,     5,     6,   162,   170,   161,     7,   121,   125,    66,
       9,   126,   153,    74,    75,    76,    77,    78,    79,   127,
       0,     0,     0,   128,   122,   129,   130,   131,   132,   133,
     134,     0,     0,     0,     0,     0,   173
};

static const yytype_int16 yycheck[] =
{
      13,    32,    96,    23,    24,    34,    42,    28,    29,    29,
      32,    33,    34,    35,    42,    44,    52,     3,     4,     5,
       6,     7,     8,   176,    52,    47,    12,    13,   181,     0,
      42,    51,    18,    62,    20,    42,    30,    31,    24,    50,
      52,   109,   110,   111,    25,    52,    21,    22,   107,   108,
      51,   145,    52,    51,    51,    51,    15,    86,    87,    88,
      89,    90,    54,   157,    93,    54,    24,    53,    51,     3,
       4,     5,     6,     7,     8,    24,    54,    43,    12,    13,
      44,    46,    45,    96,    18,    55,    20,    48,    24,    19,
      24,     3,     4,     5,     6,     7,     8,    50,    42,    54,
      12,    13,    23,    15,    56,    53,    18,    52,    20,    56,
      16,    16,    24,    54,    54,    14,    50,     3,     4,     5,
       6,     7,     8,   157,   166,   156,    12,    95,    97,    43,
       0,    98,   145,    36,    37,    38,    39,    40,    41,    99,
      -1,    -1,    -1,   100,   157,   101,   102,   103,   104,   105,
     106,    -1,    -1,    -1,    -1,    -1,   169
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    12,    58,   128,
       0,    25,    51,    52,    50,    59,    59,    60,    13,    18,
      20,    24,    53,    61,    62,    65,    77,    82,    86,    87,
      90,   128,    51,    51,    51,    66,    54,    54,    15,    63,
      65,    23,    24,    29,    51,   102,   104,   106,   108,   110,
     112,   119,   122,   125,   127,   102,    32,    33,    34,    35,
      47,    67,    51,    24,    64,    54,   127,   102,    42,    52,
      43,    44,    46,    45,    36,    37,    38,    39,    40,    41,
      28,    29,    30,    31,    48,    52,    69,    71,    73,    75,
      68,   102,    55,    83,    52,   103,    78,   105,   107,   109,
     111,   114,   116,   118,   117,   113,   115,   120,   121,   123,
     124,   126,    91,   102,   102,   102,   102,   102,    52,    24,
     102,   104,    59,    61,    81,   106,   108,   110,   112,   119,
     119,   119,   119,   119,   119,   122,   122,   125,   125,   125,
      50,    70,    72,    74,    76,    88,    84,    19,    79,    21,
      22,    92,    93,    59,    61,    89,    54,    80,    23,    95,
      53,    65,    81,    94,    56,    85,    56,    60,   101,    52,
     101,    16,    99,    59,    16,    96,    98,   100,    97,    93,
      54,    54,    93
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    57,    58,    59,    60,    60,    60,    61,    61,    61,
      61,    61,    61,    63,    62,    64,    64,    66,    65,    68,
      67,    69,    70,    67,    71,    72,    67,    73,    74,    67,
      75,    76,    67,    78,    77,    80,    79,    79,    81,    81,
      83,    84,    85,    82,    87,    88,    86,    89,    89,    91,
      90,    92,    94,    93,    95,    93,    93,    97,    96,    98,
      96,   100,    99,    99,   101,   103,   102,   102,   105,   104,
     104,   107,   106,   106,   109,   108,   108,   111,   110,   110,
     113,   112,   114,   112,   115,   112,   116,   112,   117,   112,
     118,   112,   112,   120,   119,   121,   119,   119,   123,   122,
     124,   122,   122,   126,   125,   125,   127,   127,   127,   127,
     128,   128,   128,   128,   128,   128,   128
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     3,     1,     2,     0,     2,     2,     1,
       1,     1,     1,     0,     3,     3,     1,     0,     3,     0,
       3,     0,     0,     4,     0,     0,     4,     0,     0,     4,
       0,     0,     4,     0,     7,     0,     3,     0,     1,     1,
       0,     0,     0,    12,     0,     0,     7,     1,     1,     0,
       8,     1,     0,     6,     0,     5,     0,     0,     4,     0,
       2,     0,     3,     0,     1,     0,     4,     1,     0,     4,
       1,     0,     4,     1,     0,     4,     1,     0,     4,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     1,     0,     4,     0,     4,     1,     0,     4,
       0,     4,     1,     0,     4,     1,     3,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 13:
#line 30 "k_parse1.y" /* yacc.c:1646  */
    { set_datatype(); }
#line 1435 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 32 "k_parse1.y" /* yacc.c:1646  */
    { var_decl();}
#line 1441 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 34 "k_parse1.y" /* yacc.c:1646  */
    { var_decl(); }
#line 1447 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 36 "k_parse1.y" /* yacc.c:1646  */
    { check_decl(); push();}
#line 1453 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 38 "k_parse1.y" /* yacc.c:1646  */
    {push();}
#line 1459 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 38 "k_parse1.y" /* yacc.c:1646  */
    {exp_asgn_evaluate();}
#line 1465 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 41 "k_parse1.y" /* yacc.c:1646  */
    {push1("+");}
#line 1471 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 41 "k_parse1.y" /* yacc.c:1646  */
    {exp_evaluate(); }
#line 1477 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 41 "k_parse1.y" /* yacc.c:1646  */
    {exp_asgn_evaluate();}
#line 1483 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 44 "k_parse1.y" /* yacc.c:1646  */
    {push1("-");}
#line 1489 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 44 "k_parse1.y" /* yacc.c:1646  */
    {exp_evaluate(); }
#line 1495 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 44 "k_parse1.y" /* yacc.c:1646  */
    {exp_asgn_evaluate();}
#line 1501 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 46 "k_parse1.y" /* yacc.c:1646  */
    {push1("*");}
#line 1507 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 46 "k_parse1.y" /* yacc.c:1646  */
    {exp_evaluate(); }
#line 1513 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 46 "k_parse1.y" /* yacc.c:1646  */
    {exp_asgn_evaluate();}
#line 1519 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 48 "k_parse1.y" /* yacc.c:1646  */
    {push1("/");}
#line 1525 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 48 "k_parse1.y" /* yacc.c:1646  */
    {exp_evaluate(); }
#line 1531 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 48 "k_parse1.y" /* yacc.c:1646  */
    {exp_asgn_evaluate();}
#line 1537 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 50 "k_parse1.y" /* yacc.c:1646  */
    { if_fun();}
#line 1543 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 52 "k_parse1.y" /* yacc.c:1646  */
    {else_fun();}
#line 1549 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 52 "k_parse1.y" /* yacc.c:1646  */
    {if_end();}
#line 1555 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 53 "k_parse1.y" /* yacc.c:1646  */
    {if_end();}
#line 1561 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 60 "k_parse1.y" /* yacc.c:1646  */
    {fun1();}
#line 1567 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 60 "k_parse1.y" /* yacc.c:1646  */
    {fun2();}
#line 1573 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 60 "k_parse1.y" /* yacc.c:1646  */
    {fun3();}
#line 1579 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 60 "k_parse1.y" /* yacc.c:1646  */
    {fun4();}
#line 1585 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 62 "k_parse1.y" /* yacc.c:1646  */
    {while_begin();}
#line 1591 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 62 "k_parse1.y" /* yacc.c:1646  */
    {while_body();}
#line 1597 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 64 "k_parse1.y" /* yacc.c:1646  */
    {while_end();}
#line 1603 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 66 "k_parse1.y" /* yacc.c:1646  */
    {while_end();}
#line 1609 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 68 "k_parse1.y" /* yacc.c:1646  */
    {switch_begin();}
#line 1615 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 70 "k_parse1.y" /* yacc.c:1646  */
    {switch_end();}
#line 1621 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 72 "k_parse1.y" /* yacc.c:1646  */
    {switchcase_fun();}
#line 1627 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 74 "k_parse1.y" /* yacc.c:1646  */
    {switchdefault_fun();}
#line 1633 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 77 "k_parse1.y" /* yacc.c:1646  */
    {break_fun();}
#line 1639 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 78 "k_parse1.y" /* yacc.c:1646  */
    {no_break_fun();}
#line 1645 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 80 "k_parse1.y" /* yacc.c:1646  */
    {break_fun();}
#line 1651 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 81 "k_parse1.y" /* yacc.c:1646  */
    {no_break_fun();}
#line 1657 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 85 "k_parse1.y" /* yacc.c:1646  */
    {push();}
#line 1663 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 85 "k_parse1.y" /* yacc.c:1646  */
    {exp_evaluate();}
#line 1669 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 88 "k_parse1.y" /* yacc.c:1646  */
    {push();}
#line 1675 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 88 "k_parse1.y" /* yacc.c:1646  */
    {exp_evaluate();}
#line 1681 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 92 "k_parse1.y" /* yacc.c:1646  */
    {push();}
#line 1687 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 92 "k_parse1.y" /* yacc.c:1646  */
    {exp_evaluate();}
#line 1693 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 96 "k_parse1.y" /* yacc.c:1646  */
    {push();}
#line 1699 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 96 "k_parse1.y" /* yacc.c:1646  */
    {exp_evaluate();}
#line 1705 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 100 "k_parse1.y" /* yacc.c:1646  */
    {push();}
#line 1711 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 100 "k_parse1.y" /* yacc.c:1646  */
    {exp_evaluate();}
#line 1717 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 104 "k_parse1.y" /* yacc.c:1646  */
    {push();}
#line 1723 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 104 "k_parse1.y" /* yacc.c:1646  */
    {exp_evaluate();}
#line 1729 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 105 "k_parse1.y" /* yacc.c:1646  */
    {push();}
#line 1735 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 105 "k_parse1.y" /* yacc.c:1646  */
    {exp_evaluate();}
#line 1741 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 106 "k_parse1.y" /* yacc.c:1646  */
    {push();}
#line 1747 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 106 "k_parse1.y" /* yacc.c:1646  */
    {exp_evaluate();}
#line 1753 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 107 "k_parse1.y" /* yacc.c:1646  */
    {push();}
#line 1759 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 107 "k_parse1.y" /* yacc.c:1646  */
    {exp_evaluate();}
#line 1765 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 108 "k_parse1.y" /* yacc.c:1646  */
    {push();}
#line 1771 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 108 "k_parse1.y" /* yacc.c:1646  */
    {exp_evaluate();}
#line 1777 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 109 "k_parse1.y" /* yacc.c:1646  */
    {push();}
#line 1783 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 109 "k_parse1.y" /* yacc.c:1646  */
    {exp_evaluate();}
#line 1789 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 112 "k_parse1.y" /* yacc.c:1646  */
    {push();}
#line 1795 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 112 "k_parse1.y" /* yacc.c:1646  */
    {exp_evaluate();}
#line 1801 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 113 "k_parse1.y" /* yacc.c:1646  */
    {push();}
#line 1807 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 113 "k_parse1.y" /* yacc.c:1646  */
    {exp_evaluate();}
#line 1813 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 116 "k_parse1.y" /* yacc.c:1646  */
    {push();}
#line 1819 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 116 "k_parse1.y" /* yacc.c:1646  */
    {exp_evaluate();}
#line 1825 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 117 "k_parse1.y" /* yacc.c:1646  */
    {push();}
#line 1831 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 117 "k_parse1.y" /* yacc.c:1646  */
    {exp_evaluate();}
#line 1837 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 120 "k_parse1.y" /* yacc.c:1646  */
    {push();}
#line 1843 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 120 "k_parse1.y" /* yacc.c:1646  */
    {exp_evaluate();}
#line 1849 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 125 "k_parse1.y" /* yacc.c:1646  */
    { check_decl();push();}
#line 1855 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 126 "k_parse1.y" /* yacc.c:1646  */
    { push(); }
#line 1861 "y.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 127 "k_parse1.y" /* yacc.c:1646  */
    { unary_minus(); }
#line 1867 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1871 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 138 "k_parse1.y" /* yacc.c:1906  */

#include <ctype.h>
#include"lex.yy.c"
int ltrack[200][20];
int lcount[200]={0};
int lab_no[200];
int lineno=0;struct store
{
int flag;
char op1[100];
int no;
} fetch[10000];
int count=0;
char st[1000][10];
int top=0;
int tmp_no=0;
char temp[8];
int lab_store[200];
int lnum=0;
int ltop=0;
int switch_store[1000];
int stop=0;
char dtype[10];
struct SymbolTable
{
char id[20];
char type[10];
}sym_store[10000];
int sym_count=0;
int main(int argc, char *argv[])
{
yyin = fopen(argv[1], "r");
if(!yyparse())
printf("\nParsing complete\n");
else
{
printf("\nParsing failed\n");
exit(0);
}
fclose(yyin);
outputcode();
return 0;
}
yyerror(char *s)
{
printf("Syntax Error In Line : %d : %s %s\n", yylineno, s, yytext );
}
push()
{
strcpy(st[++top],yytext);
}
fun1()
{
lnum++;

}
fun2()
{
}
fun3()
{
}
fun4()
{
}

push1(char ch[])
{
char ext[10];
strcpy(st[++top],"=");
strcpy(ext,st[top-1]);
strcpy(st[++top],ext);
strcpy(st[++top],ch);
}
unary_minus()
{
sprintf(temp,"t%d",tmp_no);fetch[lineno].flag=0;
strcpy(fetch[lineno].op1,temp);
strcat(fetch[lineno].op1,"=");
strcat(fetch[lineno].op1,"-");
strcat(fetch[lineno].op1,st[top]);
strcpy(st[top],temp);
tmp_no++;
lineno++;
}
exp_evaluate()
{
sprintf(temp,"t%d",tmp_no);
fetch[lineno].flag=0;
strcpy(fetch[lineno].op1,temp);
strcat(fetch[lineno].op1,"=");
strcat(fetch[lineno].op1,st[top-2]);
strcat(fetch[lineno].op1,st[top-1]);
strcat(fetch[lineno].op1,st[top]);
top-=2;
strcpy(st[top],temp);
tmp_no++;
lineno++;
}
exp_asgn_evaluate()
{
fetch[lineno].flag=0;
strcpy(fetch[lineno].op1,st[top-2]);
strcat(fetch[lineno].op1,"=");
strcat(fetch[lineno].op1,st[top]);
top-=3;
lineno++;
}
if_fun()
{
lnum++;
fetch[lineno].flag=1;
strcpy(fetch[lineno].op1,"if(not ");
strcat(fetch[lineno].op1,st[top]);
strcat(fetch[lineno].op1,") goto ");
ltrack[lnum][lcount[lnum]++]=lineno;
lab_store[++ltop]=lnum;
lineno++;
}
else_fun()
{
int x;
lnum++;
x=lab_store[ltop--];
fetch[lineno].flag=1;
strcpy(fetch[lineno].op1,"goto ");
ltrack[lnum][lcount[lnum]++]=lineno;
lineno++;
int u=0;
for(u=0;u<lcount[x];u++)
fetch[ltrack[x][u]].no=lineno;
lab_store[++ltop]=lnum;}
if_end()
{
int y;
y=lab_store[ltop--];
int u=0;
for(u=0;u<lcount[y];u++)
fetch[ltrack[y][u]].no=lineno;
top--;
}
while_begin()
{
lnum++;
lab_store[++ltop]=lnum;
lab_no[lnum]=lineno;
}
while_body()
{
lnum++;
fetch[lineno].flag=1;
strcpy(fetch[lineno].op1,"if(not ");
strcat(fetch[lineno].op1,st[top]);
strcat(fetch[lineno].op1,") goto ");
ltrack[lnum][lcount[lnum]++]=lineno;
lab_store[++ltop]=lnum;
lineno++;
}
while_end()
{
int x,y;
y=lab_store[ltop--];
x=lab_store[ltop--];
fetch[lineno].flag=1;
strcpy(fetch[lineno].op1,"goto ");
fetch[lineno].no=lab_no[x];
lineno++;
int u=0;
for(u=0;u<lcount[y];u++)
fetch[ltrack[y][u]].no=lineno;
top--;
}
switch_begin()
{
lnum++;
lab_store[++ltop]=lnum;
lnum++;
lab_store[++ltop]=lnum;
switch_store[++stop]=1;
}
switchcase_fun()
{
int x,y,ck;
ck=switch_store[stop--];
if(ck==1)
{
x=lab_store[ltop--];}
else if(ck==2)
{
y=lab_store[ltop--];
x=lab_store[ltop--];
}
int u=0;
for(u=0;u<lcount[x];u++)
fetch[ltrack[x][u]].no=lineno;
lnum++;
lab_store[++ltop]=lnum;
fetch[lineno].flag=1;
strcpy(fetch[lineno].op1,"if(");
strcat(fetch[lineno].op1,st[top]);
strcat(fetch[lineno].op1,"!=");
strcat(fetch[lineno].op1,yytext);
strcat(fetch[lineno].op1,") goto ");
ltrack[lab_store[ltop]][lcount[lab_store[ltop]]++]=lineno;
lineno++;
if(ck==2)
{
u=0;
for(u=0;u<lcount[y];u++)
fetch[ltrack[y][u]].no=lineno;
}
}
switchdefault_fun()
{
int x,y,ck;
ck=switch_store[stop--];
if(ck==1)
{
x=lab_store[ltop--];
}
else if(ck==2)
{
y=lab_store[ltop--];
x=lab_store[ltop--];
}
int u=0;
for(u=0;u<lcount[x];u++)
fetch[ltrack[x][u]].no=lineno;
lnum++;
lab_store[++ltop]=lnum;
if(ck==2)
{
u=0;
for(u=0;u<lcount[y];u++)
fetch[ltrack[y][u]].no=lineno;
}
}
break_fun()
{
switch_store[++stop]=1;
fetch[lineno].flag=1;
strcpy(fetch[lineno].op1,"goto ");ltrack[lab_store[ltop-1]][lcount[lab_store[ltop-1]]++]=lineno;
lineno++;
}
no_break_fun()
{
switch_store[++stop]=2;
lnum++;
lab_store[++ltop]=lnum;
fetch[lineno].flag=1;
strcpy(fetch[lineno].op1,"goto ");
ltrack[lab_store[ltop]][lcount[lab_store[ltop]]++]=lineno;
lineno++;
}
switch_end()
{
int x,y,ck;
ck=switch_store[stop--];
if(ck==1)
{
x=lab_store[ltop--];
}
else if(ck==2)
{
y=lab_store[ltop--];
x=lab_store[ltop--];
}
int u=0;
for(u=0;u<lcount[x];u++)
fetch[ltrack[x][u]].no=lineno;
if(ck==2)
{
u=0;
for(u=0;u<lcount[y];u++)
fetch[ltrack[y][u]].no=lineno;
}
x=lab_store[ltop--];
u=0;
for(u=0;u<lcount[x];u++)
fetch[ltrack[x][u]].no=lineno;
top--;
stop--;
}
set_datatype()
{
strcpy(dtype,yytext);
}
int is_predeclare(char temp[])
{
int i;
for(i=0;i<sym_count;i++)
{
if(!strcmp(sym_store[i].id,temp))
return 1;
}
return 0;}
var_decl()
{
char temp[20];
strcpy(temp,yytext);
if(is_predeclare(temp))
{
yyerror("Redeclaration of variable ");
exit(0);
}
else
{
strcpy(sym_store[sym_count].id,temp);
strcpy(sym_store[sym_count].type,dtype);
sym_count++;
}
}
check_decl()
{
char temp[20];
strcpy(temp,yytext);
int flag=0,i;
for(i=0;i<sym_count;i++)
{
if(!strcmp(sym_store[i].id,temp))
{
flag=1;
break;
}
}
if(!flag)
{
yyerror("Not Predeclared variable ");
exit(0);
}
}
outputcode()
{
int u=0;
for(u=0;u<lcount[lineno];u++)
{
fetch[ltrack[lineno][u]].no=lineno;
}
for(u=0;u<lineno;u++)
{
if(fetch[u].flag==0)
printf("%d: %s\n",u,fetch[u].op1);
else
{
printf("%d: %s ",u,fetch[u].op1);
printf("%d\n",fetch[u].no);
}
}
printf("%d: PGM END\n",lineno);
}
