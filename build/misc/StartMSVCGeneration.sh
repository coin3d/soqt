cd $(dirname $0)/../..

SolutionName=soqt1

if [ -z "${COINDIR}" ]
then
  echo COINDIR must be set
  exit 1
fi

if [ -z "${QTDIR}" ]
then
  echo QTDIR must be set
  exit 1
fi

build/general/generate-all.sh ${SolutionName} 7 9
