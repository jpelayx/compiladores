%{
#include <stdio.h>
#include "parser.tab.h"

int get_line_number();

int line_number = 1;
%}

opssimples [\,\;\:\(\)\[\]\{\}\+\-\|\*\/\<\>\=\!\&\%\#\^\.\$\?]
digit [0-9]
alpha [a-zA-Z_]
integer {digit}+
exponent [eE][+-]?{integer}
real {integer}("."{integer})?{exponent}?

%x MULTILINE_COMMENT

%%
	/* Reserved words */
int { return TK_PR_INT; }
float { return TK_PR_FLOAT; }
bool { return TK_PR_BOOL; }
char { return TK_PR_CHAR; }
string { return TK_PR_STRING; }
if { return TK_PR_IF; }
then { return TK_PR_THEN; }
else { return TK_PR_ELSE; }
while { return TK_PR_WHILE; }
do { return TK_PR_DO; }
input { return TK_PR_INPUT; }
output { return TK_PR_OUTPUT; }
return { return TK_PR_RETURN; }
const { return TK_PR_CONST; }
static { return TK_PR_STATIC; }
foreach { return TK_PR_FOREACH; }
for { return TK_PR_FOR; }
switch { return TK_PR_SWITCH; }
case { return TK_PR_CASE; }
break { return TK_PR_BREAK; }
continue { return TK_PR_CONTINUE; }
class { return TK_PR_CLASS; }
private { return TK_PR_PRIVATE; }
public { return TK_PR_PUBLIC; }
protected { return TK_PR_PROTECTED; }
end { return TK_PR_END; }
default { return TK_PR_DEFAULT; }

	/* Special characters */
{opssimples} { yylval.valor_lexico.linha = get_line_number();
       yylval.valor_lexico.tipo = tk_caractere_especial;
	   yylval.valor_lexico.valor.caractere = yytext[0];
	   return yytext[0]; }

	/* Operators (more than one character) */
\<\= { yylval.valor_lexico.linha = get_line_number();
       yylval.valor_lexico.tipo = tk_operador_composto;
	   char texto[] = "<=";
	   yylval.valor_lexico.valor.cadeia_caracteres = strdup(texto); 
	   return TK_OC_LE; }
\>\= { yylval.valor_lexico.linha = get_line_number();
       yylval.valor_lexico.tipo = tk_operador_composto;
	   char texto[] = ">=";
	   yylval.valor_lexico.valor.cadeia_caracteres = strdup(texto);
	   return TK_OC_GE; }
\=\= { yylval.valor_lexico.linha = get_line_number();
       yylval.valor_lexico.tipo = tk_operador_composto;
	   char texto[] = "==";
	   yylval.valor_lexico.valor.cadeia_caracteres = strdup(texto);
	   return TK_OC_EQ; }
\!\= { yylval.valor_lexico.linha = get_line_number();
       yylval.valor_lexico.tipo = tk_operador_composto;
	   char texto[] = "!=";
	   yylval.valor_lexico.valor.cadeia_caracteres = strdup(texto);
	   return TK_OC_NE; }
\&\& { yylval.valor_lexico.linha = get_line_number();
       yylval.valor_lexico.tipo = tk_operador_composto;
	   char texto[] = "&&";
	   yylval.valor_lexico.valor.cadeia_caracteres = strdup(texto);
	   return TK_OC_AND; }
\|\| { yylval.valor_lexico.linha = get_line_number();
       yylval.valor_lexico.tipo = tk_operador_composto;
	   char texto[] = "||";
	   yylval.valor_lexico.valor.cadeia_caracteres = strdup(texto);
	   return TK_OC_OR; }
\>\> { yylval.valor_lexico.linha = get_line_number();
       yylval.valor_lexico.tipo = tk_operador_composto;
	   char texto[] = ">>";
	   yylval.valor_lexico.valor.cadeia_caracteres = strdup(texto);
	   return TK_OC_SL; }
\<\< { yylval.valor_lexico.linha = get_line_number();
       yylval.valor_lexico.tipo = tk_operador_composto;
	   char texto[] = "<<";
	   yylval.valor_lexico.valor.cadeia_caracteres = strdup(texto);
	   return TK_OC_SR; }

	/* Literals */
{integer} {
	yylval.valor_lexico.linha = get_line_number();
	yylval.valor_lexico.tipo = tk_literal;
	yylval.valor_lexico.tipo_literal = tipo_inteiro;
	yylval.valor_lexico.valor.inteiro = atoi(yytext);
	return TK_LIT_INT; }
[+-]?{real} {
	yylval.valor_lexico.linha = get_line_number();
	yylval.valor_lexico.tipo = tk_literal;
	yylval.valor_lexico.tipo_literal = tipo_ponto_flutuante;
	yylval.valor_lexico.valor.ponto_flutuante = atof(yytext);
	return TK_LIT_FLOAT; }
false { 
	yylval.valor_lexico.linha = get_line_number();
	yylval.valor_lexico.tipo = tk_literal;
	yylval.valor_lexico.tipo_literal = tipo_booleano;
	yylval.valor_lexico.valor.booleano = false;
	return TK_LIT_FALSE; }
true { 
	yylval.valor_lexico.linha = get_line_number();
	yylval.valor_lexico.tipo = tk_literal;
	yylval.valor_lexico.tipo_literal = tipo_booleano;
	yylval.valor_lexico.valor.booleano = true;
	return TK_LIT_TRUE; }
\'([^'\n])\' { 
	yylval.valor_lexico.linha = get_line_number();
	yylval.valor_lexico.tipo = tk_literal;
	yylval.valor_lexico.tipo_literal = tipo_caractere;
	yylval.valor_lexico.valor.caractere = yytext[0];
	return TK_LIT_CHAR; }
\"([^"\n])*\" { 
	yylval.valor_lexico.linha = get_line_number();
	yylval.valor_lexico.tipo = tk_literal;
	yylval.valor_lexico.tipo_literal = tipo_cadeia_caracteres;
	yylval.valor_lexico.valor.cadeia_caracteres = strdup(yytext);
	return TK_LIT_STRING; }
{alpha}({alpha}|{digit})* { 
	yylval.valor_lexico.linha = get_line_number();
	yylval.valor_lexico.tipo = tk_identificador;
	yylval.valor_lexico.valor.cadeia_caracteres = strdup(yytext);
	return TK_IDENTIFICADOR; }

	/* Empty spaces */
[ \t]

	/* Single line comment */
\/\/.*

	/* Multi line comment */
\/\*	{BEGIN(MULTILINE_COMMENT);}
<MULTILINE_COMMENT>\n {line_number+=1;}
<MULTILINE_COMMENT>"*/" {BEGIN(INITIAL);}
<MULTILINE_COMMENT>. 

	/* New line */
\n {line_number+=1;}

	/* Anything else */
. { return TOKEN_ERRO; }

%%

int get_line_number()
{
    return line_number;
}
