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

// $Id$

#ifndef SOQT_COLLISIONVIEWER_H
#define SOQT_COLLISIONVIEWER_H

#include <Inventor/SbBasic.h>

#include <Inventor/Qt/SoQtBasic.h>

class SoQtViewer;
class SoQtCollisionViewer;

// NULL is not defined under msvc++ unless you include 'windows.h'
#ifndef NULL
#define NULL ((void *) 0L)
#endif

typedef void SoQtCollisionViewerCB( void * userData, SoQtCollisionViewer * collisionViewer );

// ************************************************************************

class SOQT_DLL_API  SoQtCollisionViewer {
public:
  SoQtCollisionViewer( SoQtViewer * viewer );
  ~SoQtCollisionViewer(void);

  SoQtViewer * getViewer(void);

  void setDistance( float distance );
  float getDistance(void);
  
  void setNumSteps( int numSteps );
  int getNumSteps(void);
  
  void setCollisionDetection( SbBool value = TRUE );
  SbBool getCollisionDetection(void);
  
  void setZBufferOptimization( SbBool value = TRUE );
  SbBool getZBufferOptimization(void);
  
  void addCallback( SoQtCollisionViewerCB * func, void * user = NULL );
  void removeCallback( SoQtCollisionViewerCB * func, void * user = NULL );

private:

}; // class SoQtCollisionViewer

// ************************************************************************

#endif // ! SOQT_COLLISIONVIEWER_H
