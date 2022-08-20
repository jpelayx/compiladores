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

//Usar essa ideia aqui para procurar por variaveis em diferentes escopos
void percorre_escopo();

// se achou o identificador retorna o ponteiro para o simbolo 
// senao retorna NULL
simbolo_t* procura_nome_em_todas_tabelas(pilha_t *p, char *nome);

// verifica a existencia de erros de nao declaracao e de uso incorreto
void verifica_erros(pilha_t *p, valor_token_t *v, tipos_simbolos_t tipo);

void erro_nao_declaracao(char *nome, int linha);

//Imprime mensagens de erro e sai do programa com código adequado
void erro_redeclaracao(char *nome, int linha_redeclaracao, int linha_original);

void erro_uso_incorreto(char *nome, int linha, tipos_simbolos_t tipo, tipos_simbolos_t tipo_original);

#endif // _PILHA_H_