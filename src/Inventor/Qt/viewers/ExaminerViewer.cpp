/**************************************************************************\
 * Copyright (c) Kongsberg Oil & Gas Technologies AS
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
\**************************************************************************/

// Class documentation in common/viewers/SoGuiExaminerViewer.cpp.in.

// *************************************************************************

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H
#include <qt-config.h>

#include <qpushbutton.h>
#include <qnamespace.h>
#include <qlabel.h>
#include <qcheckbox.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qpixmap.h>
#include <qbitmap.h>
#include <qtimer.h>
#include <qcursor.h>
#include <qmetaobject.h>

#ifdef HAVE_QSTYLEFACTORY_H
#include <qstylefactory.h>
#endif // HAVE_QSTYLEFACTORY_H

#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/sensors/SoTimerSensor.h>
#include <Inventor/projectors/SbSphereSheetProjector.h>
#if SOQT_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // SOQT_DEBUG

#include <Inventor/Qt/viewers/SoQtExaminerViewerP.h>
#include <Inventor/Qt/viewers/moc_SoQtExaminerViewerP.icc>

#include <soqtdefs.h>
#include <Inventor/Qt/widgets/SoQtThumbWheel.h>
#include <Inventor/Qt/SoQtCursor.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>

// Icon graphic for the camera button.
#include <Inventor/Qt/common/pixmaps/ortho.xpm>
#include <Inventor/Qt/common/pixmaps/perspective.xpm>

// ************************************************************************

// Take care of namespace incompatibilities between Qt 3 and Qt 4.

#if QT_VERSION < 0x040000 // pre Qt 4
#define QTWIDGET_NOFOCUS QWidget::NoFocus
#else // Qt 4.0.0+
#define QTWIDGET_NOFOCUS Qt::NoFocus
#endif // Qt 4.0.0+

// *************************************************************************

#define PRIVATE(obj) ((obj)->pimpl)
#define PUBLIC(obj) ((obj)->pub)

// *************************************************************************

SOQT_OBJECT_SOURCE(SoQtExaminerViewer);

// *************************************************************************

// Documented in common/viewers/SoGuiExaminerViewer.cpp.in.
SoQtExaminerViewer::SoQtExaminerViewer(QWidget * parent,
                                       const char * name,
                                       SbBool embed,
                                       SoQtFullViewer::BuildFlag flag,
                                       SoQtViewer::Type type)
  : inherited(parent, name, embed, flag, type, FALSE)
{
  PRIVATE(this) = new SoQtExaminerViewerP(this);
  PRIVATE(this)->constructor(TRUE);
}

// *************************************************************************

// Documented in common/viewers/SoGuiExaminerViewer.cpp.in.
SoQtExaminerViewer::SoQtExaminerViewer(QWidget * parent,
                                       const char * name,
                                       SbBool embed,
                                       SoQtFullViewer::BuildFlag flag,
                                       SoQtViewer::Type type,
                                       SbBool build)
  : inherited(parent, name, embed, flag, type, FALSE)
{
  PRIVATE(this) = new SoQtExaminerViewerP(this);
  PRIVATE(this)->constructor(build);
}

// *************************************************************************

SoQtExaminerViewer::~SoQtExaminerViewer()
{
  delete PRIVATE(this);
}

// *************************************************************************

// Documented in superclass.
void
SoQtExaminerViewer::setCamera(SoCamera * newCamera)
{
  // This method overridden from parent class to toggle the camera
  // type selection button pixmap and string of the zoom/dolly
  // thumbwheel.

  if (newCamera) {
    SoType camtype = newCamera->getTypeId();
    SbBool orthogonal =
      camtype.isDerivedFrom(SoOrthographicCamera::getClassTypeId());

    const char * oldLabel = this->getRightWheelString();
    if (oldLabel) {
      if (orthogonal) {
        if (strcmp("Dolly",oldLabel) == 0)
          this->setRightWheelString("Zoom");
      }
      else if (strcmp("Zoom",oldLabel) == 0)
        this->setRightWheelString("Dolly");
    }
    if (PRIVATE(this)->cameratogglebutton) {
#if QT_VERSION >= 0x040000
      PRIVATE(this)->cameratogglebutton->setIcon(
#else
      PRIVATE(this)->cameratogglebutton->setPixmap(
#endif
	orthogonal ?
	* (PRIVATE(this)->orthopixmap) :
	* (PRIVATE(this)->perspectivepixmap));
    }
  }

  inherited::setCamera(newCamera);
}

// *************************************************************************

// Documented in superclass. Overridden so we can append the camera
// type switch button in the rightside button column.
void
SoQtExaminerViewer::createViewerButtons(QWidget * parent, SbPList * buttonlist)
{
  inherited::createViewerButtons(parent, buttonlist);

  PRIVATE(this)->cameratogglebutton = new QPushButton(parent);

#if (defined Q_OS_MAC && QT_VERSION >=0x030100) && defined(HAVE_QSTYLEFACTORY_H)
    // Since Qt/Mac 3.1.x, all pushbuttons (even those < 32x32) are drawn
    // using the Aqua style, i.e. with rounded edges and shading. This
    // looks really ugly in the viewer decoration. Drawing the buttons
    // in the Windows style gives us the flat, square buttons we want.
  QStyle * style = QStyleFactory::create("windows");
  if (style) { PRIVATE(this)->cameratogglebutton->setStyle(style); }
#endif

  PRIVATE(this)->cameratogglebutton->setFocusPolicy(QTWIDGET_NOFOCUS);
  assert(PRIVATE(this)->perspectivepixmap);
  assert(PRIVATE(this)->orthopixmap);

  QPixmap * p = NULL;
  SoType t = this->getCameraType();
  if (t.isDerivedFrom(SoOrthographicCamera::getClassTypeId()))
    p = PRIVATE(this)->orthopixmap;
  else if (t.isDerivedFrom(SoPerspectiveCamera::getClassTypeId()))
    p = PRIVATE(this)->perspectivepixmap;
  else assert(0 && "unsupported cameratype");

#if QT_VERSION >= 0x040000
  PRIVATE(this)->cameratogglebutton->setIcon(*p);
#else
  PRIVATE(this)->cameratogglebutton->setPixmap(*p);
#endif
  PRIVATE(this)->cameratogglebutton->adjustSize();

  QObject::connect(PRIVATE(this)->cameratogglebutton, SIGNAL(clicked()),
                   PRIVATE(this), SLOT(cameratoggleClicked()));

  buttonlist->append(PRIVATE(this)->cameratogglebutton);
}

// *************************************************************************

// SoQtExaminerViewerP "private implementation" class.

#ifndef DOXYGEN_SKIP_THIS

SoQtExaminerViewerP::SoQtExaminerViewerP(SoQtExaminerViewer * publ)
  : SoGuiExaminerViewerP(publ)
{
}

SoQtExaminerViewerP::~SoQtExaminerViewerP()
{
  // Button pixmaps.
  delete this->orthopixmap;
  delete this->perspectivepixmap;

  this->genericDestructor();
}

// This contains the real constructor code (the two SoQtExaminerViewer
// constructors are only entry points for this method).
void
SoQtExaminerViewerP::constructor(SbBool build)
{
  this->genericConstructor();

  this->cameratogglebutton = NULL;

  this->orthopixmap = new QPixmap((const char **)ortho_xpm);
  this->perspectivepixmap = new QPixmap((const char **)perspective_xpm);
  assert(this->orthopixmap->size() == this->perspectivepixmap->size());

  PUBLIC(this)->setClassName("SoQtExaminerViewer");

  PUBLIC(this)->setPopupMenuString("Examiner Viewer");
  PUBLIC(this)->setLeftWheelString("RotX");
  PUBLIC(this)->setBottomWheelString("RotY");

  if (build) {
    QWidget * widget = PUBLIC(this)->buildWidget(PUBLIC(this)->getParentWidget());
    PUBLIC(this)->setBaseWidget(widget);
  }
}

void
SoQtExaminerViewerP::cameratoggleClicked()
{
  if (PUBLIC(this)->getCamera()) PUBLIC(this)->toggleCameraType();
}

// *************************************************************************

#endif // DOXYGEN_SKIP_THIS

#undef PRIVATE
#undef PUBLIC
