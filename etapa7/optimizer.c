#include "optimizer.h"
#include "stdlib.h"

/* 
    OTIMIZACOES 
    REMOVER OPERACOES INUTEIS 
    s1 = s2 + 0
    s1 = s2 - 0
    s1 = s2 * 1
    s1 = s2 / 1
    
    INSTRUCOES ASSEMBLY     
    s1 = s2 + 1 --> INC 
    s1 = s2 - 1 --> DEC

    DIMINUICAO DE COMPLEXIDADE
    s1 = 2 * s2 --> s1 = s2 + s2 
    s1 = s2 / s2 --> s1 = 1
    s1 = s2 - s2  --> s1 = 0
    s1 = s2 * 0 --> s1 = 0
    s1 = imediato op imediato --> s1 = resultado
 */



code_t *optmize(code_t *c)
{    
    opt_code_t *start = load_code(c);

    return get_code(start);

}


void optimize_instr(lista_instr_t *li)
{
    // otimizacoes de uma unica instrucao e load do codigo pra estrutura 
    // de otimizacao (que eh encadeada pros dois lados) 
    while(instrucao_inutil(li->i))
        li = li->prev;
    while(li->prev != NULL)
    {
        if (instrucao_inutil(li->prev->i))
        {
            li->prev = li->prev->prev;
        }
        else
        {
            li = li->prev;
        }
    }
}

bool instrucao_inutil(instr_t *i)
{
    /*
    s1 = s2 + 0
    s1 = s2 - 0
    s1 = s2 * 1
    s1 = s2 / 1
    */
    if(i->opcode == ILOC_addI && i->op1->val == 0)
        return true;

    if(i->opcode == ILOC_subI && i->op1->val == 0)
        return true;
    
    if(i->opcode == ILOC_multI && i->op1->val == 1)
        return true;
    
    if(i->opcode == ILOC_divI && i->op1->val == 1)
        return true;
    
    return false;
}


opt_code_t *load_code(code_t *c)
{
    opt_code_t *oc = calloc(1, sizeof(opt_code_t));
    
    lista_instr_t *li = c->codigo;
    
    while(li != NULL)
    {
        if(oc->i == NULL)
            oc->i = li->i;
        else 
        {
            oc->prev = malloc(sizeof(opt_code_t));
            oc->prev->i = li->i;
            oc->prev->next = oc;
            oc->prev->prev = NULL;
            oc = oc->prev;
        }
        li = li->prev;
    }
    return oc; //inicio do codigo
}

code_t *get_code(opt_code_t *oc)
{
    code_t *c = calloc(1, sizeof(code_t));
    lista_instr_t *last = malloc(sizeof(lista_instr_t)),
                  *li;
    li = last;
    oc = fim(oc);
    
    while(oc != NULL)
    {
        li->i = oc->i;
        if(oc->prev != NULL)
        {
            li->prev = malloc(sizeof(lista_instr_t));
            li = li->prev;
        }
        else 
            li->prev = NULL;
        oc = oc->prev;
    }
    c->codigo = last;
    return c;
}

opt_code_t *fim(opt_code_t *oc)
{
    if(oc == NULL)
        return NULL;
    while(oc->next != NULL)
        oc = oc->next;
    return oc;
}

opt_code_t *inicio(opt_code_t *oc)
{
    if(oc == NULL)
        return NULL;
    while(oc->prev != NULL)
        oc = oc->prev;
    return oc;
}