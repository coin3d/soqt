############################################################################
## Process this file with automake to generate Makefile.in.

ACLOCAL_AMFLAGS = -I cfg/m4

SUFFIXES = .cpp .h .m4 .in .o .lo .Plo .TPlo

############################################################################

SUBDIRS = . src

So@Gui@BuiltSources = \
	src/so@gui@defs.h \
        src/Inventor/@Gui@/SoAny.h \
        src/Inventor/@Gui@/SoAny.cpp \
	src/Inventor/@Gui@/So@Gui@Basic.h \
	src/Inventor/@Gui@/So@Gui@Cursors.h \
	src/Inventor/@Gui@/So@Gui@Cursors.cpp \
	src/Inventor/@Gui@/So@Gui@Object.h \
	src/Inventor/@Gui@/So@Gui@Object.cpp \
	src/Inventor/@Gui@/So@Gui@RenderArea.h \
	src/Inventor/@Gui@/So@Gui@RenderArea.cpp \
	src/Inventor/@Gui@/common/gl.h \
	src/Inventor/@Gui@/devices/spwinput.h \
	src/Inventor/@Gui@/devices/spwinput_x11.cpp \
	src/Inventor/@Gui@/viewers/So@Gui@Viewer.h \
	src/Inventor/@Gui@/viewers/So@Gui@Viewer.cpp \
	src/Inventor/@Gui@/viewers/So@Gui@ConstrainedViewer.h \
	src/Inventor/@Gui@/viewers/So@Gui@ConstrainedViewer.cpp \
	src/Inventor/@Gui@/viewers/So@Gui@FlyViewer.h \
	src/Inventor/@Gui@/viewers/So@Gui@FlyViewer.cpp \
	src/Inventor/@Gui@/viewers/SoAnyFullViewer.h \
	src/Inventor/@Gui@/viewers/SoAnyFullViewer.cpp \
	src/Inventor/@Gui@/viewers/SoAnyExaminerViewer.h \
	src/Inventor/@Gui@/viewers/SoAnyExaminerViewer.cpp \
	src/Inventor/@Gui@/viewers/SoAnyPlaneViewer.h \
	src/Inventor/@Gui@/viewers/SoAnyPlaneViewer.cpp \
	src/Inventor/@Gui@/widgets/SoAnyThumbWheel.h \
	src/Inventor/@Gui@/widgets/SoAnyThumbWheel.cpp \
	src/Inventor/@Gui@/widgets/SoAnyPopupMenu.h \
	src/Inventor/@Gui@/widgets/SoAnyPopupMenu.cpp

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
	$(So@Gui@BuiltSources) \
	$(So@Gui@MocSources)

DISTCLEANFILES = \
	libtool \
	build/so@gui@.doxygen \
	so@gui@-*.cfg \
	so@gui@-config \
	$(BUILT_SOURCES)

bin_SCRIPTS = so@gui@-config

m4datadir = $(datadir)/aclocal
dist_m4data_DATA = cfg/m4/so@gui@.m4

cfgdatadir = $(datadir)/Coin/conf
cfgdata_DATA = so@gui@-@CONFIG@.cfg

# now generated in configure because of data/configure dependency
# so@gui@-@CONFIG@.cfg: Makefile config.status $(srcdir)/src/Inventor/@Gui@/common/sogui.cfg.in
#	@$(SHELL) config.status --file=$@:src/Inventor/@Gui@/common/sogui.cfg.in

so@gui@-config: Makefile config.status $(srcdir)/src/Inventor/@Gui@/common/sogui-config.in
	@$(SHELL) config.status --file=$@:src/Inventor/@Gui@/common/sogui-config.in

EXTRA_DIST = \
	LICENSE.LGPL \
	HACKING \
	README.DLL \
	README.IRIX \
	README.WIN32 \
	src/Inventor/@Gui@/common/sogui.cfg.in \
	src/Inventor/@Gui@/common/sogui-config.in \
	build/so@gui@.doxygen.in \
	build/so@gui@.spec.in \
	cfg/doxy4win.pl \
	cfg/m4/wrapmsvc.cpp \
	cfg/m4/wrapmsvc.exe \
	models/coin_soqt.iv \
	models/coin_soqt.wrl \
	src/Inventor/@Gui@/common/ChangeLog \
	src/Inventor/@Gui@/common/SoGuiBasic.h.in \
	src/Inventor/@Gui@/common/SoGuiCursors.h.in \
	src/Inventor/@Gui@/common/SoGuiCursors.cpp.in \
	src/Inventor/@Gui@/common/SoGuiObject.h.in \
	src/Inventor/@Gui@/common/SoGuiObject.cpp.in \
	src/Inventor/@Gui@/common/SoGuiRenderArea.h.in \
	src/Inventor/@Gui@/common/SoGuiRenderArea.cpp.in \
	src/Inventor/@Gui@/common/SoGuiViewer.h.in \
	src/Inventor/@Gui@/common/SoGuiViewer.cpp.in \
	src/Inventor/@Gui@/common/SoGuiConstrainedViewer.h.in \
	src/Inventor/@Gui@/common/SoGuiConstrainedViewer.cpp.in \
	src/Inventor/@Gui@/common/SoGuiFlyViewer.h.in \
	src/Inventor/@Gui@/common/SoGuiFlyViewer.cpp.in \
	src/Inventor/@Gui@/common/SoAny.h.in \
	src/Inventor/@Gui@/common/SoAny.cpp.in \
	src/Inventor/@Gui@/common/SoAnyPopupMenu.h.in \
	src/Inventor/@Gui@/common/SoAnyPopupMenu.cpp.in \
	src/Inventor/@Gui@/common/SoAnyThumbWheel.h.in \
	src/Inventor/@Gui@/common/SoAnyThumbWheel.cpp.in \
	src/Inventor/@Gui@/common/SoAnyFullViewer.h.in \
	src/Inventor/@Gui@/common/SoAnyFullViewer.cpp.in \
	src/Inventor/@Gui@/common/SoAnyExaminerViewer.h.in \
	src/Inventor/@Gui@/common/SoAnyExaminerViewer.cpp.in \
	src/Inventor/@Gui@/common/SoAnyPlaneViewer.h.in \
	src/Inventor/@Gui@/common/SoAnyPlaneViewer.cpp.in \
	src/Inventor/@Gui@/common/SoAnyConstrainedViewer.h.in \
	src/Inventor/@Gui@/common/SoAnyConstrainedViewer.cpp.in \
	src/Inventor/@Gui@/common/SoAnyWalkViewer.h.in \
	src/Inventor/@Gui@/common/SoAnyWalkViewer.cpp.in \
	src/Inventor/@Gui@/common/SoAnyFlyViewer.h.in \
	src/Inventor/@Gui@/common/SoAnyFlyViewer.cpp.in \
	src/Inventor/@Gui@/common/SoAnyMaterialList.h.in \
	src/Inventor/@Gui@/common/SoAnyMaterialList.cpp.in \
	src/Inventor/@Gui@/common/SoAnyMaterialListBuiltins.cpp.in \
	src/Inventor/@Gui@/common/gl.h.in \
	src/Inventor/@Gui@/common/soguidefs.h.in \
	src/Inventor/@Gui@/common/spwinput.h.in \
	src/Inventor/@Gui@/common/spwinput_x11.cpp.in \
	src/Inventor/@Gui@/common/pixmaps/help.xpm \
	src/Inventor/@Gui@/common/pixmaps/home.xpm \
	src/Inventor/@Gui@/common/pixmaps/ortho.xpm \
	src/Inventor/@Gui@/common/pixmaps/perspective.xpm \
	src/Inventor/@Gui@/common/pixmaps/pick.xpm \
	src/Inventor/@Gui@/common/pixmaps/seek.xpm \
	src/Inventor/@Gui@/common/pixmaps/set_home.xpm \
	src/Inventor/@Gui@/common/pixmaps/view.xpm \
	src/Inventor/@Gui@/common/pixmaps/view_all.xpm \
	src/Inventor/@Gui@/common/pixmaps/x.xpm \
	src/Inventor/@Gui@/common/pixmaps/y.xpm \
	src/Inventor/@Gui@/common/pixmaps/z.xpm \
	test-code/README \
	test-code/components/scrollview.cpp \
	test-code/components/tripleview.cpp

# This is necessary to set up a hook somewhere in the generated Makefile
# so the sources are actually built.

# this messes up "make distclean"
# Makefile: $(So@Gui@BuiltSources)

# Target which is present to make it simple to only generate all the source
# files from the common sources.

built-sources: $(BUILT_SOURCES)

# **************************************************************************

src/so@gui@defs.h: $(srcdir)/src/Inventor/@Gui@/common/soguidefs.h.in config.status
	@$(SHELL) config.status --file=$@:src/Inventor/@Gui@/common/soguidefs.h.in

src/Inventor/@Gui@/SoAny.h: \
  $(srcdir)/src/Inventor/@Gui@/common/SoAny.h.in config.status
	@$(SHELL) config.status --file=$@:src/Inventor/@Gui@/common/SoAny.h.in

src/Inventor/@Gui@/SoAny.cpp: \
  $(srcdir)/src/Inventor/@Gui@/common/SoAny.cpp.in config.status
	@$(SHELL) config.status --file=$@:src/Inventor/@Gui@/common/SoAny.cpp.in

src/Inventor/@Gui@/So@Gui@Basic.h: $(srcdir)/src/Inventor/@Gui@/common/SoGuiBasic.h.in config.status
	@$(SHELL) config.status --file=-:src/Inventor/@Gui@/common/SoGuiBasic.h.in | \
	  $(SHELL) config.status --header=$@:-

src/Inventor/@Gui@/So@Gui@Object.h: \
  $(srcdir)/src/Inventor/@Gui@/common/SoGuiObject.h.in config.status
	@$(SHELL) config.status --file=$@:src/Inventor/@Gui@/common/SoGuiObject.h.in

src/Inventor/@Gui@/So@Gui@Object.cpp: \
  $(srcdir)/src/Inventor/@Gui@/common/SoGuiObject.cpp.in config.status
	@$(SHELL) config.status --file=$@:src/Inventor/@Gui@/common/SoGuiObject.cpp.in

src/Inventor/@Gui@/So@Gui@Cursors.h: \
  $(srcdir)/src/Inventor/@Gui@/common/SoGuiCursors.h.in config.status
	@$(SHELL) config.status --file=$@:src/Inventor/@Gui@/common/SoGuiCursors.h.in

src/Inventor/@Gui@/So@Gui@Cursors.cpp: \
  $(srcdir)/src/Inventor/@Gui@/common/SoGuiCursors.cpp.in config.status
	@$(SHELL) config.status --file=$@:src/Inventor/@Gui@/common/SoGuiCursors.cpp.in

src/Inventor/@Gui@/So@Gui@RenderArea.h: \
  $(srcdir)/src/Inventor/@Gui@/common/SoGuiRenderArea.h.in config.status
	@$(SHELL) config.status --file=$@:src/Inventor/@Gui@/common/SoGuiRenderArea.h.in

src/Inventor/@Gui@/So@Gui@RenderArea.cpp: \
  $(srcdir)/src/Inventor/@Gui@/common/SoGuiRenderArea.cpp.in config.status
	@$(SHELL) config.status --file=$@:src/Inventor/@Gui@/common/SoGuiRenderArea.cpp.in

src/Inventor/@Gui@/common/gl.h: \
  $(srcdir)/src/Inventor/@Gui@/common/gl.h.in config.status
	@if test -d src/Inventor/@Gui@/common; then :; else \
	  echo " mkdir src/Inventor/@Gui@/common"; \
	  mkdir src/Inventor/@Gui@/common; \
	fi
	@$(SHELL) config.status --file=$@:src/Inventor/@Gui@/common/gl.h.in

src/Inventor/@Gui@/viewers/So@Gui@Viewer.h: \
  $(srcdir)/src/Inventor/@Gui@/common/SoGuiViewer.h.in config.status
	@$(SHELL) config.status --file=$@:src/Inventor/@Gui@/common/SoGuiViewer.h.in

src/Inventor/@Gui@/viewers/So@Gui@Viewer.cpp: \
  $(srcdir)/src/Inventor/@Gui@/common/SoGuiViewer.cpp.in config.status
	@$(SHELL) config.status --file=$@:src/Inventor/@Gui@/common/SoGuiViewer.cpp.in

src/Inventor/@Gui@/viewers/So@Gui@ConstrainedViewer.h: \
  $(srcdir)/src/Inventor/@Gui@/common/SoGuiConstrainedViewer.h.in config.status
	@$(SHELL) config.status --file=$@:src/Inventor/@Gui@/common/SoGuiConstrainedViewer.h.in

src/Inventor/@Gui@/viewers/So@Gui@ConstrainedViewer.cpp: \
  $(srcdir)/src/Inventor/@Gui@/common/SoGuiConstrainedViewer.cpp.in config.status
	@$(SHELL) config.status --file=$@:src/Inventor/@Gui@/common/SoGuiConstrainedViewer.cpp.in

src/Inventor/@Gui@/viewers/So@Gui@FlyViewer.h: \
  $(srcdir)/src/Inventor/@Gui@/common/SoGuiFlyViewer.h.in config.status
	@$(SHELL) config.status --file=$@:src/Inventor/@Gui@/common/SoGuiFlyViewer.h.in

src/Inventor/@Gui@/viewers/So@Gui@FlyViewer.cpp: \
  $(srcdir)/src/Inventor/@Gui@/common/SoGuiFlyViewer.cpp.in config.status
	@$(SHELL) config.status --file=$@:src/Inventor/@Gui@/common/SoGuiFlyViewer.cpp.in

src/Inventor/@Gui@/viewers/SoAnyFullViewer.h: \
  $(srcdir)/src/Inventor/@Gui@/common/SoAnyFullViewer.h.in config.status
	@$(SHELL) config.status --file=$@:src/Inventor/@Gui@/common/SoAnyFullViewer.h.in

src/Inventor/@Gui@/viewers/SoAnyFullViewer.cpp: \
  $(srcdir)/src/Inventor/@Gui@/common/SoAnyFullViewer.cpp.in config.status
	@$(SHELL) config.status --file=$@:src/Inventor/@Gui@/common/SoAnyFullViewer.cpp.in

src/Inventor/@Gui@/viewers/SoAnyExaminerViewer.h: \
  $(srcdir)/src/Inventor/@Gui@/common/SoAnyExaminerViewer.h.in config.status
	@$(SHELL) config.status \
	  --file=$@:src/Inventor/@Gui@/common/SoAnyExaminerViewer.h.in

src/Inventor/@Gui@/viewers/SoAnyExaminerViewer.cpp: \
  $(srcdir)/src/Inventor/@Gui@/common/SoAnyExaminerViewer.cpp.in config.status
	@$(SHELL) config.status \
	  --file=$@:src/Inventor/@Gui@/common/SoAnyExaminerViewer.cpp.in

src/Inventor/@Gui@/viewers/SoAnyPlaneViewer.h: \
  $(srcdir)/src/Inventor/@Gui@/common/SoAnyPlaneViewer.h.in config.status
	@$(SHELL) config.status \
	  --file=$@:src/Inventor/@Gui@/common/SoAnyPlaneViewer.h.in

src/Inventor/@Gui@/viewers/SoAnyPlaneViewer.cpp: \
  $(srcdir)/src/Inventor/@Gui@/common/SoAnyPlaneViewer.cpp.in config.status
	@$(SHELL) config.status \
	  --file=$@:src/Inventor/@Gui@/common/SoAnyPlaneViewer.cpp.in

src/Inventor/@Gui@/widgets/SoAnyThumbWheel.h: \
  $(srcdir)/src/Inventor/@Gui@/common/SoAnyThumbWheel.h.in config.status
	@$(SHELL) config.status --file=$@:src/Inventor/@Gui@/common/SoAnyThumbWheel.h.in

src/Inventor/@Gui@/widgets/SoAnyThumbWheel.cpp: \
  $(srcdir)/src/Inventor/@Gui@/common/SoAnyThumbWheel.cpp.in config.status
	@$(SHELL) config.status --file=$@:src/Inventor/@Gui@/common/SoAnyThumbWheel.cpp.in

src/Inventor/@Gui@/widgets/SoAnyPopupMenu.h: \
  $(srcdir)/src/Inventor/@Gui@/common/SoAnyPopupMenu.h.in config.status
	@$(SHELL) config.status --file=$@:src/Inventor/@Gui@/common/SoAnyPopupMenu.h.in

src/Inventor/@Gui@/widgets/SoAnyPopupMenu.cpp: \
  $(srcdir)/src/Inventor/@Gui@/common/SoAnyPopupMenu.cpp.in config.status
	@$(SHELL) config.status --file=$@:src/Inventor/@Gui@/common/SoAnyPopupMenu.cpp.in

src/Inventor/@Gui@/devices/spwinput.h: \
  $(srcdir)/src/Inventor/@Gui@/common/spwinput.h.in config.status
	@$(SHELL) config.status --file=$@:src/Inventor/@Gui@/common/spwinput.h.in

src/Inventor/@Gui@/devices/spwinput_x11.cpp: \
  $(srcdir)/src/Inventor/@Gui@/common/spwinput_x11.cpp.in config.status
	@$(SHELL) config.status --file=$@:src/Inventor/@Gui@/common/spwinput_x11.cpp.in

# **************************************************************************
# auto-generated Qt moc files.

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
  $(top_builddir)/src/Inventor/Qt/viewers/SoQtConstrainedViewer.h
	$(MOC) -o $@ $(top_builddir)/src/Inventor/Qt/viewers/SoQtConstrainedViewer.h

src/Inventor/Qt/viewers/moc_SoQtWalkViewer.cpp: \
  $(srcdir)/src/Inventor/Qt/viewers/SoQtWalkViewer.h
	$(MOC) -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/viewers/SoQtWalkViewer.h`

src/Inventor/Qt/viewers/moc_SoQtFlyViewer.cpp: \
  $(top_builddir)/src/Inventor/Qt/viewers/SoQtFlyViewer.h
	$(MOC) -o $@ $(top_builddir)/src/Inventor/Qt/viewers/SoQtFlyViewer.h

src/Inventor/Qt/widgets/moc_SoQtThumbWheel.cpp: \
  $(srcdir)/src/Inventor/Qt/widgets/SoQtThumbWheel.h
	$(MOC) -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/widgets/SoQtThumbWheel.h`

src/Inventor/Qt/widgets/moc_SoQtGLArea.cpp: \
  $(srcdir)/src/Inventor/Qt/widgets/SoQtGLArea.h
	$(MOC) -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/widgets/SoQtGLArea.h`

src/Inventor/Qt/widgets/moc_SoQtPopupMenu.cpp: \
  $(srcdir)/src/Inventor/Qt/widgets/SoQtPopupMenu.h
	$(MOC) -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/widgets/SoQtPopupMenu.h`

# **************************************************************************

all-local: built-sources

doxygen-doc: built-sources
	@( cd build; @sim_ac_doxygen_exe@ so@gui@.doxygen )

doxygen-docs: built-sources
	@( cd build; @sim_ac_doxygen_exe@ so@gui@.doxygen )

install-exec-local: built-sources $(srcdir)/cfg/m4/wrapmsvc.exe
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(bindir)
	@if @BUILD_WITH_MSVC@; then \
	  p=wrapmsvc.exe; \
	  echo " $(INSTALL_PROGRAM) $(srcdir)/cfg/m4/$$p $(DESTDIR)$(bindir)/$$p"; \
	  $(INSTALL_PROGRAM) $(srcdir)/cfg/m4/$$p $(DESTDIR)$(bindir)/$$p; \
	fi

install-data-local: built-sources

# EOF ######################################################################
