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
    TRAD_EXPR_ARIT,
    TRAD_CALL,
    TRAD_CALL_EXPR
} flag_traducao_t;

typedef struct escopo_registrador
{
    int num_params;
    int num_regs;
    int *reg_area;
} escopo_registrador_t;

escopo_registrador_t *novo_escopo_registrador();

int adiciona_registrador(escopo_registrador_t *e, operando_instr_t *r);

int registrador_assembly(escopo_registrador_t *e,operando_instr_t *r);

void imprime_registrador_assembly_4(escopo_registrador_t *e,  operando_instr_t *r);
void imprime_registrador_assembly_4_ref(int reg_ref);
void imprime_registrador_assembly_16(escopo_registrador_t *e,  operando_instr_t *r);
void imprime_registrador_assembly_16_ref(int reg_ref);

typedef struct pilha_escopo_registradores
{
    escopo_registrador_t *top;
    struct pilha_escopo_registradores *prev;
} pilha_escopo_registrador_t;


pilha_escopo_registrador_t *pop_pilha_registrador(pilha_escopo_registrador_t *p);
pilha_escopo_registrador_t *push_pilha_registrador(pilha_escopo_registrador_t *p, escopo_registrador_t *e);


typedef struct acumulador 
{
    operando_instr_t *op;
    int deslocamento;
    struct acumulador *prev;
} acumulador_t;

acumulador_t *push_acumulador(acumulador_t *ac, operando_instr_t *op, int sp);
acumulador_t *pop_acumulador(acumulador_t *ac);

// retorna ac se op estava no acumulador, NULL cc.
acumulador_t *acesso_acumulador(acumulador_t *ac, operando_instr_t *op);  

typedef struct chamada
{
    char *nome;
    bool eh_expr;
    int num_regs;
    operando_instr_t *end_ret;
    struct chamada *prev;
} chamada_t;


flag_traducao_t traduz_instrucao(lista_instr_t *l, flag_traducao_t f);

flag_traducao_t traducao_inicio(instr_t *i);

flag_traducao_t traducao_direta(lista_instr_t *l);

flag_traducao_t traducao_retorno(instr_t *i);

flag_traducao_t traducao_prologo(instr_t *i);

flag_traducao_t traducao_call(instr_t *i, bool eh_expr);

flag_traducao_t traducao_expr_arit(instr_t *i, bool ignora_call);

// retorna o indice do acumulador na expresao (0: primeiro op, 1: segundo, 2: ambos)
int prepara_acumulador(int *arit_stack, acumulador_t **ac, operando_instr_t *op0, operando_instr_t *op1);

void traducao_salva_acumulador(int deslocamento);
void traducao_busca_acumulador(int deslocamento);
void traducao_carrega_acumulador(int *arit_stack, acumulador_t **ac, operando_instr_t *op);
void traducao_carrega_acumulador_stack(int *arit_stack, acumulador_t **ac, operando_instr_t *op);

void traducao_alocacao_stack(operando_instr_t *val);
void traducao_libera_stack();

void traducao_alocacao_var_global(char* identificador);

bool eh_declaracao_funcao(instr_t *i);
bool eh_sequencia_retorno(instr_t *i);
bool eh_chamada_funcao(instr_t *i);
bool eh_inicio_expr_arit(instr_t *i);
bool eh_fim_expr_arit(instr_t *i);

#endif // _ASSEMBLY_H_