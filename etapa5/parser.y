%{

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

%}

%code requires { #include "ast.h" }
%code requires { #include "valor_token.h" }
%code requires { #include "tabela_simbolos.h" }
%code requires { #include "escopo.h" }
%code requires { #include "instr.h" }

%union {
	valor_token_t *valor_lexico;
	ast_t *nodo;
	tipos_semanticos_t tipo;
}

%define parse.error verbose

%token<tipo> TK_PR_INT
%token<tipo> TK_PR_FLOAT
%token<tipo> TK_PR_BOOL
%token<tipo> TK_PR_CHAR
%token<tipo> TK_PR_STRING
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

%token<valor_lexico> '|'
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
%token<valor_lexico> '$'
%token<valor_lexico> '?'

%type<nodo> programa 
%type<nodo> funcao
%type<tipo> tipo
%type<nodo> vetor
%type<nodo> cabecalho
%type<nodo> bloco_cmd
%type<nodo> corpo_funcao
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

// nodos temporarios 
%type<nodo> lista_identificadores_g
%type<nodo> lista_parametros

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

input: programa {arvore = $1; sai_escopo(escopo); };

programa: programa var_global	{$$ = $1;} 
	| programa funcao           { $$ = insere_fim_lista($2, $1);} 
	| 	                        { $$ = NULL;};

tipo: TK_PR_INT    {$$ = $1;} 
	| TK_PR_FLOAT  {$$ = $1;} 
	| TK_PR_CHAR   {$$ = $1;} 
	| TK_PR_BOOL   {$$ = $1;} 
	| TK_PR_STRING {$$ = $1;};

estatico: TK_PR_STATIC | ;

constante: TK_PR_CONST | ;

vetor: '[' TK_LIT_INT ']' {$$ = cria_nodo(literal, $2);}
     | {$$ = NULL;};

var_global: estatico tipo TK_IDENTIFICADOR vetor lista_identificadores_g ';' 
	{
	 simbolo_t *s = novo_simbolo();
	 adiciona_valor_lexico(s, $3);
	 libera_tk($3);
	 s->tipo = $2;
	 if($4 == NULL)
		s->natureza = simbolo_variavel;
	 else {
		s->natureza = simbolo_vetor;
		s->tamanho = $4->valor_lexico->valor.inteiro;
		libera($4);
	 }
	 escopo = adiciona_simbolo(escopo, s); 
	 escopo = adiciona_lista_simbolos(escopo, $5, $2); // adiciona as variaveis em lista_identificadores_g
	 libera($5); // libera arvore temporaria 
	};
lista_identificadores_g: lista_identificadores_g ',' TK_IDENTIFICADOR vetor  
	{// cria uma arvore temporaria que guarda as variaveis 
	 ast_t *n = cria_nodo_vetor($3, $4);
	 $$ = insere_fim_lista(n, $1); }
	| {$$ = NULL;} ;

funcao: cabecalho '{' corpo_funcao '}'
	{
		insere_filho($1, $3);
		$$ = $1;
		escopo = sai_escopo(escopo); // fechando o escopo local na hora da redução
		simbolo_t *s = novo_simbolo();
		adiciona_valor_lexico(s, $1->valor_lexico);
		s->natureza = simbolo_funcao;
		s->tipo = $1->tipo_sem;
		escopo = adiciona_simbolo(escopo, s); // adicionando a funcao ao escopo global
	}

bloco_cmd_inicio: '{' { 
						escopo = novo_escopo(escopo, escopo_interno, retorna_proximo_id_do_escopo_da_funcao(escopo));
					  };
bloco_cmd_fim: '}' { escopo = sai_escopo(escopo); };

corpo_funcao: 
	//NÃO ABRE ESCOPO PRÓPRIO!!!
	lista_comandos {$$ = $1;}


cabecalho: estatico tipo TK_IDENTIFICADOR '(' parametros ')' 
	{ast_t *n = cria_nodo(funcao, $3);
	 n->tipo_sem = $2;
	 $$ = n; };	
parametros: constante tipo TK_IDENTIFICADOR lista_parametros 
	{simbolo_t *s = novo_simbolo();
	 adiciona_valor_lexico(s, $3);
	 libera_tk($3);
	 s->natureza = simbolo_variavel;
	 s->tipo = $2;
	 escopo = adiciona_simbolo(escopo, s);  }
	| 
	{// primeira redução que vai ocorrer, inicio do escopo local da funcao s/ parametros
	 escopo = novo_escopo(escopo, escopo_funcao, 0);};
lista_parametros: lista_parametros ',' constante tipo TK_IDENTIFICADOR 
	{simbolo_t *s = novo_simbolo();
	 adiciona_valor_lexico(s, $5);
	 libera_tk($5);
	 s->natureza = simbolo_variavel;
	 s->tipo = $4;
	 escopo = adiciona_simbolo(escopo, s); }
	| 
	{//primeira redução que vai ocorrer, inicio do escopo local da funcao c/ paramentros
	 escopo = novo_escopo(escopo, escopo_funcao, 0);};

bloco_cmd: bloco_cmd_inicio lista_comandos bloco_cmd_fim {$$ = $2;}

lista_comandos: lista_comandos comando 
		{$$ = insere_fim_lista($2, $1);}
	|   {$$ = NULL; }
comando: 
	bloco_cmd ';' 				{$$ = $1;}
	| declaracao_variavel ';' 	{$$ = $1;}
	| atribuicao ';' 			{$$ = $1;}
	| chamada_de_funcao ';' 	{$$ = $1;}
	| shift ';' 				{$$ = $1;}
	| retorno ';' 				{$$ = $1;}
	| TK_PR_BREAK ';' 			{$$ = cria_nodo(cmd_break, NULL);}
	| TK_PR_CONTINUE ';' 		{$$ = cria_nodo(cmd_continue, NULL);}
	| entrada ';' 				{$$ = $1;}
	| saida ';' 				{$$ = $1;}
	| controle_fluxo ';'   		{$$ = $1;}	; 

	/* Comandos simples */

declaracao_variavel: estatico constante tipo inicializa_variavel lista_identificadores_l
	{ $$ = insere_inicio_lista($4, $5);
	  escopo = adiciona_lista_simbolos(escopo, $$, $3);
	  $$ = remove_nodos_inuteis($$);};
lista_identificadores_l: lista_identificadores_l ','  inicializa_variavel
		{$$ = insere_fim_lista($3, $1); } 	
	|   {$$ = NULL;}
inicializa_variavel: 
	TK_IDENTIFICADOR 					
		{
			$$ = cria_nodo(identificador, $1);
		} //ignora declaracao de variavel sem inicialização
	| TK_IDENTIFICADOR TK_OC_LE identificador_ou_literal
		{
			ast_t *n = cria_nodo(declaracao, NULL);
			insere_filho(n, cria_nodo(identificador, $1));
			insere_filho(n, $3);
			libera_tk($2);
			$$ = n;
		}	
	
literal: TK_LIT_TRUE   {$$ = cria_nodo(literal, $1); $$->tipo_sem = bool_sem;} 		
	   | TK_LIT_FALSE  {$$ = cria_nodo(literal, $1); $$->tipo_sem = bool_sem;}	
	   | TK_LIT_INT    {$$ = cria_nodo(literal, $1); $$->tipo_sem = int_sem;}	
	   | TK_LIT_FLOAT  {$$ = cria_nodo(literal, $1); $$->tipo_sem = float_sem;}
	   | TK_LIT_STRING {$$ = cria_nodo(literal, $1); $$->tipo_sem = string_sem;}
	   | TK_LIT_CHAR   {$$ = cria_nodo(literal, $1); $$->tipo_sem = char_sem;};

identificador_ou_literal: 
	literal {$$ = $1;}
	|TK_IDENTIFICADOR {
		simbolo_t *s = referencia(escopo, $1, simbolo_variavel);
		$$ = cria_nodo(identificador, $1);
		$$->tipo_sem = s->tipo;
	};	

acesso_vetor: '[' expressao ']' {verifica_tipos($2->tipo_sem, int_sem, $2->valor_lexico->linha); $$ = $2;} 
		    | {$$ = NULL;};

atribuicao: TK_IDENTIFICADOR acesso_vetor '=' expressao 
	{
		simbolo_t *s;
		if($2 == NULL)
			s = referencia(escopo, $1, simbolo_variavel);
		else 
			s = referencia(escopo, $1, simbolo_vetor);
		verifica_tipos($4->tipo_sem, s->tipo, $4->valor_lexico->linha);
		ast_t *n = cria_nodo(atribuicao, NULL);
		insere_filho(n, cria_nodo_vetor($1, $2));
		insere_filho(n, $4);
		libera_tk($3);
		n->codigo = $4->codigo;
		$$ = n;
	}

entrada: TK_PR_INPUT TK_IDENTIFICADOR 
	{
		simbolo_t *s = referencia(escopo, $2, simbolo_variavel);
		ast_t *n = cria_nodo(entrada, NULL);
		insere_filho(n, cria_nodo(identificador, $2));
		n->tipo_sem = s->tipo;
		$$ = n;
	};
saida: TK_PR_OUTPUT identificador_ou_literal
	{
		ast_t *n = cria_nodo(saida, NULL);
		insere_filho(n, $2);
		$$ = n;
	};

parametro_chamada_funcao: expressao mais_parametros_chamada_funcao 
	  {$$ = insere_inicio_lista($1, $2);}
    | {$$ = NULL;};
mais_parametros_chamada_funcao: mais_parametros_chamada_funcao ',' expressao 
	  {$$ = insere_fim_lista($3, $1);}
	| {$$ = NULL;};
chamada_de_funcao: TK_IDENTIFICADOR '(' parametro_chamada_funcao ')'
	{
		simbolo_t *s = referencia(escopo, $1, simbolo_funcao);
		ast_t *n = cria_nodo(chamada_funcao, $1);
		if($3 != NULL)
			insere_filho(n, $3);
		n->tipo_sem = s->tipo;
		$$ = n;
	};

shift: TK_IDENTIFICADOR acesso_vetor token_shift TK_LIT_INT
	{
		simbolo_t *s;
		if($2 == NULL)
			s = referencia(escopo, $1, simbolo_variavel);
		else 
			s = referencia(escopo, $1, simbolo_vetor);
		ast_t *n = cria_nodo(cmd_shift, $3);
		insere_filho(n, cria_nodo_vetor($1, $2));
		insere_filho(n, cria_nodo(literal, $4));
		n->tipo_sem = s->tipo;
		$$ = n;
	};
token_shift: TK_OC_SL {$$ = $1;}  // passando direto o valor_lexico 
           | TK_OC_SR {$$ = $1;};

retorno: TK_PR_RETURN expressao 
	{
		ast_t *n = cria_nodo(cmd_return, NULL);
		insere_filho(n, $2);
		n->tipo_sem = $2->tipo_sem;
		$$ = n;
	};

controle_fluxo: cf_if    {$$ = $1;}
              | cf_for   {$$ = $1;}
			  | cf_while {$$ = $1;};

cf_if: TK_PR_IF '(' expressao ')' bloco_cmd cf_else 
	{
		verifica_tipos($3->tipo_sem, bool_sem, $3->valor_lexico->linha);
		ast_t *n = cria_nodo(cmd_if, NULL);
		insere_filho(n, $3);
		insere_filho(n, $5);
		code_t *cod_if, *cod_else, *cod_fim;
		if($6 != NULL)
		{
			insere_filho(n, $6);
			cod_else = $6->codigo;
		}
		else
		{
			// instrução vazia que recebe o label 
			cod_else = cod_nop();
		}
		operando_instr_t *lt = novo_label(),
						 *lf = novo_label(),
						 *fim = novo_label();
		adiciona_label(lt, $5->codigo);
		adiciona_label(lf, cod_else);
		remenda_true(lt, $3->codigo);
		remenda_false(lf, $3->codigo);
		cod_else = concatena_codigo(cod_else, cod_jump_incondicional(fim));
		cod_if   = concatena_codigo($5->codigo, cod_jump_incondicional(fim));
		cod_fim = cod_nop();
		adiciona_label(fim, cod_fim);
		n->codigo = concatena_codigo($3->codigo, cod_if);
		n->codigo = concatena_codigo(n->codigo, cod_else);
		n->codigo = concatena_codigo(n->codigo, cod_fim);
		imprime_codigo(n->codigo);
		$$ = n;
	};
cf_else: TK_PR_ELSE bloco_cmd {$$ = $2;}
       | {$$ = NULL;};

cf_for: TK_PR_FOR '(' atribuicao ':' expressao ':' atribuicao ')' bloco_cmd
	{
		verifica_tipos($5->tipo_sem, bool_sem, $5->valor_lexico->linha);
		ast_t *n = cria_nodo(cmd_for, NULL);
		insere_filho(n, $3);
		insere_filho(n, $5);
		insere_filho(n, $7);
		insere_filho(n, $9);
		$$ = n;
	};

cf_while: TK_PR_WHILE '(' expressao ')' TK_PR_DO bloco_cmd
	{
		verifica_tipos($3->tipo_sem, bool_sem, $3->valor_lexico->linha);
		ast_t *n = cria_nodo(cmd_while, NULL);
		insere_filho(n, $3);
		insere_filho(n, $6);
		operando_instr_t *condicao = novo_label(),
		                 *inicio = novo_label(),
		                 *fim = novo_label();
		code_t *cod_bloco = concatena_codigo($6->codigo, cod_jump_incondicional(condicao)),
		       *cod_fim = cod_nop();
		adiciona_label(condicao, $3->codigo);
		adiciona_label(inicio, cod_bloco);
		adiciona_label(fim, cod_fim);
		remenda_true(inicio, $3->codigo);
		remenda_false(fim, $3->codigo);
		n->codigo = concatena_codigo($3->codigo, cod_bloco);
		n->codigo = concatena_codigo(n->codigo, cod_fim);
		imprime_codigo(n->codigo);
		$$ = n;
	};

  /* Expressoes */
literal_numerico: TK_LIT_INT   
	{ $$ = cria_nodo(literal, $1); 
	  $$->tipo_sem = int_sem;
	  $$->temp = novo_registrador();
	  $$->codigo = cod_load_literal($$->temp, $1->valor.inteiro);
	  imprime_codigo($$->codigo); }
	| TK_LIT_FLOAT // FORA DA ETAPA 5 
	{ $$ = cria_nodo(literal, $1);
	  $$->tipo_sem = float_sem;} ;
  
operandos_aritmeticos: 
	literal_numerico                {$$ = $1;}
	| chamada_de_funcao             {$$ = $1;} 
	| TK_IDENTIFICADOR acesso_vetor { 
		simbolo_t *s;
		if($2 == NULL)
			s = referencia(escopo, $1, simbolo_variavel);
		else 
			s = referencia(escopo, $1, simbolo_vetor);
		$$ = cria_nodo_vetor($1, $2);
		$$->tipo_sem = s->tipo; 
		// assumindo que nao vao haver vetores na etapa 5
	  	$$->temp = novo_registrador();
		$$->codigo = cod_load_variavel($$->temp, 0);
		imprime_codigo($$->codigo);  }
	| expressao_aritmetica          {$$ = $1;}
	| '(' expressao_aritmetica ')'  {$$ = $2;}
	
expressao_aritmetica: 
	// ETAPA 5: APENAS BINARIAS
	 '+' operandos_aritmeticos                          
	{ verifica_tipos($2->tipo_sem, numerico_sem, $2->valor_lexico->linha);
	  $$ = cria_nodo_unario(($1), $2);
	  $$->tipo_sem = $2->tipo_sem; 
	  $$->temp = $2->temp;
	  $$->codigo = $2->codigo;}
	| '-' operandos_aritmeticos %prec inverte_sinal     
	{ verifica_tipos($2->tipo_sem, numerico_sem, $2->valor_lexico->linha);
	  $$ = cria_nodo_unario(($1), $2);
	  $$->tipo_sem = $2->tipo_sem; }
	| '&' operandos_aritmeticos %prec endereco_variavel 
	{ verifica_tipos($2->tipo_sem, numerico_sem, $2->valor_lexico->linha);
	  $$ = cria_nodo_unario(($1), $2);
	  $$->tipo_sem = $2->tipo_sem; }
	| '*' operandos_aritmeticos %prec valor_ponteiro    
	{ verifica_tipos($2->tipo_sem, numerico_sem, $2->valor_lexico->linha);
	  $$ = cria_nodo_unario(($1), $2);
	  $$->tipo_sem = $2->tipo_sem; }
	| '#' operandos_aritmeticos                         
	{ verifica_tipos($2->tipo_sem, numerico_sem, $2->valor_lexico->linha);
	  $$ = cria_nodo_unario(($1), $2);
	  $$->tipo_sem = $2->tipo_sem; }
	  // OPERAÇÕES BINARIAS
	| operandos_aritmeticos '+' operandos_aritmeticos   
	{ verifica_tipos($1->tipo_sem, numerico_sem, $1->valor_lexico->linha);
	  verifica_tipos($3->tipo_sem, numerico_sem, $3->valor_lexico->linha);
	  $$ = cria_nodo_binario(($2), $1, $3);
	  $$->tipo_sem = infere_tipo($1, $3);
	  $$->temp = novo_registrador();
	  $$->codigo = concatena_codigo($1->codigo, $3->codigo);
	  $$->codigo = concatena_codigo($$->codigo, cod_op_bin_aritmetica($1->temp, $3->temp, $$->temp, '+'));  
	  imprime_codigo($$->codigo);}
	| operandos_aritmeticos '-' operandos_aritmeticos   
	{ verifica_tipos($1->tipo_sem, numerico_sem, $1->valor_lexico->linha);
	  verifica_tipos($3->tipo_sem, numerico_sem, $3->valor_lexico->linha);
	  $$ = cria_nodo_binario(($2), $1, $3);
	  $$->tipo_sem = infere_tipo($1, $3); 
	  $$->temp = novo_registrador();
	  $$->codigo = concatena_codigo($1->codigo, $3->codigo);
	  $$->codigo = concatena_codigo($$->codigo, cod_op_bin_aritmetica($1->temp, $3->temp, $$->temp, '-'));  
	  imprime_codigo($$->codigo);}
	| operandos_aritmeticos '^' operandos_aritmeticos   
	{ verifica_tipos($1->tipo_sem, numerico_sem, $1->valor_lexico->linha);
	  verifica_tipos($3->tipo_sem, numerico_sem, $3->valor_lexico->linha);
	  $$ = cria_nodo_binario(($2), $1, $3);
	  $$->tipo_sem = infere_tipo($1, $3); }
	| operandos_aritmeticos '*' operandos_aritmeticos   
	{ verifica_tipos($1->tipo_sem, numerico_sem, $1->valor_lexico->linha);
	  verifica_tipos($3->tipo_sem, numerico_sem, $3->valor_lexico->linha);
	  $$ = cria_nodo_binario(($2), $1, $3);
	  $$->tipo_sem = infere_tipo($1, $3); 
	  $$->temp = novo_registrador();
	  $$->codigo = concatena_codigo($1->codigo, $3->codigo);
	  $$->codigo = concatena_codigo($$->codigo, cod_op_bin_aritmetica($1->temp, $3->temp, $$->temp, '*'));  
	  imprime_codigo($$->codigo);}
	// divisao
	| operandos_aritmeticos '/' operandos_aritmeticos   
	{ verifica_tipos($1->tipo_sem, numerico_sem, $1->valor_lexico->linha);
	  verifica_tipos($3->tipo_sem, numerico_sem, $3->valor_lexico->linha);
	  $$ = cria_nodo_binario(($2), $1, $3);
	  $$->tipo_sem = infere_tipo($1, $3); 
	  $$->temp = novo_registrador();
	  $$->codigo = concatena_codigo($1->codigo, $3->codigo);
	  $$->codigo = concatena_codigo($$->codigo, cod_op_bin_aritmetica($1->temp, $3->temp, $$->temp, '/')); 
	  imprime_codigo($$->codigo);}
	// modulo
	| operandos_aritmeticos '%' operandos_aritmeticos   
	{ verifica_tipos($1->tipo_sem, numerico_sem, $1->valor_lexico->linha);
	  verifica_tipos($3->tipo_sem, numerico_sem, $3->valor_lexico->linha);
	  $$ = cria_nodo_binario(($2), $1, $3);
	  $$->tipo_sem = infere_tipo($1, $3); }
	//bitwise and
	| operandos_aritmeticos '&' operandos_aritmeticos   
	{ verifica_tipos($1->tipo_sem, numerico_sem, $1->valor_lexico->linha);
	  verifica_tipos($3->tipo_sem, numerico_sem, $3->valor_lexico->linha);
	  $$ = cria_nodo_binario(($2), $1, $3);
	  $$->tipo_sem = infere_tipo($1, $3); }
	//bitwise or
	| operandos_aritmeticos '|' operandos_aritmeticos   
	{ verifica_tipos($1->tipo_sem, numerico_sem, $1->valor_lexico->linha);
	  verifica_tipos($3->tipo_sem, numerico_sem, $3->valor_lexico->linha);
	  $$ = cria_nodo_binario(($2), $1, $3);
	  $$->tipo_sem = infere_tipo($1, $3); }
	
literal_booleano: TK_LIT_TRUE  
	{ $$ = cria_nodo(literal, ($1));
	  $$->tipo_sem = bool_sem;
	  $$->codigo = cod_op_bin_lit('t');
	  imprime_codigo($$->codigo);  } 
    | TK_LIT_FALSE 
	{ $$ = cria_nodo(literal, ($1)); 
	  $$->tipo_sem = bool_sem;
	  $$->codigo = cod_op_bin_lit('f');
	  imprime_codigo($$->codigo);  }

operandos_booleanos: 
	  TK_IDENTIFICADOR acesso_vetor	{ 
		simbolo_t *s;
		if($2 == NULL)
			s = referencia(escopo, $1, simbolo_variavel); 
		else
			s = referencia(escopo, $1, simbolo_vetor);
		$$ = cria_nodo_vetor($1, $2);
		$$->tipo_sem = s->tipo; 
		// assumindo que nao vao haver vetores na etapa 5
	  	$$->temp = novo_registrador();
		$$->codigo = cod_load_variavel($$->temp, 0);
		imprime_codigo($$->codigo);  }
	| literal_booleano {$$ = $1;}
	| expressao_booleana {$$ = $1;}
	| '(' expressao_booleana ')' {$$ = $2;}

expressao_booleana:
	 '!' operandos_booleanos
	 	{ verifica_tipos($2->tipo_sem, bool_sem, $2->valor_lexico->linha); 
		  $$ = cria_nodo_unario($1, $2);
		  $$->tipo_sem = bool_sem; }
	|'?' operandos_booleanos  %prec avaliacao_logica 
		{ verifica_tipos($2->tipo_sem, bool_sem, $2->valor_lexico->linha); 
		  $$ = cria_nodo_unario($1, $2); 
		  $$->tipo_sem = bool_sem; }
	//comparadores logicos	
	| operandos_aritmeticos '<' operandos_aritmeticos  
		{ verifica_tipos($1->tipo_sem, numerico_sem, $1->valor_lexico->linha);
		  verifica_tipos($3->tipo_sem, numerico_sem, $3->valor_lexico->linha);
		  $$ = cria_nodo_binario($2, $1, $3);
		  $$->temp = novo_registrador();
		  $$->codigo = concatena_codigo($1->codigo, $3->codigo);
		  code_t *op_rel = cod_op_rel_logica($1->temp, $3->temp, $$->temp, 1);
		  $$->codigo = concatena_codigo($$->codigo, op_rel);
		  $$->codigo->tl = op_rel->tl;
		  $$->codigo->fl = op_rel->fl;
		  imprime_codigo($$->codigo);
		  $$->tipo_sem = bool_sem; }
	| operandos_aritmeticos '>' operandos_aritmeticos  
		{ verifica_tipos($1->tipo_sem, numerico_sem, $1->valor_lexico->linha);
		  verifica_tipos($3->tipo_sem, numerico_sem, $3->valor_lexico->linha);
		  $$ = cria_nodo_binario($2, $1, $3); 
		  $$->temp = novo_registrador();
		  $$->codigo = concatena_codigo($1->codigo, $3->codigo);
		  code_t *op_rel = cod_op_rel_logica($1->temp, $3->temp, $$->temp, 3);
		  $$->codigo = concatena_codigo($$->codigo, op_rel);
		  $$->codigo->tl = op_rel->tl;
		  $$->codigo->fl = op_rel->fl;
		  imprime_codigo($$->codigo);
		  $$->tipo_sem = bool_sem; }
	| operandos_aritmeticos TK_OC_EQ operandos_aritmeticos  
		{ verifica_tipos($1->tipo_sem, numerico_sem, $1->valor_lexico->linha);
		  verifica_tipos($3->tipo_sem, numerico_sem, $3->valor_lexico->linha);
		  $$ = cria_nodo_binario($2, $1, $3); 
		  $$->temp = novo_registrador();
		  $$->codigo = concatena_codigo($1->codigo, $3->codigo);
		  code_t *op_rel = cod_op_rel_logica($1->temp, $3->temp, $$->temp, 5);
		  $$->codigo = concatena_codigo($$->codigo, op_rel);
		  $$->codigo->tl = op_rel->tl;
		  $$->codigo->fl = op_rel->fl;
		  imprime_codigo($$->codigo);
		  $$->tipo_sem = bool_sem; }
	| operandos_aritmeticos TK_OC_NE operandos_aritmeticos  
		{ verifica_tipos($1->tipo_sem, numerico_sem, $1->valor_lexico->linha);
		  verifica_tipos($3->tipo_sem, numerico_sem, $3->valor_lexico->linha);
		  $$ = cria_nodo_binario($2, $1, $3); 
		  $$->temp = novo_registrador();
		  $$->codigo = concatena_codigo($1->codigo, $3->codigo);
		  code_t *op_rel = cod_op_rel_logica($1->temp, $3->temp, $$->temp, 6);
		  $$->codigo = concatena_codigo($$->codigo, op_rel);
		  $$->codigo->tl = op_rel->tl;
		  $$->codigo->fl = op_rel->fl;
		  imprime_codigo($$->codigo);
		  $$->tipo_sem = bool_sem; }
	| operandos_aritmeticos TK_OC_GE operandos_aritmeticos  
		{ verifica_tipos($1->tipo_sem, numerico_sem, $1->valor_lexico->linha);
		  verifica_tipos($3->tipo_sem, numerico_sem, $3->valor_lexico->linha);
		  $$ = cria_nodo_binario($2, $1, $3); 
		  $$->temp = novo_registrador();
		  $$->codigo = concatena_codigo($1->codigo, $3->codigo);
		  code_t *op_rel = cod_op_rel_logica($1->temp, $3->temp, $$->temp, 4);
		  $$->codigo = concatena_codigo($$->codigo, op_rel);
		  $$->codigo->tl = op_rel->tl;
		  $$->codigo->fl = op_rel->fl;
		  imprime_codigo($$->codigo);
		  $$->tipo_sem = bool_sem; }
	| operandos_aritmeticos TK_OC_LE operandos_aritmeticos  
		{ verifica_tipos($1->tipo_sem, numerico_sem, $1->valor_lexico->linha);
		  verifica_tipos($3->tipo_sem, numerico_sem, $3->valor_lexico->linha);
		  $$ = cria_nodo_binario($2, $1, $3); 
		  $$->temp = novo_registrador();
		  $$->codigo = concatena_codigo($1->codigo, $3->codigo);
		  code_t *op_rel = cod_op_rel_logica($1->temp, $3->temp, $$->temp, 2);
		  $$->codigo = concatena_codigo($$->codigo, op_rel);
		  $$->codigo->tl = op_rel->tl;
		  $$->codigo->fl = op_rel->fl;
		  imprime_codigo($$->codigo);
		  $$->tipo_sem = bool_sem; }
	//operadores logicos	
	| operandos_booleanos TK_OC_AND operandos_booleanos 
		{ verifica_tipos($1->tipo_sem, bool_sem, $1->valor_lexico->linha);
		  verifica_tipos($3->tipo_sem, bool_sem, $3->valor_lexico->linha);
		  $$ = cria_nodo_binario($2, $1, $3); 
		  operando_instr_t *l = novo_label();
		  remenda_true(l, $1->codigo);
		  adiciona_label(l, $3->codigo);
		  $$->codigo = concatena_codigo($1->codigo, $3->codigo);
		  $$->codigo->tl = $3->codigo->tl;
		  insere_lista_buracos_false($$->codigo, $1->codigo->fl);
		  insere_lista_buracos_false($$->codigo, $3->codigo->fl);
		  imprime_codigo($$->codigo);
		  $$->tipo_sem = bool_sem; }
	| operandos_booleanos TK_OC_OR operandos_booleanos  
		{ verifica_tipos($1->tipo_sem, bool_sem, $1->valor_lexico->linha);
		  verifica_tipos($3->tipo_sem, bool_sem, $3->valor_lexico->linha);
		  $$ = cria_nodo_binario($2, $1, $3);
		  operando_instr_t *l = novo_label();
		  remenda_false(l, $1->codigo);
		  adiciona_label(l, $3->codigo);
		  $$->codigo = concatena_codigo($1->codigo, $3->codigo);
		  $$->codigo->fl = $3->codigo->fl;
		  insere_lista_buracos_true($$->codigo, $1->codigo->tl);
		  insere_lista_buracos_true($$->codigo, $3->codigo->tl);
		  imprime_codigo($$->codigo);
 		  $$->tipo_sem = bool_sem; }
	
expressao:
	TK_IDENTIFICADOR acesso_vetor	{
		simbolo_t *s;
		if($2 == NULL)
			s = referencia(escopo, $1, simbolo_variavel);
		else
			s = referencia(escopo, $1, simbolo_vetor);
		$$ = cria_nodo_vetor($1, $2);
		$$->tipo_sem = s->tipo;
	  	$$->temp = novo_registrador();
		$$->codigo = cod_load_variavel($$->temp, 0);
		imprime_codigo($$->codigo);  }
	| chamada_de_funcao             {$$ = $1;}
	| literal_numerico              {$$ = $1;}
	| expressao_aritmetica			{$$ = $1;}
	| expressao_booleana			{$$ = $1;}
	// ternario
	| expressao '?' expressao ':' expressao	{
		verifica_tipos($1->tipo_sem, bool_sem, $1->valor_lexico->linha);
		verifica_tipos($3->tipo_sem, numerico_sem, $3->valor_lexico->linha);
		verifica_tipos($5->tipo_sem, numerico_sem, $5->valor_lexico->linha);
		ast_t *n = cria_nodo(ternario, NULL);
		insere_filho(n, $1);
		insere_filho(n, $3);
		insere_filho(n, $5);
		n->tipo_sem = infere_tipo($3, $5);
		libera_tk($2);
		$$ = n;	}
	
%%
void yyerror(char const *s)
{
    printf ("line %d: %s\n", get_line_number(), s);
}

