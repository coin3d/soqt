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

//  $Id$

#ifndef SOQT_GLAREA_H
#define SOQT_GLAREA_H

#include <qgl.h>

#include <Inventor/Qt/SoQtBasic.h>

// *************************************************************************

class SOQT_DLL_EXPORT SoQtGLArea : public QGLWidget {
  typedef QGLWidget inherited;
  Q_OBJECT

public:
  SoQtGLArea( QGLFormat * const format, QWidget * const parent,
    const char * const name = "QtGLArea" );
  ~SoQtGLArea(void);

signals:
  void init_sig(void);
  void reshape_sig(int, int);
  void expose_sig(void);

protected:
  virtual void paintGL(void);
  virtual void resizeGL( int width, int height );
  virtual void initializeGL(void);

}; // class SoQtGLArea

// *************************************************************************

#endif // ! SOQT_GLAREA_H
