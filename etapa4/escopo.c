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
    simbolo_t *os = busca(topo(p), s->valor_lexico->valor.cadeia_caracteres);
    if(os != NULL){
        //Já existe esse simbolo na tabela!
        erro_redeclaracao(
            s->valor_lexico->valor.cadeia_caracteres,
            s->valor_lexico->linha,
            os->valor_lexico->linha);
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

simbolo_t *procura_nome_em_todas_tabelas(pilha_t *p, char *nome){
    simbolo_t *s;
    while (p != NULL){
        s = busca(p->t, nome);
        if(s != NULL){
            return s;
        }
        p = p->anterior;
    }
    return s;
}

void verifica_erros(pilha_t *p, valor_token_t *v, tipos_simbolos_t tipo)
{
    simbolo_t *s = procura_nome_em_todas_tabelas(p, v->valor.cadeia_caracteres);
    if(s == NULL)
        erro_nao_declaracao(v->valor.cadeia_caracteres, v->linha);
    if(s->natureza != tipo)
        erro_uso_incorreto(v->valor.cadeia_caracteres, v->linha, tipo, s->natureza);

}

void erro_redeclaracao(char *nome, int linha_redeclaracao, int linha_original){
    printf("error: redeclaration of '%s' on line %d (first declared in line %d)\n", nome, linha_redeclaracao, linha_original);
    exit(ERR_DECLARED);
}


void erro_nao_declaracao(char *nome, int linha){
    printf("error: '%s' undeclared on line %d (first use in this scope)\n", nome, linha);
    exit(ERR_UNDECLARED);
}

void erro_uso_incorreto(char *nome, int linha, tipos_simbolos_t tipo, tipos_simbolos_t tipo_original)
{
    printf("error: incorrect use of ");
    print_natureza(tipo_original);
    printf(" \"%s\", accessed as a ", nome);
    print_natureza(tipo);
    printf(" on line %d\n", linha);
    switch (tipo)
    {
    case simbolo_parametro:
    case simbolo_literal:
    case simbolo_variavel:
        exit(ERR_VARIABLE);
    case simbolo_vetor:
        exit(ERR_VECTOR);
    case simbolo_funcao:
        exit(ERR_FUNCTION);
    }
}
