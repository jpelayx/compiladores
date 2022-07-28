#ifndef _AST_H_
#define _AST_H_

// olhar https://www.inf.ufrgs.br/~schnorr/tutorial-bison-p2.html

typedef struct ast {
    char *label;
    int num_children;
    struct ast **children;    
} ast_t;

#endif //_AST_H_