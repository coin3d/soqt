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
  \class SoQtConstrainedViewer Inventor/Qt/viewers/SoQtConstrainedViewer.h
  \brief The SoQtConstrainedViewer class is yet to be documented...
  \ingroup soqtviewers
*/

#include <Inventor/errors/SoDebugError.h>

#include <soqtdefs.h>
#include <Inventor/Qt/viewers/SoQtConstrainedViewer.h>

// ************************************************************************

/*!
  Constructor.
*/

SoQtConstrainedViewer::SoQtConstrainedViewer( // protected
  QWidget * parent,
  const char * const name,
  SbBool buildInsideParent,
  SoQtFullViewer::BuildFlag flag, 
  SoQtViewer::Type type, 
  SbBool buildNow )
: inherited( parent, name, buildInsideParent, flag, type, FALSE )
{
  this->setClassName( "SoQtConstrainedViewer" );
  this->upVector = SbVec3f( 0.0f, 1.0f, 0.0f );

  if ( buildNow )
    this->setBaseWidget( this->buildWidget( this->getParentWidget() ) );
} // SoQtConstainedViewer()

// ************************************************************************

/*!
  The destructor.
*/

SoQtConstrainedViewer::~SoQtConstrainedViewer( // virtual
  void )
{
} // ~SoQtConstarinedViewer()
  
// ************************************************************************

/*!
*/

void
SoQtConstrainedViewer::setUpDirection(
  const SbVec3f & upDirection )
{
  this->upVector = upDirection;
} // setUpDirection()

// ************************************************************************

/*!
*/

const SbVec3f &
SoQtConstrainedViewer::getUpDirection(
  void )
{
  return upVector;
} // getUpDirection()

// ************************************************************************

/*!
*/

void
SoQtConstrainedViewer::setCamera( // virtual
  SoCamera * newCamera )
{
} // setCamera()

// ************************************************************************

/*!
*/

void
SoQtConstrainedViewer::saveHomePosition( // virtual
  void )
{
} // saveHomePosition()

// ************************************************************************

/*!
*/

void
SoQtConstrainedViewer::resetToHomePosition( // virtual
  void )
{
} // resetToHomePosition()

// ************************************************************************

/*!
*/

void
SoQtConstrainedViewer::recomputeSceneSize( // virtual
  void )
{
  SoDebugError::postInfo( "SoQtConstrainedViewer::recomputeSceneSize",
    "stub called" );
} // recomputeSceneGraph()

// ************************************************************************

/*!
  aka upperLeftWheelMotion() ;)
*/

void
SoQtConstrainedViewer::tiltCamera( // virtual, protected
  float delta )
{
} // tiltCamera()

// ************************************************************************

/*!
*/

void
SoQtConstrainedViewer::bottomWheelMotion( // virtual, protected
  float value )
{
} // bottomWheelMotion()

// ************************************************************************

/*!
*/

void
SoQtConstrainedViewer::leftWheelMotion( // virtual, protected
  float value )
{
//  SoAnyConstrainedViewer::elevation( );
} // leftWheelMotion()

// ************************************************************************

/*!
*/

void
SoQtConstrainedViewer::changeCameraValues( // virtual, protected
  SoCamera * camera )
{
  SoDebugError::postInfo( "SoQtConstrainedViewer::changeCameraValues",
    "stub called" );
} // changeCameraValues()

// ************************************************************************

/*!
*/

void
SoQtConstrainedViewer::findUpDirection(
  SbVec2s mouseLocation )
{
  SoDebugError::postInfo( "SoQtConstrainedViewer::findUpDirection",
    "stub called" );
  // pick on point, set upVector to normal of picked polygon
} // findUpDirection()

// ************************************************************************

/*!
*/

void
SoQtConstrainedViewer::checkForCameraUpConstrain(
  void )
{
  SoDebugError::postInfo( "SoQtConstrainedViewer::checkForCameraUpConstrain",
    "stub called" );
} // checkForCameraUpConstrain()

// ************************************************************************

/*!
*/

void
SoQtConstrainedViewer::computeSeekFinalOrientation( // virtual, protected
  void )
{
  SoDebugError::postInfo( "SoQtConstrainedViewer::computeSeekFinalOrientation",
    "stub called" );
} // computeSeekFinalOrientation()

// ************************************************************************


