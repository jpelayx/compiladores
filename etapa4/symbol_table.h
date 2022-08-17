#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_

#include "ast.h"

#define INITIAL_SIZE 100 

typedef struct symbol {
    int id;
    tipos_semanticos_t tipo;
    tipos_nodo_t natureza;
    int linha;
    int tamanho;
    int num_parametros;
    tipos_semanticos_t tipos_parametros;
    valor_token_t *valor_lexico;
} symbol_t;

symbol_t *new_symbol();

typedef symbol_t *symbol_table;

symbol_table init_symbol_table();

symbol_table insert(symbol_table t, symbol_t *s);

void search(symbol_table t, char *nome);

int hash_function(int id);


#endif //_SYMBOL_TABLE_H_