compiler: 
	flex scanner.l
	bison -d parser.y
	gcc -o parser lex.yy.c parser.tab.c ast.c anlyase.c
	./parser test.c > out.txt

clean :
	rm -f lex.yy.c
	rm -f parser.output 
	rm -f parser.tab.c
	rm -f parser.tab.h
	rm -f parser

test :
	flex scanner.l
	bison -d parser.y
	gcc -o parser lex.yy.c parser.tab.c ast.c anlyase.c
	./parser test.c > out.txt