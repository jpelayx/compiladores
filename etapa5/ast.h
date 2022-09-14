#ifndef _AST_H_
#define _AST_H_

#include "valor_token.h"
#include "instr.h"

typedef enum tipo_semantico
{
	nda, // para debug
	int_sem,
	float_sem, 
	bool_sem, 
	numerico_sem, // int, float ou bool
	char_sem, 
	void_sem,
	string_sem
} tipos_semanticos_t;

typedef enum tipos_ast_nodo
{
	funcao,
	//comandos simples
	declaracao,
	atribuicao,
	entrada,
	saida,
	chamada_funcao,
	cmd_shift,
	cmd_return,
	cmd_break,
	cmd_continue,
	cmd_if,
	cmd_for,
	cmd_while,
	//expressoes aritmeticas e logicas
	unario,
	binario,
	ternario,
	// outros
	acesso_vetor,
	identificador,
	identificador_vetor, 
	literal,
	passagem
} tipos_nodo_t;

typedef struct ast {
	tipos_nodo_t tipo;           // tipo de nodo ast (literal, identificador, op binaria/unaria, etc)
	tipos_semanticos_t tipo_sem; // tipo semantico (float, int, bool, char ou string)
	valor_token_t *valor_lexico; 
	code_t *codigo;
	operando_instr_t* temp;
    int num_filhos;
    struct ast **filhos;    
} ast_t;

// Cria nó sem filhos
ast_t *cria_nodo(tipos_nodo_t tipo, valor_token_t *valor_lexico);

// Cria nó do tipo binárico com dois filhos 
ast_t *cria_nodo_binario(valor_token_t *valor_lexico, ast_t *f1, ast_t *f2);

// Cria nó do tipo unário com um filho 
ast_t *cria_nodo_unario(valor_token_t *valor_lexico, ast_t *f1);

// Cria nó do tipo acesso_vetor ou identificador (se nenhum acesso for feito)
ast_t *cria_nodo_vetor(valor_token_t *valor_lexico, ast_t *vetor);

ast_t *cria_nodo_passagem();

// Adiciona nó filho
void insere_filho(ast_t *pai, ast_t *filho);

// dado um item, o transforma numa lista (ultimo filho é NULL)
ast_t *inicia_lista(ast_t *item);
// insere item no final de lista, garantindo que o retorno é uma lista
ast_t *insere_fim_lista(ast_t *item, ast_t *lista);
// insere item no inicio da lista
ast_t *insere_inicio_lista(ast_t *item, ast_t *lista);
// retorna o nodo que tiver NULL como ultimo filho 
ast_t *fim_da_lista(ast_t *t);

ast_t *remove_nodos_inuteis(ast_t *t);

/* registrador em que é salvo o retorno  se a arvore possui uma expressao return, 
 * NULL cc */
operando_instr_t * retorno(ast_t *t);

bool eh_booleana(ast_t *t);

// Libera recursivamente o nó e seus filhos
void libera(void *arvore);

// Imprime recursivamente a árvore
void exporta(void *arvore);

// Imprime os nós (vértices) da árvore
void imprime_nodos(ast_t *arvore);

// Imprime o nodo em questão
void imprime_nodo(ast_t *nodo); 

// Imprime as arestas (relações entre os nós) da árvore
void imprime_arestas(ast_t *arvore);

void imprime_tipo_semantico(tipos_semanticos_t t);

//Não consegui mover para instr.h/instr.c, entao fica aqui por enquanto
//Só concatena o código gerado pelos parametros e coloca no nodo de chamada de funcao.
//Ainda falta fazer os jumps, inicializar rpf e etc.

//Precisa fazer o store no escopo atual ainda!
code_t *cod_prepara_chamada_funcao(ast_t *parametros);

#endif //_AST_H_
