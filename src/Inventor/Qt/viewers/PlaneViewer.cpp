/**************************************************************************\
 *
 *  This file is part of the Coin GUI toolkit libraries.
 *  Copyright (C) 1998-2002 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  version 2.1 as published by the Free Software Foundation.  See the
 *  file LICENSE.LGPL at the root directory of this source distribution
 *  for more details.
 *
 *  If you want to use this library with software that is incompatible
 *  licensewise with the LGPL, and / or you would like to take
 *  advantage of the additional benefits with regard to our support
 *  services, please contact Systems in Motion about acquiring a Coin
 *  Professional Edition License.  See <URL:http://www.coin3d.org> for
 *  more information.
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
#include <qpixmap.h>
#include <qkeycode.h>
#include <qmetaobject.h>
#include <moc_SoQtPlaneViewerP.cpp>
#include <SoQtPlaneViewerP.h>

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

// SoQtPlaneViewerP "private implementation" class.

#define PUBLIC(ptr) (ptr->pub)
#define PRIVATE(ptr) (ptr->pimpl)

#define THIS (PRIVATE(this))

SoQtPlaneViewerP::SoQtPlaneViewerP(SoQtPlaneViewer * publ)
  : SoGuiPlaneViewerP(publ)
{
  this->pixmaps.orthogonal = new QPixmap((const char **) ortho_xpm);
  this->pixmaps.perspective = new QPixmap((const char **) perspective_xpm);
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
  PUBLIC(this)->commonConstructor(); // init generic stuff

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
  PUBLIC(this)->viewPlaneX();
}

void
SoQtPlaneViewerP::yClicked(void)
{
  PUBLIC(this)->viewPlaneY();
}

void
SoQtPlaneViewerP::zClicked(void)
{
  PUBLIC(this)->viewPlaneZ();
}

void
SoQtPlaneViewerP::cameraToggleClicked(void)
{
  PUBLIC(this)->toggleCameraType();
}

// ************************************************************************

/*!
  The public constructor, to be used by application programmers who
  want to instantiate the plain, standard SoQtPlaneViewer.
*/
SoQtPlaneViewer::SoQtPlaneViewer(QWidget * parent,
                                 const char * const name,
                                 SbBool embed,
                                 SoQtFullViewer::BuildFlag flag,
                                 SoQtViewer::Type type)
  : inherited(parent, name, embed, flag, type, FALSE)
{
  PRIVATE(this) = new SoQtPlaneViewerP(this);
  PRIVATE(this)->constructor(TRUE);
}

// ************************************************************************

/*!
  A protected constructor, to be used by application programmers who
  want to extend the SoQtPlaneViewer.
*/
SoQtPlaneViewer::SoQtPlaneViewer(QWidget * parent,
                                 const char * const name,
                                 SbBool embed,
                                 SoQtFullViewer::BuildFlag flag,
                                 SoQtViewer::Type type,
                                 SbBool build)
  : inherited(parent, name, embed, flag, type, FALSE)
{
  PRIVATE(this) = new SoQtPlaneViewerP(this);
  PRIVATE(this)->constructor(build);
}

// ************************************************************************

/*!
  The destructor.
*/
SoQtPlaneViewer::~SoQtPlaneViewer()
{
  delete PRIVATE(this);
}

// ************************************************************************

/*!
  FIXME: write doc
*/

void
SoQtPlaneViewer::setViewing(SbBool enable)
{
  inherited::setViewing(enable);
}

// ************************************************************************

/*!
  FIXME: write doc
*/

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

/*!
  FIXME: write doc
*/

QWidget *
SoQtPlaneViewer::buildWidget(QWidget * parent)
{
  QWidget * widget = inherited::buildWidget(parent);
  ((SoQtThumbWheel *)this->leftWheel)->setRangeBoundaryHandling(SoQtThumbWheel::ACCUMULATE);
  ((SoQtThumbWheel *)this->bottomWheel)->setRangeBoundaryHandling(SoQtThumbWheel::ACCUMULATE);
  return widget;
}

// ************************************************************************

/*!
  FIXME: write doc
*/
void
SoQtPlaneViewer::processEvent(QEvent * event)
{
  if (SoQtViewer::processCommonEvents(event))
    return;

  inherited::processEvent(event);
}

// ************************************************************************

/*!
  FIXME: write doc
*/
void
SoQtPlaneViewer::actualRedraw(void)
{
  inherited::actualRedraw();
//  this->drawRotateGraphics();
}

// ************************************************************************

/*!
  FIXME: write doc
*/
void
SoQtPlaneViewer::createPrefSheet(void)
{
  SOQT_STUB();
}

// ************************************************************************

/*!
  FIXME: write doc
*/
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

/*!
  FIXME: write doc
*/
void
SoQtPlaneViewer::openViewerHelpCard(void)
{
  this->openHelpCard("SoQtPlaneViewer.help");
}

// ************************************************************************
