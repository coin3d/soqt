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
} // SoQtConstainedViewer()

// ************************************************************************

/*!
  Destructor
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
} // setUpDirection()

// ************************************************************************

/*!
*/

const SbVec3f &
SoQtConstrainedViewer::getUpDirection(
  void )
{
  /* FIXME */
  static SbVec3f null( 0, 0, 0 );
  return null;
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
} // recomputeSceneGraph()

// ************************************************************************

/*!
*/

void
SoQtConstrainedViewer::tiltCamera( // virtual
  float delta )
{
} // tiltCamera()

// ************************************************************************

/*!
*/

void
SoQtConstrainedViewer::bottomWheelMotion( // virtual
  float value )
{
} // bottomWheelMotion()

// ************************************************************************

/*!
*/

void
SoQtConstrainedViewer::leftWheelMotion( // virtual
  float value )
{
} // leftWheelMotion()

// ************************************************************************

/*!
*/

void
SoQtConstrainedViewer::changeCameraValues( // virtual
  SoCamera * newCamera )
{
} // changeCameraValues()

// ************************************************************************

/*!
*/

void
SoQtConstrainedViewer::findUpDirection(
  SbVec2s mouseLocation )
{
} // findUpDirection()

// ************************************************************************

/*!
*/

void
SoQtConstrainedViewer::checkForCameraUpConstrain(
  void )
{
} // checkForCameraUpConstrain()

// ************************************************************************

/*!
*/

void
SoQtConstrainedViewer::computeSeekFinalOrientation( // virtual
  void )
{
} // computeSeekFinalOrientation()

// ************************************************************************
