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

//  $Id$

#ifndef SOQT_CONSTRAINEDVIEWER_H
#define SOQT_CONSTRAINEDVIEWER_H

#include <Inventor/Qt/viewers/SoQtFullViewer.h>

// ************************************************************************

class SOQT_DLL_EXPORT SoQtConstrainedViewer : public SoQtFullViewer {
  typedef SoQtFullViewer inherited;

  Q_OBJECT

public:
  void setUpDirection( const SbVec3f & upDirection );
  const SbVec3f & getUpDirection(void);

  virtual void setCamera( SoCamera * newCamera );
  virtual void saveHomePosition(void);
  virtual void resetToHomePosition(void);
  virtual void recomputeSceneSize(void);

protected:
  SoQtConstrainedViewer(
    QWidget * parent,
    const char * const name,
    SbBool embed,
    SoQtFullViewer::BuildFlag flag, 
    SoQtViewer::Type type, 
    SbBool build );

  ~SoQtConstrainedViewer(void);

  SbVec3f upVector;
//  float sceneHeight;
  
  virtual void tiltCamera( float delta );
  virtual void bottomWheelMotion( float value );
  virtual void leftWheelMotion( float value );

  virtual void changeCameraValues( SoCamera * camera );
  void findUpDirection( SbVec2s mouseLocation );
  void checkForCameraUpConstrain(void);
  virtual void computeSeekFinalOrientation(void);

}; // class SoQtConstrainedViewer

// ************************************************************************

#endif // ! SOQT_CONSTRAINEDVIEWER_H
