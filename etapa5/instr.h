#ifndef _INSTR_H_
#define _INSTR_H_

// operandos de instruções ILOC
typedef struct operando_instr 
{
    enum tipo_operando {registrador, imediato, rfp, rsp, rbss, rpc, buraco};
    unsigned int id;
} operando_instr_t;

// libera a memoria alocada para um operando 
void libera_operando_instr(operando_instr_t *op);

// gera um id novo de registrador nao usado ainda
unsigned int novo_registrador();

// gera um label novo nao usado ainda
unsigned int novo_label();

typedef struct lista_operando
{
    operando_instr_t * op;
    struct lista_operando *prev;
} lista_operando_t;


// estrutura instr para instruções ILOC
typedef struct instr
{
    char *opcode;
    operando_instr_t *op0, *op1, *op2;
    unsigned int label;
    
} instr_t ;

void libera_instr(instr_t *i);

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

void imprime_codigo(code_t *c);

#endif // _INSTR_H_