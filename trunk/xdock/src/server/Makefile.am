AM_CPPFLAGS = -Wall -Wextra

bin_PROGRAMS = xdockserver
xdockserver_SOURCES = main.c      client.h   \
		      client.h    client.c   \
		      debug.h     debug.c    \
		      options.h   options.c  \
		      parser.h    parser.c   \
		      network.h   network.c  \
		      uthash.h               \
		      x11.h       x11.c      \
		      x11_cmd.c   x11_cmd.h  \
		      x11_util.c  x11_util.h \
		      font_led_3.xpm
xdockserver_LDFLAGS = $(PTHREAD) $(X11) $(MMS_BITFIELDS) $(WINSOCK)
