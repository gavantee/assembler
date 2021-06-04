/* A Bison parser, made by GNU Bison 3.7.6.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30706

/* Bison version string.  */
#define YYBISON_VERSION "3.7.6"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/parser.y"

  #include <cstdio>
  #include <iostream>
  #include <string>
  #include <vector>
  #include <cstring>

  #include "parser.h"
  #include "code.h"

  using namespace std;

  extern int yylex();
  extern int yyparse();
  extern FILE *yyin;

  int pc = 0;
  extern Code code;
  string section = "NO_SEC";

  void yyerror(const char *s);
	unsigned short reverse_bytes(unsigned short i);

#line 95 "src/bison.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "bison.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUMBER = 3,                     /* NUMBER  */
  YYSYMBOL_PLUS = 4,                       /* PLUS  */
  YYSYMBOL_MINUS = 5,                      /* MINUS  */
  YYSYMBOL_COLON = 6,                      /* COLON  */
  YYSYMBOL_COMMA = 7,                      /* COMMA  */
  YYSYMBOL_LPAREN = 8,                     /* LPAREN  */
  YYSYMBOL_RPAREN = 9,                     /* RPAREN  */
  YYSYMBOL_TIMES = 10,                     /* TIMES  */
  YYSYMBOL_DOLLAR = 11,                    /* DOLLAR  */
  YYSYMBOL_PERCENT = 12,                   /* PERCENT  */
  YYSYMBOL_REG = 13,                       /* REG  */
  YYSYMBOL_HALT = 14,                      /* HALT  */
  YYSYMBOL_IRET = 15,                      /* IRET  */
  YYSYMBOL_RET = 16,                       /* RET  */
  YYSYMBOL_CALL = 17,                      /* CALL  */
  YYSYMBOL_JMP = 18,                       /* JMP  */
  YYSYMBOL_JEQ = 19,                       /* JEQ  */
  YYSYMBOL_JNE = 20,                       /* JNE  */
  YYSYMBOL_JGT = 21,                       /* JGT  */
  YYSYMBOL_PUSH = 22,                      /* PUSH  */
  YYSYMBOL_POP = 23,                       /* POP  */
  YYSYMBOL_INT = 24,                       /* INT  */
  YYSYMBOL_XCHG = 25,                      /* XCHG  */
  YYSYMBOL_MOV = 26,                       /* MOV  */
  YYSYMBOL_ADD = 27,                       /* ADD  */
  YYSYMBOL_SUB = 28,                       /* SUB  */
  YYSYMBOL_MUL = 29,                       /* MUL  */
  YYSYMBOL_DIV = 30,                       /* DIV  */
  YYSYMBOL_CMP = 31,                       /* CMP  */
  YYSYMBOL_NOT = 32,                       /* NOT  */
  YYSYMBOL_AND = 33,                       /* AND  */
  YYSYMBOL_OR = 34,                        /* OR  */
  YYSYMBOL_XOR = 35,                       /* XOR  */
  YYSYMBOL_TEST = 36,                      /* TEST  */
  YYSYMBOL_SHL = 37,                       /* SHL  */
  YYSYMBOL_SHR = 38,                       /* SHR  */
  YYSYMBOL_LDR = 39,                       /* LDR  */
  YYSYMBOL_STR = 40,                       /* STR  */
  YYSYMBOL_GLOBAL = 41,                    /* GLOBAL  */
  YYSYMBOL_EXTERN = 42,                    /* EXTERN  */
  YYSYMBOL_SECTION = 43,                   /* SECTION  */
  YYSYMBOL_WORD = 44,                      /* WORD  */
  YYSYMBOL_SKIP = 45,                      /* SKIP  */
  YYSYMBOL_EQU = 46,                       /* EQU  */
  YYSYMBOL_END = 47,                       /* END  */
  YYSYMBOL_SYMBOL = 48,                    /* SYMBOL  */
  YYSYMBOL_YYACCEPT = 49,                  /* $accept  */
  YYSYMBOL_program = 50,                   /* program  */
  YYSYMBOL_line = 51,                      /* line  */
  YYSYMBOL_label = 52,                     /* label  */
  YYSYMBOL_inst_dir = 53,                  /* inst_dir  */
  YYSYMBOL_directive = 54,                 /* directive  */
  YYSYMBOL_instruction = 55,               /* instruction  */
  YYSYMBOL_instr_0 = 56,                   /* instr_0  */
  YYSYMBOL_instr_jmp = 57,                 /* instr_jmp  */
  YYSYMBOL_instr_1 = 58,                   /* instr_1  */
  YYSYMBOL_instr_2 = 59,                   /* instr_2  */
  YYSYMBOL_instr_mem = 60,                 /* instr_mem  */
  YYSYMBOL_operand_jmp = 61,               /* operand_jmp  */
  YYSYMBOL_operand = 62,                   /* operand  */
  YYSYMBOL_sym_list = 63,                  /* sym_list  */
  YYSYMBOL_lit = 64,                       /* lit  */
  YYSYMBOL_sym_lit = 65,                   /* sym_lit  */
  YYSYMBOL_sym_lit_list = 66               /* sym_lit_list  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  62
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   148

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  74
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  113

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   303


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      45,    46,    47,    48
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    53,    53,    54,    57,    58,    59,    62,    65,    66,
      69,    72,    75,    78,    87,    88,    89,    92,    94,    97,
     100,   103,   107,   111,   117,   118,   119,   122,   123,   124,
     125,   126,   128,   129,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   146,   147,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   172,   174,   176,   179,
     180,   183,   184,   189,   191
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NUMBER", "PLUS",
  "MINUS", "COLON", "COMMA", "LPAREN", "RPAREN", "TIMES", "DOLLAR",
  "PERCENT", "REG", "HALT", "IRET", "RET", "CALL", "JMP", "JEQ", "JNE",
  "JGT", "PUSH", "POP", "INT", "XCHG", "MOV", "ADD", "SUB", "MUL", "DIV",
  "CMP", "NOT", "AND", "OR", "XOR", "TEST", "SHL", "SHR", "LDR", "STR",
  "GLOBAL", "EXTERN", "SECTION", "WORD", "SKIP", "EQU", "END", "SYMBOL",
  "$accept", "program", "line", "label", "inst_dir", "directive",
  "instruction", "instr_0", "instr_jmp", "instr_1", "instr_2", "instr_mem",
  "operand_jmp", "operand", "sym_list", "lit", "sym_lit", "sym_lit_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303
};
#endif

#define YYPACT_NINF (-41)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      62,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -12,
      -6,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,
     -41,   -41,   -41,   -41,   -41,   -41,   -41,   -40,   -40,   -38,
      23,    47,   -33,   -41,    36,    22,    62,    97,   -41,   -41,
     -41,   -41,    13,    20,    30,    41,   -41,   -41,   -41,    38,
      38,   -41,   -41,    52,    53,   -41,   -41,   -41,    51,   -41,
      55,   -41,   -41,   -41,   -41,    16,    11,   -41,   -41,   -41,
     -41,    56,    58,    18,   -41,   -41,    23,    47,    54,   -41,
     -41,   -41,   -41,    57,     1,   -41,   -41,   -41,    32,   -41,
      59,    27,    25,   -41,   -41,   -41,   -41,    -1,   -41,    65,
      35,   -41,   -41,   -41,    79,   -41,     0,   -41,   114,   -41,
     136,   -41,   -41
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    24,    25,    26,    27,    28,    29,    30,    31,     0,
       0,    32,    34,    35,    36,    37,    38,    39,    33,    40,
      41,    42,    43,    44,    45,    46,    47,     0,     0,     0,
       0,     0,     0,    16,     0,     0,     2,     4,     5,     9,
       8,    17,     0,     0,     0,     0,    22,    23,    66,    10,
      11,    12,    68,     0,     0,    71,    72,    73,    13,    14,
       0,     7,     1,     3,     6,     0,     0,    49,    18,    48,
      19,     0,     0,     0,    69,    70,     0,     0,     0,    53,
      52,    51,    50,     0,     0,    67,    74,    15,     0,    20,
       0,     0,     0,    62,    60,    21,    59,     0,    54,     0,
       0,    58,    57,    61,     0,    55,     0,    63,     0,    56,
       0,    64,    65
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -41,   110,   -41,   -41,    31,   -41,   -41,   -41,   -41,   -41,
     -41,   -41,   -41,   -41,   119,   -31,    72,   -41
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    68,    95,    49,    56,    57,    58
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      59,    46,    74,    74,    52,    53,    54,    47,    48,    90,
      51,    69,    91,    92,    93,    60,    52,    53,    54,    52,
      53,    54,    62,    65,    78,    66,    52,    53,    54,    79,
      52,    53,    54,    70,    81,    52,    97,    54,    52,   106,
      54,    98,    61,    71,   107,    73,    87,   104,   110,    94,
      52,    53,    54,    96,    72,    74,    75,    99,    76,    82,
     102,    67,    77,    83,    80,    84,    85,    88,    64,   108,
      89,    55,   100,   103,   105,   101,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,   109,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,   111,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,   112,    63,    50,    86
};

static const yytype_int8 yycheck[] =
{
      31,    13,     3,     3,     3,     4,     5,    13,    48,     8,
      48,    42,    11,    12,    13,    48,     3,     4,     5,     3,
       4,     5,     0,    10,     8,    12,     3,     4,     5,    13,
       3,     4,     5,    13,    65,     3,     4,     5,     3,     4,
       5,     9,     6,    13,     9,     7,    77,    48,    48,    48,
       3,     4,     5,    84,    13,     3,     3,    88,     7,    48,
      91,    48,     7,     7,    48,     7,    48,    13,    37,   100,
      13,    48,    13,    48,     9,    48,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,     9,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,     9,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,     9,    36,    28,    76
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    13,    13,    48,    63,
      63,    48,     3,     4,     5,    48,    64,    65,    66,    64,
      48,     6,     0,    50,    53,    10,    12,    48,    61,    64,
      13,    13,    13,     7,     3,     3,     7,     7,     8,    13,
      48,    64,    48,     7,     7,    48,    65,    64,    13,    13,
       8,    11,    12,    13,    48,    62,    64,     4,     9,    64,
      13,    48,    64,    48,    48,     9,     4,     9,    64,     9,
      48,     9,     9
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    50,    51,    51,    51,    52,    53,    53,
      54,    54,    54,    54,    54,    54,    54,    55,    55,    55,
      55,    55,    55,    55,    56,    56,    56,    57,    57,    57,
      57,    57,    58,    58,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    60,    60,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    63,    63,    64,    64,
      64,    65,    65,    66,    66
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     2,     2,     1,     1,
       2,     2,     2,     2,     2,     4,     1,     1,     2,     2,
       4,     4,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     2,     2,     4,     5,     6,     2,     2,     1,
       1,     2,     1,     3,     4,     5,     1,     3,     1,     2,
       2,     1,     1,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 7: /* label: SYMBOL COLON  */
#line 62 "src/parser.y"
                  { code.addSymbol((yyvsp[-1].sval), section, pc); }
#line 1241 "src/bison.cpp"
    break;

  case 10: /* directive: GLOBAL sym_list  */
#line 69 "src/parser.y"
                        {
			  for (string s : *((yyvsp[0].str_list)))
			  	code.addSymbol(s, section, new vector<Location>(), true); }
#line 1249 "src/bison.cpp"
    break;

  case 11: /* directive: EXTERN sym_list  */
#line 72 "src/parser.y"
                          {
			    for (string s : *((yyvsp[0].str_list))) {
			      code.addSymbol(s, "EXT", new vector<Location>(), true); }}
#line 1257 "src/bison.cpp"
    break;

  case 12: /* directive: SECTION SYMBOL  */
#line 75 "src/parser.y"
                         { pc = 0;
	                   section = (yyvsp[0].sval);
	                   code.addSymbol((yyvsp[0].sval), section, pc, true);}
#line 1265 "src/bison.cpp"
    break;

  case 13: /* directive: WORD sym_lit_list  */
#line 78 "src/parser.y"
                            {
		for (string s : *((yyvsp[0].str_list))) {
		  int tmp;
		  if (s[0] >= '0' && s[0] <= '9') tmp = stoi(s, nullptr, 0);
		  else tmp = code.resolveSymbol(s, section, pc);
		  pc += 2;
		  code.addInt(tmp, 2);
		}
	}
#line 1279 "src/bison.cpp"
    break;

  case 14: /* directive: SKIP lit  */
#line 87 "src/parser.y"
                   { pc += (yyvsp[0].ival); code.addInt(0, (yyvsp[0].ival)); }
#line 1285 "src/bison.cpp"
    break;

  case 15: /* directive: EQU SYMBOL COMMA lit  */
#line 88 "src/parser.y"
                               { code.addSymbol((yyvsp[-2].sval), "ABS", (yyvsp[0].ival)); }
#line 1291 "src/bison.cpp"
    break;

  case 17: /* instruction: instr_0  */
#line 92 "src/parser.y"
                { code.addByte((yyvsp[0].ival));
		pc += 1; }
#line 1298 "src/bison.cpp"
    break;

  case 18: /* instruction: instr_jmp operand_jmp  */
#line 94 "src/parser.y"
                                { code.addByte((yyvsp[-1].ival));
    code.addInt((yyvsp[0].op)->val, (yyvsp[0].op)->length);
		pc += 1 + (yyvsp[0].op)->length; }
#line 1306 "src/bison.cpp"
    break;

  case 19: /* instruction: instr_1 REG  */
#line 97 "src/parser.y"
                      { code.addByte((yyvsp[-1].ival));
		code.addByte(((yyvsp[0].ival) << 4) + 0xF);
		pc += 2; }
#line 1314 "src/bison.cpp"
    break;

  case 20: /* instruction: instr_2 REG COMMA REG  */
#line 100 "src/parser.y"
                                { code.addByte((yyvsp[-3].ival));
		code.addByte(((yyvsp[-2].ival) << 4) + (yyvsp[0].ival));
		pc += 2; }
#line 1322 "src/bison.cpp"
    break;

  case 21: /* instruction: instr_mem REG COMMA operand  */
#line 103 "src/parser.y"
                                      { code.addByte((yyvsp[-3].ival));
		int tmp = ((yyvsp[-2].ival) << ((yyvsp[0].op)->length * 8 - 4)) + (yyvsp[0].op)->val;
		code.addInt(tmp, (yyvsp[0].op)->length);
		pc += (yyvsp[0].op)->length + 1; }
#line 1331 "src/bison.cpp"
    break;

  case 22: /* instruction: PUSH REG  */
#line 107 "src/parser.y"
                   { code.addByte(0xB0);
		     code.addByte(((yyvsp[0].ival) << 4) + 6);
		     code.addByte((1 << 4) + 2);
		     pc += 3; }
#line 1340 "src/bison.cpp"
    break;

  case 23: /* instruction: POP REG  */
#line 111 "src/parser.y"
                   { code.addByte(0xA0);
		     code.addByte(((yyvsp[0].ival) << 4) + 6);
		     code.addByte((4 << 4) + 2);
		     pc += 3; }
#line 1349 "src/bison.cpp"
    break;

  case 24: /* instr_0: HALT  */
#line 117 "src/parser.y"
                { (yyval.ival) = 0x00; }
#line 1355 "src/bison.cpp"
    break;

  case 25: /* instr_0: IRET  */
#line 118 "src/parser.y"
                { (yyval.ival) = 0x20; }
#line 1361 "src/bison.cpp"
    break;

  case 26: /* instr_0: RET  */
#line 119 "src/parser.y"
                { (yyval.ival) = 0x40; }
#line 1367 "src/bison.cpp"
    break;

  case 27: /* instr_jmp: CALL  */
#line 122 "src/parser.y"
                { (yyval.ival) = 0x30; }
#line 1373 "src/bison.cpp"
    break;

  case 28: /* instr_jmp: JMP  */
#line 123 "src/parser.y"
                { (yyval.ival) = 0x50; }
#line 1379 "src/bison.cpp"
    break;

  case 29: /* instr_jmp: JEQ  */
#line 124 "src/parser.y"
                { (yyval.ival) = 0x51; }
#line 1385 "src/bison.cpp"
    break;

  case 30: /* instr_jmp: JNE  */
#line 125 "src/parser.y"
                { (yyval.ival) = 0x52; }
#line 1391 "src/bison.cpp"
    break;

  case 31: /* instr_jmp: JGT  */
#line 126 "src/parser.y"
                { (yyval.ival) = 0x53; }
#line 1397 "src/bison.cpp"
    break;

  case 32: /* instr_1: INT  */
#line 128 "src/parser.y"
                { (yyval.ival) = 0x10; }
#line 1403 "src/bison.cpp"
    break;

  case 33: /* instr_1: NOT  */
#line 129 "src/parser.y"
                { (yyval.ival) = 0x80; }
#line 1409 "src/bison.cpp"
    break;

  case 34: /* instr_2: XCHG  */
#line 132 "src/parser.y"
                { (yyval.ival) = 0x60; }
#line 1415 "src/bison.cpp"
    break;

  case 35: /* instr_2: ADD  */
#line 133 "src/parser.y"
                { (yyval.ival) = 0x70; }
#line 1421 "src/bison.cpp"
    break;

  case 36: /* instr_2: SUB  */
#line 134 "src/parser.y"
                { (yyval.ival) = 0x71; }
#line 1427 "src/bison.cpp"
    break;

  case 37: /* instr_2: MUL  */
#line 135 "src/parser.y"
                { (yyval.ival) = 0x72; }
#line 1433 "src/bison.cpp"
    break;

  case 38: /* instr_2: DIV  */
#line 136 "src/parser.y"
                { (yyval.ival) = 0x73; }
#line 1439 "src/bison.cpp"
    break;

  case 39: /* instr_2: CMP  */
#line 137 "src/parser.y"
                { (yyval.ival) = 0x74; }
#line 1445 "src/bison.cpp"
    break;

  case 40: /* instr_2: AND  */
#line 138 "src/parser.y"
                { (yyval.ival) = 0x81; }
#line 1451 "src/bison.cpp"
    break;

  case 41: /* instr_2: OR  */
#line 139 "src/parser.y"
                  { (yyval.ival) = 0x82; }
#line 1457 "src/bison.cpp"
    break;

  case 42: /* instr_2: XOR  */
#line 140 "src/parser.y"
                { (yyval.ival) = 0x83; }
#line 1463 "src/bison.cpp"
    break;

  case 43: /* instr_2: TEST  */
#line 141 "src/parser.y"
                { (yyval.ival) = 0x84; }
#line 1469 "src/bison.cpp"
    break;

  case 44: /* instr_2: SHL  */
#line 142 "src/parser.y"
                { (yyval.ival) = 0x90; }
#line 1475 "src/bison.cpp"
    break;

  case 45: /* instr_2: SHR  */
#line 143 "src/parser.y"
                { (yyval.ival) = 0x91; }
#line 1481 "src/bison.cpp"
    break;

  case 46: /* instr_mem: LDR  */
#line 146 "src/parser.y"
                  { (yyval.ival) = 0xA0; }
#line 1487 "src/bison.cpp"
    break;

  case 47: /* instr_mem: STR  */
#line 147 "src/parser.y"
                { (yyval.ival) = 0xB0; }
#line 1493 "src/bison.cpp"
    break;

  case 48: /* operand_jmp: lit  */
#line 150 "src/parser.y"
            { (yyval.op) = new Op((0xF << 28) + (0 << 16) + reverse_bytes((yyvsp[0].ival)), 4) ;}
#line 1499 "src/bison.cpp"
    break;

  case 49: /* operand_jmp: SYMBOL  */
#line 151 "src/parser.y"
                 { (yyval.op) = new Op((0xF << 28) + (0 << 16) + reverse_bytes(code.resolveSymbol((yyvsp[0].sval), section, pc + 3)), 4); }
#line 1505 "src/bison.cpp"
    break;

  case 50: /* operand_jmp: PERCENT SYMBOL  */
#line 152 "src/parser.y"
                         { (yyval.op) = new Op((0xF << 28) + (7 << 24) + (5 << 16) + reverse_bytes(- 2 + code.resolveSymbol((yyvsp[0].sval), section, pc + 3, true) & 0xffff), 4); }
#line 1511 "src/bison.cpp"
    break;

  case 51: /* operand_jmp: TIMES lit  */
#line 153 "src/parser.y"
                    { (yyval.op) = new Op((0xF << 28) + (4 << 16) + reverse_bytes((yyvsp[0].ival)), 4); }
#line 1517 "src/bison.cpp"
    break;

  case 52: /* operand_jmp: TIMES SYMBOL  */
#line 154 "src/parser.y"
                       { (yyval.op) = new Op((0xF << 28) + (4 << 16) + reverse_bytes(code.resolveSymbol((yyvsp[0].sval), section, pc + 3)), 4); }
#line 1523 "src/bison.cpp"
    break;

  case 53: /* operand_jmp: TIMES REG  */
#line 155 "src/parser.y"
                    { (yyval.op) = new Op((0xF << 12) + ((yyvsp[0].ival) << 8) + (1 << 0), 2); }
#line 1529 "src/bison.cpp"
    break;

  case 54: /* operand_jmp: TIMES LPAREN REG RPAREN  */
#line 156 "src/parser.y"
                                  { (yyval.op) = new Op((0xF << 12) + ((yyvsp[-1].ival) << 8) + (2 << 0), 2); }
#line 1535 "src/bison.cpp"
    break;

  case 55: /* operand_jmp: TIMES LPAREN REG lit RPAREN  */
#line 157 "src/parser.y"
                                      { (yyval.op) = new Op((0xF << 28) + ((yyvsp[-2].ival) << 24) + (3 << 16) + reverse_bytes((yyvsp[-1].ival)), 4); }
#line 1541 "src/bison.cpp"
    break;

  case 56: /* operand_jmp: TIMES LPAREN REG PLUS SYMBOL RPAREN  */
#line 158 "src/parser.y"
                                              { (yyval.op) = new Op((0xF << 28) + ((yyvsp[-3].ival) << 24) + (3 << 16) + reverse_bytes(code.resolveSymbol((yyvsp[-1].sval), section, pc + 3)), 4); }
#line 1547 "src/bison.cpp"
    break;

  case 57: /* operand: DOLLAR lit  */
#line 161 "src/parser.y"
                   { (yyval.op) = new Op(reverse_bytes((yyvsp[0].ival)), 4); }
#line 1553 "src/bison.cpp"
    break;

  case 58: /* operand: DOLLAR SYMBOL  */
#line 162 "src/parser.y"
                  { (yyval.op) = new Op(reverse_bytes(code.resolveSymbol((yyvsp[0].sval), section, pc + 3)), 4); }
#line 1559 "src/bison.cpp"
    break;

  case 59: /* operand: lit  */
#line 163 "src/parser.y"
        { (yyval.op) = new Op((4 << 16) + reverse_bytes((yyvsp[0].ival)), 4); }
#line 1565 "src/bison.cpp"
    break;

  case 60: /* operand: SYMBOL  */
#line 164 "src/parser.y"
                 { (yyval.op) = new Op((4 << 16) + reverse_bytes(code.resolveSymbol((yyvsp[0].sval), section, pc + 3)), 4); }
#line 1571 "src/bison.cpp"
    break;

  case 61: /* operand: PERCENT SYMBOL  */
#line 165 "src/parser.y"
                         { (yyval.op) = new Op((7 << 24) + (3 << 16)  + reverse_bytes(- 2 + code.resolveSymbol((yyvsp[0].sval), section, pc + 3, true) & 0xffff), 4); }
#line 1577 "src/bison.cpp"
    break;

  case 62: /* operand: REG  */
#line 166 "src/parser.y"
              { (yyval.op) = new Op(((yyvsp[0].ival) << 8) + (1 << 0), 2); }
#line 1583 "src/bison.cpp"
    break;

  case 63: /* operand: LPAREN REG RPAREN  */
#line 167 "src/parser.y"
                            { (yyval.op) = new Op(((yyvsp[-1].ival) << 8) + (2 << 0), 2); }
#line 1589 "src/bison.cpp"
    break;

  case 64: /* operand: LPAREN REG lit RPAREN  */
#line 168 "src/parser.y"
                                { (yyval.op) = new Op(((yyvsp[-2].ival) << 24) + (3 << 16) + reverse_bytes((yyvsp[-1].ival)), 4); }
#line 1595 "src/bison.cpp"
    break;

  case 65: /* operand: LPAREN REG PLUS SYMBOL RPAREN  */
#line 169 "src/parser.y"
                                        { (yyval.op) = new Op(((yyvsp[-3].ival) << 24) + (3 << 16) + reverse_bytes(code.resolveSymbol((yyvsp[-1].sval), section, pc + 3)), 4); }
#line 1601 "src/bison.cpp"
    break;

  case 66: /* sym_list: SYMBOL  */
#line 172 "src/parser.y"
               { (yyval.str_list) = new vector<string>();
		 (yyval.str_list)->push_back((yyvsp[0].sval)); }
#line 1608 "src/bison.cpp"
    break;

  case 67: /* sym_list: sym_list COMMA SYMBOL  */
#line 174 "src/parser.y"
                                { (yyval.str_list)->push_back((yyvsp[0].sval)); }
#line 1614 "src/bison.cpp"
    break;

  case 68: /* lit: NUMBER  */
#line 176 "src/parser.y"
            { (yyval.ival) = (yyvsp[0].ival); if ((yyvsp[0].ival) > 0xffff) {
	 printf("number %d too large\n", (yyvsp[0].ival));
	 exit(1); }}
#line 1622 "src/bison.cpp"
    break;

  case 69: /* lit: PLUS NUMBER  */
#line 179 "src/parser.y"
                       { (yyval.ival) = (yyvsp[0].ival); }
#line 1628 "src/bison.cpp"
    break;

  case 70: /* lit: MINUS NUMBER  */
#line 180 "src/parser.y"
                        { (yyval.ival) = (1 << 16) - (yyvsp[0].ival); }
#line 1634 "src/bison.cpp"
    break;

  case 71: /* sym_lit: SYMBOL  */
#line 183 "src/parser.y"
               { (yyval.sval) = (yyvsp[0].sval); }
#line 1640 "src/bison.cpp"
    break;

  case 72: /* sym_lit: lit  */
#line 184 "src/parser.y"
               { (yyval.sval) = (char *) calloc(7, sizeof(char));
		 snprintf((yyval.sval), 6, "%d", (yyvsp[0].ival));
		 (yyval.sval)[6] = '\0'; }
#line 1648 "src/bison.cpp"
    break;

  case 73: /* sym_lit_list: sym_lit  */
#line 189 "src/parser.y"
                { (yyval.str_list) = new vector<string>();
		  (yyval.str_list)->push_back((yyvsp[0].sval)); }
#line 1655 "src/bison.cpp"
    break;

  case 74: /* sym_lit_list: sym_lit_list COMMA sym_lit  */
#line 191 "src/parser.y"
                                     {(yyval.str_list)->push_back((yyvsp[0].sval)); }
#line 1661 "src/bison.cpp"
    break;


#line 1665 "src/bison.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

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


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 193 "src/parser.y"


unsigned short reverse_bytes(unsigned short i) {
  return ((i & 0xff) << 8) + ((i & 0xff00) >> 8);
}
void yyerror(const char *s) {
  cout << "Parse error:" << s << endl;
  exit(-1);
}
