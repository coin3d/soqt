############################################################################
#
#  Copyright (C) 1998-1999 by Systems in Motion.  All rights reserved.
#
#  This file is part of the Coin library.
#
#  This file may be distributed under the terms of the Q Public License
#  as defined by Troll Tech AS of Norway and appearing in the file
#  LICENSE.QPL included in the packaging of this file.
#
#  If you want to use Coin in applications not covered by licenses
#  compatible with the QPL, you can contact SIM to aquire a
#  Professional Edition license for Coin.
#
#  Systems in Motion AS, Prof. Brochs gate 6, N-7030 Trondheim, NORWAY
#  http://www.sim.no/ sales@sim.no Voice: +47 73540378 Fax: +47 73943861
#
############################################################################

TEMPLATE	=	lib
CONFIG		+=	opengl qt
INCLUDEPATH	+=	../include;$(QTDIR)/include;

HEADERS = \
	../include/Inventor/Qt/SoQt.h \
	../include/Inventor/Qt/SoQtComponent.h \
\
	  ../include/Inventor/Qt/SoQtSliderSetBase.h \
	    ../include/Inventor/Qt/SoQtSliderSet.h \
	      ../include/Inventor/Qt/SoQtTransformSliderSet.h \
\
	  ../include/Inventor/Qt/SoQtGLWidget.h \
	    ../include/Inventor/Qt/SoQtRenderArea.h \
	      ../include/Inventor/Qt/viewers/SoQtViewer.h \
	        ../include/Inventor/Qt/viewers/SoQtFullViewer.h \
	          ../include/Inventor/Qt/viewers/SoQtExaminerViewer.h \
\
	../include/Inventor/Qt/devices/SoQtDevice.h \
	  ../include/Inventor/Qt/devices/SoQtMouse.h \
	  ../include/Inventor/Qt/devices/SoQtKeyboard.h \
	  ../include/Inventor/Qt/devices/SoQtSpaceball.h \
	  ../include/Inventor/Qt/devices/SoQtInputFocus.h \
\
	../include/Inventor/Qt/widgets/QtThumbwheel.h


SOURCES = \
	../src/SoQt.cpp \
	../src/SoQtComponent.cpp \
\
	  ../src/SoQtSliderSetBase.cpp \
	    ../src/SoQtSliderSet.cpp \
	      ../src/SoQtTransformSliderSet.cpp \
\
	  ../src/SoQtGLWidget.cpp \
	    ../src/SoQtRenderArea.cpp \
	      ../src/viewers/SoQtViewer.cpp \
	        ../src/viewers/SoQtFullViewer.cpp \
	          ../src/viewers/SoQtExaminerViewer.cpp \
\
	../src/SoQtCursors.cpp \
\
	../src/devices/SoQtDevice.cpp \
	  ../src/devices/SoQtMouse.cpp \
	  ../src/devices/SoQtKeyboard.cpp \
	  ../src/devices/SoQtSpaceball.cpp \
	  ../src/devices/SoQtInputFocus.cpp \
\
	../src/widgets/QtThumbwheel.cpp
