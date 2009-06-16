# Microsoft Developer Studio Project File - Name="soqt1" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=soqt1 - Win32 DLL (Release)
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE
!MESSAGE NMAKE /f "soqt1.mak".
!MESSAGE
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE
!MESSAGE NMAKE /f "soqt1.mak" CFG="soqt1 - Win32 DLL (Debug)"
!MESSAGE
!MESSAGE Possible choices for configuration are:
!MESSAGE
!MESSAGE "soqt1 - Win32 LIB (Release)" (based on "Win32 (x86) Static Library")
!MESSAGE "soqt1 - Win32 LIB (Debug)" (based on "Win32 (x86) Static Library")
!MESSAGE "soqt1 - Win32 DLL (Release)" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "soqt1 - Win32 DLL (Debug)" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "StaticRelease"
# PROP BASE Intermediate_Dir "StaticRelease"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "StaticRelease"
# PROP Intermediate_Dir "StaticRelease"
# PROP Target_Dir ""
MTL=midl.exe
CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /Ox /Gy /Zi /I "src" /I "data" /I "..\..\src" /I "$(COINDIR)\include" /I "$(COINDIR)\include\Inventor\annex" /I "$(QTDIR)\include" /I "$(QTDIR)\include\Qt" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_LIB" /D SOQT_DEBUG=0  /D "HAVE_CONFIG_H" /D "COIN_NOT_DLL" /D "SOQT_INTERNAL" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Ox /Gy /Zi /I "src" /I "data" /I "..\..\src" /I "$(COINDIR)\include" /I "$(COINDIR)\include\Inventor\annex" /I "$(QTDIR)\include" /I "$(QTDIR)\include\Qt" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_LIB" /D SOQT_DEBUG=0  /D "HAVE_CONFIG_H" /D "COIN_NOT_DLL" /D "SOQT_INTERNAL" /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x414 /d "NDEBUG"
# ADD RSC /l 0x414 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /machine:I386 /out:"soqt1s.lib"
# ADD LIB32 /nologo /machine:I386 /out:"soqt1s.lib"

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "StaticDebug"
# PROP BASE Intermediate_Dir "StaticDebug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "StaticDebug"
# PROP Intermediate_Dir "StaticDebug"
# PROP Target_Dir ""
MTL=midl.exe
CPP=cl.exe
# ADD BASE CPP /nologo /MDd /W3 /GX /GZ /Od /Zi /I "src" /I "data" /I "..\..\src" /I "$(COINDIR)\include" /I "$(COINDIR)\include\Inventor\annex" /I "$(QTDIR)\include" /I "$(QTDIR)\include\Qt" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_LIB" /D SOQT_DEBUG=1  /D "HAVE_CONFIG_H" /D "COIN_NOT_DLL" /D "SOQT_INTERNAL" /FD /c
# ADD CPP /nologo /MDd /W3 /GX /GZ /Od /Zi /I "src" /I "data" /I "..\..\src" /I "$(COINDIR)\include" /I "$(COINDIR)\include\Inventor\annex" /I "$(QTDIR)\include" /I "$(QTDIR)\include\Qt" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_LIB" /D SOQT_DEBUG=1  /D "HAVE_CONFIG_H" /D "COIN_NOT_DLL" /D "SOQT_INTERNAL" /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x414 /d "_DEBUG"
# ADD RSC /l 0x414 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /machine:I386 /out:"soqt1sd.lib"
# ADD LIB32 /nologo /machine:I386 /out:"soqt1sd.lib"

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /Ox /Gy /Zi /I "src" /I "data" /I "..\..\src" /I "$(COINDIR)\include" /I "$(COINDIR)\include\Inventor\annex" /I "$(QTDIR)\include" /I "$(QTDIR)\include\Qt" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D SOQT_DEBUG=0 /D "HAVE_CONFIG_H" /D "SOQT_MAKE_DLL" /D "COIN_DLL" /D "SOQT_INTERNAL" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Ox /Gy /Zi /I "src" /I "data" /I "..\..\src" /I "$(COINDIR)\include" /I "$(COINDIR)\include\Inventor\annex" /I "$(QTDIR)\include" /I "$(QTDIR)\include\Qt" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D SOQT_DEBUG=0 /D "HAVE_CONFIG_H" /D "SOQT_MAKE_DLL" /D "COIN_DLL" /D "SOQT_INTERNAL" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
RCS=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 $(QTDIR)\lib\QtOpenGL4.lib $(QTDIR)\lib\QtGui4.lib $(QTDIR)\lib\QtCore4.lib $(COINDIR)\lib\coin3.lib opengl32.lib gdi32.lib winmm.lib user32.lib /nologo /dll /release /machine:I386 /pdbtype:sept
# ADD LINK32 $(QTDIR)\lib\QtOpenGL4.lib $(QTDIR)\lib\QtGui4.lib $(QTDIR)\lib\QtCore4.lib $(COINDIR)\lib\coin3.lib opengl32.lib gdi32.lib winmm.lib user32.lib /nologo /dll /release /machine:I386 /pdbtype:sept /out:"soqt1.dll" /opt:nowin98
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
CPP=cl.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /GZ /Zi /Od /I "src" /I "data" /I "..\..\src" /I "$(COINDIR)\include" /I "$(COINDIR)\include\Inventor\annex" /I "$(QTDIR)\include" /I "$(QTDIR)\include\Qt" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D SOQT_DEBUG=1 /D "HAVE_CONFIG_H" /D "SOQT_MAKE_DLL" /D "COIN_DLL" /D "SOQT_INTERNAL" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /GZ /Zi /Od /I "src" /I "data" /I "..\..\src" /I "$(COINDIR)\include" /I "$(COINDIR)\include\Inventor\annex" /I "$(QTDIR)\include" /I "$(QTDIR)\include\Qt" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D SOQT_DEBUG=1 /D "HAVE_CONFIG_H" /D "SOQT_MAKE_DLL" /D "COIN_DLL" /D "SOQT_INTERNAL" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
RCS=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 $(QTDIR)\lib\QtOpenGLd4.lib $(QTDIR)\lib\QtGuid4.lib $(QTDIR)\lib\QtCored4.lib $(COINDIR)\lib\coin3d.lib opengl32.lib gdi32.lib winmm.lib user32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 $(QTDIR)\lib\QtOpenGLd4.lib $(QTDIR)\lib\QtGuid4.lib $(QTDIR)\lib\QtCored4.lib $(COINDIR)\lib\coin3d.lib opengl32.lib gdi32.lib winmm.lib user32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept /out:"soqt1d.dll" /opt:nowin98

!ENDIF

# Begin Target

# Name "soqt1 - Win32 DLL (Release)"
# Name "soqt1 - Win32 DLL (Debug)"
# Name "soqt1 - Win32 LIB (Release)"
# Name "soqt1 - Win32 LIB (Debug)"
# Begin Group "Documents"
# PROP Default_Filter ";txt"
# Begin Source File

SOURCE=..\..\README
# End Source File
# Begin Source File

SOURCE=..\..\README.WIN32
# End Source File
# Begin Source File

SOURCE=..\..\NEWS
# End Source File
# Begin Source File

SOURCE=..\..\LICENSE.GPL
# End Source File
# Begin Source File

SOURCE=..\..\COPYING
# End Source File
# Begin Source File

SOURCE=..\..\ChangeLog
# End Source File
# End Group
# Begin Group "Template Files"
# PROP Default_Filter "in"
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\gl.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\gl.h.in

"src\Inventor\Qt\common\gl.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\gl.h.in:src\Inventor\Qt\common\gl.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\common\gl.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\gl.h.in:src\Inventor\Qt\common\gl.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\common\gl.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\gl.h.in:src\Inventor\Qt\common\gl.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\common\gl.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\gl.h.in:src\Inventor\Qt\common\gl.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\devices\SoGuiDeviceP.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\devices\SoGuiDeviceP.h.in

"src\Inventor\Qt\devices\SoGuiDeviceP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiDeviceP.h.in:src\Inventor\Qt\devices\SoGuiDeviceP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoGuiDeviceP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiDeviceP.h.in:src\Inventor\Qt\devices\SoGuiDeviceP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoGuiDeviceP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiDeviceP.h.in:src\Inventor\Qt\devices\SoGuiDeviceP.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoGuiDeviceP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiDeviceP.h.in:src\Inventor\Qt\devices\SoGuiDeviceP.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\devices\SoGuiInputFocusP.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\devices\SoGuiInputFocusP.h.in

"src\Inventor\Qt\devices\SoGuiInputFocusP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiInputFocusP.h.in:src\Inventor\Qt\devices\SoGuiInputFocusP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoGuiInputFocusP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiInputFocusP.h.in:src\Inventor\Qt\devices\SoGuiInputFocusP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoGuiInputFocusP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiInputFocusP.h.in:src\Inventor\Qt\devices\SoGuiInputFocusP.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoGuiInputFocusP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiInputFocusP.h.in:src\Inventor\Qt\devices\SoGuiInputFocusP.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\devices\SoGuiKeyboardP.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\devices\SoGuiKeyboardP.h.in

"src\Inventor\Qt\devices\SoGuiKeyboardP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiKeyboardP.h.in:src\Inventor\Qt\devices\SoGuiKeyboardP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoGuiKeyboardP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiKeyboardP.h.in:src\Inventor\Qt\devices\SoGuiKeyboardP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoGuiKeyboardP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiKeyboardP.h.in:src\Inventor\Qt\devices\SoGuiKeyboardP.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoGuiKeyboardP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiKeyboardP.h.in:src\Inventor\Qt\devices\SoGuiKeyboardP.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\devices\SoGuiMouseP.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\devices\SoGuiMouseP.h.in

"src\Inventor\Qt\devices\SoGuiMouseP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiMouseP.h.in:src\Inventor\Qt\devices\SoGuiMouseP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoGuiMouseP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiMouseP.h.in:src\Inventor\Qt\devices\SoGuiMouseP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoGuiMouseP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiMouseP.h.in:src\Inventor\Qt\devices\SoGuiMouseP.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoGuiMouseP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiMouseP.h.in:src\Inventor\Qt\devices\SoGuiMouseP.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\

"src\Inventor\Qt\devices\SoGuiSpaceballP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\:src\Inventor\Qt\devices\SoGuiSpaceballP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoGuiSpaceballP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\:src\Inventor\Qt\devices\SoGuiSpaceballP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoGuiSpaceballP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\:src\Inventor\Qt\devices\SoGuiSpaceballP.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoGuiSpaceballP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\:src\Inventor\Qt\devices\SoGuiSpaceballP.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\devices\SoGuiDevice.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\devices\SoGuiDevice.h.in

"src\Inventor\Qt\devices\SoQtDevice.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiDevice.h.in:src\Inventor\Qt\devices\SoQtDevice.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoQtDevice.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiDevice.h.in:src\Inventor\Qt\devices\SoQtDevice.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoQtDevice.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiDevice.h.in:src\Inventor\Qt\devices\SoQtDevice.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoQtDevice.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiDevice.h.in:src\Inventor\Qt\devices\SoQtDevice.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\devices\SoGuiDevice.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\devices\SoGuiDevice.cpp.in

"src\Inventor\Qt\devices\SoQtDeviceCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiDevice.cpp.in:src\Inventor\Qt\devices\SoQtDeviceCommon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoQtDeviceCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiDevice.cpp.in:src\Inventor\Qt\devices\SoQtDeviceCommon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoQtDeviceCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiDevice.cpp.in:src\Inventor\Qt\devices\SoQtDeviceCommon.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoQtDeviceCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiDevice.cpp.in:src\Inventor\Qt\devices\SoQtDeviceCommon.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\devices\SoGuiInputFocus.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\devices\SoGuiInputFocus.h.in

"src\Inventor\Qt\devices\SoQtInputFocus.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiInputFocus.h.in:src\Inventor\Qt\devices\SoQtInputFocus.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoQtInputFocus.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiInputFocus.h.in:src\Inventor\Qt\devices\SoQtInputFocus.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoQtInputFocus.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiInputFocus.h.in:src\Inventor\Qt\devices\SoQtInputFocus.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoQtInputFocus.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiInputFocus.h.in:src\Inventor\Qt\devices\SoQtInputFocus.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\devices\SoGuiInputFocus.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\devices\SoGuiInputFocus.cpp.in

"src\Inventor\Qt\devices\SoQtInputFocusCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiInputFocus.cpp.in:src\Inventor\Qt\devices\SoQtInputFocusCommon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoQtInputFocusCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiInputFocus.cpp.in:src\Inventor\Qt\devices\SoQtInputFocusCommon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoQtInputFocusCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiInputFocus.cpp.in:src\Inventor\Qt\devices\SoQtInputFocusCommon.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoQtInputFocusCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiInputFocus.cpp.in:src\Inventor\Qt\devices\SoQtInputFocusCommon.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\devices\SoGuiKeyboard.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\devices\SoGuiKeyboard.h.in

"src\Inventor\Qt\devices\SoQtKeyboard.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiKeyboard.h.in:src\Inventor\Qt\devices\SoQtKeyboard.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoQtKeyboard.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiKeyboard.h.in:src\Inventor\Qt\devices\SoQtKeyboard.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoQtKeyboard.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiKeyboard.h.in:src\Inventor\Qt\devices\SoQtKeyboard.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoQtKeyboard.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiKeyboard.h.in:src\Inventor\Qt\devices\SoQtKeyboard.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\devices\SoGuiKeyboard.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\devices\SoGuiKeyboard.cpp.in

"src\Inventor\Qt\devices\SoQtKeyboardCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiKeyboard.cpp.in:src\Inventor\Qt\devices\SoQtKeyboardCommon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoQtKeyboardCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiKeyboard.cpp.in:src\Inventor\Qt\devices\SoQtKeyboardCommon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoQtKeyboardCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiKeyboard.cpp.in:src\Inventor\Qt\devices\SoQtKeyboardCommon.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoQtKeyboardCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiKeyboard.cpp.in:src\Inventor\Qt\devices\SoQtKeyboardCommon.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\devices\SoGuiMouse.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\devices\SoGuiMouse.h.in

"src\Inventor\Qt\devices\SoQtMouse.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiMouse.h.in:src\Inventor\Qt\devices\SoQtMouse.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoQtMouse.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiMouse.h.in:src\Inventor\Qt\devices\SoQtMouse.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoQtMouse.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiMouse.h.in:src\Inventor\Qt\devices\SoQtMouse.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoQtMouse.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiMouse.h.in:src\Inventor\Qt\devices\SoQtMouse.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\devices\SoGuiMouse.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\devices\SoGuiMouse.cpp.in

"src\Inventor\Qt\devices\SoQtMouseCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiMouse.cpp.in:src\Inventor\Qt\devices\SoQtMouseCommon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoQtMouseCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiMouse.cpp.in:src\Inventor\Qt\devices\SoQtMouseCommon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoQtMouseCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiMouse.cpp.in:src\Inventor\Qt\devices\SoQtMouseCommon.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoQtMouseCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\devices\SoGuiMouse.cpp.in:src\Inventor\Qt\devices\SoQtMouseCommon.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\

"src\Inventor\Qt\devices\SoQtSpaceball.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\:src\Inventor\Qt\devices\SoQtSpaceball.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoQtSpaceball.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\:src\Inventor\Qt\devices\SoQtSpaceball.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoQtSpaceball.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\:src\Inventor\Qt\devices\SoQtSpaceball.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoQtSpaceball.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\:src\Inventor\Qt\devices\SoQtSpaceball.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\

"src\Inventor\Qt\devices\SoQtSpaceballCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\:src\Inventor\Qt\devices\SoQtSpaceballCommon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoQtSpaceballCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\:src\Inventor\Qt\devices\SoQtSpaceballCommon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoQtSpaceballCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\:src\Inventor\Qt\devices\SoQtSpaceballCommon.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\SoQtSpaceballCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\:src\Inventor\Qt\devices\SoQtSpaceballCommon.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\spwinput.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\spwinput.h.in

"src\Inventor\Qt\devices\spwinput.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\spwinput.h.in:src\Inventor\Qt\devices\spwinput.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\spwinput.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\spwinput.h.in:src\Inventor\Qt\devices\spwinput.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\spwinput.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\spwinput.h.in:src\Inventor\Qt\devices\spwinput.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\spwinput.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\spwinput.h.in:src\Inventor\Qt\devices\spwinput.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\spwinput_win32.c.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\spwinput_win32.c.in

"src\Inventor\Qt\devices\spwinput_win32.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\spwinput_win32.c.in:src\Inventor\Qt\devices\spwinput_win32.c

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\spwinput_win32.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\spwinput_win32.c.in:src\Inventor\Qt\devices\spwinput_win32.c

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\spwinput_win32.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\spwinput_win32.c.in:src\Inventor\Qt\devices\spwinput_win32.c

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\spwinput_win32.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\spwinput_win32.c.in:src\Inventor\Qt\devices\spwinput_win32.c

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\spwinput_win32.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\spwinput_win32.h.in

"src\Inventor\Qt\devices\spwinput_win32.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\spwinput_win32.h.in:src\Inventor\Qt\devices\spwinput_win32.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\spwinput_win32.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\spwinput_win32.h.in:src\Inventor\Qt\devices\spwinput_win32.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\spwinput_win32.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\spwinput_win32.h.in:src\Inventor\Qt\devices\spwinput_win32.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\spwinput_win32.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\spwinput_win32.h.in:src\Inventor\Qt\devices\spwinput_win32.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\spwinput_x11.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\spwinput_x11.cpp.in

"src\Inventor\Qt\devices\spwinput_x11.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\spwinput_x11.cpp.in:src\Inventor\Qt\devices\spwinput_x11.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\spwinput_x11.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\spwinput_x11.cpp.in:src\Inventor\Qt\devices\spwinput_x11.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\spwinput_x11.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\spwinput_x11.cpp.in:src\Inventor\Qt\devices\spwinput_x11.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\devices\spwinput_x11.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\spwinput_x11.cpp.in:src\Inventor\Qt\devices\spwinput_x11.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\editors\SoGuiColorEditor.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\editors\SoGuiColorEditor.cpp.in

"src\Inventor\Qt\editors\SoQtColorEditor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\editors\SoGuiColorEditor.cpp.in:src\Inventor\Qt\editors\SoQtColorEditor.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\editors\SoQtColorEditor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\editors\SoGuiColorEditor.cpp.in:src\Inventor\Qt\editors\SoQtColorEditor.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\editors\SoQtColorEditor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\editors\SoGuiColorEditor.cpp.in:src\Inventor\Qt\editors\SoQtColorEditor.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\editors\SoQtColorEditor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\editors\SoGuiColorEditor.cpp.in:src\Inventor\Qt\editors\SoQtColorEditor.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\editors\SoGuiColorEditor.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\editors\SoGuiColorEditor.h.in

"src\Inventor\Qt\editors\SoQtColorEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\editors\SoGuiColorEditor.h.in:src\Inventor\Qt\editors\SoQtColorEditor.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\editors\SoQtColorEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\editors\SoGuiColorEditor.h.in:src\Inventor\Qt\editors\SoQtColorEditor.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\editors\SoQtColorEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\editors\SoGuiColorEditor.h.in:src\Inventor\Qt\editors\SoQtColorEditor.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\editors\SoQtColorEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\editors\SoGuiColorEditor.h.in:src\Inventor\Qt\editors\SoQtColorEditor.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\editors\SoGuiMaterialEditor.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\editors\SoGuiMaterialEditor.cpp.in

"src\Inventor\Qt\editors\SoQtMaterialEditor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\editors\SoGuiMaterialEditor.cpp.in:src\Inventor\Qt\editors\SoQtMaterialEditor.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\editors\SoQtMaterialEditor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\editors\SoGuiMaterialEditor.cpp.in:src\Inventor\Qt\editors\SoQtMaterialEditor.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\editors\SoQtMaterialEditor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\editors\SoGuiMaterialEditor.cpp.in:src\Inventor\Qt\editors\SoQtMaterialEditor.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\editors\SoQtMaterialEditor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\editors\SoGuiMaterialEditor.cpp.in:src\Inventor\Qt\editors\SoQtMaterialEditor.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\editors\SoGuiMaterialEditor.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\editors\SoGuiMaterialEditor.h.in

"src\Inventor\Qt\editors\SoQtMaterialEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\editors\SoGuiMaterialEditor.h.in:src\Inventor\Qt\editors\SoQtMaterialEditor.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\editors\SoQtMaterialEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\editors\SoGuiMaterialEditor.h.in:src\Inventor\Qt\editors\SoQtMaterialEditor.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\editors\SoQtMaterialEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\editors\SoGuiMaterialEditor.h.in:src\Inventor\Qt\editors\SoQtMaterialEditor.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\editors\SoQtMaterialEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\editors\SoGuiMaterialEditor.h.in:src\Inventor\Qt\editors\SoQtMaterialEditor.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\engines\Engines.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\engines\Engines.cpp.in

"src\Inventor\Qt\engines\Engines.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\engines\Engines.cpp.in:src\Inventor\Qt\engines\Engines.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\engines\Engines.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\engines\Engines.cpp.in:src\Inventor\Qt\engines\Engines.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\engines\Engines.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\engines\Engines.cpp.in:src\Inventor\Qt\engines\Engines.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\engines\Engines.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\engines\Engines.cpp.in:src\Inventor\Qt\engines\Engines.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\engines\Format.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\engines\Format.cpp.in

"src\Inventor\Qt\engines\Format.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\engines\Format.cpp.in:src\Inventor\Qt\engines\Format.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\engines\Format.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\engines\Format.cpp.in:src\Inventor\Qt\engines\Format.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\engines\Format.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\engines\Format.cpp.in:src\Inventor\Qt\engines\Format.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\engines\Format.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\engines\Format.cpp.in:src\Inventor\Qt\engines\Format.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\engines\RadioGroup.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\engines\RadioGroup.cpp.in

"src\Inventor\Qt\engines\RadioGroup.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\engines\RadioGroup.cpp.in:src\Inventor\Qt\engines\RadioGroup.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\engines\RadioGroup.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\engines\RadioGroup.cpp.in:src\Inventor\Qt\engines\RadioGroup.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\engines\RadioGroup.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\engines\RadioGroup.cpp.in:src\Inventor\Qt\engines\RadioGroup.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\engines\RadioGroup.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\engines\RadioGroup.cpp.in:src\Inventor\Qt\engines\RadioGroup.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\engines\Engines.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\engines\Engines.h.in

"src\Inventor\Qt\engines\SoGuiEngines.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\engines\Engines.h.in:src\Inventor\Qt\engines\SoGuiEngines.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\engines\SoGuiEngines.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\engines\Engines.h.in:src\Inventor\Qt\engines\SoGuiEngines.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\engines\SoGuiEngines.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\engines\Engines.h.in:src\Inventor\Qt\engines\SoGuiEngines.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\engines\SoGuiEngines.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\engines\Engines.h.in:src\Inventor\Qt\engines\SoGuiEngines.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\engines\Format.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\engines\Format.h.in

"src\Inventor\Qt\engines\SoGuiFormat.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\engines\Format.h.in:src\Inventor\Qt\engines\SoGuiFormat.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\engines\SoGuiFormat.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\engines\Format.h.in:src\Inventor\Qt\engines\SoGuiFormat.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\engines\SoGuiFormat.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\engines\Format.h.in:src\Inventor\Qt\engines\SoGuiFormat.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\engines\SoGuiFormat.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\engines\Format.h.in:src\Inventor\Qt\engines\SoGuiFormat.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\engines\RadioGroup.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\engines\RadioGroup.h.in

"src\Inventor\Qt\engines\SoGuiRadioGroup.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\engines\RadioGroup.h.in:src\Inventor\Qt\engines\SoGuiRadioGroup.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\engines\SoGuiRadioGroup.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\engines\RadioGroup.h.in:src\Inventor\Qt\engines\SoGuiRadioGroup.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\engines\SoGuiRadioGroup.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\engines\RadioGroup.h.in:src\Inventor\Qt\engines\SoGuiRadioGroup.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\engines\SoGuiRadioGroup.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\engines\RadioGroup.h.in:src\Inventor\Qt\engines\SoGuiRadioGroup.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\ClickCounter.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\ClickCounter.cpp.in

"src\Inventor\Qt\nodes\ClickCounter.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ClickCounter.cpp.in:src\Inventor\Qt\nodes\ClickCounter.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\ClickCounter.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ClickCounter.cpp.in:src\Inventor\Qt\nodes\ClickCounter.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\ClickCounter.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ClickCounter.cpp.in:src\Inventor\Qt\nodes\ClickCounter.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\ClickCounter.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ClickCounter.cpp.in:src\Inventor\Qt\nodes\ClickCounter.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\ColorEditor.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\ColorEditor.cpp.in

"src\Inventor\Qt\nodes\ColorEditor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ColorEditor.cpp.in:src\Inventor\Qt\nodes\ColorEditor.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\ColorEditor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ColorEditor.cpp.in:src\Inventor\Qt\nodes\ColorEditor.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\ColorEditor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ColorEditor.cpp.in:src\Inventor\Qt\nodes\ColorEditor.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\ColorEditor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ColorEditor.cpp.in:src\Inventor\Qt\nodes\ColorEditor.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\Frame.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\Frame.cpp.in

"src\Inventor\Qt\nodes\Frame.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Frame.cpp.in:src\Inventor\Qt\nodes\Frame.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\Frame.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Frame.cpp.in:src\Inventor\Qt\nodes\Frame.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\Frame.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Frame.cpp.in:src\Inventor\Qt\nodes\Frame.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\Frame.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Frame.cpp.in:src\Inventor\Qt\nodes\Frame.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\Image.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\Image.cpp.in

"src\Inventor\Qt\nodes\Image.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Image.cpp.in:src\Inventor\Qt\nodes\Image.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\Image.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Image.cpp.in:src\Inventor\Qt\nodes\Image.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\Image.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Image.cpp.in:src\Inventor\Qt\nodes\Image.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\Image.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Image.cpp.in:src\Inventor\Qt\nodes\Image.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\Label.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\Label.cpp.in

"src\Inventor\Qt\nodes\Label.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Label.cpp.in:src\Inventor\Qt\nodes\Label.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\Label.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Label.cpp.in:src\Inventor\Qt\nodes\Label.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\Label.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Label.cpp.in:src\Inventor\Qt\nodes\Label.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\Label.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Label.cpp.in:src\Inventor\Qt\nodes\Label.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\MaterialEditor.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\MaterialEditor.cpp.in

"src\Inventor\Qt\nodes\MaterialEditor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\MaterialEditor.cpp.in:src\Inventor\Qt\nodes\MaterialEditor.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\MaterialEditor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\MaterialEditor.cpp.in:src\Inventor\Qt\nodes\MaterialEditor.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\MaterialEditor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\MaterialEditor.cpp.in:src\Inventor\Qt\nodes\MaterialEditor.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\MaterialEditor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\MaterialEditor.cpp.in:src\Inventor\Qt\nodes\MaterialEditor.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\Nodes.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\Nodes.cpp.in

"src\Inventor\Qt\nodes\Nodes.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Nodes.cpp.in:src\Inventor\Qt\nodes\Nodes.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\Nodes.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Nodes.cpp.in:src\Inventor\Qt\nodes\Nodes.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\Nodes.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Nodes.cpp.in:src\Inventor\Qt\nodes\Nodes.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\Nodes.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Nodes.cpp.in:src\Inventor\Qt\nodes\Nodes.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\Pane.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\Pane.cpp.in

"src\Inventor\Qt\nodes\Pane.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Pane.cpp.in:src\Inventor\Qt\nodes\Pane.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\Pane.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Pane.cpp.in:src\Inventor\Qt\nodes\Pane.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\Pane.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Pane.cpp.in:src\Inventor\Qt\nodes\Pane.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\Pane.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Pane.cpp.in:src\Inventor\Qt\nodes\Pane.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\Position.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\Position.cpp.in

"src\Inventor\Qt\nodes\Position.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Position.cpp.in:src\Inventor\Qt\nodes\Position.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\Position.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Position.cpp.in:src\Inventor\Qt\nodes\Position.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\Position.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Position.cpp.in:src\Inventor\Qt\nodes\Position.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\Position.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Position.cpp.in:src\Inventor\Qt\nodes\Position.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\RadioButton.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\RadioButton.cpp.in

"src\Inventor\Qt\nodes\RadioButton.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\RadioButton.cpp.in:src\Inventor\Qt\nodes\RadioButton.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\RadioButton.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\RadioButton.cpp.in:src\Inventor\Qt\nodes\RadioButton.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\RadioButton.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\RadioButton.cpp.in:src\Inventor\Qt\nodes\RadioButton.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\RadioButton.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\RadioButton.cpp.in:src\Inventor\Qt\nodes\RadioButton.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\SceneTexture2.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\SceneTexture2.cpp.in

"src\Inventor\Qt\nodes\SceneTexture2.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\SceneTexture2.cpp.in:src\Inventor\Qt\nodes\SceneTexture2.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SceneTexture2.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\SceneTexture2.cpp.in:src\Inventor\Qt\nodes\SceneTexture2.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SceneTexture2.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\SceneTexture2.cpp.in:src\Inventor\Qt\nodes\SceneTexture2.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SceneTexture2.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\SceneTexture2.cpp.in:src\Inventor\Qt\nodes\SceneTexture2.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\Slider1.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\Slider1.cpp.in

"src\Inventor\Qt\nodes\Slider1.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Slider1.cpp.in:src\Inventor\Qt\nodes\Slider1.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\Slider1.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Slider1.cpp.in:src\Inventor\Qt\nodes\Slider1.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\Slider1.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Slider1.cpp.in:src\Inventor\Qt\nodes\Slider1.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\Slider1.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Slider1.cpp.in:src\Inventor\Qt\nodes\Slider1.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\Slider2.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\Slider2.cpp.in

"src\Inventor\Qt\nodes\Slider2.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Slider2.cpp.in:src\Inventor\Qt\nodes\Slider2.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\Slider2.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Slider2.cpp.in:src\Inventor\Qt\nodes\Slider2.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\Slider2.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Slider2.cpp.in:src\Inventor\Qt\nodes\Slider2.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\Slider2.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Slider2.cpp.in:src\Inventor\Qt\nodes\Slider2.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\ClickCounter.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\ClickCounter.h.in

"src\Inventor\Qt\nodes\SoGuiClickCounter.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ClickCounter.h.in:src\Inventor\Qt\nodes\SoGuiClickCounter.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiClickCounter.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ClickCounter.h.in:src\Inventor\Qt\nodes\SoGuiClickCounter.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiClickCounter.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ClickCounter.h.in:src\Inventor\Qt\nodes\SoGuiClickCounter.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiClickCounter.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ClickCounter.h.in:src\Inventor\Qt\nodes\SoGuiClickCounter.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\ColorEditor.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\ColorEditor.h.in

"src\Inventor\Qt\nodes\SoGuiColorEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ColorEditor.h.in:src\Inventor\Qt\nodes\SoGuiColorEditor.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiColorEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ColorEditor.h.in:src\Inventor\Qt\nodes\SoGuiColorEditor.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiColorEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ColorEditor.h.in:src\Inventor\Qt\nodes\SoGuiColorEditor.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiColorEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ColorEditor.h.in:src\Inventor\Qt\nodes\SoGuiColorEditor.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\Frame.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\Frame.h.in

"src\Inventor\Qt\nodes\SoGuiFrame.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Frame.h.in:src\Inventor\Qt\nodes\SoGuiFrame.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiFrame.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Frame.h.in:src\Inventor\Qt\nodes\SoGuiFrame.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiFrame.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Frame.h.in:src\Inventor\Qt\nodes\SoGuiFrame.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiFrame.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Frame.h.in:src\Inventor\Qt\nodes\SoGuiFrame.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\Image.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\Image.h.in

"src\Inventor\Qt\nodes\SoGuiImage.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Image.h.in:src\Inventor\Qt\nodes\SoGuiImage.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiImage.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Image.h.in:src\Inventor\Qt\nodes\SoGuiImage.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiImage.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Image.h.in:src\Inventor\Qt\nodes\SoGuiImage.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiImage.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Image.h.in:src\Inventor\Qt\nodes\SoGuiImage.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\Label.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\Label.h.in

"src\Inventor\Qt\nodes\SoGuiLabel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Label.h.in:src\Inventor\Qt\nodes\SoGuiLabel.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiLabel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Label.h.in:src\Inventor\Qt\nodes\SoGuiLabel.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiLabel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Label.h.in:src\Inventor\Qt\nodes\SoGuiLabel.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiLabel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Label.h.in:src\Inventor\Qt\nodes\SoGuiLabel.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\MaterialEditor.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\MaterialEditor.h.in

"src\Inventor\Qt\nodes\SoGuiMaterialEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\MaterialEditor.h.in:src\Inventor\Qt\nodes\SoGuiMaterialEditor.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiMaterialEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\MaterialEditor.h.in:src\Inventor\Qt\nodes\SoGuiMaterialEditor.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiMaterialEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\MaterialEditor.h.in:src\Inventor\Qt\nodes\SoGuiMaterialEditor.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiMaterialEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\MaterialEditor.h.in:src\Inventor\Qt\nodes\SoGuiMaterialEditor.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\Nodes.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\Nodes.h.in

"src\Inventor\Qt\nodes\SoGuiNodes.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Nodes.h.in:src\Inventor\Qt\nodes\SoGuiNodes.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiNodes.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Nodes.h.in:src\Inventor\Qt\nodes\SoGuiNodes.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiNodes.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Nodes.h.in:src\Inventor\Qt\nodes\SoGuiNodes.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiNodes.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Nodes.h.in:src\Inventor\Qt\nodes\SoGuiNodes.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\Pane.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\Pane.h.in

"src\Inventor\Qt\nodes\SoGuiPane.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Pane.h.in:src\Inventor\Qt\nodes\SoGuiPane.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiPane.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Pane.h.in:src\Inventor\Qt\nodes\SoGuiPane.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiPane.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Pane.h.in:src\Inventor\Qt\nodes\SoGuiPane.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiPane.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Pane.h.in:src\Inventor\Qt\nodes\SoGuiPane.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\Position.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\Position.h.in

"src\Inventor\Qt\nodes\SoGuiPosition.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Position.h.in:src\Inventor\Qt\nodes\SoGuiPosition.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiPosition.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Position.h.in:src\Inventor\Qt\nodes\SoGuiPosition.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiPosition.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Position.h.in:src\Inventor\Qt\nodes\SoGuiPosition.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiPosition.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Position.h.in:src\Inventor\Qt\nodes\SoGuiPosition.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\RadioButton.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\RadioButton.h.in

"src\Inventor\Qt\nodes\SoGuiRadioButton.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\RadioButton.h.in:src\Inventor\Qt\nodes\SoGuiRadioButton.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiRadioButton.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\RadioButton.h.in:src\Inventor\Qt\nodes\SoGuiRadioButton.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiRadioButton.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\RadioButton.h.in:src\Inventor\Qt\nodes\SoGuiRadioButton.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiRadioButton.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\RadioButton.h.in:src\Inventor\Qt\nodes\SoGuiRadioButton.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\SceneTexture2.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\SceneTexture2.h.in

"src\Inventor\Qt\nodes\SoGuiSceneTexture2.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\SceneTexture2.h.in:src\Inventor\Qt\nodes\SoGuiSceneTexture2.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiSceneTexture2.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\SceneTexture2.h.in:src\Inventor\Qt\nodes\SoGuiSceneTexture2.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiSceneTexture2.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\SceneTexture2.h.in:src\Inventor\Qt\nodes\SoGuiSceneTexture2.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiSceneTexture2.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\SceneTexture2.h.in:src\Inventor\Qt\nodes\SoGuiSceneTexture2.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\Slider1.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\Slider1.h.in

"src\Inventor\Qt\nodes\SoGuiSlider1.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Slider1.h.in:src\Inventor\Qt\nodes\SoGuiSlider1.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiSlider1.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Slider1.h.in:src\Inventor\Qt\nodes\SoGuiSlider1.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiSlider1.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Slider1.h.in:src\Inventor\Qt\nodes\SoGuiSlider1.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiSlider1.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Slider1.h.in:src\Inventor\Qt\nodes\SoGuiSlider1.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\Slider2.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\Slider2.h.in

"src\Inventor\Qt\nodes\SoGuiSlider2.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Slider2.h.in:src\Inventor\Qt\nodes\SoGuiSlider2.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiSlider2.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Slider2.h.in:src\Inventor\Qt\nodes\SoGuiSlider2.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiSlider2.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Slider2.h.in:src\Inventor\Qt\nodes\SoGuiSlider2.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiSlider2.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Slider2.h.in:src\Inventor\Qt\nodes\SoGuiSlider2.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\ToggleButton.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\ToggleButton.h.in

"src\Inventor\Qt\nodes\SoGuiToggleButton.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ToggleButton.h.in:src\Inventor\Qt\nodes\SoGuiToggleButton.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiToggleButton.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ToggleButton.h.in:src\Inventor\Qt\nodes\SoGuiToggleButton.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiToggleButton.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ToggleButton.h.in:src\Inventor\Qt\nodes\SoGuiToggleButton.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiToggleButton.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ToggleButton.h.in:src\Inventor\Qt\nodes\SoGuiToggleButton.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\Translation.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\Translation.h.in

"src\Inventor\Qt\nodes\SoGuiTranslation.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Translation.h.in:src\Inventor\Qt\nodes\SoGuiTranslation.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiTranslation.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Translation.h.in:src\Inventor\Qt\nodes\SoGuiTranslation.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiTranslation.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Translation.h.in:src\Inventor\Qt\nodes\SoGuiTranslation.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiTranslation.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Translation.h.in:src\Inventor\Qt\nodes\SoGuiTranslation.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\ViewpointWrapper.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\ViewpointWrapper.h.in

"src\Inventor\Qt\nodes\SoGuiViewpointWrapper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ViewpointWrapper.h.in:src\Inventor\Qt\nodes\SoGuiViewpointWrapper.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiViewpointWrapper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ViewpointWrapper.h.in:src\Inventor\Qt\nodes\SoGuiViewpointWrapper.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiViewpointWrapper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ViewpointWrapper.h.in:src\Inventor\Qt\nodes\SoGuiViewpointWrapper.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiViewpointWrapper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ViewpointWrapper.h.in:src\Inventor\Qt\nodes\SoGuiViewpointWrapper.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\ViewportFix.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\ViewportFix.h.in

"src\Inventor\Qt\nodes\SoGuiViewportFix.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ViewportFix.h.in:src\Inventor\Qt\nodes\SoGuiViewportFix.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiViewportFix.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ViewportFix.h.in:src\Inventor\Qt\nodes\SoGuiViewportFix.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiViewportFix.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ViewportFix.h.in:src\Inventor\Qt\nodes\SoGuiViewportFix.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\SoGuiViewportFix.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ViewportFix.h.in:src\Inventor\Qt\nodes\SoGuiViewportFix.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\ToggleButton.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\ToggleButton.cpp.in

"src\Inventor\Qt\nodes\ToggleButton.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ToggleButton.cpp.in:src\Inventor\Qt\nodes\ToggleButton.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\ToggleButton.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ToggleButton.cpp.in:src\Inventor\Qt\nodes\ToggleButton.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\ToggleButton.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ToggleButton.cpp.in:src\Inventor\Qt\nodes\ToggleButton.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\ToggleButton.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ToggleButton.cpp.in:src\Inventor\Qt\nodes\ToggleButton.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\Translation.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\Translation.cpp.in

"src\Inventor\Qt\nodes\Translation.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Translation.cpp.in:src\Inventor\Qt\nodes\Translation.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\Translation.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Translation.cpp.in:src\Inventor\Qt\nodes\Translation.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\Translation.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Translation.cpp.in:src\Inventor\Qt\nodes\Translation.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\Translation.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\Translation.cpp.in:src\Inventor\Qt\nodes\Translation.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\ViewpointWrapper.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\ViewpointWrapper.cpp.in

"src\Inventor\Qt\nodes\ViewpointWrapper.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ViewpointWrapper.cpp.in:src\Inventor\Qt\nodes\ViewpointWrapper.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\ViewpointWrapper.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ViewpointWrapper.cpp.in:src\Inventor\Qt\nodes\ViewpointWrapper.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\ViewpointWrapper.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ViewpointWrapper.cpp.in:src\Inventor\Qt\nodes\ViewpointWrapper.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\ViewpointWrapper.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ViewpointWrapper.cpp.in:src\Inventor\Qt\nodes\ViewpointWrapper.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\nodes\ViewportFix.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\nodes\ViewportFix.cpp.in

"src\Inventor\Qt\nodes\ViewportFix.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ViewportFix.cpp.in:src\Inventor\Qt\nodes\ViewportFix.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\ViewportFix.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ViewportFix.cpp.in:src\Inventor\Qt\nodes\ViewportFix.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\ViewportFix.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ViewportFix.cpp.in:src\Inventor\Qt\nodes\ViewportFix.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\nodes\ViewportFix.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\nodes\ViewportFix.cpp.in:src\Inventor\Qt\nodes\ViewportFix.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\SoAny.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\SoAny.cpp.in

"src\Inventor\Qt\SoAny.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoAny.cpp.in:src\Inventor\Qt\SoAny.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoAny.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoAny.cpp.in:src\Inventor\Qt\SoAny.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoAny.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoAny.cpp.in:src\Inventor\Qt\SoAny.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoAny.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoAny.cpp.in:src\Inventor\Qt\SoAny.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\SoAny.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\SoAny.h.in

"src\Inventor\Qt\SoAny.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoAny.h.in:src\Inventor\Qt\SoAny.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoAny.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoAny.h.in:src\Inventor\Qt\SoAny.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoAny.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoAny.h.in:src\Inventor\Qt\SoAny.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoAny.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoAny.h.in:src\Inventor\Qt\SoAny.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\SoGuiComponentP.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\SoGuiComponentP.h.in

"src\Inventor\Qt\SoGuiComponentP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiComponentP.h.in:src\Inventor\Qt\SoGuiComponentP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoGuiComponentP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiComponentP.h.in:src\Inventor\Qt\SoGuiComponentP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoGuiComponentP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiComponentP.h.in:src\Inventor\Qt\SoGuiComponentP.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoGuiComponentP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiComponentP.h.in:src\Inventor\Qt\SoGuiComponentP.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\SoGuiGLWidgetP.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\SoGuiGLWidgetP.h.in

"src\Inventor\Qt\SoGuiGLWidgetP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiGLWidgetP.h.in:src\Inventor\Qt\SoGuiGLWidgetP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoGuiGLWidgetP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiGLWidgetP.h.in:src\Inventor\Qt\SoGuiGLWidgetP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoGuiGLWidgetP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiGLWidgetP.h.in:src\Inventor\Qt\SoGuiGLWidgetP.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoGuiGLWidgetP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiGLWidgetP.h.in:src\Inventor\Qt\SoGuiGLWidgetP.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\SoGuiP.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\SoGuiP.h.in

"src\Inventor\Qt\SoGuiP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiP.h.in:src\Inventor\Qt\SoGuiP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoGuiP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiP.h.in:src\Inventor\Qt\SoGuiP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoGuiP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiP.h.in:src\Inventor\Qt\SoGuiP.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoGuiP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiP.h.in:src\Inventor\Qt\SoGuiP.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\SoGui.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\SoGui.h.in

"src\Inventor\Qt\SoQt.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGui.h.in:src\Inventor\Qt\SoQt.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQt.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGui.h.in:src\Inventor\Qt\SoQt.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQt.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGui.h.in:src\Inventor\Qt\SoQt.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQt.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGui.h.in:src\Inventor\Qt\SoQt.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\editors\SoGuiColorEditor.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\editors\SoGuiColorEditor.h.in

"src\Inventor\Qt\SoQtColorEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\editors\SoGuiColorEditor.h.in:src\Inventor\Qt\SoQtColorEditor.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtColorEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\editors\SoGuiColorEditor.h.in:src\Inventor\Qt\SoQtColorEditor.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtColorEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\editors\SoGuiColorEditor.h.in:src\Inventor\Qt\SoQtColorEditor.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtColorEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\editors\SoGuiColorEditor.h.in:src\Inventor\Qt\SoQtColorEditor.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\SoGuiCommon.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\SoGuiCommon.cpp.in

"src\Inventor\Qt\SoQtCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiCommon.cpp.in:src\Inventor\Qt\SoQtCommon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiCommon.cpp.in:src\Inventor\Qt\SoQtCommon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiCommon.cpp.in:src\Inventor\Qt\SoQtCommon.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiCommon.cpp.in:src\Inventor\Qt\SoQtCommon.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\SoGuiComponent.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\SoGuiComponent.h.in

"src\Inventor\Qt\SoQtComponent.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiComponent.h.in:src\Inventor\Qt\SoQtComponent.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtComponent.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiComponent.h.in:src\Inventor\Qt\SoQtComponent.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtComponent.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiComponent.h.in:src\Inventor\Qt\SoQtComponent.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtComponent.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiComponent.h.in:src\Inventor\Qt\SoQtComponent.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\SoGuiComponentCommon.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\SoGuiComponentCommon.cpp.in

"src\Inventor\Qt\SoQtComponentCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiComponentCommon.cpp.in:src\Inventor\Qt\SoQtComponentCommon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtComponentCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiComponentCommon.cpp.in:src\Inventor\Qt\SoQtComponentCommon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtComponentCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiComponentCommon.cpp.in:src\Inventor\Qt\SoQtComponentCommon.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtComponentCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiComponentCommon.cpp.in:src\Inventor\Qt\SoQtComponentCommon.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\SoGuiCursor.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\SoGuiCursor.cpp.in

"src\Inventor\Qt\SoQtCursor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiCursor.cpp.in:src\Inventor\Qt\SoQtCursor.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtCursor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiCursor.cpp.in:src\Inventor\Qt\SoQtCursor.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtCursor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiCursor.cpp.in:src\Inventor\Qt\SoQtCursor.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtCursor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiCursor.cpp.in:src\Inventor\Qt\SoQtCursor.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\SoGuiCursor.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\SoGuiCursor.h.in

"src\Inventor\Qt\SoQtCursor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiCursor.h.in:src\Inventor\Qt\SoQtCursor.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtCursor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiCursor.h.in:src\Inventor\Qt\SoQtCursor.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtCursor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiCursor.h.in:src\Inventor\Qt\SoQtCursor.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtCursor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiCursor.h.in:src\Inventor\Qt\SoQtCursor.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\SoGuiGLWidget.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\SoGuiGLWidget.h.in

"src\Inventor\Qt\SoQtGLWidget.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiGLWidget.h.in:src\Inventor\Qt\SoQtGLWidget.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtGLWidget.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiGLWidget.h.in:src\Inventor\Qt\SoQtGLWidget.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtGLWidget.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiGLWidget.h.in:src\Inventor\Qt\SoQtGLWidget.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtGLWidget.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiGLWidget.h.in:src\Inventor\Qt\SoQtGLWidget.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\SoGuiGLWidgetCommon.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\SoGuiGLWidgetCommon.cpp.in

"src\Inventor\Qt\SoQtGLWidgetCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiGLWidgetCommon.cpp.in:src\Inventor\Qt\SoQtGLWidgetCommon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtGLWidgetCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiGLWidgetCommon.cpp.in:src\Inventor\Qt\SoQtGLWidgetCommon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtGLWidgetCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiGLWidgetCommon.cpp.in:src\Inventor\Qt\SoQtGLWidgetCommon.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtGLWidgetCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiGLWidgetCommon.cpp.in:src\Inventor\Qt\SoQtGLWidgetCommon.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\editors\SoGuiMaterialEditor.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\editors\SoGuiMaterialEditor.h.in

"src\Inventor\Qt\SoQtMaterialEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\editors\SoGuiMaterialEditor.h.in:src\Inventor\Qt\SoQtMaterialEditor.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtMaterialEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\editors\SoGuiMaterialEditor.h.in:src\Inventor\Qt\SoQtMaterialEditor.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtMaterialEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\editors\SoGuiMaterialEditor.h.in:src\Inventor\Qt\SoQtMaterialEditor.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtMaterialEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\editors\SoGuiMaterialEditor.h.in:src\Inventor\Qt\SoQtMaterialEditor.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\SoGuiObject.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\SoGuiObject.cpp.in

"src\Inventor\Qt\SoQtObject.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiObject.cpp.in:src\Inventor\Qt\SoQtObject.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtObject.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiObject.cpp.in:src\Inventor\Qt\SoQtObject.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtObject.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiObject.cpp.in:src\Inventor\Qt\SoQtObject.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtObject.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiObject.cpp.in:src\Inventor\Qt\SoQtObject.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\SoGuiObject.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\SoGuiObject.h.in

"src\Inventor\Qt\SoQtObject.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiObject.h.in:src\Inventor\Qt\SoQtObject.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtObject.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiObject.h.in:src\Inventor\Qt\SoQtObject.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtObject.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiObject.h.in:src\Inventor\Qt\SoQtObject.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtObject.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiObject.h.in:src\Inventor\Qt\SoQtObject.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\SoGuiRenderArea.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\SoGuiRenderArea.cpp.in

"src\Inventor\Qt\SoQtRenderArea.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiRenderArea.cpp.in:src\Inventor\Qt\SoQtRenderArea.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtRenderArea.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiRenderArea.cpp.in:src\Inventor\Qt\SoQtRenderArea.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtRenderArea.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiRenderArea.cpp.in:src\Inventor\Qt\SoQtRenderArea.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtRenderArea.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiRenderArea.cpp.in:src\Inventor\Qt\SoQtRenderArea.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\SoGuiRenderArea.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\SoGuiRenderArea.h.in

"src\Inventor\Qt\SoQtRenderArea.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiRenderArea.h.in:src\Inventor\Qt\SoQtRenderArea.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtRenderArea.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiRenderArea.h.in:src\Inventor\Qt\SoQtRenderArea.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtRenderArea.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiRenderArea.h.in:src\Inventor\Qt\SoQtRenderArea.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\SoQtRenderArea.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\SoGuiRenderArea.h.in:src\Inventor\Qt\SoQtRenderArea.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\viewers\SoGuiExaminerViewerP.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\viewers\SoGuiExaminerViewerP.h.in

"src\Inventor\Qt\viewers\SoGuiExaminerViewerP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiExaminerViewerP.h.in:src\Inventor\Qt\viewers\SoGuiExaminerViewerP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoGuiExaminerViewerP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiExaminerViewerP.h.in:src\Inventor\Qt\viewers\SoGuiExaminerViewerP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoGuiExaminerViewerP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiExaminerViewerP.h.in:src\Inventor\Qt\viewers\SoGuiExaminerViewerP.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoGuiExaminerViewerP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiExaminerViewerP.h.in:src\Inventor\Qt\viewers\SoGuiExaminerViewerP.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\viewers\SoGuiFullViewerP.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\viewers\SoGuiFullViewerP.h.in

"src\Inventor\Qt\viewers\SoGuiFullViewerP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiFullViewerP.h.in:src\Inventor\Qt\viewers\SoGuiFullViewerP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoGuiFullViewerP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiFullViewerP.h.in:src\Inventor\Qt\viewers\SoGuiFullViewerP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoGuiFullViewerP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiFullViewerP.h.in:src\Inventor\Qt\viewers\SoGuiFullViewerP.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoGuiFullViewerP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiFullViewerP.h.in:src\Inventor\Qt\viewers\SoGuiFullViewerP.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\viewers\SoGuiPlaneViewerP.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\viewers\SoGuiPlaneViewerP.h.in

"src\Inventor\Qt\viewers\SoGuiPlaneViewerP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiPlaneViewerP.h.in:src\Inventor\Qt\viewers\SoGuiPlaneViewerP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoGuiPlaneViewerP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiPlaneViewerP.h.in:src\Inventor\Qt\viewers\SoGuiPlaneViewerP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoGuiPlaneViewerP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiPlaneViewerP.h.in:src\Inventor\Qt\viewers\SoGuiPlaneViewerP.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoGuiPlaneViewerP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiPlaneViewerP.h.in:src\Inventor\Qt\viewers\SoGuiPlaneViewerP.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\viewers\SoGuiViewerP.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\viewers\SoGuiViewerP.h.in

"src\Inventor\Qt\viewers\SoGuiViewerP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiViewerP.h.in:src\Inventor\Qt\viewers\SoGuiViewerP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoGuiViewerP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiViewerP.h.in:src\Inventor\Qt\viewers\SoGuiViewerP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoGuiViewerP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiViewerP.h.in:src\Inventor\Qt\viewers\SoGuiViewerP.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoGuiViewerP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiViewerP.h.in:src\Inventor\Qt\viewers\SoGuiViewerP.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\viewers\SoGuiConstrainedViewer.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\viewers\SoGuiConstrainedViewer.cpp.in

"src\Inventor\Qt\viewers\SoQtConstrainedViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiConstrainedViewer.cpp.in:src\Inventor\Qt\viewers\SoQtConstrainedViewer.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtConstrainedViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiConstrainedViewer.cpp.in:src\Inventor\Qt\viewers\SoQtConstrainedViewer.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtConstrainedViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiConstrainedViewer.cpp.in:src\Inventor\Qt\viewers\SoQtConstrainedViewer.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtConstrainedViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiConstrainedViewer.cpp.in:src\Inventor\Qt\viewers\SoQtConstrainedViewer.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\viewers\SoGuiConstrainedViewer.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\viewers\SoGuiConstrainedViewer.h.in

"src\Inventor\Qt\viewers\SoQtConstrainedViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiConstrainedViewer.h.in:src\Inventor\Qt\viewers\SoQtConstrainedViewer.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtConstrainedViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiConstrainedViewer.h.in:src\Inventor\Qt\viewers\SoQtConstrainedViewer.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtConstrainedViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiConstrainedViewer.h.in:src\Inventor\Qt\viewers\SoQtConstrainedViewer.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtConstrainedViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiConstrainedViewer.h.in:src\Inventor\Qt\viewers\SoQtConstrainedViewer.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\viewers\SoGuiExaminerViewer.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\viewers\SoGuiExaminerViewer.cpp.in

"src\Inventor\Qt\viewers\SoQtExaminerViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiExaminerViewer.cpp.in:src\Inventor\Qt\viewers\SoQtExaminerViewer.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtExaminerViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiExaminerViewer.cpp.in:src\Inventor\Qt\viewers\SoQtExaminerViewer.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtExaminerViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiExaminerViewer.cpp.in:src\Inventor\Qt\viewers\SoQtExaminerViewer.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtExaminerViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiExaminerViewer.cpp.in:src\Inventor\Qt\viewers\SoQtExaminerViewer.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\viewers\SoGuiExaminerViewer.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\viewers\SoGuiExaminerViewer.h.in

"src\Inventor\Qt\viewers\SoQtExaminerViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiExaminerViewer.h.in:src\Inventor\Qt\viewers\SoQtExaminerViewer.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtExaminerViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiExaminerViewer.h.in:src\Inventor\Qt\viewers\SoQtExaminerViewer.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtExaminerViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiExaminerViewer.h.in:src\Inventor\Qt\viewers\SoQtExaminerViewer.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtExaminerViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiExaminerViewer.h.in:src\Inventor\Qt\viewers\SoQtExaminerViewer.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\viewers\SoGuiFlyViewer.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\viewers\SoGuiFlyViewer.cpp.in

"src\Inventor\Qt\viewers\SoQtFlyViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiFlyViewer.cpp.in:src\Inventor\Qt\viewers\SoQtFlyViewer.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtFlyViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiFlyViewer.cpp.in:src\Inventor\Qt\viewers\SoQtFlyViewer.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtFlyViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiFlyViewer.cpp.in:src\Inventor\Qt\viewers\SoQtFlyViewer.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtFlyViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiFlyViewer.cpp.in:src\Inventor\Qt\viewers\SoQtFlyViewer.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\viewers\SoGuiFlyViewer.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\viewers\SoGuiFlyViewer.h.in

"src\Inventor\Qt\viewers\SoQtFlyViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiFlyViewer.h.in:src\Inventor\Qt\viewers\SoQtFlyViewer.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtFlyViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiFlyViewer.h.in:src\Inventor\Qt\viewers\SoQtFlyViewer.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtFlyViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiFlyViewer.h.in:src\Inventor\Qt\viewers\SoQtFlyViewer.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtFlyViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiFlyViewer.h.in:src\Inventor\Qt\viewers\SoQtFlyViewer.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\viewers\SoGuiFullViewer.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\viewers\SoGuiFullViewer.cpp.in

"src\Inventor\Qt\viewers\SoQtFullViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiFullViewer.cpp.in:src\Inventor\Qt\viewers\SoQtFullViewer.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtFullViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiFullViewer.cpp.in:src\Inventor\Qt\viewers\SoQtFullViewer.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtFullViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiFullViewer.cpp.in:src\Inventor\Qt\viewers\SoQtFullViewer.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtFullViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiFullViewer.cpp.in:src\Inventor\Qt\viewers\SoQtFullViewer.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\viewers\SoGuiFullViewer.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\viewers\SoGuiFullViewer.h.in

"src\Inventor\Qt\viewers\SoQtFullViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiFullViewer.h.in:src\Inventor\Qt\viewers\SoQtFullViewer.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtFullViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiFullViewer.h.in:src\Inventor\Qt\viewers\SoQtFullViewer.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtFullViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiFullViewer.h.in:src\Inventor\Qt\viewers\SoQtFullViewer.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtFullViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiFullViewer.h.in:src\Inventor\Qt\viewers\SoQtFullViewer.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\viewers\SoGuiPlaneViewer.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\viewers\SoGuiPlaneViewer.cpp.in

"src\Inventor\Qt\viewers\SoQtPlaneViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiPlaneViewer.cpp.in:src\Inventor\Qt\viewers\SoQtPlaneViewer.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtPlaneViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiPlaneViewer.cpp.in:src\Inventor\Qt\viewers\SoQtPlaneViewer.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtPlaneViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiPlaneViewer.cpp.in:src\Inventor\Qt\viewers\SoQtPlaneViewer.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtPlaneViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiPlaneViewer.cpp.in:src\Inventor\Qt\viewers\SoQtPlaneViewer.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\viewers\SoGuiPlaneViewer.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\viewers\SoGuiPlaneViewer.h.in

"src\Inventor\Qt\viewers\SoQtPlaneViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiPlaneViewer.h.in:src\Inventor\Qt\viewers\SoQtPlaneViewer.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtPlaneViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiPlaneViewer.h.in:src\Inventor\Qt\viewers\SoQtPlaneViewer.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtPlaneViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiPlaneViewer.h.in:src\Inventor\Qt\viewers\SoQtPlaneViewer.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtPlaneViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiPlaneViewer.h.in:src\Inventor\Qt\viewers\SoQtPlaneViewer.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\viewers\SoGuiViewer.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\viewers\SoGuiViewer.cpp.in

"src\Inventor\Qt\viewers\SoQtViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiViewer.cpp.in:src\Inventor\Qt\viewers\SoQtViewer.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiViewer.cpp.in:src\Inventor\Qt\viewers\SoQtViewer.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiViewer.cpp.in:src\Inventor\Qt\viewers\SoQtViewer.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiViewer.cpp.in:src\Inventor\Qt\viewers\SoQtViewer.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\viewers\SoGuiViewer.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\viewers\SoGuiViewer.h.in

"src\Inventor\Qt\viewers\SoQtViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiViewer.h.in:src\Inventor\Qt\viewers\SoQtViewer.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiViewer.h.in:src\Inventor\Qt\viewers\SoQtViewer.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiViewer.h.in:src\Inventor\Qt\viewers\SoQtViewer.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\viewers\SoQtViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\viewers\SoGuiViewer.h.in:src\Inventor\Qt\viewers\SoQtViewer.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\widgets\SoAnyThumbWheel.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\widgets\SoAnyThumbWheel.cpp.in

"src\Inventor\Qt\widgets\SoAnyThumbWheel.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\widgets\SoAnyThumbWheel.cpp.in:src\Inventor\Qt\widgets\SoAnyThumbWheel.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\widgets\SoAnyThumbWheel.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\widgets\SoAnyThumbWheel.cpp.in:src\Inventor\Qt\widgets\SoAnyThumbWheel.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\widgets\SoAnyThumbWheel.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\widgets\SoAnyThumbWheel.cpp.in:src\Inventor\Qt\widgets\SoAnyThumbWheel.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\widgets\SoAnyThumbWheel.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\widgets\SoAnyThumbWheel.cpp.in:src\Inventor\Qt\widgets\SoAnyThumbWheel.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\widgets\SoAnyThumbWheel.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\widgets\SoAnyThumbWheel.h.in

"src\Inventor\Qt\widgets\SoAnyThumbWheel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\widgets\SoAnyThumbWheel.h.in:src\Inventor\Qt\widgets\SoAnyThumbWheel.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\widgets\SoAnyThumbWheel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\widgets\SoAnyThumbWheel.h.in:src\Inventor\Qt\widgets\SoAnyThumbWheel.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\widgets\SoAnyThumbWheel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\widgets\SoAnyThumbWheel.h.in:src\Inventor\Qt\widgets\SoAnyThumbWheel.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\widgets\SoAnyThumbWheel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\widgets\SoAnyThumbWheel.h.in:src\Inventor\Qt\widgets\SoAnyThumbWheel.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\widgets\SoGuiPopupMenu.cpp.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\widgets\SoGuiPopupMenu.cpp.in

"src\Inventor\Qt\widgets\SoQtPopupMenu.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\widgets\SoGuiPopupMenu.cpp.in:src\Inventor\Qt\widgets\SoQtPopupMenu.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\widgets\SoQtPopupMenu.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\widgets\SoGuiPopupMenu.cpp.in:src\Inventor\Qt\widgets\SoQtPopupMenu.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\widgets\SoQtPopupMenu.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\widgets\SoGuiPopupMenu.cpp.in:src\Inventor\Qt\widgets\SoQtPopupMenu.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\widgets\SoQtPopupMenu.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\widgets\SoGuiPopupMenu.cpp.in:src\Inventor\Qt\widgets\SoQtPopupMenu.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\common\widgets\SoGuiPopupMenu.h.in

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\common\widgets\SoGuiPopupMenu.h.in

"src\Inventor\Qt\widgets\SoQtPopupMenu.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\widgets\SoGuiPopupMenu.h.in:src\Inventor\Qt\widgets\SoQtPopupMenu.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\widgets\SoQtPopupMenu.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\widgets\SoGuiPopupMenu.h.in:src\Inventor\Qt\widgets\SoQtPopupMenu.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\widgets\SoQtPopupMenu.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\widgets\SoGuiPopupMenu.h.in:src\Inventor\Qt\widgets\SoQtPopupMenu.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Qt\widgets\SoQtPopupMenu.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Qt\common\widgets\SoGuiPopupMenu.h.in:src\Inventor\Qt\widgets\SoQtPopupMenu.h

# End Custom Build

!ENDIF

# End Source File
# End Group
# Begin Group "Source Files"
# PROP Default_Filter "c;cpp;ic;icc;h"

# Begin Group "Qt/devices sources"
# PROP Default_Filter "c;cpp;ic;icc;h"
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\devices\SoQtDevice.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\devices"
!ENDIF
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\devices\SoQtInputFocus.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\devices"
!ENDIF
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\devices\SoQtKeyboard.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\devices"
!ENDIF
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\devices\SoQtMouse.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\devices"
!ENDIF
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\devices\6DOFEvents.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\devices"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\devices\spwinput_x11.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\devices"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\devices\spwinput_win32.c
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\devices"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\devices\SoQtDeviceCommon.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\devices"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\devices\SoQtInputFocusCommon.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\devices"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\devices\SoQtKeyboardCommon.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\devices"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\devices\SoQtMouseCommon.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\devices"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\devices"
!ENDIF
# End Source File
# End Group
# Begin Group "Qt/editors sources"
# PROP Default_Filter "c;cpp;ic;icc;h"
# Begin Source File

SOURCE=.\src\Inventor\Qt\editors\SoQtColorEditor.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\editors"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\editors"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\editors"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\editors"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\editors\SoQtMaterialEditor.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\editors"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\editors"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\editors"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\editors"
!ENDIF
# End Source File
# End Group
# Begin Group "Qt/engines sources"
# PROP Default_Filter "c;cpp;ic;icc;h"
# Begin Source File

SOURCE=.\src\Inventor\Qt\engines\Engines.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\engines"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\engines"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\engines"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\engines"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\engines\RadioGroup.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\engines"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\engines"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\engines"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\engines"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\engines\Format.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\engines"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\engines"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\engines"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\engines"
!ENDIF
# End Source File
# End Group
# Begin Group "Qt/nodes sources"
# PROP Default_Filter "c;cpp;ic;icc;h"
# Begin Source File

SOURCE=.\src\Inventor\Qt\nodes\Nodes.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\nodes"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\nodes\SceneTexture2.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\nodes"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\nodes\ViewportFix.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\nodes"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\nodes\ViewpointWrapper.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\nodes"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\nodes\Pane.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\nodes"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\nodes\Position.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\nodes"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\nodes\Translation.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\nodes"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\nodes\Frame.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\nodes"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\nodes\Image.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\nodes"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\nodes\Label.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\nodes"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\nodes\ToggleButton.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\nodes"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\nodes\RadioButton.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\nodes"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\nodes\ClickCounter.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\nodes"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\nodes\Slider1.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\nodes"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\nodes\Slider2.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\nodes"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\nodes\ColorEditor.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\nodes"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\nodes\MaterialEditor.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\nodes"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\nodes"
!ENDIF
# End Source File
# End Group
# Begin Group "Qt/viewers sources"
# PROP Default_Filter "c;cpp;ic;icc;h"
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\viewers\FullViewer.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\viewers"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\viewers"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\viewers"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\viewers"
!ENDIF
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\viewers\SoQtFullViewerP.h

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\viewers\SoQtFullViewerP.h

"src\Inventor\Qt\viewers\moc_SoQtFullViewerP.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\viewers\moc_SoQtFullViewerP.icc ..\..\src\Inventor\Qt\viewers\SoQtFullViewerP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\viewers\SoQtFullViewerP.h

"src\Inventor\Qt\viewers\moc_SoQtFullViewerP.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\viewers\moc_SoQtFullViewerP.icc ..\..\src\Inventor\Qt\viewers\SoQtFullViewerP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\viewers\SoQtFullViewerP.h

"src\Inventor\Qt\viewers\moc_SoQtFullViewerP.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\viewers\moc_SoQtFullViewerP.icc ..\..\src\Inventor\Qt\viewers\SoQtFullViewerP.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\viewers\SoQtFullViewerP.h

"src\Inventor\Qt\viewers\moc_SoQtFullViewerP.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\viewers\moc_SoQtFullViewerP.icc ..\..\src\Inventor\Qt\viewers\SoQtFullViewerP.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\viewers\ExaminerViewer.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\viewers"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\viewers"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\viewers"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\viewers"
!ENDIF
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\viewers\SoQtExaminerViewerP.h

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\viewers\SoQtExaminerViewerP.h

"src\Inventor\Qt\viewers\moc_SoQtExaminerViewerP.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\viewers\moc_SoQtExaminerViewerP.icc ..\..\src\Inventor\Qt\viewers\SoQtExaminerViewerP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\viewers\SoQtExaminerViewerP.h

"src\Inventor\Qt\viewers\moc_SoQtExaminerViewerP.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\viewers\moc_SoQtExaminerViewerP.icc ..\..\src\Inventor\Qt\viewers\SoQtExaminerViewerP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\viewers\SoQtExaminerViewerP.h

"src\Inventor\Qt\viewers\moc_SoQtExaminerViewerP.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\viewers\moc_SoQtExaminerViewerP.icc ..\..\src\Inventor\Qt\viewers\SoQtExaminerViewerP.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\viewers\SoQtExaminerViewerP.h

"src\Inventor\Qt\viewers\moc_SoQtExaminerViewerP.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\viewers\moc_SoQtExaminerViewerP.icc ..\..\src\Inventor\Qt\viewers\SoQtExaminerViewerP.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\viewers\PlaneViewer.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\viewers"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\viewers"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\viewers"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\viewers"
!ENDIF
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\viewers\SoQtPlaneViewerP.h

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\viewers\SoQtPlaneViewerP.h

"src\Inventor\Qt\viewers\moc_SoQtPlaneViewerP.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\viewers\moc_SoQtPlaneViewerP.icc ..\..\src\Inventor\Qt\viewers\SoQtPlaneViewerP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\viewers\SoQtPlaneViewerP.h

"src\Inventor\Qt\viewers\moc_SoQtPlaneViewerP.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\viewers\moc_SoQtPlaneViewerP.icc ..\..\src\Inventor\Qt\viewers\SoQtPlaneViewerP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\viewers\SoQtPlaneViewerP.h

"src\Inventor\Qt\viewers\moc_SoQtPlaneViewerP.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\viewers\moc_SoQtPlaneViewerP.icc ..\..\src\Inventor\Qt\viewers\SoQtPlaneViewerP.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\viewers\SoQtPlaneViewerP.h

"src\Inventor\Qt\viewers\moc_SoQtPlaneViewerP.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\viewers\moc_SoQtPlaneViewerP.icc ..\..\src\Inventor\Qt\viewers\SoQtPlaneViewerP.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\viewers\SoQtViewer.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\viewers"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\viewers"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\viewers"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\viewers"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\viewers\SoQtConstrainedViewer.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\viewers"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\viewers"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\viewers"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\viewers"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\viewers\SoQtFlyViewer.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\viewers"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\viewers"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\viewers"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\viewers"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\viewers\SoQtFullViewer.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\viewers"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\viewers"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\viewers"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\viewers"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\viewers\SoQtExaminerViewer.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\viewers"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\viewers"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\viewers"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\viewers"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\viewers\SoQtPlaneViewer.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\viewers"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\viewers"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\viewers"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\viewers"
!ENDIF
# End Source File
# End Group
# Begin Group "Qt/widgets sources"
# PROP Default_Filter "c;cpp;ic;icc;h"
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\widgets\SoQtGLArea.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\widgets"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\widgets"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\widgets"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\widgets"
!ENDIF
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\widgets\SoQtGLArea.h

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\widgets\SoQtGLArea.h

"src\Inventor\Qt\widgets\moc_SoQtGLArea.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\widgets\moc_SoQtGLArea.icc ..\..\src\Inventor\Qt\widgets\SoQtGLArea.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\widgets\SoQtGLArea.h

"src\Inventor\Qt\widgets\moc_SoQtGLArea.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\widgets\moc_SoQtGLArea.icc ..\..\src\Inventor\Qt\widgets\SoQtGLArea.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\widgets\SoQtGLArea.h

"src\Inventor\Qt\widgets\moc_SoQtGLArea.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\widgets\moc_SoQtGLArea.icc ..\..\src\Inventor\Qt\widgets\SoQtGLArea.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\widgets\SoQtGLArea.h

"src\Inventor\Qt\widgets\moc_SoQtGLArea.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\widgets\moc_SoQtGLArea.icc ..\..\src\Inventor\Qt\widgets\SoQtGLArea.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\widgets\SoQtThumbWheel.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\widgets"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\widgets"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\widgets"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\widgets"
!ENDIF
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\widgets\SoQtThumbWheel.h

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\widgets\SoQtThumbWheel.h

"src\Inventor\Qt\widgets\moc_SoQtThumbWheel.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\widgets\moc_SoQtThumbWheel.icc ..\..\src\Inventor\Qt\widgets\SoQtThumbWheel.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\widgets\SoQtThumbWheel.h

"src\Inventor\Qt\widgets\moc_SoQtThumbWheel.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\widgets\moc_SoQtThumbWheel.icc ..\..\src\Inventor\Qt\widgets\SoQtThumbWheel.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\widgets\SoQtThumbWheel.h

"src\Inventor\Qt\widgets\moc_SoQtThumbWheel.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\widgets\moc_SoQtThumbWheel.icc ..\..\src\Inventor\Qt\widgets\SoQtThumbWheel.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\widgets\SoQtThumbWheel.h

"src\Inventor\Qt\widgets\moc_SoQtThumbWheel.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\widgets\moc_SoQtThumbWheel.icc ..\..\src\Inventor\Qt\widgets\SoQtThumbWheel.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\widgets\QtNativePopupMenu.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\widgets"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\widgets"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\widgets"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\widgets"
!ENDIF
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\widgets\QtNativePopupMenu.h

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\widgets\QtNativePopupMenu.h

"src\Inventor\Qt\widgets\moc_QtNativePopupMenu.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\widgets\moc_QtNativePopupMenu.icc ..\..\src\Inventor\Qt\widgets\QtNativePopupMenu.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\widgets\QtNativePopupMenu.h

"src\Inventor\Qt\widgets\moc_QtNativePopupMenu.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\widgets\moc_QtNativePopupMenu.icc ..\..\src\Inventor\Qt\widgets\QtNativePopupMenu.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\widgets\QtNativePopupMenu.h

"src\Inventor\Qt\widgets\moc_QtNativePopupMenu.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\widgets\moc_QtNativePopupMenu.icc ..\..\src\Inventor\Qt\widgets\QtNativePopupMenu.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\widgets\QtNativePopupMenu.h

"src\Inventor\Qt\widgets\moc_QtNativePopupMenu.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\widgets\moc_QtNativePopupMenu.icc ..\..\src\Inventor\Qt\widgets\QtNativePopupMenu.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\widgets\SoAnyThumbWheel.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\widgets"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\widgets"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\widgets"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\widgets"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\widgets\SoQtPopupMenu.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Qt\widgets"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Qt\widgets"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Qt\widgets"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Qt\widgets"
!ENDIF
# End Source File
# End Group
# Begin Group "Inventor/Qt sources"
# PROP Default_Filter "c;cpp;ic;icc;h"
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\SoQt.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Inventor\Qt"
!ENDIF
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\SoQtP.h

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\SoQtP.h

"src\Inventor\Qt\moc_SoQtP.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\moc_SoQtP.icc ..\..\src\Inventor\Qt\SoQtP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\SoQtP.h

"src\Inventor\Qt\moc_SoQtP.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\moc_SoQtP.icc ..\..\src\Inventor\Qt\SoQtP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\SoQtP.h

"src\Inventor\Qt\moc_SoQtP.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\moc_SoQtP.icc ..\..\src\Inventor\Qt\SoQtP.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\SoQtP.h

"src\Inventor\Qt\moc_SoQtP.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\moc_SoQtP.icc ..\..\src\Inventor\Qt\SoQtP.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\SoQtSignalThread.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Inventor\Qt"
!ENDIF
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\SoQtSignalThread.h

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\SoQtSignalThread.h

"src\Inventor\Qt\moc_SoQtSignalThread.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\moc_SoQtSignalThread.icc ..\..\src\Inventor\Qt\SoQtSignalThread.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\SoQtSignalThread.h

"src\Inventor\Qt\moc_SoQtSignalThread.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\moc_SoQtSignalThread.icc ..\..\src\Inventor\Qt\SoQtSignalThread.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\SoQtSignalThread.h

"src\Inventor\Qt\moc_SoQtSignalThread.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\moc_SoQtSignalThread.icc ..\..\src\Inventor\Qt\SoQtSignalThread.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\SoQtSignalThread.h

"src\Inventor\Qt\moc_SoQtSignalThread.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\moc_SoQtSignalThread.icc ..\..\src\Inventor\Qt\SoQtSignalThread.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\SoQtComponent.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Inventor\Qt"
!ENDIF
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\SoQtComponentP.h

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\SoQtComponentP.h

"src\Inventor\Qt\moc_SoQtComponentP.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\moc_SoQtComponentP.icc ..\..\src\Inventor\Qt\SoQtComponentP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\SoQtComponentP.h

"src\Inventor\Qt\moc_SoQtComponentP.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\moc_SoQtComponentP.icc ..\..\src\Inventor\Qt\SoQtComponentP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\SoQtComponentP.h

"src\Inventor\Qt\moc_SoQtComponentP.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\moc_SoQtComponentP.icc ..\..\src\Inventor\Qt\SoQtComponentP.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\SoQtComponentP.h

"src\Inventor\Qt\moc_SoQtComponentP.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\moc_SoQtComponentP.icc ..\..\src\Inventor\Qt\SoQtComponentP.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\SoQtGLWidget.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Inventor\Qt"
!ENDIF
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\SoQtGLWidgetP.h

!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\SoQtGLWidgetP.h

"src\Inventor\Qt\moc_SoQtGLWidgetP.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\moc_SoQtGLWidgetP.icc ..\..\src\Inventor\Qt\SoQtGLWidgetP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\SoQtGLWidgetP.h

"src\Inventor\Qt\moc_SoQtGLWidgetP.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\moc_SoQtGLWidgetP.icc ..\..\src\Inventor\Qt\SoQtGLWidgetP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\SoQtGLWidgetP.h

"src\Inventor\Qt\moc_SoQtGLWidgetP.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\moc_SoQtGLWidgetP.icc ..\..\src\Inventor\Qt\SoQtGLWidgetP.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - moc'ing $(InputPath)
InputPath=..\..\src\Inventor\Qt\SoQtGLWidgetP.h

"src\Inventor\Qt\moc_SoQtGLWidgetP.icc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(QTDIR)\bin\moc -o src\Inventor\Qt\moc_SoQtGLWidgetP.icc ..\..\src\Inventor\Qt\SoQtGLWidgetP.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\SoQtImageReader.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Inventor\Qt"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\SoAny.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Inventor\Qt"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\SoQtCursor.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Inventor\Qt"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\SoQtObject.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Inventor\Qt"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\SoQtCommon.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Inventor\Qt"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\SoQtComponentCommon.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Inventor\Qt"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\SoQtGLWidgetCommon.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Inventor\Qt"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\SoQtRenderArea.cpp
!IF  "$(CFG)" == "soqt1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Inventor\Qt"
!ELSEIF  "$(CFG)" == "soqt1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Inventor\Qt"
!ENDIF
# End Source File
# End Group
# End Group
# Begin Group "Public Headers"

# PROP Default_Filter "h;ic;icc"
# Begin Group "Inventor\Qt\devices headers"
# Set Default_Filter "h"
# Begin Source File

SOURCE=src\Inventor\Qt\devices\SoQtDevice.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Qt\devices\SoQtKeyboard.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Qt\devices\SoQtMouse.h
# End Source File
# End Group
# Begin Group "Inventor\Qt\editors headers"
# Set Default_Filter "h"
# Begin Source File

SOURCE=src\Inventor\Qt\editors\SoQtColorEditor.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Qt\editors\SoQtMaterialEditor.h
# End Source File
# End Group
# Begin Group "Inventor\Qt\nodes headers"
# Set Default_Filter "h"
# Begin Source File

SOURCE=src\Inventor\Qt\nodes\SoGuiColorEditor.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Qt\nodes\SoGuiMaterialEditor.h
# End Source File
# End Group
# Begin Group "Inventor\Qt\viewers headers"
# Set Default_Filter "h"
# Begin Source File

SOURCE=src\Inventor\Qt\viewers\SoQtViewer.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Qt\viewers\SoQtFullViewer.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Qt\viewers\SoQtExaminerViewer.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Qt\viewers\SoQtPlaneViewer.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Qt\viewers\SoQtConstrainedViewer.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Qt\viewers\SoQtFlyViewer.h
# End Source File
# End Group
# Begin Group "Inventor\Qt\widgets headers"
# Set Default_Filter "h"
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\widgets\SoQtThumbWheel.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Qt\widgets\SoQtPopupMenu.h
# End Source File
# End Group
# Begin Group "Inventor\Qt headers"
# Set Default_Filter "h"
# Begin Source File

SOURCE=src\Inventor\Qt\SoQt.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Qt\SoQtBasic.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Qt\SoQtObject.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Qt\SoQtCursor.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Qt\SoQtComponent.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Qt\SoQtGLWidget.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Qt\SoQtColorEditor.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Qt\SoQtRenderArea.h
# End Source File
# End Group
# End Group
# Begin Group "Private Headers"

# PROP Default_Filter "h;ic;icc"
# Begin Group "Qt local includes"

# PROP Default_Filter "h;ic;icc"
# Begin Source File

SOURCE=.\src\Inventor\Qt\SoGuiComponentP.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\SoGuiGLWidgetP.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\SoGuiP.h

# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "devices local includes"

# PROP Default_Filter "h;ic;icc"
# Begin Source File

SOURCE=.\src\Inventor\Qt\devices\SoGuiDeviceP.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\devices\SoGuiInputFocusP.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\devices\SoGuiKeyboardP.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\devices\SoGuiMouseP.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\devices\SoGuiSpaceballP.h

# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "engines local includes"

# PROP Default_Filter "h;ic;icc"
# Begin Source File

SOURCE=.\src\Inventor\Qt\engines\SoGuiEngines.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\engines\SoGuiFormat.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\engines\SoGuiRadioGroup.h

# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "Qt local includes"

# PROP Default_Filter "h;ic;icc"
# Begin Source File

SOURCE=.\src\Inventor\Qt\moc_SoQtComponentP.icc

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\moc_SoQtGLWidgetP.icc

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\moc_SoQtP.icc

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\moc_SoQtSignalThread.icc

# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "nodes local includes"

# PROP Default_Filter "h;ic;icc"
# Begin Source File

SOURCE=.\src\Inventor\Qt\nodes\SoGuiClickCounter.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\nodes\SoGuiFrame.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\nodes\SoGuiImage.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\nodes\SoGuiLabel.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\nodes\SoGuiNodes.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\nodes\SoGuiPane.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\nodes\SoGuiPosition.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\nodes\SoGuiRadioButton.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\nodes\SoGuiSceneTexture2.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\nodes\SoGuiSlider1.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\nodes\SoGuiSlider2.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\nodes\SoGuiToggleButton.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\nodes\SoGuiTranslation.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\nodes\SoGuiViewpointWrapper.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\nodes\SoGuiViewportFix.h

# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "viewers local includes"

# PROP Default_Filter "h;ic;icc"
# Begin Source File

SOURCE=.\src\Inventor\Qt\viewers\SoGuiExaminerViewerP.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\viewers\SoGuiFullViewerP.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\viewers\SoGuiPlaneViewerP.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\viewers\SoGuiViewerP.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\viewers\moc_SoQtExaminerViewerP.icc

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\viewers\moc_SoQtFullViewerP.icc

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\viewers\moc_SoQtPlaneViewerP.icc

# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "widgets local includes"

# PROP Default_Filter "h;ic;icc"
# Begin Source File

SOURCE=.\src\Inventor\Qt\widgets\moc_QtNativePopupMenu.icc

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\widgets\moc_SoQtGLArea.icc

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Qt\widgets\moc_SoQtThumbWheel.icc

# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "src local includes"

# PROP Default_Filter "h;ic;icc"
# Begin Source File

SOURCE=.\src\config-debug.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\config-release.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\soqtdefs.h

# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "Qt local includes"

# PROP Default_Filter "h;ic;icc"
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\SoQtComponentP.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\SoQtGLWidgetP.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\SoQtP.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\SoQtSignalThread.h

# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "devices local includes"

# PROP Default_Filter "h;ic;icc"
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\devices\SoQtDeviceP.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\devices\SoQtLinuxJoystickP.h

# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "viewers local includes"

# PROP Default_Filter "h;ic;icc"
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\viewers\SoQtExaminerViewerP.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\viewers\SoQtFullViewerP.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Qt\viewers\SoQtPlaneViewerP.h

# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "src local includes"

# PROP Default_Filter "h;ic;icc"
# Begin Source File

SOURCE=..\..\src\qt-config.h

# PROP Exclude_From_Build 1
# End Source File
# End Group
# End Group
# End Target
# End Project
