#include <string.h>
#include "tabela_simbolos.h"

simbolo_t *novo_simbolo()
{
    simbolo_t *s = calloc(1, sizeof(simbolo_t));
    return s;
}

simbolo_t *novo_simbolo_de_nodo(ast_t *n, tipos_semanticos_t tipo)
{
    simbolo_t *s = novo_simbolo();
    switch (n->tipo)
    {
    case identificador:
        s->natureza = simbolo_variavel;
        s->tamanho = 0;
        s->valor_lexico = calloc(1,sizeof(valor_token_t));
        memcpy(s->valor_lexico, n->valor_lexico, sizeof(valor_token_t));
        s->tipo = nda;
        break;
    case acesso_vetor:
        s->natureza = simbolo_vetor;
        s->tamanho = n->filhos[1]->valor_lexico->valor.inteiro;
        s->valor_lexico = calloc(1,sizeof(valor_token_t));
        memcpy(s->valor_lexico, n->filhos[0]->valor_lexico, sizeof(valor_token_t));
        s->tipo = nda;
        break;
    case declaracao:
        s->natureza = simbolo_variavel;
        s->tamanho = 0;
        s->valor_lexico = calloc(1,sizeof(valor_token_t));
        memcpy(s->valor_lexico, n->filhos[0]->valor_lexico, sizeof(valor_token_t));
        s->tipo = n->filhos[1]->tipo_sem;
        break;
    default:
        s->tipo = nda;
        break;
    }
    return s;
}

void libera_simbolo(simbolo_t *s)
{
    free(s);
}

void libera_lista_simbolos(lista_simbolos_t *l)
{
    if(l->next != NULL)
        libera_lista_simbolos(l->next);
    libera_simbolo(l->simbolo);
    free(l);
}

tabela_simbolos_t *init_tabela_simbolos()
{
    tabela_simbolos_t *t = calloc(1, sizeof(tabela_simbolos_t));
    t->proximo_id = 0;
    t->tamanho = INITIAL_SIZE;
    t->dados = calloc(INITIAL_SIZE, sizeof(lista_simbolos_t*));
    for(int i=0; i<INITIAL_SIZE; i++)
    {
        t->dados[i] = calloc(1, sizeof(lista_simbolos_t));
        t->dados[i]->simbolo = NULL; // desocupado
        t->dados[i]->next = NULL;
    }
    return t;
}

int func_hash(tabela_simbolos_t *t, int id)
{
    return id % t->tamanho; 
}

tabela_simbolos_t *insere_simbolo(tabela_simbolos_t *t, simbolo_t *s)
{
    if(t == NULL)
        t = init_tabela_simbolos();

    s->id = t->proximo_id;
    t->proximo_id++;
    int idx = func_hash(t, s->id);
    lista_simbolos_t *l = t->dados[idx];
    if(l->simbolo == NULL)
    {
        l->simbolo = s;
        return t;
    }

    while(l->next != NULL)
        l = l->next;
    l->next = calloc(1, sizeof(lista_simbolos_t));
    l->next->simbolo = s;
    l->next->next = NULL;

    // TODO: checar ocupação pra ver redimensionamento.

    return t;
}

void libera_tabela_simbolos(tabela_simbolos_t *t)
{
    for (int i=0; i<t->tamanho; i++)
        libera_lista_simbolos(t->dados[i]);
    free(t->dados);
    free(t);
}

void print_tabela(tabela_simbolos_t *t)
{
    printf("--- TABELA DE SIMBOLOS ---\n");
    for(int i=0; i<t->tamanho; i++)
    {
        lista_simbolos_t *l = t->dados[i];
        if(l->simbolo != NULL)
        {
            print_simbolo(l->simbolo);
            while(l->next != NULL)
            {
                l = l->next;
                print_simbolo(l->simbolo);
            }
        }
    }
}

void print_simbolo(simbolo_t *s)
{
    if(s->valor_lexico != NULL)
    {
        valor_token_t *v = s->valor_lexico;
        if(v->tipo == tk_identificador)
        {
            printf("- %s (", v->valor.cadeia_caracteres);
            print_natureza(s->natureza);
            printf(") : ");
            imprime_tipo_semantico(s->tipo);
            printf("\n");
        }
        else
            printf("- literal \n");
    }
    else 
    {
        printf("- simbolo sem valor lexico \n");
    }
}

void print_natureza(tipos_simbolos_t n)
{
    switch (n)
    {
    case simbolo_parametro:
    case simbolo_variavel:
        printf("variable");
        break;
    case simbolo_vetor:
        printf("vector");
        break;
    case simbolo_funcao:
        printf("function");
        break;
    case simbolo_literal:
        printf("literal");
        break;
    }
}

bool compara_nome_simbolo(simbolo_t *s, char *nome){
    if(s != NULL){
        //Verificar o nome do identificador!
        if(strcmp(nome, s->valor_lexico->valor.cadeia_caracteres) == 0){
            return true;
        }
    }
    return false;
}

simbolo_t * busca(tabela_simbolos_t *t, char *nome){
    for(int i=0; i<t->tamanho; i++)
    {
        lista_simbolos_t *l = t->dados[i];
        if(l->simbolo != NULL)
        {
            if(compara_nome_simbolo(l->simbolo, nome)){
                return l->simbolo;
            }
            while(l->next != NULL)
            {
                l = l->next;
                if(compara_nome_simbolo(l->simbolo, nome)){
                    return l->simbolo;
                }
            }
        }
    }
    return NULL;
}



