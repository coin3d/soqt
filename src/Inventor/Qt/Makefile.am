############################################################################

SUBDIRS = devices viewers widgets

############################################################################

INCLUDES = -I$(top_builddir)/src -I$(top_srcdir)/src

lib_LTLIBRARIES = libSoQt.la

BUILT_SOURCES = \
	SoQtBasic.h \
	SoQtRenderArea.cpp \
	SoQtRenderArea.h \
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
	SoQtTypedObject.cpp \
	SoQtTypedObject.h \
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
	$(top_srcdir)/src/Inventor/Qt/SoQtTypedObject.h \
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

SoQtBasic.h: $(top_srcdir)/src/Inventor/Qt/common/SoGuiBasic.h.in
	@( cd $(top_builddir); $(MAKE) src/Inventor/Qt/SoQtBasic.h )

SoQtRenderArea.h: $(top_srcdir)/src/Inventor/Qt/common/SoGuiRenderArea.h.in
	@( cd $(top_builddir); $(MAKE) src/Inventor/Qt/SoQtRenderArea.h )

SoQtRenderArea.cpp: $(top_srcdir)/src/Inventor/Qt/common/SoGuiRenderArea.cpp.in
	@( cd $(top_builddir); $(MAKE) src/Inventor/Qt/SoQtRenderArea.cpp )

############################################################################

moc_SoQt.cpp: $(top_srcdir)/src/Inventor/Qt/SoQt.h
	@( cd $(top_builddir); $(MAKE) src/Inventor/Qt/moc_SoQt.cpp )

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
