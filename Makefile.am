############################################################################
## Makefile.am

include src/Inventor/Qt/common/Makefile.common

############################################################################
##

ACLOCAL_AMFLAGS = -I cfg/m4
SUFFIXES = .cpp .h .m4 .in .o .lo .Plo .TPlo

############################################################################
## 

if BUILD_HTMLPAGES
HTMLDIR = html
else
HTMLDIR =
endif

if BUILD_LIBRARY
LIBDIR = data src
else
LIBDIR =
endif

SUBDIRS = . $(LIBDIR) man $(HTMLDIR)

BUILT_SOURCES = \
	$(SoGuiAllBuiltFiles)

CLEANFILES = \
	$(SoGui_BuiltMetaFiles)

DISTCLEANFILES = \
	libtool \
	build/so@gui@.spec \
	build/so@gui@.doxygen \
	$(SoGui_BuiltFiles) \
	$(SoGui_BuiltMetaFiles)

if BUILD_LIBRARY

if MAC_FRAMEWORK
dynbindir = /usr/local/bin
else
dynbindir = $(bindir)
endif

dynbin_SCRIPTS = so@gui@-config

m4datadir = $(datadir)/aclocal
# Don't replace "qt" with "@gui@" here, is it will pøkk up
# for ``make dist''.
dist_m4data_DATA = cfg/m4/soqt.m4

cfgdatadir = $(datadir)/Coin/conf
cfgdata_DATA = so@gui@-@CONFIG@.cfg

endif

EXTRA_DIST = \
	LICENSE.LGPL \
	FAQ \
	HACKING \
	README.DLL \
	README.IRIX \
	README.WIN32 \
	build/soqt.spec.in \
	build/soqt.doxygen.in \
	cfg/m4/doxy4win.pl \
	cfg/m4/soqt.m4 \
	cfg/m4/wrapmsvc.cpp \
	cfg/m4/wrapmsvc.exe \
	models/coin_soqt.iv \
	models/coin_soqt.wrl \
	test-code/README \
	test-code/components/scrollview.cpp \
	test-code/components/tripleview.cpp \
	$(SoGuiCommonDistFiles)

# Target which is present to make it simple to only generate all the source
# files from the common sources.

built-sources: $(BUILT_SOURCES)

############################################################################

all-local: built-sources

if BUILD_LIBRARY
if MAC_FRAMEWORK
## FIXME: this may be better suited in install-data-local  20011205 larsa
install-exec-local:
	@$(NORMAL_INSTALL)
	@echo "Setting up Mac OS X framework"
	@$(mkinstalldirs) $(DESTDIR)$(prefix)/Versions/$(MAC_FRAMEWORK_VER)
	@ln -sf $(MAC_FRAMEWORK_VER) $(DESTDIR)$(prefix)/Versions/Current
	@ln -sf Versions/Current/Headers $(DESTDIR)$(prefix)/Headers
	@ln -sf Versions/Current/Resources $(DESTDIR)$(prefix)/Resources
#	@ln -sf Versions/Current/Libraries $(DESTDIR)$(prefix)/Libraries
	@case "$(ivincludedir)" in \
	/Library/Frameworks/Inventor.framework/* ) \
	  echo " ln -sf $(prefix)/Headers $(ivincludedir)/Qt"; \
	  ln -sf $(prefix)/Headers $(ivincludedir)/Qt; \
	  ;; \
	esac
else
install-exec-local: built-sources $(srcdir)/cfg/m4/wrapmsvc.exe
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(bindir)
	@if @BUILD_WITH_MSVC@; then \
	  p=wrapmsvc.exe; \
	  if cmp -s "$(srcdir)/cfg/m4/$$p" "$(DESTDIR)$(bindir)/$$p"; then \
	    echo " $(INSTALL_PROGRAM) $(srcdir)/cfg/m4/$$p $(DESTDIR)$(bindir)/$$p"; \
	    $(INSTALL_PROGRAM) $(srcdir)/cfg/m4/$$p $(DESTDIR)$(bindir)/$$p; \
	  fi \
	fi
endif
endif

install-data-local: built-sources

# **************************************************************************
# misc rules for automatic Microsoft Windows packaging.
# main: `windows-packages'

windows-files:
	@if test -d windows; then :; else mkdir windows; fi
	@for file in $(top_srcdir)/packaging/windows/*.in; do \
	  basename=`echo $$file | sed 's/^.*\///g; s/\.in$$//'`; \
	  ./config.status --file=windows/$$basename:$$file; \
	done

windows-packages: windows-files
	@( cd windows; $(MAKE) VERSION=$(VERSION) )

# EOF ######################################################################
