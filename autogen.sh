#!/bin/sh

# Author: Morten Eriksen, <mortene@sim.no>. Loosely based on Ralph
# Levien's script for Gnome.

DIE=0

PROJECT=SoQt
MACRODIR=conf-macros
SUBPROJECTS="$MACRODIR src/Inventor/Qt/common"

echo "Checking the installed configuration tools..."

# FIXME: check for minimum version number? 19990822 mortene.
(autoconf --version) < /dev/null > /dev/null 2>&1 || {
        echo
        echo "You must have autoconf installed to generate"
	echo "configure information and Makefiles for $PROJECT."
        echo "Get ftp://ftp.gnu.org/pub/gnu/autoconf-*.tar.gz"
        DIE=1
}

# FIXME: check for minimum version number? 19990822 mortene.
(libtool --version) < /dev/null > /dev/null 2>&1 || {
        echo
        echo "You must have libtool installed to generate"
	echo "configure information and Makefiles for $PROJECT."
        echo "Get ftp://ftp.gnu.org/pub/gnu/libtool-*.tar.gz"
        DIE=1
}

# FIXME: check for minimum version number? 19990822 mortene.
(automake --version) < /dev/null > /dev/null 2>&1 || {
        echo
        echo "You must have automake installed to generate"
	echo "configure information and Makefiles for $PROJECT."
        echo "Get ftp://ftp.gnu.org/pub/gnu/automake-*.tar.gz"
        DIE=1
}

for project in $SUBPROJECTS; do
  test -d $project || {
    echo
    echo "The CVS sub-project '$project' was not found."
    echo "It was probably added after you initially checked out $PROJECT."
    echo "Do a fresh 'cvs checkout' to correct this problem - the $PROJECT build system"
    echo "will probably not work properly otherwise.  For a fresh 'cvs checkout',"
    echo "run 'cvs -d :pserver:cvs@cvs.sim.no:/export/cvsroot co -P $PROJECT'."
    echo
  }
done

if test "$DIE" -eq 1; then
        exit 1
fi


echo "Running aclocal (generating aclocal.m4)..."
aclocal -I $MACRODIR

echo "Running autoheader (generating config.h.in)..."
autoheader

echo "Running automake (generating the Makefile.in files)..."
echo "(NB: if you're compiling without g++, you probably need to"
echo "manually run automake with the --include-deps argument to"
echo "avoid setting up dependency tracking. 19991006 mortene.)"
automake

echo "Running autoconf (generating ./configure and the Makefile files)..."
echo "[ignore the \"directory should not contain '/'\" warning]"
autoconf

echo "Done: Now run './configure' and 'make install' to build $PROJECT."

