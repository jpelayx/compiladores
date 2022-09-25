#include "assembly.h"
#include <string.h>
#include <stdlib.h>

pilha_escopo_registrador_t *escopo_reg;

void generateAsm(code_t *c)
{
    escopo_reg = malloc(sizeof(pilha_escopo_registrador_t));
    escopo_reg->prev = NULL;
    escopo_reg->top = novo_escopo_registrador();
    // inicio padrão 
    printf("\t.text\n");
    printf("\t.globl main\n");
    printf("\t.type main, @function\n");

    traduz_instrucao(c->codigo, TRAD_INICIO);
}


flag_traducao_t traduz_instrucao(lista_instr_t *l, flag_traducao_t f)
{
    if (l == NULL)
        return f;
    f = traduz_instrucao(l->prev, f);

    switch (f)
    {
    case TRAD_INICIO:
        f = traducao_inicio(l->i);
        return f;
    case TRAD_NORMAL:
        f = traducao_direta(l->i);
        return f;
    case TRAD_RETORNO:
        f = traducao_retorno(l->i);
        return f;
    case TRAD_PROLOGO:
        f = traducao_prologo(l->i);
        return f;
    default:
        printf("// tbd\n");
        break;
    }
    return f;
}


flag_traducao_t traducao_inicio(instr_t *i)
{
    // ignora as instrucoes iniciais até o primeiro jumpI (que é pra main)
    if(i->opcode != jumpI)
        return TRAD_INICIO;
    else
        return TRAD_NORMAL;
}

flag_traducao_t traducao_direta(instr_t *i)
{
    // traducao 1:1
    if(eh_declaracao_funcao(i))
    {
        // comentario: FUNCTION [nome da funcao]
        printf("%s:\n", i->comment + 9);
        printf("pushq %%rbp\n");
        printf("movq %%rsp, %%rbp\n");
        return TRAD_PROLOGO;
    }
    if(eh_sequencia_retorno(i))
    {
        printf("mov ");
        imprime_registrador_assembly(escopo_reg->top, i->op0);
        printf(", %%eax\n"); // retorno sempre pelo %eax
        return TRAD_RETORNO;
    }
    switch (i->opcode)
    {
	case ILOC_nop:
		printf("// traducao ILOC_nop\n");
		break;
	case ILOC_halt:
		printf("// traducao ILOC_halt\n");
		break;
	case ILOC_add:
		printf("// traducao ILOC_add\n");
		break;
	case ILOC_sub:
		printf("// traducao ILOC_sub\n");
		break;
	case ILOC_mult:
		printf("// traducao ILOC_mult\n");
		break;
	case ILOC_div:
		printf("// traducao ILOC_div\n");
		break;
	case ILOC_addI:
		printf("// traducao ILOC_addI\n");
		break;
	case ILOC_subI:
		printf("// traducao ILOC_subI\n");
		break;
	case ILOC_rsubI:
		printf("// traducao ILOC_rsubI\n");
		break;
	case ILOC_multI:
		printf("// traducao ILOC_multI\n");
		break;
	case ILOC_divI:
		printf("// traducao ILOC_divI\n");
		break;
	case ILOC_lshift:
		printf("// traducao ILOC_lshift\n");
		break;
	case ILOC_lshiftI:
		printf("// traducao ILOC_lshiftI\n");
		break;
	case ILOC_rshift:
		printf("// traducao ILOC_rshift\n");
		break;
	case ILOC_rshiftI:
		printf("// traducao ILOC_rshiftI\n");
		break;
	case ILOC_load:
		printf("// traducao ILOC_load\n");
		break;
	case ILOC_loadAI:
		printf("// traducao ILOC_loadAI\n");
		break;
	case ILOC_loadA0:
		printf("// traducao ILOC_loadA0\n");
		break;
	case ILOC_loadI:
        printf("movl $%d, ", i->op0->val);
        imprime_registrador_assembly(escopo_reg->top, i->op1);
        printf("\n");
		break;
	case ILOC_store:
		printf("// traducao ILOC_store\n");
		break;
	case ILOC_storeAI:
		printf("// traducao ILOC_storeAI\n");
		break;
	case ILOC_storeAO:
		printf("// traducao ILOC_storeAO\n");
		break;
	case ILOC_i2i:
		printf("// traducao ILOC_i2i\n");
		break;
	case ILOC_cmp_LT:
		printf("// traducao ILOC_cmp_LT\n");
		break;
	case ILOC_cmp_LE:
		printf("// traducao ILOC_cmp_LE\n");
		break;
	case ILOC_cmp_EQ:
		printf("// traducao ILOC_cmp_EQ\n");
		break;
	case ILOC_cmp_GE:
		printf("// traducao ILOC_cmp_GE\n");
		break;
	case ILOC_cmp_GT:
		printf("// traducao ILOC_cmp_GT\n");
		break;
	case ILOC_cmp_NE:
		printf("// traducao ILOC_cmp_NE\n");
		break;
	case ILOC_cbr:
		printf("// traducao ILOC_cbr\n");
		break;
	case jumpI:
		printf("// traducao jumpI\n");
		break;
	case jump:
		printf("// traducao jump\n");
		break;
	case comment:
        printf("// %s\n", i->comment);
		break;
    }
    return TRAD_NORMAL;
}

flag_traducao_t traducao_retorno(instr_t *i)
{
    if(i->opcode == jump)
    {
        printf("popq %%rbp\n");
        printf("ret\n");
        return TRAD_NORMAL;
    }
    return TRAD_RETORNO;
}

flag_traducao_t traducao_prologo(instr_t *i)
{
    int num_parametros = i->op1->val - REGISTRO_ATIVACAO_OFFSET - 4;
    if(num_parametros > 0)
        printf("add $%d, %%rsp\n", num_parametros);
    return TRAD_NORMAL;
}

bool eh_declaracao_funcao(instr_t *i)
{
    if(i->comment != NULL && strstr(i->comment, "FUNCTION") != NULL)
        return true;
    else 
        return false;
}

bool eh_sequencia_retorno(instr_t *i)
{
    if(i->comment != NULL && strstr(i->comment, "RETURN") != NULL)
        return true;
    else 
        return false;
}


escopo_registrador_t *novo_escopo_registrador()
{
    escopo_registrador_t *e = malloc(sizeof(escopo_registrador_t));
    e->num_regs = 0;
    e->reg_area = malloc(4*sizeof(int)); // cx, dx, ci, di
    return e;
}

int adiciona_registrador(escopo_registrador_t *e, operando_instr_t *r)
{
    if(e->num_regs > 3)
        e->reg_area = realloc(e->reg_area, sizeof(int) * (e->num_regs-3));

    e->reg_area[e->num_regs] = r->val;
    e->num_regs++;
    return e->num_regs - 1;
}

int registrador_assembly(escopo_registrador_t *e,operando_instr_t *r)
{
    for(int i=0; i < e->num_regs; i++)
        if(e->reg_area[i] == r->val)
            return i;
    return adiciona_registrador(e, r);
}

void imprime_registrador_assembly(escopo_registrador_t *e,  operando_instr_t *r)
{
    int reg_ref = registrador_assembly(e, r);
    switch (reg_ref)
    {
    case 0:
        printf("%%rcx");
        break;
    case 1:
        printf("%%rdx");
        break;
    case 2:
        printf("%%rci");
        break;
    case 3:
        printf("%%rdi");
        break;
    default: // spill
        printf("spill");
        break;
    }
    return;
}


pilha_escopo_registrador_t *pop_pilha_registrador(pilha_escopo_registrador_t *p)
{
    pilha_escopo_registrador_t *prev = p->prev;
    free(p->top->reg_area);
    free(p->top);
    free(p);
    return prev;
}
pilha_escopo_registrador_t *push_pilha_registrador(pilha_escopo_registrador_t *p, escopo_registrador_t *e)
{
    pilha_escopo_registrador_t *top = calloc(1, sizeof(pilha_escopo_registrador_t));
    top->top = e;
    top->prev = p;
    return top;
}