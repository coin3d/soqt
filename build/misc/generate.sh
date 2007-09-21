#! /bin/sh
#
# This script generates the Visual Studio 6 build files for Windows.
#
# 20041214 larsa

project=soqt1

rm -f ${project}.dsp ${project}.dsw ${project}.vcproj ${project}.sln \
      ${project}_install.dsp ${project}_install.dsw \
      ${project}_install.vcproj ${project}_install.sln \
      ${project}_uninstall.dsp ${project}_uninstall.dsw \
      ${project}_uninstall.vcproj ${project}_uninstall.sln \
      install-headers.bat uninstall-headers.bat

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

sed \
  -e "s/$build/./g" \
  -e "s/$build_pwd//g" \
  -e "s/$source/..\\\\../g" \
  -e "s/$source_pwd/..\\\\../g" \
  -e 's/COIN_DLL/COIN_NOT_DLL/g' \
  -e '/_MAKE_DLL/ { s/COIN_NOT_DLL/COIN_DLL/g; }' \
  -e 's/$/\r/g' \
  <${project}.dsp >new.dsp

mv new.dsp ${project}.dsp

sed \
  -e "s/$build/./g" \
  -e "s/$build_pwd//g" \
  -e "s/$source/..\\\\../g" \
  -e "s/$source_pwd/..\\\\../g" \
  -e 's/$/\r/g' \
  <install-headers.bat >new.bat

mv new.bat ../misc/install-headers.bat

sed \
  -e "s/$build/./g" \
  -e "s/$build_pwd//g" \
  -e "s/$source/..\\\\../g" \
  -e "s/$source_pwd/..\\\\../g" \
  -e 's/$/\r/g' \
  <uninstall-headers.bat >new.bat

mv new.bat ../misc/uninstall-headers.bat

echo "Done."
echo "Modify so the static configurations are built with COIN_NOT_DLL"
echo "Then make sure there are no absolute paths in the project files"
grep -i c: ${project}.dsp ${project}.dsw

find . -name "moc_*" | xargs rm

# How can I avoid the modal upgrade prompt-dialog for MSVC7.1 here???
# devenv /command "File.OpenProject $build\\${project}.dsp"

