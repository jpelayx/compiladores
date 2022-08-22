#ifndef _PILHA_H_
#define _PILHA_H_

//Implementar o escopo como uma pilha.
#include "tabela_simbolos.h"

//Declarei tamanho arbitrario
#define TAMANHO_MAX 13

// typedef struct{
//     int tamanho_atual;
//     tabela_simbolos_t tabelas[TAMANHO_MAX];
// } pilha;

typedef struct pilha_escopo
{
    tabela_simbolos_t *t;
    struct pilha_escopo *anterior;
} pilha_t;


pilha_t* inicializa_pilha();

// tabela_simbolos_t* retorna_topo_pilha(pilha_t* pilha);
tabela_simbolos_t * topo(pilha_t *p);

//Push
pilha_t* entra_escopo( pilha_t* pilha, tabela_simbolos_t* tabela);

pilha_t* novo_escopo(pilha_t *p);

//Pop
pilha_t* sai_escopo();

// adiciona simbolo no escopo no topo da pilha
pilha_t * adiciona_simbolo(pilha_t *p, simbolo_t *s);

// adiciona os simbolos retirados da ast com o tipo especificado 
pilha_t *adiciona_lista_simbolos(pilha_t *p, ast_t *t, tipos_semanticos_t tipo);

// se nao houverem erros, retorna uma referencia ao simbolo referenciado. 
simbolo_t *referencia(pilha_t *p, valor_token_t *v, tipos_simbolos_t natureza);

//Usar essa ideia aqui para procurar por variaveis em diferentes escopos
void percorre_escopo();

// se achou o identificador retorna o ponteiro para o simbolo 
// senao retorna NULL
simbolo_t* procura_nome_em_todas_tabelas(pilha_t *p, char *nome);

void erro_nao_declaracao(char *nome, int linha);

//Imprime mensagens de erro e sai do programa com código adequado
void erro_redeclaracao(char *nome, int linha_redeclaracao, int linha_original);

void erro_uso_incorreto(char *nome, int linha, tipos_simbolos_t tipo, tipos_simbolos_t tipo_original);

// verifica que o tipo da arvore t é compativel com o tipo esperado s
void verifica_tipos(ast_t *t, tipos_semanticos_t s);

// infere o tipo a partir da combinação dos tipos de t1 e t2 
tipos_semanticos_t infere_tipo(ast_t *t1, ast_t *t2);

#endif // _PILHA_H_