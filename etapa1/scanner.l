%{
#include "tokens.h"
%}

opssimples [,;:()[]{}+-|*/<>=!&%#^.$]
digit [0-9]
alpha [a-zA-Z_]
integer {digit}+
exponent [eE][+-]?{integer}
real {integer}("."{integer})?{exponent}?

%%

int return TK_PR_INT
float return TK_PR_FLOAT
bool return TK_PR_BOOL
char return TK_PR_CHAR
string return TK_PR_STRING
if return TK_PR_IF
then return TK_PR_THEN

{opssimples} return yytext[0];
<= return TK_OC_LE 
>= return TK_OC_GE
== return TK_OC_EQ
!= return TK_OC_NE
&& return TK_OC_AND
|| return TK_OC_OR
>> return TK_OC_SL
<< return TK_OC_SR
{alpha}({alpha}|{digit})* return TK_IDENTIFICADOR
[+-]?{integer} return TK_LIT_INT
[+-]?{real} return TK_LIT_FLOAT
false return TK_LIT_FALSE
true return TK_LIT_TRUE
'.' return TK_LIT_CHAR
".*" return TK_LIT_STRING



. return TOKEN_ERRO

%%


