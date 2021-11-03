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


#line 130 "yacc_sql.tab.c"

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
  YYSYMBOL_ORDER = 49,                     /* ORDER  */
  YYSYMBOL_GROUP = 50,                     /* GROUP  */
  YYSYMBOL_BY = 51,                        /* BY  */
  YYSYMBOL_UNIQUE = 52,                    /* UNIQUE  */
  YYSYMBOL_ASC = 53,                       /* ASC  */
  YYSYMBOL_NUMBER = 54,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 55,                     /* FLOAT  */
  YYSYMBOL_ID = 56,                        /* ID  */
  YYSYMBOL_PATH = 57,                      /* PATH  */
  YYSYMBOL_SSS = 58,                       /* SSS  */
  YYSYMBOL_STAR = 59,                      /* STAR  */
  YYSYMBOL_STRING_V = 60,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 61,                  /* $accept  */
  YYSYMBOL_commands = 62,                  /* commands  */
  YYSYMBOL_command = 63,                   /* command  */
  YYSYMBOL_exit = 64,                      /* exit  */
  YYSYMBOL_help = 65,                      /* help  */
  YYSYMBOL_sync = 66,                      /* sync  */
  YYSYMBOL_begin = 67,                     /* begin  */
  YYSYMBOL_commit = 68,                    /* commit  */
  YYSYMBOL_rollback = 69,                  /* rollback  */
  YYSYMBOL_drop_table = 70,                /* drop_table  */
  YYSYMBOL_show_tables = 71,               /* show_tables  */
  YYSYMBOL_desc_table = 72,                /* desc_table  */
  YYSYMBOL_create_index = 73,              /* create_index  */
  YYSYMBOL_index_attr_list = 74,           /* index_attr_list  */
  YYSYMBOL_create_unique_index = 75,       /* create_unique_index  */
  YYSYMBOL_drop_index = 76,                /* drop_index  */
  YYSYMBOL_create_table = 77,              /* create_table  */
  YYSYMBOL_attr_def_list = 78,             /* attr_def_list  */
  YYSYMBOL_attr_def = 79,                  /* attr_def  */
  YYSYMBOL_number = 80,                    /* number  */
  YYSYMBOL_type = 81,                      /* type  */
  YYSYMBOL_ID_get = 82,                    /* ID_get  */
  YYSYMBOL_insert = 83,                    /* insert  */
  YYSYMBOL_values_list = 84,               /* values_list  */
  YYSYMBOL_values = 85,                    /* values  */
  YYSYMBOL_value_list = 86,                /* value_list  */
  YYSYMBOL_value = 87,                     /* value  */
  YYSYMBOL_delete = 88,                    /* delete  */
  YYSYMBOL_update = 89,                    /* update  */
  YYSYMBOL_select = 90,                    /* select  */
  YYSYMBOL_order_by = 91,                  /* order_by  */
  YYSYMBOL_order_attr_list = 92,           /* order_attr_list  */
  YYSYMBOL_order_attr = 93,                /* order_attr  */
  YYSYMBOL_group_by = 94,                  /* group_by  */
  YYSYMBOL_group_attr_list = 95,           /* group_attr_list  */
  YYSYMBOL_group_attr = 96,                /* group_attr  */
  YYSYMBOL_select_attr_list = 97,          /* select_attr_list  */
  YYSYMBOL_select_attr = 98,               /* select_attr  */
  YYSYMBOL_simple_select_attr = 99,        /* simple_select_attr  */
  YYSYMBOL_agg_attr = 100,                 /* agg_attr  */
  YYSYMBOL_agg_value = 101,                /* agg_value  */
  YYSYMBOL_rel_list = 102,                 /* rel_list  */
  YYSYMBOL_where = 103,                    /* where  */
  YYSYMBOL_condition_list = 104,           /* condition_list  */
  YYSYMBOL_condition = 105,                /* condition  */
  YYSYMBOL_comOp = 106,                    /* comOp  */
  YYSYMBOL_load_data = 107                 /* load_data  */
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
#define YYLAST   227

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  112
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  226

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   315


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
      55,    56,    57,    58,    59,    60
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   144,   144,   146,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   171,   176,   181,   187,   193,   199,   205,   211,
     217,   224,   232,   234,   240,   247,   254,   263,   265,   269,
     280,   295,   298,   299,   300,   301,   304,   313,   318,   320,
     324,   329,   330,   332,   335,   338,   345,   355,   365,   382,
     384,   387,   389,   392,   397,   402,   407,   412,   417,   423,
     425,   428,   430,   433,   438,   445,   447,   450,   451,   454,
     460,   466,   471,   479,   486,   493,   500,   510,   519,   526,
     534,   544,   552,   561,   563,   567,   569,   573,   575,   580,
     601,   621,   641,   663,   684,   705,   727,   728,   729,   730,
     731,   732,   736
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
  "LT", "GT", "LE", "GE", "NE", "ORDER", "GROUP", "BY", "UNIQUE", "ASC",
  "NUMBER", "FLOAT", "ID", "PATH", "SSS", "STAR", "STRING_V", "$accept",
  "commands", "command", "exit", "help", "sync", "begin", "commit",
  "rollback", "drop_table", "show_tables", "desc_table", "create_index",
  "index_attr_list", "create_unique_index", "drop_index", "create_table",
  "attr_def_list", "attr_def", "number", "type", "ID_get", "insert",
  "values_list", "values", "value_list", "value", "delete", "update",
  "select", "order_by", "order_attr_list", "order_attr", "group_by",
  "group_attr_list", "group_attr", "select_attr_list", "select_attr",
  "simple_select_attr", "agg_attr", "agg_value", "rel_list", "where",
  "condition_list", "condition", "comOp", "load_data", YY_NULLPTR
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
    -118,    13,  -118,     2,    94,    -9,   -45,    14,    73,    47,
     -10,    34,    82,    91,    92,    98,   100,    63,  -118,  -118,
    -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,
    -118,  -118,  -118,  -118,  -118,  -118,  -118,    49,    50,    99,
      52,    53,    90,    93,    95,    96,    79,  -118,    -2,  -118,
    -118,  -118,   109,   111,  -118,    61,    62,    81,  -118,  -118,
    -118,  -118,  -118,    78,   101,    83,    67,   121,   122,   -40,
     -40,   -40,   -40,   -33,    -9,    70,  -118,  -118,    97,   102,
      71,    72,    76,    77,    89,  -118,  -118,  -118,  -118,   103,
    -118,   108,   113,   115,   116,  -118,  -118,  -118,   117,   120,
      17,   138,   104,   110,  -118,   123,    29,   124,    86,   -17,
    -118,  -118,  -118,  -118,   105,   102,    38,   126,  -118,  -118,
      16,  -118,    22,   112,  -118,    38,   140,    76,   129,  -118,
    -118,  -118,  -118,   131,   106,   132,  -118,  -118,   117,   107,
     133,   120,   150,   114,  -118,  -118,  -118,  -118,  -118,  -118,
      23,    28,    17,  -118,   102,   118,   123,   151,   119,  -118,
      19,   125,  -118,   127,   128,    38,   135,   126,  -118,    22,
    -118,  -118,   134,  -118,   112,   155,   156,  -118,  -118,  -118,
     139,   160,   130,   143,   136,   137,   162,   133,  -118,  -118,
      33,   141,  -118,  -118,  -118,  -118,  -118,  -118,   164,   144,
     146,  -118,   142,  -118,  -118,   147,  -118,  -118,  -118,   145,
     136,    -8,   149,  -118,   148,  -118,  -118,  -118,   152,  -118,
     142,  -118,    -7,  -118,  -118,  -118
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    21,
      20,    15,    16,    17,    18,     9,    10,    11,    12,    13,
      14,     8,     5,     7,     6,     4,    19,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    80,    79,     0,    75,
      77,    78,     0,     0,    24,     0,     0,     0,    25,    26,
      27,    23,    22,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    30,    29,     0,    95,
       0,     0,     0,     0,     0,    28,    35,    91,    92,    88,
      87,     0,     0,     0,     0,    82,    81,    76,    93,     0,
       0,     0,     0,     0,    46,    37,     0,     0,     0,     0,
      83,    84,    85,    86,     0,    95,     0,    48,    53,    54,
       0,    55,     0,    97,    56,     0,     0,     0,     0,    42,
      43,    44,    45,    40,     0,     0,    89,    90,    93,    69,
      51,     0,     0,     0,   106,   107,   108,   109,   110,   111,
       0,     0,     0,    96,    95,     0,    37,     0,     0,    33,
       0,     0,    94,     0,    59,     0,     0,    48,    47,     0,
     101,    99,   102,   100,    97,     0,     0,    38,    36,    41,
       0,     0,     0,     0,     0,     0,     0,    51,    50,    49,
       0,     0,    98,    57,   112,    39,    31,    32,     0,    73,
      70,    71,     0,    58,    52,     0,   103,   104,    34,     0,
       0,    63,    60,    61,     0,    74,    72,    65,     0,    64,
       0,   105,    66,    62,    68,    67
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,
    -118,  -118,  -118,  -118,  -118,  -118,  -118,    24,    42,  -118,
    -118,  -118,  -118,     5,    41,   -12,  -116,  -118,  -118,  -118,
    -118,  -118,   -37,  -118,  -118,   -26,  -118,   153,  -118,  -118,
      27,    51,  -103,    11,    35,  -117,  -118
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   160,    29,    30,    31,   128,   105,   180,
     133,   106,    32,   142,   117,   166,   122,    33,    34,    35,
     186,   212,   213,   164,   200,   201,    48,    49,    50,    51,
      91,   115,   101,   153,   123,   150,    36
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
     140,    42,    43,    44,    45,   151,   217,   224,    37,   154,
      38,    52,   139,     2,    87,    88,    89,     3,     4,    90,
      74,    53,     5,    95,   218,    56,    96,     6,     7,     8,
       9,    10,    11,    75,   171,   173,    12,    13,    14,   136,
     181,   182,   137,    15,    16,   219,   225,    46,   143,   187,
      47,   175,   190,    17,    39,   129,   130,   131,   132,   144,
     145,   146,   147,   148,   149,   144,   145,   146,   147,   148,
     149,   118,   119,   120,   206,   121,    54,   118,   119,   170,
      55,   121,   118,   119,   172,    58,   121,   118,   119,   205,
      57,   121,   118,   119,    59,    60,   121,    92,    93,    94,
      40,    61,    41,    62,    63,    64,    65,    66,    67,    68,
      69,    73,    76,    70,    77,    71,    72,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    98,   102,   108,   110,
     103,    99,   104,   107,   111,   109,   112,   113,   100,   114,
     116,   124,   135,   126,   134,   127,   155,   125,   141,   152,
     157,   158,   161,   168,   178,   165,   188,   163,   193,   194,
     195,   138,   159,   196,   198,   203,   191,   208,   210,   156,
     169,   220,   189,   179,   176,   204,   209,   185,   184,   214,
     177,   183,   167,   223,   216,   192,   197,   174,   202,   162,
       0,     0,   199,     0,     0,     0,     0,   207,   211,     0,
       0,   215,     0,     0,   221,     0,     0,     0,   222,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    97
};

static const yytype_int16 yycheck[] =
{
     116,    10,    11,    12,    13,   122,    14,    14,     6,   125,
       8,    56,   115,     0,    54,    55,    56,     4,     5,    59,
      22,     7,     9,    56,    32,    35,    59,    14,    15,    16,
      17,    18,    19,    35,   150,   151,    23,    24,    25,    56,
      21,    22,    59,    30,    31,    53,    53,    56,    32,   165,
      59,   154,   169,    40,    52,    26,    27,    28,    29,    43,
      44,    45,    46,    47,    48,    43,    44,    45,    46,    47,
      48,    54,    55,    56,   190,    58,     3,    54,    55,    56,
      33,    58,    54,    55,    56,     3,    58,    54,    55,    56,
      56,    58,    54,    55,     3,     3,    58,    70,    71,    72,
       6,     3,     8,     3,    41,    56,    56,     8,    56,    56,
      20,    32,     3,    20,     3,    20,    20,    56,    56,    38,
      42,    20,    39,    56,     3,     3,    56,    56,    39,    21,
      58,    34,    56,    56,    21,    32,    21,    21,    36,    22,
      20,     3,    56,    33,    20,    22,     6,    43,    22,    37,
      21,    20,    20,     3,     3,    22,    21,    50,     3,     3,
      21,    56,    56,     3,    21,     3,    32,     3,    22,   127,
      56,    22,   167,    54,    56,   187,    32,    49,    51,    32,
     156,    56,   141,   220,   210,   174,    56,   152,    51,   138,
      -1,    -1,    56,    -1,    -1,    -1,    -1,    56,    56,    -1,
      -1,    56,    -1,    -1,    56,    -1,    -1,    -1,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    74
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    62,     0,     4,     5,     9,    14,    15,    16,    17,
      18,    19,    23,    24,    25,    30,    31,    40,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    75,
      76,    77,    83,    88,    89,    90,   107,     6,     8,    52,
       6,     8,    10,    11,    12,    13,    56,    59,    97,    98,
      99,   100,    56,     7,     3,    33,    35,    56,     3,     3,
       3,     3,     3,    41,    56,    56,     8,    56,    56,    20,
      20,    20,    20,    32,    22,    35,     3,     3,    56,    56,
      38,    42,    20,    39,    56,     3,     3,    54,    55,    56,
      59,   101,   101,   101,   101,    56,    59,    98,    56,    34,
      36,   103,    56,    58,    56,    79,    82,    56,    39,    32,
      21,    21,    21,    21,    22,   102,    20,    85,    54,    55,
      56,    58,    87,   105,     3,    43,    33,    22,    78,    26,
      27,    28,    29,    81,    20,    56,    56,    59,    56,   103,
      87,    22,    84,    32,    43,    44,    45,    46,    47,    48,
     106,   106,    37,   104,    87,     6,    79,    21,    20,    56,
      74,    20,   102,    50,    94,    22,    86,    85,     3,    56,
      56,    87,    56,    87,   105,   103,    56,    78,     3,    54,
      80,    21,    22,    56,    51,    49,    91,    87,    21,    84,
     106,    32,   104,     3,     3,    21,     3,    56,    21,    56,
      95,    96,    51,     3,    86,    56,    87,    56,     3,    32,
      22,    56,    92,    93,    32,    56,    96,    14,    32,    53,
      22,    56,    56,    93,    14,    53
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    61,    62,    62,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    74,    75,    76,    77,    78,    78,    79,
      79,    80,    81,    81,    81,    81,    82,    83,    84,    84,
      85,    86,    86,    87,    87,    87,    88,    89,    90,    91,
      91,    92,    92,    93,    93,    93,    93,    93,    93,    94,
      94,    95,    95,    96,    96,    97,    97,    98,    98,    99,
      99,    99,    99,   100,   100,   100,   100,   101,   101,   101,
     101,   101,   101,   102,   102,   103,   103,   104,   104,   105,
     105,   105,   105,   105,   105,   105,   106,   106,   106,   106,
     106,   106,   107
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     4,     3,
       3,     9,     3,     1,    10,     4,     8,     0,     3,     5,
       2,     1,     1,     1,     1,     1,     1,     7,     0,     3,
       4,     0,     3,     1,     1,     1,     5,     8,     9,     0,
       3,     1,     3,     1,     2,     2,     3,     4,     4,     0,
       3,     1,     3,     1,     3,     1,     3,     1,     1,     1,
       1,     3,     3,     4,     4,     4,     4,     1,     1,     3,
       3,     1,     1,     0,     3,     0,     3,     0,     3,     3,
       3,     3,     3,     5,     5,     7,     1,     1,     1,     1,
       1,     1,     8
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
#line 171 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1392 "yacc_sql.tab.c"
    break;

  case 23: /* help: HELP SEMICOLON  */
#line 176 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1400 "yacc_sql.tab.c"
    break;

  case 24: /* sync: SYNC SEMICOLON  */
#line 181 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1408 "yacc_sql.tab.c"
    break;

  case 25: /* begin: TRX_BEGIN SEMICOLON  */
#line 187 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1416 "yacc_sql.tab.c"
    break;

  case 26: /* commit: TRX_COMMIT SEMICOLON  */
#line 193 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1424 "yacc_sql.tab.c"
    break;

  case 27: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 199 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1432 "yacc_sql.tab.c"
    break;

  case 28: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 205 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1441 "yacc_sql.tab.c"
    break;

  case 29: /* show_tables: SHOW TABLES SEMICOLON  */
#line 211 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1449 "yacc_sql.tab.c"
    break;

  case 30: /* desc_table: DESC ID SEMICOLON  */
#line 217 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1458 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE INDEX ID ON ID LBRACE index_attr_list RBRACE SEMICOLON  */
#line 225 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), 0);
		}
#line 1467 "yacc_sql.tab.c"
    break;

  case 32: /* index_attr_list: index_attr_list COMMA ID  */
#line 232 "yacc_sql.y"
                             {
    }
#line 1474 "yacc_sql.tab.c"
    break;

  case 33: /* index_attr_list: ID  */
#line 234 "yacc_sql.y"
         {
      append_create_index(&CONTEXT->ssql->sstr.create_index, (yyvsp[0].string));
    }
#line 1482 "yacc_sql.tab.c"
    break;

  case 34: /* create_unique_index: CREATE UNIQUE INDEX ID ON ID LBRACE ID RBRACE SEMICOLON  */
#line 241 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string), 1);
		}
#line 1491 "yacc_sql.tab.c"
    break;

  case 35: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 248 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1500 "yacc_sql.tab.c"
    break;

  case 36: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 255 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1512 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 265 "yacc_sql.y"
                                   {    }
#line 1518 "yacc_sql.tab.c"
    break;

  case 39: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 270 "yacc_sql.y"
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
#line 1533 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def: ID_get type  */
#line 281 "yacc_sql.y"
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
#line 1550 "yacc_sql.tab.c"
    break;

  case 41: /* number: NUMBER  */
#line 295 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1556 "yacc_sql.tab.c"
    break;

  case 42: /* type: INT_T  */
#line 298 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1562 "yacc_sql.tab.c"
    break;

  case 43: /* type: STRING_T  */
#line 299 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1568 "yacc_sql.tab.c"
    break;

  case 44: /* type: FLOAT_T  */
#line 300 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1574 "yacc_sql.tab.c"
    break;

  case 45: /* type: DATE_T  */
#line 301 "yacc_sql.y"
                { (yyval.number)=DATES; }
#line 1580 "yacc_sql.tab.c"
    break;

  case 46: /* ID_get: ID  */
#line 305 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1589 "yacc_sql.tab.c"
    break;

  case 47: /* insert: INSERT INTO ID VALUES values values_list SEMICOLON  */
#line 313 "yacc_sql.y"
                                                       {
			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string));
    }
#line 1598 "yacc_sql.tab.c"
    break;

  case 49: /* values_list: COMMA values values_list  */
#line 320 "yacc_sql.y"
                                {
    }
#line 1605 "yacc_sql.tab.c"
    break;

  case 50: /* values: LBRACE value value_list RBRACE  */
#line 324 "yacc_sql.y"
                                    {
      insert_value_tuple(&CONTEXT->ssql->sstr.insertion, CONTEXT->values, CONTEXT->value_length);
      CONTEXT->value_length=0;
    }
#line 1614 "yacc_sql.tab.c"
    break;

  case 52: /* value_list: COMMA value value_list  */
#line 330 "yacc_sql.y"
                              {}
#line 1620 "yacc_sql.tab.c"
    break;

  case 53: /* value: NUMBER  */
#line 332 "yacc_sql.y"
          {
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1628 "yacc_sql.tab.c"
    break;

  case 54: /* value: FLOAT  */
#line 335 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1636 "yacc_sql.tab.c"
    break;

  case 55: /* value: SSS  */
#line 338 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1645 "yacc_sql.tab.c"
    break;

  case 56: /* delete: DELETE FROM ID where SEMICOLON  */
#line 346 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1657 "yacc_sql.tab.c"
    break;

  case 57: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 356 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1669 "yacc_sql.tab.c"
    break;

  case 58: /* select: SELECT select_attr_list FROM ID rel_list where group_by order_by SEMICOLON  */
#line 366 "yacc_sql.y"
                {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-5].string));

			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
	}
#line 1689 "yacc_sql.tab.c"
    break;

  case 60: /* order_by: ORDER BY order_attr_list  */
#line 384 "yacc_sql.y"
                             {
  }
#line 1696 "yacc_sql.tab.c"
    break;

  case 61: /* order_attr_list: order_attr  */
#line 387 "yacc_sql.y"
             {
  }
#line 1703 "yacc_sql.tab.c"
    break;

  case 62: /* order_attr_list: order_attr_list COMMA order_attr  */
#line 389 "yacc_sql.y"
                                     {
  }
#line 1710 "yacc_sql.tab.c"
    break;

  case 63: /* order_attr: ID  */
#line 392 "yacc_sql.y"
     {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			selects_append_orderby(&CONTEXT->ssql->sstr.selection, &attr, 0);
  }
#line 1720 "yacc_sql.tab.c"
    break;

  case 64: /* order_attr: ID ASC  */
#line 397 "yacc_sql.y"
           {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_orderby(&CONTEXT->ssql->sstr.selection, &attr, 0);
  }
#line 1730 "yacc_sql.tab.c"
    break;

  case 65: /* order_attr: ID DESC  */
#line 402 "yacc_sql.y"
            {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_orderby(&CONTEXT->ssql->sstr.selection, &attr, 1);
  }
#line 1740 "yacc_sql.tab.c"
    break;

  case 66: /* order_attr: ID DOT ID  */
#line 407 "yacc_sql.y"
              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			selects_append_orderby(&CONTEXT->ssql->sstr.selection, &attr, 0);
  }
#line 1750 "yacc_sql.tab.c"
    break;

  case 67: /* order_attr: ID DOT ID ASC  */
#line 412 "yacc_sql.y"
                  {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_orderby(&CONTEXT->ssql->sstr.selection, &attr, 0);
  }
#line 1760 "yacc_sql.tab.c"
    break;

  case 68: /* order_attr: ID DOT ID DESC  */
#line 417 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_orderby(&CONTEXT->ssql->sstr.selection, &attr, 1);
  }
#line 1770 "yacc_sql.tab.c"
    break;

  case 70: /* group_by: GROUP BY group_attr_list  */
#line 425 "yacc_sql.y"
                             {
  }
#line 1777 "yacc_sql.tab.c"
    break;

  case 71: /* group_attr_list: group_attr  */
#line 428 "yacc_sql.y"
             {
  }
#line 1784 "yacc_sql.tab.c"
    break;

  case 72: /* group_attr_list: group_attr_list COMMA group_attr  */
#line 430 "yacc_sql.y"
                                     {
  }
#line 1791 "yacc_sql.tab.c"
    break;

  case 73: /* group_attr: ID  */
#line 433 "yacc_sql.y"
     {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			selects_append_groupby(&CONTEXT->ssql->sstr.selection, &attr);
  }
#line 1801 "yacc_sql.tab.c"
    break;

  case 74: /* group_attr: ID DOT ID  */
#line 438 "yacc_sql.y"
              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			selects_append_groupby(&CONTEXT->ssql->sstr.selection, &attr);
  }
#line 1811 "yacc_sql.tab.c"
    break;

  case 75: /* select_attr_list: select_attr  */
#line 445 "yacc_sql.y"
                {
    }
#line 1818 "yacc_sql.tab.c"
    break;

  case 76: /* select_attr_list: select_attr_list COMMA select_attr  */
#line 447 "yacc_sql.y"
                                         {}
#line 1824 "yacc_sql.tab.c"
    break;

  case 77: /* select_attr: simple_select_attr  */
#line 450 "yacc_sql.y"
                       {}
#line 1830 "yacc_sql.tab.c"
    break;

  case 78: /* select_attr: agg_attr  */
#line 451 "yacc_sql.y"
               {}
#line 1836 "yacc_sql.tab.c"
    break;

  case 79: /* simple_select_attr: STAR  */
#line 454 "yacc_sql.y"
         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_set_attribute(&CONTEXT->ssql->sstr.selection, &attr);
      CONTEXT->ssql->sstr.selection.attr_num++;
		}
#line 1847 "yacc_sql.tab.c"
    break;

  case 80: /* simple_select_attr: ID  */
#line 460 "yacc_sql.y"
         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			selects_set_attribute(&CONTEXT->ssql->sstr.selection, &attr);
      CONTEXT->ssql->sstr.selection.attr_num++;
		}
#line 1858 "yacc_sql.tab.c"
    break;

  case 81: /* simple_select_attr: ID DOT STAR  */
#line 466 "yacc_sql.y"
                  {
      RelAttr attr;
      relation_attr_init(&attr, (yyvsp[-2].string), "*");
      selects_set_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 1868 "yacc_sql.tab.c"
    break;

  case 82: /* simple_select_attr: ID DOT ID  */
#line 471 "yacc_sql.y"
                    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			selects_set_attribute(&CONTEXT->ssql->sstr.selection, &attr);
      CONTEXT->ssql->sstr.selection.attr_num++;
		}
#line 1879 "yacc_sql.tab.c"
    break;

  case 83: /* agg_attr: COUNT LBRACE agg_value RBRACE  */
#line 479 "yacc_sql.y"
                                  {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
      AggInfo *agg_info = &selection->attributes[selection->attr_num].attr.aggregation;
      agg_info->agg_type = AGG_COUNT;
      selection->aggregate_num++;
      selection->attr_num++;
    }
#line 1891 "yacc_sql.tab.c"
    break;

  case 84: /* agg_attr: MAX LBRACE agg_value RBRACE  */
#line 486 "yacc_sql.y"
                                  {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
      AggInfo *agg_info = &selection->attributes[selection->attr_num].attr.aggregation;
      agg_info->agg_type = AGG_MAX;
      selection->aggregate_num++;
      selection->attr_num++;
    }
#line 1903 "yacc_sql.tab.c"
    break;

  case 85: /* agg_attr: MIN LBRACE agg_value RBRACE  */
#line 493 "yacc_sql.y"
                                  {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
      AggInfo *agg_info = &selection->attributes[selection->attr_num].attr.aggregation;
      agg_info->agg_type = AGG_MIN;
      selection->aggregate_num++;
      selection->attr_num++;
    }
#line 1915 "yacc_sql.tab.c"
    break;

  case 86: /* agg_attr: AVG LBRACE agg_value RBRACE  */
#line 500 "yacc_sql.y"
                                  {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
      AggInfo *agg_info = &selection->attributes[selection->attr_num].attr.aggregation;
      agg_info->agg_type = AGG_AVG;
      selection->aggregate_num++;
      selection->attr_num++;
    }
#line 1927 "yacc_sql.tab.c"
    break;

  case 87: /* agg_value: STAR  */
#line 510 "yacc_sql.y"
         {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
			AggInfo ainfo;
      memset(&ainfo, 0, sizeof(AggInfo));
			relation_attr_init(&ainfo.agg_attr, NULL, "*");
      ainfo.need_all = 1;
      selects_set_aggregation(selection, &ainfo);
    }
#line 1940 "yacc_sql.tab.c"
    break;

  case 88: /* agg_value: ID  */
#line 519 "yacc_sql.y"
         {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
			AggInfo ainfo;
      memset(&ainfo, 0, sizeof(AggInfo));
			relation_attr_init(&ainfo.agg_attr, NULL, strdup((yyvsp[0].string)));
      selects_set_aggregation(selection, &ainfo);
    }
#line 1952 "yacc_sql.tab.c"
    break;

  case 89: /* agg_value: ID DOT ID  */
#line 526 "yacc_sql.y"
                {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
			AggInfo ainfo;
      memset(&ainfo, 0, sizeof(AggInfo));
			relation_attr_init(&ainfo.agg_attr, (yyvsp[-2].string), (yyvsp[0].string));
      ainfo.need_table_name = 1;
      selects_set_aggregation(selection, &ainfo);
    }
#line 1965 "yacc_sql.tab.c"
    break;

  case 90: /* agg_value: ID DOT STAR  */
#line 534 "yacc_sql.y"
                  {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
			AggInfo ainfo;
      memset(&ainfo, 0, sizeof(AggInfo));
			relation_attr_init(&ainfo.agg_attr, (yyvsp[-2].string), "*");
      ainfo.need_table_name = 1;
      ainfo.need_all = 1;
      selects_set_aggregation(selection, &ainfo);
    }
#line 1979 "yacc_sql.tab.c"
    break;

  case 91: /* agg_value: NUMBER  */
#line 544 "yacc_sql.y"
             {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
      AggInfo ainfo;
      memset(&ainfo, 0, sizeof(ainfo));
      ainfo.is_constant = 1;
  		value_init_integer(&ainfo.value, (yyvsp[0].number));
      selects_set_aggregation(selection, &ainfo);
		}
#line 1992 "yacc_sql.tab.c"
    break;

  case 92: /* agg_value: FLOAT  */
#line 552 "yacc_sql.y"
            {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
      AggInfo ainfo;
      memset(&ainfo, 0, sizeof(ainfo));
      ainfo.is_constant = 1;
  		value_init_float(&ainfo.value, (yyvsp[0].floats));
      selects_set_aggregation(selection, &ainfo);
		}
#line 2005 "yacc_sql.tab.c"
    break;

  case 94: /* rel_list: COMMA ID rel_list  */
#line 563 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 2013 "yacc_sql.tab.c"
    break;

  case 96: /* where: WHERE condition condition_list  */
#line 569 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2021 "yacc_sql.tab.c"
    break;

  case 98: /* condition_list: AND condition condition_list  */
#line 575 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2029 "yacc_sql.tab.c"
    break;

  case 99: /* condition: ID comOp value  */
#line 581 "yacc_sql.y"
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
#line 2054 "yacc_sql.tab.c"
    break;

  case 100: /* condition: value comOp value  */
#line 602 "yacc_sql.y"
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
#line 2078 "yacc_sql.tab.c"
    break;

  case 101: /* condition: ID comOp ID  */
#line 622 "yacc_sql.y"
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
#line 2102 "yacc_sql.tab.c"
    break;

  case 102: /* condition: value comOp ID  */
#line 642 "yacc_sql.y"
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
#line 2128 "yacc_sql.tab.c"
    break;

  case 103: /* condition: ID DOT ID comOp value  */
#line 664 "yacc_sql.y"
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
#line 2153 "yacc_sql.tab.c"
    break;

  case 104: /* condition: value comOp ID DOT ID  */
#line 685 "yacc_sql.y"
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
#line 2178 "yacc_sql.tab.c"
    break;

  case 105: /* condition: ID DOT ID comOp ID DOT ID  */
#line 706 "yacc_sql.y"
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
#line 2201 "yacc_sql.tab.c"
    break;

  case 106: /* comOp: EQ  */
#line 727 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2207 "yacc_sql.tab.c"
    break;

  case 107: /* comOp: LT  */
#line 728 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2213 "yacc_sql.tab.c"
    break;

  case 108: /* comOp: GT  */
#line 729 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2219 "yacc_sql.tab.c"
    break;

  case 109: /* comOp: LE  */
#line 730 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2225 "yacc_sql.tab.c"
    break;

  case 110: /* comOp: GE  */
#line 731 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2231 "yacc_sql.tab.c"
    break;

  case 111: /* comOp: NE  */
#line 732 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2237 "yacc_sql.tab.c"
    break;

  case 112: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 737 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2246 "yacc_sql.tab.c"
    break;


#line 2250 "yacc_sql.tab.c"

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

#line 742 "yacc_sql.y"

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
