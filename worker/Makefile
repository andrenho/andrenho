CFLAGS=-g -Wall -Wextra

all: worker

worker: main.o level.o
	gcc $(CFLAGS) -o worker $^

main.o: main.c
level.o: level.c level.h

.c.o:
	gcc $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o worker worker.exe

.PHONY : clean
