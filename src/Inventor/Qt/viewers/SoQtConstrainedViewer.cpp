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
#endif // SOQT_DEBUG

#include <Inventor/errors/SoDebugError.h>

#include <soqtdefs.h>
#include <Inventor/Qt/viewers/SoQtConstrainedViewer.h>

/*!
  \class SoQtConstrainedViewer Inventor/Qt/viewers/SoQtConstrainedViewer.h
  \brief The SoQtConstrainedViewer class is yet to be documented...
  \ingroup soqtviewers
*/

// ************************************************************************

SOQT_TYPED_ABSTRACT_OBJECT_SOURCE(SoQtConstrainedViewer, SoQtFullViewer);

// ************************************************************************

/*!
  Constructor.
*/

SoQtConstrainedViewer::SoQtConstrainedViewer( // protected
  QWidget * parent,
  const char * const name,
  SbBool embed,
  SoQtFullViewer::BuildFlag flag, 
  SoQtViewer::Type type, 
  SbBool build )
: inherited( parent, name, embed, flag, type, FALSE )
{
  this->setClassName( "SoQtConstrainedViewer" );
  this->upVector = SbVec3f( 0.0f, 1.0f, 0.0f );

  if ( build ) {
    QWidget * viewer = this->buildWidget( this->getParentWidget() );
    this->setBaseWidget( viewer );
  }
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


