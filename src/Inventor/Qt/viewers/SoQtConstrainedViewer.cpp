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

#include <Inventor/Qt/viewers/SoQtConstrainedViewer.h>

// ************************************************************************

void
SoQtConstrainedViewer::setUpDirection(
  const SbVec3f & upDirection )
{
}

const SbVec3f &
SoQtConstrainedViewer::getUpDirection(
  void )
{
}

void
SoQtConstrainedViewer::setCamera( // virtual
  SoCamera * newCamera )
{
}

void
SoQtConstrainedViewer::saveHomePosition( // virtual
  void )
{
}

void
SoQtConstrainedViewer::resetToHomePosition( // virtual
  void )
{
}

void
SoQtConstrainedViewer::recomputeSceneSize( // virtual
  void )
{
}

SoQtConstrainedViewer::SoQtConstrainedViewer( // protected
  QWidget * parent,
  const char * const name,
  SbBool buildInsideParent,
  SoQtFullViewer::BuildFlag flag, 
  SoQtViewer::Type type, 
  SbBool buildNow )
{
}

SoQtConstrainedViewer::~SoQtConstrainedViewer(
  void )
{
}
  
void
SoQtConstrainedViewer::tiltCamera( // virtual
  float delta )
{
}

void
SoQtConstrainedViewer::bottomWheelMotion( // virtual
  float value )
{
}

void
SoQtConstrainedViewer::leftWheelMotion( // virtual
  float value )
{
}

void
SoQtConstrainedViewer::changeCameraValues( // virtual
  SoCamera * newCamera )
{
}

void
SoQtConstrainedViewer::findUpDirection(
  SbVec2s mouseLocation );
{
}

void
SoQtConstrainedViewer::checkForCameraUpConstrain(
  void )
{
}

void
SoQtConstrainedViewer::computeSeekFinalOrientation( // virtual
  void )
{
}
