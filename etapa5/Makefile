etapa5: parser.y scanner.l *.c *.h
	bison -d parser.y
	flex -o scanner.lex.c  scanner.l
	gcc -Wall -o etapa5 scanner.lex.c parser.tab.c instr.c valor_token.c ast.c tabela_simbolos.c escopo.c main.c -lfl

report: parser.y scanner.l 
	bison -d -r state parser.y
	flex -o scanner.lex.c  scanner.l
	gcc -Wall -o etapa5 scanner.lex.c parser.tab.c instr.c valor_token.c ast.c tabela_simbolos.c escopo.c main.c -lfl

clean:
	rm -rf etapa5
	rm parser.tab.* scanner.lex.c	
