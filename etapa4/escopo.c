#include "escopo.h"


pilha_t* inicializa_pilha()
{
    pilha_t *p = calloc(1, sizeof(pilha_t));
    tabela_simbolos_t *escopo_global = init_tabela_simbolos();
    p->anterior = NULL; // fundo da pilha 
    p->t = escopo_global;
    return p;
}

tabela_simbolos_t *topo(pilha_t *p)
{
    return p->t;
}

//Push
pilha_t* entra_escopo(pilha_t *p, tabela_simbolos_t *t){
    pilha_t *nt = calloc(1, sizeof(pilha_t));
    nt->anterior = p;
    nt->t = t;
    return nt;    
}

pilha_t *novo_escopo(pilha_t *p)
{
    pilha_t *nt = calloc(1, sizeof(pilha_t));
    nt->anterior = p;
    nt->t = init_tabela_simbolos();
    return nt;
}

//Pop
pilha_t* sai_escopo(pilha_t *p)
{
    pilha_t *nt = p->anterior;
    libera_tabela_simbolos(p->t);
    free(p);
    return nt;
}

pilha_t * adiciona_simbolo(pilha_t *p, simbolo_t *s)
{
    if(p == NULL)
        p = inicializa_pilha();
    simbolo_t *os = busca(topo(p), s->valor_lexico->valor.cadeia_caracteres);
    if(os != NULL){
        //Já existe esse simbolo na tabela!
        erro_redeclaracao(
            s->valor_lexico->valor.cadeia_caracteres,
            s->valor_lexico->linha,
            os->valor_lexico->linha);
    } else{
        insere_simbolo(topo(p), s);
    }
    return p;
}

pilha_t *adiciona_lista_simbolos(pilha_t *p, ast_t *t, tipos_semanticos_t tipo)
{
    if(t == NULL)
        return p;
    simbolo_t *s;
    do
    {   
        s = novo_simbolo_de_nodo(t);
        if(s->tipo != nda)
            verifica_tipos(s->tipo, tipo, s->valor_lexico->linha);
        s->tipo = tipo;
        p = adiciona_simbolo(p, s);   
        if(t->num_filhos > 0)
            t = t->filhos[t->num_filhos - 1];
        else 
            t = NULL;
    } while (t != NULL);
    return p;   
}

simbolo_t *referencia(pilha_t *p, valor_token_t *v, tipos_simbolos_t natureza)
{
    simbolo_t *s = procura_nome_em_todas_tabelas(p, v->valor.cadeia_caracteres);
    if(s == NULL)
        erro_nao_declaracao(v->valor.cadeia_caracteres, v->linha);
    if(s->natureza != natureza)
        erro_uso_incorreto(v->valor.cadeia_caracteres, v->linha, natureza, s->natureza);
    return s;
}

simbolo_t *procura_nome_em_todas_tabelas(pilha_t *p, char *nome){
    simbolo_t *s;
    while (p != NULL){
        s = busca(p->t, nome);
        if(s != NULL){
            return s;
        }
        p = p->anterior;
    }
    return s;
}

void erro_redeclaracao(char *nome, int linha_redeclaracao, int linha_original){
    printf("error: redeclaration of '%s' on line %d (first declared in line %d)\n", nome, linha_redeclaracao, linha_original);
    exit(ERR_DECLARED);
}


void erro_nao_declaracao(char *nome, int linha){
    printf("error: '%s' undeclared on line %d (first use in this scope)\n", nome, linha);
    exit(ERR_UNDECLARED);
}

void erro_uso_incorreto(char *nome, int linha, tipos_simbolos_t tipo, tipos_simbolos_t tipo_original)
{
    printf("error: incorrect use of ");
    print_natureza(tipo_original);
    printf(" \"%s\", accessed as a ", nome);
    print_natureza(tipo);
    printf(" on line %d\n", linha);
    switch (tipo)
    {
    case simbolo_parametro:
    case simbolo_literal:
    case simbolo_variavel:
        exit(ERR_VARIABLE);
    case simbolo_vetor:
        exit(ERR_VECTOR);
    case simbolo_funcao:
        exit(ERR_FUNCTION);
    }
}

void verifica_tipos(tipos_semanticos_t t, tipos_semanticos_t s, int linha)
{
    switch (t)
    {
    case float_sem:
    case int_sem:
    case bool_sem:
        switch (s)
        {
        case float_sem:
        case int_sem:
        case bool_sem:
        case numerico_sem:
            return; // ok
            break;
        case char_sem:
            printf("error: tryng to convert char on line %d\n", linha);
            exit(ERR_CHAR_TO_X);
        case string_sem:
            printf("error: tryng to convert string on line %d\n", linha);
            exit(ERR_STRING_TO_X);
        default:
            break;
        }
        break;
    case char_sem:
        if(s != char_sem){
            printf("error: tryng to convert char on line %d\n", linha);
            exit(ERR_CHAR_TO_X);
        }
        break; // ok
    case string_sem:
        if(s != string_sem){
            printf("error: tryng to convert string on line %d\n", linha);
            exit(ERR_STRING_TO_X);
        }
        break; // ok
    default:
        break;
    }
}

tipos_semanticos_t infere_tipo(ast_t *t1, ast_t *t2)
{
    switch (t1->tipo_sem)
    {
    case bool_sem:
        return t2->tipo_sem;
    case int_sem:
        if(t2->tipo_sem == float_sem)
            return float_sem;
        else 
            return int_sem;
    case float_sem:
        return float_sem; 
    default:
        return nda;
    }
}