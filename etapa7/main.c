/*
  Função principal para realização da E3.
  Não modifique este arquivo.
*/
#include <stdio.h>
#include <string.h>
#include "optimizer.h"
#include "assembly.h"
#include "ast.h"
extern int yyparse(void);
extern int yylex_destroy(void);

void *arvore = NULL;
void exporta (void *arvore);
void libera (void *arvore);

int main (int argc, char **argv)
{
  int ret = yyparse(); 
  // exporta (arvore);
  if (argc > 1 && strcmp(argv[1], "-O") == 0 )
  {
    ((ast_t*)arvore)->codigo = optmize(((ast_t*)arvore)->codigo);
    printf("// versao otimizada\n");

  }  
  generateAsm(((ast_t *)arvore)->codigo);
  libera(arvore);
  arvore = NULL;
  yylex_destroy();
  return ret;
}
