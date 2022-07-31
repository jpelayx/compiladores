#include "ast.h"
#include <stdlib.h>
#include <stdio.h>

// baseado em: https://www.inf.ufrgs.br/~schnorr/tutorial-bison-p2.html

ast_t* cria_nodo(valor_token_t *valor_lexico, tipos_nodo_t tipo){
	ast_t* ret = NULL;
	ret = calloc(sizeof(ast_t), 1);
	if(ret != NULL){
		ret-> num_filhos = 0;
		ret-> filhos = NULL;
		ret-> tipo = tipo;
		ret-> valor_lexico = valor_lexico;
	}
	return ret;	
}

void insere_filho(ast_t *pai, ast_t *filho){
	if(pai != NULL && filho != NULL){
		pai-> num_filhos++;
		pai-> filhos = realloc(pai-> filhos, pai->num_filhos);
		pai-> filhos[pai-> num_filhos-1] = filho;
	}
}

void imprime_nodo(ast_t *nodo){
	if((ast_t *)nodo != NULL){
	
		/* NOT WORKING.
		Ideia: ver o tipo do valor lexico de cada nodo 
		(
		caractere_especial,
		operador_composto,
		identificador,
		literal
		)
		
		e printar o nodo de acordo. 
		
		******Problemas******:
		a) Tipo do NODO vs tipo do valor_lexico!!!! (qual usar nesse caso?)
		
		printf("%p [label=\"", arvore);
	
		switch(((ast_t *)arvore)-> valor_lexico-> tipo{
			// Se um identificador é chamada de funcao, imprime "call " na frente.
			case identificador:
				if(((ast_t *)arvore)-> tipo == chamada_funcao{
					printf("call ");
				}
				
				printf("%s", ((ast_t *)arvore)-> valor_lexico-> cadeia_caracteres);
				
				break;
			case operador_composto:
				printf("%s", ((ast_t *)arvore)-> valor_lexico-> cadeia_caracteres);
				break;
			// Se for literal tem que verificar o tipo pra poder printar.
			case literal:
				switch(((ast_t *)arvore)-> valor_lexico-> tipo_literal){
					case tipo_inteiro:
						printf("%d", ((ast_t *)arvore)-> valor_lexico -> valor.inteiro);
						break;
					case tipo_ponto_flutuante:
						printf("%f", ((ast_t *)arvore)-> valor_lexico -> valor.ponto_flutuante);
						break;
					case tipo_caractere:
						printf("%c", ((ast_t *)arvore)-> valor_lexico -> valor.caractere);
						break;
					case tipo_booleano:
						if(((ast_t *)arvore)-> valor_lexico -> valor.booleano){
							printf("true");
						} else {
							printf("false");
						}
						break;
					case tipo_cadeia_caracteres:
						printf("%s", ((ast_t *)arvore)-> valor_lexico -> valor.cadeia_caracteres);
						break;
					default:
						break;
				}
				break;
			case caractere_especial:
				//alguma coisa especial aqui ou só printar mesmo?
				printf("%s", ((ast_t *)arvore)-> valor_lexico -> valor.cadeia_caracteres);
				break;
				
		}
	}
	*/
	}
	
}

void imprime_nodos(ast_t *arvore){
	if(arvore != NULL){
		imprime_nodo(arvore);
		for(int i = 0; i < arvore-> num_filhos; i++){
			imprime_nodos((ast_t *)arvore->filhos[i]);
		}
	}
}

void imprime_arestas(ast_t *arvore){
	if(arvore != NULL){
		for(int i = 0; i < arvore-> num_filhos; i++){
			printf("%p, %p\n", (ast_t *)arvore, (ast_t *)arvore->filhos[i]); 
			imprime_arestas((ast_t *)arvore->filhos[i]);
		}
		
	}

}

void exporta (void *arvore)
{
	if(arvore != NULL){
		imprime_nodos(arvore);
		imprime_arestas(arvore);
	}
}

void libera (void *arvore)
{
    return;
}
