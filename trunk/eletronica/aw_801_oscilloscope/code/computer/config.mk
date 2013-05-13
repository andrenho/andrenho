#
# CUSTOMIZABLE SECTION
# 

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man
OSCPREFIX = ${PREFIX}/share/newhope

# libraries
SDL = yes

# compiler and linker
CC = gcc
#CC = clang

# add debugging info
DEBUG = yes
PROFILING = no
DUMA = no

#########################################################################
#
# PLEASE AVOID CHANGING THE INFORMATION BELOW, UNLESS NECESSARY
#

# osc version
VERSION = 0.0.1

# system libraries
PNG = yes
USE_CPP_THREADS = yes

# basic flags
CFLAGS = -DVERSION=\"${VERSION}\" -DDATADIR=\"${NEWHOPEPREFIX}\" -Wall \
	 -Wfatal-errors -I. -I/usr/include -std=c11
LDFLAGS = -L/usr/lib

UNAME = $(shell uname -o)

# Duma libraries
ifeq (${DUMA}, yes)
  LDFLAGS += -lduma
endif

# debugging information
ifeq (${DEBUG},yes)
  # debug flags
  CFLAGS += -g -O0 -DDEBUG
  LDFLAGS += -g
else
  # production flags
  CFLAGS += -Os -DNDEBUG
  LDFLAGS += -s
endif

# profiling information
ifeq (${PROFILING},yes)
  CFLAGS += -pg
  LDFLAGS += -pg
endif

# SDL libraries
ifeq (${SDL},yes)
  CFLAGS += `sdl-config --cflags` -D_SDL
  # if you want the console window on Windows, edit the sdl-config script
  # and remove the '-mwindows' option
  LDFLAGS += `sdl-config --libs` -lSDL_ttf
endif
