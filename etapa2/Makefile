etapa2: 
	bison -d parser.y
	flex -o scanner.lex.c  scanner.l
	gcc -Wall -o etapa2 scanner.lex.c parser.tab.c main.c -lfl

clean:
	rm -rf etapa2
