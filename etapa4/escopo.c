#include "escopo.h"


pilha* inicializa_pilha(){
    pilha* p = calloc(1, sizeof(pilha));
    p->tamanho_atual = 0;

    tabela_simbolos_t* escopo_global = init_tabela_simbolos();
    
    //Coloca o escopo global na pilha
    entra_escopo(escopo_global, p);

    return p;
    
}

tabela_simbolos_t* retorna_topo_pilha(pilha *pilha){
    //Se pilha é vazia, retorna NULL
    if(pilha->tamanho_atual == 0){
        return NULL;
    } else{
        return &pilha->tabelas[pilha->tamanho_atual-1];
    }
}

//Push
void entra_escopo(tabela_simbolos_t *tabela, pilha *pilha){
    if(pilha->tamanho_atual < TAMANHO_MAX){
        pilha->tabelas[pilha->tamanho_atual] = *tabela;
        tabela_simbolos_t* escopo_global = init_tabela_simbolos();
    }
}

//Pop
void sai_escopo(tabela_simbolos_t tabela, pilha *pilha){
    if(pilha->tamanho_atual > 1){
        pilha->tamanho_atual--;
    }
}

//Usar essa ideia aqui para procurar por variaveis em diferentes escopos
void percorre_escopos(pilha *pilha){
    int tamanho_original = pilha->tamanho_atual;
    while (pilha->tamanho_atual > 0){
        retorna_topo_pilha(pilha);
        pilha->tamanho_atual--;
    }

    pilha->tamanho_atual = tamanho_original;
}