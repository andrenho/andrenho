# AC_PREREQ(2.50)
AC_INIT(xdock, 0.3.0)
AM_INIT_AUTOMAKE([-Wall])
AM_CONFIG_HEADER(config.h)

# Checks for programs.
AC_PROG_LIBTOOL
AC_PROG_INSTALL
AC_PROG_CC
AC_LANG_C
AC_PROG_MAKE_SET

# Check for X
AC_PATH_X
AC_CHECK_LIB(X11, XFlush, [X11=-lX11], [
		echo "Unable to find Xlib libraries. You must have the Xlib development libraries installed in order to install xdock."
		exit -1
])
AC_SUBST([X11])

# Check for pthreads
AC_CHECK_LIB([pthread], [pthread_create], [PTHREAD=-lpthread])
AC_SUBST([PTHREAD])

# Checks for typedefs, structures, and compiler characteristics.
case $OSTYPE in
  *msys*) MMS_BITFIELDS='-mms-bitfields' ; WINSOCK='-lws2_32' ; X11='-lX11 -lXau' ;;
  *)      MMS_BITFIELDS='' ; WINSOCK='' ;;
esac
AC_SUBST([MMS_BITFIELDS])
AC_SUBST([WINSOCK])

# Checks for library functions.
AC_CONFIG_FILES([Makefile
                 share/Makefile
                 src/Makefile
                 src/server/Makefile
                 src/lib/Makefile
                 src/docks/Makefile])
AC_OUTPUT
