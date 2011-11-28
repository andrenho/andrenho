CC=g++
CPPFLAGS=-c -Wall
LDFLAGS=
SRC=$(wildcard src/*.cpp)
EXE=cociv

all: $(SRC) $(EXE)

$(EXE): $(SRC:.cpp=.o)
	$(CC) -o $@ $^ $(LDFLAGS)

.cpp.o:
	$(CC) -c $< $(CPPFLAGS) -o $@

clean:
	rm -f $(SRC:.cpp=.o) $(EXE) $(EXE).exe
