/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

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
#line 27 "parser.y"
 #include "ast.h" 
#line 28 "parser.y"
 #include "valor_token.h" 
#line 29 "parser.y"
 #include "tabela_simbolos.h" 
#line 30 "parser.y"
 #include "escopo.h" 
#line 31 "parser.y"
 #include "instr.h" 

#line 60 "parser.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TK_PR_INT = 258,               /* TK_PR_INT  */
    TK_PR_FLOAT = 259,             /* TK_PR_FLOAT  */
    TK_PR_BOOL = 260,              /* TK_PR_BOOL  */
    TK_PR_CHAR = 261,              /* TK_PR_CHAR  */
    TK_PR_STRING = 262,            /* TK_PR_STRING  */
    TK_PR_IF = 263,                /* TK_PR_IF  */
    TK_PR_THEN = 264,              /* TK_PR_THEN  */
    TK_PR_ELSE = 265,              /* TK_PR_ELSE  */
    TK_PR_WHILE = 266,             /* TK_PR_WHILE  */
    TK_PR_DO = 267,                /* TK_PR_DO  */
    TK_PR_INPUT = 268,             /* TK_PR_INPUT  */
    TK_PR_OUTPUT = 269,            /* TK_PR_OUTPUT  */
    TK_PR_RETURN = 270,            /* TK_PR_RETURN  */
    TK_PR_CONST = 271,             /* TK_PR_CONST  */
    TK_PR_STATIC = 272,            /* TK_PR_STATIC  */
    TK_PR_FOREACH = 273,           /* TK_PR_FOREACH  */
    TK_PR_FOR = 274,               /* TK_PR_FOR  */
    TK_PR_SWITCH = 275,            /* TK_PR_SWITCH  */
    TK_PR_CASE = 276,              /* TK_PR_CASE  */
    TK_PR_BREAK = 277,             /* TK_PR_BREAK  */
    TK_PR_CONTINUE = 278,          /* TK_PR_CONTINUE  */
    TK_PR_CLASS = 279,             /* TK_PR_CLASS  */
    TK_PR_PRIVATE = 280,           /* TK_PR_PRIVATE  */
    TK_PR_PUBLIC = 281,            /* TK_PR_PUBLIC  */
    TK_PR_PROTECTED = 282,         /* TK_PR_PROTECTED  */
    TK_PR_END = 283,               /* TK_PR_END  */
    TK_PR_DEFAULT = 284,           /* TK_PR_DEFAULT  */
    TK_OC_LE = 285,                /* TK_OC_LE  */
    TK_OC_GE = 286,                /* TK_OC_GE  */
    TK_OC_EQ = 287,                /* TK_OC_EQ  */
    TK_OC_NE = 288,                /* TK_OC_NE  */
    TK_OC_AND = 289,               /* TK_OC_AND  */
    TK_OC_OR = 290,                /* TK_OC_OR  */
    TK_OC_SL = 291,                /* TK_OC_SL  */
    TK_OC_SR = 292,                /* TK_OC_SR  */
    TK_LIT_INT = 293,              /* TK_LIT_INT  */
    TK_LIT_FLOAT = 294,            /* TK_LIT_FLOAT  */
    TK_LIT_FALSE = 295,            /* TK_LIT_FALSE  */
    TK_LIT_TRUE = 296,             /* TK_LIT_TRUE  */
    TK_LIT_CHAR = 297,             /* TK_LIT_CHAR  */
    TK_LIT_STRING = 298,           /* TK_LIT_STRING  */
    TK_IDENTIFICADOR = 299,        /* TK_IDENTIFICADOR  */
    TOKEN_ERRO = 300,              /* TOKEN_ERRO  */
    avaliacao_logica = 303,        /* avaliacao_logica  */
    endereco_variavel = 304,       /* endereco_variavel  */
    valor_ponteiro = 305,          /* valor_ponteiro  */
    inverte_sinal = 306            /* inverte_sinal  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 33 "parser.y"

	valor_token_t *valor_lexico;
	ast_t *nodo;
	tipos_semanticos_t tipo;

#line 132 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
