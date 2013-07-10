CC=gcc
CFLAGS=-Wall -g -IC:\andre\lib\curses
LIBS=-LC:\andre\lib\curses -lpdcurses
OBJECT=main.o curses_.o cpu.o video.o keyboard.o memory.o debugger.o

all: emulator

emulator: $(OBJECT)
	$(CC) $(CFLAGS) $(LIBS) pdcurses.dll $^ -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o *.exe
