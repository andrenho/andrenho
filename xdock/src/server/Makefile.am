AM_CPPFLAGS = -Wall -Wextra

bin_PROGRAMS = xdockserver
xdockserver_SOURCES = main.c \
		      debug.h   debug.c   \
		      options.h options.c \
		      parser.h  parser.c  \
		      network.h network.c \
		      window.h  window.c
xdockserver_LDFLAGS = $(PTHREAD) $(X11)
