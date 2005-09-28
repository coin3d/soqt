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

if BUILD_HTMLHELP
HTMLHELPDIR = htmlhelp
else
HTMLHELPDIR =
endif

if BUILD_LIBRARY
# Material editor(s) not part of the public API yet, so there's
# no point yet in installing the material data.
#LIBDIR = data src
LIBDIR = src
else
LIBDIR =
endif

DOCDIRS = man $(HTMLDIR) $(HTMLHELPDIR)

SUBDIRS = . $(LIBDIR) $(DOCDIRS)

SoQtBuiltFiles = \
	src/Inventor/Qt/widgets/moc_QtNativePopupMenu.icc \
	src/Inventor/Qt/widgets/moc_SoQtGLArea.icc \
	src/Inventor/Qt/widgets/moc_SoQtThumbWheel.icc


BUILT_SOURCES = \
	$(SoGuiAllBuiltFiles) \
	$(SoQtBuiltFiles)

CLEANFILES = \
	$(SoGui_BuiltMetaFiles)

DISTCLEANFILES = \
	libtool \
	$(SoGui_BuiltFiles) \
	$(SoGui_BuiltMetaFiles) \
	$(SoQtBuiltFiles)

if BUILD_LIBRARY
if MAC_FRAMEWORK
frameworkdatadir = $(MAC_FRAMEWORK_PREFIX)/$(MAC_FRAMEWORK_NAME).framework/Versions/$(MAC_FRAMEWORK_VERSION)/Resources
frameworkdata_DATA = Info.plist
endif


bin_SCRIPTS = so@gui@-config

m4datadir = $(datadir)/aclocal

# Don't replace "qt" with "@gui@" here, is it will pøkk up
# for ``make dist''.
dist_m4data_DATA = cfg/soqt.m4

cfgdatadir = $(datadir)/Coin/conf
cfgdata_DATA = so@gui@-@CONFIG@.cfg

endif

EXTRA_DIST = \
	FAQ \
	INSTALL.GNU \
	LICENSE.GPL \
	README.IRIX \
	README.WIN32 \
	README.MACOSX \
	Info.plist \
	build/msvc6/src/Inventor/Qt/common/gl.h \
	build/msvc6/src/Inventor/Qt/SoAny.cpp \
	build/msvc6/src/Inventor/Qt/SoAny.h \
	build/msvc6/src/Inventor/Qt/SoGuiComponentP.h \
	build/msvc6/src/Inventor/Qt/SoGuiGLWidgetP.h \
	build/msvc6/src/Inventor/Qt/SoGuiP.h \
	build/msvc6/src/Inventor/Qt/SoQt.h \
	build/msvc6/src/Inventor/Qt/SoQtBasic.h \
	build/msvc6/src/Inventor/Qt/SoQtColorEditor.h \
	build/msvc6/src/Inventor/Qt/SoQtCommon.cpp \
	build/msvc6/src/Inventor/Qt/SoQtComponent.h \
	build/msvc6/src/Inventor/Qt/SoQtComponentCommon.cpp \
	build/msvc6/src/Inventor/Qt/SoQtCursor.cpp \
	build/msvc6/src/Inventor/Qt/SoQtCursor.h \
	build/msvc6/src/Inventor/Qt/SoQtGLWidget.h \
	build/msvc6/src/Inventor/Qt/SoQtGLWidgetCommon.cpp \
	build/msvc6/src/Inventor/Qt/SoQtMaterialEditor.h \
	build/msvc6/src/Inventor/Qt/SoQtObject.cpp \
	build/msvc6/src/Inventor/Qt/devices/SoGuiDeviceP.h \
	build/msvc6/src/Inventor/Qt/devices/SoGuiInputFocusP.h \
	build/msvc6/src/Inventor/Qt/devices/SoGuiKeyboardP.h \
	build/msvc6/src/Inventor/Qt/devices/SoGuiMouseP.h \
	build/msvc6/src/Inventor/Qt/devices/SoGuiSpaceballP.h \
	build/msvc6/src/Inventor/Qt/devices/SoQtDevice.h \
	build/msvc6/src/Inventor/Qt/devices/SoQtDeviceCommon.cpp \
	build/msvc6/src/Inventor/Qt/devices/SoQtInputFocus.h \
	build/msvc6/src/Inventor/Qt/devices/SoQtInputFocusCommon.cpp \
	build/msvc6/src/Inventor/Qt/devices/SoQtKeyboard.h \
	build/msvc6/src/Inventor/Qt/devices/SoQtKeyboardCommon.cpp \
	build/msvc6/src/Inventor/Qt/devices/SoQtMouse.h \
	build/msvc6/src/Inventor/Qt/devices/SoQtMouseCommon.cpp \
	build/msvc6/src/Inventor/Qt/devices/SoQtSpaceball.h \
	build/msvc6/src/Inventor/Qt/devices/SoQtSpaceballCommon.cpp \
	build/msvc6/src/Inventor/Qt/devices/spwinput.h \
	build/msvc6/src/Inventor/Qt/devices/spwinput_win32.c \
	build/msvc6/src/Inventor/Qt/devices/spwinput_win32.h \
	build/msvc6/src/Inventor/Qt/devices/spwinput_x11.cpp \
	build/msvc6/src/Inventor/Qt/SoQtObject.h \
	build/msvc6/src/Inventor/Qt/SoQtRenderArea.cpp \
	build/msvc6/src/Inventor/Qt/SoQtRenderArea.h \
	build/msvc6/src/Inventor/Qt/editors/SoQtColorEditor.cpp \
	build/msvc6/src/Inventor/Qt/editors/SoQtColorEditor.h \
	build/msvc6/src/Inventor/Qt/editors/SoQtMaterialEditor.cpp \
	build/msvc6/src/Inventor/Qt/editors/SoQtMaterialEditor.h \
	build/msvc6/src/Inventor/Qt/engines/Engines.cpp \
	build/msvc6/src/Inventor/Qt/engines/Format.cpp \
	build/msvc6/src/Inventor/Qt/engines/RadioGroup.cpp \
	build/msvc6/src/Inventor/Qt/engines/SoGuiEngines.h \
	build/msvc6/src/Inventor/Qt/engines/SoGuiFormat.h \
	build/msvc6/src/Inventor/Qt/engines/SoGuiRadioGroup.h \
	build/msvc6/src/Inventor/Qt/nodes/ClickCounter.cpp \
	build/msvc6/src/Inventor/Qt/nodes/ColorEditor.cpp \
	build/msvc6/src/Inventor/Qt/nodes/Frame.cpp \
	build/msvc6/src/Inventor/Qt/nodes/Image.cpp \
	build/msvc6/src/Inventor/Qt/nodes/Label.cpp \
	build/msvc6/src/Inventor/Qt/nodes/MaterialEditor.cpp \
	build/msvc6/src/Inventor/Qt/nodes/Nodes.cpp \
	build/msvc6/src/Inventor/Qt/nodes/Pane.cpp \
	build/msvc6/src/Inventor/Qt/nodes/Position.cpp \
	build/msvc6/src/Inventor/Qt/nodes/RadioButton.cpp \
	build/msvc6/src/Inventor/Qt/nodes/SceneTexture2.cpp \
	build/msvc6/src/Inventor/Qt/nodes/Slider1.cpp \
	build/msvc6/src/Inventor/Qt/nodes/Slider2.cpp \
	build/msvc6/src/Inventor/Qt/nodes/SoGuiClickCounter.h \
	build/msvc6/src/Inventor/Qt/nodes/SoGuiColorEditor.h \
	build/msvc6/src/Inventor/Qt/nodes/SoGuiFrame.h \
	build/msvc6/src/Inventor/Qt/nodes/SoGuiImage.h \
	build/msvc6/src/Inventor/Qt/nodes/SoGuiLabel.h \
	build/msvc6/src/Inventor/Qt/nodes/SoGuiMaterialEditor.h \
	build/msvc6/src/Inventor/Qt/nodes/SoGuiNodes.h \
	build/msvc6/src/Inventor/Qt/nodes/SoGuiPane.h \
	build/msvc6/src/Inventor/Qt/nodes/SoGuiPosition.h \
	build/msvc6/src/Inventor/Qt/nodes/SoGuiRadioButton.h \
	build/msvc6/src/Inventor/Qt/nodes/SoGuiSceneTexture2.h \
	build/msvc6/src/Inventor/Qt/nodes/SoGuiSlider1.h \
	build/msvc6/src/Inventor/Qt/nodes/SoGuiSlider2.h \
	build/msvc6/src/Inventor/Qt/nodes/SoGuiToggleButton.h \
	build/msvc6/src/Inventor/Qt/nodes/SoGuiTranslation.h \
	build/msvc6/src/Inventor/Qt/nodes/SoGuiViewpointWrapper.h \
	build/msvc6/src/Inventor/Qt/nodes/SoGuiViewportFix.h \
	build/msvc6/src/Inventor/Qt/nodes/ToggleButton.cpp \
	build/msvc6/src/Inventor/Qt/nodes/Translation.cpp \
	build/msvc6/src/Inventor/Qt/nodes/ViewpointWrapper.cpp \
	build/msvc6/src/Inventor/Qt/nodes/ViewportFix.cpp \
	build/msvc6/src/Inventor/Qt/viewers/SoGuiExaminerViewerP.h \
	build/msvc6/src/Inventor/Qt/viewers/SoGuiFullViewerP.h \
	build/msvc6/src/Inventor/Qt/viewers/SoGuiPlaneViewerP.h \
	build/msvc6/src/Inventor/Qt/viewers/SoQtConstrainedViewer.cpp \
	build/msvc6/src/Inventor/Qt/viewers/SoQtConstrainedViewer.h \
	build/msvc6/src/Inventor/Qt/viewers/SoQtExaminerViewer.cpp \
	build/msvc6/src/Inventor/Qt/viewers/SoQtExaminerViewer.h \
	build/msvc6/src/Inventor/Qt/viewers/SoQtFlyViewer.cpp \
	build/msvc6/src/Inventor/Qt/viewers/SoQtFlyViewer.h \
	build/msvc6/src/Inventor/Qt/viewers/SoQtFullViewer.cpp \
	build/msvc6/src/Inventor/Qt/viewers/SoQtFullViewer.h \
	build/msvc6/src/Inventor/Qt/viewers/SoQtPlaneViewer.cpp \
	build/msvc6/src/Inventor/Qt/viewers/SoQtPlaneViewer.h \
	build/msvc6/src/Inventor/Qt/viewers/SoQtViewer.cpp \
	build/msvc6/src/Inventor/Qt/viewers/SoQtViewer.h \
	build/msvc6/src/Inventor/Qt/widgets/SoAnyThumbWheel.cpp \
	build/msvc6/src/Inventor/Qt/widgets/SoAnyThumbWheel.h \
	build/msvc6/src/Inventor/Qt/widgets/SoQtPopupMenu.cpp \
	build/msvc6/src/Inventor/Qt/widgets/SoQtPopupMenu.h \
	build/msvc6/src/config.h \
	build/msvc6/src/config-debug.h \
	build/msvc6/src/config-release.h \
	build/msvc6/src/soqtdefs.h \
	build/msvc6/install-lib-debug.bat \
	build/msvc6/install-lib-release.bat \
	build/msvc6/install-dll-debug.bat \
	build/msvc6/install-dll-release.bat \
	build/msvc6/install-headers.bat \
	build/msvc6/delete-moc-files.bat \
	build/msvc6/soqt1.dsp \
	build/msvc6/soqt1.dsw \
	build/msvc6/generate.sh \
	build/msvc6/config-wrapper.h \
	build/msvc7/src/Inventor/Qt/common/gl.h \
	build/msvc7/src/Inventor/Qt/SoAny.cpp \
	build/msvc7/src/Inventor/Qt/SoAny.h \
	build/msvc7/src/Inventor/Qt/SoGuiComponentP.h \
	build/msvc7/src/Inventor/Qt/SoGuiGLWidgetP.h \
	build/msvc7/src/Inventor/Qt/SoGuiP.h \
	build/msvc7/src/Inventor/Qt/SoQt.h \
	build/msvc7/src/Inventor/Qt/SoQtBasic.h \
	build/msvc7/src/Inventor/Qt/SoQtColorEditor.h \
	build/msvc7/src/Inventor/Qt/SoQtCommon.cpp \
	build/msvc7/src/Inventor/Qt/SoQtComponent.h \
	build/msvc7/src/Inventor/Qt/SoQtComponentCommon.cpp \
	build/msvc7/src/Inventor/Qt/SoQtCursor.cpp \
	build/msvc7/src/Inventor/Qt/SoQtCursor.h \
	build/msvc7/src/Inventor/Qt/SoQtGLWidget.h \
	build/msvc7/src/Inventor/Qt/SoQtGLWidgetCommon.cpp \
	build/msvc7/src/Inventor/Qt/SoQtMaterialEditor.h \
	build/msvc7/src/Inventor/Qt/SoQtObject.cpp \
	build/msvc7/src/Inventor/Qt/devices/SoGuiDeviceP.h \
	build/msvc7/src/Inventor/Qt/devices/SoGuiInputFocusP.h \
	build/msvc7/src/Inventor/Qt/devices/SoGuiKeyboardP.h \
	build/msvc7/src/Inventor/Qt/devices/SoGuiMouseP.h \
	build/msvc7/src/Inventor/Qt/devices/SoGuiSpaceballP.h \
	build/msvc7/src/Inventor/Qt/devices/SoQtDevice.h \
	build/msvc7/src/Inventor/Qt/devices/SoQtDeviceCommon.cpp \
	build/msvc7/src/Inventor/Qt/devices/SoQtInputFocus.h \
	build/msvc7/src/Inventor/Qt/devices/SoQtInputFocusCommon.cpp \
	build/msvc7/src/Inventor/Qt/devices/SoQtKeyboard.h \
	build/msvc7/src/Inventor/Qt/devices/SoQtKeyboardCommon.cpp \
	build/msvc7/src/Inventor/Qt/devices/SoQtMouse.h \
	build/msvc7/src/Inventor/Qt/devices/SoQtMouseCommon.cpp \
	build/msvc7/src/Inventor/Qt/devices/SoQtSpaceball.h \
	build/msvc7/src/Inventor/Qt/devices/SoQtSpaceballCommon.cpp \
	build/msvc7/src/Inventor/Qt/devices/spwinput.h \
	build/msvc7/src/Inventor/Qt/devices/spwinput_win32.c \
	build/msvc7/src/Inventor/Qt/devices/spwinput_win32.h \
	build/msvc7/src/Inventor/Qt/devices/spwinput_x11.cpp \
	build/msvc7/src/Inventor/Qt/SoQtObject.h \
	build/msvc7/src/Inventor/Qt/SoQtRenderArea.cpp \
	build/msvc7/src/Inventor/Qt/SoQtRenderArea.h \
	build/msvc7/src/Inventor/Qt/editors/SoQtColorEditor.cpp \
	build/msvc7/src/Inventor/Qt/editors/SoQtColorEditor.h \
	build/msvc7/src/Inventor/Qt/editors/SoQtMaterialEditor.cpp \
	build/msvc7/src/Inventor/Qt/editors/SoQtMaterialEditor.h \
	build/msvc7/src/Inventor/Qt/engines/Engines.cpp \
	build/msvc7/src/Inventor/Qt/engines/Format.cpp \
	build/msvc7/src/Inventor/Qt/engines/RadioGroup.cpp \
	build/msvc7/src/Inventor/Qt/engines/SoGuiEngines.h \
	build/msvc7/src/Inventor/Qt/engines/SoGuiFormat.h \
	build/msvc7/src/Inventor/Qt/engines/SoGuiRadioGroup.h \
	build/msvc7/src/Inventor/Qt/nodes/ClickCounter.cpp \
	build/msvc7/src/Inventor/Qt/nodes/ColorEditor.cpp \
	build/msvc7/src/Inventor/Qt/nodes/Frame.cpp \
	build/msvc7/src/Inventor/Qt/nodes/Image.cpp \
	build/msvc7/src/Inventor/Qt/nodes/Label.cpp \
	build/msvc7/src/Inventor/Qt/nodes/MaterialEditor.cpp \
	build/msvc7/src/Inventor/Qt/nodes/Nodes.cpp \
	build/msvc7/src/Inventor/Qt/nodes/Pane.cpp \
	build/msvc7/src/Inventor/Qt/nodes/Position.cpp \
	build/msvc7/src/Inventor/Qt/nodes/RadioButton.cpp \
	build/msvc7/src/Inventor/Qt/nodes/SceneTexture2.cpp \
	build/msvc7/src/Inventor/Qt/nodes/Slider1.cpp \
	build/msvc7/src/Inventor/Qt/nodes/Slider2.cpp \
	build/msvc7/src/Inventor/Qt/nodes/SoGuiClickCounter.h \
	build/msvc7/src/Inventor/Qt/nodes/SoGuiColorEditor.h \
	build/msvc7/src/Inventor/Qt/nodes/SoGuiFrame.h \
	build/msvc7/src/Inventor/Qt/nodes/SoGuiImage.h \
	build/msvc7/src/Inventor/Qt/nodes/SoGuiLabel.h \
	build/msvc7/src/Inventor/Qt/nodes/SoGuiMaterialEditor.h \
	build/msvc7/src/Inventor/Qt/nodes/SoGuiNodes.h \
	build/msvc7/src/Inventor/Qt/nodes/SoGuiPane.h \
	build/msvc7/src/Inventor/Qt/nodes/SoGuiPosition.h \
	build/msvc7/src/Inventor/Qt/nodes/SoGuiRadioButton.h \
	build/msvc7/src/Inventor/Qt/nodes/SoGuiSceneTexture2.h \
	build/msvc7/src/Inventor/Qt/nodes/SoGuiSlider1.h \
	build/msvc7/src/Inventor/Qt/nodes/SoGuiSlider2.h \
	build/msvc7/src/Inventor/Qt/nodes/SoGuiToggleButton.h \
	build/msvc7/src/Inventor/Qt/nodes/SoGuiTranslation.h \
	build/msvc7/src/Inventor/Qt/nodes/SoGuiViewpointWrapper.h \
	build/msvc7/src/Inventor/Qt/nodes/SoGuiViewportFix.h \
	build/msvc7/src/Inventor/Qt/nodes/ToggleButton.cpp \
	build/msvc7/src/Inventor/Qt/nodes/Translation.cpp \
	build/msvc7/src/Inventor/Qt/nodes/ViewpointWrapper.cpp \
	build/msvc7/src/Inventor/Qt/nodes/ViewportFix.cpp \
	build/msvc7/src/Inventor/Qt/viewers/SoGuiExaminerViewerP.h \
	build/msvc7/src/Inventor/Qt/viewers/SoGuiFullViewerP.h \
	build/msvc7/src/Inventor/Qt/viewers/SoGuiPlaneViewerP.h \
	build/msvc7/src/Inventor/Qt/viewers/SoQtConstrainedViewer.cpp \
	build/msvc7/src/Inventor/Qt/viewers/SoQtConstrainedViewer.h \
	build/msvc7/src/Inventor/Qt/viewers/SoQtExaminerViewer.cpp \
	build/msvc7/src/Inventor/Qt/viewers/SoQtExaminerViewer.h \
	build/msvc7/src/Inventor/Qt/viewers/SoQtFlyViewer.cpp \
	build/msvc7/src/Inventor/Qt/viewers/SoQtFlyViewer.h \
	build/msvc7/src/Inventor/Qt/viewers/SoQtFullViewer.cpp \
	build/msvc7/src/Inventor/Qt/viewers/SoQtFullViewer.h \
	build/msvc7/src/Inventor/Qt/viewers/SoQtPlaneViewer.cpp \
	build/msvc7/src/Inventor/Qt/viewers/SoQtPlaneViewer.h \
	build/msvc7/src/Inventor/Qt/viewers/SoQtViewer.cpp \
	build/msvc7/src/Inventor/Qt/viewers/SoQtViewer.h \
	build/msvc7/src/Inventor/Qt/widgets/SoAnyThumbWheel.cpp \
	build/msvc7/src/Inventor/Qt/widgets/SoAnyThumbWheel.h \
	build/msvc7/src/Inventor/Qt/widgets/SoQtPopupMenu.cpp \
	build/msvc7/src/Inventor/Qt/widgets/SoQtPopupMenu.h \
	build/msvc7/src/config.h \
	build/msvc7/src/config-release.h \
	build/msvc7/src/config-debug.h \
	build/msvc7/src/soqtdefs.h \
	build/msvc7/install-lib-debug.bat \
	build/msvc7/install-lib-release.bat \
	build/msvc7/install-dll-debug.bat \
	build/msvc7/install-dll-release.bat \
	build/msvc7/install-headers.bat \
	build/msvc7/delete-moc-files.bat \
	build/msvc7/soqt1.sln \
	build/msvc7/soqt1.vcproj \
	build/msvc7/generate.sh \
	build/msvc7/fixvcproj.sh \
	build/msvc7/config-wrapper.h \
	cfg/soqt.m4 \
	cfg/gendsp.sh.in \
	docs/announcement-1_0_0.txt \
	docs/announcement-1_0_1.txt \
	docs/announcement-1_0_2.txt \
	docs/announcement-1_2_0.txt \
	docs/announcement-1_3_0.txt \
	docs/ChangeLog.v1.0.0 \
	docs/ChangeLog.v1.0.1 \
	docs/ChangeLog.v1.0.2 \
	docs/ChangeLog.v1.2.0 \
	docs/ChangeLog.v1.3.0 \
	models/coin_soqt.iv \
	models/coin_soqt.wrl \
	test-code/README \
	test-code/components/scrollview.cpp \
	test-code/components/tripleview.cpp \
  packaging/macosx/checklist.txt \
  packaging/macosx/SoQt_Description.plist.in \
  packaging/macosx/SoQt_Info.plist.in \
  packaging/macosx/SoQt_Welcome.rtf \
  packaging/macosx/SoQtTools_Description.plist.in \
  packaging/macosx/SoQtTools_Info.plist.in \
  packaging/macosx/SoQtTools_Welcome.rtf \
  packaging/macosx/inst-dmg-files/.DS_Store \
  packaging/macosx/inst-dmg-files/.VolumeIcon.icns \
  packaging/macosx/inst-dmg-files/dmg_bg.tiff \
  packaging/macosx/inst-dmg-files/Desktop_DB \
  packaging/macosx/inst-dmg-files/Desktop_DF \
  packaging/macosx/License.rtf \
  packaging/macosx/makesoqtpkg.sh.in \
  packaging/macosx/makesoqttoolspkg.sh.in \
  packaging/macosx/makedmg.sh.in \
  packaging/macosx/Makefile.in \
  packaging/macosx/makeinstdmg.sh.in \
  packaging/macosx/makenoinstdmg.sh.in \
  packaging/macosx/noinst-dmg-files/.DS_Store \
  packaging/macosx/noinst-dmg-files/.VolumeIcon.icns \
  packaging/macosx/noinst-dmg-files/dmg_bg.tiff \
  packaging/macosx/noinst-dmg-files/Desktop_DB \
  packaging/macosx/noinst-dmg-files/Desktop_DF \
  packaging/macosx/noinst-README-gcc4.txt.in \
  packaging/macosx/noinst-README-gcc3.txt.in \
  packaging/macosx/inst-README-gcc4.txt.in \
  packaging/macosx/inst-README-gcc3.txt.in \
  packaging/macosx/background.tiff \
	packaging/windows/Makefile.in \
	packaging/windows/bfheader.nsi.in \
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
install-exec-local: built-sources $(srcdir)/cfg/wrapmsvc.exe
	@$(NORMAL_INSTALL)
	@if @BUILD_WITH_MSVC@; then \
	  echo " $(mkinstalldirs) $(DESTDIR)$(bindir)"; \
	  $(mkinstalldirs) "$(DESTDIR)$(bindir)"; \
	  p=wrapmsvc.exe; \
	  echo " $(INSTALL_PROGRAM) $(top_srcdir)/cfg/$$p $(DESTDIR)$(bindir)/$$p"; \
	  $(INSTALL_PROGRAM) "$(top_srcdir)/cfg/$$p" "$(DESTDIR)$(bindir)/$$p"; \
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

# src/Inventor/Qt/widgets/moc_SoQtGradientDialogP.icc: $(srcdir)/src/Inventor/Qt/widgets/gradientp/SoQtGradientDialogP.h
# 	$(MOC) -i -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/widgets/gradientp/SoQtGradientDialogP.h`
# 
# src/Inventor/Qt/widgets/moc_GradientView.icc: $(srcdir)/src/Inventor/Qt/widgets/gradientp/GradientView.h
# 	$(MOC) -i -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/widgets/gradientp/GradientView.h`
# 
# src/Inventor/Qt/widgets/moc_SoQtColorTableEditorP.icc: $(srcdir)/src/Inventor/Qt/widgets/curvep/SoQtColorTableEditorP.h
# 	$(MOC) -i -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/widgets/curvep/SoQtColorTableEditorP.h`
# 
# src/Inventor/Qt/widgets/moc_CurveView.icc: $(srcdir)/src/Inventor/Qt/widgets/curvep/CurveView.h
# 	$(MOC) -i -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/widgets/curvep/CurveView.h`
# 
src/Inventor/Qt/widgets/moc_QtNativePopupMenu.icc: $(srcdir)/src/Inventor/Qt/widgets/QtNativePopupMenu.h
	$(MOC) -i -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/widgets/QtNativePopupMenu.h`

src/Inventor/Qt/widgets/moc_SoQtThumbWheel.icc: $(srcdir)/src/Inventor/Qt/widgets/SoQtThumbWheel.h
	$(MOC) -i -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/widgets/SoQtThumbWheel.h`

src/Inventor/Qt/widgets/moc_SoQtGLArea.icc: $(srcdir)/src/Inventor/Qt/widgets/SoQtGLArea.h
	$(MOC) -i -o $@ `$(UNIX2WINPATH) $(srcdir)/src/Inventor/Qt/widgets/SoQtGLArea.h`

# FIXME: use MACOSX_PACKAGEABLE as in Coin build setup? 20050928 kyrah 

macosx-files:
	@if test -d macosx; then :; else mkdir macosx; fi
	@for file in $(top_srcdir)/packaging/macosx/*.in; do \
	  basename=`basename $$file .in`; \
          if ! test -f macosx/$$basename; then \
	    ./config.status --file=macosx/$$basename:$$file; \
          fi \
	done

macosx-packages: macosx-files
macosx-packages:
	@( cd macosx; $(MAKE) VERSION=$(VERSION) )

# **************************************************************************

# FIXME: this should somehow be enabled to make sure the archive is
# bootstrappable, but since distcheck isn't run on our bootstrap server
# it is disabled for now.  Also, bootstrap needs to return a useful
# return code before it can be enabled.
#
# distcheck-hook:
# 	@cd $(distdir); \
# 	./bootstrap

# EOF ######################################################################
