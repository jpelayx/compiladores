etapa4: parser.y scanner.l valor_token.c valor_token.h ast.c ast.h
	bison -d parser.y
	flex -o scanner.lex.c  scanner.l
	gcc -Wall -o etapa3 scanner.lex.c parser.tab.c valor_token.c ast.c main.c -lfl

report: parser.y scanner.l valor_token.c valor_token.h ast.c ast.h
	bison -d -r state parser.y
	flex -o scanner.lex.c  scanner.l
	gcc -Wall -o etapa3 scanner.lex.c parser.tab.c valor_token.c ast.c main.c -lfl

clean:
	rm -rf etapa4
