etapa2: parser.y scanner.l
	bison -d parser.y
	flex -o scanner.lex.c  scanner.l
	gcc -Wall -o etapa2 scanner.lex.c parser.tab.c main.c -lfl

report: parser.y scanner.l
	bison -d -r state parser.y
	flex -o scanner.lex.c  scanner.l
	gcc -Wall -o etapa2 scanner.lex.c parser.tab.c main.c -lfl

clean:
	rm -rf etapa2
