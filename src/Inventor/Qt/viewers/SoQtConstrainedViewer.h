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
