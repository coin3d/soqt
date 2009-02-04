############################################################################
## So@Gui@/src/Inventor/@Gui@/makefile.am

include common/Makefile.common

############################################################################
##

if BUILD_WITH_MSVC
SoQt_ExtraDistClean = \
  soqt@SOQT_MAJOR_VERSION@@SUFFIX@.dll \
  soqt@SOQT_MAJOR_VERSION@@SUFFIX@.exp \
  soqt@SOQT_MAJOR_VERSION@@SUFFIX@.pdb
else
SoQt_ExtraDistClean = 
endif

SUBDIRS = devices editors engines nodes viewers widgets

DEFAULT_INCLUDES = -I$(top_builddir)/src -I$(top_builddir)/data -I$(top_srcdir)/src

BUILT_SOURCES = \
	$(SoGuiAllBuiltFiles) \
	moc_SoQtSignalThread.icc

CLEANFILES = \
	$(SoGui_src_Inventor_Gui_BuiltMetaFiles)

DISTCLEANFILES = \
	$(SoQt_ExtraDistClean) \
	$(SoGui_src_Inventor_Gui_BuiltFiles) \
	$(SoGui_src_Inventor_Gui_BuiltMetaFiles) \
	stamp*

############################################################################

if BUILD_WITH_MSVC
lib_LIBRARIES = soqt@SOQT_MAJOR_VERSION@@SUFFIX@.lib
else
lib_LTLIBRARIES = libSoQt@SUFFIX@.la
endif

# On Mac OS 10.2 or later, create two-level namespace binaries and use
# prebinding. Also pad the install_name to make it possible to change it
# later (e.g. to include the library in an app bundle).

if MACOSX_10_2FF
LibtoolLinkArgs = -no-undefined -Wl,-twolevel_namespace -Wl,-undefined,error -Wl,-prebind -Wl,-seg1addr,0x30000000 -Wl,-headerpad_max_install_names 
else
LibtoolLinkArgs = -no-undefined
endif


if MAC_FRAMEWORK
# hack to change libdir value when installing Mac OS X compiler framework
lib@nop@dir = $(MAC_FRAMEWORK_PREFIX)/$(MAC_FRAMEWORK_NAME).framework/Versions/$(MAC_FRAMEWORK_VERSION)/Libraries
endif

############################################################################

RegularSources = \
	SoQt.cpp \
	SoQtP.h \
	SoQtSignalThread.h \
	SoQtSignalThread.cpp \
	SoQtInternal.h \
	SoQtComponent.cpp \
	SoQtComponentP.h \
	SoQtGLWidget.cpp \
	SoQtGLWidgetP.h \
        SoQtImageReader.cpp \
        SoQtImageReader.h

BuiltSources = \
	$(SoGui_src_Inventor_Gui_BuiltFiles)

LinkHackSources = \
	all-soqt-cpp.cpp \
	all-soqt2-cpp.cpp

if HACKING_COMPACT_BUILD
BuildSources = $(LinkHackSources)
NoDistSources =
ExtraSources = $(RegularSources)
else
BuildSources = $(RegularSources)
NoDistSources = $(BuiltSources)
ExtraSources = $(LinkHackSources)
endif

############################################################################
# libtool setup

libSoQt@SUFFIX@_la_SOURCES = \
	$(BuildSources)

nodist_libSoQt@SUFFIX@_la_SOURCES = \
	$(NoDistSources)

libSoQt@SUFFIX@_la_LIBADD = \
	devices/libSoQtDevices.la \
	editors/libSoQtEditors.la \
	engines/libSoGuiEngines.la \
	nodes/libSoGuiNodes.la \
	viewers/libSoQtViewers.la \
	widgets/libSoQtWidgets.la

libSoQt@SUFFIX@_la_LDFLAGS = \
  $(LibtoolLinkArgs) \
  -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)

############################################################################
# custom setup

soqt@SOQT_MAJOR_VERSION@@SUFFIX@_lib_SOURCES = \
	$(BuildSources)

nodist_soqt@SOQT_MAJOR_VERSION@@SUFFIX@_lib_SOURCES = \
	$(NoDistSources)

soqt@SOQT_MAJOR_VERSION@@SUFFIX@_lib_LIBADD = \
	devices/devices.lst \
	editors/editors.lst \
	engines/engines.lst \
	nodes/nodes.lst \
	viewers/viewers.lst \
	widgets/widgets.lst

############################################################################
# header installation

if MAC_FRAMEWORK
SoQtincdir = $(MAC_FRAMEWORK_PREFIX)/$(MAC_FRAMEWORK_NAME).framework/Versions/$(MAC_FRAMEWORK_VERSION)/Headers
else
SoQtincdir = $(includedir)/Inventor/Qt
endif
SoQtinc_HEADERS =

nodist_SoQtinc_HEADERS = \
	SoQt.h \
	SoQtBasic.h \
	SoQtObject.h \
	SoQtCursor.h \
	SoQtComponent.h \
	SoQtGLWidget.h \
	SoQtColorEditor.h \
	SoQtRenderArea.h

install-SoQtincHEADERS: $(SoQtinc_HEADERS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(SoQtincdir)
	@list='$(SoQtinc_HEADERS)'; for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  src="$$d$$p"; dst="$(DESTDIR)$(SoQtincdir)/$$f"; \
	  if cmp -s "$$src" "$$dst"; then :; else \
	    echo " $(INSTALL_HEADER) $$src $$dst"; \
	    $(INSTALL_HEADER) "$$src" "$$dst" || exit 1; \
	  fi \
	done

install-nodist_SoQtincHEADERS: $(nodist_SoQtinc_HEADERS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(SoQtincdir)
	@list='$(nodist_SoQtinc_HEADERS)'; for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  src="$$d$$p"; dst="$(DESTDIR)$(SoQtincdir)/$$f"; \
	  if cmp -s "$$src" "$$dst"; then :; else \
	    echo " $(INSTALL_HEADER) $$src $$dst"; \
	    $(INSTALL_HEADER) "$$src" "$$dst" || exit 1; \
	  fi \
	done

############################################################################

soqt@SOQT_MAJOR_VERSION@@SUFFIX@.lib: Makefile \
  $(soqt@SOQT_MAJOR_VERSION@@SUFFIX@_lib_OBJECTS) \
  $(soqt@SOQT_MAJOR_VERSION@@SUFFIX@_lib_DEPENDENCIES)
	@basename="soqt@SOQT_MAJOR_VERSION@@SUFFIX@"; \
	rm -f "$$basename.lib" "$$basename.dll"; \
	  echo "Linking $@..." \
	  echo $(CC) $(LDFLAGS) $(LIBFLAGS) \
	    $(soqt@SOQT_MAJOR_VERSION@@SUFFIX@_lib_OBJECTS) \
	    $(soqt@SOQT_MAJOR_VERSION@@SUFFIX@_lib_LIBADD) $(LIBS); \
	  $(CC) $(LDFLAGS) $(LIBFLAGS) \
	    $(soqt@SOQT_MAJOR_VERSION@@SUFFIX@_lib_OBJECTS) \
	    $(soqt@SOQT_MAJOR_VERSION@@SUFFIX@_lib_LIBADD) $(LIBS);

############################################################################

if MAC_FRAMEWORK
install-data-local:
	cd $(DESTDIR)$(MAC_FRAMEWORK_PREFIX)/$(MAC_FRAMEWORK_NAME).framework/Versions/Current && ln -sf Libraries/libSoQt.dylib $(MAC_FRAMEWORK_NAME) && cd -; \
  cd $(DESTDIR)$(MAC_FRAMEWORK_PREFIX)/$(MAC_FRAMEWORK_NAME).framework && ln -sf Versions/Current/$(MAC_FRAMEWORK_NAME) $(MAC_FRAMEWORK_NAME) && install_name_tool -id $(MAC_FRAMEWORK_NAME).framework/Versions/$(MAC_FRAMEWORK_VERSION)/$(MAC_FRAMEWORK_NAME) $(MAC_FRAMEWORK_NAME) && cd -;
else
install-data-local:
	@$(NORMAL_INSTALL)
	@basename="soqt@SOQT_MAJOR_VERSION@@SUFFIX@"; \
	if @BUILD_WITH_MSVC@; then \
	  for ext in lib; do \
	    file="$$basename.$$ext"; \
	    if test -f "$$file"; then \
	      $(mkinstalldirs) "$(DESTDIR)$(libdir)"; \
	      echo " $(INSTALL_DATA)" "$$file" "$(DESTDIR)$(libdir)/$$file"; \
	      $(INSTALL_DATA) "$$file" "$(DESTDIR)$(libdir)/$$file" || exit 1; \
	    fi \
	  done; \
	else :; \
	fi
endif

if BUILD_WITH_MSVC
install-exec-local: soqt@SOQT_MAJOR_VERSION@@SUFFIX@.lib
	@basename="soqt@SOQT_MAJOR_VERSION@@SUFFIX@"; \
	if @BUILD_WITH_MSVC@; then \
	  for ext in dll pdb; do \
	    file="$$basename.$$ext"; \
	    if test -f "$$file"; then \
	      $(mkinstalldirs) "$(DESTDIR)$(bindir)"; \
	      echo " $(INSTALL_PROGRAM)" "$$file" "$(DESTDIR)$(bindir)/$$file"; \
	      $(INSTALL_PROGRAM) "$$file" "$(DESTDIR)$(bindir)/$$file" || exit 1; \
	    fi \
	  done; \
	else :; \
	fi
else
install-exec-local:
endif

uninstall-local: uninstall-SoQtincHEADERS uninstall-nodist_SoQtincHEADERS
	@basename="soqt@SOQT_MAJOR_VERSION@@SUFFIX@"; \
	for file in \
	  "$(DESTDIR)$(bindir)/$$basename.dll" \
	  "$(DESTDIR)$(bindir)/$$basename.pdb" \
	  "$(DESTDIR)$(libdir)/$$basename.lib" \
	  "$(DESTDIR)$(MAC_FRAMEWORK_PREFIX)/$(MAC_FRAMEWORK_NAME).framework/$(MAKE_FRAMEWORK_NAME)"; do \
	  if test -f "$$file"; then \
	    echo "rm -f" "$$file"; \
	    rm -f "$$file"; \
	  fi \
	done; \
	baseincdir="$(DESTDIR)$(SoQtincdir)"; \
	for dir in \
	  "$$baseincdir/devices" \
	  "$$baseincdir/viewers" \
	  "$$baseincdir/widgets" \
	  "$$baseincdir"; do \
	  if test -d "$$dir"; then \
	    echo " rmdir" "$$dir"; \
	    rmdir "$$dir" &>/dev/null; \
	  fi \
	done; \
	:

# EOF **********************************************************************
