#ifndef _INSTR_H_
#define _INSTR_H_

#include <stdio.h>
#include <stdbool.h>

#define REGISTRO_ATIVACAO_OFFSET 12

typedef enum ILOC_opcode{
    ILOC_nop,
    ILOC_halt,
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
    jump,
    comment
} ILOC_op;

void imprime_opcode(ILOC_op op);

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

// gera novo buraco
operando_instr_t* novo_buraco();

operando_instr_t* gera_imediato(int val);

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
    char *comment;
    
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

void imprime_lista_intrucao(lista_instr_t *li);

void imprime_comentario(instr_t *i);

typedef struct code
{
    lista_instr_t *codigo;
    lista_operando_t *tl, *fl; 
} code_t ;

int num_linhas(code_t *c);

void remenda_true(operando_instr_t *r, code_t* c);
void remenda_false(operando_instr_t *r, code_t* c);

void insere_buraco_true(code_t *c, operando_instr_t *b);
void insere_buraco_false(code_t *c, operando_instr_t *b);

void insere_lista_buracos_true(code_t *c, lista_operando_t *bl);
void insere_lista_buracos_false(code_t *c, lista_operando_t *bl);

void adiciona_label(operando_instr_t *l, code_t *c);

void adiciona_comentario(char *comentario, code_t *c);

code_t *concatena_codigo(code_t *head, code_t *tail);

void imprime_codigo(code_t *c);

code_t *cod_store_variavel(operando_instr_t *r, int offset, bool global);

code_t *cod_load_literal(operando_instr_t *r, int n);

code_t *cod_load_pilha(operando_instr_t *r, int offset);

code_t *cod_load_variavel(operando_instr_t *r, int offset, bool global);

code_t *cod_load_variavel_logica(int offset, bool global);

code_t *cod_op_bin_aritmetica(operando_instr_t *src1, operando_instr_t *src2, operando_instr_t *dst, char op);


/* op: 
 * 1: LT
 * 2: LE
 * 3: GT
 * 4: GE
 * 5: EQ
 * 6: NE  */
code_t *cod_op_rel_logica(operando_instr_t *src1, operando_instr_t *src2, operando_instr_t *dst, char op);

code_t *cod_op_bin_lit(char op);

code_t *cod_op_bin_logica(operando_instr_t *src1, operando_instr_t *src2, operando_instr_t *dst, char op);

code_t *cod_atribuicao_logica_var(int offset, code_t *cod_expr, bool global);

code_t *cod_atribuicao_logica_reg(operando_instr_t* reg, code_t *cod_expr);

code_t *cod_load_parametro(operando_instr_t *r, int offset);

code_t *cod_chamada_func_antes(int retorno, int num_parametros);

code_t *cod_funcao_prologo(int num_parametros);

code_t *cod_funcao_prologo_main();

code_t *cod_funcao_epilogo(operando_instr_t *ret);

code_t *cod_init(int num_vars_globais, operando_instr_t *l, code_t *cod);

code_t *cod_alocacao_var_local(int num_vars);

code_t *cod_alocacao_var_global(int num_vars);

code_t *cod_jump_incondicional(operando_instr_t *l);

code_t *cod_nop();

code_t *cod_halt();

#endif // _INSTR_H_