AM_CPPFLAGS = -I$(top_srcdir)/src/lib

bin_PROGRAMS = xdclock xdcalendar xdmemory

xdclock_SOURCES = xdclock.c
xdclock_LDADD = -lxdock -L../lib $(MMS_BITFIELDS)

xdcalendar_SOURCES = xdcalendar.c
xdcalendar_LDADD = -lxdock -L../lib $(MMS_BITFIELDS)

xdmemory_SOURCES = xdmemory.c
xdmemory_LDADD = -lxdock -L../lib $(MMS_BITFIELDS)
