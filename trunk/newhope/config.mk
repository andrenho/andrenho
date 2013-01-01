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
GETTEXT = yes

# basic flags
CFLAGS = -DVERSION=\"${VERSION}\" -DDATADIR=\"${NEWHOPEPREFIX}\" -pedantic -Wall -I. -I/usr/include -std=c99
LINTFLAGS = -DVERSION=\"${VERSION}\" -DDATADIR=\"${NEWHOPEPREFIX}\" -I. -I/usr/include
LDFLAGS = -L/usr/lib

# SDL libraries
ifeq (${SDL},yes)
  CFLAGS += `sdl-config --cflags` -D_SDL
  # if you want the console window on Windows, edit the sdl-config script
  # and remove the '-mwindows' option
  LDFLAGS += `sdl-config --libs` -lSDL_ttf
endif

# PNG library
ifeq (${PNG},yes)
  CFLAGS += `pkg-config --cflags libpng`
  LDFLAGS += `pkg-config --libs libpng` -lz
endif

# gettext
ifeq (${GETTEXT},yes)
  CFLAGS += -DI18N
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
LINT = splint
