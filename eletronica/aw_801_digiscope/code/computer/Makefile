# New Hope
# See LICENSE file for copyright and license details.

include config.mk

SRC = main.c

OBJ = ${SRC:.c=.o}
DIST =
HEADERS =
DATA =

all: options osc

options:
	@echo osc build options:
	@echo "CFLAGS  = ${CFLAGS}"
	@echo "LDFLAGS = ${LDFLAGS}"
	@echo "CC      = ${CC}"

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} -o $@ $<

${OBJ}: config.mk

-include depend

osc: ${OBJ} 
	@echo CC -o $@
	@${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	@echo cleaning
	@rm -f osc ${OBJ} osc-${VERSION}.tar.gz depend

dist: clean
	@echo creating dist tarball
	@mkdir -p osc-${VERSION}
	@cp --parents config.mk Makefile ${DIST} ${SRC} ${HEADERS} ${DATA}
	@tar -cf osc-${VERSION}.tar osc-${VERSION}
	@gzip osc-${VERSION}.tar
	@rm -rf osc-${VERSION}

install: all
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f osc ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/osc
	@echo installing data to ${DESTDIR}${NEWHOPEPREFIX}
	@mkdir -p ${DESTDIR}${NEWHOPEPREFIX}
	@cp -f ${DATA} ${DESTDIR}${NEWHOPEPREFIX}

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/osc
	@echo removing data from ${DESTDIR}${NEWHOPEPREFIX}
	@rm -f ${DESTDIR}${NEWHOPEPREFIX}/*
	@rmdir ${DESTDIR}${NEWHOPEPREFIX}

.PHONY: all options clean dist install uninstall
