/**************************************************************************\
 *
 *  This file is part of the Coin family of 3D visualization libraries.
 *  Copyright (C) 1998-2002 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and / or
 *  modify it under the terms of the GNU General Public License
 *  version 2 as published by the Free Software Foundation.  See the
 *  file LICENSE.GPL at the root directory of this source distribution
 *  for more details.
 *
 *  If you desire to use this library in software that is incompatible
 *  with the GNU GPL, and / or you would like to take advantage of the
 *  additional benefits with regard to our support services, please
 *  contact Systems in Motion about acquiring a Coin Professional
 *  Edition License.  See <URL:http://www.coin3d.org> for more
 *  information.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  <URL:http://www.sim.no>, <mailto:support@sim.no>
 *
\**************************************************************************/

// ************************************************************************

// Class is documented in common/viewers/SoGuiPlaneViewer.cpp.in.

// ************************************************************************

#include <qevent.h>
#include <qpushbutton.h>
#include <qwindowsstyle.h>
#include <qpixmap.h>
#include <qkeycode.h>
#include <qmetaobject.h>
#include <Inventor/Qt/viewers/moc_SoQtPlaneViewerP.cpp>
#include <Inventor/Qt/viewers/SoQtPlaneViewerP.h>

#include <Inventor/errors/SoDebugError.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoOrthographicCamera.h>

#include <soqtdefs.h>
#include <Inventor/Qt/widgets/SoQtThumbWheel.h>

#include <Inventor/Qt/viewers/SoQtPlaneViewer.h>

#include <Inventor/Qt/common/pixmaps/ortho.xpm>
#include <Inventor/Qt/common/pixmaps/perspective.xpm>
#include <Inventor/Qt/common/pixmaps/x.xpm>
#include <Inventor/Qt/common/pixmaps/y.xpm>
#include <Inventor/Qt/common/pixmaps/z.xpm>

// ************************************************************************

#define PUBLIC(ptr) (ptr->pub)
#define PRIVATE(ptr) (ptr->pimpl)

// ************************************************************************

// Documented in superclass.
void
SoQtPlaneViewer::setCamera(SoCamera * camera)
{
  if (camera) {
    SoType type = camera->getTypeId();
    SbBool orthogonal =
      type.isDerivedFrom(SoOrthographicCamera::getClassTypeId());
    this->setRightWheelString(orthogonal ? "Zoom" : "Dolly");
    if (PRIVATE(this)->buttons.camera) {
      PRIVATE(this)->buttons.camera->setPixmap(orthogonal ?
        *(PRIVATE(this)->pixmaps.orthogonal) : *(PRIVATE(this)->pixmaps.perspective));
    }
  }
  inherited::setCamera(camera);
}

// ************************************************************************

// Documented in superclass.
QWidget *
SoQtPlaneViewer::buildWidget(QWidget * parent)
{
  return inherited::buildWidget(parent);
}

// ************************************************************************

// Documented in superclass. Overridden so we can append the X/Y/Z
// buttons and the camera type switch button in the rightside button
// column.
void
SoQtPlaneViewer::createViewerButtons(QWidget * parent,
                                     SbPList * buttons)
{
  inherited::createViewerButtons(parent, buttons);

  // add X, Y, Z viewpoint buttons
  PRIVATE(this)->buttons.x = new QPushButton(parent);
  PRIVATE(this)->buttons.x->setFocusPolicy(QWidget::NoFocus);
  PRIVATE(this)->buttons.x->setToggleButton(FALSE);
  PRIVATE(this)->buttons.x->setPixmap(QPixmap((const char **) x_xpm));
  QObject::connect(PRIVATE(this)->buttons.x, SIGNAL(clicked()),
                   PRIVATE(this), SLOT(xClicked()));
  buttons->append(PRIVATE(this)->buttons.x);
  PRIVATE(this)->buttons.y = new QPushButton(parent);
  PRIVATE(this)->buttons.y->setFocusPolicy(QWidget::NoFocus);
  PRIVATE(this)->buttons.y->setToggleButton(FALSE);
  PRIVATE(this)->buttons.y->setPixmap(QPixmap((const char **) y_xpm));
  QObject::connect(PRIVATE(this)->buttons.y, SIGNAL(clicked()),
                   PRIVATE(this), SLOT(yClicked()));
  buttons->append(PRIVATE(this)->buttons.y);
  PRIVATE(this)->buttons.z = new QPushButton(parent);
  PRIVATE(this)->buttons.z->setFocusPolicy(QWidget::NoFocus);
  PRIVATE(this)->buttons.z->setToggleButton(FALSE);
  PRIVATE(this)->buttons.z->setPixmap(QPixmap((const char **) z_xpm));
  QObject::connect(PRIVATE(this)->buttons.z, SIGNAL(clicked()),
                   PRIVATE(this), SLOT(zClicked()));
  buttons->append(PRIVATE(this)->buttons.z);

  // add camera toggle button
  assert(PRIVATE(this)->pixmaps.perspective != NULL);
  assert(PRIVATE(this)->pixmaps.orthogonal != NULL);
  PRIVATE(this)->buttons.camera = new QPushButton(parent);
  PRIVATE(this)->buttons.camera->setFocusPolicy(QWidget::NoFocus);

#if (defined Q_WS_MAC && QT_VERSION >= 0x030100) 
    // Since Qt/Mac 3.1.x, all pushbuttons (even those < 32x32) are drawn
    // using the Aqua style, i.e. with rounded edges and shading. This
    // looks really ugly in the viewer decoration. Drawing the buttons
    // in the Windows style gives us the flat, square buttons we want.
  PRIVATE(this)->buttons.x->setStyle(new QWindowsStyle());
  PRIVATE(this)->buttons.y->setStyle(new QWindowsStyle());
  PRIVATE(this)->buttons.z->setStyle(new QWindowsStyle());
  PRIVATE(this)->buttons.camera->setStyle(new QWindowsStyle());
#endif

  QPixmap * pixmap = NULL;
  SoType t = this->getCameraType();
  if (t.isDerivedFrom(SoOrthographicCamera::getClassTypeId()))
    pixmap = PRIVATE(this)->pixmaps.orthogonal;
  else if (t.isDerivedFrom(SoPerspectiveCamera::getClassTypeId()))
    pixmap = PRIVATE(this)->pixmaps.perspective;
  else assert(0 && "unsupported cameratype");

  PRIVATE(this)->buttons.camera->setPixmap(*pixmap);
  buttons->append(PRIVATE(this)->buttons.camera);

  QObject::connect(PRIVATE(this)->buttons.camera, SIGNAL(clicked()),
                   PRIVATE(this), SLOT(cameraToggleClicked()));

}

// ************************************************************************

// SoQtPlaneViewerP "private implementation" class.

#ifndef DOXYGEN_SKIP_THIS

SoQtPlaneViewerP::SoQtPlaneViewerP(SoQtPlaneViewer * publ)
  : SoGuiPlaneViewerP(publ)
{
  this->pixmaps.orthogonal = new QPixmap((const char **) ortho_xpm);
  this->pixmaps.perspective = new QPixmap((const char **) perspective_xpm);

  this->buttons.x = NULL;
  this->buttons.y = NULL;
  this->buttons.z = NULL;
  this->buttons.camera = NULL;
}

SoQtPlaneViewerP::~SoQtPlaneViewerP()
{
  delete this->pixmaps.orthogonal;
  delete this->pixmaps.perspective;
}

// Private constructor-code common for all public / protected
// constructors.
void
SoQtPlaneViewerP::constructor(SbBool buildnow)
{
  this->commonConstructor(); // init generic stuff

  PUBLIC(this)->setClassName("SoQtPlaneViewer");
  PUBLIC(this)->setLeftWheelString("transY");
  PUBLIC(this)->setBottomWheelString("transX");

  if (!buildnow) return;

  PUBLIC(this)->setSize(SbVec2s(550, 490)); // extra buttons -> more height
  QWidget * viewer = PUBLIC(this)->buildWidget(PUBLIC(this)->getParentWidget());
  PUBLIC(this)->setBaseWidget(viewer);
}

void
SoQtPlaneViewerP::xClicked(void)
{
  this->viewPlaneX();
}

void
SoQtPlaneViewerP::yClicked(void)
{
  this->viewPlaneY();
}

void
SoQtPlaneViewerP::zClicked(void)
{
  this->viewPlaneZ();
}

void
SoQtPlaneViewerP::cameraToggleClicked(void)
{
  PUBLIC(this)->toggleCameraType();
}

// ************************************************************************

#endif // DOXYGEN_SKIP_THIS
