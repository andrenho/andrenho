CC=g++
CPPFLAGS=-Wall -IC:\andre\lib\SDL-1.2.14\include\SDL -DDATA_DIR="\"./data\""
LDFLAGS=-LC:\andre\lib\SDL-1.2.14\lib -lmingw32 -lSDLmain -lSDL -lSDL_ttf -mwindows
SRC=$(wildcard src/*.cc)
EXE=cociv

all: $(SRC) $(EXE)

$(EXE): $(SRC:.cc=.o)
	$(CC) -o $@ $^ $(LDFLAGS)

.cc.o:
	$(CC) -c $< $(CPPFLAGS) -o $@

clean:
	rm -f $(SRC:.cpp=.o) $(EXE) $(EXE).exe
