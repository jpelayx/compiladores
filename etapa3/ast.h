#ifndef _AST_H_
#define _AST_H_

#include "valor_token.h"

// olhar https://www.inf.ufrgs.br/~schnorr/tutorial-bison-p2.html


// Para saber como printar o nodo da AST.
/*******Problemas*******
a)Onde se enquandra [] e palavras reservadas (if, return, while, ...)??!
b)Qual vai ser o tipo do VALOR_LEXICO deles?!
*/


typedef enum tipos_ast_nodo
{
	lista_funcao,
	lista_comando,
	lista_expressao,
	//comandos simples
	inicializacao,
	atribuicao,
	indexador_vetor,
	entrada_saida,
	chamada_funcao,
	shift,
	cmd_return,
	break_continue,
	cmd_if,
	cmd_for,
	cmd_while,
	//expressoes aritmeticas e logicas
	unario,
	binario,
	ternario
} tipos_nodo_t;

typedef struct ast {
	tipos_nodo_t tipo;
	valor_token_t *valor_lexico;
    	int num_filhos;
    	struct ast **filhos;    
} ast_t;

// Cria nó sem filhos
ast_t *cria_nodo(valor_token_t *valor_lexico, tipos_nodo_t tipo);

// Adiciona child como filho da tree
void insere_filho(ast_t *pai, ast_t *filho);

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

#endif //_AST_H_
