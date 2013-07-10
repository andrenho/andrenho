lib_LTLIBRARIES = libxdock.la

libxdock_la_SOURCES = xdock.h libxdock.c network.h network.c
#libapplet_la_LIBADD = $(DEPS_LIBS)
libxdock_la_LIBADD = $(WINSOCK)
libxdock_la_LDFLAGS = -no-undefined -version-info 2:0:0
#AM_CPPFLAGS = $(DEPS_CFLAGS) @MMS_BITFIELDS@

include_HEADERS = xdock.h

install-exec-hook:
	ldconfig
