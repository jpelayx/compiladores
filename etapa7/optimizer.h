#ifndef _OPTIMIZER_H_
#define _OPTIMIZER_H_

#include "instr.h"

typedef struct opt_code
{
    instr_t *i;
    struct opt_code *prev, 
                    *next;
} opt_code_t;

opt_code_t *load_code(code_t *c);
code_t *get_code(opt_code_t *oc);

opt_code_t *fim(opt_code_t *oc);
opt_code_t *inicio(opt_code_t *oc);


code_t* optmize(code_t *c);

opt_code_t *otimizacao_janela(opt_code_t *start);

opt_code_t *operacao_com_imediato(bool *changed, opt_code_t *oc);

opt_code_t *simplificacoes_aritmeticas(bool *changed, opt_code_t *oc);

opt_code_t *remove_instr_inutil(bool *changed, opt_code_t *oc);
bool instrucao_inutil(instr_t *i);
void substitui_reg(opt_code_t* it, operando_instr_t *old, operando_instr_t *new);

opt_code_t *remove_store_load(bool *changed, opt_code_t *oc);

#endif // _OPTIMIZER_H_