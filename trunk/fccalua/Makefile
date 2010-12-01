#INCLUDES=
#LIBS=-lcurses -llua -lm
INCLUDES=-IC:\andre\desenv\curses -IC:\andre\desenv\lua\include
LIBS=-LC:\andre\desenv\curses -LC:\andre\desenv\lua -lpdcurses -llua5.1

all:
	gcc -g -Wall -o fccacurses fccacurses.c $(INCLUDES) $(LIBS)

clean:
	rm fccacurses
