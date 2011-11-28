CC=g++
CPPFLAGS=-c -Wall -IC:\andre\lib\SDL-1.2.14\include\SDL
LDFLAGS=-LC:\andre\lib\SDL-1.2.14\lib -lmingw32 -lSDLmain -lSDL -mwindows
SRC=$(wildcard src/*.cpp)
EXE=cociv

all: $(SRC) $(EXE)

$(EXE): $(SRC:.cpp=.o)
	$(CC) -o $@ $^ $(LDFLAGS)

.cpp.o:
	$(CC) -c $< $(CPPFLAGS) -o $@

clean:
	rm -f $(SRC:.cpp=.o) $(EXE) $(EXE).exe
