############################################################################
## So@Gui@/src/Inventor/@Gui@/makefile.am

include common/Makefile.common

############################################################################
##

SUBDIRS = devices viewers widgets

INCLUDES = -I$(top_srcdir)/src

BUILT_SOURCES = \
	$(SoGuiAllBuiltfiles)

CLEANFILES = \
	$(SoGui_src_Inventor_Gui_BuiltMetaFiles)

DISTCLEANFILES = \
	$(SoGui_src_Inventor_Gui_BuiltFiles) \
	$(SoGui_src_Inventor_Gui_BuiltMetaFiles)

############################################################################

if BUILD_WITH_MSVC
lib_LIBRARIES = soqt@SOQT_MAJOR_VERSION@@SUFFIX@.lib
else
lib_LTLIBRARIES = libSoQt@SUFFIX@.la
endif

############################################################################
# libtool setup

libSoQt@SUFFIX@_la_SOURCES = \
	SoQt.cpp \
	SoQtComponent.cpp \
	SoQtGLWidget.cpp \
	SoQtLightSliderSet.cpp \
	SoQtLightSliderSet.h \
	SoQtMaterialSliderSet.cpp \
	SoQtMaterialSliderSet.h \
	SoQtSliderSet.cpp \
	SoQtSliderSet.h \
	SoQtSliderSetBase.cpp \
	SoQtSliderSetBase.h \
	SoQtTransformSliderSet.cpp \
	SoQtTransformSliderSet.h

nodist_libSoQt@SUFFIX@_la_SOURCES = \
	$(SoGui_src_Inventor_Gui_BuiltFiles) \
	$(SoGui_src_Inventor_Gui_BuiltMetaFiles)

libSoQt@SUFFIX@_la_LIBADD = \
	devices/libSoQtDevices.la \
	viewers/libSoQtViewers.la \
	widgets/libSoQtWidgets.la

libSoQt@SUFFIX@_la_LDFLAGS = \
        -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)

############################################################################
# custom setup

soqt@SOQT_MAJOR_VERSION@@SUFFIX@_lib_SOURCES = \
	SoQt.cpp \
	SoQtComponent.cpp \
	SoQtGLWidget.cpp \
	SoQtLightSliderSet.cpp \
	SoQtLightSliderSet.h \
	SoQtMaterialSliderSet.cpp \
	SoQtMaterialSliderSet.h \
	SoQtSliderSet.cpp \
	SoQtSliderSet.h \
	SoQtSliderSetBase.cpp \
	SoQtSliderSetBase.h \
	SoQtTransformSliderSet.cpp \
	SoQtTransformSliderSet.h

nodist_soqt@SOQT_MAJOR_VERSION@@SUFFIX@_lib_SOURCES = \
	$(SoGui_src_Inventor_Gui_BuiltFiles) \
	$(SoGui_src_Inventor_Gui_BuiltMetaFiles)

soqt@SOQT_MAJOR_VERSION@@SUFFIX@_lib_LIBADD = \
	devices/devices.lst \
	viewers/viewers.lst \
	widgets/widgets.lst

############################################################################
# header installation

SoQtincdir = $(includedir)/Inventor/Qt
SoQtinc_HEADERS = \
	SoQtLightSliderSet.h \
	SoQtMaterialSliderSet.h \
	SoQtSliderSet.h \
	SoQtSliderSetBase.h \
	SoQtTransformSliderSet.h

nodist_SoQtinc_HEADERS = \
	SoQt.h \
	SoQtBasic.h \
	SoQtObject.h \
	SoQtCursors.h \
	SoQtComponent.h \
	SoQtGLWidget.h \
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
	    $(INSTALL_HEADER) "$$src" "$$dst"; \
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
	    $(INSTALL_HEADER) "$$src" "$$dst"; \
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

install-exec-local:
	@basename="soqt@SOQT_MAJOR_VERSION@@SUFFIX@"; \
	if @BUILD_WITH_MSVC@; then \
	  for ext in dll pdb; do \
	    file="$$basename.$$ext"; \
	    if test -f "$$file"; then \
	      $(mkinstalldirs) "$(DESTDIR)$(bindir)"; \
	      echo " $(INSTALL_PROGRAM)" "$$file" "$(DESTDIR)$(bindir)/$$file"; \
	      $(INSTALL_PROGRAM) "$$file" "$(DESTDIR)$(bindir)/$$file"; \
	    fi \
	  done; \
	else :; fi

install-data-local:
	@basename="soqt@SOQT_MAJOR_VERSION@@SUFFIX@"; \
	if @BUILD_WITH_MSVC@; then \
	  for ext in lib; do \
	    file="$$basename.$$ext"; \
	    if test -f "$$file"; then \
	      $(mkinstalldirs) "$(DESTDIR)$(libdir)"; \
	      echo " $(INSTALL_DATA)" "$$file" "$(DESTDIR)$(libdir)/$$file"; \
	      $(INSTALL_DATA) "$$file" "$(DESTDIR)$(libdir)/$$file"; \
	    fi \
	  done; \
	else :; fi

uninstall-local: uninstall-SoQtincHEADERS uninstall-nodist_SoQtincHEADERS
	@basename="soqt@SOQT_MAJOR_VERSION@@SUFFIX@"; \
	for file in \
	  "$(DESTDIR)$(bindir)/$$basename.dll" \
	  "$(DESTDIR)$(bindir)/$$basename.pdb" \
	  "$(DESTDIR)$(libdir)/$$basename.lib"; do \
	  if test -f "$$file"; then \
	    echo " rm -f" "$$file"; \
	    echo rm -f "$$file"; \
	  fi \
	done; \
	baseincdir="$(DESTDIR)$(includedir)/Inventor/Qt"; \
	for dir in \
	  "$$baseincdir/devices" \
	  "$$baseincdir/viewers" \
	  "$$baseincdir"; do \
	  if test -d "$$dir"; then \
	    echo " rmdir" "$$dir"; \
	    rmdir "$$dir" &>/dev/null; \
	  fi \
	done; \
	:

# EOF **********************************************************************
