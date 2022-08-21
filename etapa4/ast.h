#ifndef _AST_H_
#define _AST_H_

#include "valor_token.h"

typedef enum tipo_semantico
{
	nda,
	int_sem,
	float_sem, 
	bool_sem, 
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
	literal
} tipos_nodo_t;

typedef struct ast {
	tipos_nodo_t tipo;           // tipo de nodo ast (literal, identificador, op binaria/unaria, etc)
	tipos_semanticos_t tipo_sem; // tipo semantico (float, int, bool, char ou string)
	valor_token_t *valor_lexico; 
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

// Adiciona nó filho
void insere_filho(ast_t *pai, ast_t *filho);

/* retorna uma lista head:tail (se head for NULL, retorna tail)
 * sendo que, uma lista de expressoes eh uma expressao com o ultimo filho
 * apontando para a proxima expressao etc. */
ast_t *insere_lista(ast_t *head, ast_t *tail);

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

#endif //_AST_H_
