#include "optimizer.h"

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
    lista_instr_t *li = c->codigo;

    optimize_instr(li);

    c->codigo = li;
    return c;

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
