#ifndef _AST_H_
#define _AST_H_

// olhar https://www.inf.ufrgs.br/~schnorr/tutorial-bison-p2.html


typedef struct ast
{
    char *label;
    int num_children;
    struct ast **children;    
} ast_t;


/* nao sei se vai ficar assim (ou aqui)
 * mas imagino que alguma definição como essa 
 * vai ter que existir em algum lugar */
typedef union token_type
{
    char *non_literal;
    int int_literal;
    float float_literal;
    char char_literal;
    bool bool_literal;
    char *string_literal;
} token_type_t;

// cria um no sem filhos e constroi o label
ast_t *ast_new(int tk_type, token_type_t tk_value);

// libera o nó e seus filhos
void ast_free(ast_t *tree);

// adiciona child como filho de tree
void ast_add_child(ast_t *tree, ast_t *child);

// imprime recursivamente a árvore
void ast_print(ast_t *tree);

#endif //_AST_H_