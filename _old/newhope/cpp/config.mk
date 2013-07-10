#
# CUSTOMIZABLE SECTION
# 

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man
NEWHOPEPREFIX = ${PREFIX}/share/newhope
LOCALEPREFIX = /usr/share/locale

# parse translations
GETTEXT = yes

# add debugging info
DEBUG = yes
PROFILING = no
DUMA = no


#
# PLEASE AVOID CHANGING THE INFORMATION BELOW, UNLESS NECESSARY
#

# New Hope version
VERSION = 0.0.1

# system libraries
SDL = yes
PNG = yes

# basic flags
CPPFLAGS = -DVERSION=\"${VERSION}\" -DDATADIR=\"${NEWHOPEPREFIX}\" -Wall -Wfatal-errors -I. -I/usr/include -std=c++11
LDFLAGS = -L/usr/lib -lm

UNAME = $(shell uname -o)

# SDL libraries
ifeq (${SDL},yes)
  CPPFLAGS += `sdl-config --cflags` -D_SDL
  # if you want the console window on Windows, edit the sdl-config script
  # and remove the '-mwindows' option
  LDFLAGS += `sdl-config --libs` -lSDL_ttf
endif

# PNG library
ifeq (${PNG},yes)
  CPPFLAGS += `pkg-config --cflags libpng`
  LDFLAGS += `pkg-config --libs libpng` -lz
endif

# gettext
ifeq (${GETTEXT},yes)
  CPPFLAGS += -DI18N -DLOCALEDIR=\"${LOCALEPREFIX}\"
  ifeq (${UNAME},Msys)
    LDFLAGS += -lintl
  endif
endif

# Duma libraries
ifeq (${DUMA}, yes)
  LDFLAGS += -lduma
endif

# debugging information
ifeq (${DEBUG},yes)
  # debug flags
  CPPFLAGS += -g -O0 -DDEBUG
  LDFLAGS += -g
else
  # production flags
  CPPFLAGS += -Os -DNDEBUG
  LDFLAGS += -s
endif

# profiling information
ifeq (${PROFILING},yes)
  CPPFLAGS += -pg
  LDFLAGS += -pg
endif

# compiler and linker
CC = g++
#CC = clang++
