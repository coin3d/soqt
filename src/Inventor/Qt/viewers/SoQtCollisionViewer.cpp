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

