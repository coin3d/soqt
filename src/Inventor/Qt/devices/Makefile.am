############################################################################
##

include ../common/Makefile.common

DEFAULT_INCLUDES = -I$(top_builddir)/src -I$(top_srcdir)/src

LIBS =

BUILT_SOURCES = \
	$(SoGuiAllBuiltFiles)

CLEANFILES = \
	$(SoGui_src_Inventor_Gui_devices_BuiltMetaFiles)

DISTCLEANFILES = \
	$(SoGui_src_Inventor_Gui_devices_BuiltFiles) \
	$(SoGui_src_Inventor_Gui_devices_BuiltMetaFiles) \
	SoQtDevice.h \
	SoQtInputFocus.h \
	SoQtKeyboard.h \
	SoQtMouse.h

## Process this file with automake to generate Makefile.in.

if BUILD_WITH_MSVC
noinst_LIBRARIES = devices.lst
else
noinst_LTLIBRARIES = libSoQtDevices.la
endif

############################################################################
# automake conditional stuff

# if HAVE_JOYSTICK_LINUX
# libSoQtDevicesLinuxJoystickHeaders = \
#         SoQtLinuxJoystick.h
# 
# libSoQtDevicesLinuxJoystickSources = \
#         SoQtLinuxJoystick.cpp \
# 	moc_SoQtLinuxJoystick.icc \
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

RegularSources = \
	SoQtDevice.cpp \
	SoQtDeviceP.h \
	SoQtInputFocus.cpp \
	SoQtKeyboard.cpp \
	SoQtMouse.cpp \
	6DOFEvents.cpp \
	6DOFEvents.h \
	$(libSoQtDevicesConditionalSources)

BuiltSources = \
	$(SoGui_src_Inventor_Gui_devices_BuiltFiles)

LinkHackSources = \
	all-devices-cpp.cpp \
	all-devices2-cpp.cpp

if HACKING_COMPACT_BUILD
BuildSources = $(LinkHackSources)
NoDistSources =
ExtraSources = $(RegularSources)
else
BuildSources = $(RegularSources)
NoDistSources = $(BuiltSources)
ExtraSources = $(LinkHackSources)
endif

libSoQtDevices_la_SOURCES = \
	$(BuildSources)

nodist_libSoQtDevices_la_SOURCES = \
	$(NoDistSources)

# all the sources that are conditionally not built
EXTRA_libSoQtDevices_la_SOURCES = \
	$(ExtraSources)

############################################################################
# custom setup

devices_lst_SOURCES = \
	$(BuildSources)

nodist_devices_lst_SOURCES = \
	$(NoDistSources)

devices.lst: Makefile $(devices_lst_OBJECTS)
	@echo "Linking $@..."; \
	rm -f $@; \
	for i in $(devices_lst_OBJECTS); do echo $$i >>$@; done

############################################################################
## Header file installation information.

if MAC_FRAMEWORK
SoQtDevicesincdir = $(MAC_FRAMEWORK_PREFIX)/$(MAC_FRAMEWORK_NAME).framework/Versions/$(MAC_FRAMEWORK_VERSION)/Headers/devices
else
SoQtDevicesincdir = $(includedir)/Inventor/@Gui@/devices
endif
SoQtDevicesinc_HEADERS =

nodist_SoQtDevicesinc_HEADERS = \
	SoQtDevice.h \
	SoQtKeyboard.h \
	SoQtMouse.h

install-SoQtDevicesincHEADERS: $(SoQtDevicesinc_HEADERS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(SoQtDevicesincdir)
	@list='$(SoQtDevicesinc_HEADERS)'; for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  src="$$d$$p"; dst="$(DESTDIR)$(SoQtDevicesincdir)/$$f"; \
	  if cmp -s "$$src" "$$dst"; then :; else \
	    echo " $(INSTALL_HEADER) $$src $$dst"; \
	    $(INSTALL_HEADER) "$$src" "$$dst" || exit 1; \
	  fi \
	done

install-nodist_SoQtDevicesincHEADERS: $(nodist_SoQtDevicesinc_HEADERS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(SoQtDevicesincdir)
	@list='$(nodist_SoQtDevicesinc_HEADERS)'; for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  src="$$d$$p"; dst="$(DESTDIR)$(SoQtDevicesincdir)/$$f"; \
	  if cmp -s "$$src" "$$dst"; then :; else \
	    echo " $(INSTALL_HEADER) $$src $$dst"; \
	    $(INSTALL_HEADER) "$$src" "$$dst" || exit 1; \
	  fi \
	done

# EOF ######################################################################
