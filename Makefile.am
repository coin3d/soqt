############################################################################
## Makefile.am

include src/Inventor/Qt/common/Makefile.common

############################################################################
##

ACLOCAL_AMFLAGS = -I cfg/m4
SUFFIXES = .cpp .h .m4 .in .o .lo .Plo .TPlo

############################################################################
## 

SUBDIRS = . src

BUILT_SOURCES = \
	$(SoGuiAllBuiltFiles)

CLEANFILES = \
	$(SoGui_BuiltMetaFiles)

DISTCLEANFILES = \
	libtool \
	build/so@gui@.doxygen \
	$(SoGui_BuiltFiles) \
	$(SoGui_BuiltMetaFiles)

bin_SCRIPTS = so@gui@-config

m4datadir = $(datadir)/aclocal
dist_m4data_DATA = so@gui@.m4

cfgdatadir = $(datadir)/Coin/conf
cfgdata_DATA = so@gui@-@CONFIG@.cfg

EXTRA_DIST = \
	LICENSE.LGPL \
	HACKING \
	README.DLL \
	README.IRIX \
	README.WIN32 \
	build/so@gui@.doxygen.in \
	build/so@gui@.spec.in \
	cfg/doxy4win.pl \
	cfg/m4/wrapmsvc.cpp \
	cfg/m4/wrapmsvc.exe \
	models/coin_soqt.iv \
	models/coin_soqt.wrl \
	test-code/README \
	test-code/components/scrollview.cpp \
	test-code/components/tripleview.cpp \
	$(So@Gui@CommonDistFiles)

# This is necessary to set up a hook somewhere in the generated Makefile
# so the sources are actually built.

# this messes up "make distclean"
# Makefile: $(So@Gui@BuiltSources)

# Target which is present to make it simple to only generate all the source
# files from the common sources.

built-sources: $(BUILT_SOURCES)

############################################################################

all-local: built-sources

doxygen-doc: built-sources
	@( cd build; @sim_ac_doxygen_exe@ so@gui@.doxygen )

doxygen-docs: built-sources
	@( cd build; @sim_ac_doxygen_exe@ so@gui@.doxygen )

install-exec-local: built-sources $(srcdir)/cfg/m4/wrapmsvc.exe
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(bindir)
	@if @BUILD_WITH_MSVC@; then \
	  p=wrapmsvc.exe; \
	  echo " $(INSTALL_PROGRAM) $(srcdir)/cfg/m4/$$p $(DESTDIR)$(bindir)/$$p"; \
	  $(INSTALL_PROGRAM) $(srcdir)/cfg/m4/$$p $(DESTDIR)$(bindir)/$$p; \
	fi

install-data-local: built-sources

# EOF ######################################################################
