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

#ifndef SOQT_WALKVIEWER_H
#define SOQT_WALKVIEWER_H

#include <Inventor/Qt/viewers/SoQtConstrainedViewer.h>

// ************************************************************************

class SOQT_DLL_EXPORT SoQtWalkViewer : public SoQtConstrainedViewer {
  typedef SoQtConstrainedViewer inherited;

  Q_OBJECT

public:
  SoQtWalkViewer(
    QWidget * parent = NULL,
    const char * name = NULL,
    SbBool embed = TRUE,
    SoQtFullViewer::BuildFlag flag = BUILD_ALL,
    SoQtViewer::Type type = BROWSER );
  ~SoQtWalkViewer(void);

  virtual void setViewing( SbBool enable );
  virtual void setCamera( SoCamera * camera );
  virtual void setCursorEnabled( SbBool enable );

  virtual void setCameraType( SoType type );

protected:
  SoQtWalkViewer(
    QWidget * parent,
    const char * name,
    SbBool embed,
    SoQtFullViewer::BuildFlag flag,
    SoQtViewer::Type type,
    SbBool build );

  virtual const char * getDefaultWidgetName(void) const;
  virtual const char * getDefaultTitle(void) const;
  virtual const char * getDefaultIconTitle(void) const;

  virtual void processEvent( QEvent * event );
  virtual void setSeekMode( SbBool enable );
  virtual void actualRedraw(void);

  virtual void rightWheelMotion( float value );

  virtual QWidget * buildLeftTrim( QWidget * parent );

  virtual void createPrefSheet(void);
  virtual void openViewerHelpCard(void);

}; // class SoQtWalkViewer

// ************************************************************************

#endif // ! SOQT_WALKVIEWER_H
