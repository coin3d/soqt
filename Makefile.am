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
	soqtdefs.h \
	src/Inventor/Qt/SoQtBasic.h \
	src/Inventor/Qt/SoQtRenderArea.h \
	src/Inventor/Qt/SoQtRenderArea.cpp \
	src/Inventor/Qt/viewers/SoQtViewer.h \
	src/Inventor/Qt/viewers/SoQtViewer.cpp \
	src/Inventor/Qt/viewers/SoAnyFullViewer.h \
	src/Inventor/Qt/viewers/SoAnyFullViewer.cpp \
	src/Inventor/Qt/viewers/SoAnyExaminerViewer.h \
	src/Inventor/Qt/viewers/SoAnyExaminerViewer.cpp \
	src/Inventor/Qt/viewers/SoAnyPlaneViewer.h \
	src/Inventor/Qt/viewers/SoAnyPlaneViewer.cpp \
	src/Inventor/Qt/widgets/SoAnyThumbWheel.h \
	src/Inventor/Qt/widgets/SoAnyThumbWheel.cpp \
	src/Inventor/Qt/widgets/SoAnyPopupMenu.h \
	src/Inventor/Qt/widgets/SoAnyPopupMenu.cpp \
	src/Inventor/Qt/moc_SoQt.cpp \
	src/Inventor/Qt/moc_SoQtComponent.cpp \
	src/Inventor/Qt/moc_SoQtGLWidget.cpp \
	src/Inventor/Qt/moc_SoQtLightSliderSet.cpp \
	src/Inventor/Qt/moc_SoQtMaterialSliderSet.cpp \
	src/Inventor/Qt/moc_SoQtRenderArea.cpp \
	src/Inventor/Qt/moc_SoQtSliderSet.cpp \
	src/Inventor/Qt/moc_SoQtSliderSetBase.cpp \
	src/Inventor/Qt/moc_SoQtTransformSliderSet.cpp \
	src/Inventor/Qt/devices/moc_SoQtDevice.cpp \
	src/Inventor/Qt/devices/moc_SoQtInputFocus.cpp \
	src/Inventor/Qt/devices/moc_SoQtKeyboard.cpp \
	src/Inventor/Qt/devices/moc_SoQtMouse.cpp \
	src/Inventor/Qt/devices/moc_SoQtSpaceball.cpp \
	src/Inventor/Qt/devices/moc_SoQtLinuxJoystick.cpp \
	src/Inventor/Qt/viewers/moc_SoQtViewer.cpp \
	src/Inventor/Qt/viewers/moc_SoQtFullViewer.cpp \
	src/Inventor/Qt/viewers/moc_SoQtExaminerViewer.cpp \
	src/Inventor/Qt/viewers/moc_SoQtPlaneViewer.cpp \
	src/Inventor/Qt/viewers/moc_SoQtConstrainedViewer.cpp \
	src/Inventor/Qt/viewers/moc_SoQtWalkViewer.cpp \
	src/Inventor/Qt/viewers/moc_SoQtFlyViewer.cpp \
	src/Inventor/Qt/widgets/moc_SoQtPopupMenu.cpp \
	src/Inventor/Qt/widgets/moc_SoQtGLArea.cpp \
	src/Inventor/Qt/widgets/moc_SoQtThumbWheel.cpp

# This is necessary to set up a hook somewhere in the generated Makefile
# so the sources are actually built.
noinst_DATA = $(BUILT_SOURCES)

soqt-config: soqt-config.in

EXTRA_DIST = conf-macros/soqt.m4 conf-macros/modifierlist.m4

m4datadir = $(datadir)/aclocal
m4data_DATA = conf-macros/soqt.m4 conf-macros/modifierlist.m4

############################################################################

# Target which is present to make it simple to only generate the
# sourcefiles from the common sources.
built-sources: $(BUILT_SOURCES)

soqtdefs.h: $(top_srcdir)/soqtdefs.h.in
	@CONFIG_HEADERS= CONFIG_FILES=$@:soqtdefs.h.in ./config.status

src/Inventor/Qt/SoQtBasic.h: \
  $(top_srcdir)/src/Inventor/Qt/common/SoGuiBasic.h.in
	@CONFIG_HEADERS=$@:SoQtBasic.h.in CONFIG_FILES=$(top_srcdir)/SoQtBasic.h.in:src/Inventor/Qt/common/SoGuiBasic.h.in ./config.status
	@echo "removing $(top_srcdir)/SoQtBasic.h.in (temporary file)"
	@rm $(top_srcdir)/SoQtBasic.h.in

src/Inventor/Qt/SoQtRenderArea.h: \
  $(top_srcdir)/src/Inventor/Qt/common/SoGuiRenderArea.h.in
	@CONFIG_HEADERS= \
	CONFIG_FILES=$@:src/Inventor/Qt/common/SoGuiRenderArea.h.in \
	./config.status

src/Inventor/Qt/SoQtRenderArea.cpp: \
  $(top_srcdir)/src/Inventor/Qt/common/SoGuiRenderArea.cpp.in
	@CONFIG_HEADERS= \
	CONFIG_FILES=$@:src/Inventor/Qt/common/SoGuiRenderArea.cpp.in \
	./config.status

src/Inventor/Qt/viewers/SoQtViewer.h: \
  $(top_srcdir)/src/Inventor/Qt/common/SoGuiViewer.h.in
	@CONFIG_HEADERS= \
	CONFIG_FILES=$@:src/Inventor/Qt/common/SoGuiViewer.h.in \
	$(top_builddir)/config.status

src/Inventor/Qt/viewers/SoQtViewer.cpp: \
  $(top_srcdir)/src/Inventor/Qt/common/SoGuiViewer.cpp.in
	@CONFIG_HEADERS= \
	CONFIG_FILES=$@:src/Inventor/Qt/common/SoGuiViewer.cpp.in \
	$(top_builddir)/config.status

src/Inventor/Qt/viewers/SoAnyFullViewer.h: \
  $(top_srcdir)/src/Inventor/Qt/common/SoAnyFullViewer.h.in
	@CONFIG_HEADERS= \
	CONFIG_FILES=$@:src/Inventor/Qt/common/SoAnyFullViewer.h.in \
	$(top_builddir)/config.status

src/Inventor/Qt/viewers/SoAnyFullViewer.cpp: \
  $(top_srcdir)/src/Inventor/Qt/common/SoAnyFullViewer.cpp.in
	@CONFIG_HEADERS= \
	CONFIG_FILES=$@:src/Inventor/Qt/common/SoAnyFullViewer.cpp.in \
	$(top_builddir)/config.status

src/Inventor/Qt/viewers/SoAnyExaminerViewer.h: \
  $(top_srcdir)/src/Inventor/Qt/common/SoAnyExaminerViewer.h.in
	@CONFIG_HEADERS= \
	CONFIG_FILES=$@:src/Inventor/Qt/common/SoAnyExaminerViewer.h.in \
	$(top_builddir)/config.status

src/Inventor/Qt/viewers/SoAnyExaminerViewer.cpp: \
  $(top_srcdir)/src/Inventor/Qt/common/SoAnyExaminerViewer.cpp.in
	@CONFIG_HEADERS= \
	CONFIG_FILES=$@:src/Inventor/Qt/common/SoAnyExaminerViewer.cpp.in \
	$(top_builddir)/config.status

src/Inventor/Qt/viewers/SoAnyPlaneViewer.h: \
  $(top_srcdir)/src/Inventor/Qt/common/SoAnyPlaneViewer.h.in
	@CONFIG_HEADERS= \
	CONFIG_FILES=$@:src/Inventor/Qt/common/SoAnyPlaneViewer.h.in \
	$(top_builddir)/config.status

src/Inventor/Qt/viewers/SoAnyPlaneViewer.cpp: \
  $(top_srcdir)/src/Inventor/Qt/common/SoAnyPlaneViewer.cpp.in
	@CONFIG_HEADERS= \
	CONFIG_FILES=$@:src/Inventor/Qt/common/SoAnyPlaneViewer.cpp.in \
	$(top_builddir)/config.status

src/Inventor/Qt/widgets/SoAnyThumbWheel.h: \
  $(top_srcdir)/src/Inventor/Qt/common/SoAnyThumbWheel.h.in
	@CONFIG_HEADERS= \
	CONFIG_FILES=$@:src/Inventor/Qt/common/SoAnyThumbWheel.h.in \
	$(top_builddir)/config.status

src/Inventor/Qt/widgets/SoAnyThumbWheel.cpp: \
  $(top_srcdir)/src/Inventor/Qt/common/SoAnyThumbWheel.cpp.in
	@CONFIG_HEADERS= \
	CONFIG_FILES=$@:src/Inventor/Qt/common/SoAnyThumbWheel.cpp.in \
	$(top_builddir)/config.status

src/Inventor/Qt/widgets/SoAnyPopupMenu.h: \
  $(top_srcdir)/src/Inventor/Qt/common/SoAnyPopupMenu.h.in
	@CONFIG_HEADERS= \
	CONFIG_FILES=$@:src/Inventor/Qt/common/SoAnyPopupMenu.h.in \
	$(top_builddir)/config.status

src/Inventor/Qt/widgets/SoAnyPopupMenu.cpp: \
  $(top_srcdir)/src/Inventor/Qt/common/SoAnyPopupMenu.cpp.in
	@CONFIG_HEADERS= \
	CONFIG_FILES=$@:src/Inventor/Qt/common/SoAnyPopupMenu.cpp.in \
	$(top_builddir)/config.status

############################################################################

src/Inventor/Qt/moc_SoQt.cpp: $(top_srcdir)/src/Inventor/Qt/SoQt.h
	$(MOC) -o $@ $(top_srcdir)/src/Inventor/Qt/SoQt.h

src/Inventor/Qt/moc_SoQtComponent.cpp: \
  $(top_srcdir)/src/Inventor/Qt/SoQtComponent.h
	$(MOC) -o $@ $(top_srcdir)/src/Inventor/Qt/SoQtComponent.h

src/Inventor/Qt/moc_SoQtGLWidget.cpp: \
  $(top_srcdir)/src/Inventor/Qt/SoQtGLWidget.h
	$(MOC) -o $@ $(top_srcdir)/src/Inventor/Qt/SoQtGLWidget.h

src/Inventor/Qt/moc_SoQtLightSliderSet.cpp: \
  $(top_srcdir)/src/Inventor/Qt/SoQtLightSliderSet.h
	$(MOC) -o $@ $(top_srcdir)/src/Inventor/Qt/SoQtLightSliderSet.h

src/Inventor/Qt/moc_SoQtMaterialSliderSet.cpp: \
  $(top_srcdir)/src/Inventor/Qt/SoQtMaterialSliderSet.h
	$(MOC) -o $@ $(top_srcdir)/src/Inventor/Qt/SoQtMaterialSliderSet.h

src/Inventor/Qt/moc_SoQtRenderArea.cpp: \
  $(top_builddir)/src/Inventor/Qt/SoQtRenderArea.h
	$(MOC) -o $@ $(top_builddir)/src/Inventor/Qt/SoQtRenderArea.h

src/Inventor/Qt/moc_SoQtSliderSet.cpp: \
  $(top_srcdir)/src/Inventor/Qt/SoQtSliderSet.h
	$(MOC) -o $@ $(top_srcdir)/src/Inventor/Qt/SoQtSliderSet.h

src/Inventor/Qt/moc_SoQtSliderSetBase.cpp: \
  $(top_srcdir)/src/Inventor/Qt/SoQtSliderSetBase.h
	$(MOC) -o $@ $(top_srcdir)/src/Inventor/Qt/SoQtSliderSetBase.h

src/Inventor/Qt/moc_SoQtTransformSliderSet.cpp: \
  $(top_srcdir)/src/Inventor/Qt/SoQtTransformSliderSet.h
	$(MOC) -o $@ $(top_srcdir)/src/Inventor/Qt/SoQtTransformSliderSet.h

src/Inventor/Qt/devices/moc_SoQtDevice.cpp: \
  $(top_srcdir)/src/Inventor/Qt/devices/SoQtDevice.h
	$(MOC) -o $@ $(top_srcdir)/src/Inventor/Qt/devices/SoQtDevice.h

src/Inventor/Qt/devices/moc_SoQtInputFocus.cpp: \
  $(top_srcdir)/src/Inventor/Qt/devices/SoQtInputFocus.h
	$(MOC) -o $@ $(top_srcdir)/src/Inventor/Qt/devices/SoQtInputFocus.h

src/Inventor/Qt/devices/moc_SoQtKeyboard.cpp: \
  $(top_srcdir)/src/Inventor/Qt/devices/SoQtKeyboard.h
	$(MOC) -o $@ $(top_srcdir)/src/Inventor/Qt/devices/SoQtKeyboard.h

src/Inventor/Qt/devices/moc_SoQtMouse.cpp: \
  $(top_srcdir)/src/Inventor/Qt/devices/SoQtMouse.h
	$(MOC) -o $@ $(top_srcdir)/src/Inventor/Qt/devices/SoQtMouse.h

src/Inventor/Qt/devices/moc_SoQtSpaceball.cpp: \
  $(top_srcdir)/src/Inventor/Qt/devices/SoQtSpaceball.h
	$(MOC) -o $@ $(top_srcdir)/src/Inventor/Qt/devices/SoQtSpaceball.h

src/Inventor/Qt/devices/moc_SoQtLinuxJoystick.cpp: \
  $(top_srcdir)/src/Inventor/Qt/devices/SoQtLinuxJoystick.h
	$(MOC) -o $@ $(top_srcdir)/src/Inventor/Qt/devices/SoQtLinuxJoystick.h

src/Inventor/Qt/viewers/moc_SoQtViewer.cpp: \
  $(top_builddir)/src/Inventor/Qt/viewers/SoQtViewer.h
	$(MOC) -o $@ $(top_builddir)/src/Inventor/Qt/viewers/SoQtViewer.h

src/Inventor/Qt/viewers/moc_SoQtFullViewer.cpp: \
  $(top_srcdir)/src/Inventor/Qt/viewers/SoQtFullViewer.h
	$(MOC) -o $@ $(top_srcdir)/src/Inventor/Qt/viewers/SoQtFullViewer.h

src/Inventor/Qt/viewers/moc_SoQtExaminerViewer.cpp: \
  $(top_srcdir)/src/Inventor/Qt/viewers/SoQtExaminerViewer.h
	$(MOC) -o $@ $(top_srcdir)/src/Inventor/Qt/viewers/SoQtExaminerViewer.h

src/Inventor/Qt/viewers/moc_SoQtPlaneViewer.cpp: \
  $(top_srcdir)/src/Inventor/Qt/viewers/SoQtPlaneViewer.h
	$(MOC) -o $@ $(top_srcdir)/src/Inventor/Qt/viewers/SoQtPlaneViewer.h

src/Inventor/Qt/viewers/moc_SoQtConstrainedViewer.cpp: \
  $(top_srcdir)/src/Inventor/Qt/viewers/SoQtConstrainedViewer.h
	$(MOC) -o $@ $(top_srcdir)/src/Inventor/Qt/viewers/SoQtConstrainedViewer.h

src/Inventor/Qt/viewers/moc_SoQtWalkViewer.cpp: \
  $(top_srcdir)/src/Inventor/Qt/viewers/SoQtWalkViewer.h
	$(MOC) -o $@ $(top_srcdir)/src/Inventor/Qt/viewers/SoQtWalkViewer.h

src/Inventor/Qt/viewers/moc_SoQtFlyViewer.cpp: \
  $(top_srcdir)/src/Inventor/Qt/viewers/SoQtFlyViewer.h
	$(MOC) -o $@ $(top_srcdir)/src/Inventor/Qt/viewers/SoQtFlyViewer.h

src/Inventor/Qt/widgets/moc_SoQtThumbWheel.cpp: \
  $(top_srcdir)/src/Inventor/Qt/widgets/SoQtThumbWheel.h
	$(MOC) -o $@ $(top_srcdir)/src/Inventor/Qt/widgets/SoQtThumbWheel.h

src/Inventor/Qt/widgets/moc_SoQtGLArea.cpp: \
  $(top_srcdir)/src/Inventor/Qt/widgets/SoQtGLArea.h
	$(MOC) -o $@ $(top_srcdir)/src/Inventor/Qt/widgets/SoQtGLArea.h

src/Inventor/Qt/widgets/moc_SoQtPopupMenu.cpp: \
  $(top_srcdir)/src/Inventor/Qt/widgets/SoQtPopupMenu.h
	$(MOC) -o $@ $(top_srcdir)/src/Inventor/Qt/widgets/SoQtPopupMenu.h

############################################################################
