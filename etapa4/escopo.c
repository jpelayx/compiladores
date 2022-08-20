#include "escopo.h"


pilha_t* inicializa_pilha()
{
    pilha_t *p = calloc(1, sizeof(pilha_t));
    tabela_simbolos_t *escopo_global = init_tabela_simbolos();
    p->anterior = NULL; // fundo da pilha 
    p->t = escopo_global;
    return p;
}

tabela_simbolos_t *topo(pilha_t *p)
{
    return p->t;
}

//Push
pilha_t* entra_escopo(pilha_t *p, tabela_simbolos_t *t){
    pilha_t *nt = calloc(1, sizeof(pilha_t));
    nt->anterior = p;
    nt->t = t;
    return nt;    
}

pilha_t *novo_escopo(pilha_t *p)
{
    pilha_t *nt = calloc(1, sizeof(pilha_t));
    nt->anterior = p;
    nt->t = init_tabela_simbolos();
    return nt;
}

//Pop
pilha_t* sai_escopo(pilha_t *p)
{
    pilha_t *nt = p->anterior;
    libera_tabela_simbolos(p->t);
    free(p);
    return nt;
}

pilha_t * adiciona_simbolo(pilha_t *p, simbolo_t *s)
{
    if(p == NULL)
        p = inicializa_pilha();
    if(busca(topo(p), s->valor_lexico->valor.cadeia_caracteres)){
        //Já existe esse simbolo na tabela!
        erro_redeclaracao(
            s->valor_lexico->valor.cadeia_caracteres,
            s->valor_lexico->linha);
    } else{
        insere_simbolo(topo(p), s);
    }
    return p;
}

//Usar essa ideia aqui para procurar por variaveis em diferentes escopos
// void percorre_escopos(pilha *pilha){
//     int tamanho_original = pilha->tamanho_atual;
//     while (pilha->tamanho_atual > 0){
//         retorna_topo_pilha(pilha);
//         pilha->tamanho_atual--;
//     }

//     pilha->tamanho_atual = tamanho_original;
// }

bool procura_nome_em_todas_tabelas(pilha_t *p, char *nome){
    while (p != NULL){
        if(busca(p->t, nome)){
            return true;
        }
        p = p->anterior;
    }
    return false;
}

void erro_nao_declaracao(char *nome, int linha){
    printf("error: '%s' undeclared on line %d (first use in this scope)\n", nome, linha);
    exit(ERR_DECLARED);
}

void verifica_erro_nao_declaracao(pilha_t *p, valor_token_t *v){
    //***Verifica se a variavel já foi declarada***
		if(!procura_nome_em_todas_tabelas(p, v->valor.cadeia_caracteres)){
			erro_nao_declaracao(v->valor.cadeia_caracteres, v->linha);
		} 
}
