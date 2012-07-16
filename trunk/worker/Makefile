CFLAGS=-g -Wall -Wextra -DSDL -I. -IC:\andre\lib\SDL-1.2.14\include\SDL
LDFLAGS=-LC:\andre\lib\SDL-1.2.14\bin -LC:\andre\lib\SDL-1.2.14\lib -lmingw32 -lSDLmain -lSDL -mwindows

all: worker

worker: main.o level.o sdl/ui.o
	gcc $(LDFLAGS) -o worker $^

main.o: main.c
level.o: level.c level.h
sdl/ui.o: sdl/ui.c sdl/ui.h

.c.o:
	gcc $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o worker worker.exe

.PHONY : clean
