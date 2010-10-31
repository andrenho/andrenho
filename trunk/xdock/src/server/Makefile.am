AM_CPPFLAGS = -Wall -Wextra -DVERSION=\"$(VERSION)\" -DSHAREDIR=\"$(datarootdir)/$(PACKAGE)\"

bin_PROGRAMS = xdockserver
xdockserver_SOURCES = main.c      client.h   \
		      client.h    client.c   \
		      debug.h     debug.c    \
		      font_led.c  font_led.h \
		      options.h   options.c  \
		      parser.h    parser.c   \
		      network.h   network.c  \
		      structures.h           \
		      uthash.h               \
		      x11.h       x11.c      \
		      x11_cmd.c   x11_cmd.h  \
		      x11_util.c  x11_util.h \
		      font_led_3.xpm
xdockserver_LDFLAGS = $(PTHREAD) $(X11) $(MMS_BITFIELDS) $(WINSOCK)
