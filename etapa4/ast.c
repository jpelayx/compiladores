#include "ast.h"
#include <stdlib.h>
#include <stdio.h>

// baseado em: https://www.inf.ufrgs.br/~schnorr/tutorial-bison-p2.html

ast_t* cria_nodo(tipos_nodo_t tipo, valor_token_t *valor_lexico){
	ast_t* ret = NULL;
	ret = calloc(1,sizeof(ast_t));
	if(ret != NULL){
		ret-> num_filhos = 0;
		ret-> filhos = NULL;
		ret-> tipo = tipo;
		ret-> valor_lexico = valor_lexico;
	}
	return ret;	
}

ast_t *cria_nodo_binario(valor_token_t *valor_lexico, ast_t *f1, ast_t *f2){
	ast_t *ret = cria_nodo(binario, valor_lexico);
	insere_filho(ret, f1);
	insere_filho(ret, f2);
	return ret;
}

ast_t *cria_nodo_unario(valor_token_t *valor_lexico, ast_t *f1) {
	ast_t *ret = cria_nodo(unario, valor_lexico);
	insere_filho(ret, f1);
	return ret;
}

ast_t *cria_nodo_vetor(valor_token_t *valor_lexico_id, ast_t *vetor) {
	ast_t *n;
	if(vetor == NULL)
		n = cria_nodo(identificador, valor_lexico_id);
	else {
		n = cria_nodo(acesso_vetor, NULL);
		insere_filho(n, cria_nodo(identificador, valor_lexico_id));
		insere_filho(n, vetor);
	}
	return n;
}

void insere_filho(ast_t *pai, ast_t *filho){
	if(pai == NULL)	{
		if(filho != NULL)
			free(filho);
		return;
	}
	if(pai->num_filhos > 0 && pai->filhos[pai->num_filhos-1] == NULL)
		pai->filhos[pai->num_filhos-1] = filho;
	else {
		pai->num_filhos++;
		pai->filhos = realloc(pai-> filhos, pai->num_filhos * sizeof(ast_t*));
		pai->filhos[pai-> num_filhos-1] = filho;
	}
}

ast_t *inicia_lista(ast_t* item)
{
	insere_filho(item, NULL);
	return item;
}


ast_t *insere_fim_lista(ast_t *item, ast_t *lista)
{
	if(lista == NULL)
		return inicia_lista(item);
	insere_filho(fim_da_lista(lista), item);
	insere_filho(item, NULL);
	return lista;
}

ast_t *insere_inicio_lista(ast_t *item, ast_t *lista)
{
	if(lista == NULL)
		return inicia_lista(item);
	insere_filho(item, lista);
	return item;
}

ast_t *fim_da_lista(ast_t *t)
{
	ast_t *fim = t;
	while(fim->num_filhos > 0 && fim->filhos[fim->num_filhos-1] != NULL)
		fim = fim->filhos[fim->num_filhos-1];
	if(fim->num_filhos == 0 || fim->filhos[fim->num_filhos-1] != NULL)
		return t; // nao eh lista
	return fim;
}

ast_t *remove_nodos_inuteis(ast_t *t)
{
	printf("CUUUUUUUUUUUUUUUUU \n");
	// pula nodos inuteis até achar a nova raiz 
	ast_t *root = t;
	while(root != NULL && root->tipo == identificador)
	{
		// TODO: desalocar nodo
		root = root->filhos[root->num_filhos-1];
	}
	if(root == NULL)
		return root;

	// poda nodos inuteis a partir da nova raiz
	ast_t *n = root, *next;
	do
	{
		if(n != NULL && n->num_filhos > 0)
			next = n->filhos[n->num_filhos-1];
		else 
			next = NULL;
		if(next != NULL && next->tipo == identificador)
		{
			// pula o nodo
			// TODO: desalocar nodo  
			if(next->num_filhos > 0)
				n->filhos[n->num_filhos-1] = next->filhos[next->num_filhos-1];	
			else 
				n->filhos[n->num_filhos-1] = NULL;
		}	
		else 
		{
			n = next;
			if(n != NULL && n->num_filhos > 0)
				next = n->filhos[n->num_filhos-1];
			else 
				next = NULL;
		}	
	} while(next != NULL);		
	return root;
}

void imprime_nodo(ast_t *nodo){
	if(nodo != NULL){
		printf("%p [label=\"", nodo);

		//Verifica o tipo do NODO.
		switch (nodo->tipo){
			case chamada_funcao:
				printf("call ");
				printf("%s", nodo-> valor_lexico -> valor.cadeia_caracteres);
				break;
			case declaracao:
				printf("<=");
				break;
			case atribuicao:
				printf("=");
				break;
			case acesso_vetor:
				printf("[]");
				break;
			//Palavras reservadas.
			case cmd_while:
				printf("while");
				break;
			case cmd_for:
				printf("for");
				break;
			case cmd_if:
				printf("if");
				break;
			case cmd_return:
				printf("return");
				break;
			case cmd_break:
				printf("break");
				break;
			case cmd_continue:
				printf("continue");
				break;
			case entrada:
				printf("input");
				break;
			case saida:
				printf("output");
				break;
			case ternario:
				printf("?:");
				break;
			//Se for literal, precisa verificar o tipo para fazer a impressao.
			case literal:
				switch(nodo-> valor_lexico -> tipo_literal){
					case tipo_inteiro:
						printf("%d", nodo-> valor_lexico-> valor.inteiro);
						break;
					case tipo_ponto_flutuante:
						break;
					case tipo_caractere:
						printf("%c", nodo-> valor_lexico-> valor.caractere);
						break;
					case tipo_booleano:
						nodo-> valor_lexico-> valor.booleano 
						? printf("true")
						: printf("false");
						break;
					case tipo_cadeia_caracteres:
						printf("%s", nodo-> valor_lexico-> valor.cadeia_caracteres);
						break;	
				}
				break;
			/*
				Aqui se enquadram:
				identifificadores
				operacoes cujo valor lexico é o suficiente para a impressao do label, como:
					operadores compostos (&&, ||, <<, >>, !=, ==, >=, <=)
				caracteres especiais que representam operadores aritmeticos ou booleanos, como:
					+, -, &, *, #, etc
							
			*/	
			case identificador:
			case identificador_vetor:
			case funcao:
			case unario:
			case binario:
			case cmd_shift:
					if(nodo->valor_lexico->tipo == tk_caractere_especial)
						printf("%c", nodo->valor_lexico->valor.caractere);
					else
						printf("%s", nodo->valor_lexico->valor.cadeia_caracteres);	
				break;
			default:
				/*
				Tem que ter enunciado para todos os tipos de nodos até para os que foram
				tratados foram do switch, que são os nodos intermediarios 
				(lista_funcao, lista_comando, lista_expressao)		
				*/
				break;	
			
		}		
		// Final comum para todos os labels	
		printf("\"];\n");
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
			if(arvore->filhos[i] != NULL){
				printf("%p, %p\n", (ast_t *)arvore, (ast_t *)arvore->filhos[i]); 
				imprime_arestas((ast_t *)arvore->filhos[i]);
			}
		}
		
	}

}

void imprime_tipo_semantico(tipos_semanticos_t t)
{
	switch (t)
	{
	case int_sem:
		printf("int");
		break;
	case float_sem:
		printf("float");
		break;
	case bool_sem:
		printf("bool");
		break;
	case char_sem:
		printf("char");
		break;
	case string_sem:
		printf("string");
		break;
	case void_sem:
		printf("void");
		break;
	
	default:
		printf("nda");
		break;
	}
}

extern void exporta (void *arvore)
{
	if(arvore != NULL){
		imprime_arestas(arvore);
		imprime_nodos(arvore);	
	}
}

extern void libera (void *arvore)
{
	if(arvore == NULL)
		return;
	ast_t *t = (ast_t*)arvore;
    for(int i = 0; i < t->num_filhos; i++){
		libera((void*)(t->filhos[i]));
	}

	if(t->valor_lexico != NULL)
	{
		libera_tk(t->valor_lexico);
	}
	free(t->filhos);
	free(t);
}