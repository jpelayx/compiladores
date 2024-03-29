/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"


// Eduardo Rhoden e Julia Rodrigues :)

#include <stdio.h>
#include <stdbool.h>
#include "ast.h"
#include "valor_token.h"
#include "tabela_simbolos.h"
#include "escopo.h"
#include "instr.h"

int yylex(void);
void yyerror (char const *s);
int get_line_number();


extern void *arvore;

pilha_t *escopo = NULL;

operando_instr_t *label_main = NULL;


#line 95 "parser.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 26 "parser.y"
 #include "ast.h" 
#line 27 "parser.y"
 #include "valor_token.h" 
#line 28 "parser.y"
 #include "tabela_simbolos.h" 
#line 29 "parser.y"
 #include "escopo.h" 
#line 30 "parser.y"
 #include "instr.h" 

#line 149 "parser.tab.c"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TK_PR_INT = 258,
    TK_PR_FLOAT = 259,
    TK_PR_BOOL = 260,
    TK_PR_CHAR = 261,
    TK_PR_STRING = 262,
    TK_PR_IF = 263,
    TK_PR_THEN = 264,
    TK_PR_ELSE = 265,
    TK_PR_WHILE = 266,
    TK_PR_DO = 267,
    TK_PR_INPUT = 268,
    TK_PR_OUTPUT = 269,
    TK_PR_RETURN = 270,
    TK_PR_CONST = 271,
    TK_PR_STATIC = 272,
    TK_PR_FOREACH = 273,
    TK_PR_FOR = 274,
    TK_PR_SWITCH = 275,
    TK_PR_CASE = 276,
    TK_PR_BREAK = 277,
    TK_PR_CONTINUE = 278,
    TK_PR_CLASS = 279,
    TK_PR_PRIVATE = 280,
    TK_PR_PUBLIC = 281,
    TK_PR_PROTECTED = 282,
    TK_PR_END = 283,
    TK_PR_DEFAULT = 284,
    TK_OC_LE = 285,
    TK_OC_GE = 286,
    TK_OC_EQ = 287,
    TK_OC_NE = 288,
    TK_OC_AND = 289,
    TK_OC_OR = 290,
    TK_OC_SL = 291,
    TK_OC_SR = 292,
    TK_LIT_INT = 293,
    TK_LIT_FLOAT = 294,
    TK_LIT_FALSE = 295,
    TK_LIT_TRUE = 296,
    TK_LIT_CHAR = 297,
    TK_LIT_STRING = 298,
    TK_IDENTIFICADOR = 299,
    TOKEN_ERRO = 300,
    avaliacao_logica = 303,
    endereco_variavel = 304,
    valor_ponteiro = 305,
    inverte_sinal = 306
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 32 "parser.y"

	valor_token_t *valor_lexico;
	ast_t *nodo;
	tipos_semanticos_t tipo;

#line 216 "parser.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */



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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   346

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  76
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  46
/* YYNRULES -- Number of rules.  */
#define YYNRULES  119
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  217

#define YYUNDEFTOK  2
#define YYMAXUTOK   306


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    54,     2,    57,    59,    56,    55,     2,
      74,    75,    49,    47,    71,    48,     2,    50,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    63,    70,
      51,    53,    52,    60,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    68,     2,    69,    58,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    72,    46,    73,     2,     2,     2,     2,
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
      45,    61,    62,    64,    65,    66,    67
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   162,   162,   170,   177,   185,   187,   188,   189,   190,
     191,   193,   193,   195,   195,   197,   198,   200,   231,   235,
     237,   270,   273,   277,   280,   284,   292,   294,   302,   305,
     307,   320,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   336,   346,   348,   350,   354,   363,   364,
     365,   366,   367,   368,   371,   372,   378,   379,   381,   404,
     412,   419,   421,   422,   424,   425,   471,   484,   485,   487,
     504,   505,   506,   508,   541,   542,   544,   573,   595,   601,
     606,   607,   608,   620,   621,   625,   631,   635,   639,   643,
     648,   657,   666,   671,   681,   691,   697,   703,   709,   714,
     721,   732,   733,   734,   737,   741,   746,   758,   770,   781,
     792,   803,   815,   827,   841,   852,   853,   854,   855,   857
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TK_PR_INT", "TK_PR_FLOAT", "TK_PR_BOOL",
  "TK_PR_CHAR", "TK_PR_STRING", "TK_PR_IF", "TK_PR_THEN", "TK_PR_ELSE",
  "TK_PR_WHILE", "TK_PR_DO", "TK_PR_INPUT", "TK_PR_OUTPUT", "TK_PR_RETURN",
  "TK_PR_CONST", "TK_PR_STATIC", "TK_PR_FOREACH", "TK_PR_FOR",
  "TK_PR_SWITCH", "TK_PR_CASE", "TK_PR_BREAK", "TK_PR_CONTINUE",
  "TK_PR_CLASS", "TK_PR_PRIVATE", "TK_PR_PUBLIC", "TK_PR_PROTECTED",
  "TK_PR_END", "TK_PR_DEFAULT", "TK_OC_LE", "TK_OC_GE", "TK_OC_EQ",
  "TK_OC_NE", "TK_OC_AND", "TK_OC_OR", "TK_OC_SL", "TK_OC_SR",
  "TK_LIT_INT", "TK_LIT_FLOAT", "TK_LIT_FALSE", "TK_LIT_TRUE",
  "TK_LIT_CHAR", "TK_LIT_STRING", "TK_IDENTIFICADOR", "TOKEN_ERRO", "'|'",
  "'+'", "'-'", "'*'", "'/'", "'<'", "'>'", "'='", "'!'", "'&'", "'%'",
  "'#'", "'^'", "'$'", "'?'", "\"ternario\"", "\"unario\"", "':'",
  "avaliacao_logica", "endereco_variavel", "valor_ponteiro",
  "inverte_sinal", "'['", "']'", "';'", "','", "'{'", "'}'", "'('", "')'",
  "$accept", "input", "programa", "tipo", "estatico", "constante", "vetor",
  "var_global", "lista_identificadores_g", "funcao", "bloco_cmd_inicio",
  "bloco_cmd_fim", "corpo_funcao", "cabecalho", "parametros",
  "lista_parametros", "bloco_cmd", "lista_comandos", "comando",
  "declaracao_variavel", "lista_identificadores_l", "inicializa_variavel",
  "literal", "identificador_ou_literal", "acesso_vetor", "atribuicao",
  "entrada", "saida", "parametro_chamada_funcao",
  "mais_parametros_chamada_funcao", "chamada_de_funcao", "shift",
  "token_shift", "retorno", "controle_fluxo", "cf_if", "cf_else", "cf_for",
  "cf_while", "literal_numerico", "operandos_aritmeticos",
  "expressao_aritmetica", "literal_booleano", "operandos_booleanos",
  "expressao_booleana", "expressao", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   124,    43,    45,    42,
      47,    60,    62,    61,    33,    38,    37,    35,    94,    36,
      63,   301,   302,    58,   303,   304,   305,   306,    91,    93,
      59,    44,   123,   125,    40,    41
};
# endif

#define YYPACT_NINF (-142)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-118)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -142,    22,    13,  -142,  -142,   137,  -142,  -142,   -34,  -142,
    -142,  -142,  -142,  -142,   -20,  -142,     9,   -26,    87,    20,
      -6,  -142,  -142,   -12,    -8,    26,    50,   198,     0,     8,
      12,    43,  -142,    70,  -142,    29,  -142,    33,    42,    60,
      62,    77,    78,    80,    82,  -142,  -142,  -142,    27,  -142,
     137,    79,    37,   198,   198,  -142,  -142,  -142,  -142,  -142,
    -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,    43,
       2,     2,     2,   227,     2,     2,   227,   227,   244,   257,
     247,   270,  -142,    85,    93,    95,   109,  -142,  -142,   198,
     198,   -16,   137,   197,  -142,  -142,  -142,  -142,  -142,  -142,
    -142,  -142,  -142,  -142,   112,  -142,  -142,   113,   -48,   -42,
     111,    43,     2,  -142,  -142,     5,  -142,  -142,  -142,    43,
    -142,  -142,  -142,  -142,    85,    88,    89,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   227,   227,   198,    98,   104,   -35,    94,    95,  -142,
    -142,   198,   140,   139,  -142,  -142,  -142,   116,   115,   173,
    -142,   288,   155,  -142,  -142,   288,   288,   288,   288,    66,
       5,     5,   130,   130,   288,   288,    66,   130,  -142,  -142,
     172,   -37,   154,   198,  -142,  -142,   138,    95,  -142,   183,
    -142,   146,  -142,   211,   115,   198,   -21,   198,    50,   151,
      70,   115,  -142,  -142,  -142,   109,    95,  -142,   139,   137,
    -142,   148,  -142,   184,   115,  -142,  -142
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       5,     0,    12,     1,    11,     0,     3,     4,     0,     6,
       7,     9,     8,    10,     0,    31,    16,     0,    12,     0,
      14,    19,    20,     0,     0,     0,     0,     0,     0,     0,
       0,    57,    21,    14,    31,     0,    30,     0,     0,     0,
       0,     0,     0,     0,     0,    70,    71,    72,     0,    13,
       0,     0,     0,     0,     0,    59,    50,    51,    49,    48,
      53,    52,    55,    54,    60,    78,    79,    99,    98,    57,
       0,     0,     0,     0,     0,     0,     0,     0,    81,    80,
       0,    83,   101,     0,   118,    69,     0,    38,    39,     0,
      62,     0,     0,    12,    32,    33,    34,    40,    41,    35,
      36,    37,    42,    15,     0,    24,    17,     0,     0,     0,
      82,    57,     0,    81,    80,    85,    83,    86,    88,    57,
     104,   102,    87,    89,   105,    83,   102,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    57,     0,     0,     0,    64,    67,
      68,     0,     0,     0,    22,    29,    28,    16,     0,     0,
      82,     0,    82,    84,   103,   111,   110,   108,   109,    97,
      90,    91,    93,    94,   106,   107,    96,    95,    92,   112,
     113,     0,     0,     0,    56,    65,    61,    58,    66,    46,
      45,    25,    18,    75,     0,     0,     0,     0,     0,    43,
      14,     0,    73,    77,   119,     0,    63,    47,     0,     0,
      74,     0,    44,     0,     0,    27,    76
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -142,  -142,  -142,   -47,   225,   -32,    72,  -142,  -142,  -142,
    -142,  -142,  -142,  -142,  -142,  -142,  -141,   199,  -142,  -142,
    -142,    23,  -142,    34,   -63,   -82,  -142,  -142,  -142,  -142,
     -18,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,   -22,
      64,   -25,  -142,   -57,   -62,   -46
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    14,    33,    50,    21,     6,    52,     7,
      34,   155,    17,     8,    51,   191,    35,    18,    36,    37,
     199,   190,    63,    64,    91,    38,    39,    40,   147,   186,
     113,    42,   152,    43,    44,    45,   202,    46,    47,   114,
      80,   116,    82,    83,    84,    85
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      41,    92,    81,   104,   145,    79,   110,   108,   109,    78,
      49,   121,   143,    -2,   121,   126,   120,   193,   143,   124,
     149,   150,     3,   143,    16,   143,   195,   158,    81,    81,
       4,    79,    79,   159,   184,    78,    78,   151,    15,   143,
      65,    66,   205,   146,   148,   153,   111,    22,   160,    70,
      71,    72,   125,   203,   134,   135,   162,    74,    48,    75,
     210,   139,    53,   140,    81,    81,    54,    79,    79,   -26,
      55,    78,    78,   216,    86,    41,   112,    19,    87,   121,
     121,   182,    88,    20,   179,   180,    49,   125,    56,    57,
      58,    59,    60,    61,    62,    23,   103,   181,    24,    94,
      25,    26,    27,    95,     4,   187,    28,   106,   107,    29,
      30,    89,    96,   132,   133,   134,   135,    90,    81,   141,
     142,    79,   139,   211,   140,    78,    81,  -102,  -102,    79,
      97,    31,    98,    78,   115,   117,   118,   196,   122,   123,
       9,    10,    11,    12,    13,  -100,  -100,    99,   100,   204,
     101,   206,   102,   144,   105,   143,   156,   157,    81,    32,
     -23,    79,   213,   163,   164,    78,    89,   183,   209,   185,
      81,  -114,    81,    79,  -114,    79,   161,    78,   188,    78,
    -114,  -114,  -114,   189,    19,   194,  -114,    32,   140,  -100,
    -100,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,    23,   141,   151,    24,   197,
      25,    26,    27,   198,     4,  -100,    28,   200,  -100,    29,
      30,   201,   208,   214,  -100,  -100,  -100,     5,   215,   192,
    -100,   212,   207,    93,     0,     0,    65,    66,    67,    68,
       0,    31,    69,     0,     0,    70,    71,    72,     0,     0,
       0,     0,    73,    74,     0,    75,     0,     0,    76,     0,
       0,     0,     0,     0,     0,    65,    66,    67,    68,    32,
     154,   119,    77,     0,    70,    71,    72,   127,   128,   129,
     130,    73,    74,     0,    75,     0,     0,    76,     0,     0,
       0,     0,     0,   131,   132,   133,   134,   135,   136,   137,
       0,    77,   138,   139,  -115,   140,     0,  -115,     0,     0,
       0,     0,     0,  -115,  -115,  -115,     0,  -116,     0,  -115,
    -116,     0,     0,     0,     0,     0,  -116,  -116,  -116,     0,
    -117,     0,  -116,  -117,   131,   132,   133,   134,   135,  -117,
    -117,  -117,     0,   138,   139,  -117,   140
};

static const yytype_int16 yycheck[] =
{
      18,    33,    27,    50,    86,    27,    69,    53,    54,    27,
      16,    73,    60,     0,    76,    77,    73,   158,    60,    76,
      36,    37,     0,    60,    44,    60,    63,    75,    53,    54,
      17,    53,    54,    75,    69,    53,    54,    53,    72,    60,
      38,    39,    63,    89,    90,    92,    44,    73,   111,    47,
      48,    49,    77,   194,    49,    50,   119,    55,    38,    57,
     201,    56,    74,    58,    89,    90,    74,    89,    90,    75,
      44,    89,    90,   214,    74,    93,    74,    68,    70,   141,
     142,   144,    70,    74,   141,   142,    16,   112,    38,    39,
      40,    41,    42,    43,    44,     8,    69,   143,    11,    70,
      13,    14,    15,    70,    17,   151,    19,    70,    71,    22,
      23,    68,    70,    47,    48,    49,    50,    74,   143,    34,
      35,   143,    56,   205,    58,   143,   151,    34,    35,   151,
      70,    44,    70,   151,    70,    71,    72,   183,    74,    75,
       3,     4,     5,     6,     7,    34,    35,    70,    70,   195,
      70,   197,    70,    44,    75,    60,    44,    44,   183,    72,
      73,   183,   209,    75,    75,   183,    68,    63,   200,    75,
     195,    60,   197,   195,    63,   197,   112,   195,    38,   197,
      69,    70,    71,    44,    68,    12,    75,    72,    58,    34,
      35,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,     8,    34,    53,    11,    71,
      13,    14,    15,    30,    17,    60,    19,    71,    63,    22,
      23,    10,    71,    75,    69,    70,    71,     2,    44,   157,
      75,   208,   198,    34,    -1,    -1,    38,    39,    40,    41,
      -1,    44,    44,    -1,    -1,    47,    48,    49,    -1,    -1,
      -1,    -1,    54,    55,    -1,    57,    -1,    -1,    60,    -1,
      -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,    72,
      73,    44,    74,    -1,    47,    48,    49,    30,    31,    32,
      33,    54,    55,    -1,    57,    -1,    -1,    60,    -1,    -1,
      -1,    -1,    -1,    46,    47,    48,    49,    50,    51,    52,
      -1,    74,    55,    56,    60,    58,    -1,    63,    -1,    -1,
      -1,    -1,    -1,    69,    70,    71,    -1,    60,    -1,    75,
      63,    -1,    -1,    -1,    -1,    -1,    69,    70,    71,    -1,
      60,    -1,    75,    63,    46,    47,    48,    49,    50,    69,
      70,    71,    -1,    55,    56,    75,    58
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    77,    78,     0,    17,    80,    83,    85,    89,     3,
       4,     5,     6,     7,    79,    72,    44,    88,    93,    68,
      74,    82,    73,     8,    11,    13,    14,    15,    19,    22,
      23,    44,    72,    80,    86,    92,    94,    95,   101,   102,
     103,   106,   107,   109,   110,   111,   113,   114,    38,    16,
      81,    90,    84,    74,    74,    44,    38,    39,    40,    41,
      42,    43,    44,    98,    99,    38,    39,    40,    41,    44,
      47,    48,    49,    54,    55,    57,    60,    74,   106,   115,
     116,   117,   118,   119,   120,   121,    74,    70,    70,    68,
      74,   100,    81,    93,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    69,    79,    75,    70,    71,   121,   121,
     100,    44,    74,   106,   115,   116,   117,   116,   116,    44,
     119,   120,   116,   116,   119,   117,   120,    30,    31,    32,
      33,    46,    47,    48,    49,    50,    51,    52,    55,    56,
      58,    34,    35,    60,    44,   101,   121,   104,   121,    36,
      37,    53,   108,    79,    73,    87,    44,    44,    75,    75,
     100,   116,   100,    75,    75,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   119,
     119,   121,   100,    63,    69,    75,   105,   121,    38,    44,
      97,    91,    82,    92,    12,    63,   121,    71,    30,    96,
      71,    10,   112,    92,   121,    63,   121,    99,    71,    81,
      92,   101,    97,    79,    75,    44,    92
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    76,    77,    78,    78,    78,    79,    79,    79,    79,
      79,    80,    80,    81,    81,    82,    82,    83,    84,    84,
      85,    86,    87,    88,    89,    90,    90,    91,    91,    92,
      93,    93,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    95,    96,    96,    97,    97,    98,    98,
      98,    98,    98,    98,    99,    99,   100,   100,   101,   102,
     103,   104,   104,   105,   105,   106,   107,   108,   108,   109,
     110,   110,   110,   111,   112,   112,   113,   114,   115,   115,
     116,   116,   116,   116,   116,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   118,   118,
     119,   119,   119,   119,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   121,   121,   121,   121,   121,   121
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     2,     0,     1,     1,     1,     1,
       1,     1,     0,     1,     0,     3,     0,     6,     4,     0,
       4,     1,     1,     1,     6,     4,     0,     5,     0,     3,
       2,     0,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     5,     3,     0,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     2,
       2,     2,     0,     3,     0,     4,     4,     1,     1,     2,
       1,     1,     1,     6,     2,     0,     9,     6,     1,     1,
       1,     1,     2,     1,     3,     2,     2,     2,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       2,     1,     1,     3,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     1,     1,     1,     1,     5
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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
# undef YYSTACK_RELOCATE
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
  case 2:
#line 163 "parser.y"
        { 
		(yyvsp[0].nodo)->codigo = cod_init(num_vars_globais((yyvsp[0].nodo)), label_main, (yyvsp[0].nodo)->codigo);
		imprime_codigo((yyvsp[0].nodo)->codigo);
	    arvore = (yyvsp[0].nodo); 
	    sai_escopo(escopo); 
	}
#line 1591 "parser.tab.c"
    break;

  case 3:
#line 171 "parser.y"
        { (yyval.nodo) = insere_fim_lista((yyvsp[0].nodo), (yyvsp[-1].nodo));
	  if((yyvsp[-1].nodo) != NULL)
	  	(yyval.nodo)->codigo = concatena_codigo((yyvsp[-1].nodo)->codigo, (yyvsp[0].nodo)->codigo);
	  else 
	  	(yyval.nodo)->codigo = (yyvsp[0].nodo)->codigo; 
	}
#line 1602 "parser.tab.c"
    break;

  case 4:
#line 178 "parser.y"
        { (yyval.nodo) = insere_fim_lista((yyvsp[0].nodo), (yyvsp[-1].nodo));
	  if((yyvsp[-1].nodo) != NULL)
	  	(yyval.nodo)->codigo = concatena_codigo((yyvsp[-1].nodo)->codigo, (yyvsp[0].nodo)->codigo);
	  else 
	  	(yyval.nodo)->codigo = (yyvsp[0].nodo)->codigo; 
	}
#line 1613 "parser.tab.c"
    break;

  case 5:
#line 185 "parser.y"
        { (yyval.nodo) = NULL;}
#line 1619 "parser.tab.c"
    break;

  case 6:
#line 187 "parser.y"
                   {(yyval.tipo) = (yyvsp[0].tipo);}
#line 1625 "parser.tab.c"
    break;

  case 7:
#line 188 "parser.y"
                       {(yyval.tipo) = (yyvsp[0].tipo);}
#line 1631 "parser.tab.c"
    break;

  case 8:
#line 189 "parser.y"
                       {(yyval.tipo) = (yyvsp[0].tipo);}
#line 1637 "parser.tab.c"
    break;

  case 9:
#line 190 "parser.y"
                       {(yyval.tipo) = (yyvsp[0].tipo);}
#line 1643 "parser.tab.c"
    break;

  case 10:
#line 191 "parser.y"
                       {(yyval.tipo) = (yyvsp[0].tipo);}
#line 1649 "parser.tab.c"
    break;

  case 15:
#line 197 "parser.y"
                          {(yyval.nodo) = cria_nodo(literal, (yyvsp[-1].valor_lexico));}
#line 1655 "parser.tab.c"
    break;

  case 16:
#line 198 "parser.y"
       {(yyval.nodo) = NULL;}
#line 1661 "parser.tab.c"
    break;

  case 17:
#line 201 "parser.y"
        {
	 simbolo_t *s = novo_simbolo();
	 adiciona_valor_lexico(s, (yyvsp[-3].valor_lexico));
	 libera_tk((yyvsp[-3].valor_lexico));
	 s->tipo = (yyvsp[-4].tipo);
	 if((yyvsp[-2].nodo) == NULL)
		s->natureza = simbolo_variavel;
	 else {
		s->natureza = simbolo_vetor;
		s->tamanho = (yyvsp[-2].nodo)->valor_lexico->valor.inteiro;
		libera((yyvsp[-2].nodo));
	 }
	//  int aux_proximo_id_antes = retorna_proximo_id_do_escopo_da_funcao(escopo);
	 escopo = adiciona_simbolo(escopo, s); 
	 escopo = adiciona_lista_simbolos(escopo, (yyvsp[-1].nodo), (yyvsp[-4].tipo)); // adiciona as variaveis em lista_identificadores_g
	//  int aux_proximo_id_depois = retorna_proximo_id_do_escopo_da_funcao(escopo);
	//  int numero_de_declaracoes = (aux_proximo_id_depois - aux_proximo_id_antes)/4;
	 
	//  libera($5); // libera arvore temporaria

	 (yyval.nodo) = cria_nodo_passagem();
	 (yyval.nodo)->filhos[0] = (yyvsp[-1].nodo);
	 
	//  $$->codigo = cod_alocacao_var_global(numero_de_declaracoes);
     //Cria ILOC para variaveis globais
	 ///Esse nodo serve somente para passar para a raiz da arvore o código gerado;
	 //$$ = cria_nodo(nodo_inutil, NULL);
	 //Faz mesma coisa que foi feita nas variaveis locais sem inicializacao, mas desloca em rbss

	}
#line 1696 "parser.tab.c"
    break;

  case 18:
#line 232 "parser.y"
        {// cria uma arvore temporaria que guarda as variaveis 
	 ast_t *n = cria_nodo_vetor((yyvsp[-1].valor_lexico), (yyvsp[0].nodo));
	 (yyval.nodo) = insere_fim_lista(n, (yyvsp[-3].nodo)); }
#line 1704 "parser.tab.c"
    break;

  case 19:
#line 235 "parser.y"
          {(yyval.nodo) = NULL;}
#line 1710 "parser.tab.c"
    break;

  case 20:
#line 238 "parser.y"
        {
		insere_filho((yyvsp[-3].nodo), (yyvsp[-1].nodo));
		(yyval.nodo) = (yyvsp[-3].nodo);
		bool func_main = eh_main((yyval.nodo));
		if(func_main)
			(yyval.nodo)->codigo = cod_funcao_prologo_main(numero_parametros(escopo->t));
		else 
			(yyval.nodo)->codigo = cod_funcao_prologo(numero_parametros(escopo->t)); // adiciona o prologo antes de fechar o escopo local
		escopo = sai_escopo(escopo); // fechando o escopo local na hora da redução
		simbolo_t *s = novo_simbolo();
		adiciona_valor_lexico(s, (yyvsp[-3].nodo)->valor_lexico);
		s->natureza = simbolo_funcao;
		s->tipo = (yyvsp[-3].nodo)->tipo_sem;
		s->label = novo_label();
		if(func_main)
			label_main = s->label;
		escopo = adiciona_simbolo(escopo, s); // adicionando a funcao ao escopo global
		operando_instr_t *ret;
		if((yyvsp[-1].nodo) != NULL)
		{
			(yyval.nodo)->codigo = concatena_codigo((yyval.nodo)->codigo, (yyvsp[-1].nodo)->codigo);
		    ret = retorno((yyvsp[-1].nodo));
		}
		else 
			ret = NULL;
		if(func_main)
			(yyval.nodo)->codigo = concatena_codigo((yyval.nodo)->codigo, cod_halt());
		else
			(yyval.nodo)->codigo = concatena_codigo((yyval.nodo)->codigo, cod_funcao_epilogo(ret));
		adiciona_label(s->label, (yyval.nodo)->codigo);
	}
#line 1746 "parser.tab.c"
    break;

  case 21:
#line 270 "parser.y"
                      { 
						escopo = novo_escopo(escopo, escopo_interno, retorna_proximo_id_do_escopo_da_funcao(escopo));
					  }
#line 1754 "parser.tab.c"
    break;

  case 22:
#line 273 "parser.y"
                   { escopo = sai_escopo(escopo); }
#line 1760 "parser.tab.c"
    break;

  case 23:
#line 277 "parser.y"
                       {(yyval.nodo) = (yyvsp[0].nodo);}
#line 1766 "parser.tab.c"
    break;

  case 24:
#line 281 "parser.y"
        {ast_t *n = cria_nodo(funcao, (yyvsp[-3].valor_lexico));
	 n->tipo_sem = (yyvsp[-4].tipo);
	 (yyval.nodo) = n; }
#line 1774 "parser.tab.c"
    break;

  case 25:
#line 285 "parser.y"
        {simbolo_t *s = novo_simbolo();
	 adiciona_valor_lexico(s, (yyvsp[-1].valor_lexico));
	 libera_tk((yyvsp[-1].valor_lexico));
	 s->natureza = simbolo_parametro;
	 s->tipo = (yyvsp[-2].tipo);
	 escopo = adiciona_simbolo(escopo, s);  }
#line 1785 "parser.tab.c"
    break;

  case 26:
#line 292 "parser.y"
        {// primeira redução que vai ocorrer, inicio do escopo local da funcao s/ parametros
	 escopo = novo_escopo(escopo, escopo_funcao, REGISTRO_ATIVACAO_OFFSET+4);}
#line 1792 "parser.tab.c"
    break;

  case 27:
#line 295 "parser.y"
        {simbolo_t *s = novo_simbolo();
	 adiciona_valor_lexico(s, (yyvsp[0].valor_lexico));
	 libera_tk((yyvsp[0].valor_lexico));
	 s->natureza = simbolo_parametro;
	 s->tipo = (yyvsp[-1].tipo);
	 escopo = adiciona_simbolo(escopo, s); }
#line 1803 "parser.tab.c"
    break;

  case 28:
#line 302 "parser.y"
        {//primeira redução que vai ocorrer, inicio do escopo local da funcao c/ paramentros
	 escopo = novo_escopo(escopo, escopo_funcao, REGISTRO_ATIVACAO_OFFSET+4);}
#line 1810 "parser.tab.c"
    break;

  case 29:
#line 305 "parser.y"
                                                         {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 1816 "parser.tab.c"
    break;

  case 30:
#line 308 "parser.y"
                {
			(yyval.nodo) = insere_fim_lista((yyvsp[0].nodo), (yyvsp[-1].nodo));
			if((yyvsp[-1].nodo) != NULL && (yyvsp[0].nodo) != NULL)
				(yyval.nodo)->codigo = concatena_codigo((yyvsp[-1].nodo)->codigo, (yyvsp[0].nodo)->codigo);
			else
			{
				if((yyvsp[-1].nodo) != NULL)
					(yyval.nodo)->codigo = (yyvsp[-1].nodo)->codigo;
				if((yyvsp[0].nodo) != NULL)
					(yyval.nodo)->codigo = (yyvsp[0].nodo)->codigo;
			}
		}
#line 1833 "parser.tab.c"
    break;

  case 31:
#line 320 "parser.y"
            {(yyval.nodo) = NULL; }
#line 1839 "parser.tab.c"
    break;

  case 32:
#line 322 "parser.y"
                                                {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 1845 "parser.tab.c"
    break;

  case 33:
#line 323 "parser.y"
                                        {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 1851 "parser.tab.c"
    break;

  case 34:
#line 324 "parser.y"
                                                {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 1857 "parser.tab.c"
    break;

  case 35:
#line 325 "parser.y"
                                        {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 1863 "parser.tab.c"
    break;

  case 36:
#line 326 "parser.y"
                                                {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 1869 "parser.tab.c"
    break;

  case 37:
#line 327 "parser.y"
                                                {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 1875 "parser.tab.c"
    break;

  case 38:
#line 328 "parser.y"
                                                {(yyval.nodo) = cria_nodo(cmd_break, NULL);}
#line 1881 "parser.tab.c"
    break;

  case 39:
#line 329 "parser.y"
                                        {(yyval.nodo) = cria_nodo(cmd_continue, NULL);}
#line 1887 "parser.tab.c"
    break;

  case 40:
#line 330 "parser.y"
                                                {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 1893 "parser.tab.c"
    break;

  case 41:
#line 331 "parser.y"
                                                {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 1899 "parser.tab.c"
    break;

  case 42:
#line 332 "parser.y"
                                        {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 1905 "parser.tab.c"
    break;

  case 43:
#line 337 "parser.y"
        { (yyval.nodo) = insere_inicio_lista((yyvsp[-1].nodo), (yyvsp[0].nodo));
	  int aux_proximo_id_antes = retorna_proximo_id_do_escopo_da_funcao(escopo);
	  escopo = adiciona_lista_simbolos(escopo, (yyval.nodo), (yyvsp[-2].tipo));
	  int aux_proximo_id_depois = retorna_proximo_id_do_escopo_da_funcao(escopo);
	  int numero_de_declaracoes = (aux_proximo_id_depois - aux_proximo_id_antes)/4;
	  (yyval.nodo) = remove_nodos_inuteis((yyval.nodo));
	  if((yyval.nodo) == NULL)
	  	(yyval.nodo) = cria_nodo_passagem();
	  (yyval.nodo)->codigo = cod_alocacao_var_local(numero_de_declaracoes); }
#line 1919 "parser.tab.c"
    break;

  case 44:
#line 347 "parser.y"
                {(yyval.nodo) = insere_fim_lista((yyvsp[0].nodo), (yyvsp[-2].nodo)); }
#line 1925 "parser.tab.c"
    break;

  case 45:
#line 348 "parser.y"
            {(yyval.nodo) = NULL;}
#line 1931 "parser.tab.c"
    break;

  case 46:
#line 351 "parser.y"
                {
			(yyval.nodo) = cria_nodo(identificador, (yyvsp[0].valor_lexico));
		}
#line 1939 "parser.tab.c"
    break;

  case 47:
#line 355 "parser.y"
                {
			ast_t *n = cria_nodo(declaracao, NULL);
			insere_filho(n, cria_nodo(identificador, (yyvsp[-2].valor_lexico)));
			insere_filho(n, (yyvsp[0].nodo));
			libera_tk((yyvsp[-1].valor_lexico));
			(yyval.nodo) = n;
		}
#line 1951 "parser.tab.c"
    break;

  case 48:
#line 363 "parser.y"
                       {(yyval.nodo) = cria_nodo(literal, (yyvsp[0].valor_lexico)); (yyval.nodo)->tipo_sem = bool_sem;}
#line 1957 "parser.tab.c"
    break;

  case 49:
#line 364 "parser.y"
                           {(yyval.nodo) = cria_nodo(literal, (yyvsp[0].valor_lexico)); (yyval.nodo)->tipo_sem = bool_sem;}
#line 1963 "parser.tab.c"
    break;

  case 50:
#line 365 "parser.y"
                           {(yyval.nodo) = cria_nodo(literal, (yyvsp[0].valor_lexico)); (yyval.nodo)->tipo_sem = int_sem;}
#line 1969 "parser.tab.c"
    break;

  case 51:
#line 366 "parser.y"
                           {(yyval.nodo) = cria_nodo(literal, (yyvsp[0].valor_lexico)); (yyval.nodo)->tipo_sem = float_sem;}
#line 1975 "parser.tab.c"
    break;

  case 52:
#line 367 "parser.y"
                           {(yyval.nodo) = cria_nodo(literal, (yyvsp[0].valor_lexico)); (yyval.nodo)->tipo_sem = string_sem;}
#line 1981 "parser.tab.c"
    break;

  case 53:
#line 368 "parser.y"
                           {(yyval.nodo) = cria_nodo(literal, (yyvsp[0].valor_lexico)); (yyval.nodo)->tipo_sem = char_sem;}
#line 1987 "parser.tab.c"
    break;

  case 54:
#line 371 "parser.y"
                {(yyval.nodo) = (yyvsp[0].nodo);}
#line 1993 "parser.tab.c"
    break;

  case 55:
#line 372 "parser.y"
                          {
		simbolo_t *s = referencia(escopo, (yyvsp[0].valor_lexico), simbolo_variavel);
		(yyval.nodo) = cria_nodo(identificador, (yyvsp[0].valor_lexico));
		(yyval.nodo)->tipo_sem = s->tipo;
	}
#line 2003 "parser.tab.c"
    break;

  case 56:
#line 378 "parser.y"
                                {verifica_tipos((yyvsp[-1].nodo)->tipo_sem, int_sem, (yyvsp[-1].nodo)->valor_lexico->linha); (yyval.nodo) = (yyvsp[-1].nodo);}
#line 2009 "parser.tab.c"
    break;

  case 57:
#line 379 "parser.y"
                      {(yyval.nodo) = NULL;}
#line 2015 "parser.tab.c"
    break;

  case 58:
#line 382 "parser.y"
        {
		simbolo_t *s;
		if((yyvsp[-2].nodo) == NULL)
			s = referencia(escopo, (yyvsp[-3].valor_lexico), simbolo_variavel);
		else 
			s = referencia(escopo, (yyvsp[-3].valor_lexico), simbolo_vetor);
		verifica_tipos((yyvsp[0].nodo)->tipo_sem, s->tipo, (yyvsp[0].nodo)->valor_lexico->linha);
		ast_t *n = cria_nodo(atribuicao, NULL);
		insere_filho(n, cria_nodo_vetor((yyvsp[-3].valor_lexico), (yyvsp[-2].nodo)));
		insere_filho(n, (yyvsp[0].nodo));
		libera_tk((yyvsp[-1].valor_lexico));
		if(eh_booleana((yyvsp[0].nodo))) // atriuicao bool
		{
			n->codigo = cod_atribuicao_logica_var(s->id, (yyvsp[0].nodo)->codigo, s->global);
		}
		else // atribuicao int
		{
			n->codigo = concatena_codigo((yyvsp[0].nodo)->codigo, cod_store_variavel((yyvsp[0].nodo)->temp, s->id, s->global));
		}
		(yyval.nodo) = n;
	}
#line 2041 "parser.tab.c"
    break;

  case 59:
#line 405 "parser.y"
        {
		simbolo_t *s = referencia(escopo, (yyvsp[0].valor_lexico), simbolo_variavel);
		ast_t *n = cria_nodo(entrada, NULL);
		insere_filho(n, cria_nodo(identificador, (yyvsp[0].valor_lexico)));
		n->tipo_sem = s->tipo;
		(yyval.nodo) = n;
	}
#line 2053 "parser.tab.c"
    break;

  case 60:
#line 413 "parser.y"
        {
		ast_t *n = cria_nodo(saida, NULL);
		insere_filho(n, (yyvsp[0].nodo));
		(yyval.nodo) = n;
	}
#line 2063 "parser.tab.c"
    break;

  case 61:
#line 420 "parser.y"
          {(yyval.nodo) = insere_inicio_lista((yyvsp[-1].nodo), (yyvsp[0].nodo));}
#line 2069 "parser.tab.c"
    break;

  case 62:
#line 421 "parser.y"
      {(yyval.nodo) = NULL;}
#line 2075 "parser.tab.c"
    break;

  case 63:
#line 423 "parser.y"
          {(yyval.nodo) = insere_fim_lista((yyvsp[0].nodo), (yyvsp[-2].nodo));}
#line 2081 "parser.tab.c"
    break;

  case 64:
#line 424 "parser.y"
          {(yyval.nodo) = NULL;}
#line 2087 "parser.tab.c"
    break;

  case 65:
#line 426 "parser.y"
        {
		simbolo_t *s = referencia(escopo, (yyvsp[-3].valor_lexico), simbolo_funcao);
		ast_t *n = cria_nodo(chamada_funcao, (yyvsp[-3].valor_lexico));
		n->tipo_sem = s->tipo;
		/* rsp + 0: endereco de retorno 
		 *     + 4: rsp 
		 *     + 8: rfp 
		 *     + 12: valor de retorno 
		 *     + ... 12 + num_params * 4: parametros 
		 *     + ...: vars locais                     */
		code_t *cod_params = NULL;
		ast_t  *ps = (yyvsp[-1].nodo);
		int param_offset = REGISTRO_ATIVACAO_OFFSET; // primeiro parametro salvo em rsp + 16
		while(ps != NULL)
		{
			param_offset += 4;
			if(ps->codigo != NULL)
			{
				if(eh_booleana(ps))
				{
					ps->temp = novo_registrador();
					cod_params = concatena_codigo(cod_params, 
					                              cod_atribuicao_logica_reg(ps->temp, ps->codigo));
				}
				else
					cod_params = concatena_codigo(cod_params, ps->codigo);
				cod_params = concatena_codigo(cod_params, cod_load_parametro(ps->temp, param_offset));
			}
			if(ps->num_filhos > 0)
				ps = ps->filhos[ps->num_filhos-1];
			else 
				ps = NULL;
		}
		n->temp = novo_registrador();
		n->codigo = concatena_codigo(cod_params, 
									 cod_chamada_func_antes( 5,
		                                                     param_offset/4-REGISTRO_ATIVACAO_OFFSET/4));
		// n->codigo = cod_chamada_func_antes(num_linhas(cod_params) + 5,
		//                                    param_offset/4-REGISTRO_ATIVACAO_OFFSET/4);
	    // n->codigo = concatena_codigo(n->codigo, cod_params);
	    n->codigo = concatena_codigo(n->codigo, cod_jump_incondicional(s->label));
		n->codigo = concatena_codigo(n->codigo, cod_load_pilha(n->temp, 12));
		(yyval.nodo) = n;
	}
#line 2136 "parser.tab.c"
    break;

  case 66:
#line 472 "parser.y"
        {
		simbolo_t *s;
		if((yyvsp[-2].nodo) == NULL)
			s = referencia(escopo, (yyvsp[-3].valor_lexico), simbolo_variavel);
		else 
			s = referencia(escopo, (yyvsp[-3].valor_lexico), simbolo_vetor);
		ast_t *n = cria_nodo(cmd_shift, (yyvsp[-1].valor_lexico));
		insere_filho(n, cria_nodo_vetor((yyvsp[-3].valor_lexico), (yyvsp[-2].nodo)));
		insere_filho(n, cria_nodo(literal, (yyvsp[0].valor_lexico)));
		n->tipo_sem = s->tipo;
		(yyval.nodo) = n;
	}
#line 2153 "parser.tab.c"
    break;

  case 67:
#line 484 "parser.y"
                      {(yyval.valor_lexico) = (yyvsp[0].valor_lexico);}
#line 2159 "parser.tab.c"
    break;

  case 68:
#line 485 "parser.y"
                      {(yyval.valor_lexico) = (yyvsp[0].valor_lexico);}
#line 2165 "parser.tab.c"
    break;

  case 69:
#line 488 "parser.y"
        {
		ast_t *n = cria_nodo(cmd_return, NULL);
		insere_filho(n, (yyvsp[0].nodo));
		n->tipo_sem = (yyvsp[0].nodo)->tipo_sem;
		if(eh_booleana((yyvsp[0].nodo))){
			// faz a atribuicao 
			n->temp = novo_registrador();
			n->codigo = cod_atribuicao_logica_reg(n->temp, (yyvsp[0].nodo)->codigo);
		}
		else{
			n->temp = (yyvsp[0].nodo)->temp;
			n->codigo = (yyvsp[0].nodo)->codigo;
		} 
		(yyval.nodo) = n;
	}
#line 2185 "parser.tab.c"
    break;

  case 70:
#line 504 "parser.y"
                         {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2191 "parser.tab.c"
    break;

  case 71:
#line 505 "parser.y"
                         {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2197 "parser.tab.c"
    break;

  case 72:
#line 506 "parser.y"
                                     {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2203 "parser.tab.c"
    break;

  case 73:
#line 509 "parser.y"
        {
		verifica_tipos((yyvsp[-3].nodo)->tipo_sem, bool_sem, (yyvsp[-3].nodo)->valor_lexico->linha);
		ast_t *n = cria_nodo(cmd_if, NULL);
		insere_filho(n, (yyvsp[-3].nodo));
		insere_filho(n, (yyvsp[-1].nodo));
		code_t *cod_if, *cod_else, *cod_fim;
		if((yyvsp[0].nodo) != NULL)
		{
			insere_filho(n, (yyvsp[0].nodo));
			cod_else = (yyvsp[0].nodo)->codigo;
		}
		else
		{
			// instrução vazia que recebe o label 
			cod_else = cod_nop();
		}
		operando_instr_t *lt = novo_label(),
						 *lf = novo_label(),
						 *fim = novo_label();
		adiciona_label(lt, (yyvsp[-1].nodo)->codigo);
		adiciona_label(lf, cod_else);
		remenda_true(lt, (yyvsp[-3].nodo)->codigo);
		remenda_false(lf, (yyvsp[-3].nodo)->codigo);
		cod_else = concatena_codigo(cod_else, cod_jump_incondicional(fim));
		cod_if   = concatena_codigo((yyvsp[-1].nodo)->codigo, cod_jump_incondicional(fim));
		cod_fim = cod_nop();
		adiciona_label(fim, cod_fim);
		n->codigo = concatena_codigo((yyvsp[-3].nodo)->codigo, cod_if);
		n->codigo = concatena_codigo(n->codigo, cod_else);
		n->codigo = concatena_codigo(n->codigo, cod_fim);
		(yyval.nodo) = n;
	}
#line 2240 "parser.tab.c"
    break;

  case 74:
#line 541 "parser.y"
                              {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2246 "parser.tab.c"
    break;

  case 75:
#line 542 "parser.y"
         {(yyval.nodo) = NULL;}
#line 2252 "parser.tab.c"
    break;

  case 76:
#line 545 "parser.y"
        {
		verifica_tipos((yyvsp[-4].nodo)->tipo_sem, bool_sem, (yyvsp[-4].nodo)->valor_lexico->linha);
		ast_t *n = cria_nodo(cmd_for, NULL);
		insere_filho(n, (yyvsp[-6].nodo));
		insere_filho(n, (yyvsp[-4].nodo));
		insere_filho(n, (yyvsp[-2].nodo));
		insere_filho(n, (yyvsp[0].nodo));
		operando_instr_t *condicao = novo_label(),
		                 *inicio = novo_label(),
		                 *fim = novo_label();
		code_t *cod_bloco = concatena_codigo((yyvsp[0].nodo)->codigo, (yyvsp[-2].nodo)->codigo);
		cod_bloco = concatena_codigo(cod_bloco, cod_jump_incondicional(condicao));
		adiciona_label(inicio, cod_bloco);

		adiciona_label(condicao, (yyvsp[-4].nodo)->codigo);
		remenda_true(inicio, (yyvsp[-4].nodo)->codigo);
		remenda_false(fim, (yyvsp[-4].nodo)->codigo);
		adiciona_label(inicio, (yyvsp[0].nodo)->codigo);

		code_t *cod_fim = cod_nop();
		adiciona_label(fim, cod_fim);

		n->codigo = concatena_codigo((yyvsp[-6].nodo)->codigo, (yyvsp[-4].nodo)->codigo);
		n->codigo = concatena_codigo(n->codigo, cod_bloco);
		n->codigo = concatena_codigo(n->codigo, cod_fim);
		(yyval.nodo) = n;
	}
#line 2284 "parser.tab.c"
    break;

  case 77:
#line 574 "parser.y"
        {
		verifica_tipos((yyvsp[-3].nodo)->tipo_sem, bool_sem, (yyvsp[-3].nodo)->valor_lexico->linha);
		ast_t *n = cria_nodo(cmd_while, NULL);
		insere_filho(n, (yyvsp[-3].nodo));
		insere_filho(n, (yyvsp[0].nodo));
		operando_instr_t *condicao = novo_label(),
		                 *inicio = novo_label(),
		                 *fim = novo_label();
		code_t *cod_bloco = concatena_codigo((yyvsp[0].nodo)->codigo, cod_jump_incondicional(condicao)),
		       *cod_fim = cod_nop();
		adiciona_label(condicao, (yyvsp[-3].nodo)->codigo);
		adiciona_label(inicio, cod_bloco);
		adiciona_label(fim, cod_fim);
		remenda_true(inicio, (yyvsp[-3].nodo)->codigo);
		remenda_false(fim, (yyvsp[-3].nodo)->codigo);
		n->codigo = concatena_codigo((yyvsp[-3].nodo)->codigo, cod_bloco);
		n->codigo = concatena_codigo(n->codigo, cod_fim);
		(yyval.nodo) = n;
	}
#line 2308 "parser.tab.c"
    break;

  case 78:
#line 596 "parser.y"
        { (yyval.nodo) = cria_nodo(literal, (yyvsp[0].valor_lexico)); 
	  (yyval.nodo)->tipo_sem = int_sem;
	  (yyval.nodo)->temp = novo_registrador();
	  (yyval.nodo)->codigo = cod_load_literal((yyval.nodo)->temp, (yyvsp[0].valor_lexico)->valor.inteiro);
	   }
#line 2318 "parser.tab.c"
    break;

  case 79:
#line 602 "parser.y"
        { (yyval.nodo) = cria_nodo(literal, (yyvsp[0].valor_lexico));
	  (yyval.nodo)->tipo_sem = float_sem;}
#line 2325 "parser.tab.c"
    break;

  case 80:
#line 606 "parser.y"
                                        {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2331 "parser.tab.c"
    break;

  case 81:
#line 607 "parser.y"
                                        {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2337 "parser.tab.c"
    break;

  case 82:
#line 608 "parser.y"
                                        { 
		simbolo_t *s;
		if((yyvsp[0].nodo) == NULL)
			s = referencia(escopo, (yyvsp[-1].valor_lexico), simbolo_variavel);
		else 
			s = referencia(escopo, (yyvsp[-1].valor_lexico), simbolo_vetor);
		(yyval.nodo) = cria_nodo_vetor((yyvsp[-1].valor_lexico), (yyvsp[0].nodo));
		(yyval.nodo)->tipo_sem = s->tipo; 
		// assumindo que nao vao haver vetores na etapa 5
	  	(yyval.nodo)->temp = novo_registrador();
		(yyval.nodo)->codigo = cod_load_variavel((yyval.nodo)->temp, s->id, s->global);
		  }
#line 2354 "parser.tab.c"
    break;

  case 83:
#line 620 "parser.y"
                                        {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2360 "parser.tab.c"
    break;

  case 84:
#line 621 "parser.y"
                                        {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 2366 "parser.tab.c"
    break;

  case 85:
#line 626 "parser.y"
        { verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
	  (yyval.nodo) = cria_nodo_unario(((yyvsp[-1].valor_lexico)), (yyvsp[0].nodo));
	  (yyval.nodo)->tipo_sem = (yyvsp[0].nodo)->tipo_sem; 
	  (yyval.nodo)->temp = (yyvsp[0].nodo)->temp;
	  (yyval.nodo)->codigo = (yyvsp[0].nodo)->codigo;}
#line 2376 "parser.tab.c"
    break;

  case 86:
#line 632 "parser.y"
        { verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
	  (yyval.nodo) = cria_nodo_unario(((yyvsp[-1].valor_lexico)), (yyvsp[0].nodo));
	  (yyval.nodo)->tipo_sem = (yyvsp[0].nodo)->tipo_sem; }
#line 2384 "parser.tab.c"
    break;

  case 87:
#line 636 "parser.y"
        { verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
	  (yyval.nodo) = cria_nodo_unario(((yyvsp[-1].valor_lexico)), (yyvsp[0].nodo));
	  (yyval.nodo)->tipo_sem = (yyvsp[0].nodo)->tipo_sem; }
#line 2392 "parser.tab.c"
    break;

  case 88:
#line 640 "parser.y"
        { verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
	  (yyval.nodo) = cria_nodo_unario(((yyvsp[-1].valor_lexico)), (yyvsp[0].nodo));
	  (yyval.nodo)->tipo_sem = (yyvsp[0].nodo)->tipo_sem; }
#line 2400 "parser.tab.c"
    break;

  case 89:
#line 644 "parser.y"
        { verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
	  (yyval.nodo) = cria_nodo_unario(((yyvsp[-1].valor_lexico)), (yyvsp[0].nodo));
	  (yyval.nodo)->tipo_sem = (yyvsp[0].nodo)->tipo_sem; }
#line 2408 "parser.tab.c"
    break;

  case 90:
#line 649 "parser.y"
        { verifica_tipos((yyvsp[-2].nodo)->tipo_sem, numerico_sem, (yyvsp[-2].nodo)->valor_lexico->linha);
	  verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
	  (yyval.nodo) = cria_nodo_binario(((yyvsp[-1].valor_lexico)), (yyvsp[-2].nodo), (yyvsp[0].nodo));
	  (yyval.nodo)->tipo_sem = infere_tipo((yyvsp[-2].nodo), (yyvsp[0].nodo));
	  (yyval.nodo)->temp = novo_registrador();
	  (yyval.nodo)->codigo = concatena_codigo((yyvsp[-2].nodo)->codigo, (yyvsp[0].nodo)->codigo);
	  (yyval.nodo)->codigo = concatena_codigo((yyval.nodo)->codigo, cod_op_bin_aritmetica((yyvsp[-2].nodo)->temp, (yyvsp[0].nodo)->temp, (yyval.nodo)->temp, '+'));  
	  }
#line 2421 "parser.tab.c"
    break;

  case 91:
#line 658 "parser.y"
        { verifica_tipos((yyvsp[-2].nodo)->tipo_sem, numerico_sem, (yyvsp[-2].nodo)->valor_lexico->linha);
	  verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
	  (yyval.nodo) = cria_nodo_binario(((yyvsp[-1].valor_lexico)), (yyvsp[-2].nodo), (yyvsp[0].nodo));
	  (yyval.nodo)->tipo_sem = infere_tipo((yyvsp[-2].nodo), (yyvsp[0].nodo)); 
	  (yyval.nodo)->temp = novo_registrador();
	  (yyval.nodo)->codigo = concatena_codigo((yyvsp[-2].nodo)->codigo, (yyvsp[0].nodo)->codigo);
	  (yyval.nodo)->codigo = concatena_codigo((yyval.nodo)->codigo, cod_op_bin_aritmetica((yyvsp[-2].nodo)->temp, (yyvsp[0].nodo)->temp, (yyval.nodo)->temp, '-'));  
	  }
#line 2434 "parser.tab.c"
    break;

  case 92:
#line 667 "parser.y"
        { verifica_tipos((yyvsp[-2].nodo)->tipo_sem, numerico_sem, (yyvsp[-2].nodo)->valor_lexico->linha);
	  verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
	  (yyval.nodo) = cria_nodo_binario(((yyvsp[-1].valor_lexico)), (yyvsp[-2].nodo), (yyvsp[0].nodo));
	  (yyval.nodo)->tipo_sem = infere_tipo((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2443 "parser.tab.c"
    break;

  case 93:
#line 672 "parser.y"
        { verifica_tipos((yyvsp[-2].nodo)->tipo_sem, numerico_sem, (yyvsp[-2].nodo)->valor_lexico->linha);
	  verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
	  (yyval.nodo) = cria_nodo_binario(((yyvsp[-1].valor_lexico)), (yyvsp[-2].nodo), (yyvsp[0].nodo));
	  (yyval.nodo)->tipo_sem = infere_tipo((yyvsp[-2].nodo), (yyvsp[0].nodo)); 
	  (yyval.nodo)->temp = novo_registrador();
	  (yyval.nodo)->codigo = concatena_codigo((yyvsp[-2].nodo)->codigo, (yyvsp[0].nodo)->codigo);
	  (yyval.nodo)->codigo = concatena_codigo((yyval.nodo)->codigo, cod_op_bin_aritmetica((yyvsp[-2].nodo)->temp, (yyvsp[0].nodo)->temp, (yyval.nodo)->temp, '*'));  
	  }
#line 2456 "parser.tab.c"
    break;

  case 94:
#line 682 "parser.y"
        { verifica_tipos((yyvsp[-2].nodo)->tipo_sem, numerico_sem, (yyvsp[-2].nodo)->valor_lexico->linha);
	  verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
	  (yyval.nodo) = cria_nodo_binario(((yyvsp[-1].valor_lexico)), (yyvsp[-2].nodo), (yyvsp[0].nodo));
	  (yyval.nodo)->tipo_sem = infere_tipo((yyvsp[-2].nodo), (yyvsp[0].nodo)); 
	  (yyval.nodo)->temp = novo_registrador();
	  (yyval.nodo)->codigo = concatena_codigo((yyvsp[-2].nodo)->codigo, (yyvsp[0].nodo)->codigo);
	  (yyval.nodo)->codigo = concatena_codigo((yyval.nodo)->codigo, cod_op_bin_aritmetica((yyvsp[-2].nodo)->temp, (yyvsp[0].nodo)->temp, (yyval.nodo)->temp, '/')); 
	  }
#line 2469 "parser.tab.c"
    break;

  case 95:
#line 692 "parser.y"
        { verifica_tipos((yyvsp[-2].nodo)->tipo_sem, numerico_sem, (yyvsp[-2].nodo)->valor_lexico->linha);
	  verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
	  (yyval.nodo) = cria_nodo_binario(((yyvsp[-1].valor_lexico)), (yyvsp[-2].nodo), (yyvsp[0].nodo));
	  (yyval.nodo)->tipo_sem = infere_tipo((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2478 "parser.tab.c"
    break;

  case 96:
#line 698 "parser.y"
        { verifica_tipos((yyvsp[-2].nodo)->tipo_sem, numerico_sem, (yyvsp[-2].nodo)->valor_lexico->linha);
	  verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
	  (yyval.nodo) = cria_nodo_binario(((yyvsp[-1].valor_lexico)), (yyvsp[-2].nodo), (yyvsp[0].nodo));
	  (yyval.nodo)->tipo_sem = infere_tipo((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2487 "parser.tab.c"
    break;

  case 97:
#line 704 "parser.y"
        { verifica_tipos((yyvsp[-2].nodo)->tipo_sem, numerico_sem, (yyvsp[-2].nodo)->valor_lexico->linha);
	  verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
	  (yyval.nodo) = cria_nodo_binario(((yyvsp[-1].valor_lexico)), (yyvsp[-2].nodo), (yyvsp[0].nodo));
	  (yyval.nodo)->tipo_sem = infere_tipo((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2496 "parser.tab.c"
    break;

  case 98:
#line 710 "parser.y"
        { (yyval.nodo) = cria_nodo(literal, ((yyvsp[0].valor_lexico)));
	  (yyval.nodo)->tipo_sem = bool_sem;
	  (yyval.nodo)->codigo = cod_op_bin_lit('t');
	    }
#line 2505 "parser.tab.c"
    break;

  case 99:
#line 715 "parser.y"
        { (yyval.nodo) = cria_nodo(literal, ((yyvsp[0].valor_lexico))); 
	  (yyval.nodo)->tipo_sem = bool_sem;
	  (yyval.nodo)->codigo = cod_op_bin_lit('f');
	    }
#line 2514 "parser.tab.c"
    break;

  case 100:
#line 721 "parser.y"
                                        { 
		simbolo_t *s;
		if((yyvsp[0].nodo) == NULL)
			s = referencia(escopo, (yyvsp[-1].valor_lexico), simbolo_variavel); 
		else
			s = referencia(escopo, (yyvsp[-1].valor_lexico), simbolo_vetor);
		(yyval.nodo) = cria_nodo_vetor((yyvsp[-1].valor_lexico), (yyvsp[0].nodo));
		(yyval.nodo)->tipo_sem = s->tipo; 
		// assumindo que nao vao haver vetores na etapa 5
		(yyval.nodo)->codigo = cod_load_variavel_logica(s->id, s->global);
		  }
#line 2530 "parser.tab.c"
    break;

  case 101:
#line 732 "parser.y"
                           {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2536 "parser.tab.c"
    break;

  case 102:
#line 733 "parser.y"
                             {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2542 "parser.tab.c"
    break;

  case 103:
#line 734 "parser.y"
                                     {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 2548 "parser.tab.c"
    break;

  case 104:
#line 738 "parser.y"
                { verifica_tipos((yyvsp[0].nodo)->tipo_sem, bool_sem, (yyvsp[0].nodo)->valor_lexico->linha); 
		  (yyval.nodo) = cria_nodo_unario((yyvsp[-1].valor_lexico), (yyvsp[0].nodo));
		  (yyval.nodo)->tipo_sem = bool_sem; }
#line 2556 "parser.tab.c"
    break;

  case 105:
#line 742 "parser.y"
                { verifica_tipos((yyvsp[0].nodo)->tipo_sem, bool_sem, (yyvsp[0].nodo)->valor_lexico->linha); 
		  (yyval.nodo) = cria_nodo_unario((yyvsp[-1].valor_lexico), (yyvsp[0].nodo)); 
		  (yyval.nodo)->tipo_sem = bool_sem; }
#line 2564 "parser.tab.c"
    break;

  case 106:
#line 747 "parser.y"
                { verifica_tipos((yyvsp[-2].nodo)->tipo_sem, numerico_sem, (yyvsp[-2].nodo)->valor_lexico->linha);
		  verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
		  (yyval.nodo) = cria_nodo_binario((yyvsp[-1].valor_lexico), (yyvsp[-2].nodo), (yyvsp[0].nodo));
		  (yyval.nodo)->temp = novo_registrador();
		  (yyval.nodo)->codigo = concatena_codigo((yyvsp[-2].nodo)->codigo, (yyvsp[0].nodo)->codigo);
		  code_t *op_rel = cod_op_rel_logica((yyvsp[-2].nodo)->temp, (yyvsp[0].nodo)->temp, (yyval.nodo)->temp, 1);
		  (yyval.nodo)->codigo = concatena_codigo((yyval.nodo)->codigo, op_rel);
		  (yyval.nodo)->codigo->tl = op_rel->tl;
		  (yyval.nodo)->codigo->fl = op_rel->fl;
		  
		  (yyval.nodo)->tipo_sem = bool_sem; }
#line 2580 "parser.tab.c"
    break;

  case 107:
#line 759 "parser.y"
                { verifica_tipos((yyvsp[-2].nodo)->tipo_sem, numerico_sem, (yyvsp[-2].nodo)->valor_lexico->linha);
		  verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
		  (yyval.nodo) = cria_nodo_binario((yyvsp[-1].valor_lexico), (yyvsp[-2].nodo), (yyvsp[0].nodo)); 
		  (yyval.nodo)->temp = novo_registrador();
		  (yyval.nodo)->codigo = concatena_codigo((yyvsp[-2].nodo)->codigo, (yyvsp[0].nodo)->codigo);
		  code_t *op_rel = cod_op_rel_logica((yyvsp[-2].nodo)->temp, (yyvsp[0].nodo)->temp, (yyval.nodo)->temp, 3);
		  (yyval.nodo)->codigo = concatena_codigo((yyval.nodo)->codigo, op_rel);
		  (yyval.nodo)->codigo->tl = op_rel->tl;
		  (yyval.nodo)->codigo->fl = op_rel->fl;
		  
		  (yyval.nodo)->tipo_sem = bool_sem; }
#line 2596 "parser.tab.c"
    break;

  case 108:
#line 771 "parser.y"
                { verifica_tipos((yyvsp[-2].nodo)->tipo_sem, numerico_sem, (yyvsp[-2].nodo)->valor_lexico->linha);
		  verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
		  (yyval.nodo) = cria_nodo_binario((yyvsp[-1].valor_lexico), (yyvsp[-2].nodo), (yyvsp[0].nodo)); 
		  (yyval.nodo)->temp = novo_registrador();
		  (yyval.nodo)->codigo = concatena_codigo((yyvsp[-2].nodo)->codigo, (yyvsp[0].nodo)->codigo);
		  code_t *op_rel = cod_op_rel_logica((yyvsp[-2].nodo)->temp, (yyvsp[0].nodo)->temp, (yyval.nodo)->temp, 5);
		  (yyval.nodo)->codigo = concatena_codigo((yyval.nodo)->codigo, op_rel);
		  (yyval.nodo)->codigo->tl = op_rel->tl;
		  (yyval.nodo)->codigo->fl = op_rel->fl;
		  (yyval.nodo)->tipo_sem = bool_sem; }
#line 2611 "parser.tab.c"
    break;

  case 109:
#line 782 "parser.y"
                { verifica_tipos((yyvsp[-2].nodo)->tipo_sem, numerico_sem, (yyvsp[-2].nodo)->valor_lexico->linha);
		  verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
		  (yyval.nodo) = cria_nodo_binario((yyvsp[-1].valor_lexico), (yyvsp[-2].nodo), (yyvsp[0].nodo)); 
		  (yyval.nodo)->temp = novo_registrador();
		  (yyval.nodo)->codigo = concatena_codigo((yyvsp[-2].nodo)->codigo, (yyvsp[0].nodo)->codigo);
		  code_t *op_rel = cod_op_rel_logica((yyvsp[-2].nodo)->temp, (yyvsp[0].nodo)->temp, (yyval.nodo)->temp, 6);
		  (yyval.nodo)->codigo = concatena_codigo((yyval.nodo)->codigo, op_rel);
		  (yyval.nodo)->codigo->tl = op_rel->tl;
		  (yyval.nodo)->codigo->fl = op_rel->fl;
		  (yyval.nodo)->tipo_sem = bool_sem; }
#line 2626 "parser.tab.c"
    break;

  case 110:
#line 793 "parser.y"
                { verifica_tipos((yyvsp[-2].nodo)->tipo_sem, numerico_sem, (yyvsp[-2].nodo)->valor_lexico->linha);
		  verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
		  (yyval.nodo) = cria_nodo_binario((yyvsp[-1].valor_lexico), (yyvsp[-2].nodo), (yyvsp[0].nodo)); 
		  (yyval.nodo)->temp = novo_registrador();
		  (yyval.nodo)->codigo = concatena_codigo((yyvsp[-2].nodo)->codigo, (yyvsp[0].nodo)->codigo);
		  code_t *op_rel = cod_op_rel_logica((yyvsp[-2].nodo)->temp, (yyvsp[0].nodo)->temp, (yyval.nodo)->temp, 4);
		  (yyval.nodo)->codigo = concatena_codigo((yyval.nodo)->codigo, op_rel);
		  (yyval.nodo)->codigo->tl = op_rel->tl;
		  (yyval.nodo)->codigo->fl = op_rel->fl;
		  (yyval.nodo)->tipo_sem = bool_sem; }
#line 2641 "parser.tab.c"
    break;

  case 111:
#line 804 "parser.y"
                { verifica_tipos((yyvsp[-2].nodo)->tipo_sem, numerico_sem, (yyvsp[-2].nodo)->valor_lexico->linha);
		  verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
		  (yyval.nodo) = cria_nodo_binario((yyvsp[-1].valor_lexico), (yyvsp[-2].nodo), (yyvsp[0].nodo)); 
		  (yyval.nodo)->temp = novo_registrador();
		  (yyval.nodo)->codigo = concatena_codigo((yyvsp[-2].nodo)->codigo, (yyvsp[0].nodo)->codigo);
		  code_t *op_rel = cod_op_rel_logica((yyvsp[-2].nodo)->temp, (yyvsp[0].nodo)->temp, (yyval.nodo)->temp, 2);
		  (yyval.nodo)->codigo = concatena_codigo((yyval.nodo)->codigo, op_rel);
		  (yyval.nodo)->codigo->tl = op_rel->tl;
		  (yyval.nodo)->codigo->fl = op_rel->fl;
		  (yyval.nodo)->tipo_sem = bool_sem; }
#line 2656 "parser.tab.c"
    break;

  case 112:
#line 816 "parser.y"
                { verifica_tipos((yyvsp[-2].nodo)->tipo_sem, bool_sem, (yyvsp[-2].nodo)->valor_lexico->linha);
		  verifica_tipos((yyvsp[0].nodo)->tipo_sem, bool_sem, (yyvsp[0].nodo)->valor_lexico->linha);
		  (yyval.nodo) = cria_nodo_binario((yyvsp[-1].valor_lexico), (yyvsp[-2].nodo), (yyvsp[0].nodo)); 
		  operando_instr_t *l = novo_label();
		  remenda_true(l, (yyvsp[-2].nodo)->codigo);
		  adiciona_label(l, (yyvsp[0].nodo)->codigo);
		  (yyval.nodo)->codigo = concatena_codigo((yyvsp[-2].nodo)->codigo, (yyvsp[0].nodo)->codigo);
		  (yyval.nodo)->codigo->tl = (yyvsp[0].nodo)->codigo->tl;
		  insere_lista_buracos_false((yyval.nodo)->codigo, (yyvsp[-2].nodo)->codigo->fl);
		  insere_lista_buracos_false((yyval.nodo)->codigo, (yyvsp[0].nodo)->codigo->fl);
		  (yyval.nodo)->tipo_sem = bool_sem; }
#line 2672 "parser.tab.c"
    break;

  case 113:
#line 828 "parser.y"
                { verifica_tipos((yyvsp[-2].nodo)->tipo_sem, bool_sem, (yyvsp[-2].nodo)->valor_lexico->linha);
		  verifica_tipos((yyvsp[0].nodo)->tipo_sem, bool_sem, (yyvsp[0].nodo)->valor_lexico->linha);
		  (yyval.nodo) = cria_nodo_binario((yyvsp[-1].valor_lexico), (yyvsp[-2].nodo), (yyvsp[0].nodo));
		  operando_instr_t *l = novo_label();
		  remenda_false(l, (yyvsp[-2].nodo)->codigo);
		  adiciona_label(l, (yyvsp[0].nodo)->codigo);
		  (yyval.nodo)->codigo = concatena_codigo((yyvsp[-2].nodo)->codigo, (yyvsp[0].nodo)->codigo);
		  (yyval.nodo)->codigo->fl = (yyvsp[0].nodo)->codigo->fl;
		  insere_lista_buracos_true((yyval.nodo)->codigo, (yyvsp[-2].nodo)->codigo->tl);
		  insere_lista_buracos_true((yyval.nodo)->codigo, (yyvsp[0].nodo)->codigo->tl);
 		  (yyval.nodo)->tipo_sem = bool_sem; }
#line 2688 "parser.tab.c"
    break;

  case 114:
#line 841 "parser.y"
                                        {
		simbolo_t *s;
		if((yyvsp[0].nodo) == NULL)
			s = referencia(escopo, (yyvsp[-1].valor_lexico), simbolo_variavel);
		else
			s = referencia(escopo, (yyvsp[-1].valor_lexico), simbolo_vetor);
		(yyval.nodo) = cria_nodo_vetor((yyvsp[-1].valor_lexico), (yyvsp[0].nodo));
		(yyval.nodo)->tipo_sem = s->tipo;
	  	(yyval.nodo)->temp = novo_registrador();
		(yyval.nodo)->codigo = cod_load_variavel((yyval.nodo)->temp, s->id, s->global);
		  }
#line 2704 "parser.tab.c"
    break;

  case 115:
#line 852 "parser.y"
                                        {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2710 "parser.tab.c"
    break;

  case 116:
#line 853 "parser.y"
                                        {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2716 "parser.tab.c"
    break;

  case 117:
#line 854 "parser.y"
                                                {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2722 "parser.tab.c"
    break;

  case 118:
#line 855 "parser.y"
                                                {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2728 "parser.tab.c"
    break;

  case 119:
#line 857 "parser.y"
                                                {
		verifica_tipos((yyvsp[-4].nodo)->tipo_sem, bool_sem, (yyvsp[-4].nodo)->valor_lexico->linha);
		verifica_tipos((yyvsp[-2].nodo)->tipo_sem, numerico_sem, (yyvsp[-2].nodo)->valor_lexico->linha);
		verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
		ast_t *n = cria_nodo(ternario, NULL);
		insere_filho(n, (yyvsp[-4].nodo));
		insere_filho(n, (yyvsp[-2].nodo));
		insere_filho(n, (yyvsp[0].nodo));
		n->tipo_sem = infere_tipo((yyvsp[-2].nodo), (yyvsp[0].nodo));
		libera_tk((yyvsp[-3].valor_lexico));
		(yyval.nodo) = n;	}
#line 2744 "parser.tab.c"
    break;


#line 2748 "parser.tab.c"

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
                  yystos[+*yyssp], yyvsp);
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
#line 869 "parser.y"

void yyerror(char const *s)
{
    printf ("line %d: %s\n", get_line_number(), s);
}

