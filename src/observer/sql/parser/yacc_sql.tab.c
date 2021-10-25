/* A Bison parser, made by GNU Bison 3.8.2.  */

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
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.h"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ParserContext {
  Query * ssql;
  size_t select_length;
  size_t condition_length;
  size_t from_length;
  size_t value_length;
  Value values[MAX_NUM];
  Condition conditions[MAX_NUM];
  CompOp comp;
	char id[MAX_NUM];
} ParserContext;

//获取子串
char *substr(const char *s,int n1,int n2)/*从s中提取下标为n1~n2的字符组成一个新字符串，然后返回这个新串的首地址*/
{
  char *sp = malloc(sizeof(char) * (n2 - n1 + 2));
  int i, j = 0;
  for (i = n1; i <= n2; i++) {
    sp[j++] = s[i];
  }
  sp[j] = 0;
  return sp;
}

void yyerror(yyscan_t scanner, const char *str)
{
  ParserContext *context = (ParserContext *)(yyget_extra(scanner));
  query_reset(context->ssql);
  context->ssql->flag = SCF_ERROR;
  context->condition_length = 0;
  context->from_length = 0;
  context->select_length = 0;
  context->value_length = 0;
  context->ssql->sstr.insertion.values_num = 0;
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)


#line 128 "yacc_sql.tab.c"

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

#include "yacc_sql.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_CREATE = 4,                     /* CREATE  */
  YYSYMBOL_DROP = 5,                       /* DROP  */
  YYSYMBOL_TABLE = 6,                      /* TABLE  */
  YYSYMBOL_TABLES = 7,                     /* TABLES  */
  YYSYMBOL_INDEX = 8,                      /* INDEX  */
  YYSYMBOL_SELECT = 9,                     /* SELECT  */
  YYSYMBOL_COUNT = 10,                     /* COUNT  */
  YYSYMBOL_MAX = 11,                       /* MAX  */
  YYSYMBOL_MIN = 12,                       /* MIN  */
  YYSYMBOL_AVG = 13,                       /* AVG  */
  YYSYMBOL_DESC = 14,                      /* DESC  */
  YYSYMBOL_SHOW = 15,                      /* SHOW  */
  YYSYMBOL_SYNC = 16,                      /* SYNC  */
  YYSYMBOL_INSERT = 17,                    /* INSERT  */
  YYSYMBOL_DELETE = 18,                    /* DELETE  */
  YYSYMBOL_UPDATE = 19,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 20,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 21,                    /* RBRACE  */
  YYSYMBOL_COMMA = 22,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 23,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 24,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 25,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 26,                     /* INT_T  */
  YYSYMBOL_STRING_T = 27,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 28,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 29,                    /* DATE_T  */
  YYSYMBOL_HELP = 30,                      /* HELP  */
  YYSYMBOL_EXIT = 31,                      /* EXIT  */
  YYSYMBOL_DOT = 32,                       /* DOT  */
  YYSYMBOL_INTO = 33,                      /* INTO  */
  YYSYMBOL_VALUES = 34,                    /* VALUES  */
  YYSYMBOL_FROM = 35,                      /* FROM  */
  YYSYMBOL_WHERE = 36,                     /* WHERE  */
  YYSYMBOL_AND = 37,                       /* AND  */
  YYSYMBOL_SET = 38,                       /* SET  */
  YYSYMBOL_ON = 39,                        /* ON  */
  YYSYMBOL_LOAD = 40,                      /* LOAD  */
  YYSYMBOL_DATA = 41,                      /* DATA  */
  YYSYMBOL_INFILE = 42,                    /* INFILE  */
  YYSYMBOL_EQ = 43,                        /* EQ  */
  YYSYMBOL_LT = 44,                        /* LT  */
  YYSYMBOL_GT = 45,                        /* GT  */
  YYSYMBOL_LE = 46,                        /* LE  */
  YYSYMBOL_GE = 47,                        /* GE  */
  YYSYMBOL_NE = 48,                        /* NE  */
  YYSYMBOL_NUMBER = 49,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 50,                     /* FLOAT  */
  YYSYMBOL_ID = 51,                        /* ID  */
  YYSYMBOL_PATH = 52,                      /* PATH  */
  YYSYMBOL_SSS = 53,                       /* SSS  */
  YYSYMBOL_STAR = 54,                      /* STAR  */
  YYSYMBOL_STRING_V = 55,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 56,                  /* $accept  */
  YYSYMBOL_commands = 57,                  /* commands  */
  YYSYMBOL_command = 58,                   /* command  */
  YYSYMBOL_exit = 59,                      /* exit  */
  YYSYMBOL_help = 60,                      /* help  */
  YYSYMBOL_sync = 61,                      /* sync  */
  YYSYMBOL_begin = 62,                     /* begin  */
  YYSYMBOL_commit = 63,                    /* commit  */
  YYSYMBOL_rollback = 64,                  /* rollback  */
  YYSYMBOL_drop_table = 65,                /* drop_table  */
  YYSYMBOL_show_tables = 66,               /* show_tables  */
  YYSYMBOL_desc_table = 67,                /* desc_table  */
  YYSYMBOL_create_index = 68,              /* create_index  */
  YYSYMBOL_drop_index = 69,                /* drop_index  */
  YYSYMBOL_create_table = 70,              /* create_table  */
  YYSYMBOL_attr_def_list = 71,             /* attr_def_list  */
  YYSYMBOL_attr_def = 72,                  /* attr_def  */
  YYSYMBOL_number = 73,                    /* number  */
  YYSYMBOL_type = 74,                      /* type  */
  YYSYMBOL_ID_get = 75,                    /* ID_get  */
  YYSYMBOL_insert = 76,                    /* insert  */
  YYSYMBOL_values_list = 77,               /* values_list  */
  YYSYMBOL_values = 78,                    /* values  */
  YYSYMBOL_value_list = 79,                /* value_list  */
  YYSYMBOL_value = 80,                     /* value  */
  YYSYMBOL_delete = 81,                    /* delete  */
  YYSYMBOL_update = 82,                    /* update  */
  YYSYMBOL_select = 83,                    /* select  */
  YYSYMBOL_select_attr = 84,               /* select_attr  */
  YYSYMBOL_attr_list = 85,                 /* attr_list  */
  YYSYMBOL_agg_list = 86,                  /* agg_list  */
  YYSYMBOL_agg_value = 87,                 /* agg_value  */
  YYSYMBOL_rel_list = 88,                  /* rel_list  */
  YYSYMBOL_where = 89,                     /* where  */
  YYSYMBOL_condition_list = 90,            /* condition_list  */
  YYSYMBOL_condition = 91,                 /* condition  */
  YYSYMBOL_comOp = 92,                     /* comOp  */
  YYSYMBOL_load_data = 93                  /* load_data  */
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
typedef yytype_int16 yy_state_t;

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

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   275

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  105
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  263

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   310


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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   137,   137,   139,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   163,   168,   173,   179,   185,   191,   197,   203,   209,
     216,   224,   231,   240,   242,   246,   257,   272,   275,   276,
     277,   278,   281,   290,   295,   297,   301,   306,   307,   309,
     312,   315,   322,   332,   342,   361,   366,   371,   376,   382,
     387,   392,   397,   402,   412,   422,   432,   442,   453,   455,
     462,   469,   474,   476,   481,   486,   491,   496,   506,   516,
     526,   536,   549,   557,   564,   570,   577,   579,   583,   585,
     589,   591,   596,   617,   637,   657,   679,   700,   721,   743,
     744,   745,   746,   747,   748,   752
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
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "CREATE",
  "DROP", "TABLE", "TABLES", "INDEX", "SELECT", "COUNT", "MAX", "MIN",
  "AVG", "DESC", "SHOW", "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE",
  "RBRACE", "COMMA", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T",
  "STRING_T", "FLOAT_T", "DATE_T", "HELP", "EXIT", "DOT", "INTO", "VALUES",
  "FROM", "WHERE", "AND", "SET", "ON", "LOAD", "DATA", "INFILE", "EQ",
  "LT", "GT", "LE", "GE", "NE", "NUMBER", "FLOAT", "ID", "PATH", "SSS",
  "STAR", "STRING_V", "$accept", "commands", "command", "exit", "help",
  "sync", "begin", "commit", "rollback", "drop_table", "show_tables",
  "desc_table", "create_index", "drop_index", "create_table",
  "attr_def_list", "attr_def", "number", "type", "ID_get", "insert",
  "values_list", "values", "value_list", "value", "delete", "update",
  "select", "select_attr", "attr_list", "agg_list", "agg_value",
  "rel_list", "where", "condition_list", "condition", "comOp", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-118)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -118,    77,  -118,    91,   121,     3,   -20,     0,    38,    -1,
      17,     4,    53,    58,    59,    63,    64,    27,  -118,  -118,
    -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,
    -118,  -118,  -118,  -118,  -118,  -118,    23,    33,    34,    52,
      92,    95,   111,   116,     1,    82,   102,   139,   153,  -118,
     106,   127,   124,  -118,  -118,  -118,  -118,  -118,   125,   152,
     140,   177,   178,   -14,    -6,     9,    29,   131,    22,  -118,
    -118,   132,  -118,  -118,   150,   149,   135,   134,   137,   138,
    -118,  -118,  -118,  -118,   158,  -118,   170,   160,   172,   162,
     174,   165,   175,     2,    82,    82,   176,   179,    90,   197,
     159,   168,  -118,   181,    61,   184,    62,   183,   155,   183,
     156,   183,   157,   183,    70,  -118,  -118,  -118,   161,   149,
     -11,   187,  -118,  -118,   -26,  -118,   -18,   173,  -118,   -11,
     205,   137,   192,  -118,  -118,  -118,  -118,   194,   166,   195,
     198,   164,  -118,   199,  -118,   200,  -118,   201,  -118,    82,
      82,   176,   212,   196,   179,   220,   180,  -118,  -118,  -118,
    -118,  -118,  -118,   110,   115,    90,  -118,   149,   182,   181,
     221,   185,   204,   183,   183,   206,   207,   208,   209,   183,
     183,   183,  -118,  -118,  -118,  -118,   -11,   211,   187,  -118,
     -18,  -118,  -118,   203,  -118,   173,   227,   233,  -118,  -118,
    -118,   216,   235,  -118,  -118,    60,    69,    84,   104,  -118,
    -118,  -118,   196,  -118,  -118,   120,   188,  -118,  -118,  -118,
    -118,  -118,   210,   219,   213,   222,   214,   223,   215,   228,
    -118,   218,  -118,  -118,    71,   183,   190,   183,   202,   183,
     217,   183,   224,   230,   231,  -118,   234,  -118,   236,  -118,
     237,  -118,  -118,   183,   183,   183,   183,   183,  -118,  -118,
    -118,  -118,  -118
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    20,
      19,    14,    15,    16,    17,     9,    10,    11,    12,    13,
       8,     5,     7,     6,     4,    18,     0,     0,     0,     0,
       0,     0,     0,     0,    68,    68,     0,     0,     0,    23,
       0,     0,     0,    24,    25,    26,    22,    21,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    56,
      55,     0,    29,    28,     0,    88,     0,     0,     0,     0,
      27,    31,    84,    85,    83,    82,     0,    83,     0,    83,
       0,    83,     0,    68,    68,    68,    86,     0,     0,     0,
       0,     0,    42,    33,     0,     0,     0,    72,     0,    72,
       0,    72,     0,    72,     0,    69,    57,    58,     0,    88,
       0,    44,    49,    50,     0,    51,     0,    90,    52,     0,
       0,     0,     0,    38,    39,    40,    41,    36,     0,     0,
       0,     0,    59,     0,    60,     0,    61,     0,    62,    68,
      68,    86,     0,    47,     0,     0,     0,    99,   100,   101,
     102,   103,   104,     0,     0,     0,    89,    88,     0,    33,
       0,     0,     0,    72,    72,     0,     0,     0,     0,    72,
      72,    72,    70,    71,    87,    54,     0,     0,    44,    43,
       0,    94,    92,    95,    93,    90,     0,     0,    34,    32,
      37,     0,     0,    63,    67,     0,     0,     0,     0,    64,
      65,    66,    47,    46,    45,     0,     0,    91,    53,   105,
      35,    30,    83,     0,    83,     0,    83,     0,    83,     0,
      48,     0,    96,    97,     0,    72,     0,    72,     0,    72,
       0,    72,     0,     0,     0,    73,     0,    74,     0,    75,
       0,    76,    98,    72,    72,    72,    72,    72,    77,    81,
      78,    79,    80
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,
    -118,  -118,  -118,  -118,  -118,    79,   123,  -118,  -118,  -118,
    -118,    68,   105,    48,  -117,  -118,  -118,  -118,  -118,   -44,
    -109,   -56,   112,  -114,    66,    97,  -115,  -118
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,   132,   103,   201,   137,   104,
      31,   155,   121,   187,   126,    32,    33,    34,    46,    69,
     142,    86,   119,    99,   166,   127,   163,    35
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     144,    70,   146,   153,   148,   152,   156,    48,    88,    90,
      92,   164,   167,    40,    41,    42,    43,   157,   158,   159,
     160,   161,   162,    67,    67,   157,   158,   159,   160,   161,
     162,    47,    50,    68,   114,    82,    83,    84,   122,   123,
      85,    49,   125,    82,    83,    87,   192,   194,    85,   115,
     116,   117,    51,   196,    44,    52,    53,    45,    82,    83,
      89,    54,    55,    85,   203,   204,    56,    57,    58,   212,
     209,   210,   211,    94,    59,   215,    95,     2,    82,    83,
      91,     3,     4,    85,    60,    61,     5,   133,   134,   135,
     136,     6,     7,     8,     9,    10,    11,    36,   232,    37,
      12,    13,    14,    62,    67,   182,   183,    15,    16,    82,
      83,   222,    63,   139,    85,    64,   140,    17,    82,    83,
     224,   149,   243,    85,   150,   244,   245,    38,   247,    39,
     249,    65,   251,    82,    83,   226,    66,    71,    85,   122,
     123,   124,    72,   125,   258,   259,   260,   261,   262,   223,
     225,   227,   229,    82,    83,   228,    73,    74,    85,   122,
     123,   191,    76,   125,   122,   123,   193,    77,   125,   122,
     123,   231,    78,   125,   175,   176,   177,   178,    75,    79,
      80,    81,    93,    96,    97,    98,   100,   101,   102,   105,
     106,   107,   108,   109,   110,   111,   113,   112,   118,   120,
     128,   130,   129,   131,   138,   141,   143,   145,   147,   154,
     165,   168,   151,   170,   171,   185,   173,   172,   186,   174,
     179,   180,   181,   189,   199,   202,   205,   206,   207,   208,
     218,   190,   213,   197,   200,   216,   219,   220,   221,   233,
     235,   246,   234,   237,   239,   236,   238,   240,   198,   241,
     242,   253,   254,   248,   169,   255,   214,   256,   257,   188,
     230,   217,   195,   184,     0,     0,     0,     0,   250,     0,
       0,     0,     0,     0,     0,   252
};

static const yytype_int16 yycheck[] =
{
     109,    45,   111,   120,   113,   119,    32,     7,    64,    65,
      66,   126,   129,    10,    11,    12,    13,    43,    44,    45,
      46,    47,    48,    22,    22,    43,    44,    45,    46,    47,
      48,    51,    33,    32,    32,    49,    50,    51,    49,    50,
      54,     3,    53,    49,    50,    51,   163,   164,    54,    93,
      94,    95,    35,   167,    51,    51,     3,    54,    49,    50,
      51,     3,     3,    54,   173,   174,     3,     3,    41,   186,
     179,   180,   181,    51,    51,   190,    54,     0,    49,    50,
      51,     4,     5,    54,    51,    51,     9,    26,    27,    28,
      29,    14,    15,    16,    17,    18,    19,     6,   215,     8,
      23,    24,    25,    51,    22,   149,   150,    30,    31,    49,
      50,    51,    20,    51,    54,    20,    54,    40,    49,    50,
      51,    51,    51,    54,    54,    54,   235,     6,   237,     8,
     239,    20,   241,    49,    50,    51,    20,    35,    54,    49,
      50,    51,     3,    53,   253,   254,   255,   256,   257,   205,
     206,   207,   208,    49,    50,    51,     3,    51,    54,    49,
      50,    51,    38,    53,    49,    50,    51,    42,    53,    49,
      50,    51,    20,    53,    10,    11,    12,    13,    51,    39,
       3,     3,    51,    51,    34,    36,    51,    53,    51,    51,
      32,    21,    32,    21,    32,    21,    21,    32,    22,    20,
       3,    33,    43,    22,    20,    22,    51,    51,    51,    22,
      37,     6,    51,    21,    20,     3,    21,    51,    22,    21,
      21,    21,    21,     3,     3,    21,    20,    20,    20,    20,
       3,    51,    21,    51,    49,    32,     3,    21,     3,    51,
      21,    51,    32,    21,    21,    32,    32,    32,   169,    21,
      32,    21,    21,    51,   131,    21,   188,    21,    21,   154,
     212,   195,   165,   151,    -1,    -1,    -1,    -1,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    51
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    57,     0,     4,     5,     9,    14,    15,    16,    17,
      18,    19,    23,    24,    25,    30,    31,    40,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    76,    81,    82,    83,    93,     6,     8,     6,     8,
      10,    11,    12,    13,    51,    54,    84,    51,     7,     3,
      33,    35,    51,     3,     3,     3,     3,     3,    41,    51,
      51,    51,    51,    20,    20,    20,    20,    22,    32,    85,
      85,    35,     3,     3,    51,    51,    38,    42,    20,    39,
       3,     3,    49,    50,    51,    54,    87,    51,    87,    51,
      87,    51,    87,    51,    51,    54,    51,    34,    36,    89,
      51,    53,    51,    72,    75,    51,    32,    21,    32,    21,
      32,    21,    32,    21,    32,    85,    85,    85,    22,    88,
      20,    78,    49,    50,    51,    53,    80,    91,     3,    43,
      33,    22,    71,    26,    27,    28,    29,    74,    20,    51,
      54,    22,    86,    51,    86,    51,    86,    51,    86,    51,
      54,    51,    89,    80,    22,    77,    32,    43,    44,    45,
      46,    47,    48,    92,    92,    37,    90,    80,     6,    72,
      21,    20,    51,    21,    21,    10,    11,    12,    13,    21,
      21,    21,    85,    85,    88,     3,    22,    79,    78,     3,
      51,    51,    80,    51,    80,    91,    89,    51,    71,     3,
      49,    73,    21,    86,    86,    20,    20,    20,    20,    86,
      86,    86,    80,    21,    77,    92,    32,    90,     3,     3,
      21,     3,    51,    87,    51,    87,    51,    87,    51,    87,
      79,    51,    80,    51,    32,    21,    32,    21,    32,    21,
      32,    21,    32,    51,    54,    86,    51,    86,    51,    86,
      51,    86,    51,    21,    21,    21,    21,    21,    86,    86,
      86,    86,    86
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    56,    57,    57,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    71,    72,    72,    73,    74,    74,
      74,    74,    75,    76,    77,    77,    78,    79,    79,    80,
      80,    80,    81,    82,    83,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    85,    85,
      85,    85,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    87,    87,    87,    87,    88,    88,    89,    89,
      90,    90,    91,    91,    91,    91,    91,    91,    91,    92,
      92,    92,    92,    92,    92,    93
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
       9,     4,     8,     0,     3,     5,     2,     1,     1,     1,
       1,     1,     1,     7,     0,     3,     4,     0,     3,     1,
       1,     1,     5,     8,     7,     2,     2,     4,     4,     5,
       5,     5,     5,     7,     7,     7,     7,     7,     0,     3,
       5,     5,     0,     6,     6,     6,     6,     8,     8,     8,
       8,     8,     1,     1,     1,     1,     0,     3,     0,     3,
       0,     3,     3,     3,     3,     3,     5,     5,     7,     1,
       1,     1,     1,     1,     1,     8
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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
        yyerror (scanner, YY_("syntax error: cannot back up")); \
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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, scanner);
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
                 int yyrule, void *scanner)
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
                       &yyvsp[(yyi + 1) - (yynrhs)], scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, void *scanner)
{
  YY_USE (yyvaluep);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

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
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
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
      yychar = yylex (&yylval, scanner);
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
  case 21: /* exit: EXIT SEMICOLON  */
#line 163 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1390 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 168 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1398 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 173 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1406 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 179 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1414 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 185 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1422 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 191 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1430 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 197 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1439 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 203 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1447 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 209 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1456 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID RBRACE SEMICOLON  */
#line 217 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string));
		}
#line 1465 "yacc_sql.tab.c"
    break;

  case 31: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 225 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1474 "yacc_sql.tab.c"
    break;

  case 32: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 232 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1486 "yacc_sql.tab.c"
    break;

  case 34: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 242 "yacc_sql.y"
                                   {    }
#line 1492 "yacc_sql.tab.c"
    break;

  case 35: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 247 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-3].number), (yyvsp[-1].number));
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
#line 1507 "yacc_sql.tab.c"
    break;

  case 36: /* attr_def: ID_get type  */
#line 258 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[0].number), 4);
			if (attribute.type == CHARS) attribute.length = 256;
			if (attribute.type == DATES) attribute.length = 10;
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
#line 1524 "yacc_sql.tab.c"
    break;

  case 37: /* number: NUMBER  */
#line 272 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1530 "yacc_sql.tab.c"
    break;

  case 38: /* type: INT_T  */
#line 275 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1536 "yacc_sql.tab.c"
    break;

  case 39: /* type: STRING_T  */
#line 276 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1542 "yacc_sql.tab.c"
    break;

  case 40: /* type: FLOAT_T  */
#line 277 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1548 "yacc_sql.tab.c"
    break;

  case 41: /* type: DATE_T  */
#line 278 "yacc_sql.y"
                { (yyval.number)=DATES; }
#line 1554 "yacc_sql.tab.c"
    break;

  case 42: /* ID_get: ID  */
#line 282 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1563 "yacc_sql.tab.c"
    break;

  case 43: /* insert: INSERT INTO ID VALUES values values_list SEMICOLON  */
#line 290 "yacc_sql.y"
                                                       {
			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string));
    }
#line 1572 "yacc_sql.tab.c"
    break;

  case 45: /* values_list: COMMA values values_list  */
#line 297 "yacc_sql.y"
                                {
    }
#line 1579 "yacc_sql.tab.c"
    break;

  case 46: /* values: LBRACE value value_list RBRACE  */
#line 301 "yacc_sql.y"
                                    {
      insert_value_tuple(&CONTEXT->ssql->sstr.insertion, CONTEXT->values, CONTEXT->value_length);
      CONTEXT->value_length=0;
    }
#line 1588 "yacc_sql.tab.c"
    break;

  case 48: /* value_list: COMMA value value_list  */
#line 307 "yacc_sql.y"
                              {}
#line 1594 "yacc_sql.tab.c"
    break;

  case 49: /* value: NUMBER  */
#line 309 "yacc_sql.y"
          {
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1602 "yacc_sql.tab.c"
    break;

  case 50: /* value: FLOAT  */
#line 312 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1610 "yacc_sql.tab.c"
    break;

  case 51: /* value: SSS  */
#line 315 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1619 "yacc_sql.tab.c"
    break;

  case 52: /* delete: DELETE FROM ID where SEMICOLON  */
#line 323 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1631 "yacc_sql.tab.c"
    break;

  case 53: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 333 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1643 "yacc_sql.tab.c"
    break;

  case 54: /* select: SELECT select_attr FROM ID rel_list where SEMICOLON  */
#line 343 "yacc_sql.y"
                {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-3].string));

			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
	}
#line 1663 "yacc_sql.tab.c"
    break;

  case 55: /* select_attr: STAR attr_list  */
#line 361 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1673 "yacc_sql.tab.c"
    break;

  case 56: /* select_attr: ID attr_list  */
#line 366 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1683 "yacc_sql.tab.c"
    break;

  case 57: /* select_attr: ID DOT ID attr_list  */
#line 371 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1693 "yacc_sql.tab.c"
    break;

  case 58: /* select_attr: ID DOT STAR attr_list  */
#line 376 "yacc_sql.y"
                                {
      RelAttr attr;
      relation_attr_init(&attr, (yyvsp[-3].string), "*");
      selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1703 "yacc_sql.tab.c"
    break;

  case 59: /* select_attr: COUNT LBRACE agg_value RBRACE agg_list  */
#line 382 "yacc_sql.y"
                                             {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
      AggInfo *agg_info = &selection->aggregations[selection->aggregation_num++];
      agg_info->agg_type = AGG_COUNT;
    }
#line 1713 "yacc_sql.tab.c"
    break;

  case 60: /* select_attr: MAX LBRACE agg_value RBRACE agg_list  */
#line 387 "yacc_sql.y"
                                           {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
      AggInfo *agg_info = &selection->aggregations[selection->aggregation_num++];
      agg_info->agg_type = AGG_MAX;
    }
#line 1723 "yacc_sql.tab.c"
    break;

  case 61: /* select_attr: MIN LBRACE agg_value RBRACE agg_list  */
#line 392 "yacc_sql.y"
                                           {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
      AggInfo *agg_info = &selection->aggregations[selection->aggregation_num++];
      agg_info->agg_type = AGG_MIN;
    }
#line 1733 "yacc_sql.tab.c"
    break;

  case 62: /* select_attr: AVG LBRACE agg_value RBRACE agg_list  */
#line 397 "yacc_sql.y"
                                           {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
      AggInfo *agg_info = &selection->aggregations[selection->aggregation_num++];
      agg_info->agg_type = AGG_AVG;
    }
#line 1743 "yacc_sql.tab.c"
    break;

  case 63: /* select_attr: COUNT LBRACE ID DOT ID RBRACE agg_list  */
#line 402 "yacc_sql.y"
                                           {
      RelAttr attr;
      relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
      AggInfo ainfo;
      memset(&ainfo, 0, sizeof(AggInfo));
      ainfo.agg_type = AGG_COUNT;
      ainfo.agg_attr = attr;
      ainfo.need_table_name = 1;
      selects_append_aggregation(&CONTEXT->ssql->sstr.selection, &ainfo);
    }
#line 1758 "yacc_sql.tab.c"
    break;

  case 64: /* select_attr: MAX LBRACE ID DOT ID RBRACE agg_list  */
#line 412 "yacc_sql.y"
                                         {
      RelAttr attr;
      relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
      AggInfo ainfo;
      memset(&ainfo, 0, sizeof(AggInfo));
      ainfo.agg_type = AGG_MAX;
      ainfo.agg_attr = attr;
      ainfo.need_table_name = 1;
      selects_append_aggregation(&CONTEXT->ssql->sstr.selection, &ainfo);
    }
#line 1773 "yacc_sql.tab.c"
    break;

  case 65: /* select_attr: MIN LBRACE ID DOT ID RBRACE agg_list  */
#line 422 "yacc_sql.y"
                                         {
      RelAttr attr;
      relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
      AggInfo ainfo;
      memset(&ainfo, 0, sizeof(AggInfo));
      ainfo.agg_type = AGG_MIN;
      ainfo.agg_attr = attr;
      ainfo.need_table_name = 1;
      selects_append_aggregation(&CONTEXT->ssql->sstr.selection, &ainfo);
    }
#line 1788 "yacc_sql.tab.c"
    break;

  case 66: /* select_attr: AVG LBRACE ID DOT ID RBRACE agg_list  */
#line 432 "yacc_sql.y"
                                         {
      RelAttr attr;
      relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
      AggInfo ainfo;
      memset(&ainfo, 0, sizeof(AggInfo));
      ainfo.agg_type = AGG_AVG;
      ainfo.agg_attr = attr;
      ainfo.need_table_name = 1;
      selects_append_aggregation(&CONTEXT->ssql->sstr.selection, &ainfo);
    }
#line 1803 "yacc_sql.tab.c"
    break;

  case 67: /* select_attr: COUNT LBRACE ID DOT STAR RBRACE agg_list  */
#line 442 "yacc_sql.y"
                                             {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), "*");
			AggInfo ainfo;
      memset(&ainfo, 0, sizeof(AggInfo));
			ainfo.agg_type = AGG_COUNT;
			ainfo.agg_attr = attr;
      ainfo.need_table_name = 1;
      selects_append_aggregation(&CONTEXT->ssql->sstr.selection, &ainfo);
		}
#line 1818 "yacc_sql.tab.c"
    break;

  case 69: /* attr_list: COMMA ID attr_list  */
#line 455 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 1830 "yacc_sql.tab.c"
    break;

  case 70: /* attr_list: COMMA ID DOT ID attr_list  */
#line 462 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 1842 "yacc_sql.tab.c"
    break;

  case 71: /* attr_list: COMMA ID DOT STAR attr_list  */
#line 469 "yacc_sql.y"
                                  {
    			RelAttr attr;
    			relation_attr_init(&attr, (yyvsp[-3].string), "*");
    			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 1852 "yacc_sql.tab.c"
    break;

  case 73: /* agg_list: COMMA COUNT LBRACE agg_value RBRACE agg_list  */
#line 476 "yacc_sql.y"
                                                   {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
      AggInfo *agg_info = &selection->aggregations[selection->aggregation_num++];
      agg_info->agg_type = AGG_COUNT;
    }
#line 1862 "yacc_sql.tab.c"
    break;

  case 74: /* agg_list: COMMA MAX LBRACE agg_value RBRACE agg_list  */
#line 481 "yacc_sql.y"
                                                 {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
      AggInfo *agg_info = &selection->aggregations[selection->aggregation_num++];
      agg_info->agg_type = AGG_MAX;
    }
#line 1872 "yacc_sql.tab.c"
    break;

  case 75: /* agg_list: COMMA MIN LBRACE agg_value RBRACE agg_list  */
#line 486 "yacc_sql.y"
                                                 {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
      AggInfo *agg_info = &selection->aggregations[selection->aggregation_num++];
      agg_info->agg_type = AGG_MIN;
    }
#line 1882 "yacc_sql.tab.c"
    break;

  case 76: /* agg_list: COMMA AVG LBRACE agg_value RBRACE agg_list  */
#line 491 "yacc_sql.y"
                                                 {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
      AggInfo *agg_info = &selection->aggregations[selection->aggregation_num++];
      agg_info->agg_type = AGG_AVG;
    }
#line 1892 "yacc_sql.tab.c"
    break;

  case 77: /* agg_list: COMMA COUNT LBRACE ID DOT ID RBRACE agg_list  */
#line 496 "yacc_sql.y"
                                                 {
      RelAttr attr;
      relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
      AggInfo ainfo;
      memset(&ainfo, 0, sizeof(AggInfo));
      ainfo.agg_type = AGG_COUNT;
      ainfo.agg_attr = attr;
      ainfo.need_table_name = 1;
      selects_append_aggregation(&CONTEXT->ssql->sstr.selection, &ainfo);
    }
#line 1907 "yacc_sql.tab.c"
    break;

  case 78: /* agg_list: COMMA MAX LBRACE ID DOT ID RBRACE agg_list  */
#line 506 "yacc_sql.y"
                                               {
      RelAttr attr;
      relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
      AggInfo ainfo;
      memset(&ainfo, 0, sizeof(AggInfo));
      ainfo.agg_type = AGG_MAX;
      ainfo.agg_attr = attr;
      ainfo.need_table_name = 1;
      selects_append_aggregation(&CONTEXT->ssql->sstr.selection, &ainfo);
    }
#line 1922 "yacc_sql.tab.c"
    break;

  case 79: /* agg_list: COMMA MIN LBRACE ID DOT ID RBRACE agg_list  */
#line 516 "yacc_sql.y"
                                               {
      RelAttr attr;
      relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
      AggInfo ainfo;
      memset(&ainfo, 0, sizeof(AggInfo));
      ainfo.agg_type = AGG_MIN;
      ainfo.agg_attr = attr;
      ainfo.need_table_name = 1;
      selects_append_aggregation(&CONTEXT->ssql->sstr.selection, &ainfo);
    }
#line 1937 "yacc_sql.tab.c"
    break;

  case 80: /* agg_list: COMMA AVG LBRACE ID DOT ID RBRACE agg_list  */
#line 526 "yacc_sql.y"
                                               {
      RelAttr attr;
      relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
      AggInfo ainfo;
      memset(&ainfo, 0, sizeof(AggInfo));
      ainfo.agg_type = AGG_AVG;
      ainfo.agg_attr = attr;
      ainfo.need_table_name = 1;
      selects_append_aggregation(&CONTEXT->ssql->sstr.selection, &ainfo);
    }
#line 1952 "yacc_sql.tab.c"
    break;

  case 81: /* agg_list: COMMA COUNT LBRACE ID DOT STAR RBRACE agg_list  */
#line 536 "yacc_sql.y"
                                                   {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), "*");
			AggInfo ainfo;
      memset(&ainfo, 0, sizeof(AggInfo));
			ainfo.agg_type = AGG_COUNT;
			ainfo.agg_attr = attr;
      ainfo.need_table_name = 1;
      selects_append_aggregation(&CONTEXT->ssql->sstr.selection, &ainfo);
		}
#line 1967 "yacc_sql.tab.c"
    break;

  case 82: /* agg_value: STAR  */
#line 549 "yacc_sql.y"
         {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
      AggInfo *agg_info = &selection->aggregations[selection->aggregation_num];
      agg_info->need_all = 1;
      agg_info->agg_attr.attribute_name = strdup("*");
      selection->attributes[selection->attr_num++] = agg_info->agg_attr;
    }
#line 1979 "yacc_sql.tab.c"
    break;

  case 83: /* agg_value: ID  */
#line 557 "yacc_sql.y"
         {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
      AggInfo *agg_info = &selection->aggregations[selection->aggregation_num];
      agg_info->agg_attr.attribute_name = strdup((yyvsp[0].string));
      selection->attributes[selection->attr_num++] = agg_info->agg_attr;
    }
#line 1990 "yacc_sql.tab.c"
    break;

  case 84: /* agg_value: NUMBER  */
#line 564 "yacc_sql.y"
             {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
      AggInfo *agg_info = &selection->aggregations[selection->aggregation_num];
      agg_info->is_constant = 1;
  		value_init_integer(&agg_info->value, (yyvsp[0].number));
		}
#line 2001 "yacc_sql.tab.c"
    break;

  case 85: /* agg_value: FLOAT  */
#line 570 "yacc_sql.y"
            {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
      AggInfo *agg_info = &selection->aggregations[selection->aggregation_num];
      agg_info->is_constant = 1;
  		value_init_float(&agg_info->value, (yyvsp[0].floats));
		}
#line 2012 "yacc_sql.tab.c"
    break;

  case 87: /* rel_list: COMMA ID rel_list  */
#line 579 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 2020 "yacc_sql.tab.c"
    break;

  case 89: /* where: WHERE condition condition_list  */
#line 585 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2028 "yacc_sql.tab.c"
    break;

  case 91: /* condition_list: AND condition condition_list  */
#line 591 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2036 "yacc_sql.tab.c"
    break;

  case 92: /* condition: ID comOp value  */
#line 597 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name = NULL;
			// $$->left_attr.attribute_name= $1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 2061 "yacc_sql.tab.c"
    break;

  case 93: /* condition: value comOp value  */
#line 618 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 2085 "yacc_sql.tab.c"
    break;

  case 94: /* condition: ID comOp ID  */
#line 638 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
#line 2109 "yacc_sql.tab.c"
    break;

  case 95: /* condition: value comOp ID  */
#line 658 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp=CONTEXT->comp;
			
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;
		
		}
#line 2135 "yacc_sql.tab.c"
    break;

  case 96: /* condition: ID DOT ID comOp value  */
#line 680 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp=CONTEXT->comp;
			// $$->right_is_attr = 0;   //属性值
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=NULL;
			// $$->right_value =*$5;			
							
    }
#line 2160 "yacc_sql.tab.c"
    break;

  case 97: /* condition: value comOp ID DOT ID  */
#line 701 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;//属性值
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;//属性
			// $$->right_attr.relation_name = $3;
			// $$->right_attr.attribute_name = $5;
									
    }
#line 2185 "yacc_sql.tab.c"
    break;

  case 98: /* condition: ID DOT ID comOp ID DOT ID  */
#line 722 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
#line 2208 "yacc_sql.tab.c"
    break;

  case 99: /* comOp: EQ  */
#line 743 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2214 "yacc_sql.tab.c"
    break;

  case 100: /* comOp: LT  */
#line 744 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2220 "yacc_sql.tab.c"
    break;

  case 101: /* comOp: GT  */
#line 745 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2226 "yacc_sql.tab.c"
    break;

  case 102: /* comOp: LE  */
#line 746 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2232 "yacc_sql.tab.c"
    break;

  case 103: /* comOp: GE  */
#line 747 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2238 "yacc_sql.tab.c"
    break;

  case 104: /* comOp: NE  */
#line 748 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2244 "yacc_sql.tab.c"
    break;

  case 105: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 753 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2253 "yacc_sql.tab.c"
    break;


#line 2257 "yacc_sql.tab.c"

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
      yyerror (scanner, YY_("syntax error"));
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
                      yytoken, &yylval, scanner);
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
  ++yynerrs;

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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, scanner);
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
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 758 "yacc_sql.y"

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
