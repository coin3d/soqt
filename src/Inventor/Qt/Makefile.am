############################################################################

SUBDIRS = devices viewers widgets

############################################################################

INCLUDES = -I$(top_builddir)/src -I$(top_srcdir)/src

lib_LTLIBRARIES = libSoQt.la

BUILT_SOURCES = \
	moc_SoQt.cpp \
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
	SoQtCursors.cpp \
	SoQtCursors.h \
	SoQtGLWidget.cpp \
	SoQtGLWidget.h \
	SoQtLightSliderSet.cpp \
	SoQtLightSliderSet.h \
	SoQtMaterialSliderSet.cpp \
	SoQtMaterialSliderSet.h \
	$(top_builddir)/src/Inventor/Qt/SoQtRenderArea.cpp \
	$(top_builddir)/src/Inventor/Qt/SoQtRenderArea.h \
	SoQtRenderAreaExtra.cpp \
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
        -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) \
        -release $(LT_RELEASE)

libSoQtincdir = $(includedir)/Inventor/Qt

libSoQtinc_HEADERS = \
	$(top_srcdir)/src/Inventor/Qt/SoQt.h \
	$(top_srcdir)/src/Inventor/Qt/SoQtComponent.h \
	$(top_srcdir)/src/Inventor/Qt/SoQtCursors.h \
	$(top_srcdir)/src/Inventor/Qt/SoQtGLWidget.h \
	$(top_srcdir)/src/Inventor/Qt/SoQtLightSliderSet.h \
	$(top_srcdir)/src/Inventor/Qt/SoQtMaterialSliderSet.h \
	$(top_builddir)/src/Inventor/Qt/SoQtRenderArea.h \
	$(top_srcdir)/src/Inventor/Qt/SoQtSliderSet.h \
	$(top_srcdir)/src/Inventor/Qt/SoQtSliderSetBase.h \
	$(top_srcdir)/src/Inventor/Qt/SoQtTransformSliderSet.h

############################################################################

SoQtRenderArea.h: $(top_srcdir)/src/Inventor/Qt/common/SoAnyRenderArea.h.in
	@( cd $(top_builddir); $(MAKE) src/Inventor/Qt/SoQtRenderArea.h )

SoQtRenderArea.cpp: $(top_srcdir)/src/Inventor/Qt/common/SoAnyRenderArea.cpp.in
	@( cd $(top_builddir); $(MAKE) src/Inventor/Qt/SoQtRenderArea.cpp )

############################################################################

moc_SoQt.cpp: $(top_srcdir)/src/Inventor/Qt/SoQt.h
	$(MOC) -o moc_SoQt.cpp $(top_srcdir)/src/Inventor/Qt/SoQt.h

moc_SoQtComponent.cpp: $(top_srcdir)/src/Inventor/Qt/SoQtComponent.h
	$(MOC) -o moc_SoQtComponent.cpp $(top_srcdir)/src/Inventor/Qt/SoQtComponent.h

moc_SoQtGLWidget.cpp: $(top_srcdir)/src/Inventor/Qt/SoQtGLWidget.h
	$(MOC) -o moc_SoQtGLWidget.cpp $(top_srcdir)/src/Inventor/Qt/SoQtGLWidget.h

moc_SoQtLightSliderSet.cpp: $(top_srcdir)/src/Inventor/Qt/SoQtLightSliderSet.h
	$(MOC) -o moc_SoQtLightSliderSet.cpp $(top_srcdir)/src/Inventor/Qt/SoQtLightSliderSet.h

moc_SoQtMaterialSliderSet.cpp: $(top_srcdir)/src/Inventor/Qt/SoQtMaterialSliderSet.h
	$(MOC) -o moc_SoQtMaterialSliderSet.cpp $(top_srcdir)/src/Inventor/Qt/SoQtMaterialSliderSet.h

moc_SoQtRenderArea.cpp: $(top_builddir)/src/Inventor/Qt/SoQtRenderArea.h
	$(MOC) -o moc_SoQtRenderArea.cpp $(top_builddir)/src/Inventor/Qt/SoQtRenderArea.h

moc_SoQtSliderSet.cpp: $(top_srcdir)/src/Inventor/Qt/SoQtSliderSet.h
	$(MOC) -o moc_SoQtSliderSet.cpp $(top_srcdir)/src/Inventor/Qt/SoQtSliderSet.h

moc_SoQtSliderSetBase.cpp: $(top_srcdir)/src/Inventor/Qt/SoQtSliderSetBase.h
	$(MOC) -o moc_SoQtSliderSetBase.cpp $(top_srcdir)/src/Inventor/Qt/SoQtSliderSetBase.h

moc_SoQtTransformSliderSet.cpp: $(top_srcdir)/src/Inventor/Qt/SoQtTransformSliderSet.h
	$(MOC) -o moc_SoQtTransformSliderSet.cpp $(top_srcdir)/src/Inventor/Qt/SoQtTransformSliderSet.h

############################################################################
## FIXME: this is a temporary workaround for a bug in Automake. The
## bug is fixed in the latest Automake CVS, but not in any "official"
## release (?). Last checked with Automake 1.4a. 19990912 mortene.

install-libSoQtincHEADERS: $(libSoQtinc_HEADERS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(libSoQtincdir)
	@list='$(libSoQtinc_HEADERS)'; for p in $$list; do \
	  if test -f "$$p"; then d= ; else d="$(srcdir)/"; fi; \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " $(INSTALL_DATA) $$d$$p $(DESTDIR)$(libSoQtincdir)/$$f"; \
	  $(INSTALL_DATA) $$d$$p $(DESTDIR)$(libSoQtincdir)/$$f; \
	done

uninstall-libSoQtincHEADERS:
	@$(NORMAL_UNINSTALL)
	@list='$(libSoQtinc_HEADERS)'; for p in $$list; do \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " rm -f $(DESTDIR)$(libSoQtincdir)/$$f"; \
	  rm -f $(DESTDIR)$(libSoQtincdir)/$$f; \
	done

############################################################################
