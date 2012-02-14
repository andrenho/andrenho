#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([8bitsprite], [0.1], [bug@noadress.com])
AM_INIT_AUTOMAKE([-Wall -Werror])
AC_CONFIG_SRCDIR([src/main.c])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
dnl Check for SDL
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

# Checks for header files.
AC_CONFIG_HEADERS([config.h])

# Checks for typedefs, structures, and compiler characteristics.

# Makefiles
AC_CONFIG_FILES([Makefile src/Makefile data/Makefile])

# Checks for library functions.
AC_OUTPUT
