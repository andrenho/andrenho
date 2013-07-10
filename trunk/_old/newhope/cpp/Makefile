# New Hope
# See LICENSE file for copyright and license details.

include config.mk

SRC = main.cc		   \
      libs/sdl/sdl.cc      \
      libs/sdl/sdlfont.cc  \
      libs/sdl/sdlimage.cc \
      ui/decorengine.cc    \
      ui/minimap.cc        \
      ui/resource.cc       \
      ui/terrainsurface.cc \
      ui/ui.cc             \
      util/logger.cc       \
      util/i18n.cc         \
      util/polygon.cc      \
      world/city.cc        \
      world/mapbuild.cc    \
      world/person.cc      \
      world/world.cc
TRANSLATIONS = pt_BR
	
OBJ = ${SRC:.cc=.o}
HEADERS = $(filter-out main.h,${SRC:.cc=.h}) libs/graphiclibrary.h \
	util/point.h world/biome.h util/mapcache.h util/defines.h  \
	libs/sdl/sdltimer.h
DIST = AUTHORS HACKING LICENSE NEWS README INSTALL
DATA = $(wildcard data/*.png) $(wildcard data/*.ttf)

all: options newhope translation

options:
	@echo New Hope build options:
	@echo "CPPFLAGS  = ${CPPFLAGS}"
	@echo "LDFLAGS = ${LDFLAGS}"
	@echo "CC      = ${CC}"

.cc.o:
	@echo CC $<
	@${CC} -c ${CPPFLAGS} -o $@ $<

${OBJ}: config.mk

-include depend

newhope: ${OBJ} depend
	@echo CC -o $@
	@${CC} -o $@ ${OBJ} ${LDFLAGS}

po:
	@echo creating PO file
	@xgettext -d newhope -s -o po/newhope.pot --keyword=_ ${SRC}
	@$(foreach t,$(TRANSLATIONS),msginit -l $(t).utf8 -o po/$(t).po -i po/newhope.pot;)

translation:
ifeq (${GETTEXT},yes)
	@echo creating translation files
	@xgettext -d newhope -s -o po/newhope.pot --keyword=_ ${SRC}
	@$(foreach t,$(TRANSLATIONS),msgmerge -s -U po/$(t).po po/newhope.pot;)
	@$(foreach t,$(TRANSLATIONS),mkdir -p po/$(t)/LC_MESSAGES; msgfmt -c -v -o po/$(t)/LC_MESSAGES/newhope.mo po/$(t).po;)
endif

clean:
	@echo cleaning
	@rm -f newhope ${OBJ} newhope-${VERSION}.tar.gz depend

dist: clean
	@echo creating dist tarball
	@mkdir -p newhope-${VERSION}
	@cp --parents config.mk newhope.1 Makefile ${DIST} ${SRC} ${HEADERS} ${DATA} po/newhope.pot $(foreach t,$(TRANSLATIONS), po/$(t).po) newhope-${VERSION}
	@tar -cf newhope-${VERSION}.tar newhope-${VERSION}
	@gzip newhope-${VERSION}.tar
	@rm -rf newhope-${VERSION}

depend: ${SRC}
	@echo checking dependencies
	@${CC} -MM ${CPPFLAGS} ${SRC} ${HEADERS} >depend

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
ifeq (${GETTEXT},yes)
	@echo installing translations to ${LOCALEPREFIX}
	@$(foreach t,$(TRANSLATIONS),mkdir -p ${LOCALEPREFIX}/$(t)/LC_MESSAGES;)
	@$(foreach t,$(TRANSLATIONS),cp -f po/$(t)/LC_MESSAGES/newhope.mo ${LOCALEPREFIX}/$(t)/LC_MESSAGES;)
endif

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/newhope
	@echo removing data from ${DESTDIR}${NEWHOPEPREFIX}
	@rm -f ${DESTDIR}${NEWHOPEPREFIX}/*
	@rmdir ${DESTDIR}${NEWHOPEPREFIX}
	@echo removing manual page from ${DESTDIR}${MANPREFIX}/man1
	@rm -f ${DESTDIR}${MANPREFIX}/man1/newhope.1
	@echo removing translation files, if installed
	@$(foreach t,$(TRANSLATIONS),rm -f ${LOCALEPREFIX}/$(t)/LC_MESSAGES/newhope.mo;)

.PHONY: all options clean po dist install uninstall translation
