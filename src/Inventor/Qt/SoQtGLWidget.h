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

#ifndef SOQT_GLWIDGET_H
#define SOQT_GLWIDGET_H

#include <qgl.h>

#include <Inventor/SbBasic.h>

#include <Inventor/Qt/SoQtBasic.h>
#include <Inventor/Qt/SoQtComponent.h>

class SoQtGLArea;
class QFrame;

enum GLModes {
  SO_GL_RGB      = 0x01, SO_GLX_RGB      = SO_GL_RGB,
  SO_GL_DOUBLE   = 0x02, SO_GLX_DOUBLE   = SO_GL_DOUBLE,
  SO_GL_ZBUFFER  = 0x04, SO_GLX_ZBUFFER  = SO_GL_ZBUFFER,
  SO_GL_OVERLAY  = 0x08, SO_GLX_OVERLAY  = SO_GL_OVERLAY,
  SO_GL_STEREO   = 0x10, SO_GLX_STEREO   = SO_GL_STEREO,
  SO_GL_DEFAULT_MODE =
    (SO_GL_RGB | SO_GL_ZBUFFER | SO_GL_DOUBLE | SO_GL_OVERLAY)
};

// *************************************************************************

class SOQT_DLL_API SoQtGLWidget : public SoQtComponent {
  SOQT_OBJECT_ABSTRACT_HEADER(SoQtGLWidget, SoQtComponent);
  Q_OBJECT

public:
  void setBorder( const SbBool enable );
  SbBool isBorder(void) const;

  virtual void setDoubleBuffer( const SbBool enable );
  SbBool isDoubleBuffer(void) const;

  void setDrawToFrontBufferEnable( const SbBool enable );
  SbBool isDrawToFrontBufferEnable(void) const;
  
  void setQuadBufferStereo( const SbBool enable );
  SbBool isQuadBufferStereo(void) const;

  QWidget * getNormalWidget(void) const;
  QWidget * getOverlayWidget(void) const;

protected:
  SoQtGLWidget(
    QWidget * const parent = NULL,
    const char * const name = NULL,
    const SbBool embed = TRUE,
    const int glmodes = SO_GL_RGB,
    const SbBool build = TRUE );
  ~SoQtGLWidget(void);

  virtual void processEvent( QEvent * event );

  QWidget * buildWidget( QWidget * parent );

  QWidget * getGLWidget(void);

  virtual void redraw(void) = 0;

  virtual void sizeChanged( const SbVec2s size );
  virtual void widgetChanged( QWidget * w );

  void setGLSize( const SbVec2s size );
  SbVec2s getGLSize(void) const;
  float getGLAspectRatio(void) const;

  // old aliases
  void setGlxSize( const SbVec2s size ) { setGLSize( size ); }
  SbVec2s getGlxSize(void) const { return getGLSize(); }
  float getGlxAspectRatio(void) const { return getGLAspectRatio(); }

  SbBool waitForExpose;
  SbBool drawToFrontBuffer;

  virtual bool eventFilter( QObject * obj, QEvent * e );
  static void eventHandler( QWidget *, void *, QEvent *, bool * );

  void glLock(void);
  void glUnlock(void);
  void glSwapBuffers(void);
  void glFlushBuffer(void);

  void setOverlayRender( const SbBool enable );
  SbBool isOverlayRender(void) const;

  virtual void glInit(void);
  virtual void glReshape( int width, int height );
  virtual void glRender(void);

private slots:
  void gl_init(void);
  void gl_reshape(int, int);
  void gl_exposed(void);

private:
  class SoQtGLWidgetP * pimpl;
  void buildGLWidget(void);

}; // class SoQtGLWidget

// *************************************************************************

#endif // ! SOQT_GLWIDGET_H
