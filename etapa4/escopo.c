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
    int linha = busca(topo(p), s->valor_lexico->valor.cadeia_caracteres);
    if(linha != -1){
        //Já existe esse simbolo na tabela!
        erro_redeclaracao(
            s->valor_lexico->valor.cadeia_caracteres,
            s->valor_lexico->linha,
            linha);
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

int procura_nome_em_todas_tabelas(pilha_t *p, char *nome){
    int l;
    while (p != NULL){
        l = busca(p->t, nome);
        if(l != -1){
            return l;
        }
        p = p->anterior;
    }
    return l;
}

void erro_redeclaracao(char *nome, int linha_redeclaracao, int linha_original){
    printf("error: redeclaration of '%s' on line %d (first declared in line %d)\n", nome, linha_redeclaracao, linha_original);
    exit(ERR_DECLARED);
}


void erro_nao_declaracao(char *nome, int linha){
    printf("error: '%s' undeclared on line %d (first use in this scope)\n", nome, linha);
    exit(ERR_UNDECLARED);
}

void verifica_erro_nao_declaracao(pilha_t *p, valor_token_t *v){
    //***Verifica se a variavel já foi declarada***
		if(!procura_nome_em_todas_tabelas(p, v->valor.cadeia_caracteres)){
			erro_nao_declaracao(v->valor.cadeia_caracteres, v->linha);
		} 
}
