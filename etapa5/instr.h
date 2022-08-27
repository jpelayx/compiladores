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

lista_instr_t * insere_lista_instr(lista_instr_t *l, instr_t *i);


lista_instr_t * concatena_lista_instr(lista_instr_t *head, lista_instr_t *tail);

lista_instr_t * primeiro_item(lista_instr_t *l);

#endif // _INSTR_H_