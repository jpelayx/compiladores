//Implementar o escopo como uma pilha.
#include "tabela_simbolos.h"

//Declarei tamanho arbitrario
#define TAMANHO_MAX 13

typedef struct{
    int tamanho_atual;
    tabela_simbolos_t tabelas[TAMANHO_MAX];
} pilha;

pilha* inicializa_pilha();

tabela_simbolos_t* retorna_topo_pilha(pilha* pilha);

//Push
void entra_escopo(tabela_simbolos_t* tabela, pilha* pilha);

//Pop
void sai_escopo();

//Usar essa ideia aqui para procurar por variaveis em diferentes escopos
void percorre_escopo();
