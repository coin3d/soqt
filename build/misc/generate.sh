#! /bin/sh
#
# This script generates the Visual Studio 6 build files for Windows.
#
# 20041214 larsa

if test x"$COINDIR" = x""; then
  echo >&2 "error: you must have the environment variable COINDIR set."
  exit 1
fi

if test x"$QTDIR" = x""; then
  echo >&2 "error: you must have the environment variable QTDIR set."
  exit 1
fi

project=soqt1

function cleansolution() {
  name=$1;
  rm -f ${name}.dsw ${name}.sln;
}

function cleanproject() {
  name=$1;
  rm -f ${name}.dsp ${name}.vcproj;
}

function escape () {
  echo $1 | sed -e 's/\\/\\\\/g'
}

proper=true;

cleansolution ${project}
cleanproject ${project}
cleanproject ${project}_install
cleanproject ${project}_uninstall
cleanproject ${project}_docs

rm -f install-headers.bat uninstall-headers.bat

build_pwd=`pwd`
build="`cygpath -w $build_pwd | sed -e 's/\\\\/\\\\\\\\/g'`"
build_pwd="`pwd | sed -e 's/\\//\\\\\\\\/g'`\\\\"

source_pwd=`cd ../..; pwd`
source="`cygpath -w $source_pwd | sed -e 's/\\\\/\\\\\\\\/g'`"
source_pwd="`(cd ../..; pwd) | sed -e 's/\\//\\\\\\\\/g'`"

../../configure --with-msvcrt=mtd --with-suffix=d \
  --enable-debug --enable-symbols || exit 1
mv src/config.h src/config-debug.h

../../configure --enable-msvcdsp --with-msvcrt=mt \
  --disable-debug --disable-symbols --enable-optimization || exit 1
mv src/config.h src/config-release.h

cp ../misc/config-wrapper.h src/config.h

make || exit 1

ECOINDIR=$(escape ${COINDIR})
EQTDIR=$(escape ${QTDIR})

sed \
  -e "s/$build/./g" \
  -e "s/$build_pwd//g" \
  -e "s/$source/..\\\\../g" \
  -e "s/$source_pwd/..\\\\../g" \
  -e "s/${ECOINDIR}/\$(COINDIR)/gi" \
  -e "s/${EQTDIR}/\$(QTDIR)/gi" \
  -e 's/COIN_DLL/COIN_NOT_DLL/g' \
  -e '/_MAKE_DLL/ { s/COIN_NOT_DLL/COIN_DLL/g; }' \
  -e '/^# ADD .*LINK32.*\/debug/ { s/COINDIR)\\lib\\coin3.lib/COINDIR)\\lib\\coin3d.lib/g; }' \
  -e '/^# ADD .*LINK32.*\/debug/ { s/QTDIR)\\lib\\Qt\([^ ]*\)4.lib/QTDIR)\\lib\\Qt\1d4.lib/g; }' \
  -e 's/$/\r/g' \
  <${project}.dsp >new.dsp

mv new.dsp ${project}.dsp

sed \
  -e "s/$build/./g" \
  -e "s/$build_pwd//g" \
  -e "s/$source/..\\\\../g" \
  -e "s/$source_pwd/..\\\\../g" \
  -e "s/${ECOINDIR}/\$(COINDIR)/gi" \
  -e "s/${EQTDIR}/\$(QTDIR)/gi" \
  -e 's/$/\r/g' \
  <install-headers.bat >new.bat

mv new.bat ../misc/install-headers.bat

sed \
  -e "s/$build/./g" \
  -e "s/$build_pwd//g" \
  -e "s/$source/..\\\\../g" \
  -e "s/$source_pwd/..\\\\../g" \
  -e "s/${ECOINDIR}/\$(COINDIR)/gi" \
  -e "s/${EQTDIR}/\$(QTDIR)/gi" \
  -e 's/$/\r/g' \
  <uninstall-headers.bat >new.bat

mv new.bat ../misc/uninstall-headers.bat

echo "Done."
echo ""
echo "* Make sure there are no absolute paths in the project files"
grep -i c: ${project}.dsp ${project}.dsw
echo "* Make sure 'Public Headers' group is preceded by 2s 'End Group' lines."
echo "* Fix up DLL library dependencies, so Debug Builds use debug dependencies."
echo "* Upgrade project files by running devenv soqt1.dsw"
echo "* Run ./fixvcproj.sh if you are using msvc7."

find . -name "moc_*" | xargs rm

# How can I avoid the modal upgrade prompt-dialog for MSVC7.1 here???
# devenv /command "File.OpenProject $build\\${project}.dsp"
