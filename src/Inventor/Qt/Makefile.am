############################################################################

SUBDIRS = devices viewers widgets

############################################################################

INCLUDES = -I$(top_builddir)/src -I$(top_srcdir)/src

if BUILD_WITH_MSVC
lib_LIBRARIES = soqt@SOQT_MAJOR_VERSION@@SUFFIX@.lib
else
lib_LTLIBRARIES = libSoQt@SUFFIX@.la
endif

BUILT_SOURCES = \
	SoAny.h \
	SoAny.cpp \
	SoQtBasic.h \
	SoQtObject.cpp \
	SoQtObject.h \
	SoQtCursors.h \
	SoQtCursors.cpp \
	SoQtRenderArea.h \
	SoQtRenderArea.cpp \
	moc_SoQt.cpp \
	moc_SoQtObject.cpp \
	moc_SoQtComponent.cpp \
	moc_SoQtGLWidget.cpp \
	moc_SoQtLightSliderSet.cpp \
	moc_SoQtMaterialSliderSet.cpp \
	moc_SoQtRenderArea.cpp \
	moc_SoQtSliderSet.cpp \
	moc_SoQtSliderSetBase.cpp \
	moc_SoQtTransformSliderSet.cpp

SOQTSOURCES = \
	$(BUILT_SOURCES) \
	SoQt.cpp \
	SoQt.h \
	SoQtComponent.cpp \
	SoQtComponent.h \
	SoQtGLWidget.cpp \
	SoQtGLWidget.h \
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

############################################################################
# libtool setup

libSoQt@SUFFIX@_la_SOURCES = \
	$(SOQTSOURCES)

libSoQt@SUFFIX@_la_LIBADD = \
	devices/libSoQtDevices.la \
	viewers/libSoQtViewers.la \
	widgets/libSoQtWidgets.la

libSoQt@SUFFIX@_la_LDFLAGS = \
        -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)

############################################################################
# custom setup

soqt@SOQT_MAJOR_VERSION@@SUFFIX@_lib_SOURCES = \
	$(SOQTSOURCES)

soqt@SOQT_MAJOR_VERSION@@SUFFIX@_lib_LIBADD = \
	devices/devices.lst \
	viewers/viewers.lst \
	widgets/widgets.lst

############################################################################
# header installation

libSoQt@SUFFIX@incdir = $(includedir)/Inventor/Qt

libSoQt@SUFFIX@inc_HEADERS = \
	$(top_srcdir)/src/Inventor/Qt/SoQt.h \
	$(top_builddir)/src/Inventor/Qt/SoQtBasic.h \
	$(top_builddir)/src/Inventor/Qt/SoQtObject.h \
	$(top_srcdir)/src/Inventor/Qt/SoQtComponent.h \
	$(top_builddir)/src/Inventor/Qt/SoQtCursors.h \
	$(top_srcdir)/src/Inventor/Qt/SoQtGLWidget.h \
	$(top_srcdir)/src/Inventor/Qt/SoQtLightSliderSet.h \
	$(top_srcdir)/src/Inventor/Qt/SoQtMaterialSliderSet.h \
	$(top_builddir)/src/Inventor/Qt/SoQtRenderArea.h \
	$(top_srcdir)/src/Inventor/Qt/SoQtSliderSet.h \
	$(top_srcdir)/src/Inventor/Qt/SoQtSliderSetBase.h \
	$(top_srcdir)/src/Inventor/Qt/SoQtTransformSliderSet.h

############################################################################

SoQtBasic.h: $(top_srcdir)/src/Inventor/Qt/common/SoGuiBasic.h.in
	@( cd $(top_builddir); $(MAKE) src/Inventor/Qt/SoQtBasic.h )

SoAny.h: $(top_srcdir)/src/Inventor/Qt/common/SoAny.h.in
	@( cd $(top_builddir); $(MAKE) src/Inventor/Qt/SoAny.h )

SoAny.cpp: $(top_srcdir)/src/Inventor/Qt/common/SoAny.cpp.in
	@( cd $(top_builddir); $(MAKE) src/Inventor/Qt/SoAny.cpp )

SoQtCursors.h: $(top_srcdir)/src/Inventor/Qt/common/SoGuiCursors.h.in
	@( cd $(top_builddir); $(MAKE) src/Inventor/Qt/SoQtCursors.h )

SoQtCursors.cpp: $(top_srcdir)/src/Inventor/Qt/common/SoGuiCursors.cpp.in
	@( cd $(top_builddir); $(MAKE) src/Inventor/Qt/SoQtCursors.cpp )

SoQtObject.h: $(top_srcdir)/src/Inventor/Qt/common/SoGuiObject.h.in
	@( cd $(top_builddir); $(MAKE) src/Inventor/Qt/SoQtObject.h )

SoQtObject.cpp: $(top_srcdir)/src/Inventor/Qt/common/SoGuiObject.cpp.in
	@( cd $(top_builddir); $(MAKE) src/Inventor/Qt/SoQtObject.cpp )

SoQtRenderArea.h: $(top_srcdir)/src/Inventor/Qt/common/SoGuiRenderArea.h.in
	@( cd $(top_builddir); $(MAKE) src/Inventor/Qt/SoQtRenderArea.h )

SoQtRenderArea.cpp: $(top_srcdir)/src/Inventor/Qt/common/SoGuiRenderArea.cpp.in
	@( cd $(top_builddir); $(MAKE) src/Inventor/Qt/SoQtRenderArea.cpp )

############################################################################

moc_SoQt.cpp: $(top_srcdir)/src/Inventor/Qt/SoQt.h
	@( cd $(top_builddir); $(MAKE) src/Inventor/Qt/moc_SoQt.cpp )

moc_SoQtObject.cpp: $(top_builddir)/src/Inventor/Qt/SoQtObject.h
	@( cd $(top_builddir); $(MAKE) src/Inventor/Qt/moc_SoQtObject.cpp )

moc_SoQtComponent.cpp: $(top_srcdir)/src/Inventor/Qt/SoQtComponent.h
	@( cd $(top_builddir); $(MAKE) src/Inventor/Qt/moc_SoQtComponent.cpp )

moc_SoQtGLWidget.cpp: $(top_srcdir)/src/Inventor/Qt/SoQtGLWidget.h
	@( cd $(top_builddir); $(MAKE) src/Inventor/Qt/moc_SoQtGLWidget.cpp )

moc_SoQtLightSliderSet.cpp: $(top_srcdir)/src/Inventor/Qt/SoQtLightSliderSet.h
	@( cd $(top_builddir); \
	   $(MAKE) src/Inventor/Qt/moc_SoQtLightSliderSet.cpp )

moc_SoQtMaterialSliderSet.cpp: \
  $(top_srcdir)/src/Inventor/Qt/SoQtMaterialSliderSet.h
	@( cd $(top_builddir); \
	   $(MAKE) src/Inventor/Qt/moc_SoQtMaterialSliderSet.cpp )

moc_SoQtRenderArea.cpp: $(top_builddir)/src/Inventor/Qt/SoQtRenderArea.h
	@( cd $(top_builddir); $(MAKE) src/Inventor/Qt/moc_SoQtRenderArea.cpp )

moc_SoQtSliderSet.cpp: $(top_srcdir)/src/Inventor/Qt/SoQtSliderSet.h
	@( cd $(top_builddir); $(MAKE) src/Inventor/Qt/moc_SoQtSliderSet.cpp )

moc_SoQtSliderSetBase.cpp: $(top_srcdir)/src/Inventor/Qt/SoQtSliderSetBase.h
	@( cd $(top_builddir); \
	   $(MAKE) src/Inventor/Qt/moc_SoQtSliderSetBase.cpp )

moc_SoQtTransformSliderSet.cpp: \
  $(top_srcdir)/src/Inventor/Qt/SoQtTransformSliderSet.h
	@( cd $(top_builddir); \
	   $(MAKE) src/Inventor/Qt/moc_SoQtTransformSliderSet.cpp )

# **************************************************************************

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

# **************************************************************************

install-exec-local: soqt@SOQT_MAJOR_VERSION@@SUFFIX@.lib
	@basename="soqt@SOQT_MAJOR_VERSION@@SUFFIX@"; \
	for ext in dll pdb; do \
	  file="$$basename.$$ext"; \
	  if test -f "$$file"; then \
	    $(mkinstalldirs) "$(DESTDIR)$(bindir)"; \
	    echo " $(INSTALL_PROGRAM)" "$$file" "$(DESTDIR)$(bindir)/$$file"; \
	    $(INSTALL_PROGRAM) "$$file" "$(DESTDIR)$(bindir)/$$file"; \
	  fi \
	done;

install-data-local: soqt@SOQT_MAJOR_VERSION@@SUFFIX@.lib
	@basename="soqt@SOQT_MAJOR_VERSION@@SUFFIX@"; \
	for ext in lib; do \
	  file="$$basename.$$ext"; \
	  if test -f "$$file"; then \
	    $(mkinstalldirs) "$(DESTDIR)$(libdir)"; \
	    echo " $(INSTALL_DATA)" "$$file" "$(DESTDIR)$(libdir)/$$file"; \
	    $(INSTALL_DATA) "$$file" "$(DESTDIR)$(libdir)/$$file"; \
	  fi \
	done

uninstall-local:
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
	    rmdir "$$dir"; \
	  fi \
	done;

# EOF **********************************************************************
