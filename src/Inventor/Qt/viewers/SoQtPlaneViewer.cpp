/**************************************************************************
 *
 *  Copyright (C) 2000 by Systems in Motion.  All rights reserved.
 *
 *  This file is part of the Coin library.
 *
 *  This file may be distributed under the terms of the Q Public License
 *  as defined by Troll Tech AS of Norway and appearing in the file
 *  LICENSE.QPL included in the packaging of this file.
 *
 *  If you want to use Coin in applications not covered by licenses
 *  compatible with the QPL, you can contact SIM to aquire a
 *  Professional Edition license for Coin.
 *
 *  Systems in Motion AS, Prof. Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ sales@sim.no Voice: +47 22114160 Fax: +47 67172912
 *
 **************************************************************************/

static const char rcsid[] =
  "$Id$";

/*!
  \class SoQtPlaneViewer Inventor/Qt/viewers/SoQtPlaneViewer.h
  \brief The SoQtPlaneViewer class is yet to be documented...
  \ingroup soqtviewers
*/

#include <Inventor/projectors/SbPlaneProjector.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoOrthographicCamera.h>

#include <Inventor/Qt/widgets/QtThumbwheel.h>

#include <Inventor/Qt/common/SoAnyPlaneViewer.h>
#include <Inventor/Qt/viewers/SoQtPlaneViewer.h>

// ************************************************************************

/*!
  The public constructor.
*/

SoQtPlaneViewer::SoQtPlaneViewer(
  QWidget * parent = NULL,
  const char * const name = NULL, 
  SbBool buildInsideParent = TRUE,
  SoQtFullViewer::BuildFlag flag = BUILD_ALL, 
  SoQtViewer::Type type = BROWSER )
: inherited( parent, name, buildInsideParent, flag, type, FALSE )
{
  this->constructor( TRUE );
} // SoQtPlaneViewer()

// ************************************************************************

/*!
  A protected constructor.
*/

SoQtPlaneViewer::SoQtPlaneViewer(
  QWidget * parent,
  const char * const name, 
  SbBool buildInsideParent, 
  SoQtFullViewer::BuildFlag flag, 
  SoQtViewer::Type type, 
  SbBool buildNow )
: inherited( parent, name, buildInsideParent, flag, type, FALSE )
{
  this->constructor( buildNow );
} // SoQtPlaneViewer()

// ************************************************************************

/*!
*/

void
SoQtPlaneViewer::constructor( // private
  SbBool buildNow )
{
  this->projector = new SbPlaneProjector;
  SbViewVolume vv;
  vv.ortho(-1, 1, -1, 1, -1, 1);
  this->projector->setViewVolume(vv);

/*  this->addVisibilityChangeCallback(SoQtPlaneViewer::visibilityCB, this); */

  this->setClassName("SoQtPlaneViewer");
  this->setLeftWheelString( "transY" );
  this->setBottomWheelString( "transX" );
  if ( buildNow )
    this->setBaseWidget( this->buildWidget( this->getParentWidget() ) );
} // constructor()

// ************************************************************************

/*!
  The destructor.
*/

SoQtPlaneViewer::~SoQtPlaneViewer(
  void )
{
  delete this->projector;
} // ~SoQtPlaneViewer()

// ************************************************************************

/*!
*/

void
SoQtPlaneViewer::setViewing( // virtual
  SbBool enable )
{
  inherited::setViewing( enable );
} // setViewing()

// ************************************************************************

/*!
*/

void
SoQtPlaneViewer::setCamera( // virtual
  SoCamera * camera )
{
  if ( camera ) {
    SoType type = camera->getTypeId();
    SbBool orthogonal =
      type.isDerivedFrom( SoOrthographicCamera::getClassTypeId() );
    this->setRightWheelString( orthogonal ? "Zoom" : "Dolly" );
/*
    if ( this->cameratogglebutton ) {
      this->cameratogglebutton->setPixmap( orthogonal ?
                                          * (this->orthopixmap) :
                                          * (this->perspectivepixmap) );
    }
*/
  }
  inherited::setCamera( camera );
} // setCamera()

// ************************************************************************

/*!
*/

void
SoQtPlaneViewer::setCursorEnabled( // virtual
  SbBool enable )
{
  inherited::setCursorEnabled( enable );
} // setCursorEnabled()

// ************************************************************************

/*!
*/

QWidget *
SoQtPlaneViewer::buildWidget(
  QWidget * parent )
{
  QWidget * widget = inherited::buildWidget( parent );

  this->getThumbwheel( LEFTDECORATION )->
    setRangeBoundaryHandling( QtThumbwheel::ACCUMULATE );
  this->getThumbwheel( BOTTOMDECORATION )->
    setRangeBoundaryHandling( QtThumbwheel::ACCUMULATE );
  
  return widget;
} // buildWidget()

// ************************************************************************

/*!
*/

const char *
SoQtPlaneViewer::getDefaultWidgetName( // virtual
  void ) const
{
  static const char defaultWidgetName[] = "";
  return defaultWidgetName;
} // getDefaultWidgetName()

// ************************************************************************

/*!
*/

const char *
SoQtPlaneViewer::getDefaultTitle( // virtual
  void ) const
{
  static const char defaultTitle[] = "Plane Viewer";
  return defaultTitle;
} // getDefaultTitle()

// ************************************************************************

/*!
*/

const char *
SoQtPlaneViewer::getDefaultIconTitle( // virtual
  void ) const
{
  static const char defaultIconTitle[] = "";
  return defaultIconTitle;
} // getDefaultIconTitle()

// ************************************************************************

/*!
*/

void
SoQtPlaneViewer::processEvent( // virtual
  QEvent * event )
{
} // processEvent()

// ************************************************************************

/*!
*/

void
SoQtPlaneViewer::setSeekMode( // virtual
  SbBool enable )
{
  inherited::setSeekMode( enable );
} // setSeekMode()

// ************************************************************************

/*!
*/

void
SoQtPlaneViewer::actualRedraw( // virtual
  void )
{
  inherited::actualRedraw();
//  if ( this->isFeedbackVisible() )
//    this->drawAxisCross();
} // actualRedraw()

// ************************************************************************

/*!
*/

void
SoQtPlaneViewer::bottomWheelMotion( // virtual
  float value )
{
  inherited::bottomWheelMotion(
    SoAnyPlaneViewer::transXWheelMotion( value, this->getBottomWheelValue(),
                                         this->getCamera() ) );
} // bottomWheelMotion()

// ************************************************************************

/*!
*/

void
SoQtPlaneViewer::leftWheelMotion( // virtual
  float value )
{
  inherited::leftWheelMotion(
    SoAnyPlaneViewer::transYWheelMotion( value, this->getLeftWheelValue(),
                                         this->getCamera() ) );
} // leftWheelMotion()

// ************************************************************************

/*!
*/

void
SoQtPlaneViewer::rightWheelMotion( // virtual
  float value )
{
  this->zoom( value - this->getRightWheelValue() );
  inherited::rightWheelMotion( value );
} // rightWheelMotion()

// ************************************************************************

/*!
*/

void
SoQtPlaneViewer::createPrefSheet( // virtual
  void )
{
} // createPrefSheet()

// ************************************************************************

/*!
*/

void
SoQtPlaneViewer::createViewerButtons( // virtual
  QWidget * parent )
{
/* add X, Y, Z buttons */
//  inherited::createViewerButtons( parent );
} // createViewerButtons()

// ************************************************************************

/*!
*/

void
SoQtPlaneViewer::openViewerHelpCard( // virtual
  void )
{
} // openViewerHelpCard()

// ************************************************************************

/*!
*/

void
SoQtPlaneViewer::computeSeekFinalOrientation( // virtual
  void )
{
} // computeSeekFinalOrientation()

// ************************************************************************

/*!
*/

void
SoQtPlaneViewer::zoom(
  const float difference )
{
  SoCamera * camera = this->getCamera();
  assert( camera != NULL );
  SoType type = camera->getTypeId();
  float multiplicator = exp( difference ); // in the range of <0, ->>

  if ( type.isDerivedFrom( SoOrthographicCamera::getClassTypeId() ) ) {
    SoOrthographicCamera * orthocam = (SoOrthographicCamera *) camera;
    orthocam->height = orthocam->height.getValue() * multiplicator;
  } else if ( type.isDerivedFrom( SoPerspectiveCamera::getClassTypeId() ) ) {
    float oldfocaldist = camera->focalDistance.getValue();
    camera->focalDistance = oldfocaldist * multiplicator;
    SbVec3f direction;
    camera->orientation.getValue().multVec( SbVec3f( 0, 0, -1 ), direction );
    camera->position = camera->position.getValue() +
      (camera->focalDistance.getValue() - oldfocaldist) * -direction;
  } else {
    assert( 0 && "impossible" );
  }
} // zoom()

// ************************************************************************
