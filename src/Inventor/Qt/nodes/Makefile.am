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

nodist_libSoGuiNodes_la_SOURCES = \
	$(SoGui_src_Inventor_Gui_nodes_BuiltFiles)

nodist_nodes_lst_SOURCES = \
	$(SoGui_src_Inventor_Gui_nodes_BuiltFiles)

nodes.lst: Makefile $(nodes_lst_OBJECTS)
	@echo "Linking $@..."; \
	rm -f $@; \
	for i in $(nodes_lst_OBJECTS); do echo $$i >>$@; done

############################################################################
## Header file installation information.

# These nodes are kept internal for now.  We know people will ask for them
# to be made public, but until then we'll let them mature.  Besides, the
# nodes can be used indirectly already through getTypeByName(),
# createInstance(), getFieldByName() and such indirect methods, which will
# allow us to change the nodes without any consequences for others.

# SoGuiNodesincdir = $(includedir)/Inventor/@Gui@/nodes
# 
# SoGuiNodesinc_HEADERS = \
# 	SoGuiNode.h \
# 	SoGuiSlider1.h

# EOF ######################################################################
