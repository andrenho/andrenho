GO_FILES = fcca.go game.go land.go tile.go static.go nation.go unit.go \
		   landunit.go
OBJ = $(GO_FILES:.go=.8)

GC = 8g
LD = 8l
TARG = fcca.exe

all:
	make $(TARG)

$(TARG): $(OBJ)
	$(LD) -o $@ $<

$(OBJ): $(GO_FILES)
	$(GC) $^

clean:
	rm -rf $(OBJ) $(TARG)
