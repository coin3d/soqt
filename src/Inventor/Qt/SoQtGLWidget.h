/**************************************************************************\
 *
 *  Copyright (C) 1998-1999 by Systems in Motion.  All rights reserved.
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
\**************************************************************************/

//  $Id$

#ifndef SOQT_GLWIDGET_H
#define SOQT_GLWIDGET_H

#include <qgl.h>

#include <Inventor/SbBasic.h>

#include <Inventor/Qt/SoQtComponent.h>

class QtGLArea;

enum GLModes {        // remove the GLX ones?
  SO_GL_RGB      = 0x01, SO_GLX_RGB      = SO_GL_RGB,
  SO_GL_DOUBLE   = 0x02, SO_GLX_DOUBLE   = SO_GL_DOUBLE,
  SO_GL_ZBUFFER  = 0x04, SO_GLX_ZBUFFER  = SO_GL_ZBUFFER,
  SO_GL_OVERLAY  = 0x08, SO_GLX_OVERLAY  = SO_GL_OVERLAY,
  SO_GL_STEREO   = 0x10, SO_GLX_STEREO   = SO_GL_STEREO
};

// *************************************************************************

class SoQtGLWidget : public SoQtComponent
{
  typedef SoQtComponent inherited;

  Q_OBJECT

public:
  void setBorder( const SbBool enable );
  SbBool isBorder(void) const;

  virtual void setDoubleBuffer( const SbBool enable );
  SbBool isDoubleBuffer(void) const;

  void setDrawToFrontBufferEnable( const SbBool enable );
  SbBool isDrawToFrontBufferEnable(void) const;

protected:
  SoQtGLWidget( QWidget * const parent = NULL, const char * const name = NULL,
      const SbBool inParent = TRUE, const int glModes = SO_GLX_RGB,
      const SbBool build = TRUE );

  virtual void processEvent( QEvent * event );

  QWidget * buildWidget( QWidget * parent );

  QtGLArea * getQtGLArea(void);

  virtual void redraw(void) = 0;

  virtual void sizeChanged( const SbVec2s size );
  virtual void widgetChanged(void);

  void setGlxSize( const SbVec2s size );
  void setGLSize( const SbVec2s size );
  SbVec2s getGlxSize(void) const;
  SbVec2s getGLSize(void) const;
  float getGlxAspectRatio(void) const;
  float getGLAspectRatio(void) const;

  SbBool drawToFrontBuffer;

  virtual bool eventFilter( QObject * obj, QEvent * e );

  int glLockLevel;
  void glLock(void);
  void glUnlock(void);
  void glSwapBuffers(void);
  void glFlushBuffer(void);

  virtual void glInit(void);
  virtual void glReshape( int width, int height );
  virtual void glRender(void);

private slots:
  void gl_init(void);
  void gl_reshape(int, int);
  void gl_render(void);

private:
  QtGLArea * glwidget;
  QWidget * glparent, * borderwidget;
  int borderthickness, glmodebits;

  struct {
    unsigned int mouseinput    : 1;
    unsigned int keyboardinput : 1;
    unsigned int drawfrontbuff : 1;
  } properties;

}; // class SoQtGLWidget

// *************************************************************************

#endif // ! SOQT_GLWIDGET_H
