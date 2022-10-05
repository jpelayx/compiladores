etapa7: parser.y scanner.l *.c *.h
	bison -d parser.y
	flex -o scanner.lex.c  scanner.l
	gcc -Wall -o etapa7 scanner.lex.c parser.tab.c instr.c valor_token.c ast.c tabela_simbolos.c escopo.c assembly.c optimizer.c main.c -lfl

report: parser.y scanner.l 
	bison -d -r state parser.y
	flex -o scanner.lex.c  scanner.l
	gcc -Wall -o etapa7 scanner.lex.c parser.tab.c instr.c valor_token.c ast.c tabela_simbolos.c escopo.c assembly.c optimizer.c main.c -lfl

debug: parser.y scanner.l *.c *.h
	bison -d parser.y
	flex -o scanner.lex.c  scanner.l
	gcc -g -Wall -o etapa7 scanner.lex.c parser.tab.c instr.c valor_token.c ast.c tabela_simbolos.c escopo.c assembly.c optimizer.c main.c -lfl

assembly: parser.y scanner.l *.c *.h 
	make 
	./etapa7 < in > out.s
	gcc out.s -o out

assembly_opt: parser.y scanner.l *.c *.h
	make 
	./etapa7 -O < in > out.s
	gcc out.s -o out

clean:
	rm -rf etapa7
	rm parser.tab.* scanner.lex.c	
