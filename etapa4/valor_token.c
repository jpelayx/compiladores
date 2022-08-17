#include "valor_token.h"
#include "stdlib.h"
#include "stdio.h"

void libera_tk(valor_token_t *tk)
{
    if(tk == NULL)
        return;
    if( 
        tk->tipo == tk_identificador ||
        tk->tipo == tk_operador_composto ||
       (tk->tipo == tk_literal && tk->tipo_literal == tipo_cadeia_caracteres))
    {
        free(tk->valor.cadeia_caracteres);
    }
    free(tk);
}
