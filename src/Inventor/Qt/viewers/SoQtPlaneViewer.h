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

#ifndef SOQT_PLANEVIEWER_H
#define SOQT_PLANEVIEWER_H

class QPushButton;
class QPixmap;
class SbPlaneProjector;
class SoAnyPlaneViewer;

#include <Inventor/Qt/viewers/SoQtFullViewer.h>

// ************************************************************************

class SOQT_DLL_API SoQtPlaneViewer : public SoQtFullViewer {
  SOQT_OBJECT_HEADER(SoQtPlaneViewer, SoQtFullViewer);
  friend class SoAnyPlaneViewer;
  Q_OBJECT

public:
  SoQtPlaneViewer(
    QWidget * parent = NULL,
    const char * const name = NULL, 
    SbBool embed = TRUE, 
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
    SbBool embed, 
    SoQtFullViewer::BuildFlag flag, 
    SoQtViewer::Type type, 
    SbBool build );

  QWidget * buildWidget( QWidget * parent );

  virtual const char * getDefaultWidgetName(void) const;
  virtual const char * getDefaultTitle(void) const;
  virtual const char * getDefaultIconTitle(void) const;

  virtual SbBool processSoEvent( const SoEvent * const event );
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

  SoAnyPlaneViewer * const common;

private slots:
  void xClicked(void);
  void yClicked(void);
  void zClicked(void);
  void cameraToggleClicked(void);

}; // class SoQtPlaneViewer

// ************************************************************************

#endif // ! SOQT_PLANEVIEWER_H
