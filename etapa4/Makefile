etapa4: parser.y scanner.l valor_token.c valor_token.h ast.c ast.h tabela_simbolos.h tabela_simbolos.c escopo.c escopo.h
	bison -d parser.y
	flex -o scanner.lex.c  scanner.l
	gcc -Wall -o etapa4 scanner.lex.c parser.tab.c valor_token.c ast.c tabela_simbolos.c escopo.c main.c -lfl

report: parser.y scanner.l 
	bison -d -r state parser.y
	flex -o scanner.lex.c  scanner.l
	gcc -Wall -o etapa4 scanner.lex.c parser.tab.c valor_token.c ast.c tabela_simbolos.c escopo.c main.c -lfl

clean:
	rm -rf etapa4
