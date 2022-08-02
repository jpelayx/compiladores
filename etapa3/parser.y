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

%token<valor_lexico> ','
%token<valor_lexico> ';'
%token<valor_lexico> ':'
%token<valor_lexico> '|'
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
%type<nodo> funcao
%type<valor_lexico> cabecalho
%type<nodo> bloco_cmd
%type<nodo> lista_comandos
%type<nodo> comando
%type<nodo> chamada_de_funcao
%type<nodo> declaracao_variavel
%type<nodo> shift 
%type<nodo> retorno
%type<nodo> entrada
%type<nodo> saida
%type<nodo> controle_fluxo
%type<nodo> inicializa_variavel
%type<nodo> lista_identificadores_l
%type<nodo> identificador_ou_literal
%type<nodo> literal
%type<nodo> acesso_vetor
%type<nodo> atribuicao
%type<nodo> parametro_chamada_funcao
%type<nodo> mais_parametros_chamada_funcao
%type<valor_lexico> token_shift
%type<nodo> cf_if
%type<nodo> cf_else
%type<nodo> cf_for
%type<nodo> cf_while
%type<nodo> literal_numerico
%type<nodo> operandos_booleanos
%type<nodo> expressao_booleana
%type<nodo> operandos_aritmeticos  
%type<nodo> expressao_aritmetica
%type<nodo> literal_booleano
%type<nodo> expressao


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

input: programa YYEOF {arvore = $1;};

programa: programa var_global	{$$ = $1;} // var_global não tem inicializacao.
	| programa funcao 
		{
			ast_t *n = cria_nodo(lista_funcao, NULL);
			insere_filho(n, $2);
			if($1 != NULL)
				insere_filho(n, $1);
		}
	| 	{$$ = NULL;};

tipo: TK_PR_INT | TK_PR_FLOAT | TK_PR_CHAR | TK_PR_BOOL | TK_PR_STRING;
estatico: TK_PR_STATIC | ;
constante: TK_PR_CONST | ;
vetor: '[' TK_LIT_INT ']' | ; 

var_global: estatico tipo TK_IDENTIFICADOR vetor lista_identificadores_g ';' ;
lista_identificadores_g: lista_identificadores_g ',' TK_IDENTIFICADOR vetor | ;

//Bloco de comandos é filho de um identificador que tá no cabecalho!
funcao: cabecalho bloco_cmd
	{
		ast_t *n = cria_nodo(lista_comando, &$1); 
		insere_filho(n, $2);
		$$ = n;
	}	

cabecalho: estatico tipo TK_IDENTIFICADOR '(' parametros ')' {$$ = $3;};	
parametros: constante tipo TK_IDENTIFICADOR lista_parametros | ;
lista_parametros: lista_parametros ',' constante tipo TK_IDENTIFICADOR | ;

bloco_cmd: '{' lista_comandos '}' 	{$$ = $2;}
lista_comandos: lista_comandos comando 
		{
			if($2 != NULL) {
				ast_t *n = cria_nodo(lista_comando, NULL);
				insere_filho(n, $2); // 1o, comando
				if($1 != NULL)
					insere_filho(n, $1); // 2o, proximo da lista
				$$ = n;
			}
			else 
				$$ = $1;
		}
	|   {$$ = NULL;};
comando: 
	bloco_cmd ';' 				{$$ = NULL;}
	| declaracao_variavel ';' 	{$$ = $1;}
	| atribuicao ';' 			{$$ = $1;}
	| chamada_de_funcao ';' 	{$$ = NULL;}
	| shift ';' 				{$$ = NULL;}
	| retorno ';' 				{$$ = NULL;}
	| TK_PR_BREAK ';' 			{$$ = NULL;}
	| TK_PR_CONTINUE ';' 		{$$ = NULL;}
	| entrada ';' 				{$$ = NULL;}
	| saida ';' 				{$$ = NULL;}
	| controle_fluxo ';' 		{$$ = NULL;}
	; 

	/* Comandos simples */

/* supondo aqui que, como mais de uma atribuição é possivel, elas vao em uma lista de 
 * expressoes, mas acho que talvez seja uma boa perguntar pro schnorr */
declaracao_variavel: estatico constante tipo inicializa_variavel lista_identificadores_l
	{
		if($4 != NULL) {
			ast_t *n = cria_nodo(lista_expressao, NULL);
			insere_filho(n, $4); // 1o, expressao
			if($5 != NULL)
				insere_filho(n, $5); // 2o, proximo da lista
			$$ = n;
		}
		else 
			$$ = $5;
	};
lista_identificadores_l: lista_identificadores_l ','  inicializa_variavel
		{
			if($3 != NULL){
				ast_t *n = cria_nodo(lista_expressao, NULL);
				insere_filho(n, $3); // 1o, expressao
				if($1 != NULL)
					insere_filho(n, $1); // 2o, proximo da lista
				$$ = n;
			}
			else 
				$$ = $1;
		} 	
	|   {$$ = NULL;}
inicializa_variavel: 
	TK_IDENTIFICADOR 					
		{$$ = NULL;} //ignora declaracao de variavel sem inicialização
	| TK_IDENTIFICADOR TK_OC_LE identificador_ou_literal
		{
			ast_t *n = cria_nodo(declaracao, NULL);
			insere_filho(n, cria_nodo(identificador, &$1));
			insere_filho(n, $3);
			$$ = n;
		}	
	
literal: TK_LIT_TRUE   {$$ = cria_nodo(literal, &$1);} 		
	   | TK_LIT_FALSE  {$$ = cria_nodo(literal, &$1);}	
	   | TK_LIT_INT    {$$ = cria_nodo(literal, &$1);}	
	   | TK_LIT_FLOAT  {$$ = cria_nodo(literal, &$1);}
	   | TK_LIT_STRING {$$ = cria_nodo(literal, &$1);}
	   | TK_LIT_CHAR   {$$ = cria_nodo(literal, &$1);};

identificador_ou_literal: 
	literal {$$ = $1;}
	|TK_IDENTIFICADOR {$$ = cria_nodo(identificador, &$1);};	


acesso_vetor: '[' expressao ']' {$$ = $2;} 
		    | {$$ = NULL;};

atribuicao: TK_IDENTIFICADOR acesso_vetor '=' expressao 
	{
		ast_t *n = cria_nodo(atribuicao, NULL);
		insere_filho(n, cria_nodo_vetor(&$1, $2));
		insere_filho(n, $4);
		$$ = n;
	}

entrada: TK_PR_INPUT TK_IDENTIFICADOR 
	{
		ast_t *n = cria_nodo(entrada, NULL);
		insere_filho(n, cria_nodo(identificador, &$2));
		$$ = n;
	};
saida: TK_PR_OUTPUT identificador_ou_literal
	{
		ast_t *n = cria_nodo(entrada, NULL);
		insere_filho(n, $2);
		$$ = n;
	};

/* na especificacao diz que a lista de expressoes tem pelo menos um filho 
 * mas acho que tem que ter pelo menos dois, o primeiro que é a expressao 
 * e o segundo, opcional, que é a próxima lista_expressao, se houver.     */
parametro_chamada_funcao: expressao mais_parametros_chamada_funcao 
	{
		ast_t *n = cria_nodo(lista_expressao, NULL);
		insere_filho(n, $1); // 1o a expressao
		if($2 != NULL)
			insere_filho(n, $2); // 2o o proximo item da lista
		$$ = n;
	}
    | {$$ = NULL;};
mais_parametros_chamada_funcao: mais_parametros_chamada_funcao ',' expressao 
	{
		ast_t *n = cria_nodo(lista_expressao, NULL);
		insere_filho(n, $3);
		if($1 != NULL)
			insere_filho(n, $1);
		$$ = n;
	}
	| {$$ = NULL;};
chamada_de_funcao: TK_IDENTIFICADOR '(' parametro_chamada_funcao ')'
	{
		ast_t *n = cria_nodo(chamada_funcao, &$1);
		if($3 != NULL)
			insere_filho(n, $3);
		$$ = n;
	};

shift: TK_IDENTIFICADOR acesso_vetor token_shift TK_LIT_INT
	{
		ast_t *n = cria_nodo(cmd_shift, &$3);
		insere_filho(n, cria_nodo_vetor(&$1, $2));
		insere_filho(n, cria_nodo(literal, &$4));
		$$ = n;
	};
token_shift: TK_OC_SL {$$ = $1;}  // passando direto o valor_lexico 
           | TK_OC_SR {$$ = $1;};

retorno: TK_PR_RETURN expressao 
	{
		ast_t *n = cria_nodo(cmd_return, NULL);
		insere_filho(n, $2);
		$$ = n;
	};

controle_fluxo: cf_if    {$$ = $1;}
              | cf_for   {$$ = $1;}
			  | cf_while {$$ = $1;};

cf_if: TK_PR_IF '(' expressao ')' bloco_cmd cf_else 
	{
		ast_t *n = cria_nodo(cmd_if, NULL);
		insere_filho(n, $3);
		insere_filho(n, $5);
		if($6 != NULL)
			insere_filho(n, $6);
		$$ = n;
	};
cf_else: TK_PR_ELSE bloco_cmd {$$ = $2;}
       | {$$ = NULL;};

cf_for: TK_PR_FOR '(' atribuicao ':' expressao ':' atribuicao ')' bloco_cmd
	{
		ast_t *n = cria_nodo(cmd_for, NULL);
		insere_filho(n, $3);
		insere_filho(n, $5);
		insere_filho(n, $7);
		insere_filho(n, $9);
		$$ = n;
	};

cf_while: TK_PR_WHILE '(' expressao ')' TK_PR_DO bloco_cmd
	{
		ast_t *n = cria_nodo(cmd_while, NULL);
		insere_filho(n, $3);
		insere_filho(n, $6);
		$$ = n;
	};

  /* Expressoes */
literal_numerico: TK_LIT_INT   {$$ = cria_nodo(literal, &$1);}
	            | TK_LIT_FLOAT {$$ = cria_nodo(literal, &$1);} 
  
operandos_aritmeticos: 
	literal_numerico                {$$ = $1;}
	| chamada_de_funcao             {$$ = $1;} 
	| TK_IDENTIFICADOR acesso_vetor {$$ = cria_nodo_vetor(&$1, $2);}
	| expressao_aritmetica          {$$ = $1;}
	| '(' expressao_aritmetica ')'  {$$ = $2;}
	
expressao_aritmetica: 
	 '+' operandos_aritmeticos                          { $$ = cria_nodo_unario(&($1), $2); }
	| '-' operandos_aritmeticos %prec inverte_sinal     { $$ = cria_nodo_unario(&($1), $2); }
	| '&' operandos_aritmeticos %prec endereco_variavel { $$ = cria_nodo_unario(&($1), $2); }
	| '*' operandos_aritmeticos %prec valor_ponteiro    { $$ = cria_nodo_unario(&($1), $2); }
	| '#' operandos_aritmeticos                         { $$ = cria_nodo_unario(&($1), $2); }
	| operandos_aritmeticos '+' operandos_aritmeticos   { $$ = cria_nodo_binario(&($2), $1, $3); }
	| operandos_aritmeticos '-' operandos_aritmeticos   { $$ = cria_nodo_binario(&($2), $1, $3); }
	| operandos_aritmeticos '^' operandos_aritmeticos   { $$ = cria_nodo_binario(&($2), $1, $3); }
	| operandos_aritmeticos '*' operandos_aritmeticos   { $$ = cria_nodo_binario(&($2), $1, $3); }
	| operandos_aritmeticos '/' operandos_aritmeticos   { $$ = cria_nodo_binario(&($2), $1, $3); }
	| operandos_aritmeticos '%' operandos_aritmeticos   { $$ = cria_nodo_binario(&($2), $1, $3); }
	//bitwise and
	| operandos_aritmeticos '&' operandos_aritmeticos   { $$ = cria_nodo_binario(&($2), $1, $3); }
	//bitwise or
	| operandos_aritmeticos '|' operandos_aritmeticos   { $$ = cria_nodo_binario(&($2), $1, $3); }
	
literal_booleano: TK_LIT_TRUE  {$$ = cria_nodo(literal, &($1));} 
                | TK_LIT_FALSE {$$ = cria_nodo(literal, &($1));}

operandos_booleanos: 
	  TK_IDENTIFICADOR acesso_vetor	{ $$ = cria_nodo_vetor(&$1, $2);}
	| literal_booleano {$$ = $1;}
	| expressao_booleana {$$ = $1;}
	| '(' expressao_booleana ')' {$$ = $2;}

expressao_booleana:
	 '!' operandos_booleanos	{ $$ = cria_nodo_unario(&($1), $2); }
	|'?' operandos_booleanos  %prec avaliacao_logica { $$ = cria_nodo_unario(&($1), $2); }
	//comparadores logicos	
	| operandos_aritmeticos '<' operandos_aritmeticos  { $$ = cria_nodo_binario(&($2), $1, $3); }
	| operandos_aritmeticos '>' operandos_aritmeticos  { $$ = cria_nodo_binario(&($2), $1, $3); }
	| operandos_aritmeticos TK_OC_EQ operandos_aritmeticos  { $$ = cria_nodo_binario(&($2), $1, $3); }
	| operandos_aritmeticos TK_OC_NE operandos_aritmeticos  { $$ = cria_nodo_binario(&($2), $1, $3); }
	| operandos_aritmeticos TK_OC_GE operandos_aritmeticos  { $$ = cria_nodo_binario(&($2), $1, $3); }
	| operandos_aritmeticos TK_OC_LE operandos_aritmeticos  { $$ = cria_nodo_binario(&($2), $1, $3); }
	//operadores logicos	
	| operandos_booleanos TK_OC_AND operandos_booleanos { $$ = cria_nodo_binario(&($2), $1, $3); }
	| operandos_booleanos TK_OC_OR operandos_booleanos  { $$ = cria_nodo_binario(&($2), $1, $3); }
	
expressao:
	TK_IDENTIFICADOR acesso_vetor	{$$ = cria_nodo_vetor(&($1), $2);}
	| chamada_de_funcao             {$$ = $1;}
	| literal_numerico              {$$ = $1;}
	| expressao_aritmetica			{$$ = $1;}
	| expressao_booleana			{$$ = $1;}
	// ternario
	| expressao '?' expressao ':' expressao	{
		ast_t *n = cria_nodo(ternario, NULL);
		insere_filho(n, $1);
		insere_filho(n, $3);
		insere_filho(n, $5);
		$$ = n;	}
	
%%
void yyerror(char const *s)
{
    printf ("line %d: %s\n", get_line_number(), s);
}

