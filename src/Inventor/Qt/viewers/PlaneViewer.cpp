/**************************************************************************
 *
 *  This file is part of the Coin SoQt GUI binding library.
 *  Copyright (C) 1998-2000 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License version
 *  2.1 as published by the Free Software Foundation.  See the file
 *  LICENSE.LGPL at the root directory of the distribution for all the
 *  details.
 *
 *  If you want to use Coin SoQt for applications not compatible with the
 *  LGPL, please contact SIM to acquire a Professional Edition License.
 *
 *  Systems in Motion, Prof Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ support@sim.no Voice: +47 22114160 Fax: +47 22207097
 *
 **************************************************************************/

#if SOQT_DEBUG
static const char rcsid[] =
  "$Id$";
#endif

#include <qevent.h>
#include <qpushbutton.h>
#include <qpixmap.h>
#include <qkeycode.h>
#include <qmetaobject.h>
#include <moc_SoQtPlaneViewer.cpp>

#include <Inventor/errors/SoDebugError.h>
#include <Inventor/projectors/SbPlaneProjector.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoOrthographicCamera.h>

#include <soqtdefs.h>
#include <Inventor/Qt/widgets/SoQtThumbWheel.h>

#include <Inventor/Qt/viewers/SoAnyPlaneViewer.h>
#include <Inventor/Qt/viewers/SoQtPlaneViewer.h>

#include <Inventor/Qt/common/pixmaps/ortho.xpm>
#include <Inventor/Qt/common/pixmaps/perspective.xpm>
#include <Inventor/Qt/common/pixmaps/x.xpm>
#include <Inventor/Qt/common/pixmaps/y.xpm>
#include <Inventor/Qt/common/pixmaps/z.xpm>

/*!
  \class SoQtPlaneViewer Inventor/Qt/viewers/SoQtPlaneViewer.h
  \brief The SoQtPlaneViewer class is yet to be documented...
  \ingroup soqtviewers
*/

// ************************************************************************

SOQT_OBJECT_SOURCE(SoQtPlaneViewer);

// ************************************************************************

/*!
  The public constructor.
*/

SoQtPlaneViewer::SoQtPlaneViewer(
  QWidget * parent,
  const char * const name, 
  SbBool embed,
  SoQtFullViewer::BuildFlag flag, 
  SoQtViewer::Type type)
: inherited(parent, name, embed, flag, type, FALSE)
, common(new SoAnyPlaneViewer(this))
{
  this->constructor(TRUE);
} // SoQtPlaneViewer()

// ************************************************************************

/*!
  A protected constructor.
*/

SoQtPlaneViewer::SoQtPlaneViewer(
  QWidget * parent,
  const char * const name, 
  SbBool embed, 
  SoQtFullViewer::BuildFlag flag, 
  SoQtViewer::Type type, 
  SbBool build)
: inherited(parent, name, embed, flag, type, FALSE)
, common(new SoAnyPlaneViewer(this))
{
  this->constructor(build);
} // SoQtPlaneViewer()

// ************************************************************************

/*!
  FIXME: write doc
*/

void
SoQtPlaneViewer::constructor(// private
  SbBool build)
{
  this->mode = IDLE_MODE;

  this->projector = new SbPlaneProjector;
  SbViewVolume vv;
  vv.ortho(-1, 1, -1, 1, -1, 1);
  this->projector->setViewVolume(vv);

  this->addVisibilityChangeCallback(SoQtPlaneViewer::visibilityCB, this);

  this->setClassName("SoQtPlaneViewer");
  this->setLeftWheelString("transY");
  this->setBottomWheelString("transX");

  this->pixmaps.orthogonal = new QPixmap((const char **) ortho_xpm);
  this->pixmaps.perspective = new QPixmap((const char **) perspective_xpm);

  if (! build) return;

  this->setSize(SbVec2s(550, 490)); // extra buttons -> more height
  QWidget * viewer = this->buildWidget(this->getParentWidget());
  this->setBaseWidget(viewer);
} // constructor()

// ************************************************************************

/*!
  The destructor.
*/

SoQtPlaneViewer::~SoQtPlaneViewer(
  void)
{
  delete this->pixmaps.orthogonal;
  delete this->pixmaps.perspective;
  delete this->projector;
} // ~SoQtPlaneViewer()

// ************************************************************************

/*!
  FIXME: write doc
*/

void
SoQtPlaneViewer::setViewing(// virtual
  SbBool enable)
{
  inherited::setViewing(enable);
} // setViewing()

// ************************************************************************

/*!
  FIXME: write doc
*/

void
SoQtPlaneViewer::setCamera(// virtual
  SoCamera * camera)
{
  if (camera) {
    SoType type = camera->getTypeId();
    SbBool orthogonal =
      type.isDerivedFrom(SoOrthographicCamera::getClassTypeId());
    this->setRightWheelString(orthogonal ? "Zoom" : "Dolly");
    if (this->buttons.camera) {
      this->buttons.camera->setPixmap(orthogonal ?
        *(this->pixmaps.orthogonal) : *(this->pixmaps.perspective));
    }
  }
  inherited::setCamera(camera);
} // setCamera()

// ************************************************************************

/*!
  FIXME: write doc
*/

void
SoQtPlaneViewer::setCursorEnabled(// virtual
  SbBool enable)
{
  inherited::setCursorEnabled(enable);
} // setCursorEnabled()

// ************************************************************************

/*!
  FIXME: write doc
*/

QWidget *
SoQtPlaneViewer::buildWidget(
  QWidget * parent)
{
  QWidget * widget = inherited::buildWidget(parent);
  ((SoQtThumbWheel *)this->leftWheel)->setRangeBoundaryHandling(SoQtThumbWheel::ACCUMULATE);
  ((SoQtThumbWheel *)this->bottomWheel)->setRangeBoundaryHandling(SoQtThumbWheel::ACCUMULATE);
  return widget;
} // buildWidget()

// ************************************************************************

/*!
  FIXME: write doc
*/

const char *
SoQtPlaneViewer::getDefaultWidgetName(// virtual
  void) const
{
  static const char defaultWidgetName[] = "SoQtPlaneViewer";
  return defaultWidgetName;
} // getDefaultWidgetName()

// ************************************************************************

/*!
  FIXME: write doc
*/

const char *
SoQtPlaneViewer::getDefaultTitle(// virtual
  void) const
{
  static const char defaultTitle[] = "Plane Viewer";
  return defaultTitle;
} // getDefaultTitle()

// ************************************************************************

/*!
  FIXME: write doc
*/

const char *
SoQtPlaneViewer::getDefaultIconTitle(// virtual
  void) const
{
  static const char defaultIconTitle[] = "Plane Viewer";
  return defaultIconTitle;
} // getDefaultIconTitle()

// ************************************************************************

/*!
  FIXME: write doc
*/

SbBool
SoQtPlaneViewer::processSoEvent(// virtual, protected
  const SoEvent * const event)
{
  if (common->processSoEvent(event))
    return TRUE;

  return inherited::processSoEvent(event);
} // processSoEvent()

/*!
  FIXME: write doc
*/

void
SoQtPlaneViewer::processEvent(// virtual
  QEvent * event)
{
  if (SoQtViewer::processCommonEvents(event))
    return;

  inherited::processEvent(event);
} // processEvent()

// ************************************************************************

/*!
  FIXME: write doc
*/

void
SoQtPlaneViewer::setSeekMode(// virtual
  SbBool enable)
{
  inherited::setSeekMode(enable);
} // setSeekMode()

// ************************************************************************

/*!
  FIXME: write doc
*/

void
SoQtPlaneViewer::actualRedraw(// virtual
  void)
{
  inherited::actualRedraw();
//  common->drawRotateGraphics();
} // actualRedraw()

// ************************************************************************

/*!
  FIXME: write doc
*/

void
SoQtPlaneViewer::leftWheelMotion(// virtual
  float value)
{
  common->translateY(value - this->getLeftWheelValue());
  inherited::leftWheelMotion(value);
} // leftWheelMotion()

/*!
  FIXME: write doc
*/

void
SoQtPlaneViewer::bottomWheelMotion(// virtual
  float value)
{
  common->translateX(value - this->getBottomWheelValue());
  inherited::bottomWheelMotion(value);
} // bottomWheelMotion()

/*!
  FIXME: write doc
*/

void
SoQtPlaneViewer::rightWheelMotion(// virtual
  float value)
{
  common->zoom(this->getRightWheelValue() - value);
  inherited::rightWheelMotion(value);
} // rightWheelMotion()

// ************************************************************************

/*!
  FIXME: write doc
*/

void
SoQtPlaneViewer::createPrefSheet(// virtual
  void)
{
} // createPrefSheet()

// ************************************************************************

/*!
  FIXME: write doc
*/

void
SoQtPlaneViewer::createViewerButtons(// virtual
  QWidget * parent,
  SbPList * buttons)
{
  inherited::createViewerButtons(parent, buttons);

  // add X, Y, Z viewpoint buttons
  this->buttons.x = new QPushButton(parent);
  this->buttons.x->setFocusPolicy(QWidget::NoFocus);
  this->buttons.x->setToggleButton(FALSE);
  this->buttons.x->setPixmap(QPixmap((const char **) x_xpm));
  QObject::connect(this->buttons.x, SIGNAL(clicked()),
                    this, SLOT(xClicked()));
  buttons->append(this->buttons.x);
  this->buttons.y = new QPushButton(parent);
  this->buttons.y->setFocusPolicy(QWidget::NoFocus);
  this->buttons.y->setToggleButton(FALSE);
  this->buttons.y->setPixmap(QPixmap((const char **) y_xpm));
  QObject::connect(this->buttons.y, SIGNAL(clicked()),
                    this, SLOT(yClicked()));
  buttons->append(this->buttons.y);
  this->buttons.z = new QPushButton(parent);
  this->buttons.z->setFocusPolicy(QWidget::NoFocus);
  this->buttons.z->setToggleButton(FALSE);
  this->buttons.z->setPixmap(QPixmap((const char **) z_xpm));
  QObject::connect(this->buttons.z, SIGNAL(clicked()),
                    this, SLOT(zClicked()));
  buttons->append(this->buttons.z);

  // add camera toggle button
  assert(this->pixmaps.perspective != NULL);
  assert(this->pixmaps.orthogonal != NULL);
  this->buttons.camera = new QPushButton(parent);
  this->buttons.camera->setFocusPolicy(QWidget::NoFocus);

  QPixmap * pixmap = NULL;
  SoType t = this->getCameraType();
  if (t.isDerivedFrom(SoOrthographicCamera::getClassTypeId()))
    pixmap = this->pixmaps.orthogonal;
  else if (t.isDerivedFrom(SoPerspectiveCamera::getClassTypeId()))
    pixmap = this->pixmaps.perspective;
  else assert(0 && "unsupported cameratype");

  this->buttons.camera->setPixmap(*pixmap);
  buttons->append(this->buttons.camera);

  QObject::connect(this->buttons.camera, SIGNAL(clicked()),
                    this, SLOT(cameraToggleClicked()));

} // createViewerButtons()

// ************************************************************************

/*!
  FIXME: write doc
*/

void
SoQtPlaneViewer::openViewerHelpCard(// virtual
  void)
{
  this->openHelpCard("SoQtPlaneViewer.help");
} // openViewerHelpCard()

// ************************************************************************

/*!
  FIXME: write doc
*/

void
SoQtPlaneViewer::computeSeekFinalOrientation(// virtual
  void)
{
} // computeSeekFinalOrientation()

// ************************************************************************

/*!
  \internal
*/

void
SoQtPlaneViewer::xClicked(
  void)
{
  common->viewPlaneX();
} // xClicked()

/*!
  \internal
*/

void
SoQtPlaneViewer::yClicked(
  void)
{
  common->viewPlaneY();
} // yClicked()

/*!
  \internal
*/

void
SoQtPlaneViewer::zClicked(
  void)
{
  common->viewPlaneZ();
} // zClicked()

/*!
  \internal
*/

void
SoQtPlaneViewer::cameraToggleClicked(
  void)
{
  this->toggleCameraType();
} // cameraToggleClicked()

// ************************************************************************

/*!
  \internal
*/

void
SoQtPlaneViewer::visibilityCB(// static
  void * data,
  SbBool visible)
{
  SoQtPlaneViewer * thisp = (SoQtPlaneViewer *) data;

/*
  examiner viewer does this, we don't have to...
  if (thisp->isAnimating()) {
    if (visible)
      thisp->timerTrigger->schedule();
    else
      thisp->timerTrigger->unschedule();
  }
*/
} // visibilityCB()

// ************************************************************************

/*!
  FIXME: write doc
*/

void
SoQtPlaneViewer::setModeFromState(// private
  unsigned int state)
{
  PlaneViewerMode mode = IDLE_MODE;

  const unsigned int maskedstate =
    state & (LeftButton|MidButton|ControlButton);

  switch (maskedstate) {
  case 0:
    mode = IDLE_MODE;
    break;

  case LeftButton:
    mode = TRANSLATE_MODE;
    break;

  case MidButton:
  case (LeftButton|ControlButton):
    mode = DOLLY_MODE;
    break;

  case ControlButton:
    mode = ROTZ_WAIT_MODE;
    break;

  case (MidButton|ControlButton):
  case (LeftButton|MidButton|ControlButton):
    mode = ROTZ_MODE;
    break;

  default:
    SoDebugError::postWarning("SoQtPlaneViewer::setModeFromState",
      "state not handled: %d", maskedstate);
    break;

  } // switch (maskedstate)

  this->setMode(mode);
} // setModeFromState()

/*!
*/

void
SoQtPlaneViewer::setMode(
  PlaneViewerMode mode)
{
  // FIXME: set cursor...

  switch (mode) {
  case IDLE_MODE:
    while (this->getInteractiveCount())
      this->interactiveCountDec();
    break;

  case TRANSLATE_MODE:
  case DOLLY_MODE:
  case ROTZ_MODE:
    while (this->getInteractiveCount())
      this->interactiveCountDec();
    break;

  default:
    break;
  } // switch (mode)

  this->mode = mode;
} // setMode()

// ************************************************************************

#if SOQT_DEBUG
static const char * getSoQtPlaneViewerRCSId(void) { return rcsid; }
#endif
