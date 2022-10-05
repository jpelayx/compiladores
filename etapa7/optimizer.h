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


code_t* optmize(code_t *c);

void optimize_instr(lista_instr_t *li);

bool instrucao_inutil(instr_t *i);

#endif // _OPTIMIZER_H_