#!/bin/sh
############################################################################

GUI=Qt
module=So$GUI
cvs2cl=$HOME/store/cvs/cvs2cl/cvs2cl.pl
moduledir=$HOME/code/coin/src/$module
headerfile=/tmp/$module.header

cd $moduledir

############################################################################
cat > $headerfile <<ENDOFHEADER
ChangeLog
=========

This is the ChangeLog file for the $module module.  This file is automatically
generated every night.  Entries are in reversed chronological order.  Check
also out the following ChangeLog files:

  ./conf-macros/ChangeLog
  ./src/Inventor/$GUI/common/ChangeLog
  ./examples/components/ChangeLog

See http://www.red-bean.com/~kfogel/cvs2cl.shtml for information about the
cvs2cl script used to generate this file.

============================================================================

ENDOFHEADER
############################################################################

cvs update -dP

cvs log | $cvs2cl --stdin --header $headerfile --separate-header --prune \
  --ignore 'ChangeLog$' \
  --ignore '(Makefile\.in|configure|aclocal\.m4|config\.sub|config\.guess)$' \
  --ignore '(ltconfig|ltmain\.sh|missing|mkinstalldirs|stamp-h.*|install-sh)$' \
  --ignore 'config\.h\.in$' \
  --ignore 'conf-macros' \
  --ignore "src/Inventor/$GUI/common" \
  --ignore 'examples/components' 

rm ChangeLog.bak $headerfile

cvs commit -m "Automatic ChangeLog generation" ChangeLog

