etapa6: parser.y scanner.l *.c *.h
	bison -d parser.y
	flex -o scanner.lex.c  scanner.l
	gcc -Wall -o etapa6 scanner.lex.c parser.tab.c instr.c valor_token.c ast.c tabela_simbolos.c escopo.c assembly.c main.c -lfl

report: parser.y scanner.l 
	bison -d -r state parser.y
	flex -o scanner.lex.c  scanner.l
	gcc -Wall -o etapa6 scanner.lex.c parser.tab.c instr.c valor_token.c ast.c tabela_simbolos.c escopo.c assembly.c main.c -lfl

debug: parser.y scanner.l *.c *.h
	bison -d parser.y
	flex -o scanner.lex.c  scanner.l
	gcc -g -Wall -o etapa6 scanner.lex.c parser.tab.c instr.c valor_token.c ast.c tabela_simbolos.c escopo.c assembly.c main.c -lfl

assembly: ex.c 
	gcc -S ex.c
	gcc ex.s -o ex

clean:
	rm -rf etapa6
	rm parser.tab.* scanner.lex.c	
