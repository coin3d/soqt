############################################################################
# Usage:
#   SIM_AC_HAVE_SOQT_IFELSE( IF-FOUND, IF-NOT-FOUND )
#
# Description:
#   This macro locates the SoQt development system.  If it is found,
#   the set of variables listed below are set up as described and made
#   available to the configure script.
#
#   The $sim_ac_soqt_desired variable can be set to false externally to
#   make SoQt default to be excluded.
#
# Autoconf Variables:
# > $sim_ac_soqt_desired     true | false (defaults to true)
# < $sim_ac_soqt_avail       true | false
# < $sim_ac_soqt_cppflags    (extra flags the preprocessor needs)
# < $sim_ac_soqt_ldflags     (extra flags the linker needs)
# < $sim_ac_soqt_libs        (link library flags the linker needs)
# < $sim_ac_soqt_datadir     (location of SoQt data files)
# < $sim_ac_soqt_includedir  (location of SoQt headers)
# < $sim_ac_soqt_version     (the libSoQt version)
#
# Authors:
#   Lars J. Aas, <larsa@sim.no>
#   Morten Eriksen, <mortene@sim.no>
#
# TODO:
#

AC_DEFUN([SIM_AC_HAVE_SOQT_IFELSE], [
AC_PREREQ([2.14a])

# official variables
sim_ac_soqt_avail=false
sim_ac_soqt_cppflags=
sim_ac_soqt_ldflags=
sim_ac_soqt_libs=
sim_ac_soqt_datadir=
sim_ac_soqt_includedir=
sim_ac_soqt_version=

# internal variables
: ${sim_ac_soqt_desired=true}
sim_ac_soqt_extrapath=

AC_ARG_WITH([soqt], AC_HELP_STRING([--without-soqt], [disable use of SoQt]))
AC_ARG_WITH([soqt], AC_HELP_STRING([--with-soqt], [enable use of SoQt]))
AC_ARG_WITH([soqt],
  AC_HELP_STRING([--with-soqt=DIR], [give prefix location of SoQt]),
  [ case $withval in
    no)  sim_ac_soqt_desired=false ;;
    yes) sim_ac_soqt_desired=true ;;
    *)   sim_ac_soqt_desired=true
         sim_ac_soqt_extrapath=$withval ;;
    esac],
  [])

if $sim_ac_soqt_desired; then
  sim_ac_path=$PATH
  test -z "$sim_ac_soqt_extrapath" ||   ## search in --with-soqt path
    sim_ac_path=$sim_ac_soqt_extrapath/bin:$sim_ac_path
  test x"$prefix" = xNONE ||          ## search in --prefix path
    sim_ac_path=$sim_ac_path:$prefix/bin

  AC_PATH_PROG(sim_ac_soqt_configcmd, soqt-config, false, $sim_ac_path)

  if test "X$sim_ac_soqt_configcmd" = "Xfalse"; then :; else
    test -n "$CONFIG" &&
      $sim_ac_soqt_configcmd --alternate=$CONFIG >/dev/null 2>/dev/null &&
      sim_ac_soqt_configcmd="$sim_ac_soqt_configcmd --alternate=$CONFIG"
  fi

  if $sim_ac_soqt_configcmd; then
    sim_ac_soqt_cppflags=`$sim_ac_soqt_configcmd --cppflags`
    sim_ac_soqt_ldflags=`$sim_ac_soqt_configcmd --ldflags`
    sim_ac_soqt_libs=`$sim_ac_soqt_configcmd --libs`
    sim_ac_soqt_datadir=`$sim_ac_soqt_configcmd --datadir`
    sim_ac_soqt_includedir=`$sim_ac_soqt_configcmd --includedir`
    sim_ac_soqt_version=`$sim_ac_soqt_configcmd --version`
    AC_CACHE_CHECK(
      [whether libSoQt is available],
      sim_cv_soqt_avail,
      [sim_ac_save_cppflags=$CPPFLAGS
      sim_ac_save_ldflags=$LDFLAGS
      sim_ac_save_libs=$LIBS
      CPPFLAGS="$CPPFLAGS $sim_ac_soqt_cppflags"
      LDFLAGS="$LDFLAGS $sim_ac_soqt_ldflags"
      LIBS="$sim_ac_soqt_libs $LIBS"
      AC_LANG_PUSH(C++)
      AC_TRY_LINK(
        [#include <Inventor/Qt/SoQt.h>],
        [(void)SoQt::init((const char *)0L);],
        [sim_cv_soqt_avail=true],
        [sim_cv_soqt_avail=false])
      AC_LANG_POP
      CPPFLAGS=$sim_ac_save_cppflags
      LDFLAGS=$sim_ac_save_ldflags
      LIBS=$sim_ac_save_libs
    ])
    sim_ac_soqt_avail=$sim_cv_soqt_avail
  else
    locations=`IFS=:; for p in $sim_ac_path; do echo " -> $p/soqt-config"; done`
    AC_MSG_WARN([cannot find 'soqt-config' at any of these locations:
$locations])
  fi
fi

if $sim_ac_soqt_avail; then
  ifelse([$1], , :, [$1])
else
  ifelse([$2], , :, [$2])
fi
]) # SIM_AC_HAVE_SOQT_IFELSE()

