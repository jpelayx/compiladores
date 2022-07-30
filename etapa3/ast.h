#ifndef _AST_H_
#define _AST_H_

// olhar https://www.inf.ufrgs.br/~schnorr/tutorial-bison-p2.html

typedef struct ast {
    char *label;
    int num_children;
    struct ast **children;    
} ast_t;

// Cria nó sem filhos
ast_t *ast_new(const char *label);

// Libera recursivamente o nó e seus filhos
void ast_free(ast_t *tree);

// Adiciona child como filho da tree
void ast_add_child(ast_t *tree, ast_t *child);

// Imprime recursivamente a árvore
void ast_print(ast_t *tree);

#endif //_AST_H_
