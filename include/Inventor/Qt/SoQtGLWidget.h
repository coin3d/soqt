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
 *  http://www.sim.no/ sales@sim.no Voice: +47 73540378 Fax: +47 73943861
 *
\**************************************************************************/

#ifndef __SOQTGLWIDGET_H__
#define __SOQTGLWIDGET_H__

#include <qgl.h>
#include <Inventor/Qt/SoQtComponent.h>
#include <Inventor/SbBasic.h>

#define SO_GLX_RGB	0x01
#define SO_GLX_DOUBLE	0x02
#define SO_GLX_ZBUFFER	0x04
#define SO_GLX_OVERLAY	0x08
#define SO_GLX_STEREO	0x10


// FIXME: should move PrivateGLWidget definition inside the .cpp-file?
// (=> moc-trouble?)  990209 mortene.

/* internal class start ****************************************************/

class SoQtGLWidget;

class PrivateGLWidget : public QGLWidget
{
  Q_OBJECT

  typedef QGLWidget inherited;

public:
  PrivateGLWidget(SoQtGLWidget * owner,
		  QWidget *parent, const char * const name);

  virtual void swapBuffers(void);

signals:
  void do_repaint();

protected:
  virtual void paintGL(void);
  virtual void initializeGL(void);

private:
  SoQtGLWidget * owner;
};

/* internal class end ******************************************************/


/***********************************************************************/

class SoQtGLWidget : public SoQtComponent
{
  friend PrivateGLWidget; // necessary because of protected drawToFrontBuffer
  typedef SoQtComponent inherited;

  Q_OBJECT

public:
  void setBorder(const SbBool enable);
  SbBool isBorder(void) const;

  virtual void setDoubleBuffer(const SbBool enable);
  SbBool isDoubleBuffer(void) const;

  void setDrawToFrontBufferEnable(const SbBool enable);
  SbBool isDrawToFrontBufferEnable(void) const;

protected:
  SoQtGLWidget(QWidget * const parent = NULL,
	       const char * const name = NULL, 
	       const SbBool buildInsideParent = TRUE, 
	       const int glModes = SO_GLX_RGB, 
	       const SbBool buildNow = TRUE);

  virtual void processEvent(QEvent * anyevent);

  QWidget * buildWidget(QWidget * parent);

  QGLWidget * getQGLWidget(void);

  virtual void redraw(void) = 0;

  virtual void sizeChanged(const SbVec2s & newSize);
  virtual void widgetChanged(void);

  void setGlxSize(SbVec2s newSize);
  const SbVec2s getGlxSize(void) const;
  float getGlxAspectRatio(void) const;

  SbBool drawToFrontBuffer;

  virtual bool eventFilter(QObject *obj, QEvent * e);

private slots:
  void repaint_slot();

private:  
  QGLWidget * glwidget;
  QWidget * glparent, * borderwidget;
  int borderthickness, glmodebits;

  struct {
    unsigned int mouseinput    : 1;
    unsigned int keyboardinput : 1;
    unsigned int drawfrontbuff : 1;
  } properties;
};

#endif // !__SOQTGLWIDGET_H__
