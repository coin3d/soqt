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

#ifndef SOQT_FLYVIEWER_H
#define SOQT_FLYVIEWER_H

#include <Inventor/Qt/viewers/SoQtConstrainedViewer.h>

// ************************************************************************

class SoQtFlyViewer : public SoQtConstrainedViewer {
  typedef SoQtConstrainedViewer inherited;

  Q_OBJECT

public:
  SoQtFlyViewer(
    QWidget * parent,
    const char *name = NULL, 
    SbBool buildInsideParent = TRUE, 
    SoQtFullViewer::BuildFlag flag = BUILD_ALL,
    SoQtViewer::Type type = BROWSER );
  ~SoQtFlyViewer(void);

  virtual void setViewing( SbBool enable );
  virtual void resetToHomePosition(void);
  virtual void setCamera( SoCamera * camera );
  virtual void setCursorEnabled( SbBool enable );
  virtual void setCameraType( SoType type );

protected:
  SoQtFlyViewer(
    QWidget * parent,
    const char * const name, 
    SbBool buildInsideParent, 
    SoQtFullViewer::BuildFlag flag, 
    SoQtViewer::Type type, 
    SbBool buildNow );

  virtual const char * getDefaultWidgetName(void) const;
  virtual const char * getDefaultTitle(void) const;
  virtual const char * getDefaultIconTitle(void) const;

  virtual void processEvent( QEvent * event );
  virtual void setSeekMode( SbBool enable );
  virtual void actualRedraw(void);

  virtual void rightWheelMotion( float value );

  virtual void createPrefSheet(void);
  virtual void openViewerHelpCard(void);

}; // class SoQtFlyViewer

// ************************************************************************

#endif // ! SOQT_FLYVIEWER_H
