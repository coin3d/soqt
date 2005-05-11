#! /bin/sh
#
# This script generates the Visual Studio 6 build files for Windows.
#
# 20041214 larsa

rm -f soqt1.dsp soqt1.dsw installsoqtheaders.bat

../../configure --enable-msvcdsp --with-msvcrt=mt || exit 1
make || exit 1

build_pwd=`pwd`
build="`cygpath -w $build_pwd | sed -e 's/\\\\/\\\\\\\\/g'`"
build_pwd="`pwd | sed -e 's/\\//\\\\\\\\/g'`\\\\"

source_pwd=`cd ../..; pwd`
source="`cygpath -w $source_pwd | sed -e 's/\\\\/\\\\\\\\/g'`"
source_pwd="`(cd ../..; pwd) | sed -e 's/\\//\\\\\\\\/g'`"

sed \
  -e "s/$build/./g" \
  -e "s/$build_pwd//g" \
  -e "s/$source/..\\\\../g" \
  -e "s/$source_pwd/..\\\\../g" \
  -e 's/$/\r/g' \
  <soqt1.dsp >new.dsp

mv new.dsp soqt1.dsp

sed \
  -e "s/$build/./g" \
  -e "s/$build_pwd//g" \
  -e "s/$source/..\\\\../g" \
  -e "s/$source_pwd/..\\\\../g" \
  -e 's/$/\r/g' \
  <installsoqtheaders.bat >new.bat

mv new.bat installsoqtheaders.bat

echo "Run 'devenv soqt1.dsw', save all solution files, and then run './fixproj.sh'"

