############################################################################
## SoQt/src/Inventor/Qt/engines/Makefile.am

include ../common/Makefile.common

if BUILD_WITH_MSVC
noinst_LIBRARIES = engines.lst
else
noinst_LTLIBRARIES = libSoGuiEngines.la
endif

DEFAULT_INCLUDES = -I$(top_builddir)/src -I$(top_srcdir)/src
LIBS =

BUILT_SOURCES = \
	$(SoGuiAllBuiltFiles)

CLEANFILES = \
	$(SoGui_src_Inventor_Gui_engines_BuiltMetaFiles)

DISTCLEANFILES = \
	$(SoGui_src_Inventor_Gui_engines_BuiltFiles) \
	$(SoGui_src_Inventor_Gui_engines_BuiltMetaFiles)

############################################################################

# libSoGuiEngines_la_SOURCES =

nodist_libSoGuiEngines_la_SOURCES = \
	$(SoGui_src_Inventor_Gui_engines_BuiltFiles)

nodist_engines_lst_SOURCES = \
	$(SoGui_src_Inventor_Gui_engines_BuiltFiles)

engines.lst: Makefile $(engines_lst_OBJECTS)
	@echo "Linking $@..."; \
	rm -f $@; \
	for i in $(engines_lst_OBJECTS); do echo $$i >>$@; done

############################################################################
## Header file installation information.

if MAC_FRAMEWORK
SoGuiEnginesincdir = $(MAC_FRAMEWORK_PREFIX)/$(MAC_FRAMEWORK_NAME).framework/Versions/$(MAC_FRAMEWORK_VERSION)/Headers/engines
else
SoGuiEnginesincdir = $(includedir)/Inventor/@Gui@/engines
endif

SoGuiEnginesinc_HEADERS =
nodist_SoGuiEnginesinc_HEADERS =

install-SoQtEnginesincHEADERS: $(SoQtEnginesinc_HEADERS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(SoQtEnginesincdir)
	@list='$(SoQtEnginesinc_HEADERS)'; for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  src="$$d$$p"; dst="$(DESTDIR)$(SoQtEnginesincdir)/$$f"; \
	  if cmp -s "$$src" "$$dst"; then :; else \
	    echo " $(INSTALL_HEADER) $$src $$dst"; \
	    $(INSTALL_HEADER) "$$src" "$$dst"; \
	  fi; \
	done

install-nodist_SoQtEnginesincHEADERS: $(nodist_SoQtEnginesinc_HEADERS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(SoQtEnginesincdir)
	@list='$(nodist_SoQtEnginesinc_HEADERS)'; for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  src="$$d$$p"; dst="$(DESTDIR)$(SoQtEnginesincdir)/$$f"; \
	  if cmp -s "$$src" "$$dst"; then :; else \
	    echo " $(INSTALL_HEADER) $$src $$dst"; \
	    $(INSTALL_HEADER) "$$src" "$$dst"; \
	  fi; \
	done

# EOF ######################################################################
