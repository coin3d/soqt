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

//  $Id$

#ifndef SOQT_COLLISIONVIEWER_H
#define SOQT_COLLISIONVIEWER_H

#include <Inventor/SbBasic.h>

class SoQtViewer;

typedef void SoQtCollisionViewerCB( void * userData,
                                    SoQtCollisionViewer * collisionViewer );

// ************************************************************************

class SoQtCollisionViewer {
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
