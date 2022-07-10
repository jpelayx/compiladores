%{
#include <stdio.h>

int yylex(void);
void yyerror (char const *s);
int get_line_number();
%}

%define parse.error detailed

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



/* nomeacao: 
  - op1, ..., opn: opn: operadores aritmeticos com precedencia 1 
                   op1: operadores aritmeticos com precedencia n ...
  - e1, ..., en: expressoes aritmeticas em diferentes niveis para 
                 implementar associatividade */

expressao: e1;
e1: e1 '?' e1 ':' e1 | e2;
e2: e2 '?' | e3;
e3: e3 TK_OC_OR e4 | e4; 
e4: e4 TK_OC_AND e5 | e5;
e5: e5 '|' e6 | e6;
e6: e6 '&' e7 | e7;
e7: e7 op7 e8 | e8;
op7: TK_OC_EQ
   | TK_OC_NE;
e8: e8 op8 e9 | e9;
op8: TK_OC_GE
   | TK_OC_LE
   | '>'
   | '<';
e9: e9 op9 e10 | e10;
op9: '+'
   | '-';
e10: e10 op10 e11 | e11;
op10: '*'
    | '/'
    | '%';
e11: e11 '^' e10 | e10;
e12: op12 e12 | operador;
op12: '*'
    | '&'
	| '#'
	| '+'
	| '-'
	| '!';
operador: '(' expressao ')' 
        | TK_IDENTIFICADOR acesso_vetor
    	| chamada_de_funcao
        | TK_LIT_FLOAT
    	| TK_LIT_INT
        | TK_LIT_TRUE 
		| TK_LIT_FALSE;

%%

void yyerror(char const *s)
{
    printf ("line %d: %s\n", get_line_number(), s);
}
