## Process this file with automake to generate Makefile.in.

noinst_LTLIBRARIES = libSoQtDevices.la

INCLUDES = -I$(top_builddir)/src -I$(top_srcdir)/src
LIBS =

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
	SoQtSpaceball.h

############################################################################
## Header file installation information.

libSoQtDevicesincdir = $(includedir)/Inventor/Qt/devices

libSoQtDevicesinc_HEADERS = \
	$(srcdir)/SoQtDevice.h \
	$(srcdir)/SoQtInputFocus.h \
	$(srcdir)/SoQtKeyboard.h \
	$(srcdir)/SoQtMouse.h \
	$(srcdir)/SoQtSpaceball.h
