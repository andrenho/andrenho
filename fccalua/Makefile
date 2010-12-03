#INCLUDES=
#LIBS=-lncurses -llua -lm
INCLUDES=-IC:\andre\desenv\lua\include -IC:\andre\lib\libtcod-1.5.1\include
LIBS=-LC:\andre\desenv\lua -LC:\andre\lib\libtcod-1.5.1 -llua5.1 -ltcod-mingw

all:
	gcc -g -Wall -o fccacurses fccacurses.c $(INCLUDES) $(LIBS)

clean:
	rm fccacurses
