## Process this file with automake to generate Makefile.in.

noinst_LTLIBRARIES = libSoQtDevices.la

INCLUDES = -I$(top_builddir)/src -I$(top_srcdir)/src
LIBS =

# every built sourcefile
BUILT_SOURCES = \
	moc_SoQtDevice.cpp \
	moc_SoQtInputFocus.cpp \
	moc_SoQtKeyboard.cpp \
	moc_SoQtMouse.cpp \
	moc_SoQtSpaceball.cpp \
	moc_SoQtLinuxJoystick.cpp \
	spwinput_x11.cpp spwinput.h

# built sourcefiles that are to be included in any case
libSoQtDevicesBuiltSources = \
	moc_SoQtDevice.cpp \
	moc_SoQtInputFocus.cpp \
	moc_SoQtKeyboard.cpp \
	moc_SoQtMouse.cpp \
	moc_SoQtSpaceball.cpp \
	spwinput_x11.cpp spwinput.h

############################################################################
# automake conditional stuff

if HAVE_JOYSTICK_LINUX
libSoQtDevicesLinuxJoystickHeaders = \
        SoQtLinuxJoystick.h

libSoQtDevicesLinuxJoystickSources = \
        SoQtLinuxJoystick.cpp \
	moc_SoQtLinuxJoystick.cpp \
        $(libSoQtDevicesLinuxJoystickHeaders)
else
libSoQtDevicesLinuxJoystickHeaders =
libSoQtDevicesLinuxJoystickSources =
endif

libSoQtDevicesConditionalSources = \
        $(libSoQtDevicesLinuxJoystickSources)

libSoQtDevicesConditionalHeaders = \
        $(libSoQtDevicesLinuxJoystickHeaders)

############################################################################

libSoQtDevices_la_SOURCES = \
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
	$(libSoQtDevicesBuiltSources) \
	$(libSoQtDevicesConditionalSources)

# all the sources that are conditional
EXTRA_libSoQtDevices_la_SOURCES = \
	SoQtLinuxJoystick.h \
	SoQtLinuxJoystick.cpp \
	moc_SoQtLinuxJoystick.cpp

############################################################################
## Header file installation information.

libSoQtDevicesincdir = $(includedir)/Inventor/Qt/devices

libSoQtDevicesinc_HEADERS = \
	$(srcdir)/SoQtDevice.h \
	$(srcdir)/SoQtInputFocus.h \
	$(srcdir)/SoQtKeyboard.h \
	$(srcdir)/SoQtMouse.h \
	$(srcdir)/SoQtSpaceball.h \
	$(libSoQtDevicesConditionalHeaders)

############################################################################

moc_SoQtDevice.cpp: $(srcdir)/SoQtDevice.h
	@( cd $(top_builddir); \
	   $(MAKE) src/Inventor/Qt/devices/moc_SoQtDevice.cpp )

moc_SoQtInputFocus.cpp: $(srcdir)/SoQtInputFocus.h
	@( cd $(top_builddir); \
	   $(MAKE) src/Inventor/Qt/devices/moc_SoQtInputFocus.cpp )

moc_SoQtKeyboard.cpp: $(srcdir)/SoQtKeyboard.h
	@( cd $(top_builddir); \
	   $(MAKE) src/Inventor/Qt/devices/moc_SoQtKeyboard.cpp )

moc_SoQtMouse.cpp: $(srcdir)/SoQtMouse.h
	@( cd $(top_builddir); \
	   $(MAKE) src/Inventor/Qt/devices/moc_SoQtMouse.cpp )

moc_SoQtSpaceball.cpp: $(srcdir)/SoQtSpaceball.h
	@( cd $(top_builddir); \
	   $(MAKE) src/Inventor/Qt/devices/moc_SoQtSpaceball.cpp )

moc_SoQtLinuxJoystick.cpp: $(srcdir)/SoQtLinuxJoystick.h
	@( cd $(top_builddir); \
	   $(MAKE) src/Inventor/Qt/devices/moc_SoQtLinuxJoystick.cpp )

spwinput.h: $(top_srcdir)/src/Inventor/Qt/common/spwinput.h.in
	@( cd $(top_builddir); $(MAKE) src/Inventor/Qt/devices/spwinput.h )

spwinput_x11.cpp: $(top_srcdir)/src/Inventor/Qt/common/spwinput_x11.cpp.in
	@( cd $(top_builddir); \
		$(MAKE) src/Inventor/Qt/devices/spwinput_x11.cpp )

