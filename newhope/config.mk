#
# CUSTOMIZABLE SECTION
# 

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man
NEWHOPEPREFIX = ${PREFIX}/share/newhope

# add debugging info
DEBUG = yes
PROFILING = no
DUMA = no

#
# PLEASE AVOID CHANGING THE INFORMATION BELOW
#

# New Hope version
VERSION = 0.0.1

# system libraries
SDL = yes
PNG = yes
X11 = no

# basic flags
CFLAGS = -DVERSION=\"${VERSION}\" -DDATADIR=\"${NEWHOPEPREFIX}\" -pedantic -Wall -I. -I/usr/include -std=c99
LDFLAGS = -L/usr/lib

# SDL libraries
ifeq (${SDL},yes)
  CFLAGS += `sdl-config --cflags` -D_SDL
  # if you want the console window on Windows, edit the sdl-config script
  # and remove the '-mwindows' option
  LDFLAGS += `sdl-config --libs`
endif

# PNG library
ifeq (${PNG},yes)
  CFLAGS += `pkg-config --cflags libpng` -lz
  LDFLAGS += `pkg-config --libs libpng` -lz
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

# debugging information
ifeq (${DEBUG},yes)
  # debug flags
  CFLAGS += -g -O0 -DDEBUG
  LDFLAGS += -g
else
  # production flags
  CFLAGS += -Os
  LDFLAGS += -s
endif

# profiling information
ifeq (${PROFILING},yes)
  CFLAGS += -pg
  LDFLAGS += -pg
endif

# compiler and linker
CC = gcc
