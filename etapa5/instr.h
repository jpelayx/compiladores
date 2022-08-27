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
int novo_registrador();

// gera um label novo nao usado ainda
int novo_label();

// estrutura instr para instruções ILOC
typedef struct instr
{
    char *opcode;
    operando_instr_t *op0, *op1, *op2;
    unsigned int label;
    
} instr_t ;

typedef struct lista_instr
{
    instr_t *i;
    struct lista_instr * prev;
    
} lista_instr_t;



#endif // _INSTR_H_