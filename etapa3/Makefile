etapa3: parser.y scanner.l ast.c ast.h
	bison -d parser.y
	flex -o scanner.lex.c  scanner.l
	gcc -Wall -o etapa3 scanner.lex.c parser.tab.c ast.c main.c -lfl

report: parser.y scanner.l ast.c ast.h
	bison -d -r state parser.y
	flex -o scanner.lex.c  scanner.l
	gcc -Wall -o etapa3 scanner.lex.c parser.tab.c ast.c main.c -lfl

clean:
	rm -rf etapa3
