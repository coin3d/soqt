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

if BUILD_IV_EXAMPLES
IVEXAMPLEDIR = ivexamples
else
IVEXAMPLEDIR = 
endif

SUBDIRS = . src/Inventor/Qt $(TESTDIR) $(EXAMPLEDIR) $(IVEXAMPLEDIR)

bin_SCRIPTS = soqt-config

BUILT_SOURCES = \
	soqt-config \
	src/Inventor/Qt/SoQtRenderArea.h \
	src/Inventor/Qt/SoQtRenderArea.cpp \
	src/Inventor/Qt/viewers/SoQtViewer.h \
	src/Inventor/Qt/viewers/SoQtViewer.cpp \
	src/Inventor/Qt/viewers/SoAnyFullViewer.h \
	src/Inventor/Qt/viewers/SoAnyFullViewer.cpp \
	src/Inventor/Qt/widgets/SoAnyPopupMenu.h \
	src/Inventor/Qt/widgets/SoAnyPopupMenu.cpp

soqt-config: soqt-config.in

EXTRA_DIST = conf-macros/soqt.m4 conf-macros/modifierlist.m4

m4datadir = $(datadir)/aclocal
m4data_DATA = conf-macros/soqt.m4 conf-macros/modifierlist.m4

############################################################################

src/Inventor/Qt/SoQtRenderArea.h: $(top_srcdir)/src/Inventor/Qt/common/SoGuiRenderArea.h.in
	@CONFIG_HEADERS= CONFIG_FILES=$@:src/Inventor/Qt/common/SoGuiRenderArea.h.in ./config.status

src/Inventor/Qt/SoQtRenderArea.cpp: $(top_srcdir)/src/Inventor/Qt/common/SoGuiRenderArea.cpp.in
	@CONFIG_HEADERS= CONFIG_FILES=$@:src/Inventor/Qt/common/SoGuiRenderArea.cpp.in ./config.status

src/Inventor/Qt/viewers/SoQtViewer.h: $(top_srcdir)/src/Inventor/Qt/common/SoGuiViewer.h.in
	@CONFIG_HEADERS= CONFIG_FILES=$@:src/Inventor/Qt/common/SoGuiViewer.h.in $(top_builddir)/config.status

src/Inventor/Qt/viewers/SoQtViewer.cpp: $(top_srcdir)/src/Inventor/Qt/common/SoGuiViewer.cpp.in
	@CONFIG_HEADERS= CONFIG_FILES=$@:src/Inventor/Qt/common/SoGuiViewer.cpp.in $(top_builddir)/config.status

src/Inventor/Qt/viewers/SoAnyFullViewer.h: $(top_srcdir)/src/Inventor/Qt/common/SoAnyFullViewer.h.in
	@CONFIG_HEADERS= CONFIG_FILES=$@:src/Inventor/Qt/common/SoAnyFullViewer.h.in $(top_builddir)/config.status

src/Inventor/Qt/viewers/SoAnyFullViewer.cpp: $(top_srcdir)/src/Inventor/Qt/common/SoAnyFullViewer.cpp.in
	@CONFIG_HEADERS= CONFIG_FILES=$@:src/Inventor/Qt/common/SoAnyFullViewer.cpp.in $(top_builddir)/config.status

src/Inventor/Qt/widgets/SoAnyPopupMenu.h: $(top_srcdir)/src/Inventor/Qt/common/SoAnyPopupMenu.h.in
	@CONFIG_HEADERS= CONFIG_FILES=$@:src/Inventor/Qt/common/SoAnyPopupMenu.h.in $(top_builddir)/config.status

src/Inventor/Qt/widgets/SoAnyPopupMenu.cpp: $(top_srcdir)/src/Inventor/Qt/common/SoAnyPopupMenu.cpp.in
	@CONFIG_HEADERS= CONFIG_FILES=$@:src/Inventor/Qt/common/SoAnyPopupMenu.cpp.in $(top_builddir)/config.status

############################################################################
