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

bool operandos_iguais(operando_instr_t *op0, operando_instr_t *op1)
{
    if (op0 == NULL)
        return op1 == NULL;
    if (op1 == NULL)
        return false;
    if(op0->tipo != op1->tipo)
        return false;
    if(op0->tipo == rsp  || 
       op0->tipo == rfp  || 
       op0->tipo == rbss ||
       op0->tipo == rpc    )
        return true;
    if(op0->tipo == registrador)
        return op0->id == op1->id;
    if(op0->tipo == imediato)
        return op0->val == op1->val;
    return false;
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

int num_linhas(code_t *c)
{
    int n = 0;
    if (c == NULL)
        return n;
    lista_instr_t *l = c->codigo;
    while(l != NULL)
    {
        n++;
        l = l->prev;
    }
    return n;
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

void adiciona_comentario(char *comentario, code_t *c)
{
    lista_instr_t *inicio = primeiro_item(c->codigo);
    if(inicio->i->comment != NULL)
    {
        size_t old = strlen(inicio->i->comment),
               new = strlen(comentario);
        inicio->i->comment = realloc(inicio->i->comment, old + new + 1);
        inicio->i->comment = strcat(inicio->i->comment, ",");
        inicio->i->comment = strcat(inicio->i->comment, comentario);
    }
    else
        inicio->i->comment = comentario;
}

void adiciona_comentario_fim(char *comentario, code_t *c)
{
    lista_instr_t *inicio = c->codigo;
    if(inicio->i->comment != NULL)
    {
        size_t old = strlen(inicio->i->comment),
               new = strlen(comentario);
        inicio->i->comment = realloc(inicio->i->comment, old + new + 1);
        inicio->i->comment = strcat(inicio->i->comment, ",");
        inicio->i->comment = strcat(inicio->i->comment, comentario);
    }
    else
        inicio->i->comment = comentario;
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

void imprime_comentario(instr_t *i)
{
    if (i->comment != NULL)
        printf(" // %s", i->comment);
}

void imprime_codigo(code_t *c)
{
    imprime_lista_intrucao(c->codigo);
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
        imprime_comentario(i);
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
        imprime_comentario(i);
        printf("\n");
        return;
    }
    if(i->op1 != NULL)
    {
        print_operando(i->op0);
        printf(" => ");
        print_operando(i->op1);
        imprime_comentario(i);
        printf("\n");
        return;
    }
    if(i->op0 != NULL)
    {
        printf("=> ");
        print_operando(i->op0);
        imprime_comentario(i);
        printf("\n");
        return;
    }
    imprime_comentario(i);
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

code_t *cod_store_variavel(operando_instr_t *r, int offset, bool global)
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
    frame->tipo = global ? rbss : rfp;
    c->codigo->i->op0 = r;
    c->codigo->i->op1 = frame;
    c->codigo->i->op2 = off;

    return c;

}

code_t *cod_load_pilha(operando_instr_t *r, int offset)
{
    // loadAI (rfp | rsp), offset => r
    code_t *c = calloc(1, sizeof(code_t));
    c->codigo = calloc(1, sizeof(lista_instr_t));
    c->codigo->prev = NULL;
    c->codigo->i = calloc(1, sizeof(instr_t));
    c->codigo->i->opcode = ILOC_loadAI;
    operando_instr_t *off = calloc(1, sizeof(operando_instr_t)), 
                     *frame = calloc(1, sizeof(operando_instr_t));
    off->tipo = imediato;
    off->val = offset;
    frame->tipo = rsp;
    c->codigo->i->op0 = frame;
    c->codigo->i->op1 = off;
    c->codigo->i->op2 = r;

    return c;
}

code_t *cod_load_variavel(operando_instr_t *r, int offset, bool global)
{
    // loadAI (rfp | rsp), offset => r
    code_t *c = calloc(1, sizeof(code_t));
    c->codigo = calloc(1, sizeof(lista_instr_t));
    c->codigo->prev = NULL;
    c->codigo->i = calloc(1, sizeof(instr_t));
    c->codigo->i->opcode = ILOC_loadAI;
    operando_instr_t *off = calloc(1, sizeof(operando_instr_t)), 
                     *frame = calloc(1, sizeof(operando_instr_t));
    off->tipo = imediato;
    off->val = offset;
    frame->tipo = global ? rbss : rfp;
    c->codigo->i->op0 = frame;
    c->codigo->i->op1 = off;
    c->codigo->i->op2 = r;

    return c;
}

code_t *cod_load_variavel_logica(int offset, bool global)
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
    frame->tipo = global ? rbss : rfp;
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

code_t *cod_atribuicao_logica_var(int offset, code_t *cod_expr, bool global)
{
    operando_instr_t *lt = novo_label(),
                     *lf = novo_label(),
                     *fim = novo_label(),
                     *temp = novo_registrador();
    
    code_t *cod_true = cod_load_literal(temp, 1);
    cod_true = concatena_codigo(cod_true, cod_store_variavel(temp, offset, global));
    cod_true = concatena_codigo(cod_true, cod_jump_incondicional(fim));
    adiciona_label(lt, cod_true);
    code_t *cod_false = cod_load_literal(temp, 0);
    cod_false = concatena_codigo(cod_false, cod_store_variavel(temp, offset, global));
    cod_false = concatena_codigo(cod_false, cod_jump_incondicional(fim));
    adiciona_label(lf, cod_false);
    code_t *cod_fim = cod_nop();
    adiciona_label(fim, cod_fim);
    remenda_true(lt, cod_expr);
    remenda_false(lf, cod_expr);

    code_t *c = concatena_codigo(cod_expr, cod_true);
    c = concatena_codigo(c, cod_false);
    c = concatena_codigo(c, cod_fim);
    return c;
}

code_t *cod_atribuicao_logica_reg(operando_instr_t *reg, code_t *cod_expr)
{
    operando_instr_t *lt = novo_label(),
                     *lf = novo_label(),
                     *fim = novo_label();
    
    code_t *cod_true = cod_load_literal(reg, 1);
    cod_true = concatena_codigo(cod_true, cod_jump_incondicional(fim));
    adiciona_label(lt, cod_true);
    code_t *cod_false = cod_load_literal(reg, 0);
    cod_false = concatena_codigo(cod_false, cod_jump_incondicional(fim));
    adiciona_label(lf, cod_false);
    code_t *cod_fim = cod_nop();
    adiciona_label(fim, cod_fim);
    remenda_true(lt, cod_expr);
    remenda_false(lf, cod_expr);

    code_t *c = concatena_codigo(cod_expr, cod_true);
    c = concatena_codigo(c, cod_false);
    c = concatena_codigo(c, cod_fim);
    return c;
}

code_t *cod_funcao_prologo(int num_parametros)
{
    // i2i rsp => rfp 
    // addI rsp, n => rsp // n depende do numero de parametros 
    code_t *c = calloc(1, sizeof(code_t));

    lista_instr_t *i2i = calloc(1, sizeof(lista_instr_t));
    i2i->i = calloc(1, sizeof(instr_t));
    i2i->i->opcode = ILOC_i2i;
    operando_instr_t *sp = calloc(1, sizeof(operando_instr_t)),
                     *fp = calloc(1, sizeof(operando_instr_t));
    sp->tipo = rsp;
    fp->tipo = rfp;
    i2i->i->op0 = sp;
    i2i->i->op1 = fp;
    i2i->prev = NULL;

    lista_instr_t *addI = calloc(1, sizeof(lista_instr_t));
    addI->i = calloc(1, sizeof(instr_t));
    addI->i->opcode = ILOC_addI;
    operando_instr_t *n = calloc(1, sizeof(operando_instr_t));
    n->tipo = imediato;
    n->val = REGISTRO_ATIVACAO_OFFSET + num_parametros*4 + 4;
    addI->i->op0 = sp;
    addI->i->op1 = n;
    addI->i->op2 = sp;
    addI->prev = i2i;

    c->codigo = addI;
    return c;
}

code_t *cod_funcao_prologo_main()
{
    // i2i rfp => rsp 
    // addI rsp, 16 => rsp // usando o mesmo offset  
    // não me pergunta o porque :(
    code_t *c = calloc(1, sizeof(code_t));

    lista_instr_t *i2i = calloc(1, sizeof(lista_instr_t));
    i2i->i = calloc(1, sizeof(instr_t));
    i2i->i->opcode = ILOC_i2i;
    operando_instr_t *sp = calloc(1, sizeof(operando_instr_t)),
                     *fp = calloc(1, sizeof(operando_instr_t));
    sp->tipo = rsp;
    fp->tipo = rfp;
    i2i->i->op0 = fp;
    i2i->i->op1 = sp;
    i2i->prev = NULL;

    lista_instr_t *addI = calloc(1, sizeof(lista_instr_t));
    addI->i = calloc(1, sizeof(instr_t));
    addI->i->opcode = ILOC_addI;
    operando_instr_t *n = calloc(1, sizeof(operando_instr_t));
    n->tipo = imediato;
    n->val = REGISTRO_ATIVACAO_OFFSET + 4;
    addI->i->op0 = sp;
    addI->i->op1 = n;
    addI->i->op2 = sp;
    addI->prev = i2i;

    c->codigo = addI;
    return c;
}

code_t *cod_funcao_epilogo(operando_instr_t *ret)
{
    // storeAI ret => rfp, 12 // se ret == NULL
    // loadAI rfp, 0 => t0 // endereco de retorno  
    // loadAI rfp, 4 => t1 // rsp
    // loadAI rfp, 8 => t2 // rfp
    // i2i t1 => rsp 
    // i2i t2 => rfp
    // jump => t0

    code_t *c = calloc(1, sizeof(code_t));

    lista_instr_t *str_ret = calloc(1, sizeof(lista_instr_t));
	str_ret->i = calloc(1, sizeof(instr_t));
    str_ret->i->opcode = ILOC_storeAI;
    operando_instr_t *fp = calloc(1, sizeof(operando_instr_t)),
                     *i12 = gera_imediato(12);
    fp->tipo = rfp;
    str_ret->i->op0 = ret;
    str_ret->i->op1 = fp;
    str_ret->i->op2 = i12;
    str_ret->prev = NULL;
    str_ret->i->comment = strdup("RETURN");
    

    lista_instr_t *ld_end = calloc(1, sizeof(lista_instr_t));
	ld_end->i = calloc(1, sizeof(instr_t));
    ld_end->i->opcode = ILOC_loadAI;
    operando_instr_t *t0 = novo_registrador(),
                     *i0 = gera_imediato(0);
    ld_end->i->op0 = fp;
    ld_end->i->op1 = i0;
    ld_end->i->op2 = t0;
    ld_end->prev = (ret == NULL)? NULL : str_ret;

    lista_instr_t *ld_rsp = calloc(1, sizeof(lista_instr_t));
	ld_rsp->i = calloc(1, sizeof(instr_t));
    ld_rsp->i->opcode = ILOC_loadAI;
    operando_instr_t *t1 = novo_registrador(),
                     *i4 = gera_imediato(4);
    ld_rsp->i->op0 = fp;
    ld_rsp->i->op1 = i4;
    ld_rsp->i->op2 = t1;
    ld_rsp->prev = ld_end;

    lista_instr_t *ld_rfp = calloc(1, sizeof(lista_instr_t));
	ld_rfp->i = calloc(1, sizeof(instr_t));
    ld_rfp->i->opcode = ILOC_loadAI;
    operando_instr_t *t2 = novo_registrador(),
                     *i8 = gera_imediato(8);
    ld_rfp->i->op0 = fp;
    ld_rfp->i->op1 = i8;
    ld_rfp->i->op2 = t2;
    ld_rfp->prev = ld_rsp;

    lista_instr_t *i2_rsp = calloc(1, sizeof(lista_instr_t));
	i2_rsp->i = calloc(1, sizeof(instr_t));
    i2_rsp->i->opcode = ILOC_i2i;
    operando_instr_t *sp = calloc(1, sizeof(operando_instr_t));
    sp->tipo = rsp;
    i2_rsp->i->op0 = t1;
    i2_rsp->i->op1 = sp;
    i2_rsp->prev = ld_rfp;

    lista_instr_t *i2_rfp = calloc(1, sizeof(lista_instr_t));
	i2_rfp->i = calloc(1, sizeof(instr_t));
    i2_rfp->i->opcode = ILOC_i2i;
    i2_rfp->i->op0 = t2;
    i2_rfp->i->op1 = fp;
    i2_rfp->prev = i2_rsp;

    lista_instr_t *jump_end = calloc(1, sizeof(lista_instr_t));
	jump_end->i = calloc(1, sizeof(instr_t));
    jump_end->i->opcode = jump;
    jump_end->i->op0 = t0;
    jump_end->prev = i2_rfp;

    c->codigo = jump_end;
    return c;
}

code_t *cod_chamada_func_antes(int retorno, int num_parametros)
{
    // addI rpc, ret => t0  
    // storeAI t0 => rsp, 0
    // storeAI rsp => rsp, 4
    // storeAI rfp => rsp, 8
    code_t *c = calloc(1, sizeof(code_t));

    lista_instr_t *calc_ret = calloc(1, sizeof(lista_instr_t));
	calc_ret->i = calloc(1, sizeof(instr_t));
    calc_ret->i->opcode = ILOC_addI;
    operando_instr_t *pc = calloc(1, sizeof(operando_instr_t)),
                     *ret = calloc(1, sizeof(operando_instr_t)),
                     *t0 = novo_registrador();
    pc->tipo = rpc;
    ret->tipo = imediato;
    ret->val = retorno;
    calc_ret->i->op0 = pc;
    calc_ret->i->op1 = ret;
    calc_ret->i->op2 = t0;
    calc_ret->prev = NULL;

    lista_instr_t *store_ret = calloc(1, sizeof(lista_instr_t));
	store_ret->i = calloc(1, sizeof(instr_t));
    store_ret->i->opcode = ILOC_storeAI;
    operando_instr_t *sp = calloc(1, sizeof(operando_instr_t)), 
                     *i0 = calloc(1, sizeof(instr_t));
    sp->tipo = rsp;
    i0->tipo = imediato;
    i0->val = 0;
    store_ret->i->op0 = t0;
    store_ret->i->op1 = sp;
    store_ret->i->op2 = i0;
    store_ret->prev = calc_ret;

    lista_instr_t *store_rsp = calloc(1, sizeof(lista_instr_t));
	store_rsp->i = calloc(1, sizeof(instr_t));
    store_rsp->i->opcode = ILOC_storeAI;
    operando_instr_t *i4 = calloc(1, sizeof(instr_t));
    i4->tipo = imediato;
    i4->val = 4;
    store_rsp->i->op0 = sp;
    store_rsp->i->op1 = sp;
    store_rsp->i->op2 = i4;
    store_rsp->prev = store_ret;
    
    lista_instr_t *store_rfp = calloc(1, sizeof(lista_instr_t));
	store_rfp->i = calloc(1, sizeof(instr_t));
    store_rfp->i->opcode = ILOC_storeAI;
    operando_instr_t *fp = calloc(1, sizeof(operando_instr_t)), 
                     *i8 = calloc(1, sizeof(instr_t));
    fp->tipo = rfp;
    i8->tipo = imediato;
    i8->val = 8;
    store_rfp->i->op0 = fp;
    store_rfp->i->op1 = sp;
    store_rfp->i->op2 = i8;
    store_rfp->prev = store_rsp;

    c->codigo = store_rfp;
    return c;
}

code_t *cod_init(code_t *cod_vars_globais, operando_instr_t *l, code_t *cod)
{
    // loadI 1024 => rfp
    // loadI 1024 => rsp
    // loadI len(cod + 4) => rbss
    // alocacoes de vars globais 
    // jumpI => l
    code_t *c = calloc(1, sizeof(code_t));
    printf("TA NO COD_INIT\n");

    operando_instr_t *fp = calloc(1, sizeof(operando_instr_t)),
                     *sp = calloc(1, sizeof(operando_instr_t)),
                     *bss = calloc(1, sizeof(operando_instr_t));
    fp->tipo = rfp;
    sp->tipo = rsp;
    bss->tipo = rbss;

    lista_instr_t *ld_rfp = calloc(1, sizeof(lista_instr_t));
    ld_rfp->i = calloc(1, sizeof(instr_t));
    ld_rfp->i->opcode = ILOC_loadI;
    ld_rfp->i->op0 = gera_imediato(1024);
    ld_rfp->i->op1 = fp;
    ld_rfp->prev = NULL;  

    lista_instr_t *ld_rsp = calloc(1, sizeof(lista_instr_t));
    ld_rsp->i = calloc(1, sizeof(instr_t));
    ld_rsp->i->opcode = ILOC_loadI;
    ld_rsp->i->op0 = gera_imediato(1024);
    ld_rsp->i->op1 = sp;
    ld_rsp->prev = ld_rfp;  

    //code_t * cod_vars = cod_alocacao_var_global(num_vars_globais);
    //Append com o codigo criado para as globais.


    lista_instr_t *ld_rbss = calloc(1, sizeof(lista_instr_t));
    ld_rbss->i = calloc(1, sizeof(instr_t));
    ld_rbss->i->opcode = ILOC_loadI;
    ld_rbss->i->op0 = gera_imediato(num_linhas(cod) + 5 + num_linhas(cod_vars_globais));
    ld_rbss->i->op1 = bss;
    ld_rbss->prev = ld_rsp;  

    c->codigo = ld_rbss;
    c = concatena_codigo(c, cod_vars_globais);
    if (l == NULL) // sem main 
    {
        ld_rbss->i->op0->val = 5;
        return concatena_codigo(c, cod_halt());
    }
    
    c = concatena_codigo(c, cod_jump_incondicional(l));
    return concatena_codigo(c, cod);
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

code_t *cod_alocacao_var_local(int num_vars)
{
    if(num_vars == 0)
        return NULL;

    code_t *c = calloc(1, sizeof(code_t));
    lista_instr_t *declaracoes = NULL,
                  *prev = NULL;
    operando_instr_t *sp = calloc(1, sizeof(operando_instr_t)),
                     *i4 = gera_imediato(4);
    sp->tipo = rsp;
    for(int i = 0; i<num_vars; i++)
    {
        prev = declaracoes;
        declaracoes = calloc(1, sizeof(instr_t)); 
        declaracoes->i = calloc(1, sizeof(instr_t));
        declaracoes->i->opcode = ILOC_addI;
        declaracoes->i->op0 = sp;
        declaracoes->i->op1 = i4;
        declaracoes->i->op2 = sp;
        declaracoes->prev = prev; 
    }
    c->codigo = declaracoes;
    return c;
}

code_t *cod_alocacao_var_global(char *identificador)
{
    code_t *c = calloc(1, sizeof(code_t));
    lista_instr_t *declaracoes = NULL,
                  *prev = NULL;
    operando_instr_t *bss = calloc(1, sizeof(operando_instr_t)),
                     *i4 = gera_imediato(4);
    bss->tipo = rbss;

    prev = declaracoes;
    declaracoes = calloc(1, sizeof(instr_t)); 
    declaracoes->i = calloc(1, sizeof(instr_t));
    declaracoes->i->opcode = ILOC_addI;
    declaracoes->i->op0 = bss;
    declaracoes->i->op1 = i4;
    declaracoes->i->op2 = bss;
    declaracoes->i->comment = identificador;
    declaracoes->prev = prev; 

    c->codigo = declaracoes;
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

code_t *cod_halt()
{
    code_t *c = calloc(1, sizeof(code_t));
    c->codigo = calloc(1, sizeof(lista_instr_t));
    c->codigo->i = calloc(1, sizeof(instr_t));
    c->codigo->i->opcode = ILOC_halt;
    return c;
}

void imprime_opcode(ILOC_op op)
{
    switch (op)
    {
    case ILOC_halt :
		printf("halt ");
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
    default:
        break;
    }
}