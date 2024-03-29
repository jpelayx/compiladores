%{
#include <stdio.h>
#include "parser.tab.h"

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
{opssimples} { return yytext[0]; }

	/* Operators (more than one character) */
\<\= { return TK_OC_LE; }
\>\= { return TK_OC_GE; }
\=\= { return TK_OC_EQ; }
\!\= { return TK_OC_NE; }
\&\& { return TK_OC_AND; }
\|\| { return TK_OC_OR; }
\>\> { return TK_OC_SL; }
\<\< { return TK_OC_SR; }

	/* Literals */
{integer} { return TK_LIT_INT; }
[+-]?{real} { return TK_LIT_FLOAT; }
false { return TK_LIT_FALSE; }
true { return TK_LIT_TRUE; }
\'([^'\n])\' { return TK_LIT_CHAR; }
\"([^"\n])*\" { return TK_LIT_STRING; }
{alpha}({alpha}|{digit})* { return TK_IDENTIFICADOR; }

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