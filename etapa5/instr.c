#include "instr.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

operando_instr_t* novo_buraco()
{
    operando_instr_t *new_b = (operando_instr_t*)malloc(sizeof(operando_instr_t));
    new_b->tipo = buraco;
    return new_b;
}

operando_instr_t* gera_imediato(int val)
{
    operando_instr_t *new_i = (operando_instr_t*)malloc(sizeof(operando_instr_t));
    new_i->tipo = imediato;
    new_i->val = val;
    return new_i;
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
    case buraco:
        printf("__");
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
    lista_operando_t *l = c->tl;
    if (l == NULL)
        return;
    do
    {
        memcpy(l->op, r, sizeof(operando_instr_t));
        l = l->prev;
    } while (l != NULL );
}

void remenda_false(operando_instr_t *r, code_t* c)
{
    lista_operando_t *l = c->fl;
    if (l == NULL)
        return;
    do
    {
        memcpy(l->op, r, sizeof(operando_instr_t));
        l = l->prev;
    } while (l != NULL );
}

void insere_buraco_true(code_t *c, operando_instr_t *b)
{
    lista_operando_t *n = (lista_operando_t *)calloc(1,sizeof(lista_operando_t));
    n->op = b;
    n->prev = c->tl;
    c->tl = n;
}

void insere_buraco_false(code_t *c, operando_instr_t *b)
{
    lista_operando_t *n = (lista_operando_t *)calloc(1,sizeof(lista_operando_t));
    n->op = b;
    n->prev = c->fl;
    c->fl = n;
}

void insere_lista_buracos_true(code_t *c, lista_operando_t *bl)
{
    if(bl == NULL)
        return;
    lista_operando_t *bs = bl;
    while(bs != NULL && bs->prev != NULL)
        bs = bs->prev;
    bs->prev = c->tl;
    c->tl = bl;
}
void insere_lista_buracos_false(code_t *c, lista_operando_t *bl)
{
    if(bl == NULL)
        return;
    lista_operando_t *bs = bl;
    while(bs != NULL && bs->prev != NULL)
        bs = bs->prev;
    bs->prev = c->fl;
    c->fl = bl;
}

void adiciona_label(operando_instr_t *l, code_t *c)
{
    lista_instr_t *inicio = primeiro_item(c->codigo);
    inicio->i->label = l;
}

code_t *concatena_codigo(code_t *head, code_t *tail)
{
    if(head == NULL && tail == NULL)
        return NULL;
    if(head == NULL)
        return tail;
    if(tail == NULL)
        return head;
    code_t *c = (code_t*)calloc(1,sizeof(code_t));
    c->codigo = concatena_lista_instr(head->codigo, tail->codigo);
    return c;
}

void imprime_codigo(code_t *c)
{
    printf("-------\n");
    imprime_lista_intrucao(c->codigo);
    printf("-------\n");
}

void imprime_lista_intrucao(lista_instr_t *li)
{
    if (li == NULL)
        return;
    imprime_lista_intrucao(li->prev);

    instr_t *i = li->i;
    if (i == NULL)
        return;
    if(i->label != NULL){
        print_operando(i->label);
        printf(": ");
    }
    imprime_opcode(i->opcode);
    if(i->opcode == ILOC_cbr      ||
       i->opcode == ILOC_storeAI  ||
       i->opcode == ILOC_storeAO    )
    {
        print_operando(i->op0);
        printf(" => ");
        print_operando(i->op1);
        printf(", ");
        print_operando(i->op2);
        printf("\n");
        return;
    } 
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

code_t *cod_store_variavel(operando_instr_t *r, int offset)
{
    // storeAI r => rfp, offset 
    code_t *c = calloc(1, sizeof(code_t));
    c->codigo = calloc(1, sizeof(lista_instr_t));
    c->codigo->prev = NULL;
    c->codigo->i = calloc(1, sizeof(instr_t));
    c->codigo->i->opcode = ILOC_storeAI;
    operando_instr_t *off = calloc(1, sizeof(operando_instr_t)), 
                     *frame = calloc(1, sizeof(operando_instr_t));
    off->tipo = imediato;
    off->val = offset;
    frame->tipo = rfp;
    c->codigo->i->op0 = r;
    c->codigo->i->op1 = frame;
    c->codigo->i->op2 = off;

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

code_t *cod_load_variavel_logica(int offset)
{
    // loadAI rfp, offset => temp
    // cbr temp => t, f
    code_t *c = calloc(1, sizeof(code_t));

    lista_instr_t *load = calloc(1, sizeof(lista_instr_t));
    load->i = calloc(1, sizeof(instr_t));
    load->i->opcode = ILOC_loadAI;
    operando_instr_t *off = calloc(1, sizeof(operando_instr_t)), 
                     *frame = calloc(1, sizeof(operando_instr_t)),
                     *temp = novo_registrador();
    off->tipo = imediato;
    off->val = offset;
    frame->tipo = rfp;
    load->i->op0 = frame;
    load->i->op1 = off;
    load->i->op2 = temp;

    lista_instr_t *cbr = calloc(1, sizeof(lista_instr_t));
    cbr->prev = load;
    cbr->i = calloc(1, sizeof(instr_t));
    cbr->i->opcode = ILOC_cbr;
    cbr->i->op0 = temp;
    operando_instr_t *t = novo_buraco(),
                     *f = novo_buraco();
    cbr->i->op1 = t; 
    cbr->i->op2 = f; 

    c->codigo = cbr;
    insere_buraco_true(c, t);
    insere_buraco_false(c, f);
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

code_t *cod_op_rel_logica(operando_instr_t *src1, operando_instr_t *src2, operando_instr_t *dst, char op)
{
    // cmp_OP src1, src2 -> dst
    // cbr dst -> t, f

    // comp
    lista_instr_t *comp = calloc(1, sizeof(lista_instr_t));
    comp->prev = NULL;
    comp->i = calloc(1, sizeof(instr_t));
    switch (op)
    {
    case 1:
        comp->i->opcode = ILOC_cmp_LT;
        break;
    case 2:
        comp->i->opcode = ILOC_cmp_LE;
        break;
    case 3:
        comp->i->opcode = ILOC_cmp_GT;
        break;
    case 4:
        comp->i->opcode = ILOC_cmp_GE;
        break;
    case 5:
        comp->i->opcode = ILOC_cmp_EQ;
        break;
    case 6:
        comp->i->opcode = ILOC_cmp_NE;
        break;
    default:
        break;
    }
    comp->i->op0 = src1;
    comp->i->op1 = src2;
    comp->i->op2 = dst;

    // branch
    code_t *cbr = calloc(1, sizeof(code_t));
    cbr->codigo = calloc(1, sizeof(lista_instr_t));
    cbr->codigo->prev = comp;
    cbr->codigo->i = calloc(1, sizeof(instr_t));
    cbr->codigo->i->opcode = ILOC_cbr;
    cbr->codigo->i->op0 = dst;
    operando_instr_t *t = novo_buraco(),
                     *f = novo_buraco();
    cbr->codigo->i->op1 = t;
    cbr->codigo->i->op2 = f;
    insere_buraco_true(cbr, t);
    insere_buraco_false(cbr, f);

    return cbr;
}

code_t *cod_op_bin_lit(char op)
{
    operando_instr_t *b = novo_buraco();
    code_t *c = calloc(1, sizeof(code_t));
    c->codigo = calloc(1, sizeof(lista_instr_t));
    c->codigo->prev = NULL;
    c->codigo->i = calloc(1, sizeof(instr_t));
    c->codigo->i->opcode = jumpI;
    c->codigo->i->op0 = b;
    if(op == 't')
        insere_buraco_true(c, b);
    else
        insere_buraco_false(c, b);
    return c;
}

code_t *cod_load_parametro(operando_instr_t *r, int offset)
{
    // storeAI r => rsp, offset
    code_t *c = calloc(1, sizeof(code_t));
    c->codigo = calloc(1, sizeof(lista_instr_t));
    c->codigo->i = calloc(1, sizeof(instr_t));
    c->codigo->i->opcode = ILOC_storeAI;
    operando_instr_t *sp = calloc(1, sizeof(operando_instr_t)),
                     *of = calloc(1, sizeof(operando_instr_t));
    sp->tipo = rsp;
    of->tipo = imediato;
    of->val = offset;
    c->codigo->i->op0 = r;
    c->codigo->i->op1 = sp;
    c->codigo->i->op2 = of;
    return c;
}

code_t *cod_jump_incondicional(operando_instr_t *l)
{
    code_t *c = calloc(1, sizeof(code_t));
    c->codigo = calloc(1, sizeof(lista_instr_t));
    c->codigo->i = calloc(1, sizeof(instr_t));
    c->codigo->i->opcode = jumpI;
    c->codigo->i->op0 = l;
    return c;
}

code_t *cod_nop()
{
    code_t *c = calloc(1, sizeof(code_t));
    c->codigo = calloc(1, sizeof(lista_instr_t));
    c->codigo->i = calloc(1, sizeof(instr_t));
    return c;
}

void imprime_opcode(ILOC_op op)
{
    switch (op)
    {
    case ILOC_nop :
		printf("nop ");
		break;
    case ILOC_add :
		printf("add ");
		break;
    case ILOC_sub :
		printf("sub ");
		break;
    case ILOC_mult :
		printf("mult ");
		break;
    case ILOC_div :
		printf("div ");
		break;
    case ILOC_addI :
		printf("addI ");
		break;
    case ILOC_subI :
		printf("subI ");
		break;
    case ILOC_rsubI :
		printf("rsubI ");
		break;
    case ILOC_multI :
		printf("multI ");
		break;
    case ILOC_divI :
		printf("divI ");
		break;
    case ILOC_lshift :
		printf("lshift ");
		break;
    case ILOC_lshiftI :
		printf("lshiftI ");
		break;
    case ILOC_rshift :
		printf("rshift ");
		break;
    case ILOC_rshiftI :
		printf("rshiftI ");
		break;
    case ILOC_load :
		printf("load ");
		break;
    case ILOC_loadAI :
		printf("loadAI ");
		break;
    case ILOC_loadA0 :
		printf("loadA0 ");
		break;
    case ILOC_loadI :
		printf("loadI ");
		break;
    case ILOC_store :
		printf("store ");
		break;
    case ILOC_storeAI :
		printf("storeAI ");
		break;
    case ILOC_storeAO :
		printf("storeAO ");
		break;
    case ILOC_i2i :
		printf("i2i ");
		break;
    case ILOC_cmp_LT :
		printf("cmp_LT ");
		break;
    case ILOC_cmp_LE :
		printf("cmp_LE ");
		break;
    case ILOC_cmp_EQ :
		printf("cmp_EQ ");
		break;
    case ILOC_cmp_GE :
		printf("cmp_GE ");
		break;
    case ILOC_cmp_GT :
		printf("cmp_GT ");
		break;
    case ILOC_cmp_NE :
		printf("cmp_NE ");
		break;
    case ILOC_cbr :
		printf("cbr ");
		break;
    case jumpI :
		printf("jumpI ");
		break;
    case jump :
		printf("jump ");
		break;
    }
}