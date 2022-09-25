#ifndef _ASSEMBLY_H_
#define _ASSEMBLY_H_

#include "instr.h"

void generateAsm(code_t *c);

typedef enum flag_traducao
{
    TRAD_NORMAL,
    TRAD_INICIO,
    TRAD_PROLOGO,
    TRAD_RETORNO,
    TRAD_CALL
} flag_traducao_t;

typedef struct escopo_registrador
{
    int num_regs;
    int *reg_area;
} escopo_registrador_t;

escopo_registrador_t *novo_escopo_registrador();

int adiciona_registrador(escopo_registrador_t *e, operando_instr_t *r);

int registrador_assembly(escopo_registrador_t *e,operando_instr_t *r);

void imprime_registrador_assembly(escopo_registrador_t *e,  operando_instr_t *r);

typedef struct pilha_escopo_registradores
{
    escopo_registrador_t *top;
    struct pilha_escopo_registradores *prev;
} pilha_escopo_registrador_t;


pilha_escopo_registrador_t *pop_pilha_registrador(pilha_escopo_registrador_t *p);
pilha_escopo_registrador_t *push_pilha_registrador(pilha_escopo_registrador_t *p, escopo_registrador_t *e);


flag_traducao_t traduz_instrucao(lista_instr_t *l, flag_traducao_t f);

flag_traducao_t traducao_inicio(instr_t *i);

flag_traducao_t traducao_direta(instr_t *i);

flag_traducao_t traducao_retorno(instr_t *i);

flag_traducao_t traducao_prologo(instr_t *i);

bool eh_declaracao_funcao(instr_t *i);
bool eh_sequencia_retorno(instr_t *i);

#endif // _ASSEMBLY_H_