
SUBDIRS = . Inventor

BUILT_SOURCES = \
	soqtdefs.h

DISTCLEANFILES = \
	$(BUILT_SOURCES)

EXTRA_DIST = \
	soqtdefs.h.in

soqtdefs.h: $(srcdir)/soqtdefs.h.in
	@( cd ..; $(MAKE) built-sources )

install-data-local: soqtdefs.h

