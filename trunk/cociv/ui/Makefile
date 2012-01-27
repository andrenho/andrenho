CC=g++
CPPFLAGS=-g -Wall -IC:\andre\lib\SDL-1.2.14\include\SDL -DDATA_DIR="\"./data\"" `sdl-config --cflags`
#LDFLAGS=-LC:\andre\lib\SDL-1.2.14\lib -lmingw32 -lSDLmain -lSDL -lSDL_ttf -mwindows
LDFLAGS=-lSDL_ttf `sdl-config --libs`
SRC=$(wildcard src/*.cc)
EXE=cociv

all: $(SRC) $(EXE)

$(EXE): $(SRC:.cc=.o)
	$(CC) -o $@ $^ $(LDFLAGS)

.cc.o:
	$(CC) -c $< $(CPPFLAGS) -o $@

clean:
	rm -f $(SRC:.cc=.o) $(EXE) $(EXE).exe
