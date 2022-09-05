#ifndef _TABELA_SIMBOLOS_H_
#define _TABELA_SIMBOLOS_H_

#include "errors.h"
#include "ast.h"

#include "stdlib.h"
#include "stdio.h"

#define INITIAL_SIZE 10 

typedef enum tipos_simbolo
{
    simbolo_variavel, 
    simbolo_vetor,
    simbolo_funcao, 
    simbolo_parametro,
    simbolo_literal
} tipos_simbolos_t;

// simbolo
typedef struct simbolo {
    int id;
    tipos_semanticos_t tipo;
    tipos_simbolos_t natureza;
    int tamanho;
    valor_token_t *valor_lexico;
} simbolo_t;

// cria novo simbolo vazio
simbolo_t *novo_simbolo();

void adiciona_valor_lexico(simbolo_t *s, valor_token_t *v);

// cria novo simbolo a partir de nodo da ast.
simbolo_t *novo_simbolo_de_nodo(ast_t *n);

// libera a memoria alocada pelo simbolo 
void libera_simbolo(simbolo_t *s);

void print_simbolo(simbolo_t *s);

void print_natureza(tipos_simbolos_t n);

// lista encadeada de simbolos
typedef struct lista_simbolos
{
    simbolo_t *simbolo;
    struct lista_simbolos *next;
} lista_simbolos_t;

// libera recursivamente memoria alocada em uma lista de simbolos
void libera_lista_simbolos(lista_simbolos_t *l);

// tabela hash de simbolos
typedef struct tabela_simbolos 
{
  lista_simbolos_t **dados;
  int tamanho;
  int proximo_id;
} tabela_simbolos_t;

// inicia a tabela com o tamanho inicial padrao INITIAL_SIZE
tabela_simbolos_t *init_tabela_simbolos(int offset);

void libera_tabela_simbolos(tabela_simbolos_t *t);

/* adiciona um simbolo à tabela. 
 * retorna t ou um ponteiro novo em caso de redimensionamento
 * da tabela hash. */
tabela_simbolos_t *insere_simbolo(tabela_simbolos_t *t, simbolo_t *s);

tabela_simbolos_t *insere_simbolo_com_offset(tabela_simbolos_t *t, simbolo_t *s, int offset);

bool compara_nome_simbolo(simbolo_t *s, char *nome);

// procura um simbolo na tabela por identificador
// retorna o ponteiro para o simbolo 
// e NULL se não achou
simbolo_t *busca(tabela_simbolos_t *t, char *nome);

int func_hash(tabela_simbolos_t *t, char* id);

// p/ debug
void print_tabela(tabela_simbolos_t *t);


#endif //_TABELA_SIMBOLOS_H_