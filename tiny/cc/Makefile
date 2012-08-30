OBJECTS = lex.yy.o parser.tab.o compiler.o type.o error.o
CFLAGS = -Wall -Wextra -g -DDEBUG

cc: $(OBJECTS)
	gcc $(CFLAGS) -o $@ $^ -lfl

lex.yy.c: scanner.l
	flex scanner.l

parser.tab.c: parser.y
	bison -d parser.y

%.o: %.c parser.tab.c
	gcc -c $(CFLAGS) -o $@ $<

clean:
	rm -f *.o lex.yy.c parser.tab.c parser.tab.h cc

test: cc
	cc <teste.c
