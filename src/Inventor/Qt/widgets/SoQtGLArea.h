/**************************************************************************\
 *
 *  This file is part of the Coin GUI toolkit libraries.
 *  Copyright (C) 1998-2002 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  version 2.1 as published by the Free Software Foundation.  See the
 *  file LICENSE.LGPL at the root directory of this source distribution
 *  for more details.
 *
 *  If you want to use this library with software that is incompatible
 *  licensewise with the LGPL, and / or you would like to take
 *  advantage of the additional benefits with regard to our support
 *  services, please contact Systems in Motion about acquiring a Coin
 *  Professional Edition License.  See <URL:http://www.coin3d.org> for
 *  more information.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  <URL:http://www.sim.no>, <mailto:support@sim.no>
 *
\**************************************************************************/

#ifndef SOQT_GLAREA_H
#define SOQT_GLAREA_H

#include <qgl.h>

#include <Inventor/Qt/SoQtBasic.h>


typedef void GLAreaKeyHandler(QKeyEvent * ke, void * userdata);

// *************************************************************************

class SoQtGLArea : public QGLWidget {
  typedef QGLWidget inherited;
  Q_OBJECT

public:
  SoQtGLArea(QGLFormat * const format, QWidget * const parent,
             const QGLWidget * sharewidget,
             const char * const name = "QtGLArea");
  ~SoQtGLArea();

  void registerQKeyEventHandler(GLAreaKeyHandler * cb, void * userdata)
  {
    this->keycb = cb;
    this->keycbuserdata = userdata;
  }

signals:
  void init_sig(void);
  void reshape_sig(int, int);
  void expose_sig(void);

protected:
  virtual void paintGL(void);
  virtual void resizeGL(int width, int height);
  virtual void initializeGL(void);

  virtual void focusInEvent(QFocusEvent * e);
  virtual void focusOutEvent(QFocusEvent * e);
  virtual bool event(QEvent * e);

private:
  GLAreaKeyHandler * keycb;
  void * keycbuserdata;
};

// *************************************************************************

#endif // ! SOQT_GLAREA_H
