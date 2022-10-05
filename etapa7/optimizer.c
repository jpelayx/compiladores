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

    start = otimizacao_janela(start);

    return get_code(start);

}

opt_code_t *otimizacao_janela(opt_code_t *start)
{
    opt_code_t *oc = start;
    while(oc != NULL)
    {
        // coloca aqui as otimizacoes 
        oc = operacao_com_imediato(oc);
        oc = oc->next;
    }
    return start;
}

opt_code_t *operacao_com_imediato(opt_code_t *oc)
{
    // loadI c => r1 
    // op r1, r2 => r3
    // vira:
    // opI r2, c => r3
    if(oc == NULL)
        return oc;
    
    instr_t *i = oc->i;
    
    if(i->opcode != ILOC_loadI)
        return oc;
    
    if(oc->next == NULL)
        return oc;
    
    instr_t *j = oc->next->i;
    int op_idx = operando_em_instr(j, i->op1);
    if(op_idx == -1 || op_idx == 2)
        return oc;

    instr_t *new_j = calloc(1, sizeof(instr_t)); 
    switch (j->opcode)
    {
    case ILOC_add:
        new_j->opcode = ILOC_addI;
        new_j->op0 = op_idx == 0 ? j->op1 : j->op0;
        new_j->op1 = i->op0;
        new_j->op2 = j->op2;
        new_j->comment = j->comment;
        new_j->label = j->label;
        break;
    case ILOC_sub:
        new_j->opcode = op_idx == 0 ? ILOC_rsubI : ILOC_subI;
        new_j->op0 = op_idx == 0 ? j->op1 : j->op0;
        new_j->op1 = i->op0;
        new_j->op2 = j->op2;
        new_j->comment = j->comment;
        new_j->label = j->label;
        break;
    case ILOC_mult:
        new_j->opcode = ILOC_multI;
        new_j->op0 = op_idx == 0 ? j->op1 : j->op0;
        new_j->op1 = i->op0;
        new_j->op2 = j->op2;
        new_j->comment = j->comment;
        new_j->label = j->label;
        break;
    case ILOC_div:
        new_j->opcode = op_idx == 0 ? ILOC_rdivI : ILOC_divI;
        new_j->op0 = op_idx == 0 ? j->op1 : j->op0;
        new_j->op1 = i->op0;
        new_j->op2 = j->op2;
        new_j->comment = j->comment;
        new_j->label = j->label;
        break;
    default:
        new_j = j;
        break;
    }
    concatena_comentario(i->comment, new_j);
    oc->next = oc->next->next;
    oc->i = new_j;
    return oc;
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