## Process this file with automake to generate Makefile.in.

if BUILD_EXAMPLES
EXAMPLEDIR = examples
else
EXAMPLEDIR = 
endif

SUBDIRS = . src/Inventor/Qt $(EXAMPLEDIR)

bin_SCRIPTS = soqt-config

BUILT_SOURCES = \
	soqt-config \
	src/Inventor/Qt/SoQtRenderArea.h \
	src/Inventor/Qt/SoQtRenderArea.cpp \
	src/Inventor/Qt/viewers/SoQtViewer.cpp \
	src/Inventor/Qt/viewers/SoQtViewer.cpp

soqt-config: soqt-config.in

EXTRA_DIST = conf-macros/soqt.m4

m4datadir = $(datadir)/aclocal
m4data_DATA = conf-macros/soqt.m4

############################################################################

src/Inventor/Qt/SoQtRenderArea.h: $(top_srcdir)/src/Inventor/Qt/common/SoAnyRenderArea.h.in
	$(top_builddir)/config.status $@

src/Inventor/Qt/SoQtRenderArea.cpp: $(top_srcdir)/src/Inventor/Qt/common/SoAnyRenderArea.cpp.in
	$(top_builddir)/config.status $@

src/Inventor/Qt/viewers/SoQtViewer.h: $(top_srcdir)/src/Inventor/Qt/common/SoAnyViewer.h.in
	$(top_builddir)/config.status $@

src/Inventor/Qt/viewers/SoQtViewer.cpp: $(top_srcdir)/src/Inventor/Qt/common/SoAnyViewer.cpp.in
	$(top_builddir)/config.status $@

############################################################################
