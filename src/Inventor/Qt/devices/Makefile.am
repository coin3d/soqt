## Process this file with automake to generate Makefile.in.

noinst_LTLIBRARIES = libSoQtDevices.la

## Remove any linklibraries detected by configure, as they are not
## needed in the submodules -- only in the toplevel libSoQt build.
LIBS = 

INCLUDES = -I$(top_srcdir)/src

## All source files used when building this submodule, including all
## headers.

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

## Installation information.

libSoQtDevicesincdir = $(includedir)/Inventor/Qt/devices

libSoQtDevicesinc_HEADERS = \
	$(top_srcdir)/src/Inventor/Qt/devices/SoQtDevice.h \
	$(top_srcdir)/src/Inventor/Qt/devices/SoQtInputFocus.h \
	$(top_srcdir)/src/Inventor/Qt/devices/SoQtKeyboard.h \
	$(top_srcdir)/src/Inventor/Qt/devices/SoQtMouse.h \
	$(top_srcdir)/src/Inventor/Qt/devices/SoQtSpaceball.h


## FIXME: this is a temporary workaround for a bug in Automake. The
## bug is fixed in the latest Automake CVS, but not in any "official"
## release (?). Last checked with Automake 1.4a. 19990912 mortene.

install-libSoQtDevicesincHEADERS: $(libSoQtDevicesinc_HEADERS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(libSoQtDevicesincdir)
	@list='$(libSoQtDevicesinc_HEADERS)'; for p in $$list; do \
	  if test -f "$$p"; then d= ; else d="$(srcdir)/"; fi; \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " $(INSTALL_DATA) $$d$$p $(DESTDIR)$(libSoQtDevicesincdir)/$$f"; \
	  $(INSTALL_DATA) $$d$$p $(DESTDIR)$(libSoQtDevicesincdir)/$$f; \
	done

uninstall-libSoQtDevicesincHEADERS:
	@$(NORMAL_UNINSTALL)
	@list='$(libSoQtDevicesinc_HEADERS)'; for p in $$list; do \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " rm -f $(DESTDIR)$(libSoQtDevicesincdir)/$$f"; \
	  rm -f $(DESTDIR)$(libSoQtDevicesincdir)/$$f; \
	done

