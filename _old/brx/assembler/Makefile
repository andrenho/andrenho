CC=gcc
CFLAGS=-Wall -g
EXTRA=text.o opcodes.o

all: preprocess 1st_pass 2nd_pass hex2bin

preprocess: preprocess.o $(EXTRA)
	$(CC) $(CFLAGS) $^ -o $@

1st_pass: 1st_pass.o $(EXTRA)
	$(CC) $(CFLAGS) $^ -o $@

2nd_pass: 2nd_pass.o $(EXTRA)
	$(CC) $(CFLAGS) $^ -o $@

hex2bin: hex2bin.o $(EXTRA)
	$(CC) $(CFLAGS) $^ -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o *.exe
