#include "optimizer.h"
#include <stdlib.h>
#include <string.h>

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
    bool changed = true;
    while(changed)
    {
        changed = false;
        while(oc != NULL)
        {
            // coloca aqui as otimizacoes 
            oc = operacao_com_imediato(&changed, oc);
            oc = remove_instr_inutil(&changed, oc);
            // oc = remove_store_load(&changed, oc);
            oc = oc->next;
        }
        oc = start;
    }
    return start;
}

opt_code_t *remove_store_load(bool *changed, opt_code_t *oc)
{
    /* REMOVE INSTRUCOES DO TIPO
        storeAI r1 => rfp, n
        loadAI rfp, n => r2 
     */

    if (oc == NULL)
        return oc;
    if (oc->next == NULL )
        return oc;

    instr_t *i = oc->i, 
            *j = oc->next->i;
    if(i->opcode == ILOC_storeAI && j->opcode == ILOC_loadAI)
    {
        if(!operandos_iguais(i->op1, j->op0) || !operandos_iguais(i->op2, j->op1))
            return oc;
        if(j->comment != NULL && oc->next->next != NULL)
        {
            concatena_comentario(j->comment, oc->next->next->i);
        }
        if(j->label != NULL && oc->next->next != NULL)
        {
            instr_t *k = oc->next->next->i;
            if(k->label != NULL)
            {
                instr_t *nop_i = calloc(1, sizeof(instr_t));
                opt_code_t *nop = malloc(sizeof(opt_code_t));
                nop->i = nop_i;
                oc->next->next->prev = nop;
                nop->next = oc->next->next;
                oc->next->next = nop;
            }
            oc->next->next->i->label = j->label;
        }
        substitui_reg(oc->next->next, j->op2, i->op0);
        opt_code_t *aux = oc->next;
        oc->next->next->prev = oc;
        oc->next = oc->next->next;
        free(aux);
        *changed = true;
    }
    return oc;
}

opt_code_t *remove_instr_inutil(bool *changed, opt_code_t *oc)
{
   /* 
    REMOVER OPERACOES INUTEIS 
    s1 = s2 + 0
    s1 = s2 - 0
    s1 = s2 * 1
    s1 = s2 / 1
   */
    instr_t *i = oc->i;
    if (!instrucao_inutil(i))
        return oc;
    if(i->comment != NULL && oc->prev != NULL)
    {
        concatena_comentario(i->comment, oc->prev->i);
    }
    if(i->label != NULL && oc->next != NULL)
    {
        if(oc->next->i->label != NULL)
        {
            // adiciona NOP pra colocar a outra label 
            instr_t *l = calloc(1, sizeof(instr_t));
            opt_code_t *nop = malloc(sizeof(opt_code_t));
            nop->i = l;
            nop->prev = oc;
            nop->next = oc->next;
            oc->next->prev = nop;
            oc->next = nop;
        }
        oc->next->i->label = i->label;
    }
    operando_instr_t *old = i->op2, 
                     *new = i->op0;
    opt_code_t *it = oc->next;
    substitui_reg(it, old, new);
    if(oc->prev != NULL)
        oc->prev->next = oc->next;
    if(oc->next != NULL)
        oc->next->prev = oc->prev;
    it = oc->next;
    free(oc);
    *changed = true;
    return it;
}

bool instrucao_inutil(instr_t *i)
{
    if ((i->opcode == ILOC_addI || 
         i->opcode == ILOC_subI ||
         i->opcode == ILOC_rsubI  ) && 
        i->op1->val == 0)
        return true;
    if ((i->opcode == ILOC_multI || 
         i->opcode == ILOC_divI    ) && 
        i->op1->val == 1)
        return true;
    return false;
}

void substitui_reg(opt_code_t* it, operando_instr_t *old, operando_instr_t *new)
{   
    int op_idx;
    while(it != NULL)
    {
        op_idx = operando_em_instr(it->i, old);
        switch (op_idx)
        {
        case 0:
            it->i->op0 = new;
            break;
        case 1:
            it->i->op1 = new;
            break;
        case 2:
            it->i->op2 = new;
            break;
        default:
            break;
        }
        it = it->next;
    }
}


opt_code_t *operacao_com_imediato(bool *changed, opt_code_t *oc)
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
        break;
    case ILOC_sub:
        new_j->opcode = op_idx == 0 ? ILOC_rsubI : ILOC_subI;
        new_j->op0 = op_idx == 0 ? j->op1 : j->op0;
        new_j->op1 = i->op0;
        new_j->op2 = j->op2;
        break;
    case ILOC_mult:
        new_j->opcode = ILOC_multI;
        new_j->op0 = op_idx == 0 ? j->op1 : j->op0;
        new_j->op1 = i->op0;
        new_j->op2 = j->op2;
        break;
    case ILOC_div:
        new_j->opcode = op_idx == 0 ? ILOC_rdivI : ILOC_divI;
        new_j->op0 = op_idx == 0 ? j->op1 : j->op0;
        new_j->op1 = i->op0;
        new_j->op2 = j->op2;
        break;
    case ILOC_addI:
        new_j->opcode = ILOC_loadI;
        new_j->op0 = gera_imediato(j->op1->val + i->op0->val);
        new_j->op1 = j->op2;
        break;
    case ILOC_subI:
        new_j->opcode = ILOC_loadI;
        new_j->op0 = gera_imediato(i->op0->val - j->op1->val) ;
        new_j->op1 = j->op2;
        break;
    case ILOC_rsubI:
        new_j->opcode = ILOC_loadI;
        new_j->op0 = gera_imediato(j->op1->val - i->op0->val) ;
        new_j->op1 = j->op2;
        break;
    case ILOC_multI:
        new_j->opcode = ILOC_loadI;
        new_j->op0 = gera_imediato(j->op1->val * i->op0->val);
        new_j->op1 = j->op2;
        break;
    case ILOC_divI:
        new_j->opcode = ILOC_loadI;
        new_j->op0 = gera_imediato(i->op0->val / j->op1->val) ;
        new_j->op1 = j->op2;
        break;
    case ILOC_rdivI:
        new_j->opcode = ILOC_loadI;
        new_j->op0 = gera_imediato(j->op1->val / i->op0->val) ;
        new_j->op1 = j->op2;
        break;
    case ILOC_store:
    case ILOC_storeAI:
    case ILOC_storeAO:
        // char *flag = strdup("OPT_STORE_IMEDIATO");
        // if(i->comment == NULL || strstr(i->comment, flag) == NULL)
        //     concatena_comentario(flag, i);
        return oc;
    default:
        return oc;
        break;
    }
    new_j->comment = j->comment;
    new_j->label = j->label;
    concatena_comentario(i->comment, new_j);
    oc->next = oc->next->next;
    oc->next->prev = oc;
    oc->i = new_j;
    *changed = true;
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