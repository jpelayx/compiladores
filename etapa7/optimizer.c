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

    AVALIACAO DE OPERACOES COM CONSTANTES
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
            oc->i = simplificacao_algebrica(&changed, oc->i);
            oc = simplificacao_inc_dec(&changed, oc);
            oc = remove_jump_inutil(&changed, oc);
            oc = oc->next;
        }
        oc = start;
    }

    return start;
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
    if(oc->i->opcode != ILOC_loadI)
        return oc;    

    int tam_janela = 2;
    
    instr_t *i = oc->i,
            *j = NULL;
    opt_code_t *next = oc->next;
    bool remove_i = false, subs_j = false;
    for(int pos = 0; pos < tam_janela; pos++)
    {
        if (next == NULL)
            break;
        j = next->i;    
    
        int op_idx = operando_em_instr(j, i->op1);
        if(op_idx == 0 || op_idx == 1)
        {
            instr_t *new_j = calloc(1, sizeof(instr_t)); 
            subs_j = false;
            switch (j->opcode)
            {
            case ILOC_add:
                new_j->opcode = ILOC_addI;
                new_j->op0 = op_idx == 0 ? j->op1 : j->op0;
                new_j->op1 = i->op0;
                new_j->op2 = j->op2;
                subs_j = true;
                break;
            case ILOC_sub:
                new_j->opcode = op_idx == 0 ? ILOC_rsubI : ILOC_subI;
                new_j->op0 = op_idx == 0 ? j->op1 : j->op0;
                new_j->op1 = i->op0;
                new_j->op2 = j->op2;
                subs_j = true;
                break;
            case ILOC_mult:
                new_j->opcode = ILOC_multI;
                new_j->op0 = op_idx == 0 ? j->op1 : j->op0;
                new_j->op1 = i->op0;
                new_j->op2 = j->op2;
                subs_j = true;
                break;
            case ILOC_div:
                new_j->opcode = op_idx == 0 ? ILOC_rdivI : ILOC_divI;
                new_j->op0 = op_idx == 0 ? j->op1 : j->op0;
                new_j->op1 = i->op0;
                new_j->op2 = j->op2;
                subs_j = true;
                break;
            case ILOC_addI:
                new_j->opcode = ILOC_loadI;
                new_j->op0 = gera_imediato(j->op1->val + i->op0->val);
                new_j->op1 = j->op2;
                subs_j = true;
                break;
            case ILOC_subI:
                new_j->opcode = ILOC_loadI;
                new_j->op0 = gera_imediato(i->op0->val - j->op1->val) ;
                new_j->op1 = j->op2;
                subs_j = true;
                break;
            case ILOC_rsubI:
                new_j->opcode = ILOC_loadI;
                new_j->op0 = gera_imediato(j->op1->val - i->op0->val) ;
                new_j->op1 = j->op2;
                subs_j = true;
                break;
            case ILOC_multI:
                new_j->opcode = ILOC_loadI;
                new_j->op0 = gera_imediato(j->op1->val * i->op0->val);
                new_j->op1 = j->op2;
                subs_j = true;
                break;
            case ILOC_divI:
                new_j->opcode = ILOC_loadI;
                new_j->op0 = gera_imediato(i->op0->val / j->op1->val) ;
                new_j->op1 = j->op2;
                subs_j = true;
                break;
            case ILOC_rdivI:
                new_j->opcode = ILOC_loadI;
                new_j->op0 = gera_imediato(j->op1->val / i->op0->val) ;
                new_j->op1 = j->op2;
                subs_j = true;
                break;
            case ILOC_store:
            case ILOC_storeAI:
            case ILOC_storeAO:
                char *flag = malloc((19 + 10) * sizeof(char));
                sprintf(flag, "OPT_STORE_IMEDIATO %d", i->op0->val);
                if(j->comment == NULL || strstr(j->comment, flag) == NULL)
                    concatena_comentario(flag, j);
            default:
                break;
            }
            if(subs_j)
            {
                new_j->comment = j->comment;
                new_j->label = j->label;
                next->i = new_j;
                remove_i = true;
            }
            else 
                free(new_j);
        }
        next = next->next;
    }
    if(remove_i)
    {
        if(i->comment != NULL)
            realoca_comentario(oc);
        opt_code_t *aux = oc->next;
        if(oc->next != NULL)
            oc->next->prev = oc->prev;
        if(oc->prev != NULL)
            oc->prev->next = oc->next;    
        free(oc);
        *changed = true;
        return aux;
    }
    return oc;
}

void realoca_comentario(opt_code_t *oc)
{
    char *c = oc->i->comment;
    if( strstr(c, "EXPR_ARIT_END") != NULL && strstr(c, "EXPR_ARIT_START") != NULL)
        return;
    // move o comentario pra instrucao anterior
    if(strstr(c, "EXPR_ARIT_END") != NULL)
    {
        if(oc->prev == NULL)
            return;
        concatena_comentario(c, oc->prev->i);
    }
    else 
    {
        if(oc->next == NULL)
            return;
        concatena_comentario(c, oc->next->i);
    }
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

instr_t* simplificacao_algebrica(bool *changed, instr_t *i)
{
    if (i->opcode == ILOC_multI){
        if (i->op1->val == 2){
            i->opcode = ILOC_add;
            i->op1 = i->op0;
            *changed = true;
            return i;
        }
        if(i->op1->val == 0)
        {
            i->opcode = ILOC_loadI;
            i->op0 = i->op1;
            i->op1 = i->op2;
            *changed = true;
            return i;
        }
    }
    if(i->opcode == ILOC_sub && operandos_iguais(i->op0, i->op1))
    {
        i->opcode = ILOC_loadI;
        i->op0 = gera_imediato(0);
        i->op1 = i->op2;
        *changed = true;
        return i;
    }
    if(i->opcode == ILOC_div && operandos_iguais(i->op0, i->op1))
    {
        i->opcode = ILOC_loadI;
        i->op0 = gera_imediato(1);
        i->op1 = i->op2;
        *changed = true;
        return i;
    }
    return i;
}

opt_code_t *simplificacao_inc_dec(bool *changed, opt_code_t *oc)
{
    instr_t *i = oc->i;
    if(i->opcode == ILOC_addI && i->op1->val == 1)
    {
        char *flag = strdup("OPT_INC");
        if(i->comment == NULL || strstr(i->comment, flag) == NULL)
        {
            concatena_comentario(flag, i);
            *changed = true;
        }
        return oc;
    }
    if(i->opcode == ILOC_subI && i->op1->val == 1)
    {
        char *flag = strdup("OPT_DEC");
        if(i->comment == NULL || strstr(i->comment, flag) == NULL)
        {
            concatena_comentario(flag, i);
            *changed = true;
        }
        return oc;
    }
    return oc;
}

opt_code_t *remove_jump_inutil(bool *changed, opt_code_t *oc)
{
    instr_t *i, *j;
    i = oc->i;
    if(i->opcode != jumpI)
        return oc;
    if(oc->next == NULL)
        return oc;
    j = oc->next->i;    
    if(operandos_iguais(i->op0, j->label))
    {
        if(j->comment != NULL && strstr(j->comment, "FUNCTION") != NULL)
            return oc;
        if(i->label == NULL)
        {
            opt_code_t *aux = oc->next;
            if(oc->next != NULL)
                oc->next->prev  = oc->prev;
            if(oc->prev != NULL)
                oc->prev->next = oc->next;
            free(oc);
            *changed = true;
            return aux;
        }
    }
    return oc;
}