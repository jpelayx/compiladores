#ifndef _INSTR_H_
#define _INSTR_H_

#include <stdio.h>

typedef enum ILOC_opcode{
    ILOC_nop,
    //Aritmeticas  
    ILOC_add,
    ILOC_sub,
    ILOC_mult,
    ILOC_div,
    ILOC_addI,
    ILOC_subI,
    ILOC_rsubI,
    ILOC_multI,
    ILOC_divI,
    //Shifts
    ILOC_lshift,
    ILOC_lshiftI,
    ILOC_rshift,
    ILOC_rshiftI,
    //Loads
    ILOC_load,
    ILOC_loadAI,
    ILOC_loadA0,
    ILOC_loadI,
    //Stores
    ILOC_store,
    ILOC_storeAI,
    ILOC_storeAO,
    //Copy
    ILOC_i2i,
    //Fluxo de controle
    ILOC_cmp_LT,
    ILOC_cmp_LE,
    ILOC_cmp_EQ,
    ILOC_cmp_GE,
    ILOC_cmp_GT,
    ILOC_cmp_NE,
    ILOC_cbr,
    //Jumps
    jumpI,
    jump
} ILOC_op;

// operandos de instruções ILOC
typedef struct operando_instr 
{
    enum tipo_operando {registrador, label, imediato, rfp, rsp, rbss, rpc, buraco} tipo;
    unsigned int id;
    int val;
} operando_instr_t;

// libera a memoria alocada para um operando 
void libera_operando_instr(operando_instr_t *op);

// gera um id novo de registrador nao usado ainda
operando_instr_t* novo_registrador();

// gera um label novo nao usado ainda
operando_instr_t* novo_label();

void print_operando(operando_instr_t *op);

typedef struct lista_operando
{
    operando_instr_t * op;
    struct lista_operando *prev;
} lista_operando_t;


// estrutura instr para instruções ILOC
typedef struct instr
{
    ILOC_op opcode;
    operando_instr_t *op0, *op1, *op2, *label;
    
} instr_t ;

void libera_instr(instr_t *i);
 
instr_t * cria_instr(ILOC_op opcode, operando_instr_t *arg0, operando_instr_t *arg1, operando_instr_t *arg2);

typedef struct lista_instr
{
    instr_t *i;
    struct lista_instr * prev;
    
} lista_instr_t;

void libera_lista_instr(lista_instr_t *l);

// insere a instrução i no final da lista l
lista_instr_t * insere_lista_instr(lista_instr_t *l, instr_t *i);

// concatena as listas, retorna head:tail
lista_instr_t * concatena_lista_instr(lista_instr_t *head, lista_instr_t *tail);

// retorna o primeiro item da lista l
lista_instr_t * primeiro_item(lista_instr_t *l);

typedef struct code
{
    lista_instr_t *codigo;
    lista_operando_t *tl, *fl; 
} code_t ;

void remenda_true(operando_instr_t *r, code_t* c);

void remenda_false(operando_instr_t *r, code_t* c);

void insere_buraco_true(code_t *c, operando_instr_t *b);
void insere_buraco_false(code_t *c, operando_instr_t *b);

void insere_lista_buracos_true(code_t *c, lista_operando_t *bl);
void insere_lista_buracos_false(code_t *c, lista_operando_t *bl);

code_t *concatena_codigo(code_t *head, code_t *tail);

void imprime_codigo(code_t *c);

code_t *cod_load_literal(operando_instr_t *r, int n);

code_t *cod_load_variavel(operando_instr_t *r, int offset);

code_t *cod_inverte_sinal(operando_instr_t *src, operando_instr_t *dst);

code_t *cod_op_bin_aritmetica(operando_instr_t *src1, operando_instr_t *src2, operando_instr_t *dst, char op);
#endif // _INSTR_H_