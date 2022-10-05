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
#include <string.h>

int yylex(void);
void yyerror (char const *s);
int get_line_number();


extern void *arvore;

pilha_t *escopo = NULL;

operando_instr_t *label_main = NULL;


#line 97 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TK_PR_INT = 3,                  /* TK_PR_INT  */
  YYSYMBOL_TK_PR_FLOAT = 4,                /* TK_PR_FLOAT  */
  YYSYMBOL_TK_PR_BOOL = 5,                 /* TK_PR_BOOL  */
  YYSYMBOL_TK_PR_CHAR = 6,                 /* TK_PR_CHAR  */
  YYSYMBOL_TK_PR_STRING = 7,               /* TK_PR_STRING  */
  YYSYMBOL_TK_PR_IF = 8,                   /* TK_PR_IF  */
  YYSYMBOL_TK_PR_THEN = 9,                 /* TK_PR_THEN  */
  YYSYMBOL_TK_PR_ELSE = 10,                /* TK_PR_ELSE  */
  YYSYMBOL_TK_PR_WHILE = 11,               /* TK_PR_WHILE  */
  YYSYMBOL_TK_PR_DO = 12,                  /* TK_PR_DO  */
  YYSYMBOL_TK_PR_INPUT = 13,               /* TK_PR_INPUT  */
  YYSYMBOL_TK_PR_OUTPUT = 14,              /* TK_PR_OUTPUT  */
  YYSYMBOL_TK_PR_RETURN = 15,              /* TK_PR_RETURN  */
  YYSYMBOL_TK_PR_CONST = 16,               /* TK_PR_CONST  */
  YYSYMBOL_TK_PR_STATIC = 17,              /* TK_PR_STATIC  */
  YYSYMBOL_TK_PR_FOREACH = 18,             /* TK_PR_FOREACH  */
  YYSYMBOL_TK_PR_FOR = 19,                 /* TK_PR_FOR  */
  YYSYMBOL_TK_PR_SWITCH = 20,              /* TK_PR_SWITCH  */
  YYSYMBOL_TK_PR_CASE = 21,                /* TK_PR_CASE  */
  YYSYMBOL_TK_PR_BREAK = 22,               /* TK_PR_BREAK  */
  YYSYMBOL_TK_PR_CONTINUE = 23,            /* TK_PR_CONTINUE  */
  YYSYMBOL_TK_PR_CLASS = 24,               /* TK_PR_CLASS  */
  YYSYMBOL_TK_PR_PRIVATE = 25,             /* TK_PR_PRIVATE  */
  YYSYMBOL_TK_PR_PUBLIC = 26,              /* TK_PR_PUBLIC  */
  YYSYMBOL_TK_PR_PROTECTED = 27,           /* TK_PR_PROTECTED  */
  YYSYMBOL_TK_PR_END = 28,                 /* TK_PR_END  */
  YYSYMBOL_TK_PR_DEFAULT = 29,             /* TK_PR_DEFAULT  */
  YYSYMBOL_TK_OC_LE = 30,                  /* TK_OC_LE  */
  YYSYMBOL_TK_OC_GE = 31,                  /* TK_OC_GE  */
  YYSYMBOL_TK_OC_EQ = 32,                  /* TK_OC_EQ  */
  YYSYMBOL_TK_OC_NE = 33,                  /* TK_OC_NE  */
  YYSYMBOL_TK_OC_AND = 34,                 /* TK_OC_AND  */
  YYSYMBOL_TK_OC_OR = 35,                  /* TK_OC_OR  */
  YYSYMBOL_TK_OC_SL = 36,                  /* TK_OC_SL  */
  YYSYMBOL_TK_OC_SR = 37,                  /* TK_OC_SR  */
  YYSYMBOL_TK_LIT_INT = 38,                /* TK_LIT_INT  */
  YYSYMBOL_TK_LIT_FLOAT = 39,              /* TK_LIT_FLOAT  */
  YYSYMBOL_TK_LIT_FALSE = 40,              /* TK_LIT_FALSE  */
  YYSYMBOL_TK_LIT_TRUE = 41,               /* TK_LIT_TRUE  */
  YYSYMBOL_TK_LIT_CHAR = 42,               /* TK_LIT_CHAR  */
  YYSYMBOL_TK_LIT_STRING = 43,             /* TK_LIT_STRING  */
  YYSYMBOL_TK_IDENTIFICADOR = 44,          /* TK_IDENTIFICADOR  */
  YYSYMBOL_TOKEN_ERRO = 45,                /* TOKEN_ERRO  */
  YYSYMBOL_46_ = 46,                       /* '|'  */
  YYSYMBOL_47_ = 47,                       /* '+'  */
  YYSYMBOL_48_ = 48,                       /* '-'  */
  YYSYMBOL_49_ = 49,                       /* '*'  */
  YYSYMBOL_50_ = 50,                       /* '/'  */
  YYSYMBOL_51_ = 51,                       /* '<'  */
  YYSYMBOL_52_ = 52,                       /* '>'  */
  YYSYMBOL_53_ = 53,                       /* '='  */
  YYSYMBOL_54_ = 54,                       /* '!'  */
  YYSYMBOL_55_ = 55,                       /* '&'  */
  YYSYMBOL_56_ = 56,                       /* '%'  */
  YYSYMBOL_57_ = 57,                       /* '#'  */
  YYSYMBOL_58_ = 58,                       /* '^'  */
  YYSYMBOL_59_ = 59,                       /* '$'  */
  YYSYMBOL_60_ = 60,                       /* '?'  */
  YYSYMBOL_61_ternario_ = 61,              /* "ternario"  */
  YYSYMBOL_62_unario_ = 62,                /* "unario"  */
  YYSYMBOL_63_ = 63,                       /* ':'  */
  YYSYMBOL_avaliacao_logica = 64,          /* avaliacao_logica  */
  YYSYMBOL_endereco_variavel = 65,         /* endereco_variavel  */
  YYSYMBOL_valor_ponteiro = 66,            /* valor_ponteiro  */
  YYSYMBOL_inverte_sinal = 67,             /* inverte_sinal  */
  YYSYMBOL_68_ = 68,                       /* '['  */
  YYSYMBOL_69_ = 69,                       /* ']'  */
  YYSYMBOL_70_ = 70,                       /* ';'  */
  YYSYMBOL_71_ = 71,                       /* ','  */
  YYSYMBOL_72_ = 72,                       /* '{'  */
  YYSYMBOL_73_ = 73,                       /* '}'  */
  YYSYMBOL_74_ = 74,                       /* '('  */
  YYSYMBOL_75_ = 75,                       /* ')'  */
  YYSYMBOL_YYACCEPT = 76,                  /* $accept  */
  YYSYMBOL_input = 77,                     /* input  */
  YYSYMBOL_programa = 78,                  /* programa  */
  YYSYMBOL_tipo = 79,                      /* tipo  */
  YYSYMBOL_estatico = 80,                  /* estatico  */
  YYSYMBOL_constante = 81,                 /* constante  */
  YYSYMBOL_vetor = 82,                     /* vetor  */
  YYSYMBOL_var_global = 83,                /* var_global  */
  YYSYMBOL_lista_identificadores_g = 84,   /* lista_identificadores_g  */
  YYSYMBOL_funcao = 85,                    /* funcao  */
  YYSYMBOL_bloco_cmd_inicio = 86,          /* bloco_cmd_inicio  */
  YYSYMBOL_bloco_cmd_fim = 87,             /* bloco_cmd_fim  */
  YYSYMBOL_corpo_funcao = 88,              /* corpo_funcao  */
  YYSYMBOL_cabecalho = 89,                 /* cabecalho  */
  YYSYMBOL_parametros = 90,                /* parametros  */
  YYSYMBOL_lista_parametros = 91,          /* lista_parametros  */
  YYSYMBOL_bloco_cmd = 92,                 /* bloco_cmd  */
  YYSYMBOL_lista_comandos = 93,            /* lista_comandos  */
  YYSYMBOL_comando = 94,                   /* comando  */
  YYSYMBOL_declaracao_variavel = 95,       /* declaracao_variavel  */
  YYSYMBOL_lista_identificadores_l = 96,   /* lista_identificadores_l  */
  YYSYMBOL_inicializa_variavel = 97,       /* inicializa_variavel  */
  YYSYMBOL_literal = 98,                   /* literal  */
  YYSYMBOL_identificador_ou_literal = 99,  /* identificador_ou_literal  */
  YYSYMBOL_acesso_vetor = 100,             /* acesso_vetor  */
  YYSYMBOL_atribuicao = 101,               /* atribuicao  */
  YYSYMBOL_entrada = 102,                  /* entrada  */
  YYSYMBOL_saida = 103,                    /* saida  */
  YYSYMBOL_parametro_chamada_funcao = 104, /* parametro_chamada_funcao  */
  YYSYMBOL_mais_parametros_chamada_funcao = 105, /* mais_parametros_chamada_funcao  */
  YYSYMBOL_chamada_de_funcao = 106,        /* chamada_de_funcao  */
  YYSYMBOL_shift = 107,                    /* shift  */
  YYSYMBOL_token_shift = 108,              /* token_shift  */
  YYSYMBOL_retorno = 109,                  /* retorno  */
  YYSYMBOL_controle_fluxo = 110,           /* controle_fluxo  */
  YYSYMBOL_cf_if = 111,                    /* cf_if  */
  YYSYMBOL_cf_else = 112,                  /* cf_else  */
  YYSYMBOL_cf_for = 113,                   /* cf_for  */
  YYSYMBOL_cf_while = 114,                 /* cf_while  */
  YYSYMBOL_literal_numerico = 115,         /* literal_numerico  */
  YYSYMBOL_operandos_aritmeticos = 116,    /* operandos_aritmeticos  */
  YYSYMBOL_expressao_aritmetica = 117,     /* expressao_aritmetica  */
  YYSYMBOL_literal_booleano = 118,         /* literal_booleano  */
  YYSYMBOL_operandos_booleanos = 119,      /* operandos_booleanos  */
  YYSYMBOL_expressao_booleana = 120,       /* expressao_booleana  */
  YYSYMBOL_expressao = 121                 /* expressao  */
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

#if 1

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
#endif /* 1 */

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

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   306


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
       0,   163,   163,   170,   177,   185,   187,   188,   189,   190,
     191,   193,   193,   195,   195,   197,   198,   200,   218,   222,
     224,   271,   274,   278,   281,   299,   307,   313,   321,   328,
     330,   343,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   354,   355,   359,   369,   371,   373,   377,   386,   387,
     388,   389,   390,   391,   394,   395,   401,   402,   404,   427,
     435,   442,   444,   445,   447,   448,   496,   509,   510,   512,
     529,   530,   531,   533,   566,   567,   569,   598,   620,   626,
     631,   632,   633,   645,   646,   650,   656,   662,   666,   670,
     675,   684,   693,   698,   708,   718,   724,   730,   736,   741,
     748,   759,   760,   761,   764,   768,   773,   789,   804,   819,
     834,   849,   865,   877,   891,   902,   903,   904,   910,   912
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TK_PR_INT",
  "TK_PR_FLOAT", "TK_PR_BOOL", "TK_PR_CHAR", "TK_PR_STRING", "TK_PR_IF",
  "TK_PR_THEN", "TK_PR_ELSE", "TK_PR_WHILE", "TK_PR_DO", "TK_PR_INPUT",
  "TK_PR_OUTPUT", "TK_PR_RETURN", "TK_PR_CONST", "TK_PR_STATIC",
  "TK_PR_FOREACH", "TK_PR_FOR", "TK_PR_SWITCH", "TK_PR_CASE",
  "TK_PR_BREAK", "TK_PR_CONTINUE", "TK_PR_CLASS", "TK_PR_PRIVATE",
  "TK_PR_PUBLIC", "TK_PR_PROTECTED", "TK_PR_END", "TK_PR_DEFAULT",
  "TK_OC_LE", "TK_OC_GE", "TK_OC_EQ", "TK_OC_NE", "TK_OC_AND", "TK_OC_OR",
  "TK_OC_SL", "TK_OC_SR", "TK_LIT_INT", "TK_LIT_FLOAT", "TK_LIT_FALSE",
  "TK_LIT_TRUE", "TK_LIT_CHAR", "TK_LIT_STRING", "TK_IDENTIFICADOR",
  "TOKEN_ERRO", "'|'", "'+'", "'-'", "'*'", "'/'", "'<'", "'>'", "'='",
  "'!'", "'&'", "'%'", "'#'", "'^'", "'$'", "'?'", "\"ternario\"",
  "\"unario\"", "':'", "avaliacao_logica", "endereco_variavel",
  "valor_ponteiro", "inverte_sinal", "'['", "']'", "';'", "','", "'{'",
  "'}'", "'('", "')'", "$accept", "input", "programa", "tipo", "estatico",
  "constante", "vetor", "var_global", "lista_identificadores_g", "funcao",
  "bloco_cmd_inicio", "bloco_cmd_fim", "corpo_funcao", "cabecalho",
  "parametros", "lista_parametros", "bloco_cmd", "lista_comandos",
  "comando", "declaracao_variavel", "lista_identificadores_l",
  "inicializa_variavel", "literal", "identificador_ou_literal",
  "acesso_vetor", "atribuicao", "entrada", "saida",
  "parametro_chamada_funcao", "mais_parametros_chamada_funcao",
  "chamada_de_funcao", "shift", "token_shift", "retorno", "controle_fluxo",
  "cf_if", "cf_else", "cf_for", "cf_while", "literal_numerico",
  "operandos_aritmeticos", "expressao_aritmetica", "literal_booleano",
  "operandos_booleanos", "expressao_booleana", "expressao", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

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
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    14,    33,    50,    21,     6,    52,     7,
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

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
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

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
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

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
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
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
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
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
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

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

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
  case 2: /* input: programa  */
#line 164 "parser.y"
        { 
		(yyvsp[0].nodo)->codigo = cod_init(vars_globais((yyvsp[0].nodo)), label_main, (yyvsp[0].nodo)->codigo);
	    arvore = (yyvsp[0].nodo); 
	    sai_escopo(escopo); 
	}
#line 1666 "parser.tab.c"
    break;

  case 3: /* programa: programa var_global  */
#line 171 "parser.y"
        { (yyval.nodo) = insere_fim_lista((yyvsp[0].nodo), (yyvsp[-1].nodo));
	  if((yyvsp[-1].nodo) != NULL)
	  	(yyval.nodo)->codigo = concatena_codigo((yyvsp[-1].nodo)->codigo, (yyvsp[0].nodo)->codigo);
	  else 
	  	(yyval.nodo)->codigo = (yyvsp[0].nodo)->codigo; 		
	}
#line 1677 "parser.tab.c"
    break;

  case 4: /* programa: programa funcao  */
#line 178 "parser.y"
        { (yyval.nodo) = insere_fim_lista((yyvsp[0].nodo), (yyvsp[-1].nodo));
	  if((yyvsp[-1].nodo) != NULL)
	  	(yyval.nodo)->codigo = concatena_codigo((yyvsp[-1].nodo)->codigo, (yyvsp[0].nodo)->codigo);
	  else 
	  	(yyval.nodo)->codigo = (yyvsp[0].nodo)->codigo; 
	}
#line 1688 "parser.tab.c"
    break;

  case 5: /* programa: %empty  */
#line 185 "parser.y"
        { (yyval.nodo) = NULL;}
#line 1694 "parser.tab.c"
    break;

  case 6: /* tipo: TK_PR_INT  */
#line 187 "parser.y"
                   {(yyval.tipo) = (yyvsp[0].tipo);}
#line 1700 "parser.tab.c"
    break;

  case 7: /* tipo: TK_PR_FLOAT  */
#line 188 "parser.y"
                       {(yyval.tipo) = (yyvsp[0].tipo);}
#line 1706 "parser.tab.c"
    break;

  case 8: /* tipo: TK_PR_CHAR  */
#line 189 "parser.y"
                       {(yyval.tipo) = (yyvsp[0].tipo);}
#line 1712 "parser.tab.c"
    break;

  case 9: /* tipo: TK_PR_BOOL  */
#line 190 "parser.y"
                       {(yyval.tipo) = (yyvsp[0].tipo);}
#line 1718 "parser.tab.c"
    break;

  case 10: /* tipo: TK_PR_STRING  */
#line 191 "parser.y"
                       {(yyval.tipo) = (yyvsp[0].tipo);}
#line 1724 "parser.tab.c"
    break;

  case 15: /* vetor: '[' TK_LIT_INT ']'  */
#line 197 "parser.y"
                          {(yyval.nodo) = cria_nodo(literal, (yyvsp[-1].valor_lexico));}
#line 1730 "parser.tab.c"
    break;

  case 16: /* vetor: %empty  */
#line 198 "parser.y"
       {(yyval.nodo) = NULL;}
#line 1736 "parser.tab.c"
    break;

  case 17: /* var_global: estatico tipo TK_IDENTIFICADOR vetor lista_identificadores_g ';'  */
#line 201 "parser.y"
        {
	 simbolo_t *s = novo_simbolo();
	 adiciona_valor_lexico(s, (yyvsp[-3].valor_lexico));
	 s->tipo = (yyvsp[-4].tipo);
	 if((yyvsp[-2].nodo) == NULL)
		s->natureza = simbolo_variavel;
	 else {
		s->natureza = simbolo_vetor;
		s->tamanho = (yyvsp[-2].nodo)->valor_lexico->valor.inteiro;
		libera((yyvsp[-2].nodo));
	 }
	 escopo = adiciona_simbolo(escopo, s); 
	 escopo = adiciona_lista_simbolos(escopo, (yyvsp[-1].nodo), (yyvsp[-4].tipo)); // adiciona as variaveis em lista_identificadores_g

	 (yyval.nodo) = cria_nodo_passagem((yyvsp[-3].valor_lexico));
	 (yyval.nodo)->filhos[0] = (yyvsp[-1].nodo);
	}
#line 1758 "parser.tab.c"
    break;

  case 18: /* lista_identificadores_g: lista_identificadores_g ',' TK_IDENTIFICADOR vetor  */
#line 219 "parser.y"
        {// cria uma arvore temporaria que guarda as variaveis 
	 ast_t *n = cria_nodo_vetor((yyvsp[-1].valor_lexico), (yyvsp[0].nodo));
	 (yyval.nodo) = insere_fim_lista(n, (yyvsp[-3].nodo)); }
#line 1766 "parser.tab.c"
    break;

  case 19: /* lista_identificadores_g: %empty  */
#line 222 "parser.y"
          {(yyval.nodo) = NULL;}
#line 1772 "parser.tab.c"
    break;

  case 20: /* funcao: cabecalho '{' corpo_funcao '}'  */
#line 225 "parser.y"
        {
		insere_filho((yyvsp[-3].nodo), (yyvsp[-1].nodo));
		(yyval.nodo) = (yyvsp[-3].nodo);
		bool func_main = eh_main((yyval.nodo));
		if(func_main)
			(yyval.nodo)->codigo = cod_funcao_prologo_main(numero_parametros(escopo->t));
		else 
			(yyval.nodo)->codigo = cod_funcao_prologo(numero_parametros(escopo->t)); // adiciona o prologo antes de fechar o escopo local
		char *function_id = calloc(strlen((yyval.nodo)->valor_lexico->valor.cadeia_caracteres) + 10, sizeof(char));
		sprintf(function_id, "FUNCTION %s", (yyval.nodo)->valor_lexico->valor.cadeia_caracteres);
		adiciona_comentario(function_id, (yyval.nodo)->codigo);

		escopo = sai_escopo(escopo); // fechando o escopo local na hora da redução
		/*
		
		ALTERACAO PARA FUNCAO RECURSIVA.
		Isso aqui é feito no cabecalho agora.

		simbolo_t *s = novo_simbolo();
		adiciona_valor_lexico(s, $1->valor_lexico);
		s->natureza = simbolo_funcao;
		s->tipo = $1->tipo_sem;
		s->label = novo_label();
		if(func_main)
			label_main = s->label;
		escopo = adiciona_simbolo(escopo, s); // adicionando a funcao ao escopo global
		*/
		operando_instr_t *ret;
		if((yyvsp[-1].nodo) != NULL)
		{
			(yyval.nodo)->codigo = concatena_codigo((yyval.nodo)->codigo, (yyvsp[-1].nodo)->codigo);
		    ret = retorno((yyvsp[-1].nodo));
		}
		else 
			ret = NULL;
		(yyval.nodo)->codigo = concatena_codigo((yyval.nodo)->codigo, cod_funcao_epilogo(ret));

		//ALTERACAO PARA FUNCAO RECURSIVA
		//No cabecalho o simbolo é incluso na tabela do escopo global.
		//Basta achar a referencia para ele agora.
		simbolo_t *s = procura_nome_em_todas_tabelas(escopo, (yyvsp[-3].nodo)->valor_lexico->valor.cadeia_caracteres);

		
		adiciona_label(s->label, (yyval.nodo)->codigo);
	}
#line 1822 "parser.tab.c"
    break;

  case 21: /* bloco_cmd_inicio: '{'  */
#line 271 "parser.y"
                      { 
						escopo = novo_escopo(escopo, escopo_interno, retorna_proximo_id_do_escopo_da_funcao(escopo));
					  }
#line 1830 "parser.tab.c"
    break;

  case 22: /* bloco_cmd_fim: '}'  */
#line 274 "parser.y"
                   {escopo = sai_escopo(escopo); }
#line 1836 "parser.tab.c"
    break;

  case 23: /* corpo_funcao: lista_comandos  */
#line 278 "parser.y"
                       {(yyval.nodo) = (yyvsp[0].nodo);}
#line 1842 "parser.tab.c"
    break;

  case 24: /* cabecalho: estatico tipo TK_IDENTIFICADOR '(' parametros ')'  */
#line 282 "parser.y"
        {ast_t *n = cria_nodo(funcao, (yyvsp[-3].valor_lexico));
	 n->tipo_sem = (yyvsp[-4].tipo);
	 (yyval.nodo) = n; 
	 
	//ALTERACAO PARA FUNCAO RECURSIVA
	bool func_main = eh_main((yyval.nodo));
	simbolo_t *s = novo_simbolo();
	adiciona_valor_lexico(s, n->valor_lexico);
	s->natureza = simbolo_funcao;
	s->tipo = n->tipo_sem;
	s->label = novo_label();
	if(func_main)
			label_main = s->label;

	adiciona_simbolo_no_escopo_global(escopo, s);
	
	}
#line 1864 "parser.tab.c"
    break;

  case 25: /* parametros: constante tipo TK_IDENTIFICADOR lista_parametros  */
#line 300 "parser.y"
        {simbolo_t *s = novo_simbolo();
	 adiciona_valor_lexico(s, (yyvsp[-1].valor_lexico));
	 libera_tk((yyvsp[-1].valor_lexico));
	 s->natureza = simbolo_parametro;
	 s->tipo = (yyvsp[-2].tipo);
	 escopo = adiciona_simbolo(escopo, s);  }
#line 1875 "parser.tab.c"
    break;

  case 26: /* parametros: %empty  */
#line 307 "parser.y"
        {// primeira redução que vai ocorrer, inicio do escopo local da funcao s/ parametros
	 //ALTERACAO PARA FUNCAO RECURSIVA.
	 //Precisa inicializar a pilha para que exista um escopo global.
	 if(escopo == NULL)
	 	escopo = inicializa_pilha();
	 escopo = novo_escopo(escopo, escopo_funcao, REGISTRO_ATIVACAO_OFFSET+4);}
#line 1886 "parser.tab.c"
    break;

  case 27: /* lista_parametros: lista_parametros ',' constante tipo TK_IDENTIFICADOR  */
#line 314 "parser.y"
        {simbolo_t *s = novo_simbolo();
	 adiciona_valor_lexico(s, (yyvsp[0].valor_lexico));
	 libera_tk((yyvsp[0].valor_lexico));
	 s->natureza = simbolo_parametro;
	 s->tipo = (yyvsp[-1].tipo);
	 escopo = adiciona_simbolo(escopo, s); }
#line 1897 "parser.tab.c"
    break;

  case 28: /* lista_parametros: %empty  */
#line 321 "parser.y"
        {//primeira redução que vai ocorrer, inicio do escopo local da funcao c/ paramentros
	 //ALTERACAO PARA FUNCAO RECURSIVA.
	 //Precisa inicializar a pilha para que exista um escopo global.
	 if(escopo == NULL)
	 	escopo = inicializa_pilha();
	 escopo = novo_escopo(escopo, escopo_funcao, REGISTRO_ATIVACAO_OFFSET+4);}
#line 1908 "parser.tab.c"
    break;

  case 29: /* bloco_cmd: bloco_cmd_inicio lista_comandos bloco_cmd_fim  */
#line 328 "parser.y"
                                                         {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 1914 "parser.tab.c"
    break;

  case 30: /* lista_comandos: lista_comandos comando  */
#line 331 "parser.y"
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
#line 1931 "parser.tab.c"
    break;

  case 31: /* lista_comandos: %empty  */
#line 343 "parser.y"
            {(yyval.nodo) = NULL; }
#line 1937 "parser.tab.c"
    break;

  case 32: /* comando: bloco_cmd ';'  */
#line 345 "parser.y"
                                                {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 1943 "parser.tab.c"
    break;

  case 33: /* comando: declaracao_variavel ';'  */
#line 346 "parser.y"
                                        {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 1949 "parser.tab.c"
    break;

  case 34: /* comando: atribuicao ';'  */
#line 347 "parser.y"
                                                {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 1955 "parser.tab.c"
    break;

  case 35: /* comando: chamada_de_funcao ';'  */
#line 348 "parser.y"
                                        {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 1961 "parser.tab.c"
    break;

  case 36: /* comando: shift ';'  */
#line 349 "parser.y"
                                                {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 1967 "parser.tab.c"
    break;

  case 37: /* comando: retorno ';'  */
#line 350 "parser.y"
                                                {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 1973 "parser.tab.c"
    break;

  case 38: /* comando: TK_PR_BREAK ';'  */
#line 351 "parser.y"
                                                {(yyval.nodo) = cria_nodo(cmd_break, NULL);}
#line 1979 "parser.tab.c"
    break;

  case 39: /* comando: TK_PR_CONTINUE ';'  */
#line 352 "parser.y"
                                        {(yyval.nodo) = cria_nodo(cmd_continue, NULL);}
#line 1985 "parser.tab.c"
    break;

  case 40: /* comando: entrada ';'  */
#line 353 "parser.y"
                                                {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 1991 "parser.tab.c"
    break;

  case 41: /* comando: saida ';'  */
#line 354 "parser.y"
                                                {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 1997 "parser.tab.c"
    break;

  case 42: /* comando: controle_fluxo ';'  */
#line 355 "parser.y"
                                        {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 2003 "parser.tab.c"
    break;

  case 43: /* declaracao_variavel: estatico constante tipo inicializa_variavel lista_identificadores_l  */
#line 360 "parser.y"
        { (yyval.nodo) = insere_inicio_lista((yyvsp[-1].nodo), (yyvsp[0].nodo));
	  int aux_proximo_id_antes = retorna_proximo_id_do_escopo_da_funcao(escopo);
	  escopo = adiciona_lista_simbolos(escopo, (yyval.nodo), (yyvsp[-2].tipo));
	  int aux_proximo_id_depois = retorna_proximo_id_do_escopo_da_funcao(escopo);
	  int numero_de_declaracoes = (aux_proximo_id_depois - aux_proximo_id_antes)/4;
	  (yyval.nodo) = remove_nodos_inuteis((yyval.nodo));
	  if((yyval.nodo) == NULL)
	  	(yyval.nodo) = cria_nodo_passagem(NULL);
	  (yyval.nodo)->codigo = cod_alocacao_var_local(numero_de_declaracoes); }
#line 2017 "parser.tab.c"
    break;

  case 44: /* lista_identificadores_l: lista_identificadores_l ',' inicializa_variavel  */
#line 370 "parser.y"
                {(yyval.nodo) = insere_fim_lista((yyvsp[0].nodo), (yyvsp[-2].nodo)); }
#line 2023 "parser.tab.c"
    break;

  case 45: /* lista_identificadores_l: %empty  */
#line 371 "parser.y"
            {(yyval.nodo) = NULL;}
#line 2029 "parser.tab.c"
    break;

  case 46: /* inicializa_variavel: TK_IDENTIFICADOR  */
#line 374 "parser.y"
                {
			(yyval.nodo) = cria_nodo(identificador, (yyvsp[0].valor_lexico));
		}
#line 2037 "parser.tab.c"
    break;

  case 47: /* inicializa_variavel: TK_IDENTIFICADOR TK_OC_LE identificador_ou_literal  */
#line 378 "parser.y"
                {
			ast_t *n = cria_nodo(declaracao, NULL);
			insere_filho(n, cria_nodo(identificador, (yyvsp[-2].valor_lexico)));
			insere_filho(n, (yyvsp[0].nodo));
			libera_tk((yyvsp[-1].valor_lexico));
			(yyval.nodo) = n;
		}
#line 2049 "parser.tab.c"
    break;

  case 48: /* literal: TK_LIT_TRUE  */
#line 386 "parser.y"
                       {(yyval.nodo) = cria_nodo(literal, (yyvsp[0].valor_lexico)); (yyval.nodo)->tipo_sem = bool_sem;}
#line 2055 "parser.tab.c"
    break;

  case 49: /* literal: TK_LIT_FALSE  */
#line 387 "parser.y"
                           {(yyval.nodo) = cria_nodo(literal, (yyvsp[0].valor_lexico)); (yyval.nodo)->tipo_sem = bool_sem;}
#line 2061 "parser.tab.c"
    break;

  case 50: /* literal: TK_LIT_INT  */
#line 388 "parser.y"
                           {(yyval.nodo) = cria_nodo(literal, (yyvsp[0].valor_lexico)); (yyval.nodo)->tipo_sem = int_sem;}
#line 2067 "parser.tab.c"
    break;

  case 51: /* literal: TK_LIT_FLOAT  */
#line 389 "parser.y"
                           {(yyval.nodo) = cria_nodo(literal, (yyvsp[0].valor_lexico)); (yyval.nodo)->tipo_sem = float_sem;}
#line 2073 "parser.tab.c"
    break;

  case 52: /* literal: TK_LIT_STRING  */
#line 390 "parser.y"
                           {(yyval.nodo) = cria_nodo(literal, (yyvsp[0].valor_lexico)); (yyval.nodo)->tipo_sem = string_sem;}
#line 2079 "parser.tab.c"
    break;

  case 53: /* literal: TK_LIT_CHAR  */
#line 391 "parser.y"
                           {(yyval.nodo) = cria_nodo(literal, (yyvsp[0].valor_lexico)); (yyval.nodo)->tipo_sem = char_sem;}
#line 2085 "parser.tab.c"
    break;

  case 54: /* identificador_ou_literal: literal  */
#line 394 "parser.y"
                {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2091 "parser.tab.c"
    break;

  case 55: /* identificador_ou_literal: TK_IDENTIFICADOR  */
#line 395 "parser.y"
                          {
		simbolo_t *s = referencia(escopo, (yyvsp[0].valor_lexico), simbolo_variavel);
		(yyval.nodo) = cria_nodo(identificador, (yyvsp[0].valor_lexico));
		(yyval.nodo)->tipo_sem = s->tipo;
	}
#line 2101 "parser.tab.c"
    break;

  case 56: /* acesso_vetor: '[' expressao ']'  */
#line 401 "parser.y"
                                {verifica_tipos((yyvsp[-1].nodo)->tipo_sem, int_sem, (yyvsp[-1].nodo)->valor_lexico->linha); (yyval.nodo) = (yyvsp[-1].nodo);}
#line 2107 "parser.tab.c"
    break;

  case 57: /* acesso_vetor: %empty  */
#line 402 "parser.y"
                      {(yyval.nodo) = NULL;}
#line 2113 "parser.tab.c"
    break;

  case 58: /* atribuicao: TK_IDENTIFICADOR acesso_vetor '=' expressao  */
#line 405 "parser.y"
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
#line 2139 "parser.tab.c"
    break;

  case 59: /* entrada: TK_PR_INPUT TK_IDENTIFICADOR  */
#line 428 "parser.y"
        {
		simbolo_t *s = referencia(escopo, (yyvsp[0].valor_lexico), simbolo_variavel);
		ast_t *n = cria_nodo(entrada, NULL);
		insere_filho(n, cria_nodo(identificador, (yyvsp[0].valor_lexico)));
		n->tipo_sem = s->tipo;
		(yyval.nodo) = n;
	}
#line 2151 "parser.tab.c"
    break;

  case 60: /* saida: TK_PR_OUTPUT identificador_ou_literal  */
#line 436 "parser.y"
        {
		ast_t *n = cria_nodo(saida, NULL);
		insere_filho(n, (yyvsp[0].nodo));
		(yyval.nodo) = n;
	}
#line 2161 "parser.tab.c"
    break;

  case 61: /* parametro_chamada_funcao: expressao mais_parametros_chamada_funcao  */
#line 443 "parser.y"
          {(yyval.nodo) = insere_inicio_lista((yyvsp[-1].nodo), (yyvsp[0].nodo));}
#line 2167 "parser.tab.c"
    break;

  case 62: /* parametro_chamada_funcao: %empty  */
#line 444 "parser.y"
      {(yyval.nodo) = NULL;}
#line 2173 "parser.tab.c"
    break;

  case 63: /* mais_parametros_chamada_funcao: mais_parametros_chamada_funcao ',' expressao  */
#line 446 "parser.y"
          {(yyval.nodo) = insere_fim_lista((yyvsp[0].nodo), (yyvsp[-2].nodo));}
#line 2179 "parser.tab.c"
    break;

  case 64: /* mais_parametros_chamada_funcao: %empty  */
#line 447 "parser.y"
          {(yyval.nodo) = NULL;}
#line 2185 "parser.tab.c"
    break;

  case 65: /* chamada_de_funcao: TK_IDENTIFICADOR '(' parametro_chamada_funcao ')'  */
#line 449 "parser.y"
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

		code_t *preparacao = cod_chamada_func_antes(5, param_offset/4-REGISTRO_ATIVACAO_OFFSET/4);

		char *call_id = calloc(strlen(s->valor_lexico->valor.cadeia_caracteres) + 6, sizeof(char));
		sprintf(call_id, "CALL %s", s->valor_lexico->valor.cadeia_caracteres);

		n->temp = novo_registrador();
		n->codigo = concatena_codigo(cod_params, preparacao);
	    n->codigo = concatena_codigo(n->codigo, cod_jump_incondicional(s->label));
		n->codigo = concatena_codigo(n->codigo, cod_load_pilha(n->temp, 12));
		adiciona_comentario(call_id, n->codigo);
		(yyval.nodo) = n;
	}
#line 2236 "parser.tab.c"
    break;

  case 66: /* shift: TK_IDENTIFICADOR acesso_vetor token_shift TK_LIT_INT  */
#line 497 "parser.y"
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
#line 2253 "parser.tab.c"
    break;

  case 67: /* token_shift: TK_OC_SL  */
#line 509 "parser.y"
                      {(yyval.valor_lexico) = (yyvsp[0].valor_lexico);}
#line 2259 "parser.tab.c"
    break;

  case 68: /* token_shift: TK_OC_SR  */
#line 510 "parser.y"
                      {(yyval.valor_lexico) = (yyvsp[0].valor_lexico);}
#line 2265 "parser.tab.c"
    break;

  case 69: /* retorno: TK_PR_RETURN expressao  */
#line 513 "parser.y"
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
#line 2285 "parser.tab.c"
    break;

  case 70: /* controle_fluxo: cf_if  */
#line 529 "parser.y"
                         {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2291 "parser.tab.c"
    break;

  case 71: /* controle_fluxo: cf_for  */
#line 530 "parser.y"
                         {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2297 "parser.tab.c"
    break;

  case 72: /* controle_fluxo: cf_while  */
#line 531 "parser.y"
                                     {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2303 "parser.tab.c"
    break;

  case 73: /* cf_if: TK_PR_IF '(' expressao ')' bloco_cmd cf_else  */
#line 534 "parser.y"
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
#line 2340 "parser.tab.c"
    break;

  case 74: /* cf_else: TK_PR_ELSE bloco_cmd  */
#line 566 "parser.y"
                              {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2346 "parser.tab.c"
    break;

  case 75: /* cf_else: %empty  */
#line 567 "parser.y"
         {(yyval.nodo) = NULL;}
#line 2352 "parser.tab.c"
    break;

  case 76: /* cf_for: TK_PR_FOR '(' atribuicao ':' expressao ':' atribuicao ')' bloco_cmd  */
#line 570 "parser.y"
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
#line 2384 "parser.tab.c"
    break;

  case 77: /* cf_while: TK_PR_WHILE '(' expressao ')' TK_PR_DO bloco_cmd  */
#line 599 "parser.y"
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
#line 2408 "parser.tab.c"
    break;

  case 78: /* literal_numerico: TK_LIT_INT  */
#line 621 "parser.y"
        { (yyval.nodo) = cria_nodo(literal, (yyvsp[0].valor_lexico)); 
	  (yyval.nodo)->tipo_sem = int_sem;
	  (yyval.nodo)->temp = novo_registrador();
	  (yyval.nodo)->codigo = cod_load_literal((yyval.nodo)->temp, (yyvsp[0].valor_lexico)->valor.inteiro);
	   }
#line 2418 "parser.tab.c"
    break;

  case 79: /* literal_numerico: TK_LIT_FLOAT  */
#line 627 "parser.y"
        { (yyval.nodo) = cria_nodo(literal, (yyvsp[0].valor_lexico));
	  (yyval.nodo)->tipo_sem = float_sem;}
#line 2425 "parser.tab.c"
    break;

  case 80: /* operandos_aritmeticos: literal_numerico  */
#line 631 "parser.y"
                                        {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2431 "parser.tab.c"
    break;

  case 81: /* operandos_aritmeticos: chamada_de_funcao  */
#line 632 "parser.y"
                                        {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2437 "parser.tab.c"
    break;

  case 82: /* operandos_aritmeticos: TK_IDENTIFICADOR acesso_vetor  */
#line 633 "parser.y"
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
#line 2454 "parser.tab.c"
    break;

  case 83: /* operandos_aritmeticos: expressao_aritmetica  */
#line 645 "parser.y"
                                        {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2460 "parser.tab.c"
    break;

  case 84: /* operandos_aritmeticos: '(' expressao_aritmetica ')'  */
#line 646 "parser.y"
                                        {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 2466 "parser.tab.c"
    break;

  case 85: /* expressao_aritmetica: '+' operandos_aritmeticos  */
#line 651 "parser.y"
        { verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
	  (yyval.nodo) = cria_nodo_unario(((yyvsp[-1].valor_lexico)), (yyvsp[0].nodo));
	  (yyval.nodo)->tipo_sem = (yyvsp[0].nodo)->tipo_sem; 
	  (yyval.nodo)->temp = (yyvsp[0].nodo)->temp;
	  (yyval.nodo)->codigo = (yyvsp[0].nodo)->codigo;}
#line 2476 "parser.tab.c"
    break;

  case 86: /* expressao_aritmetica: '-' operandos_aritmeticos  */
#line 657 "parser.y"
        { verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
	  (yyval.nodo) = cria_nodo_unario(((yyvsp[-1].valor_lexico)), (yyvsp[0].nodo));
	  (yyval.nodo)->tipo_sem = (yyvsp[0].nodo)->tipo_sem;
	  (yyval.nodo)->temp = novo_registrador();
	  (yyval.nodo)->codigo = cod_load_literal((yyval.nodo)->temp, -(yyvsp[0].nodo)->valor_lexico->valor.inteiro); }
#line 2486 "parser.tab.c"
    break;

  case 87: /* expressao_aritmetica: '&' operandos_aritmeticos  */
#line 663 "parser.y"
        { verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
	  (yyval.nodo) = cria_nodo_unario(((yyvsp[-1].valor_lexico)), (yyvsp[0].nodo));
	  (yyval.nodo)->tipo_sem = (yyvsp[0].nodo)->tipo_sem; }
#line 2494 "parser.tab.c"
    break;

  case 88: /* expressao_aritmetica: '*' operandos_aritmeticos  */
#line 667 "parser.y"
        { verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
	  (yyval.nodo) = cria_nodo_unario(((yyvsp[-1].valor_lexico)), (yyvsp[0].nodo));
	  (yyval.nodo)->tipo_sem = (yyvsp[0].nodo)->tipo_sem; }
#line 2502 "parser.tab.c"
    break;

  case 89: /* expressao_aritmetica: '#' operandos_aritmeticos  */
#line 671 "parser.y"
        { verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
	  (yyval.nodo) = cria_nodo_unario(((yyvsp[-1].valor_lexico)), (yyvsp[0].nodo));
	  (yyval.nodo)->tipo_sem = (yyvsp[0].nodo)->tipo_sem; }
#line 2510 "parser.tab.c"
    break;

  case 90: /* expressao_aritmetica: operandos_aritmeticos '+' operandos_aritmeticos  */
#line 676 "parser.y"
        { verifica_tipos((yyvsp[-2].nodo)->tipo_sem, numerico_sem, (yyvsp[-2].nodo)->valor_lexico->linha);
	  verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
	  (yyval.nodo) = cria_nodo_binario(((yyvsp[-1].valor_lexico)), (yyvsp[-2].nodo), (yyvsp[0].nodo));
	  (yyval.nodo)->tipo_sem = infere_tipo((yyvsp[-2].nodo), (yyvsp[0].nodo));
	  (yyval.nodo)->temp = novo_registrador();
	  (yyval.nodo)->codigo = concatena_codigo((yyvsp[-2].nodo)->codigo, (yyvsp[0].nodo)->codigo);
	  (yyval.nodo)->codigo = concatena_codigo((yyval.nodo)->codigo, cod_op_bin_aritmetica((yyvsp[-2].nodo)->temp, (yyvsp[0].nodo)->temp, (yyval.nodo)->temp, '+'));  
	  }
#line 2523 "parser.tab.c"
    break;

  case 91: /* expressao_aritmetica: operandos_aritmeticos '-' operandos_aritmeticos  */
#line 685 "parser.y"
        { verifica_tipos((yyvsp[-2].nodo)->tipo_sem, numerico_sem, (yyvsp[-2].nodo)->valor_lexico->linha);
	  verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
	  (yyval.nodo) = cria_nodo_binario(((yyvsp[-1].valor_lexico)), (yyvsp[-2].nodo), (yyvsp[0].nodo));
	  (yyval.nodo)->tipo_sem = infere_tipo((yyvsp[-2].nodo), (yyvsp[0].nodo)); 
	  (yyval.nodo)->temp = novo_registrador();
	  (yyval.nodo)->codigo = concatena_codigo((yyvsp[-2].nodo)->codigo, (yyvsp[0].nodo)->codigo);
	  (yyval.nodo)->codigo = concatena_codigo((yyval.nodo)->codigo, cod_op_bin_aritmetica((yyvsp[-2].nodo)->temp, (yyvsp[0].nodo)->temp, (yyval.nodo)->temp, '-'));  
	  }
#line 2536 "parser.tab.c"
    break;

  case 92: /* expressao_aritmetica: operandos_aritmeticos '^' operandos_aritmeticos  */
#line 694 "parser.y"
        { verifica_tipos((yyvsp[-2].nodo)->tipo_sem, numerico_sem, (yyvsp[-2].nodo)->valor_lexico->linha);
	  verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
	  (yyval.nodo) = cria_nodo_binario(((yyvsp[-1].valor_lexico)), (yyvsp[-2].nodo), (yyvsp[0].nodo));
	  (yyval.nodo)->tipo_sem = infere_tipo((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2545 "parser.tab.c"
    break;

  case 93: /* expressao_aritmetica: operandos_aritmeticos '*' operandos_aritmeticos  */
#line 699 "parser.y"
        { verifica_tipos((yyvsp[-2].nodo)->tipo_sem, numerico_sem, (yyvsp[-2].nodo)->valor_lexico->linha);
	  verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
	  (yyval.nodo) = cria_nodo_binario(((yyvsp[-1].valor_lexico)), (yyvsp[-2].nodo), (yyvsp[0].nodo));
	  (yyval.nodo)->tipo_sem = infere_tipo((yyvsp[-2].nodo), (yyvsp[0].nodo)); 
	  (yyval.nodo)->temp = novo_registrador();
	  (yyval.nodo)->codigo = concatena_codigo((yyvsp[-2].nodo)->codigo, (yyvsp[0].nodo)->codigo);
	  (yyval.nodo)->codigo = concatena_codigo((yyval.nodo)->codigo, cod_op_bin_aritmetica((yyvsp[-2].nodo)->temp, (yyvsp[0].nodo)->temp, (yyval.nodo)->temp, '*'));  
	  }
#line 2558 "parser.tab.c"
    break;

  case 94: /* expressao_aritmetica: operandos_aritmeticos '/' operandos_aritmeticos  */
#line 709 "parser.y"
        { verifica_tipos((yyvsp[-2].nodo)->tipo_sem, numerico_sem, (yyvsp[-2].nodo)->valor_lexico->linha);
	  verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
	  (yyval.nodo) = cria_nodo_binario(((yyvsp[-1].valor_lexico)), (yyvsp[-2].nodo), (yyvsp[0].nodo));
	  (yyval.nodo)->tipo_sem = infere_tipo((yyvsp[-2].nodo), (yyvsp[0].nodo)); 
	  (yyval.nodo)->temp = novo_registrador();
	  (yyval.nodo)->codigo = concatena_codigo((yyvsp[-2].nodo)->codigo, (yyvsp[0].nodo)->codigo);
	  (yyval.nodo)->codigo = concatena_codigo((yyval.nodo)->codigo, cod_op_bin_aritmetica((yyvsp[-2].nodo)->temp, (yyvsp[0].nodo)->temp, (yyval.nodo)->temp, '/')); 
	  }
#line 2571 "parser.tab.c"
    break;

  case 95: /* expressao_aritmetica: operandos_aritmeticos '%' operandos_aritmeticos  */
#line 719 "parser.y"
        { verifica_tipos((yyvsp[-2].nodo)->tipo_sem, numerico_sem, (yyvsp[-2].nodo)->valor_lexico->linha);
	  verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
	  (yyval.nodo) = cria_nodo_binario(((yyvsp[-1].valor_lexico)), (yyvsp[-2].nodo), (yyvsp[0].nodo));
	  (yyval.nodo)->tipo_sem = infere_tipo((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2580 "parser.tab.c"
    break;

  case 96: /* expressao_aritmetica: operandos_aritmeticos '&' operandos_aritmeticos  */
#line 725 "parser.y"
        { verifica_tipos((yyvsp[-2].nodo)->tipo_sem, numerico_sem, (yyvsp[-2].nodo)->valor_lexico->linha);
	  verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
	  (yyval.nodo) = cria_nodo_binario(((yyvsp[-1].valor_lexico)), (yyvsp[-2].nodo), (yyvsp[0].nodo));
	  (yyval.nodo)->tipo_sem = infere_tipo((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2589 "parser.tab.c"
    break;

  case 97: /* expressao_aritmetica: operandos_aritmeticos '|' operandos_aritmeticos  */
#line 731 "parser.y"
        { verifica_tipos((yyvsp[-2].nodo)->tipo_sem, numerico_sem, (yyvsp[-2].nodo)->valor_lexico->linha);
	  verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
	  (yyval.nodo) = cria_nodo_binario(((yyvsp[-1].valor_lexico)), (yyvsp[-2].nodo), (yyvsp[0].nodo));
	  (yyval.nodo)->tipo_sem = infere_tipo((yyvsp[-2].nodo), (yyvsp[0].nodo)); }
#line 2598 "parser.tab.c"
    break;

  case 98: /* literal_booleano: TK_LIT_TRUE  */
#line 737 "parser.y"
        { (yyval.nodo) = cria_nodo(literal, ((yyvsp[0].valor_lexico)));
	  (yyval.nodo)->tipo_sem = bool_sem;
	  (yyval.nodo)->codigo = cod_op_bin_lit('t');
	    }
#line 2607 "parser.tab.c"
    break;

  case 99: /* literal_booleano: TK_LIT_FALSE  */
#line 742 "parser.y"
        { (yyval.nodo) = cria_nodo(literal, ((yyvsp[0].valor_lexico))); 
	  (yyval.nodo)->tipo_sem = bool_sem;
	  (yyval.nodo)->codigo = cod_op_bin_lit('f');
	    }
#line 2616 "parser.tab.c"
    break;

  case 100: /* operandos_booleanos: TK_IDENTIFICADOR acesso_vetor  */
#line 748 "parser.y"
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
#line 2632 "parser.tab.c"
    break;

  case 101: /* operandos_booleanos: literal_booleano  */
#line 759 "parser.y"
                           {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2638 "parser.tab.c"
    break;

  case 102: /* operandos_booleanos: expressao_booleana  */
#line 760 "parser.y"
                             {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2644 "parser.tab.c"
    break;

  case 103: /* operandos_booleanos: '(' expressao_booleana ')'  */
#line 761 "parser.y"
                                     {(yyval.nodo) = (yyvsp[-1].nodo);}
#line 2650 "parser.tab.c"
    break;

  case 104: /* expressao_booleana: '!' operandos_booleanos  */
#line 765 "parser.y"
                { verifica_tipos((yyvsp[0].nodo)->tipo_sem, bool_sem, (yyvsp[0].nodo)->valor_lexico->linha); 
		  (yyval.nodo) = cria_nodo_unario((yyvsp[-1].valor_lexico), (yyvsp[0].nodo));
		  (yyval.nodo)->tipo_sem = bool_sem; }
#line 2658 "parser.tab.c"
    break;

  case 105: /* expressao_booleana: '?' operandos_booleanos  */
#line 769 "parser.y"
                { verifica_tipos((yyvsp[0].nodo)->tipo_sem, bool_sem, (yyvsp[0].nodo)->valor_lexico->linha); 
		  (yyval.nodo) = cria_nodo_unario((yyvsp[-1].valor_lexico), (yyvsp[0].nodo)); 
		  (yyval.nodo)->tipo_sem = bool_sem; }
#line 2666 "parser.tab.c"
    break;

  case 106: /* expressao_booleana: operandos_aritmeticos '<' operandos_aritmeticos  */
#line 774 "parser.y"
                { verifica_tipos((yyvsp[-2].nodo)->tipo_sem, numerico_sem, (yyvsp[-2].nodo)->valor_lexico->linha);
		  verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
		  (yyval.nodo) = cria_nodo_binario((yyvsp[-1].valor_lexico), (yyvsp[-2].nodo), (yyvsp[0].nodo));
		  adiciona_comentario(strdup("EXPR_ARIT_START"), (yyvsp[-2].nodo)->codigo); 
		  adiciona_comentario_fim(strdup("EXPR_ARIT_END"), (yyvsp[-2].nodo)->codigo); 
		  adiciona_comentario(strdup("EXPR_ARIT_START"), (yyvsp[0].nodo)->codigo); 
		  adiciona_comentario_fim(strdup("EXPR_ARIT_END"), (yyvsp[0].nodo)->codigo); 
		  (yyval.nodo)->temp = novo_registrador();
		  (yyval.nodo)->codigo = concatena_codigo((yyvsp[-2].nodo)->codigo, (yyvsp[0].nodo)->codigo);
		  code_t *op_rel = cod_op_rel_logica((yyvsp[-2].nodo)->temp, (yyvsp[0].nodo)->temp, (yyval.nodo)->temp, 1);
		  (yyval.nodo)->codigo = concatena_codigo((yyval.nodo)->codigo, op_rel);
		  (yyval.nodo)->codigo->tl = op_rel->tl;
		  (yyval.nodo)->codigo->fl = op_rel->fl;
		  
		  (yyval.nodo)->tipo_sem = bool_sem; }
#line 2686 "parser.tab.c"
    break;

  case 107: /* expressao_booleana: operandos_aritmeticos '>' operandos_aritmeticos  */
#line 790 "parser.y"
                { verifica_tipos((yyvsp[-2].nodo)->tipo_sem, numerico_sem, (yyvsp[-2].nodo)->valor_lexico->linha);
		  verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
		  (yyval.nodo) = cria_nodo_binario((yyvsp[-1].valor_lexico), (yyvsp[-2].nodo), (yyvsp[0].nodo));
		  adiciona_comentario(strdup("EXPR_ARIT_START"), (yyvsp[-2].nodo)->codigo); 
		  adiciona_comentario_fim(strdup("EXPR_ARIT_END"), (yyvsp[-2].nodo)->codigo); 
		  adiciona_comentario(strdup("EXPR_ARIT_START"), (yyvsp[0].nodo)->codigo); 
		  adiciona_comentario_fim(strdup("EXPR_ARIT_END"), (yyvsp[0].nodo)->codigo); 
		  (yyval.nodo)->temp = novo_registrador();
		  (yyval.nodo)->codigo = concatena_codigo((yyvsp[-2].nodo)->codigo, (yyvsp[0].nodo)->codigo);
		  code_t *op_rel = cod_op_rel_logica((yyvsp[-2].nodo)->temp, (yyvsp[0].nodo)->temp, (yyval.nodo)->temp, 3);
		  (yyval.nodo)->codigo = concatena_codigo((yyval.nodo)->codigo, op_rel);
		  (yyval.nodo)->codigo->tl = op_rel->tl;
		  (yyval.nodo)->codigo->fl = op_rel->fl; 
		  (yyval.nodo)->tipo_sem = bool_sem; }
#line 2705 "parser.tab.c"
    break;

  case 108: /* expressao_booleana: operandos_aritmeticos TK_OC_EQ operandos_aritmeticos  */
#line 805 "parser.y"
                { verifica_tipos((yyvsp[-2].nodo)->tipo_sem, numerico_sem, (yyvsp[-2].nodo)->valor_lexico->linha);
		  verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
		  (yyval.nodo) = cria_nodo_binario((yyvsp[-1].valor_lexico), (yyvsp[-2].nodo), (yyvsp[0].nodo)); 
		  adiciona_comentario(strdup("EXPR_ARIT_START"), (yyvsp[-2].nodo)->codigo); 
		  adiciona_comentario_fim(strdup("EXPR_ARIT_END"), (yyvsp[-2].nodo)->codigo); 
		  adiciona_comentario(strdup("EXPR_ARIT_START"), (yyvsp[0].nodo)->codigo); 
		  adiciona_comentario_fim(strdup("EXPR_ARIT_END"), (yyvsp[0].nodo)->codigo); 
		  (yyval.nodo)->temp = novo_registrador();
		  (yyval.nodo)->codigo = concatena_codigo((yyvsp[-2].nodo)->codigo, (yyvsp[0].nodo)->codigo);
		  code_t *op_rel = cod_op_rel_logica((yyvsp[-2].nodo)->temp, (yyvsp[0].nodo)->temp, (yyval.nodo)->temp, 5);
		  (yyval.nodo)->codigo = concatena_codigo((yyval.nodo)->codigo, op_rel);
		  (yyval.nodo)->codigo->tl = op_rel->tl;
		  (yyval.nodo)->codigo->fl = op_rel->fl;
		  (yyval.nodo)->tipo_sem = bool_sem; }
#line 2724 "parser.tab.c"
    break;

  case 109: /* expressao_booleana: operandos_aritmeticos TK_OC_NE operandos_aritmeticos  */
#line 820 "parser.y"
                { verifica_tipos((yyvsp[-2].nodo)->tipo_sem, numerico_sem, (yyvsp[-2].nodo)->valor_lexico->linha);
		  verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
		  (yyval.nodo) = cria_nodo_binario((yyvsp[-1].valor_lexico), (yyvsp[-2].nodo), (yyvsp[0].nodo)); 
		  adiciona_comentario(strdup("EXPR_ARIT_START"), (yyvsp[-2].nodo)->codigo); 
		  adiciona_comentario_fim(strdup("EXPR_ARIT_END"), (yyvsp[-2].nodo)->codigo); 
		  adiciona_comentario(strdup("EXPR_ARIT_START"), (yyvsp[0].nodo)->codigo); 
		  adiciona_comentario_fim(strdup("EXPR_ARIT_END"), (yyvsp[0].nodo)->codigo); 
		  (yyval.nodo)->temp = novo_registrador();
		  (yyval.nodo)->codigo = concatena_codigo((yyvsp[-2].nodo)->codigo, (yyvsp[0].nodo)->codigo);
		  code_t *op_rel = cod_op_rel_logica((yyvsp[-2].nodo)->temp, (yyvsp[0].nodo)->temp, (yyval.nodo)->temp, 6);
		  (yyval.nodo)->codigo = concatena_codigo((yyval.nodo)->codigo, op_rel);
		  (yyval.nodo)->codigo->tl = op_rel->tl;
		  (yyval.nodo)->codigo->fl = op_rel->fl;
		  (yyval.nodo)->tipo_sem = bool_sem; }
#line 2743 "parser.tab.c"
    break;

  case 110: /* expressao_booleana: operandos_aritmeticos TK_OC_GE operandos_aritmeticos  */
#line 835 "parser.y"
                { verifica_tipos((yyvsp[-2].nodo)->tipo_sem, numerico_sem, (yyvsp[-2].nodo)->valor_lexico->linha);
		  verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
		  (yyval.nodo) = cria_nodo_binario((yyvsp[-1].valor_lexico), (yyvsp[-2].nodo), (yyvsp[0].nodo)); 
		  adiciona_comentario(strdup("EXPR_ARIT_START"), (yyvsp[-2].nodo)->codigo); 
		  adiciona_comentario_fim(strdup("EXPR_ARIT_END"), (yyvsp[-2].nodo)->codigo); 
		  adiciona_comentario(strdup("EXPR_ARIT_START"), (yyvsp[0].nodo)->codigo); 
		  adiciona_comentario_fim(strdup("EXPR_ARIT_END"), (yyvsp[0].nodo)->codigo); 
		  (yyval.nodo)->temp = novo_registrador();
		  (yyval.nodo)->codigo = concatena_codigo((yyvsp[-2].nodo)->codigo, (yyvsp[0].nodo)->codigo);
		  code_t *op_rel = cod_op_rel_logica((yyvsp[-2].nodo)->temp, (yyvsp[0].nodo)->temp, (yyval.nodo)->temp, 4);
		  (yyval.nodo)->codigo = concatena_codigo((yyval.nodo)->codigo, op_rel);
		  (yyval.nodo)->codigo->tl = op_rel->tl;
		  (yyval.nodo)->codigo->fl = op_rel->fl;
		  (yyval.nodo)->tipo_sem = bool_sem; }
#line 2762 "parser.tab.c"
    break;

  case 111: /* expressao_booleana: operandos_aritmeticos TK_OC_LE operandos_aritmeticos  */
#line 850 "parser.y"
                { verifica_tipos((yyvsp[-2].nodo)->tipo_sem, numerico_sem, (yyvsp[-2].nodo)->valor_lexico->linha);
		  verifica_tipos((yyvsp[0].nodo)->tipo_sem, numerico_sem, (yyvsp[0].nodo)->valor_lexico->linha);
		  (yyval.nodo) = cria_nodo_binario((yyvsp[-1].valor_lexico), (yyvsp[-2].nodo), (yyvsp[0].nodo)); 
		  adiciona_comentario(strdup("EXPR_ARIT_START"), (yyvsp[-2].nodo)->codigo); 
		  adiciona_comentario_fim(strdup("EXPR_ARIT_END"), (yyvsp[-2].nodo)->codigo); 
		  adiciona_comentario(strdup("EXPR_ARIT_START"), (yyvsp[0].nodo)->codigo); 
		  adiciona_comentario_fim(strdup("EXPR_ARIT_END"), (yyvsp[0].nodo)->codigo); 
		  (yyval.nodo)->temp = novo_registrador();
		  (yyval.nodo)->codigo = concatena_codigo((yyvsp[-2].nodo)->codigo, (yyvsp[0].nodo)->codigo);
		  code_t *op_rel = cod_op_rel_logica((yyvsp[-2].nodo)->temp, (yyvsp[0].nodo)->temp, (yyval.nodo)->temp, 2);
		  (yyval.nodo)->codigo = concatena_codigo((yyval.nodo)->codigo, op_rel);
		  (yyval.nodo)->codigo->tl = op_rel->tl;
		  (yyval.nodo)->codigo->fl = op_rel->fl;
		  (yyval.nodo)->tipo_sem = bool_sem; }
#line 2781 "parser.tab.c"
    break;

  case 112: /* expressao_booleana: operandos_booleanos TK_OC_AND operandos_booleanos  */
#line 866 "parser.y"
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
#line 2797 "parser.tab.c"
    break;

  case 113: /* expressao_booleana: operandos_booleanos TK_OC_OR operandos_booleanos  */
#line 878 "parser.y"
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
#line 2813 "parser.tab.c"
    break;

  case 114: /* expressao: TK_IDENTIFICADOR acesso_vetor  */
#line 891 "parser.y"
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
#line 2829 "parser.tab.c"
    break;

  case 115: /* expressao: chamada_de_funcao  */
#line 902 "parser.y"
                                        {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2835 "parser.tab.c"
    break;

  case 116: /* expressao: literal_numerico  */
#line 903 "parser.y"
                                        {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2841 "parser.tab.c"
    break;

  case 117: /* expressao: expressao_aritmetica  */
#line 905 "parser.y"
        {
		(yyval.nodo) = (yyvsp[0].nodo);
	 	adiciona_comentario(strdup("EXPR_ARIT_START"), (yyval.nodo)->codigo);
	 	adiciona_comentario_fim(strdup("EXPR_ARIT_END"), (yyval.nodo)->codigo);
	}
#line 2851 "parser.tab.c"
    break;

  case 118: /* expressao: expressao_booleana  */
#line 910 "parser.y"
                                                {(yyval.nodo) = (yyvsp[0].nodo);}
#line 2857 "parser.tab.c"
    break;

  case 119: /* expressao: expressao '?' expressao ':' expressao  */
#line 912 "parser.y"
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
#line 2873 "parser.tab.c"
    break;


#line 2877 "parser.tab.c"

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  yyerror (YY_("memory exhausted"));
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
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 924 "parser.y"

void yyerror(char const *s)
{
    printf ("line %d: %s\n", get_line_number(), s);
}

