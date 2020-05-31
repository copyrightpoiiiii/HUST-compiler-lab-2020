compiler: 
	flex scanner.l
	bison -d parser.y
	gcc -o parser lex.yy.c parser.tab.c ast.c

clean :
	rm -f lex.yy.c
	rm -f parser.output 
	rm -f parser.tab.c
	rm -f parser.tab.h
	rm -f parser

test :
	flex scanner.l
	bison -d parser.y
	gcc -o parser lex.yy.c parser.tab.c ast.c
	./parser test.c
	./parser fool.c
	./parser char_string.c