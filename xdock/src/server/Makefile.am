AM_CPPFLAGS = -Wall

bin_PROGRAMS = xdockserver
xdockserver_SOURCES = main.c \
		      debug.h   debug.c   \
		      options.h options.c \
		      network.h network.c \
		      window.h  window.c
xdockserver_LDFLAGS = $(PTHREAD) $(X11)
