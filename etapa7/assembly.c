#include "assembly.h"
#include <string.h>
#include <stdlib.h>

pilha_escopo_registrador_t *escopo_reg;

int stack_ctrl;

void generateAsm(code_t *c)
{
    escopo_reg = NULL;
    stack_ctrl = 0;
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
        f = traducao_direta(l);
        return f;
    case TRAD_RETORNO:
        f = traducao_retorno(l->i);
        return f;
    case TRAD_PROLOGO:
        f = traducao_prologo(l->i);
        return f;
    case TRAD_EXPR_ARIT:
        f = traducao_expr_arit(l->i, false);
        return f;
    case TRAD_CALL:
        f = traducao_call(l->i, false);
        return f;
    case TRAD_CALL_EXPR:
        f = traducao_call(l->i, true);
        return f;
	case TRAD_STORE_IMEDIATO_DIRETO:
        printf("-%d(", l->i->op2->val - REGISTRO_ATIVACAO_OFFSET);
        imprime_registrador_assembly_16(escopo_reg->top, l->i->op1);
		printf(")\n");
		return TRAD_NORMAL;
	case TRAD_STORE_IMEDIATO_EXPR:
        printf("-%d(", l->i->op2->val - REGISTRO_ATIVACAO_OFFSET);
        imprime_registrador_assembly_16(escopo_reg->top, l->i->op1);
		printf(")\n");
		return TRAD_EXPR_ARIT;
    default:
        printf("// tbd\n");
        break;
    }
    return f;
}

flag_traducao_t traducao_inicio(instr_t *i)
{
    // faz o print das declaracoes do segmento de dados (vars globais)
    if(i->opcode != jumpI){    
        if(i->op0->tipo == rbss && i->op2->tipo == rbss)
            traducao_alocacao_var_global(i->comment);
        return TRAD_INICIO;
    }
    else{
        return TRAD_NORMAL;
    }
}

flag_traducao_t traducao_direta(lista_instr_t *l)
{
	if(l->i->label != NULL){
			printf(".");
        	print_operando(l->i->label);
        	printf(": ");
			printf("\n");
    }
    // traducao 1:1
    if(eh_declaracao_funcao(l->i))
    {
        // comentario: FUNCTION [nome da funcao]
        printf("%s:\n", strstr(l->i->comment, "FUNCTION") + 9);
        printf("movq %%rsp, %%rbp\n");
        escopo_reg = push_pilha_registrador(escopo_reg, novo_escopo_registrador());
        return TRAD_PROLOGO;
    }
    if(eh_sequencia_retorno(l->i))
    {
        printf("movl ");
        imprime_registrador_assembly_4(escopo_reg->top, l->i->op0);
        printf(", %%eax\n"); // retorno sempre pelo %eax
        return TRAD_RETORNO;
    }
	if(eh_chamada_funcao(l->i) && eh_inicio_expr_arit(l->i))
		return traducao_call(l->i, false);
	if(eh_inicio_expr_arit(l->i))
		return traducao_expr_arit(l->i, false);
	if(eh_chamada_funcao(l->i))
		return traducao_call(l->i, false);

    switch (l->i->opcode)
    {
	case ILOC_nop:
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
        if(l->i->op0->tipo == rsp && l->i->op2->tipo == rsp)
            traducao_alocacao_stack(l->i->op1);
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
	case ILOC_rdivI:
		printf("// traducao ILOC_rdivI\n");
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
		printf("movl -%d(", l->i->op1->val - REGISTRO_ATIVACAO_OFFSET);
        imprime_registrador_assembly_16(escopo_reg->top, l->i->op0);
        printf("), ");
        imprime_registrador_assembly_4(escopo_reg->top, l->i->op2);
        printf("\n");
		break;
	case ILOC_loadA0:
		printf("// traducao ILOC_loadA0\n");
		break;
	case ILOC_loadI:
		if(eh_store_imediato(l->i))
		{
			printf("movl $%d, ", l->i->op0->val);
			return TRAD_STORE_IMEDIATO_DIRETO;
		}
        printf("movl $%d, ", l->i->op0->val);
        imprime_registrador_assembly_4(escopo_reg->top, l->i->op1);
        printf("\n");
		break;
	case ILOC_store:
		printf("// traducao ILOC_store\n");
		break;
	case ILOC_storeAI:
        printf("movl ");
        imprime_registrador_assembly_4(escopo_reg->top, l->i->op0);
        printf(", -%d(", l->i->op2->val - REGISTRO_ATIVACAO_OFFSET);
        imprime_registrador_assembly_16(escopo_reg->top, l->i->op1);
        printf(")\n");
		break;
	case ILOC_storeAO:
		printf("// traducao ILOC_storeAO\n");
		break;
	case ILOC_i2i:
		printf("// traducao ILOC_i2i\n");
		break;
	case ILOC_cmp_LT:
		//printf("// traducao ILOC_cmp_LT\n");
		break;
	case ILOC_cmp_LE:
		///printf("// traducao ILOC_cmp_LE\n");
		break;
	case ILOC_cmp_EQ:
		//printf("// traducao ILOC_cmp_EQ\n");
		break;
	case ILOC_cmp_GE:
		//printf("// traducao ILOC_cmp_GE\n");
		break;
	case ILOC_cmp_GT:
		//printf("// traducao ILOC_cmp_GT\n");
		break;
	case ILOC_cmp_NE:
		//printf("// traducao ILOC_cmp_NE\n");
		break;
	case ILOC_cbr:
		//IMPRIMIR OS REGISTRADORES CERTOS AQUI!!!!
		printf("cmpl ");
		imprime_registrador_assembly_4(escopo_reg->top, l->prev->i->op1);
		printf(", ");
		imprime_registrador_assembly_4(escopo_reg->top, l->prev->i->op0);
		printf("\n");
		
		switch (l->prev->i->opcode)
		{
		case ILOC_cmp_LT:
			printf("jge .");
			print_operando(l->i->op2);
			printf("\n");
			break;
		case ILOC_cmp_LE:
			printf("jg .");
			print_operando(l->i->op2);
			printf("\n");
			break;
		case ILOC_cmp_GT:
			printf("jle .");
			print_operando(l->i->op2);
			printf("\n");
			break;
		case ILOC_cmp_GE:
			printf("jl .");
			print_operando(l->i->op2);
			printf("\n");
			break;
		case ILOC_cmp_EQ:
			printf("jne .");
			print_operando(l->i->op2);
			printf("\n");
			break;
		case ILOC_cmp_NE:
			printf("je .");
			print_operando(l->i->op2);
			printf("\n");
			break;
		default:
			break;
		}
		printf("jmp .");
		print_operando(l->i->op1);
		printf("\n");
		break;
	case jumpI:
		//Verificar aqui se nao é jump para um funcao?
		//Se for simplesmente para um label, faz o jmp normal.
		printf("jmp .");
		print_operando(l->i->op0);
		printf("\n");
		break;
	case jump:
		printf("// traducao jump\n");
		break;
	case comment:
        printf("// %s\n", l->i->comment);
		break;
    }
    return TRAD_NORMAL;
}

flag_traducao_t traducao_retorno(instr_t *i)
{
    if(i->opcode == jump)
    {
        traducao_libera_stack();
		// printf("addq $%d, %%rsp\n", escopo_reg->top->num_params);
        printf("ret\n");
        escopo_reg = pop_pilha_registrador(escopo_reg);
        return TRAD_NORMAL;
    }
    return TRAD_RETORNO;
}

flag_traducao_t traducao_prologo(instr_t *i)
{
    int num_parametros = i->op1->val - REGISTRO_ATIVACAO_OFFSET - 4;
	num_parametros = num_parametros/4;
	escopo_reg->top->num_params = num_parametros;
	// salva os parametros passados por registradores na pilha
	for(int idx = 0; idx < num_parametros; idx++)
	{
    	printf("subq $4, %%rsp\n");
		stack_ctrl += 4;
    	printf("movl ");
		imprime_registrador_assembly_4_ref(idx); 
		printf(", -%d(%%rbp)\n", (idx+1)*4);
	}
    return TRAD_NORMAL;
}

flag_traducao_t traducao_call(instr_t *i, bool eh_expr)
{
	static chamada_t * call = NULL;
	bool ignora_call = false;
	if(eh_chamada_funcao(i)) // inicio: CALL [nome da funcao]
	{	
		
		chamada_t *c = malloc(sizeof(chamada_t));
		c->nome = strdup(strstr(i->comment, "CALL") + 5);
		char* end = strstr(c->nome, ",");
		if (end != NULL)
			end = 0;
		printf("// inicio da chamada de %s\n", c->nome);
		
		c->num_regs = escopo_reg->top->num_regs;
		c->num_params = 0;
		c->eh_expr = eh_expr;
		c->prev = call;
		call = c;

		// 1. salva sp e eax
		printf("pushq %%rsp\n");
		printf("pushq %%rbp\n");
		printf("pushq %%rax\n");
		// 2. salva registradores em uso na pilha
		escopo_registrador_t *regs_em_uso = escopo_reg->top;
		for (int idx=0; idx<regs_em_uso->num_regs; idx++)
		{
			printf("pushq ");
			imprime_registrador_assembly_16_ref(idx);
			printf("\n");
		}
		ignora_call = true;	
	}
	switch (i->opcode)
	{
	case ILOC_addI:
		if(i->op0->tipo == rpc) // ignora
		{
			call->end_ret = i->op2;
			break;
		}
		traducao_expr_arit(i, ignora_call);
		break;
	case ILOC_storeAI:
		if(i->op0->tipo == rsp)
			break;
		if(i->op0->tipo == rfp)
			break;
		if(operandos_iguais(i->op0, call->end_ret))
			break;
		if(i->op1->tipo == rsp && i->op2->val > 12)
		{
			// 3. salva parametros na pilha  
			// printf("movl ");
			// imprime_registrador_assembly_4(escopo_reg->top, i->op0);
			// printf(", ");
			// imprime_registrador_assembly_4_ref(call->num_params);
			// printf("\n");
			printf("pushq ");
			imprime_registrador_assembly_16(escopo_reg->top, i->op0);
			printf("\n");
			call->num_params++;
			break;
		}
		traducao_expr_arit(i, ignora_call);
	case jumpI:
		for(int idx = call->num_params-1; idx >= 0; idx--)
		{
			printf("popq ");
			imprime_registrador_assembly_16_ref(idx);
			printf("\n");
		}
		printf("call %s\n", call->nome);
		break;
	case ILOC_loadAI:
		if(i->op0->tipo == rsp && i->op1->val == 12)
		{
			// 4. libera registradores usados nos parametros 
			escopo_registrador_t *regs_em_uso = escopo_reg->top;
			regs_em_uso->num_regs = call->num_regs;

			// depois retorno 
			// 5. carrega valor do retorno (eax)
			printf("movl %%eax, ");
			imprime_registrador_assembly_4(escopo_reg->top, i->op2);
			printf("\n");

			// 6. pop dos registradores, rsp, rfp, rax
			for(int idx = regs_em_uso->num_regs-2; idx>=0; idx--)
			{
				printf("popq ");
				imprime_registrador_assembly_16_ref(idx);
				printf("\n");
			}
			// fim da chamada
			printf("popq %%rax\n");
			printf("popq %%rbp\n");
			printf("popq %%rsp\n");
			eh_expr = call->eh_expr;
			chamada_t *c = call->prev;
			free(call->nome);
			free(call);
			call = c;
			printf("// fim da chamada eh_expr = %d\n", eh_expr);
			return eh_expr ? TRAD_EXPR_ARIT : TRAD_NORMAL ;				
		}
	default:
		traducao_expr_arit(i, ignora_call);
	}
	return call->eh_expr ? TRAD_CALL_EXPR : TRAD_CALL;
}

flag_traducao_t traducao_expr_arit(instr_t *i, bool ignora_call)
{
	static acumulador_t *ac;
	static int num_regs;
	static int arit_stack;
	if(eh_inicio_expr_arit(i))
	{
		num_regs = escopo_reg->top->num_regs;
		ac = NULL;
		arit_stack = stack_ctrl; // topo da pilha no inicio da expr
		printf("// INICIO EXPR AR\n");
	}
	if(eh_chamada_funcao(i) && !ignora_call)
		return traducao_call(i, true);
	if(i->opcode == ILOC_loadAI || i->opcode == ILOC_loadI)
	{
		if(i->opcode == ILOC_loadAI)
		{
			printf("movl -%d(", i->op1->val - REGISTRO_ATIVACAO_OFFSET);
        	imprime_registrador_assembly_16(escopo_reg->top, i->op0);
        	printf("), ");
        	imprime_registrador_assembly_4(escopo_reg->top, i->op2);
        	printf("\n");
		}
		else 
		{
			printf("movl $%d, ", i->op0->val);
        	imprime_registrador_assembly_4(escopo_reg->top, i->op1);
        	printf("\n");
		}
	}
	else 
	{
		int ac_idx = prepara_acumulador(&arit_stack, &ac, i->op0, i->op1);
		switch (i->opcode)
		{
		case ILOC_add:
			printf("addl ");
			ac_idx == 0? 
				imprime_registrador_assembly_4(escopo_reg->top, i->op1) : 
				imprime_registrador_assembly_4(escopo_reg->top, i->op0) ;
			printf(", %%eax\n");
			break;
		case ILOC_addI:
			if(i->comment != NULL && strstr(i->comment, "OPT_INC") != NULL)
				printf("incl %%eax\n");
			else
				printf("addl $%d, %%eax\n", i->op1->val);
			break;
		case ILOC_sub:
			if (ac_idx == 0)
			{
				printf("subl ");
				imprime_registrador_assembly_4(escopo_reg->top, i->op1);
				printf(", %%eax\n");
			}
			else 
			{
				printf("negl %%eax\n");
				printf("addl ");
				imprime_registrador_assembly_4(escopo_reg->top, i->op0);
				printf(", %%eax\n");
			}
			break;
		case ILOC_subI:
			if(i->comment != NULL && strstr(i->comment, "OPT_DEC") != NULL)
				printf("decl %%eax\n");
			else
				printf("subl $%d, %%eax\n", i->op1->val);
			break;
		case ILOC_rsubI:
			printf("negl %%eax\n");
			printf("addl $%d, %%eax\n", i->op1->val);
			break;

		case ILOC_mult:
			printf("imull ");
			ac_idx == 0? 
				imprime_registrador_assembly_4(escopo_reg->top, i->op1) : 
				imprime_registrador_assembly_4(escopo_reg->top, i->op0) ;
			printf(", %%eax\n");
			break;
		case ILOC_multI:
			printf("imull $%d, %%eax\n", i->op1->val);
			break;
		case ILOC_div:
			printf("pushq %%rdx\n");
			if (ac_idx == 1)
			{
				// troca os operandos de registrador
				printf("pushq %%rax\n");
				printf("movl ");
				imprime_registrador_assembly_4(escopo_reg->top, i->op1);
				printf(", %%eax\n");
				printf("popq ");
				imprime_registrador_assembly_16(escopo_reg->top, i->op1);
				printf("\n");
			}
			// printf("cltd\n");
			printf("idivl ");
			imprime_registrador_assembly_4(escopo_reg->top, i->op1);
			printf("\n");
			printf("popq %%rdx\n");
			break;
		case ILOC_divI:

		default:
			printf("// missing translation: ");
			imprime_opcode(i->opcode);
			printf("\n");
			break;
		}
		ac->op = i->op2;
		
	}
	if(eh_fim_expr_arit(i))
	{
		if(arit_stack - stack_ctrl > 0)
			printf("addq $%d, %%rsp\n", arit_stack - stack_ctrl); // desalocando espaco na pilha
		// move o resultado pro temporario adequado 
		if(ac != NULL)
		{
			escopo_reg->top->num_regs = num_regs;
			printf("movl %%eax, ");
			imprime_registrador_assembly_4(escopo_reg->top, i->op2);
			printf("\n");
		}
		
		printf("// FIM EXPR AR\n");
		return TRAD_NORMAL;
	}
	else
		return TRAD_EXPR_ARIT;
}

int prepara_acumulador(int *arit_stack, acumulador_t **ac, operando_instr_t *op0, operando_instr_t *op1)
{
	acumulador_t *ac0 = acesso_acumulador(*ac, op0),
	             *ac1 = acesso_acumulador(*ac, op1);
	if(ac0 == NULL && ac1 == NULL)
	{
		traducao_carrega_acumulador(arit_stack, ac, op0); // nenhum dos operandos é o acumulador 
		return 0; // carregou o op0 
	}
	if(ac0 != NULL && ac1 == NULL)
	{
		if(ac0->deslocamento == -1) // esta no eax, alegria 
			return 0;

		// esta salvo na pilha
		// precisa salvar o conteudo do eax, e carregar da memoria
		traducao_carrega_acumulador_stack(arit_stack, ac, op0);
		return 0;
	}	
	if(ac0 == NULL && ac1 != NULL)
	{
		if(ac1->deslocamento == -1) // esta no eax, alegria 
			return 1;

		// esta salvo na pilha
		// precisa salvar o conteudo do eax, e carregar da memoria
		traducao_carrega_acumulador_stack(arit_stack, ac, op1);
		return 1;
	}	
	// os dois estao na pilha
	if(ac0->deslocamento == -1)
	{
		printf("movl -%d(%%rsp), ", ac1->deslocamento);
		imprime_registrador_assembly_4(escopo_reg->top, ac1->op);
		printf("\n");
		return 0;
	}
	if(ac1->deslocamento == -1)
	{
		printf("movl -%d(%%rsp), ", ac0->deslocamento);
		imprime_registrador_assembly_4(escopo_reg->top, ac0->op);
		printf("\n");
		return 1;
	}
	// um deve ser carregado para um registrador 
	printf("movl -%d(%%rsp), ", ac1->deslocamento);
	imprime_registrador_assembly_4(escopo_reg->top, ac1->op);
	printf("\n");
	// e o outro pro eax
	traducao_carrega_acumulador_stack(arit_stack, ac, op0);
	return 0;
}

void traducao_salva_acumulador(int deslocamento)
{
	printf("subq $4, %%rsp\n");
	printf("movl %%eax, -%d(%%rsp)\n", deslocamento); 
}

void traducao_busca_acumulador(int deslocamento)
{
	printf("movl -%d(%%rsp)\n", deslocamento);
}

void traducao_carrega_acumulador(int *arit_stack, acumulador_t **ac, operando_instr_t *op)
{
	if(*ac != NULL) 
	{
		// ja havia algo no acumulador, salvando na pilha para depois
		*arit_stack = *arit_stack + 4;
		traducao_salva_acumulador(*arit_stack - stack_ctrl);
	}
	*ac = push_acumulador(*ac, op, *arit_stack);
	printf("movl ");
	imprime_registrador_assembly_4(escopo_reg->top, op);
	printf(", %%eax\n");
}

void traducao_carrega_acumulador_stack(int *arit_stack, acumulador_t **ac, operando_instr_t *op)
{
	// ja havia algo no acumulador, salvando na pilha para depois
	*arit_stack = *arit_stack + 4;
	traducao_salva_acumulador(*arit_stack - stack_ctrl);

	acumulador_t *ac_ref = acesso_acumulador(*ac, op);
	printf("movl -%d(%%rsp), %%eax\n", ac_ref->deslocamento);
	*ac = push_acumulador(*ac, op, *arit_stack);
}

acumulador_t *push_acumulador(acumulador_t *ac, operando_instr_t *op, int sp)
{
	acumulador_t *a = malloc(sizeof(acumulador_t));
	a->prev = ac;
	a->op = op;
	a->deslocamento = -1; // esta no registrador eax
	if(ac != NULL)
		ac->deslocamento = sp - stack_ctrl;
	return a;
}

acumulador_t *pop_acumulador(acumulador_t *ac)
{
	acumulador_t *a = ac->prev;
	free(ac);
	return a;
}
acumulador_t *acesso_acumulador(acumulador_t *ac, operando_instr_t *op)
{
	while(ac != NULL)
	{
		if(operandos_iguais(ac->op, op))
			return ac;
		ac = ac->prev;
	}
	return NULL;
} 

void traducao_alocacao_stack(operando_instr_t *val)
{
    int v = val->val;
    stack_ctrl += v;
    printf("subq $%d, %%rsp\n", v);
}

void traducao_libera_stack()
{
    if(stack_ctrl > 0)
    {
        printf("addq $%d, %%rsp\n", stack_ctrl);
        stack_ctrl = 0;
    }
}

void traducao_alocacao_var_global(char* identificador){
    printf("\t.comm %s,4,4\n", identificador);
}

bool eh_declaracao_funcao(instr_t *i)
{
    return (i->comment != NULL && strstr(i->comment, "FUNCTION") != NULL);
}

bool eh_sequencia_retorno(instr_t *i)
{
    return (i->comment != NULL && strstr(i->comment, "RETURN") != NULL);
}

bool eh_inicio_expr_arit(instr_t *i)
{
    return (i->comment != NULL && strstr(i->comment, "EXPR_ARIT_START") != NULL);
}

bool eh_fim_expr_arit(instr_t *i)
{
    return (i->comment != NULL && strstr(i->comment, "EXPR_ARIT_END") != NULL);
}

bool eh_chamada_funcao(instr_t *i)
{
    return (i->comment != NULL && strstr(i->comment, "CALL") != NULL);
}

bool eh_store_imediato(instr_t *i)
{
    return (i->comment != NULL && strstr(i->comment, "OPT_STORE_IMEDIATO") != NULL);
}

escopo_registrador_t *novo_escopo_registrador()
{
    escopo_registrador_t *e = malloc(sizeof(escopo_registrador_t));
    e->num_regs = 0;
    e->reg_area = malloc(13*sizeof(int)); 
    return e;
}

int adiciona_registrador(escopo_registrador_t *e, operando_instr_t *r)
{
    if(e->num_regs > 14)
        e->reg_area = realloc(e->reg_area, sizeof(int) * (e->num_regs-3));

    e->reg_area[e->num_regs] = r->id;
    e->num_regs++;
    return e->num_regs - 1;
}

int registrador_assembly(escopo_registrador_t *e,operando_instr_t *r)
{
    for(int i=0; i < e->num_regs; i++)
    {
        if(e->reg_area[i] == r->id)
            return i;
        
    }
    return adiciona_registrador(e, r);
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

void imprime_registrador_assembly_4(escopo_registrador_t *e,  operando_instr_t *r)
{
	switch (r->tipo)
	{
    case rfp:
        printf("%%rbp");
		break;
    case rsp:
        printf("%%rsp");
		break;
	case imediato:
		printf("$%d", r->val);
		break;
	case registrador:{
 		int reg_ref = registrador_assembly(e, r);
		imprime_registrador_assembly_4_ref(reg_ref);
		break;
		}
	default:
		break;
	}
}
void imprime_registrador_assembly_4_ref(int reg_ref)
{
    switch (reg_ref)
    {
	case 0:
		printf("%%ecx");
		break;
	case 1:
		printf("%%edx");
		break;
	case 2:
		printf("%%ebx");
		break;
	case 3:
		printf("%%esi");
		break;
	case 4:
		printf("%%edi");
		break;
	case 5:
		printf("%%r8d");
		break;
	case 6:
		printf("%%r9d");
		break;
	case 7:
		printf("%%r10d");
		break;
	case 8:
		printf("%%r11d");
		break;
	case 9:
		printf("%%r12d");
		break;
	case 10:
		printf("%%r13d");
		break;
	case 11:
		printf("%%r14d");
		break;
	case 12:
		printf("%%r15d");
		break;
    default:
        printf("spill :(");
    }
}

void imprime_registrador_assembly_16(escopo_registrador_t *e,  operando_instr_t *r)
{
	switch (r->tipo)
	{
    case rfp:
        printf("%%rbp");
		break;
    case rsp:
        printf("%%rsp");
		break;
	case imediato:
		printf("$%d", r->val);
		break;
	case registrador:{
 		int reg_ref = registrador_assembly(e, r);
		imprime_registrador_assembly_16_ref(reg_ref);
		break;
		}
	default:
		break;
	}
}

void imprime_registrador_assembly_16_ref(int reg_ref)
{
    switch (reg_ref)
    {
	case 0:
		printf("%%rcx");
		break;
	case 1:
		printf("%%rdx");
		break;
	case 2:
		printf("%%rbx");
		break;
	case 3:
		printf("%%rsi");
		break;
	case 4:
		printf("%%rdi");
		break;
	case 5:
		printf("%%r8");
		break;
	case 6:
		printf("%%r9");
		break;
	case 7:
		printf("%%r10");
		break;
	case 8:
		printf("%%r11");
		break;
	case 9:
		printf("%%r12");
		break;
	case 10:
		printf("%%r13");
		break;
	case 11:
		printf("%%r14");
		break;
	case 12:
		printf("%%r15");
		break;
    default:
        printf("spill :(");
    }
}