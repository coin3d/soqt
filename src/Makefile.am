
SUBDIRS = . Inventor

BUILT_SOURCES = \
	soqtdefs.h

DISTCLEANFILES = \
	$(BUILT_SOURCES)

soqtdefs.h: $(srcdir)/Inventor/Qt/common/soguidefs.h.in
	@( cd ..; $(MAKE) built-sources )

install-data-local: soqtdefs.h

