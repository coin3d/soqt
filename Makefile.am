############################################################################
## Makefile.am

include src/Inventor/Qt/common/Makefile.common

############################################################################
## 

if BUILD_HTMLPAGES
HTMLDIR = html
else
HTMLDIR =
endif

if BUILD_LIBRARY
# Material editor(s) not part of the public API yet, so there's
# no point yet in installing the material data.
#LIBDIR = data src
LIBDIR = src
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
	$(SoGui_BuiltFiles) \
	$(SoGui_BuiltMetaFiles)

if BUILD_LIBRARY
if MAC_FRAMEWORK
frameworkdatadir = $(MAC_FRAMEWORK_PREFIX)/$(MAC_FRAMEWORK_NAME).framework/Versions/$(MAC_FRAMEWORK_VERSION)/Resources
frameworkdata_DATA = Info.plist
endif


bin_SCRIPTS = so@gui@-config

m4datadir = $(datadir)/aclocal

# Don't replace "qt" with "@gui@" here, is it will pøkk up
# for ``make dist''.
dist_m4data_DATA = cfg/m4/soqt.m4

cfgdatadir = $(datadir)/Coin/conf
cfgdata_DATA = so@gui@-@CONFIG@.cfg

endif

EXTRA_DIST = \
	FAQ \
	LICENSE.GPL \
	README.DLL \
	README.IRIX \
	README.WIN32 \
	README.MAC \
	Info.plist \
	cfg/m4/soqt.m4 \
	models/coin_soqt.iv \
	models/coin_soqt.wrl \
	test-code/README \
	test-code/components/scrollview.cpp \
	test-code/components/tripleview.cpp \
	packaging/windows/Makefile.in \
	packaging/windows/footer.nsi.in \
	packaging/windows/heading.nsi.in \
	packaging/windows/middle.nsi.in \
	packaging/windows/post.nsi.in \
	packaging/windows/soqt-sdk.html.in \
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
	@$(mkinstalldirs) $(DESTDIR)$(MAC_FRAMEWORK_PREFIX)/$(MAC_FRAMEWORK_NAME).framework/Versions/$(MAC_FRAMEWORK_VERSION)
	@ln -sf $(MAC_FRAMEWORK_VERSION) $(DESTDIR)$(MAC_FRAMEWORK_PREFIX)/$(MAC_FRAMEWORK_NAME).framework/Versions/Current
	@ln -sf Versions/Current/Headers $(DESTDIR)$(MAC_FRAMEWORK_PREFIX)/$(MAC_FRAMEWORK_NAME).framework/Headers
	@ln -sf Versions/Current/Resources $(DESTDIR)$(MAC_FRAMEWORK_PREFIX)/$(MAC_FRAMEWORK_NAME).framework/Resources
#	@case "@ivincludedir@" in \
#	/Library/Frameworks/Inventor.framework/* ) \
#	  echo " ln -sf $(prefix)/Headers $(ivincludedir)/Qt"; \
#	  ln -sf $(prefix)/Headers $(ivincludedir)/Qt; \
#	  ;; \
#	esac
else
install-exec-local: built-sources $(srcdir)/cfg/m4/wrapmsvc.exe
	@$(NORMAL_INSTALL)
	@if @BUILD_WITH_MSVC@; then \
	  echo " $(mkinstalldirs) $(DESTDIR)$(bindir)"; \
	  $(mkinstalldirs) "$(DESTDIR)$(bindir)"; \
	  p=wrapmsvc.exe; \
	  echo " $(INSTALL_PROGRAM) $(top_srcdir)/cfg/m4/$$p $(DESTDIR)$(bindir)/$$p"; \
	  $(INSTALL_PROGRAM) "$(top_srcdir)/cfg/m4/$$p" "$(DESTDIR)$(bindir)/$$p"; \
	fi
endif
endif

install-data-local: built-sources

# **************************************************************************
# misc rules for automatic Microsoft Windows packaging.
# main: `windows-packages'

windows-files:
	@if test -d windows; then :; else \
	  echo " mkdir windows"; \
	  mkdir windows; \
	fi
	@for file in $(top_srcdir)/packaging/windows/*.in; do \
	  basename=`echo $$file | sed 's%^.*/%%g; s%\.in$$%%'`; \
	  echo " config.status: generating windows/$$basename"; \
	  ./config.status --file=-:- >"windows/$$basename" <"$$file"; \
	done

windows-packages: windows-files
	@( cd windows; $(MAKE) VERSION=$(VERSION) )

# EOF ######################################################################
