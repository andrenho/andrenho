# New Hope version
VERSION = 0.0.1

# system libraries
SDL = yes
X11 = no

# add debugging info
DEBUG = yes
DUMA = no

# Customize below to fit your system

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man
NEWHOPEPREFIX = ${PREFIX}/share/newhope

# basic flags
CFLAGS = -DVERSION=\"${VERSION}\" -DDATADIR=\"${NEWHOPEPREFIX}\" -pedantic -Wall -I. -I/usr/include -std=c99
LDFLAGS = -L/usr/lib

# SDL libraries
ifeq (${SDL},yes)
  CFLAGS += `sdl-config --cflags` -D_SDL
  LDFLAGS += `sdl-config --libs` -lSDL_image
endif

# X11 libraries
ifeq (${X11},yes)
  CFLAGS += -I/usr/X11R6/include -D_X11
  LDFLAGS += -L/usr/X11R6/lib -lX11
endif

# Duma libraries
ifeq (${DUMA}, yes)
  LDFLAGS += -lduma
endif

ifeq (${DEBUG},yes)
  # debug flags
  CFLAGS += -g -O0 -DDEBUG
  LDFLAGS += -g
else
  # production flags
  CFLAGS += -Os
  LDFLAGS += -s
endif

# compiler and linker
CC = gcc
