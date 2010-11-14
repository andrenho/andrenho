cc: lex.yy.c parser.tab.c parser.tab.h
	gcc -g -Wall -Wextra -o $@ $^ -lfl

lex.yy.c: scanner.l
	flex scanner.l

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

clean:
	rm *.o lex.yy.c parser.tab.c parser.tab.h cc

test: cc
	./cc <teste.c
