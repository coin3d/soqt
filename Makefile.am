## Process this file with automake to generate Makefile.in.

SUFFIXES = .cpp .h .m4 .in .o .lo .Plo .TPlo

if BUILD_TESTS
TESTDIR = test-code
else
TESTDIR =
endif

if BUILD_EXAMPLES
EXAMPLEDIR = examples
else
EXAMPLEDIR = 
endif

SUBDIRS = . src/Inventor/Qt $(TESTDIR) $(EXAMPLEDIR)

bin_SCRIPTS = soqt-config

BUILT_SOURCES = \
	soqt-config \
	src/Inventor/Qt/SoQtRenderArea.h \
	src/Inventor/Qt/SoQtRenderArea.cpp \
	src/Inventor/Qt/viewers/SoQtViewer.h \
	src/Inventor/Qt/viewers/SoQtViewer.cpp

soqt-config: soqt-config.in

EXTRA_DIST = conf-macros/soqt.m4 conf-macros/modifierlist.m4

m4datadir = $(datadir)/aclocal
m4data_DATA = conf-macros/soqt.m4 conf-macros/modifierlist.m4

############################################################################

src/Inventor/Qt/SoQtRenderArea.h: $(top_srcdir)/src/Inventor/Qt/common/SoAnyRenderArea.h.in
	@CONFIG_HEADERS= CONFIG_FILES=$@:src/Inventor/Qt/common/SoAnyRenderArea.h.in ./config.status

src/Inventor/Qt/SoQtRenderArea.cpp: $(top_srcdir)/src/Inventor/Qt/common/SoAnyRenderArea.cpp.in
	@CONFIG_HEADERS= CONFIG_FILES=$@:src/Inventor/Qt/common/SoAnyRenderArea.cpp.in ./config.status

src/Inventor/Qt/viewers/SoQtViewer.h: $(top_srcdir)/src/Inventor/Qt/common/SoAnyViewer.h.in
	@CONFIG_HEADERS= CONFIG_FILES=$@:src/Inventor/Qt/common/SoAnyViewer.h.in $(top_builddir)/config.status

src/Inventor/Qt/viewers/SoQtViewer.cpp: $(top_srcdir)/src/Inventor/Qt/common/SoAnyViewer.cpp.in
	@CONFIG_HEADERS= CONFIG_FILES=$@:src/Inventor/Qt/common/SoAnyViewer.cpp.in $(top_builddir)/config.status

############################################################################
