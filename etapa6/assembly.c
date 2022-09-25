#include "assembly.h"
#include <string.h>

void generateAsm(code_t *c)
{
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
        return TRAD_NORMAL;
    }
    if(eh_sequencia_retorno(i))
    {
        printf("mov ");
        registrador_assembly(i->op0);
        printf(", %%eax\n");
        return TRAD_RETORNO;
    }
    printf("// trad direta \n");
    return TRAD_NORMAL;
}

flag_traducao_t traducao_retorno(instr_t *i)
{
    if(i->opcode == jump)
    {
        printf("ret\n");
        return TRAD_NORMAL;
    }
    return TRAD_RETORNO;
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

void registrador_assembly(operando_instr_t *r)
{
    printf("tbd");
}