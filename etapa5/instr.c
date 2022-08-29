#include "instr.h"

#include <stdlib.h>
#include <stdio.h>

void libera_operando_instr(operando_instr_t *op)
{
    if(op != NULL)
        free(op);
}


unsigned int novo_registrador()
{
    static unsigned int r = 0;
    unsigned int new_r = r;
    r++;
    return new_r;
}

unsigned int novo_label()
{
    static unsigned int l = 0;
    unsigned int new_l = l;
    l++;
    return new_l;
}

void libera_instr(instr_t *i)
{
    if (i == NULL)
        return;
    libera_operando_instr(i->op0);
    libera_operando_instr(i->op1);
    libera_operando_instr(i->op2);
    free(i->opcode);
    free(i);
}

void libera_lista_instr(lista_instr_t *l)
{
    if(l == NULL)
        return;
    lista_instr_t *aux;
    do
    {
        aux = l->prev;
        libera_instr(l);
        free(l);
        l = aux;
    } while (l != NULL);
}

lista_instr_t * insere_lista_instr(lista_instr_t *l, instr_t *i)
{
    lista_instr_t *nl = (lista_instr_t*)malloc(sizeof(lista_instr_t)); 
    nl->i = i;
    nl->prev = l;
    return nl;
}

lista_instr_t * concatena_lista_instr(lista_instr_t *head, lista_instr_t *tail)
{
    lista_instr_t * ts = primeiro_item(tail);
    ts->prev = head;
    return tail;
}

lista_instr_t * primeiro_item(lista_instr_t *l)
{
    while(l != NULL && l->prev != NULL)
        l = l->prev;
    return l;
}

void remenda_true(operando_instr_t *r, code_t* c)
{
    operando_instr_t *b;
    lista_operando_t *l = c->tl;
    if (l == NULL)
        return;
    do
    {
        b = l->op;
        *(l->op) = *r;
        libera_operando_instr(b);       
    } while (l != NULL );
    free(c->tl);
}

void remenda_false(operando_instr_t *r, code_t* c)
{
    operando_instr_t *b;
    lista_operando_t *l = c->fl;
    if (l == NULL)
        return;
    do
    {
        b = l->op;
        *(l->op) = *r;
        libera_operando_instr(b);       
    } while (l != NULL );
    free(c->fl);
}

void insere_buraco_true(code_t *c, operando_instr_t *b)
{
    lista_operando_t *n = (lista_operando_t *)malloc(sizeof(lista_operando_t));
    n->op = b;
    n->prev = c->tl;
    c->tl = n;
}

void insere_buraco_false(code_t *c, operando_instr_t *b)
{
    lista_operando_t *n = (lista_operando_t *)malloc(sizeof(lista_operando_t));
    n->op = b;
    n->prev = c->fl;
    c->fl = n;
}

void insere_lista_buracos_true(code_t *c, lista_operando_t *bl)
{
    lista_operando_t *bs = bl;
    while(bs != NULL && bs->prev != NULL)
        bs = bs->prev;
    bs->prev = c->tl;
    c->tl = bl;
}
void insere_lista_buracos_false(code_t *c, lista_operando_t *bl)
{
    lista_operando_t *bs = bl;
    while(bs != NULL && bs->prev != NULL)
        bs = bs->prev;
    bs->prev = c->fl;
    c->fl = bl;
}

// void imprime_codigo(code_t *c)
