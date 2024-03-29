#ifndef _VALOR_TOKEN_H_
#define _VALOR_TOKEN_H_

#include <stdbool.h>

typedef enum tipo_token {
	tk_caractere_especial,
	tk_operador_composto,
	tk_identificador,
	tk_literal
} tipo_token_t;

typedef enum tipo_literal {
	tipo_inteiro,
	tipo_ponto_flutuante,
	tipo_caractere,
	tipo_booleano,
	tipo_cadeia_caracteres
} tipo_literal_t;

typedef struct valor_token {
	int linha;
	tipo_token_t tipo;
	tipo_literal_t tipo_literal;
	union {
		int inteiro;
		float ponto_flutuante;
		char caractere;
		bool booleano;
		char* cadeia_caracteres;
	} valor;
} valor_token_t;

void libera_tk(valor_token_t *v);

#endif // _VALOR_TOKEN_H_
