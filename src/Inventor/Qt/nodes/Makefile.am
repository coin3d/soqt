############################################################################
## SoQt/src/Inventor/Qt/nodes/Makefile.am

include ../common/Makefile.common

if BUILD_WITH_MSVC
noinst_LIBRARIES = nodes.lst
else
noinst_LTLIBRARIES = libSoGuiNodes.la
endif

DEFAULT_INCLUDES = -I$(top_builddir)/src -I$(top_srcdir)/src
LIBS =

BUILT_SOURCES = \
	$(SoGuiAllBuiltFiles)

CLEANFILES = \
	$(SoGui_src_Inventor_Gui_nodes_BuiltMetaFiles)

DISTCLEANFILES = \
	$(SoGui_src_Inventor_Gui_nodes_BuiltFiles) \
	$(SoGui_src_Inventor_Gui_nodes_BuiltMetaFiles)

############################################################################

# libSoGuiNodes_la_SOURCES =

RegularSources =
BuiltSources = \
	$(SoGui_src_Inventor_Gui_nodes_BuiltFiles)
LinkHackSources = \
	all-nodes-cpp.cpp


if HACKING_COMPACT_BUILD
BuildSources = $(LinkHackSources)
NoDistSources =
ExtraSources = $(RegularSources)
else
BuildSources = $(RegularSources)
NoDistSources = $(BuiltSources)
ExtraSources = $(LinkHackSources)
endif


libSoGuiNodes_la_SOURCES = \
	$(BuildSources)

nodist_libSoGuiNodes_la_SOURCES = \
	$(NoDistSources)

nodes_lst_SOURCES = \
	$(BuildSources)

nodist_nodes_lst_SOURCES = \
	$(NoDistSources)

nodes.lst: Makefile $(nodes_lst_OBJECTS)
	@echo "Linking $@..."; \
	rm -f $@; \
	for i in $(nodes_lst_OBJECTS); do echo $$i >>$@; done

############################################################################
## Header file installation information.

if MAC_FRAMEWORK
SoGuiNodesincdir = $(MAC_FRAMEWORK_PREFIX)/$(MAC_FRAMEWORK_NAME).framework/Versions/$(MAC_FRAMEWORK_VERSION)/Headers/nodes
else
SoGuiNodesincdir = $(includedir)/Inventor/@Gui@/nodes
endif

SoGuiNodesinc_HEADERS =
nodist_SoGuiNodesinc_HEADERS = \
	SoGuiColorEditor.h \
	SoGuiMaterialEditor.h

install-SoQtNodesincHEADERS: $(SoQtNodesinc_HEADERS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(SoQtNodesincdir)
	@list='$(SoQtNodesinc_HEADERS)'; for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  src="$$d$$p"; dst="$(DESTDIR)$(SoQtNodesincdir)/$$f"; \
	  if cmp -s "$$src" "$$dst"; then :; else \
	    echo " $(INSTALL_HEADER) $$src $$dst"; \
	    $(INSTALL_HEADER) "$$src" "$$dst" || exit 1; \
	  fi; \
	done

install-nodist_SoQtNodesincHEADERS: $(nodist_SoQtNodesinc_HEADERS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(SoQtNodesincdir)
	@list='$(nodist_SoQtNodesinc_HEADERS)'; for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  src="$$d$$p"; dst="$(DESTDIR)$(SoQtNodesincdir)/$$f"; \
	  if cmp -s "$$src" "$$dst"; then :; else \
	    echo " $(INSTALL_HEADER) $$src $$dst"; \
	    $(INSTALL_HEADER) "$$src" "$$dst" || exit 1; \
	  fi; \
	done

# EOF ######################################################################
