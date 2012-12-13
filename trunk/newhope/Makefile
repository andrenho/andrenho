# Vintage Terminal
# See LICENSE file for copyright and license details.

include config.mk

SRC = main.c		\
      options.c         \
      ui/buildtile.c    \
      ui/event.c        \
      ui/resource.c     \
      ui/ui.c           \
      util/log.c	\
      util/numbers.c    \
      util/strings.c	\
      world/world.c
OBJ = ${SRC:.c=.o}
HEADERS = ${SRC:.c=.h} util/uthash.h
DIST = AUTHORS HACKING LICENSE NEWS README INSTALL
DATA =

all: options newhope

options:
	@echo New Hope build options:
	@echo "CFLAGS  = ${CFLAGS}"
	@echo "LDFLAGS = ${LDFLAGS}"
	@echo "CC      = ${CC}"

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} -o $@ $<

${OBJ}: config.mk

newhope: ${OBJ} depend
	@echo CC -o $@
	@${CC} -o $@ ${OBJ} ${LDFLAGS}
-include depend

clean:
	@echo cleaning
	@rm -f newhope ${OBJ} newhope-${VERSION}.tar.gz depend

dist: clean
	@echo creating dist tarball
	@mkdir -p newhope-${VERSION}
	@cp --parents config.mk newhope.1 Makefile ${DIST} ${SRC} ${HEADERS} ${DATA} newhope-${VERSION}
	@tar -cf newhope-${VERSION}.tar newhope-${VERSION}
	@gzip newhope-${VERSION}.tar
	@rm -rf newhope-${VERSION}

depend: ${SRC}
	@echo checking dependencies
	@${CC} -MM ${CFLAGS} ${SRC} >depend

install: all
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f newhope ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/newhope
	@echo installing data to ${DESTDIR}${NEWHOPEPREFIX}
	@mkdir -p ${DESTDIR}${NEWHOPEPREFIX}
	@cp -f ${DATA} ${DESTDIR}${NEWHOPEPREFIX}
	@echo installing manual page to ${DESTDIR}${MANPREFIX}/man1
	@mkdir -p ${DESTDIR}${MANPREFIX}/man1
	@sed "s/VERSION/${VERSION}/g" < newhope.1 > ${DESTDIR}${MANPREFIX}/man1/newhope.1
	@chmod 644 ${DESTDIR}${MANPREFIX}/man1/newhope.1
	@echo compiling terminfo data
	@tic -s data/newhope.info

# TODO - check data
uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/st
	@echo removing data from ${DESTDIR}${NEWHOPEPREFIX}
	@rm -f ${DESTDIR}${NEWHOPEPREFIX}/*
	@rmdir ${DESTDIR}${NEWHOPEPREFIX}
	@echo removing manual page from ${DESTDIR}${MANPREFIX}/man1
	@rm -f ${DESTDIR}${MANPREFIX}/man1/newhope.1

.PHONY: all options clean dist install uninstall
