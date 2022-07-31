%{
#include <stdio.h>
#include <stdbool.h>
#include "ast.h"
#include "valor_token.h"

int yylex(void);
void yyerror (char const *s);
int get_line_number();


extern void *arvore;
%}

%code requires { #include "ast.h" }
%code requires { #include "valor_token.h" }

%union {
	valor_token_t valor_lexico;
	ast_t *nodo;
}

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
%token<valor_lexico> TK_OC_LE
%token<valor_lexico> TK_OC_GE
%token<valor_lexico> TK_OC_EQ
%token<valor_lexico> TK_OC_NE
%token<valor_lexico> TK_OC_AND
%token<valor_lexico> TK_OC_OR
%token<valor_lexico> TK_OC_SL
%token<valor_lexico> TK_OC_SR
%token<valor_lexico> TK_LIT_INT
%token<valor_lexico> TK_LIT_FLOAT
%token<valor_lexico> TK_LIT_FALSE
%token<valor_lexico> TK_LIT_TRUE
%token<valor_lexico> TK_LIT_CHAR
%token<valor_lexico> TK_LIT_STRING
%token<valor_lexico> TK_IDENTIFICADOR
%token TOKEN_ERRO

//Caracteres especiais também tem valor léxico
%token<valor_lexico> ','
%token<valor_lexico> ';'
%token<valor_lexico> ':'
%token<valor_lexico> '('
%token<valor_lexico> ')'
%token<valor_lexico> '['
%token<valor_lexico> ']'
%token<valor_lexico> '{'
%token<valor_lexico> '}'
%token<valor_lexico> '+'
%token<valor_lexico> '-'
%token<valor_lexico> '*'
%token<valor_lexico> '/'
%token<valor_lexico> '<'
%token<valor_lexico> '>'
%token<valor_lexico> '='
%token<valor_lexico> '!'
%token<valor_lexico> '&'
%token<valor_lexico> '%'
%token<valor_lexico> '#'
%token<valor_lexico> '^'
%token<valor_lexico> '.'
%token<valor_lexico> '$'
%token<valor_lexico> '?'

%type<nodo> programa 
%type<nodo> var_global
%type<nodo> funcao
%type<nodo> cabecalho
%type<nodo> bloco_cmd
%type<nodo> lista_comandos
%type<nodo> comando
%type<nodo> atribuicao
%type<nodo> expressao
%type<nodo> operador_atribuicao
%type<nodo> declaracao_variavel
%type<nodo> lista_identificadores_l
%type<nodo> inicializa_variavel
%type<nodo> identificador_ou_literal
%type<nodo> literal



%precedence "ternario"
%precedence "unario"

%left '?' 
%left ':'
%left avaliacao_logica
%left '<' '>' TK_OC_LE TK_OC_GE TK_OC_EQ TK_OC_NE
%left TK_OC_OR
%left TK_OC_AND
%left '&' '|'
%left '+' '-'
%left '*' '/' '%'
%left '^'
%right '#'
%right endereco_variavel valor_ponteiro
%left '!'
%left inverte_sinal

%%

programa: programa var_global	{$$ = $1;} // var_global não tem inicializacao.
	| programa funcao 	{arvore = $2; insere_filhos($2, $1, NULL, NULL, NULL);} //resto do programa é filho da funcao
	| 			{$$ = NULL;}
	;

tipo: TK_PR_INT | TK_PR_FLOAT | TK_PR_CHAR | TK_PR_BOOL | TK_PR_STRING;
estatico: TK_PR_STATIC | ;
constante: TK_PR_CONST | ;
vetor: '[' TK_LIT_INT ']' | ; /* falta garantir que positivo */

var_global: estatico tipo TK_IDENTIFICADOR vetor lista_identificadores_g ';' {$$ = NULL;};
lista_identificadores_g: lista_identificadores_g ',' TK_IDENTIFICADOR vetor | ;

//Bloco de comandos é filho de um identificador que tá no cabecalho!
funcao: cabecalho bloco_cmd 		{$$ = insere_filhos($1, $2, NULL, NULL, NULL);}

cabecalho: estatico tipo TK_IDENTIFICADOR '(' parametros ')' 	{$$ = cria_nodo(&$3, lista_funcao);} 
parametros: constante tipo TK_IDENTIFICADOR lista_parametros | ;
lista_parametros: lista_parametros ',' constante tipo TK_IDENTIFICADOR | ;

bloco_cmd: '{' lista_comandos '}' 	{$$ = $2;}
lista_comandos: lista_comandos comando 	{$$ = insere_filhos($2, $1, NULL, NULL, NULL);} // o filho do comando é a lista de comandos
		| 				{$$ = NULL;}
comando: 
	bloco_cmd ';' 				{$$ = NULL;}
	| declaracao_variavel ';' 		{$$ = $1;}
	| atribuicao ';' 			{$$ = $1;}
	| chamada_de_funcao ';' 		{$$ = NULL;}
	| shift ';' 				{$$ = NULL;}
	| retorno ';' 				{$$ = NULL;}
	| TK_PR_BREAK ';' 			{$$ = NULL;}
	| TK_PR_CONTINUE ';' 			{$$ = NULL;}
	| entrada ';' 				{$$ = NULL;}
	| saida ';' 				{$$ = NULL;}
	| controle_fluxo ';' 			{$$ = NULL;}
	; 

	/* Comandos simples */

declaracao_variavel: estatico constante tipo inicializa_variavel lista_identificadores_l {$$ = insere_filhos($4, $5, NULL, NULL, NULL);}
lista_identificadores_l: lista_identificadores_l ','  inicializa_variavel 	{$$ = insere_filhos($3, $1, NULL, NULL, NULL);}
	| 									{$$ = NULL;}
inicializa_variavel: 
	TK_IDENTIFICADOR 					{$$ = NULL;} //ignora declaracao de variavel sem inicialização
	| TK_IDENTIFICADOR TK_OC_LE identificador_ou_literal	{$$ = insere_filhos(cria_nodo(&$2, inicializacao), cria_nodo(&$1, id), $3, NULL, NULL);}
	
literal: TK_LIT_TRUE 		{$$ = cria_nodo(&$1, placeholder_literal);}
	|TK_LIT_FALSE 		{$$ = cria_nodo(&$1, placeholder_literal);}
	|TK_LIT_INT 		{$$ = cria_nodo(&$1, placeholder_literal);}
	|TK_LIT_FLOAT 		{$$ = cria_nodo(&$1, placeholder_literal);}
	|TK_LIT_STRING 	{$$ = cria_nodo(&$1, placeholder_literal);}
	|TK_LIT_CHAR 		{$$ = cria_nodo(&$1, placeholder_literal);}

identificador_ou_literal: 
	literal 		{$$ = $1;}
	|TK_IDENTIFICADOR 	{$$ = cria_nodo(&$1, id);}


acesso_vetor: '[' expressao ']' 
		|
		;
atribuicao: TK_IDENTIFICADOR acesso_vetor operador_atribuicao expressao {$$ = insere_filhos($3, cria_nodo(&$1, id), $4, NULL, NULL);}
operador_atribuicao: '=' 	{$$ = cria_nodo(&$1, atribuicao);}


entrada: TK_PR_INPUT TK_IDENTIFICADOR;
saida: TK_PR_OUTPUT identificador_ou_literal;

parametro_chamada_funcao: expressao mais_parametros_chamada_funcao | ;
mais_parametros_chamada_funcao: mais_parametros_chamada_funcao ',' expressao | ;
chamada_de_funcao: TK_IDENTIFICADOR '(' parametro_chamada_funcao ')';

shift: TK_IDENTIFICADOR acesso_vetor token_shift TK_LIT_INT;
token_shift: TK_OC_SL | TK_OC_SR ;

retorno: TK_PR_RETURN expressao ;

controle_fluxo: cf_if | cf_for | cf_while ;

cf_if: TK_PR_IF '(' expressao ')' bloco_cmd cf_else;
cf_else: TK_PR_ELSE bloco_cmd | ;

cf_for: TK_PR_FOR '(' atribuicao ':' expressao ':' atribuicao ')' bloco_cmd;

cf_while: TK_PR_WHILE '(' expressao ')' TK_PR_DO bloco_cmd;

  /* Expressoes */
literal_numerico: TK_LIT_INT | TK_LIT_FLOAT  
  
operandos_aritmeticos: 
	literal_numerico 
	| chamada_de_funcao 
	| TK_IDENTIFICADOR acesso_vetor
	| expressao_aritmetica
	| '(' expressao_aritmetica ')'
	
expressao_aritmetica: 
	'+' operandos_aritmeticos
	| '-' operandos_aritmeticos %prec inverte_sinal
	| '&' operandos_aritmeticos %prec endereco_variavel
	| '*' operandos_aritmeticos %prec valor_ponteiro
	| '#' operandos_aritmeticos
	| operandos_aritmeticos '+' operandos_aritmeticos
	| operandos_aritmeticos '-' operandos_aritmeticos
	| operandos_aritmeticos '^' operandos_aritmeticos
	| operandos_aritmeticos '*' operandos_aritmeticos
	| operandos_aritmeticos '/' operandos_aritmeticos
	| operandos_aritmeticos '%' operandos_aritmeticos
	//bitwise and
	| operandos_aritmeticos '&' operandos_aritmeticos
	//bitwise or
	| operandos_aritmeticos '|' operandos_aritmeticos
	
literal_booleano: TK_LIT_TRUE | TK_LIT_FALSE

operandos_booleanos: 
	TK_IDENTIFICADOR acesso_vetor
	| literal_booleano
	| expressao_booleana
	| '(' expressao_booleana ')'

expressao_booleana:
	'!' operandos_booleanos
	|'?' operandos_booleanos  %prec avaliacao_logica
	//comparadores logicos	
	| operandos_aritmeticos '<' operandos_aritmeticos
	| operandos_aritmeticos '>' operandos_aritmeticos
	| operandos_aritmeticos TK_OC_EQ operandos_aritmeticos
	| operandos_aritmeticos TK_OC_NE operandos_aritmeticos
	| operandos_aritmeticos TK_OC_GE operandos_aritmeticos
	| operandos_aritmeticos TK_OC_LE operandos_aritmeticos
	//operadores logicos	
	| operandos_booleanos TK_OC_AND operandos_booleanos
	| operandos_booleanos TK_OC_OR operandos_booleanos
	
expressao:
	TK_IDENTIFICADOR acesso_vetor			{$$ = NULL;}
	| chamada_de_funcao 				{$$ = NULL;}
	| literal_numerico				{$$ = NULL;}
	| expressao_aritmetica				{$$ = NULL;}
	| expressao_booleana				{$$ = NULL;}
	// ternario
	| expressao '?' expressao ':' expressao	{$$ = NULL;}
	
%%
void yyerror(char const *s)
{
    printf ("line %d: %s\n", get_line_number(), s);
}

