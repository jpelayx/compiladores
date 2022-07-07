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

var_global: estatico tipo TK_IDENTIFICADOR vetor lista_identificadores ';'
lista_identificadores: lista_identificadores ',' TK_IDENTIFICADOR | ;

funcao: cabecalho bloco_cmd;

cabecalho: estatico tipo vetor '(' lista_parametros ')'
lista_parametros: constante tipo TK_IDENTIFICADOR mais_parametros | ;
mais_parametros: ',' constante tipo TK_IDENTIFICADOR mais_parametros | ;

	/* Comandos simples */

valores_inicializa_variavel: TK_LIT_TRUE | TK_LIT_FALSE | TK_LIT_INT | TK_LIT_FLOAT | TK_LIT_STRING | TK_LIT_CHAR | TK_IDENTIFICADOR
inicializa_variavel: "<=" valores_inicializa_variavel ; 
declaracao_variavel: estatico constante tipo lista_identificadores inicializa_variavel;

atribuicao: TK_IDENTIFICADOR '=' expressao | TK_IDENTIFICADOR'['expressao']' '=' expressao

parametro_chamada_funcao: expressao mais_parametros_chamada_funcao | ;
mais_parametros_chamada_funcao: ',' expressao mais_parametros_chamada_funcao | ;
chamada_de_funcao: TK_IDENTIFICADOR '(' parametro_chamada_funcao ')';

return: TK_PR_RETURN expressao;
break: TK_PR_BREAK;
continue: TK_PR_CONTINUE;

expressao: TK_IDENTIFICADOR 
	 | TK_IDENTIFICADOR vetor 
	 | TK_LIT_INT 
	 | TK_LIT_FLOAT 
	 | chamada_de_funcao 
	 /*Unarios
	 | '+' expressao
	 | '-' expressao
	 | '!' expressao
	 | '&' expressao
	 | '*' expressao
	 | '?' expressao
	 | '#' expressao
	 */
	 /*Binarios*/
	 | expressao '+' expressao
	 | expressao '-' expressao
	 | expressao '*' expressao
	 | expressao '/' expressao
	 | expressao '%' expressao
	 | expressao '|' expressao
	 | expressao '&' expressao
	 | expressao '^' expressao
	 | expressao TK_OC_LE expressao
	 | expressao TK_OC_GE expressao
	 | expressao TK_OC_EQ expressao
	 | expressao TK_OC_NE expressao
	 | expressao '<' expressao
	 | expressao '>' expressao	 	 
	 | expressao TK_OC_AND expressao
	 | expressao TK_OC_OR expressao
	 /*Ternario*/
	 | expressao '?' expressao ':' expressao
	 
bloco_cmd: ;
	


%%

void yyerror(char const *s)
{
    printf ("line %d: %s\n", get_line_number(), s);
}
