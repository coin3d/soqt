############################################################################
##

include ../common/Makefile.common

INCLUDES = -I$(top_srcdir)/src

LIBS =

BUILT_SOURCES = \
	$(SoGuiAllBuiltFiles)

CLEANFILES = \
	$(SoGui_src_Inventor_Gui_devices_BuiltMetaFiles)

DISTCLEANFILES = \
	$(SoGui_src_Inventor_Gui_devices_BuiltFiles) \
	$(SoGui_src_Inventor_Gui_devices_BuiltMetaFiles)

## Process this file with automake to generate Makefile.in.

if BUILD_WITH_MSVC
noinst_LIBRARIES = devices.lst
else
noinst_LTLIBRARIES = libSoQtDevices.la
endif

# built sourcefiles that are to be included in any case
libSoQtDevicesBuiltSources = \
	SoQtInputFocus.h \
	SoQtKeyboard.h \
	SoQtMouse.h \
	SoQtSpaceball.h \
	moc_SoQtDevice.cpp \
	moc_SoQtInputFocus.cpp \
	moc_SoQtKeyboard.cpp \
	moc_SoQtMouse.cpp \
	moc_SoQtSpaceball.cpp \
	spwinput_x11.cpp \
	spwinput.h

############################################################################
# automake conditional stuff

# if HAVE_JOYSTICK_LINUX
# libSoQtDevicesLinuxJoystickHeaders = \
#         SoQtLinuxJoystick.h
# 
# libSoQtDevicesLinuxJoystickSources = \
#         SoQtLinuxJoystick.cpp \
# 	moc_SoQtLinuxJoystick.cpp \
#         $(libSoQtDevicesLinuxJoystickHeaders)
# else
libSoQtDevicesLinuxJoystickHeaders =
libSoQtDevicesLinuxJoystickSources =
# endif

libSoQtDevicesConditionalSources = \
        $(libSoQtDevicesLinuxJoystickSources)

# libSoQtDevicesConditionalHeaders = \
#         $(libSoQtDevicesLinuxJoystickHeaders)

############################################################################
# libtool setup

libSoQtDevices_la_SOURCES = \
	SoQtDevice.cpp \
	SoQtDevice.h \
	SoQtInputFocus.cpp \
	SoQtKeyboard.cpp \
	SoQtMouse.cpp \
	SoQtSpaceball.cpp \
	$(libSoQtDevicesConditionalSources)

nodist_libSoQtDevices_la_SOURCES = \
	$(SoGui_src_Inventor_Gui_devices_BuiltFiles) \
	$(SoGui_src_Inventor_Gui_devices_BuiltMetaFiles)

# all the sources that are conditional
EXTRA_libSoQtDevices_la_SOURCES = \
	SoQtLinuxJoystick.h \
	SoQtLinuxJoystick.cpp

############################################################################
# custom setup

devices_lst_SOURCES = \
	SoQtDevice.cpp \
	SoQtDevice.h \
	SoQtInputFocus.cpp \
	SoQtInputFocus.h \
	SoQtKeyboard.cpp \
	SoQtKeyboard.h \
	SoQtMouse.cpp \
	SoQtMouse.h \
	SoQtSpaceball.cpp \
	SoQtSpaceball.h \
	$(libSoQtDevicesConditionalSources)

nodist_devices_lst_SOURCES = \
	$(SoGui_src_Inventor_Gui_devices_BuiltFiles) \
	$(SoGui_src_Inventor_Gui_devices_BuiltMetaFiles)

devices.lst: Makefile $(devices_lst_OBJECTS)
	@echo "Linking devices.lst..."; \
	rm -f $@; \
	for i in $(devices_lst_OBJECTS); do echo $$i >>$@; done

############################################################################
## Header file installation information.

libSoQtDevicesincdir = $(includedir)/Inventor/Qt/devices
libSoQtDevicesinc_HEADERS = \
	SoQtDevice.h \
	SoQtInputFocus.h \
	SoQtKeyboard.h \
	SoQtMouse.h \
	SoQtSpaceball.h
# FIXME: this is bad practice...
#	$(libSoQtDevicesConditionalHeaders)

install-libSoQtDevicesincHEADERS: $(libSoQtDevicesinc_HEADERS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(libSoQtDevicesincdir)
	@list='$(libSoQtDevicesinc_HEADERS)'; for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  src="$$d$$p"; dst="$(DESTDIR)$(libSoQtDevicesincdir)/$$f"; \
	  if cmp -s "$$src" "$$dst"; then :; else \
	    echo " $(INSTALL_HEADER) $$src $$dst"; \
	    $(INSTALL_HEADER) "$$src" "$$dst"; \
	  fi \
	done

# EOF ######################################################################
