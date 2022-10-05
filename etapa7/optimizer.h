#ifndef _OPTIMIZER_H_
#define _OPTIMIZER_H_

#include "instr.h"

code_t* optmize(code_t *c);

void optimize_instr(lista_instr_t *li);

bool instrucao_inutil(instr_t *i);

#endif // _OPTIMIZER_H_