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
  size_t aggregations_length;
  Value values[MAX_NUM];
  Condition conditions[MAX_NUM];
  CompOp comp;
	char id[MAX_NUM];
  struct ParserContext *next_ctx;
  // int ctx_id; /* 此次执行第几个 select */
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
  context->aggregations_length = 0;
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


#line 132 "yacc_sql.tab.c"

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
  YYSYMBOL_TEXT_T = 30,                    /* TEXT_T  */
  YYSYMBOL_HELP = 31,                      /* HELP  */
  YYSYMBOL_EXIT = 32,                      /* EXIT  */
  YYSYMBOL_DOT = 33,                       /* DOT  */
  YYSYMBOL_INTO = 34,                      /* INTO  */
  YYSYMBOL_VALUES = 35,                    /* VALUES  */
  YYSYMBOL_FROM = 36,                      /* FROM  */
  YYSYMBOL_WHERE = 37,                     /* WHERE  */
  YYSYMBOL_AND = 38,                       /* AND  */
  YYSYMBOL_SET = 39,                       /* SET  */
  YYSYMBOL_ON = 40,                        /* ON  */
  YYSYMBOL_LOAD = 41,                      /* LOAD  */
  YYSYMBOL_DATA = 42,                      /* DATA  */
  YYSYMBOL_INFILE = 43,                    /* INFILE  */
  YYSYMBOL_EQ = 44,                        /* EQ  */
  YYSYMBOL_LT = 45,                        /* LT  */
  YYSYMBOL_GT = 46,                        /* GT  */
  YYSYMBOL_LE = 47,                        /* LE  */
  YYSYMBOL_GE = 48,                        /* GE  */
  YYSYMBOL_NE = 49,                        /* NE  */
  YYSYMBOL_ORDER = 50,                     /* ORDER  */
  YYSYMBOL_GROUP = 51,                     /* GROUP  */
  YYSYMBOL_BY = 52,                        /* BY  */
  YYSYMBOL_UNIQUE = 53,                    /* UNIQUE  */
  YYSYMBOL_ASC = 54,                       /* ASC  */
  YYSYMBOL_INNER = 55,                     /* INNER  */
  YYSYMBOL_JOIN = 56,                      /* JOIN  */
  YYSYMBOL_IN = 57,                        /* IN  */
  YYSYMBOL_NOT = 58,                       /* NOT  */
  YYSYMBOL_NUMBER = 59,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 60,                     /* FLOAT  */
  YYSYMBOL_ID = 61,                        /* ID  */
  YYSYMBOL_PATH = 62,                      /* PATH  */
  YYSYMBOL_SSS = 63,                       /* SSS  */
  YYSYMBOL_STAR = 64,                      /* STAR  */
  YYSYMBOL_STRING_V = 65,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 66,                  /* $accept  */
  YYSYMBOL_commands = 67,                  /* commands  */
  YYSYMBOL_command = 68,                   /* command  */
  YYSYMBOL_exit = 69,                      /* exit  */
  YYSYMBOL_help = 70,                      /* help  */
  YYSYMBOL_sync = 71,                      /* sync  */
  YYSYMBOL_begin = 72,                     /* begin  */
  YYSYMBOL_commit = 73,                    /* commit  */
  YYSYMBOL_rollback = 74,                  /* rollback  */
  YYSYMBOL_drop_table = 75,                /* drop_table  */
  YYSYMBOL_show_tables = 76,               /* show_tables  */
  YYSYMBOL_desc_table = 77,                /* desc_table  */
  YYSYMBOL_create_index = 78,              /* create_index  */
  YYSYMBOL_create_unique_index = 79,       /* create_unique_index  */
  YYSYMBOL_drop_index = 80,                /* drop_index  */
  YYSYMBOL_create_table = 81,              /* create_table  */
  YYSYMBOL_attr_def_list = 82,             /* attr_def_list  */
  YYSYMBOL_attr_def = 83,                  /* attr_def  */
  YYSYMBOL_number = 84,                    /* number  */
  YYSYMBOL_type = 85,                      /* type  */
  YYSYMBOL_ID_get = 86,                    /* ID_get  */
  YYSYMBOL_insert = 87,                    /* insert  */
  YYSYMBOL_values_list = 88,               /* values_list  */
  YYSYMBOL_values = 89,                    /* values  */
  YYSYMBOL_value_list = 90,                /* value_list  */
  YYSYMBOL_value = 91,                     /* value  */
  YYSYMBOL_delete = 92,                    /* delete  */
  YYSYMBOL_update = 93,                    /* update  */
  YYSYMBOL_do_select = 94,                 /* do_select  */
  YYSYMBOL_select = 95,                    /* select  */
  YYSYMBOL_FromCluse = 96,                 /* FromCluse  */
  YYSYMBOL_TableRefs = 97,                 /* TableRefs  */
  YYSYMBOL_TableRef = 98,                  /* TableRef  */
  YYSYMBOL_JoinTables = 99,                /* JoinTables  */
  YYSYMBOL_JoinTable = 100,                /* JoinTable  */
  YYSYMBOL_order_by = 101,                 /* order_by  */
  YYSYMBOL_order_attr_list = 102,          /* order_attr_list  */
  YYSYMBOL_order_attr = 103,               /* order_attr  */
  YYSYMBOL_group_by = 104,                 /* group_by  */
  YYSYMBOL_group_attr_list = 105,          /* group_attr_list  */
  YYSYMBOL_group_attr = 106,               /* group_attr  */
  YYSYMBOL_select_attr_list = 107,         /* select_attr_list  */
  YYSYMBOL_select_attr = 108,              /* select_attr  */
  YYSYMBOL_simple_select_attr = 109,       /* simple_select_attr  */
  YYSYMBOL_agg_attr = 110,                 /* agg_attr  */
  YYSYMBOL_agg_value = 111,                /* agg_value  */
  YYSYMBOL_where = 112,                    /* where  */
  YYSYMBOL_condition_list = 113,           /* condition_list  */
  YYSYMBOL_condition = 114,                /* condition  */
  YYSYMBOL_before_select = 115,            /* before_select  */
  YYSYMBOL_after_select = 116,             /* after_select  */
  YYSYMBOL_comOp = 117,                    /* comOp  */
  YYSYMBOL_load_data = 118                 /* load_data  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYLAST   248

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  66
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  124
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  249

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   320


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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   154,   154,   156,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   181,   186,   191,   197,   203,   209,   215,   221,
     227,   234,   241,   248,   255,   264,   266,   270,   281,   297,
     300,   301,   302,   303,   304,   307,   316,   321,   323,   327,
     332,   333,   335,   338,   341,   348,   358,   368,   371,   388,
     389,   394,   395,   398,   404,   405,   408,   412,   414,   417,
     419,   422,   427,   432,   437,   442,   447,   453,   455,   458,
     460,   463,   468,   475,   477,   480,   481,   484,   490,   496,
     501,   509,   516,   523,   530,   540,   549,   556,   564,   574,
     582,   591,   593,   597,   599,   604,   625,   645,   665,   687,
     708,   729,   748,   757,   769,   790,   810,   811,   812,   813,
     814,   815,   816,   817,   821
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
  "STRING_T", "FLOAT_T", "DATE_T", "TEXT_T", "HELP", "EXIT", "DOT", "INTO",
  "VALUES", "FROM", "WHERE", "AND", "SET", "ON", "LOAD", "DATA", "INFILE",
  "EQ", "LT", "GT", "LE", "GE", "NE", "ORDER", "GROUP", "BY", "UNIQUE",
  "ASC", "INNER", "JOIN", "IN", "NOT", "NUMBER", "FLOAT", "ID", "PATH",
  "SSS", "STAR", "STRING_V", "$accept", "commands", "command", "exit",
  "help", "sync", "begin", "commit", "rollback", "drop_table",
  "show_tables", "desc_table", "create_index", "create_unique_index",
  "drop_index", "create_table", "attr_def_list", "attr_def", "number",
  "type", "ID_get", "insert", "values_list", "values", "value_list",
  "value", "delete", "update", "do_select", "select", "FromCluse",
  "TableRefs", "TableRef", "JoinTables", "JoinTable", "order_by",
  "order_attr_list", "order_attr", "group_by", "group_attr_list",
  "group_attr", "select_attr_list", "select_attr", "simple_select_attr",
  "agg_attr", "agg_value", "where", "condition_list", "condition",
  "before_select", "after_select", "comOp", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-190)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -190,    14,  -190,     9,   107,    -4,   -35,    29,    39,     7,
      11,   -13,    51,    83,   100,   105,   111,    74,  -190,  -190,
    -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,
    -190,  -190,  -190,  -190,  -190,  -190,   114,  -190,    57,    58,
     112,    60,    61,   103,   104,   106,   108,    92,  -190,    -9,
    -190,  -190,  -190,   124,   126,  -190,    69,    71,    94,  -190,
    -190,  -190,  -190,  -190,    88,  -190,   115,    96,    73,   134,
     135,    31,    31,    31,    31,    43,    -4,    78,  -190,  -190,
     109,   110,    79,    80,    81,    84,   101,  -190,  -190,  -190,
    -190,   113,  -190,   127,   128,   129,   130,  -190,  -190,  -190,
      97,   110,   131,  -190,   136,   -10,   151,   116,   121,  -190,
     137,    70,   138,   102,    45,  -190,  -190,  -190,  -190,   117,
      97,  -190,   118,   119,    42,   139,  -190,  -190,  -190,    30,
    -190,    36,   132,   148,  -190,    42,   156,    81,   143,  -190,
    -190,  -190,  -190,  -190,   145,   120,   146,  -190,  -190,   122,
    -190,   123,   140,  -190,  -190,   149,   136,   164,   125,  -190,
    -190,  -190,  -190,  -190,  -190,  -190,   141,     5,   -39,   -10,
    -190,   147,   110,   133,   137,   169,   142,   153,   144,   152,
     150,   154,  -190,    42,   155,   139,  -190,    36,  -190,  -190,
    -190,   148,   158,  -190,   132,  -190,    36,   174,   175,  -190,
    -190,  -190,   161,   176,   163,   -10,   160,   165,  -190,   157,
     149,  -190,  -190,    10,   147,   159,  -190,   162,  -190,  -190,
    -190,  -190,   182,   132,   166,   150,     2,   167,  -190,  -190,
     170,  -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,
     168,  -190,   157,   171,    -2,  -190,  -190,  -190,  -190
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    21,
      20,    15,    16,    17,    18,     9,    10,    11,    12,    13,
      14,     8,     5,     7,     6,     4,     0,    19,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    88,    87,     0,
      83,    85,    86,     0,     0,    24,     0,     0,     0,    25,
      26,    27,    23,    22,     0,    57,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    30,    29,
       0,   101,     0,     0,     0,     0,     0,    28,    33,    99,
     100,    96,    95,     0,     0,     0,     0,    90,    89,    84,
      63,   101,    59,    62,     0,     0,     0,     0,     0,    45,
      35,     0,     0,     0,     0,    91,    92,    93,    94,     0,
      60,    65,    77,     0,     0,    47,   114,    52,    53,     0,
      54,     0,   103,     0,    55,     0,     0,     0,     0,    40,
      41,    42,    43,    44,    38,     0,     0,    97,    98,     0,
      64,     0,    67,    63,    61,    50,     0,     0,     0,   116,
     117,   118,   119,   120,   121,   123,     0,     0,     0,     0,
     102,     0,   101,     0,    35,     0,     0,     0,     0,     0,
       0,     0,    58,     0,     0,    47,    46,     0,   122,   107,
     105,     0,   108,   106,   103,   115,     0,     0,     0,    36,
      34,    39,     0,     0,     0,     0,    81,    78,    79,     0,
      50,    49,    48,     0,     0,     0,   104,     0,    56,   124,
      37,    31,     0,   103,     0,     0,    71,    68,    69,    51,
       0,   109,   112,   110,   113,    32,    66,    82,    80,    73,
       0,    72,     0,     0,    74,    70,   111,    76,    75
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,
    -190,  -190,  -190,  -190,  -190,  -190,    21,    59,  -190,  -190,
    -190,  -190,     3,    41,   -11,  -124,  -190,  -190,  -190,  -130,
    -190,  -190,    77,  -190,    82,  -190,  -190,   -38,  -190,  -190,
     -18,  -190,   172,  -190,  -190,    38,  -100,  -189,  -165,    46,
      -6,  -129,  -190
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,   138,   110,   202,   144,
     111,    32,   157,   125,   184,   131,    33,    34,    35,    36,
     101,   102,   103,   120,   121,   182,   227,   228,   152,   207,
     208,    49,    50,    51,    52,    93,   106,   170,   132,   133,
     196,   167,    37
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
     155,   122,   168,   171,   194,   216,    43,    44,    45,    46,
     126,   172,   247,    76,     2,    38,   239,    39,     3,     4,
     127,   128,   192,     5,   130,   126,    53,    77,     6,     7,
       8,     9,    10,    11,   236,   240,    54,    12,    13,    14,
     223,    56,    55,   190,   193,    15,    16,    57,    58,   127,
     128,   129,   248,   130,    59,    17,   241,    47,   213,   210,
      48,   214,    40,   158,   127,   128,   189,   217,   130,   127,
     128,   230,   197,   130,   159,   160,   161,   162,   163,   164,
     159,   160,   161,   162,   163,   164,    60,   165,   166,   231,
      89,    90,    91,   165,   166,    92,   139,   140,   141,   142,
     143,   127,   128,    61,    97,   130,   147,    98,    62,   148,
      94,    95,    96,    41,    63,    42,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    75,    73,    78,    74,    79,
      80,    83,    81,    82,    86,    84,    85,    87,    88,   100,
     107,   113,   109,   108,   104,   112,   114,   105,   115,   116,
     117,   118,   119,   123,   134,   136,   124,     5,   145,   137,
     135,   156,   173,   146,   175,   176,   178,   186,   195,   151,
     169,   183,   200,   149,   203,   180,   211,   218,   219,   221,
     153,   177,   220,   179,   222,   235,   187,   225,   212,   242,
     181,   215,   205,   224,   198,   199,   174,   185,   188,   229,
     154,   201,   150,   243,   245,   204,   209,   238,   232,     0,
       0,   206,     0,   191,     0,     0,     0,     0,   226,     0,
     233,     0,     0,   234,     0,     0,     0,   237,     0,   244,
       0,     0,   246,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    99
};

static const yytype_int16 yycheck[] =
{
     124,   101,   131,   133,   169,   194,    10,    11,    12,    13,
      20,   135,    14,    22,     0,     6,    14,     8,     4,     5,
      59,    60,    61,     9,    63,    20,    61,    36,    14,    15,
      16,    17,    18,    19,   223,    33,     7,    23,    24,    25,
     205,    34,     3,   167,   168,    31,    32,    36,    61,    59,
      60,    61,    54,    63,     3,    41,    54,    61,   187,   183,
      64,   191,    53,    33,    59,    60,    61,   196,    63,    59,
      60,    61,   172,    63,    44,    45,    46,    47,    48,    49,
      44,    45,    46,    47,    48,    49,     3,    57,    58,   213,
      59,    60,    61,    57,    58,    64,    26,    27,    28,    29,
      30,    59,    60,     3,    61,    63,    61,    64,     3,    64,
      72,    73,    74,     6,     3,     8,    42,     3,    61,    61,
       8,    61,    61,    20,    20,    33,    20,     3,    20,     3,
      61,    43,    61,    39,    61,    20,    40,     3,     3,    61,
      61,    40,    61,    63,    35,    61,    33,    37,    21,    21,
      21,    21,    55,    22,     3,    34,    20,     9,    20,    22,
      44,    22,     6,    61,    21,    20,    20,     3,    21,    51,
      38,    22,     3,    56,    21,    52,    21,     3,     3,     3,
      61,    61,    21,    61,    21,     3,    61,    22,   185,    22,
      50,    33,    40,    33,    61,   174,   137,   156,    57,   210,
     123,    59,   120,    33,   242,    61,    52,   225,   214,    -1,
      -1,    61,    -1,   167,    -1,    -1,    -1,    -1,    61,    -1,
      61,    -1,    -1,    61,    -1,    -1,    -1,    61,    -1,    61,
      -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    67,     0,     4,     5,     9,    14,    15,    16,    17,
      18,    19,    23,    24,    25,    31,    32,    41,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    87,    92,    93,    94,    95,   118,     6,     8,
      53,     6,     8,    10,    11,    12,    13,    61,    64,   107,
     108,   109,   110,    61,     7,     3,    34,    36,    61,     3,
       3,     3,     3,     3,    42,     3,    61,    61,     8,    61,
      61,    20,    20,    20,    20,    33,    22,    36,     3,     3,
      61,    61,    39,    43,    20,    40,    61,     3,     3,    59,
      60,    61,    64,   111,   111,   111,   111,    61,    64,   108,
      61,    96,    97,    98,    35,    37,   112,    61,    63,    61,
      83,    86,    61,    40,    33,    21,    21,    21,    21,    55,
      99,   100,   112,    22,    20,    89,    20,    59,    60,    61,
      63,    91,   114,   115,     3,    44,    34,    22,    82,    26,
      27,    28,    29,    30,    85,    20,    61,    61,    64,    56,
     100,    51,   104,    61,    98,    91,    22,    88,    33,    44,
      45,    46,    47,    48,    49,    57,    58,   117,   117,    38,
     113,    95,    91,     6,    83,    21,    20,    61,    20,    61,
      52,    50,   101,    22,    90,    89,     3,    61,    57,    61,
      91,   115,    61,    91,   114,    21,   116,   112,    61,    82,
       3,    59,    84,    21,    61,    40,    61,   105,   106,    52,
      91,    21,    88,   117,    95,    33,   113,   117,     3,     3,
      21,     3,    21,   114,    33,    22,    61,   102,   103,    90,
      61,    91,   116,    61,    61,     3,   113,    61,   106,    14,
      33,    54,    22,    33,    61,   103,    61,    14,    54
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    66,    67,    67,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    82,    83,    83,    84,
      85,    85,    85,    85,    85,    86,    87,    88,    88,    89,
      90,    90,    91,    91,    91,    92,    93,    94,    95,    96,
      96,    97,    97,    98,    99,    99,   100,   101,   101,   102,
     102,   103,   103,   103,   103,   103,   103,   104,   104,   105,
     105,   106,   106,   107,   107,   108,   108,   109,   109,   109,
     109,   110,   110,   110,   110,   111,   111,   111,   111,   111,
     111,   112,   112,   113,   113,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   115,   116,   117,   117,   117,   117,
     117,   117,   117,   117,   118
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     4,     3,
       3,     9,    10,     4,     8,     0,     3,     5,     2,     1,
       1,     1,     1,     1,     1,     1,     7,     0,     3,     4,
       0,     3,     1,     1,     1,     5,     8,     2,     7,     1,
       2,     3,     1,     1,     2,     1,     6,     0,     3,     1,
       3,     1,     2,     2,     3,     4,     4,     0,     3,     1,
       3,     1,     3,     1,     3,     1,     1,     1,     1,     3,
       3,     4,     4,     4,     4,     1,     1,     3,     3,     1,
       1,     0,     3,     0,     3,     3,     3,     3,     3,     5,
       5,     7,     5,     5,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     8
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
  case 22: /* exit: EXIT SEMICOLON  */
#line 181 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1423 "yacc_sql.tab.c"
    break;

  case 23: /* help: HELP SEMICOLON  */
#line 186 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1431 "yacc_sql.tab.c"
    break;

  case 24: /* sync: SYNC SEMICOLON  */
#line 191 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1439 "yacc_sql.tab.c"
    break;

  case 25: /* begin: TRX_BEGIN SEMICOLON  */
#line 197 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1447 "yacc_sql.tab.c"
    break;

  case 26: /* commit: TRX_COMMIT SEMICOLON  */
#line 203 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1455 "yacc_sql.tab.c"
    break;

  case 27: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 209 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1463 "yacc_sql.tab.c"
    break;

  case 28: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 215 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1472 "yacc_sql.tab.c"
    break;

  case 29: /* show_tables: SHOW TABLES SEMICOLON  */
#line 221 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1480 "yacc_sql.tab.c"
    break;

  case 30: /* desc_table: DESC ID SEMICOLON  */
#line 227 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1489 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE INDEX ID ON ID LBRACE ID RBRACE SEMICOLON  */
#line 235 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string), 0);
		}
#line 1498 "yacc_sql.tab.c"
    break;

  case 32: /* create_unique_index: CREATE UNIQUE INDEX ID ON ID LBRACE ID RBRACE SEMICOLON  */
#line 242 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string), 1);
		}
#line 1507 "yacc_sql.tab.c"
    break;

  case 33: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 249 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1516 "yacc_sql.tab.c"
    break;

  case 34: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 256 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1528 "yacc_sql.tab.c"
    break;

  case 36: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 266 "yacc_sql.y"
                                   {    }
#line 1534 "yacc_sql.tab.c"
    break;

  case 37: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 271 "yacc_sql.y"
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
#line 1549 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def: ID_get type  */
#line 282 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[0].number), 4);
			if (attribute.type == TEXTS) attribute.length = sizeof(int) * 2;
			if (attribute.type == CHARS) attribute.length = 256;
			if (attribute.type == DATES) attribute.length = 10;
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
#line 1567 "yacc_sql.tab.c"
    break;

  case 39: /* number: NUMBER  */
#line 297 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1573 "yacc_sql.tab.c"
    break;

  case 40: /* type: INT_T  */
#line 300 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1579 "yacc_sql.tab.c"
    break;

  case 41: /* type: STRING_T  */
#line 301 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1585 "yacc_sql.tab.c"
    break;

  case 42: /* type: FLOAT_T  */
#line 302 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1591 "yacc_sql.tab.c"
    break;

  case 43: /* type: DATE_T  */
#line 303 "yacc_sql.y"
                { (yyval.number)=DATES; }
#line 1597 "yacc_sql.tab.c"
    break;

  case 44: /* type: TEXT_T  */
#line 304 "yacc_sql.y"
                { (yyval.number)=TEXTS; }
#line 1603 "yacc_sql.tab.c"
    break;

  case 45: /* ID_get: ID  */
#line 308 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1612 "yacc_sql.tab.c"
    break;

  case 46: /* insert: INSERT INTO ID VALUES values values_list SEMICOLON  */
#line 316 "yacc_sql.y"
                                                       {
			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string));
    }
#line 1621 "yacc_sql.tab.c"
    break;

  case 48: /* values_list: COMMA values values_list  */
#line 323 "yacc_sql.y"
                                {
    }
#line 1628 "yacc_sql.tab.c"
    break;

  case 49: /* values: LBRACE value value_list RBRACE  */
#line 327 "yacc_sql.y"
                                    {
      insert_value_tuple(&CONTEXT->ssql->sstr.insertion, CONTEXT->values, CONTEXT->value_length);
      CONTEXT->value_length=0;
    }
#line 1637 "yacc_sql.tab.c"
    break;

  case 51: /* value_list: COMMA value value_list  */
#line 333 "yacc_sql.y"
                              {}
#line 1643 "yacc_sql.tab.c"
    break;

  case 52: /* value: NUMBER  */
#line 335 "yacc_sql.y"
          {
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1651 "yacc_sql.tab.c"
    break;

  case 53: /* value: FLOAT  */
#line 338 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1659 "yacc_sql.tab.c"
    break;

  case 54: /* value: SSS  */
#line 341 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1668 "yacc_sql.tab.c"
    break;

  case 55: /* delete: DELETE FROM ID where SEMICOLON  */
#line 349 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1680 "yacc_sql.tab.c"
    break;

  case 56: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 359 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1692 "yacc_sql.tab.c"
    break;

  case 57: /* do_select: select SEMICOLON  */
#line 368 "yacc_sql.y"
                     {}
#line 1698 "yacc_sql.tab.c"
    break;

  case 58: /* select: SELECT select_attr_list FROM FromCluse where group_by order_by  */
#line 372 "yacc_sql.y"
                {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;

			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
	}
#line 1717 "yacc_sql.tab.c"
    break;

  case 59: /* FromCluse: TableRefs  */
#line 388 "yacc_sql.y"
            {}
#line 1723 "yacc_sql.tab.c"
    break;

  case 60: /* FromCluse: ID JoinTables  */
#line 389 "yacc_sql.y"
                  {
    selects_insert_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
  }
#line 1731 "yacc_sql.tab.c"
    break;

  case 61: /* TableRefs: TableRefs COMMA TableRef  */
#line 394 "yacc_sql.y"
                                {}
#line 1737 "yacc_sql.tab.c"
    break;

  case 62: /* TableRefs: TableRef  */
#line 395 "yacc_sql.y"
             {}
#line 1743 "yacc_sql.tab.c"
    break;

  case 63: /* TableRef: ID  */
#line 398 "yacc_sql.y"
           {
    selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[0].string));
  }
#line 1751 "yacc_sql.tab.c"
    break;

  case 64: /* JoinTables: JoinTables JoinTable  */
#line 404 "yacc_sql.y"
                       {
  }
#line 1758 "yacc_sql.tab.c"
    break;

  case 65: /* JoinTables: JoinTable  */
#line 405 "yacc_sql.y"
                {}
#line 1764 "yacc_sql.tab.c"
    break;

  case 66: /* JoinTable: INNER JOIN ID ON condition condition_list  */
#line 408 "yacc_sql.y"
                                            {
    selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-3].string));
  }
#line 1772 "yacc_sql.tab.c"
    break;

  case 68: /* order_by: ORDER BY order_attr_list  */
#line 414 "yacc_sql.y"
                             {
  }
#line 1779 "yacc_sql.tab.c"
    break;

  case 69: /* order_attr_list: order_attr  */
#line 417 "yacc_sql.y"
             {
  }
#line 1786 "yacc_sql.tab.c"
    break;

  case 70: /* order_attr_list: order_attr_list COMMA order_attr  */
#line 419 "yacc_sql.y"
                                     {
  }
#line 1793 "yacc_sql.tab.c"
    break;

  case 71: /* order_attr: ID  */
#line 422 "yacc_sql.y"
     {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			selects_append_orderby(&CONTEXT->ssql->sstr.selection, &attr, 0);
  }
#line 1803 "yacc_sql.tab.c"
    break;

  case 72: /* order_attr: ID ASC  */
#line 427 "yacc_sql.y"
           {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_orderby(&CONTEXT->ssql->sstr.selection, &attr, 0);
  }
#line 1813 "yacc_sql.tab.c"
    break;

  case 73: /* order_attr: ID DESC  */
#line 432 "yacc_sql.y"
            {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_orderby(&CONTEXT->ssql->sstr.selection, &attr, 1);
  }
#line 1823 "yacc_sql.tab.c"
    break;

  case 74: /* order_attr: ID DOT ID  */
#line 437 "yacc_sql.y"
              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			selects_append_orderby(&CONTEXT->ssql->sstr.selection, &attr, 0);
  }
#line 1833 "yacc_sql.tab.c"
    break;

  case 75: /* order_attr: ID DOT ID ASC  */
#line 442 "yacc_sql.y"
                  {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_orderby(&CONTEXT->ssql->sstr.selection, &attr, 0);
  }
#line 1843 "yacc_sql.tab.c"
    break;

  case 76: /* order_attr: ID DOT ID DESC  */
#line 447 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_orderby(&CONTEXT->ssql->sstr.selection, &attr, 1);
  }
#line 1853 "yacc_sql.tab.c"
    break;

  case 78: /* group_by: GROUP BY group_attr_list  */
#line 455 "yacc_sql.y"
                             {
  }
#line 1860 "yacc_sql.tab.c"
    break;

  case 79: /* group_attr_list: group_attr  */
#line 458 "yacc_sql.y"
             {
  }
#line 1867 "yacc_sql.tab.c"
    break;

  case 80: /* group_attr_list: group_attr_list COMMA group_attr  */
#line 460 "yacc_sql.y"
                                     {
  }
#line 1874 "yacc_sql.tab.c"
    break;

  case 81: /* group_attr: ID  */
#line 463 "yacc_sql.y"
     {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			selects_append_groupby(&CONTEXT->ssql->sstr.selection, &attr);
  }
#line 1884 "yacc_sql.tab.c"
    break;

  case 82: /* group_attr: ID DOT ID  */
#line 468 "yacc_sql.y"
              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			selects_append_groupby(&CONTEXT->ssql->sstr.selection, &attr);
  }
#line 1894 "yacc_sql.tab.c"
    break;

  case 83: /* select_attr_list: select_attr  */
#line 475 "yacc_sql.y"
                {
    }
#line 1901 "yacc_sql.tab.c"
    break;

  case 84: /* select_attr_list: select_attr_list COMMA select_attr  */
#line 477 "yacc_sql.y"
                                         {}
#line 1907 "yacc_sql.tab.c"
    break;

  case 85: /* select_attr: simple_select_attr  */
#line 480 "yacc_sql.y"
                       {}
#line 1913 "yacc_sql.tab.c"
    break;

  case 86: /* select_attr: agg_attr  */
#line 481 "yacc_sql.y"
               {}
#line 1919 "yacc_sql.tab.c"
    break;

  case 87: /* simple_select_attr: STAR  */
#line 484 "yacc_sql.y"
         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_set_attribute(&CONTEXT->ssql->sstr.selection, &attr);
      CONTEXT->ssql->sstr.selection.attr_num++;
		}
#line 1930 "yacc_sql.tab.c"
    break;

  case 88: /* simple_select_attr: ID  */
#line 490 "yacc_sql.y"
         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			selects_set_attribute(&CONTEXT->ssql->sstr.selection, &attr);
      CONTEXT->ssql->sstr.selection.attr_num++;
		}
#line 1941 "yacc_sql.tab.c"
    break;

  case 89: /* simple_select_attr: ID DOT STAR  */
#line 496 "yacc_sql.y"
                  {
      RelAttr attr;
      relation_attr_init(&attr, (yyvsp[-2].string), "*");
      selects_set_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 1951 "yacc_sql.tab.c"
    break;

  case 90: /* simple_select_attr: ID DOT ID  */
#line 501 "yacc_sql.y"
                    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			selects_set_attribute(&CONTEXT->ssql->sstr.selection, &attr);
      CONTEXT->ssql->sstr.selection.attr_num++;
		}
#line 1962 "yacc_sql.tab.c"
    break;

  case 91: /* agg_attr: COUNT LBRACE agg_value RBRACE  */
#line 509 "yacc_sql.y"
                                  {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
      AggInfo *agg_info = &selection->attributes[selection->attr_num].attr.aggregation;
      agg_info->agg_type = AGG_COUNT;
      selection->aggregate_num++;
      selection->attr_num++;
    }
#line 1974 "yacc_sql.tab.c"
    break;

  case 92: /* agg_attr: MAX LBRACE agg_value RBRACE  */
#line 516 "yacc_sql.y"
                                  {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
      AggInfo *agg_info = &selection->attributes[selection->attr_num].attr.aggregation;
      agg_info->agg_type = AGG_MAX;
      selection->aggregate_num++;
      selection->attr_num++;
    }
#line 1986 "yacc_sql.tab.c"
    break;

  case 93: /* agg_attr: MIN LBRACE agg_value RBRACE  */
#line 523 "yacc_sql.y"
                                  {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
      AggInfo *agg_info = &selection->attributes[selection->attr_num].attr.aggregation;
      agg_info->agg_type = AGG_MIN;
      selection->aggregate_num++;
      selection->attr_num++;
    }
#line 1998 "yacc_sql.tab.c"
    break;

  case 94: /* agg_attr: AVG LBRACE agg_value RBRACE  */
#line 530 "yacc_sql.y"
                                  {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
      AggInfo *agg_info = &selection->attributes[selection->attr_num].attr.aggregation;
      agg_info->agg_type = AGG_AVG;
      selection->aggregate_num++;
      selection->attr_num++;
    }
#line 2010 "yacc_sql.tab.c"
    break;

  case 95: /* agg_value: STAR  */
#line 540 "yacc_sql.y"
         {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
			AggInfo ainfo;
      memset(&ainfo, 0, sizeof(AggInfo));
			relation_attr_init(&ainfo.agg_attr, NULL, "*");
      ainfo.need_all = 1;
      selects_set_aggregation(selection, &ainfo);
    }
#line 2023 "yacc_sql.tab.c"
    break;

  case 96: /* agg_value: ID  */
#line 549 "yacc_sql.y"
         {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
			AggInfo ainfo;
      memset(&ainfo, 0, sizeof(AggInfo));
			relation_attr_init(&ainfo.agg_attr, NULL, strdup((yyvsp[0].string)));
      selects_set_aggregation(selection, &ainfo);
    }
#line 2035 "yacc_sql.tab.c"
    break;

  case 97: /* agg_value: ID DOT ID  */
#line 556 "yacc_sql.y"
                {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
			AggInfo ainfo;
      memset(&ainfo, 0, sizeof(AggInfo));
			relation_attr_init(&ainfo.agg_attr, (yyvsp[-2].string), (yyvsp[0].string));
      ainfo.need_table_name = 1;
      selects_set_aggregation(selection, &ainfo);
    }
#line 2048 "yacc_sql.tab.c"
    break;

  case 98: /* agg_value: ID DOT STAR  */
#line 564 "yacc_sql.y"
                  {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
			AggInfo ainfo;
      memset(&ainfo, 0, sizeof(AggInfo));
			relation_attr_init(&ainfo.agg_attr, (yyvsp[-2].string), "*");
      ainfo.need_table_name = 1;
      ainfo.need_all = 1;
      selects_set_aggregation(selection, &ainfo);
    }
#line 2062 "yacc_sql.tab.c"
    break;

  case 99: /* agg_value: NUMBER  */
#line 574 "yacc_sql.y"
             {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
      AggInfo ainfo;
      memset(&ainfo, 0, sizeof(ainfo));
      ainfo.is_constant = 1;
  		value_init_integer(&ainfo.value, (yyvsp[0].number));
      selects_set_aggregation(selection, &ainfo);
		}
#line 2075 "yacc_sql.tab.c"
    break;

  case 100: /* agg_value: FLOAT  */
#line 582 "yacc_sql.y"
            {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
      AggInfo ainfo;
      memset(&ainfo, 0, sizeof(ainfo));
      ainfo.is_constant = 1;
  		value_init_float(&ainfo.value, (yyvsp[0].floats));
      selects_set_aggregation(selection, &ainfo);
		}
#line 2088 "yacc_sql.tab.c"
    break;

  case 102: /* where: WHERE condition condition_list  */
#line 593 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2096 "yacc_sql.tab.c"
    break;

  case 104: /* condition_list: AND condition condition_list  */
#line 599 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2104 "yacc_sql.tab.c"
    break;

  case 105: /* condition: ID comOp value  */
#line 605 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, 0, NULL, right_value, 0, NULL);
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
#line 2129 "yacc_sql.tab.c"
    break;

  case 106: /* condition: value comOp value  */
#line 626 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, 0, NULL, right_value, 0, NULL);
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
#line 2153 "yacc_sql.tab.c"
    break;

  case 107: /* condition: ID comOp ID  */
#line 646 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, 1, &right_attr, NULL, 0, NULL);
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
#line 2177 "yacc_sql.tab.c"
    break;

  case 108: /* condition: value comOp ID  */
#line 666 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, 1, &right_attr, NULL, 0, NULL);
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
#line 2203 "yacc_sql.tab.c"
    break;

  case 109: /* condition: ID DOT ID comOp value  */
#line 688 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, 0, NULL, right_value, 0, NULL);
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
#line 2228 "yacc_sql.tab.c"
    break;

  case 110: /* condition: value comOp ID DOT ID  */
#line 709 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, 1, &right_attr, NULL, 0, NULL);
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
#line 2253 "yacc_sql.tab.c"
    break;

  case 111: /* condition: ID DOT ID comOp ID DOT ID  */
#line 730 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, 1, &right_attr, NULL, 0, NULL);
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
#line 2276 "yacc_sql.tab.c"
    break;

  case 112: /* condition: ID comOp before_select select after_select  */
#line 748 "yacc_sql.y"
                                                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-4].string));
      Selects *selection = (yyvsp[0].select1);
			Condition condition;
      memset(&condition, 0, sizeof(Condition));
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, 0, NULL, NULL, 1, selection);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2290 "yacc_sql.tab.c"
    break;

  case 113: /* condition: before_select select after_select comOp ID  */
#line 757 "yacc_sql.y"
                                                 {
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));
      Selects *selection = (yyvsp[-2].select1);
			Condition condition;
      memset(&condition, 0, sizeof(Condition));
			condition_init(&condition, CONTEXT->comp, 0, NULL, NULL, 1, selection, 1, &right_attr, NULL, 0, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2304 "yacc_sql.tab.c"
    break;

  case 114: /* before_select: LBRACE  */
#line 769 "yacc_sql.y"
           {
      ParserContext *next_ctx_value = (ParserContext *)malloc(sizeof(ParserContext));
      // *next_ctx = malloc(sizeof(ParserContext));
      next_ctx_value->ssql = CONTEXT->ssql;
      next_ctx_value->select_length = CONTEXT->select_length;
      next_ctx_value->condition_length = CONTEXT->condition_length;
      next_ctx_value->from_length = CONTEXT->from_length;
      next_ctx_value->value_length = CONTEXT->value_length;
      next_ctx_value->aggregations_length = CONTEXT->aggregations_length;
      next_ctx_value->comp = CONTEXT->comp;
      next_ctx_value->next_ctx = NULL;
      memcpy(next_ctx_value->values, CONTEXT->values, MAX_NUM * sizeof(Value));
      memcpy(next_ctx_value->conditions, CONTEXT->conditions, MAX_NUM * sizeof(Condition));
      memcpy(next_ctx_value->id, CONTEXT->id, MAX_NUM * sizeof(char));
      memset(CONTEXT, 0, sizeof(ParserContext));
      ParserContext **next_ctx = &CONTEXT->next_ctx;
      *next_ctx = next_ctx_value;
      CONTEXT->ssql = calloc(1, sizeof(Query));
    }
#line 2328 "yacc_sql.tab.c"
    break;

  case 115: /* after_select: RBRACE  */
#line 790 "yacc_sql.y"
           {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
      ParserContext **next_ctx = &CONTEXT->next_ctx;
      ParserContext *next_ctx_value = *next_ctx;
      CONTEXT->ssql = next_ctx_value->ssql;
      CONTEXT->select_length = next_ctx_value->select_length;
      CONTEXT->condition_length = next_ctx_value->condition_length;
      CONTEXT->from_length = next_ctx_value->from_length;
      CONTEXT->value_length = next_ctx_value->value_length;
      CONTEXT->aggregations_length = next_ctx_value->aggregations_length;
      CONTEXT->comp = next_ctx_value->comp;
      memcpy(CONTEXT->values, next_ctx_value->values, MAX_NUM * sizeof(Value));
      memcpy(CONTEXT->conditions, next_ctx_value->conditions, MAX_NUM * sizeof(Condition));
      memcpy(CONTEXT->id, next_ctx_value->id, MAX_NUM * sizeof(char));
      free(*next_ctx);
      *next_ctx = NULL;
      (yyval.select1) = selection;
    }
#line 2351 "yacc_sql.tab.c"
    break;

  case 116: /* comOp: EQ  */
#line 810 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2357 "yacc_sql.tab.c"
    break;

  case 117: /* comOp: LT  */
#line 811 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2363 "yacc_sql.tab.c"
    break;

  case 118: /* comOp: GT  */
#line 812 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2369 "yacc_sql.tab.c"
    break;

  case 119: /* comOp: LE  */
#line 813 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2375 "yacc_sql.tab.c"
    break;

  case 120: /* comOp: GE  */
#line 814 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2381 "yacc_sql.tab.c"
    break;

  case 121: /* comOp: NE  */
#line 815 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2387 "yacc_sql.tab.c"
    break;

  case 122: /* comOp: NOT IN  */
#line 816 "yacc_sql.y"
             { CONTEXT->comp = NOT_ING; }
#line 2393 "yacc_sql.tab.c"
    break;

  case 123: /* comOp: IN  */
#line 817 "yacc_sql.y"
         { CONTEXT->comp = ING; }
#line 2399 "yacc_sql.tab.c"
    break;

  case 124: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 822 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2408 "yacc_sql.tab.c"
    break;


#line 2412 "yacc_sql.tab.c"

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

#line 827 "yacc_sql.y"

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
