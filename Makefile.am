## Process this file with automake to generate Makefile.in.

if BUILD_EXAMPLES
EXAMPLEDIR = examples
else
EXAMPLEDIR = 
endif

SUBDIRS = src/Inventor/Qt $(EXAMPLEDIR)


bin_SCRIPTS = soqt-config

BUILT_SOURCES = soqt-config

soqt-config: soqt-config.in
