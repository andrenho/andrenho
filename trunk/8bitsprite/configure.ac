#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([8bitsprite], [0.1], [bug@noadress.com])
AM_INIT_AUTOMAKE([-Wall])
AC_CONFIG_SRCDIR([src/main.c])

# Checks for programs, clear CFLAGS
OLD_CFLAGS=$CFLAGS
AC_PROG_CC
CFLAGS=$OLD_CFLAGS

# debug compilation support
AC_MSG_CHECKING([whether to build with debug information])
AC_ARG_ENABLE([debug],
    [AS_HELP_STRING([--enable-debug],
        [enable debug data generation (def=no)])],
    [debugit="$enableval"],
    [debugit=no])
AC_MSG_RESULT([$debugit])
if test x"$debugit" = x"yes"; then
    AC_DEFINE([DEBUG],[],[Debug Mode])
    AM_CFLAGS="$AM_CFLAGS -g -Wall -Wno-uninitialized -O0"
else
    AC_DEFINE([NDEBUG],[],[No-debug Mode])
    AM_CFLAGS="$AM_CFLAGS -O3"
fi
AC_SUBST([AM_CFLAGS])

# Checks for SDL libraries
SDL_VERSION=1.2.0
AM_PATH_SDL($SDL_VERSION,
            :,
            AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!])
)
CFLAGS="$CFLAGS $SDL_CFLAGS"
LIBS="$LIBS $SDL_LIBS"
AC_CHECK_LIB(SDL_ttf, TTF_Init, [], [
	echo "Error! You need to have the SDL_ttf library."
	exit -1
	])
AC_CHECK_LIB(SDL_image, IMG_Init, [], [
	echo "Error! You need to have the SDL_image library."
	exit -1
	])

# Check for libtar
AC_CHECK_LIB(archive, archive_write_new, [], [
	echo "Error! You need to have the libarchive library."
	exit -1
	])

# Checks for header files.
AC_CONFIG_HEADERS([config.h])

# Checks for typedefs, structures, and compiler characteristics.

# Makefiles
AC_CONFIG_FILES([Makefile src/Makefile data/Makefile])

# Checks for library functions.
AC_OUTPUT
