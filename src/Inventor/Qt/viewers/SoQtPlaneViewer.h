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

#ifndef SOQT_PLANEVIEWER_H
#define SOQT_PLANEVIEWER_H

class SbPlaneProjector;

class QPushButton;
class QPixmap;

#ifndef __SOQT_FULLVIEWER_H__
#include <Inventor/Qt/viewers/SoQtFullViewer.h>
#endif // ! __SOQT_FULLVIEWER_H__

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

  virtual void createViewerButtons( QWidget * parent, SbPList * buttons );
  virtual void openViewerHelpCard(void);
  virtual void computeSeekFinalOrientation(void);

private:
  void constructor( SbBool buildNow );

  void zoom( const float difference );

  enum PlaneViewerMode {
    IDLE_MODE,

    DOLLY_MODE,
    TRANSLATE_MODE,

    ROTZ_WAIT_MODE,
    ROTZ_MODE,

    SEEK_WAIT_MODE,
    SEEK_MODE
  } mode;

  void setModeFromState( unsigned int state );
  void setMode( PlaneViewerMode mode );

  SbVec2f prevMousePosition;

  SbPlaneProjector * projector;

  struct {
    QPushButton * x, * y, * z;
    QPushButton * camera;
  } buttons;

  struct {
    QPixmap * orthogonal, * perspective;
  } pixmaps;

  static void visibilityCB( void * data, SbBool visible );

private slots:
  void xClicked(void);
  void yClicked(void);
  void zClicked(void);
  void cameraToggleClicked(void);

}; // class SoQtPlaneViewer

// ************************************************************************

#endif // ! SOQT_PLANEVIEWER_H
