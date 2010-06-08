VPATH = src gui dbg

cpp = g++
executable = cityscape
objects = main.o \
	  city.o structure.o residence.o \
	  dbggui.o dbgscr.o dbgdraw.o
cppflags = -Wall -Wextra -g

ifeq ($(OS),Windows_NT)
	executable = cityscape.exe
	cppflags += -Ic:/andre/programas/msys/local/include/SDL
	libs += -Lc:/andre/programas/msys/local/lib/ -lmingw32 -lSDLmain -lSDL -mwindows
else
	cppflags += `sdl-config --cflags`
	libs += `sdl-config --libs`
endif
cppflags += -Isrc -Igui -Idbg
libs += -lSDL_gfx

all: $(executable)

#.PHONY: data
#data:
#	cd data && $(MAKE)

#
# Basic rules
#
$(executable) : $(objects)
	$(cpp) $^ -o $(executable) $(libs)

.cc.o :
	$(cpp) $(cppflags) -c $<

#
# Clean
#
.PHONY : clean
clean :
ifeq ($(OS),Windows_NT)
	-del $(objects) $(executable)
else
	-rm $(objects) $(executable)
endif
#	cd data && $(MAKE) clean

