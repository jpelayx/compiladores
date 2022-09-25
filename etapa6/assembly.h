#ifndef _ASSEMBLY_H_
#define _ASSEMBLY_H_

#include "instr.h"

void generateAsm(code_t *c);

typedef enum flag_traducao
{
    TRAD_NORMAL,
    TRAD_INICIO,
    TRAD_RETORNO,
    TRAD_CALL
} flag_traducao_t;

void registrador_assembly(operando_instr_t *r);

flag_traducao_t traduz_instrucao(lista_instr_t *l, flag_traducao_t f);

flag_traducao_t traducao_inicio(instr_t *i);

flag_traducao_t traducao_direta(instr_t *i);

flag_traducao_t traducao_retorno(instr_t *i);

bool eh_declaracao_funcao(instr_t *i);
bool eh_sequencia_retorno(instr_t *i);

#endif // _ASSEMBLY_H_