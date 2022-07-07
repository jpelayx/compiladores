%{
#include <stdio.h>

int yylex(void);
void yyerror (char const *s);
int get_line_number();
%}

%define parse.error verbose

%token TK_PR_INT
%token TK_PR_FLOAT
%token TK_PR_BOOL
%token TK_PR_CHAR
%token TK_PR_STRING
%token TK_PR_IF
%token TK_PR_THEN
%token TK_PR_ELSE
%token TK_PR_WHILE
%token TK_PR_DO
%token TK_PR_INPUT
%token TK_PR_OUTPUT
%token TK_PR_RETURN
%token TK_PR_CONST
%token TK_PR_STATIC
%token TK_PR_FOREACH
%token TK_PR_FOR
%token TK_PR_SWITCH
%token TK_PR_CASE
%token TK_PR_BREAK
%token TK_PR_CONTINUE
%token TK_PR_CLASS
%token TK_PR_PRIVATE
%token TK_PR_PUBLIC
%token TK_PR_PROTECTED
%token TK_PR_END
%token TK_PR_DEFAULT
%token TK_OC_LE
%token TK_OC_GE
%token TK_OC_EQ
%token TK_OC_NE
%token TK_OC_AND
%token TK_OC_OR
%token TK_OC_SL
%token TK_OC_SR
%token TK_LIT_INT
%token TK_LIT_FLOAT
%token TK_LIT_FALSE
%token TK_LIT_TRUE
%token TK_LIT_CHAR
%token TK_LIT_STRING
%token TK_IDENTIFICADOR
%token TOKEN_ERRO

%%

programa: programa var_global | programa funcao | ;

tipo: TK_PR_INT | TK_PR_FLOAT | TK_PR_CHAR | TK_PR_BOOL | TK_PR_STRING;
estatico: TK_PR_STATIC | ;
constante: TK_PR_CONST | ;
vetor: '[' TK_LIT_INT ']' |; /* falta garantir que positivo */

var_global: estatico tipo TK_IDENTIFICADOR vetor lista_identificadores_g ';' ;
lista_identificadores_g: lista_identificadores_g ',' TK_IDENTIFICADOR vetor | ;

funcao: cabecalho bloco_cmd;

cabecalho: estatico tipo TK_IDENTIFICADOR '(' lista_parametros ')' ;
lista_parametros: constante tipo TK_IDENTIFICADOR mais_parametros | ;
mais_parametros: ',' constante tipo TK_IDENTIFICADOR mais_parametros | ;

bloco_cmd: '{' lista_comandos '}';
lista_comandos: lista_comandos comando | ;
comando: bloco_cmd | declaracao_variavel ';' | atribuicao ';'| chamada_de_funcao ';'| shift ';'| retorno ';'| 
         TK_PR_BREAK ';'| TK_PR_CONTINUE ';' | controle_fluxo; /* etc....*/

	/* Comandos simples */

declaracao_variavel: estatico constante tipo TK_IDENTIFICADOR inicializa_variavel lista_identificadores_l;
valores_inicializa_variavel: TK_LIT_TRUE | TK_LIT_FALSE | TK_LIT_INT | TK_LIT_FLOAT | TK_LIT_STRING | TK_LIT_CHAR | TK_IDENTIFICADOR;
inicializa_variavel: TK_OC_LE valores_inicializa_variavel | ; 
lista_identificadores_l: lista_identificadores_l ',' TK_IDENTIFICADOR inicializa_variavel | ;

acesso_vetor: '[' expressao ']' |;

atribuicao: TK_IDENTIFICADOR acesso_vetor '=' expressao;

parametro_chamada_funcao: expressao mais_parametros_chamada_funcao | ;
mais_parametros_chamada_funcao: ',' expressao mais_parametros_chamada_funcao | ;
chamada_de_funcao: TK_IDENTIFICADOR '(' parametro_chamada_funcao ')';

shift: TK_IDENTIFICADOR acesso_vetor token_shift TK_LIT_INT;
token_shift: TK_OC_SL | TK_OC_SR ;

retorno: TK_PR_RETURN expressao;

controle_fluxo: if | for | while;

if: TK_PR_IF '(' expressao ')' bloco_cmd else; /* com ambiguidade */
else: TK_PR_ELSE bloco_cmd;

for: TK_PR_FOR '(' atribuicao ':' expressao ':' atribuicao ')' bloco_cmd;

while: TK_PR_WHILE '(' expressao ')' TK_PR_DO bloco_cmd;

  /* Expressoes */

/* Obs: A precedencia dos operadores foi baseada na precedencia em C.

TODO: 
- associatividade do &, * e  #
- expressoes bitwise??? valem para expressoes booleanas e aritimeticas? 
  concertar precedencia do | e & quando uma expressao aritmetica é chamada em uma 
  expressao booleana via operador comparativo. */

operandos_aritmeticos: TK_IDENTIFICADOR acesso_vetor | TK_LIT_FLOAT | TK_LIT_INT | chamada_de_funcao;
operandos_booleanos: TK_IDENTIFICADOR acesso_vetor | TK_LIT_TRUE | TK_LIT_FALSE | chamada_de_funcao;

expressao: ternario | expr_aritmetica | expr_booleana ;
ternario: expressao '?' expressao ':' expressao ;

/* nomeacao: 
  - opa1, ..., opan: opan: operadores aritmeticos com precedencia 1 
                     opa1: operadores aritmeticos com precedencia n ...
  - a1, ..., an: expressoes aritmeticas em diferentes niveis para 
                 implementar associatividade */
expr_aritmetica: expr_aritmetica opa1 a1 | a1;
opa1: '|';                   /* bitwise or */
a1: a1 opa2 a2 | a2;
opa2: '&';                          /* bitwise and */
a2: a2 opa3 a3 | a3;
opa3: '+' | '-';                    /* soma, subtracao */
a3: a3 opa4 a4 | a4;
opa4: '%' | '*' | '/';              /* resto,  multiplicao e divisao */
a4: a4 opa5 a5 | a5;
opa5: '^';                          /* exponenciacao */
a5: opa6 a5 | a5 opa6_dir | a6 ;
opa6: '+' | '-' | '&' | '#';        /* + unario, - unario, #, endereco de variavel */
opa6_dir: '*';                      /* conteudo de endereco */  
a6: '(' expr_aritmetica ')' | operandos_aritmeticos;

/* nomeacao: 
  - opb1, ..., opbn: opbn: operadores booleanos com precedencia 1 
                     opb1: operadores booleanos com precedencia n ...
  - b1, ..., bn: expressoes booleanas em diferentes niveis para 
                 implementar associatividade */
expr_booleana: expr_booleana opb1 b1 | b1;
opb1: TK_OC_OR;                        /* || */
b1: b1 opb2 b2 | b2;
opb2: TK_OC_AND;                       /* && */
b2: b2 opb3 b3 | b3;
opb3: '|';                             /* bitwise or */ 
b3: b3 opb4 b4_oc | b3 opb4 b4 | b4_oc | b4; /* separando em ops comparativas (b4_oc) e demais ops */
opb4: '&';                             /* bitwise and */
b4_oc: b4_oc opb5_oc expr_aritmetica | b5_oc;
opb5_oc: TK_OC_EQ | TK_OC_NE;          /* ==, != */
b5_oc: b5_oc opb6 expr_aritmetica | expr_aritmetica;
opb6: TK_OC_GE | '>' | TK_OC_LE | '<'; /* >=, >, <=, < */
b4: opb5 b4 | b4 opb5_dir | b5
opb5: '!' | '#' | '&';                 /* negacao, endereco de variavel, # */
opb5_dir: '*';                         /* conteudo de endereco */
b5: '(' expr_booleana ')' | operandos_booleanos

%%

void yyerror(char const *s)
{
    printf ("line %d: %s\n", get_line_number(), s);
}
