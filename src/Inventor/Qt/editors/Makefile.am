############################################################################
## SoQt/src/Inventor/Qt/editors/Makefile.am

include ../common/Makefile.common

if BUILD_WITH_MSVC
noinst_LIBRARIES = editors.lst
else
noinst_LTLIBRARIES = libSoQtEditors.la
endif

DEFAULT_INCLUDES = -I$(top_builddir)/src -I$(top_srcdir)/src
LIBS =

BUILT_SOURCES = \
	$(SoGuiAllBuiltFiles)

CLEANFILES = \
	$(SoGui_src_Inventor_Gui_editors_BuiltMetaFiles)

DISTCLEANFILES = \
	$(SoGui_src_Inventor_Gui_editors_BuiltFiles) \
	$(SoGui_src_Inventor_Gui_editors_BuiltMetaFiles)

############################################################################

RegularSources =

BuiltSources = \
	$(SoGui_src_Inventor_Gui_editors_BuiltFiles) \
	$(SoGui_src_Inventor_Gui_editors_BuiltMetaFiles)

LinkHackSources = \
	all-editors-cpp.cpp

if HACKING_COMPACT_BUILD
BuildSources = $(LinkHackSources)
NoDistSources =
ExtraSources = $(RegularSources)
else
BuildSources = $(RegularSources)
NoDistSources = $(BuiltSources)
ExtraSources = $(LinkHackSources)
endif

libSoQtEditors_la_SOURCES = \
	$(BuildSources)

nodist_libSoQtEditors_la_SOURCES = \
	$(NoDistSources)

############################################################################

editors_lst_SOURCES = \
	$(BuildSources)

nodist_editors_lst_SOURCES = \
	$(NoDistSources)

editors.lst: Makefile $(editors_lst_OBJECTS)
	@echo "Linking $@..."; \
	rm -f $@; \
	for i in $(editors_lst_OBJECTS); do echo $$i >>$@; done

############################################################################
# header installation

if MAC_FRAMEWORK
SoQtEditorsincdir = $(MAC_FRAMEWORK_PREFIX)/$(MAC_FRAMEWORK_NAME).framework/Versions/$(MAC_FRAMEWORK_VERSION)/Headers/editors
else
SoQtEditorsincdir = $(includedir)/Inventor/@Gui@/editors
endif
SoQtEditorsinc_HEADERS =

nodist_SoQtEditorsinc_HEADERS = \
	So@Gui@ColorEditor.h \
	So@Gui@MaterialEditor.h

install-SoQtEditorsincHEADERS: $(SoQtEditorsinc_HEADERS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(SoQtEditorsincdir)
	@list='$(SoQtEditorsinc_HEADERS)'; \
	for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  src="$$d$$p"; dst="$(DESTDIR)$(SoQtEditorsincdir)/$$f"; \
	  if cmp -s "$$src" "$$dst"; then :; else \
	    echo " $(INSTALL_HEADER) $$src $$dst"; \
	    $(INSTALL_HEADER) "$$src" "$$dst" || exit 1; \
	  fi; \
	done

install-nodist_SoQtEditorsincHEADERS: $(nodist_SoQtEditorsinc_HEADERS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(SoQtEditorsincdir)
	@list='$(nodist_SoQtEditorsinc_HEADERS)'; for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  src="$$d$$p"; dst="$(DESTDIR)$(SoQtEditorsincdir)/$$f"; \
	  if cmp -s "$$src" "$$dst"; then :; else \
	    echo " $(INSTALL_HEADER) $$src $$dst"; \
	    $(INSTALL_HEADER) "$$src" "$$dst" || exit 1; \
	  fi; \
	done

# EOF ######################################################################
