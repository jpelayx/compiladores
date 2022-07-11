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

%left '?' ':'
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
comando: 
	bloco_cmd 
	| declaracao_variavel ';'
	| atribuicao ';'
	| chamada_de_funcao ';'
	| shift ';'
	| retorno ';'
	| TK_PR_BREAK ';'
	| TK_PR_CONTINUE ';' 
	| entrada ';'
	| saida ';'
	| controle_fluxo; 
	/* etc....*/

	/* Comandos simples */

declaracao_variavel: estatico constante tipo TK_IDENTIFICADOR inicializa_variavel lista_identificadores_l;
lista_identificadores_l: lista_identificadores_l ',' estatico constante tipo TK_IDENTIFICADOR inicializa_variavel | ;
inicializa_variavel: TK_OC_LE identificador_ou_literal | ; 
literal: TK_LIT_TRUE 
	|TK_LIT_FALSE
	|TK_LIT_INT
	|TK_LIT_FLOAT
	|TK_LIT_STRING
	|TK_LIT_CHAR;

identificador_ou_literal: 
	literal
	|TK_IDENTIFICADOR;


acesso_vetor: '[' expressao ']' | ;
atribuicao: TK_IDENTIFICADOR acesso_vetor '=' expressao;

entrada: TK_PR_INPUT TK_IDENTIFICADOR;
saida: TK_PR_OUTPUT identificador_ou_literal;

parametro_chamada_funcao: expressao mais_parametros_chamada_funcao | ;
mais_parametros_chamada_funcao: ',' expressao mais_parametros_chamada_funcao | ;
chamada_de_funcao: TK_IDENTIFICADOR '(' parametro_chamada_funcao ')';

shift: TK_IDENTIFICADOR acesso_vetor token_shift TK_LIT_INT;
token_shift: TK_OC_SL | TK_OC_SR ;

retorno: TK_PR_RETURN expressao;

controle_fluxo: if | for | while;

if: TK_PR_IF '(' expressao ')' bloco_cmd else;
else: TK_PR_ELSE bloco_cmd | ;

for: TK_PR_FOR '(' atribuicao ':' expressao ':' atribuicao ')' bloco_cmd;

while: TK_PR_WHILE '(' expressao ')' TK_PR_DO bloco_cmd;

  /* Expressoes */

expressao:
	'(' expressao ')' 
	| literal 
	| TK_IDENTIFICADOR acesso_vetor
	| chamada_de_funcao	
	| '+' expressao
	| '-' expressao %prec inverte_sinal
	| '!' expressao
	| '&' expressao %prec endereco_variavel
	| '*' expressao %prec valor_ponteiro
	| '?' expressao %prec avaliacao_logica
	| '#' expressao 
	| expressao '^' expressao
	| expressao '*' expressao
	| expressao '/' expressao
	| expressao '%' expressao
	| expressao '+' expressao
	| expressao '-' expressao
	//bitwise and
	| expressao '&' expressao
	//bitwise or
	| expressao '|' expressao
	//comparadores logicos	
	| expressao '<' expressao
	| expressao '>' expressao
	| expressao TK_OC_EQ expressao
	| expressao TK_OC_NE expressao
	| expressao TK_OC_GE expressao
	| expressao TK_OC_LE expressao
	//operadores logicos	
	| expressao TK_OC_AND expressao
	| expressao TK_OC_OR expressao
	// ternario
	| expressao '?' expressao ':'
	
	
	
	
	
	
	
	

	
%%
void yyerror(char const *s)
{
    printf ("line %d: %s\n", get_line_number(), s);
}

