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

/*!
  \class SoQtCollisionViewer Inventor/Qt/viewers/SoQtCollisionViewer.h
  \brief The SoQtCollisionViewer class is yet to be documented...
  \ingroup soqtviewers
*/

#include <soqtdefs.h>
#include <Inventor/Qt/viewers/SoQtCollisionViewer.h>

// ************************************************************************

SoQtCollisionViewer::SoQtCollisionViewer(
  SoQtViewer * viewer )
{
}

SoQtCollisionViewer::~SoQtCollisionViewer(
  void )
{
}

SoQtViewer *
SoQtCollisionViewer::getViewer(
  void )
{
    return NULL;
}

void
SoQtCollisionViewer::setDistance(
  float distance )
{
}

float
SoQtCollisionViewer::getDistance(
  void )
{
    return 0.0;
}

void
SoQtCollisionViewer::setNumSteps(
  int numSteps )
{
}

int
SoQtCollisionViewer::getNumSteps(
  void )
{
    return 0;
}
  
void
SoQtCollisionViewer::setCollisionDetection(
  SbBool value )
{
}

SbBool
SoQtCollisionViewer::getCollisionDetection(
  void )
{
    return FALSE;
}

void
SoQtCollisionViewer::setZBufferOptimization(
  SbBool value )
{
}

SbBool
SoQtCollisionViewer::getZBufferOptimization(
  void )
{
    return FALSE;
}
  
void
SoQtCollisionViewer::addCallback(
  SoQtCollisionViewerCB * func,
  void * user )
{
}

void
SoQtCollisionViewer::removeCallback(
  SoQtCollisionViewerCB * func,
  void * user )
{
}

