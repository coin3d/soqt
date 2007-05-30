@echo off

REM **********************************************************************
REM * Create all the directories for the installed files

pushd %COINDIR%

if exist bin\*.* goto binexists
echo mkdir %COINDIR%\bin
mkdir bin
:binexists
if exist data\*.* goto dataexists
echo mkdir %COINDIR%\data
mkdir data
:dataexists
chdir data
if exist draggerDefaults\*.* goto draggerdefaultsexists
echo mkdir %COINDIR%\data\draggerDefaults
mkdir draggerDefaults
:draggerdefaultsexists
chdir ..
if exist lib\*.* goto libexists
echo mkdir %COINDIR%\lib
mkdir lib
:libexists
if exist include\*.* goto includeexists
echo mkdir %COINDIR%\include
mkdir include
:includeexists
chdir include
if exist Inventor\*.* goto inventorexists
echo mkdir %COINDIR%\include\Inventor
mkdir Inventor
:inventorexists
chdir Inventor
if exist Qt\*.* goto qtexists
echo mkdir %COINDIR%\include\Inventor\Qt
mkdir Qt
:qtexists
chdir Qt
if exist common\*.* goto qtcommonexists
echo mkdir %COINDIR%\include\Inventor\Qt\common
mkdir common
:qtcommonexists
if exist devices\*.* goto qtdevicesexists
echo mkdir %COINDIR%\include\Inventor\Qt\devices
mkdir devices
:qtdevicesexists
if exist editors\*.* goto qteditorsexists
echo mkdir %COINDIR%\include\Inventor\Qt\editors
mkdir editors
:qteditorsexists
if exist engines\*.* goto qtenginesexists
echo mkdir %COINDIR%\include\Inventor\Qt\engines
mkdir engines
:qtenginesexists
if exist nodes\*.* goto qtnodesexists
echo mkdir %COINDIR%\include\Inventor\Qt\nodes
mkdir nodes
:qtnodesexists
if exist viewers\*.* goto qtviewersexists
echo mkdir %COINDIR%\include\Inventor\Qt\viewers
mkdir viewers
:qtviewersexists
if exist widgets\*.* goto qtwidgetsexists
echo mkdir %COINDIR%\include\Inventor\Qt\widgets
mkdir widgets
:qtwidgetsexists

popd
