#INCLUDES=-I/usr/include/lua5.1
#LIBS=-lncurses -llua5.1 -lm
INCLUDES=-IC:\andre\lib\curses -IC:\andre\desenv\lua\include
LIBS=-LC:\andre\lib\curses -LC:\andre\desenv\lua -lpdcurses -llua5.1

all:
	gcc -g -Wall -o fccacurses fccacurses.c $(INCLUDES) $(LIBS)

clean:
	rm fccacurses
