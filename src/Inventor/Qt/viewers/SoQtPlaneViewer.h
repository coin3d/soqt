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

#ifndef __SOQT_PLANEVIEWER_H__
#define __SOQT_PLANEVIEWER_H__

class SbPlaneProjector;

#include <Inventor/Qt/viewers/SoQtFullViewer.h>

// ************************************************************************

class SoQtPlaneViewer : public SoQtFullViewer {
  typedef SoQtFullViewer inherited;

  Q_OBJECT

public:
  SoQtPlaneViewer(
    QWidget * parent = NULL,
    const char * const name = NULL, 
    SbBool buildInsideParent = TRUE, 
    SoQtFullViewer::BuildFlag flag = BUILD_ALL, 
    SoQtViewer::Type type = BROWSER );
  ~SoQtPlaneViewer(void);

  virtual void setViewing( SbBool enable );
  virtual void setCamera( SoCamera * camera );
  virtual void setCursorEnabled( SbBool enable );

protected:
  SoQtPlaneViewer(
    QWidget * parent,
    const char * const name, 
    SbBool buildInsideParent, 
    SoQtFullViewer::BuildFlag flag, 
    SoQtViewer::Type type, 
    SbBool buildNow );

  QWidget * buildWidget( QWidget * parent );

  virtual const char * getDefaultWidgetName(void) const;
  virtual const char * getDefaultTitle(void) const;
  virtual const char * getDefaultIconTitle(void) const;

  virtual void processEvent( QEvent * event );
  virtual void setSeekMode( SbBool enable );
  virtual void actualRedraw(void);

  virtual void bottomWheelMotion( float value );
  virtual void leftWheelMotion( float value );
  virtual void rightWheelMotion( float value );

  virtual void createPrefSheet(void);

  virtual void createViewerButtons( QWidget * parent );
  virtual void openViewerHelpCard(void);
  virtual void computeSeekFinalOrientation(void);

private:
  void constructor( SbBool buildNow );

  void zoom( const float difference );

  int planeViewerMode;
  SbVec2f prevMousePosition;

  SbPlaneProjector * projector;

}; // class SoQtPlaneViewer

// ************************************************************************

#endif // ! __SOQT_PLANEVIEWER_H__
