############################################################################
## Process this file with automake to generate Makefile.in.

ACLOCAL_AMFLAGS = -I cfg/m4

SUFFIXES = .cpp .h .m4 .in .o .lo .Plo .TPlo

############################################################################

SUBDIRS = . src/Inventor/Qt

SoQtBuiltSources = \
	soqt-config \
	soqtdefs.h \
	src/Inventor/Qt/SoQtBasic.h \
	src/Inventor/Qt/SoQtCursors.h \
	src/Inventor/Qt/SoQtCursors.cpp \
	src/Inventor/Qt/SoQtObject.h \
	src/Inventor/Qt/SoQtObject.cpp \
	src/Inventor/Qt/SoQtRenderArea.h \
	src/Inventor/Qt/SoQtRenderArea.cpp \
	src/Inventor/Qt/devices/spwinput.h \
	src/Inventor/Qt/devices/spwinput_x11.cpp \
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
	src/Inventor/Qt/widgets/SoAnyPopupMenu.cpp

SoQtMocSources = \
	src/Inventor/Qt/moc_SoQt.cpp \
	src/Inventor/Qt/moc_SoQtObject.cpp \
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

BUILT_SOURCES = \
	$(SoQtBuiltSources) \
	$(SoQtMocSources)

bin_SCRIPTS = soqt-config

soqt-config: soqt-config.in

EXTRA_DIST = cfg/m4/soqt.m4

m4datadir = $(datadir)/aclocal
m4data_DATA = cfg/m4/soqt.m4

# This is necessary to set up a hook somewhere in the generated Makefile
# so the sources are actually built.

Makefile: $(SoQtBuiltSources)

############################################################################

# Target which is present to make it simple to only generate all the source
# files from the common sources.

built-sources: $(BUILT_SOURCES)

soqtdefs.h: $(srcdir)/soqtdefs.h.in
	@./config.status --file=soqtdefs.h

src/Inventor/Qt/SoQtBasic.h: $(srcdir)/src/Inventor/Qt/common/SoGuiBasic.h.in
	@./config.status \
	  --file=-:$(srcdir)/src/Inventor/Qt/common/SoGuiBasic.h.in | \
	  ./config.status --header=$@:-

src/Inventor/Qt/SoQtObject.h: \
  $(srcdir)/src/Inventor/Qt/common/SoGuiObject.h.in
	@./config.status --file=$@:src/Inventor/Qt/common/SoGuiObject.h.in

src/Inventor/Qt/SoQtObject.cpp: \
  $(srcdir)/src/Inventor/Qt/common/SoGuiObject.cpp.in
	@./config.status --file=$@:src/Inventor/Qt/common/SoGuiObject.cpp.in

src/Inventor/Qt/SoQtCursors.h: \
  $(srcdir)/src/Inventor/Qt/common/SoGuiCursors.h.in
	@./config.status --file=$@:src/Inventor/Qt/common/SoGuiCursors.h.in

src/Inventor/Qt/SoQtCursors.cpp: \
  $(srcdir)/src/Inventor/Qt/common/SoGuiCursors.cpp.in
	@./config.status --file=$@:src/Inventor/Qt/common/SoGuiCursors.cpp.in

src/Inventor/Qt/SoQtRenderArea.h: \
  $(srcdir)/src/Inventor/Qt/common/SoGuiRenderArea.h.in
	@./config.status --file=$@:src/Inventor/Qt/common/SoGuiRenderArea.h.in

src/Inventor/Qt/SoQtRenderArea.cpp: \
  $(srcdir)/src/Inventor/Qt/common/SoGuiRenderArea.cpp.in
	@./config.status --file=$@:src/Inventor/Qt/common/SoGuiRenderArea.cpp.in

src/Inventor/Qt/viewers/SoQtViewer.h: \
  $(srcdir)/src/Inventor/Qt/common/SoGuiViewer.h.in
	@./config.status --file=$@:src/Inventor/Qt/common/SoGuiViewer.h.in

src/Inventor/Qt/viewers/SoQtViewer.cpp: \
  $(srcdir)/src/Inventor/Qt/common/SoGuiViewer.cpp.in
	@./config.status --file=$@:src/Inventor/Qt/common/SoGuiViewer.cpp.in

src/Inventor/Qt/viewers/SoAnyFullViewer.h: \
  $(srcdir)/src/Inventor/Qt/common/SoAnyFullViewer.h.in
	@./config.status --file=$@:src/Inventor/Qt/common/SoAnyFullViewer.h.in

src/Inventor/Qt/viewers/SoAnyFullViewer.cpp: \
  $(srcdir)/src/Inventor/Qt/common/SoAnyFullViewer.cpp.in
	@./config.status --file=$@:src/Inventor/Qt/common/SoAnyFullViewer.cpp.in

src/Inventor/Qt/viewers/SoAnyExaminerViewer.h: \
  $(srcdir)/src/Inventor/Qt/common/SoAnyExaminerViewer.h.in
	@./config.status \
	  --file=$@:src/Inventor/Qt/common/SoAnyExaminerViewer.h.in

src/Inventor/Qt/viewers/SoAnyExaminerViewer.cpp: \
  $(srcdir)/src/Inventor/Qt/common/SoAnyExaminerViewer.cpp.in
	@./config.status \
	  --file=$@:src/Inventor/Qt/common/SoAnyExaminerViewer.cpp.in

src/Inventor/Qt/viewers/SoAnyPlaneViewer.h: \
  $(srcdir)/src/Inventor/Qt/common/SoAnyPlaneViewer.h.in
	@./config.status \
	  --file=$@:src/Inventor/Qt/common/SoAnyPlaneViewer.h.in

src/Inventor/Qt/viewers/SoAnyPlaneViewer.cpp: \
  $(srcdir)/src/Inventor/Qt/common/SoAnyPlaneViewer.cpp.in
	@./config.status \
	  --file=$@:src/Inventor/Qt/common/SoAnyPlaneViewer.cpp.in

src/Inventor/Qt/widgets/SoAnyThumbWheel.h: \
  $(srcdir)/src/Inventor/Qt/common/SoAnyThumbWheel.h.in
	@./config.status --file=$@:src/Inventor/Qt/common/SoAnyThumbWheel.h.in

src/Inventor/Qt/widgets/SoAnyThumbWheel.cpp: \
  $(srcdir)/src/Inventor/Qt/common/SoAnyThumbWheel.cpp.in
	@./config.status --file=$@:src/Inventor/Qt/common/SoAnyThumbWheel.cpp.in

src/Inventor/Qt/widgets/SoAnyPopupMenu.h: \
  $(srcdir)/src/Inventor/Qt/common/SoAnyPopupMenu.h.in
	@./config.status --file=$@:src/Inventor/Qt/common/SoAnyPopupMenu.h.in

src/Inventor/Qt/widgets/SoAnyPopupMenu.cpp: \
  $(srcdir)/src/Inventor/Qt/common/SoAnyPopupMenu.cpp.in
	@./config.status --file=$@:src/Inventor/Qt/common/SoAnyPopupMenu.cpp.in

src/Inventor/Qt/devices/spwinput.h: \
  $(srcdir)/src/Inventor/Qt/common/spwinput.h.in
	@./config.status --file=$@:src/Inventor/Qt/common/spwinput.h.in

src/Inventor/Qt/devices/spwinput_x11.cpp: \
  $(srcdir)/src/Inventor/Qt/common/spwinput_x11.cpp.in
	@./config.status --file=$@:src/Inventor/Qt/common/spwinput_x11.cpp.in

############################################################################
## auto-generated Qt moc files.

src/Inventor/Qt/moc_SoQt.cpp: $(srcdir)/src/Inventor/Qt/SoQt.h
	$(MOC) -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/SoQt.h`

src/Inventor/Qt/moc_SoQtObject.cpp: $(top_builddir)/src/Inventor/Qt/SoQtObject.h
	$(MOC) -o $@ $(top_builddir)/src/Inventor/Qt/SoQtObject.h

src/Inventor/Qt/moc_SoQtComponent.cpp: $(srcdir)/src/Inventor/Qt/SoQtComponent.h
	$(MOC) -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/SoQtComponent.h`

src/Inventor/Qt/moc_SoQtGLWidget.cpp: \
  $(srcdir)/src/Inventor/Qt/SoQtGLWidget.h
	$(MOC) -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/SoQtGLWidget.h`

src/Inventor/Qt/moc_SoQtLightSliderSet.cpp: \
  $(srcdir)/src/Inventor/Qt/SoQtLightSliderSet.h
	$(MOC) -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/SoQtLightSliderSet.h`

src/Inventor/Qt/moc_SoQtMaterialSliderSet.cpp: \
  $(srcdir)/src/Inventor/Qt/SoQtMaterialSliderSet.h
	$(MOC) -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/SoQtMaterialSliderSet.h`

src/Inventor/Qt/moc_SoQtRenderArea.cpp: \
  $(top_builddir)/src/Inventor/Qt/SoQtRenderArea.h
	$(MOC) -o $@ $(top_builddir)/src/Inventor/Qt/SoQtRenderArea.h

src/Inventor/Qt/moc_SoQtSliderSet.cpp: \
  $(srcdir)/src/Inventor/Qt/SoQtSliderSet.h
	$(MOC) -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/SoQtSliderSet.h`

src/Inventor/Qt/moc_SoQtSliderSetBase.cpp: \
  $(srcdir)/src/Inventor/Qt/SoQtSliderSetBase.h
	$(MOC) -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/SoQtSliderSetBase.h`

src/Inventor/Qt/moc_SoQtTransformSliderSet.cpp: \
  $(srcdir)/src/Inventor/Qt/SoQtTransformSliderSet.h
	$(MOC) -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/SoQtTransformSliderSet.h`

src/Inventor/Qt/devices/moc_SoQtDevice.cpp: \
  $(srcdir)/src/Inventor/Qt/devices/SoQtDevice.h
	$(MOC) -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/devices/SoQtDevice.h`

src/Inventor/Qt/devices/moc_SoQtInputFocus.cpp: \
  $(srcdir)/src/Inventor/Qt/devices/SoQtInputFocus.h
	$(MOC) -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/devices/SoQtInputFocus.h`

src/Inventor/Qt/devices/moc_SoQtKeyboard.cpp: \
  $(srcdir)/src/Inventor/Qt/devices/SoQtKeyboard.h
	$(MOC) -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/devices/SoQtKeyboard.h`

src/Inventor/Qt/devices/moc_SoQtMouse.cpp: \
  $(srcdir)/src/Inventor/Qt/devices/SoQtMouse.h
	$(MOC) -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/devices/SoQtMouse.h`

src/Inventor/Qt/devices/moc_SoQtSpaceball.cpp: \
  $(srcdir)/src/Inventor/Qt/devices/SoQtSpaceball.h
	$(MOC) -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/devices/SoQtSpaceball.h`

src/Inventor/Qt/devices/moc_SoQtLinuxJoystick.cpp: \
  $(srcdir)/src/Inventor/Qt/devices/SoQtLinuxJoystick.h
	$(MOC) -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/devices/SoQtLinuxJoystick.h`

src/Inventor/Qt/viewers/moc_SoQtViewer.cpp: \
  $(top_builddir)/src/Inventor/Qt/viewers/SoQtViewer.h
	$(MOC) -o $@ $(top_builddir)/src/Inventor/Qt/viewers/SoQtViewer.h

src/Inventor/Qt/viewers/moc_SoQtFullViewer.cpp: \
  $(srcdir)/src/Inventor/Qt/viewers/SoQtFullViewer.h
	$(MOC) -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/viewers/SoQtFullViewer.h`

src/Inventor/Qt/viewers/moc_SoQtExaminerViewer.cpp: \
  $(srcdir)/src/Inventor/Qt/viewers/SoQtExaminerViewer.h
	$(MOC) -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/viewers/SoQtExaminerViewer.h`

src/Inventor/Qt/viewers/moc_SoQtPlaneViewer.cpp: \
  $(srcdir)/src/Inventor/Qt/viewers/SoQtPlaneViewer.h
	$(MOC) -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/viewers/SoQtPlaneViewer.h`

src/Inventor/Qt/viewers/moc_SoQtConstrainedViewer.cpp: \
  $(srcdir)/src/Inventor/Qt/viewers/SoQtConstrainedViewer.h
	$(MOC) -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/viewers/SoQtConstrainedViewer.h`

src/Inventor/Qt/viewers/moc_SoQtWalkViewer.cpp: \
  $(srcdir)/src/Inventor/Qt/viewers/SoQtWalkViewer.h
	$(MOC) -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/viewers/SoQtWalkViewer.h`

src/Inventor/Qt/viewers/moc_SoQtFlyViewer.cpp: \
  $(srcdir)/src/Inventor/Qt/viewers/SoQtFlyViewer.h
	$(MOC) -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/viewers/SoQtFlyViewer.h`

src/Inventor/Qt/widgets/moc_SoQtThumbWheel.cpp: \
  $(srcdir)/src/Inventor/Qt/widgets/SoQtThumbWheel.h
	$(MOC) -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/widgets/SoQtThumbWheel.h`

src/Inventor/Qt/widgets/moc_SoQtGLArea.cpp: \
  $(srcdir)/src/Inventor/Qt/widgets/SoQtGLArea.h
	$(MOC) -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/widgets/SoQtGLArea.h`

src/Inventor/Qt/widgets/moc_SoQtPopupMenu.cpp: \
  $(srcdir)/src/Inventor/Qt/widgets/SoQtPopupMenu.h
	$(MOC) -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/widgets/SoQtPopupMenu.h`

############################################################################

doxygen-docs:
	@( cd build; @sim_ac_doxygen_exe@ soqt.doxygen )

