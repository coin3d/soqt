############################################################################

SUBDIRS = devices viewers widgets

############################################################################

INCLUDES = -I$(top_builddir)/src -I$(top_srcdir)/src

lib_LTLIBRARIES = libSoQt.la

BUILT_SOURCES = \
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

############################################################################

libSoQt_la_SOURCES = \
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
	SoQtTransformSliderSet.h \
	$(BUILT_SOURCES)

libSoQt_la_LIBADD = \
	devices/libSoQtDevices.la \
	viewers/libSoQtViewers.la \
	widgets/libSoQtWidgets.la

libSoQt_la_LDFLAGS = \
        -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)

libSoQtincdir = $(includedir)/Inventor/Qt

libSoQtinc_HEADERS = \
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

############################################################################

#### Additional "native" Make rules #########################################


## Rule for linking up a .DLL on MSWindows with MSVC++.
##
## Short explanation of what the shell-code does: tests if the C
## compiler is our MSVC++ wrapper script, and if so: properly link the
## DLL. If not, just make an empty soqt{version}.dll file so the
## install-exec-hook knows when to _not_ install the .dll.

soqt@SOQT_MAJOR_VERSION@.dll: $(libSoQt_la_OBJECTS) $(libSoQt_la_DEPENDENCIES)
	@rm -f soqt@SOQT_MAJOR_VERSION@.dll && \
	if @BUILD_WITH_MSVC@; then \
	  echo "Linking DLL..."; \
	  $(CC) @DLLFLAGS@ /out:soqt@SOQT_MAJOR_VERSION@.dll $(LDFLAGS) \
	        `echo $(libSoQt_la_OBJECTS) | sed 's%\.lo%.obj%g'` \
	        $(libSoQt_la_LIBADD) $(LIBS); \
	else \
	  touch soqt@SOQT_MAJOR_VERSION@.dll; \
	fi

## This hook will be run at the end of a ``make install''.
##
## The single action taken is to install the soqt.dll and soqt.lib
## files (if they have been built properly).

install-exec-hook: soqt@SOQT_MAJOR_VERSION@.dll
	@if test -s soqt@SOQT_MAJOR_VERSION@.dll; then \
	  echo "Installing soqt@SOQT_MAJOR_VERSION@.dll"; \
	  for e in dll lib pdb; do \
	    file="soqt@SOQT_MAJOR_VERSION@.$$e"; \
	    if test -s "$$file"; then \
	      $(INSTALL_DATA) $$file $(DESTDIR)$(libdir)/$$file; \
	    fi; \
	  done \
	fi

uninstall: uninstall-am
	@for e in dll lib pdb; do \
	  file="$(DESTDIR)$(libdir)/coin@SOQT_MAJOR_VERSION@.$$e"; \
	  if test -f "$$file"; then \
	    echo rm -f "$$file"; \
	    rm -f "$$file"; \
	  fi \
	done

