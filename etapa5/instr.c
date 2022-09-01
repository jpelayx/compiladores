#include "instr.h"

#include <stdlib.h>
#include <stdio.h>

void libera_operando_instr(operando_instr_t *op)
{
    if(op != NULL)
        free(op);
}


operando_instr_t* novo_registrador()
{
    static unsigned int r = 0;

    operando_instr_t *new_r = (operando_instr_t*)malloc(sizeof(operando_instr_t));
    new_r->tipo = registrador;
    new_r->id = r;
    r++;
    return new_r;
}

operando_instr_t* novo_label()
{
    static unsigned int l = 0;
    operando_instr_t *new_l = (operando_instr_t*)malloc(sizeof(operando_instr_t));
    new_l->tipo = label;
    new_l->id = l;
    l++;
    return new_l;
}

void print_operando(operando_instr_t *op)
{
    switch (op->tipo)
    {
    case registrador:
        printf("r%d", op->id);
        break;
    case label:
        printf("L%d", op->id);
        break;
    case imediato:
        printf("%d", op->val);
        break;
    case rfp:
        printf("rfp");
        break;
    case rsp:
        printf("rsp");
        break;
    case rbss:
        printf("rbss");
        break;
    case rpc:
        printf("rpc");
        break;
    default:
        break;
    }
}

instr_t  *cria_instr(ILOC_op opcode, operando_instr_t *arg0, operando_instr_t *arg1, operando_instr_t *arg2){
    instr_t *instr = (instr_t *)malloc(sizeof(instr_t));

    instr->opcode = opcode;
    instr->op0 = arg0;
    instr->op1 = arg1;
    instr->op2 = arg2;
    instr->label = NULL;

    return instr;
}

void libera_instr(instr_t *i)
{
    if (i == NULL)
        return;
    libera_operando_instr(i->op0);
    libera_operando_instr(i->op1);
    libera_operando_instr(i->op2);
    free(i);
}

void libera_lista_instr(lista_instr_t *l)
{
    if(l == NULL)
        return;
    lista_instr_t *aux;
    do
    {
        aux = l->prev;
        libera_instr(l->i);
        free(l);
        l = aux;
    } while (l != NULL);
}

lista_instr_t * insere_lista_instr(lista_instr_t *l, instr_t *i)
{
    lista_instr_t *nl = (lista_instr_t*)malloc(sizeof(lista_instr_t)); 
    nl->i = i;
    nl->prev = l;
    return nl;
}

lista_instr_t * concatena_lista_instr(lista_instr_t *head, lista_instr_t *tail)
{
    lista_instr_t * ts = primeiro_item(tail);
    ts->prev = head;
    return tail;
}

lista_instr_t * primeiro_item(lista_instr_t *l)
{
    while(l != NULL && l->prev != NULL)
        l = l->prev;
    return l;
}

void remenda_true(operando_instr_t *r, code_t* c)
{
    operando_instr_t *b;
    lista_operando_t *l = c->tl;
    if (l == NULL)
        return;
    do
    {
        b = l->op;
        *(l->op) = *r;
        libera_operando_instr(b);       
    } while (l != NULL );
    free(c->tl);
}

void remenda_false(operando_instr_t *r, code_t* c)
{
    operando_instr_t *b;
    lista_operando_t *l = c->fl;
    if (l == NULL)
        return;
    do
    {
        b = l->op;
        *(l->op) = *r;
        libera_operando_instr(b);       
    } while (l != NULL );
    free(c->fl);
}

void insere_buraco_true(code_t *c, operando_instr_t *b)
{
    lista_operando_t *n = (lista_operando_t *)malloc(sizeof(lista_operando_t));
    n->op = b;
    n->prev = c->tl;
    c->tl = n;
}

void insere_buraco_false(code_t *c, operando_instr_t *b)
{
    lista_operando_t *n = (lista_operando_t *)malloc(sizeof(lista_operando_t));
    n->op = b;
    n->prev = c->fl;
    c->fl = n;
}

void insere_lista_buracos_true(code_t *c, lista_operando_t *bl)
{
    lista_operando_t *bs = bl;
    while(bs != NULL && bs->prev != NULL)
        bs = bs->prev;
    bs->prev = c->tl;
    c->tl = bl;
}
void insere_lista_buracos_false(code_t *c, lista_operando_t *bl)
{
    lista_operando_t *bs = bl;
    while(bs != NULL && bs->prev != NULL)
        bs = bs->prev;
    bs->prev = c->fl;
    c->fl = bl;
}

code_t *concatena_codigo(code_t *head, code_t *tail)
{
    code_t *c = (code_t*)malloc(sizeof(code_t));
    c->tl = NULL;
    c->fl = NULL;
    c->codigo = concatena_lista_instr(head->codigo, tail->codigo);
    return c;
}

void imprime_codigo(code_t *c)
{
    instr_t *i = c->codigo->i;

    if(i->label != NULL){
        print_operando(i->label);
        printf(": ");
    }
    printf("opcode %d ", i->opcode);
    if(i->op2 != NULL)
    {
        print_operando(i->op0);
        printf(", ");
        print_operando(i->op1);
        printf(" => ");
        print_operando(i->op2);
        printf("\n");
        return;
    }
    if(i->op1 != NULL)
    {
        print_operando(i->op0);
        printf(" => ");
        print_operando(i->op1);
        printf("\n");
        return;
    }
    if(i->op0 != NULL)
    {
        print_operando(i->op0);
        printf("\n");
        return;
    }
    printf("\n");
}

code_t *cod_load_literal(operando_instr_t *r, int n)
{
    // loadI n => r
    code_t *c = calloc(1, sizeof(code_t));
    c->codigo = calloc(1, sizeof(lista_instr_t));
    c->codigo->prev = NULL;
    c->codigo->i = calloc(1, sizeof(instr_t));
    c->codigo->i->opcode = ILOC_loadI;
    operando_instr_t *lit = calloc(1, sizeof(operando_instr_t));
    lit->tipo = imediato;
    lit->val = n;
    c->codigo->i->op0 = lit;
    c->codigo->i->op1 = r;

    return c;
}

code_t *cod_load_variavel(operando_instr_t *r, int offset)
{
    // loadAI rfp, offset => r
    code_t *c = calloc(1, sizeof(code_t));
    c->codigo = calloc(1, sizeof(lista_instr_t));
    c->codigo->prev = NULL;
    c->codigo->i = calloc(1, sizeof(instr_t));
    c->codigo->i->opcode = ILOC_loadAI;
    operando_instr_t *off = calloc(1, sizeof(operando_instr_t)), 
                     *frame = calloc(1, sizeof(operando_instr_t));
    off->tipo = imediato;
    off->val = offset;
    frame->tipo = rfp;
    c->codigo->i->op0 = frame;
    c->codigo->i->op1 = off;
    c->codigo->i->op2 = r;

    return c;

}

code_t *cod_op_bin_aritmetica(operando_instr_t *src1, operando_instr_t *src2, operando_instr_t *dst, char op)
{
    // OP src1, src2  => dst
    code_t *c = calloc(1, sizeof(code_t));
    c->codigo = calloc(1, sizeof(lista_instr_t));
    c->codigo->prev = NULL;
    c->codigo->i = calloc(1, sizeof(instr_t));
    switch (op)
    {
    case '+':
        c->codigo->i->opcode = ILOC_add;
        break;
    case '-':
        c->codigo->i->opcode = ILOC_sub;
        break;
    case '*':
        c->codigo->i->opcode = ILOC_mult;
        break;
    case '/':
        c->codigo->i->opcode = ILOC_div;
        break;
    default:
        break;
    }
    c->codigo->i->op0 = src1;
    c->codigo->i->op1 = src2;
    c->codigo->i->op2 = dst;

    return c;
}