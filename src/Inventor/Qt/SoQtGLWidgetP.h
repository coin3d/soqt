#ifndef SOQTGLWIDGETP_H
#define SOQTGLWIDGETP_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) by Kongsberg Oil & Gas Technologies.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Kongsberg Oil & Gas Technologies
 *  about acquiring a Coin Professional Edition License.
 *
 *  See http://www.coin3d.org/ for more information.
 *
 *  Kongsberg Oil & Gas Technologies, Bygdoy Alle 5, 0257 Oslo, NORWAY.
 *  http://www.sim.no/  sales@sim.no  coin-support@coin3d.org
 *
\**************************************************************************/

#ifndef SOQT_INTERNAL
#error this is a private header file
#endif /* !SOQT_INTERNAL */

// *************************************************************************

#include <qobject.h>

#include <Inventor/Qt/SoGuiGLWidgetP.h>
#include <Inventor/SbLinear.h>

class QKeyEvent;

// ************************************************************************

// This class contains private data and methods used within the
// SoQtGLWidget class.

class SoQtGLWidgetP : public QObject, public SoGuiGLWidgetP
{
  Q_OBJECT

public:
  SoQtGLWidgetP(SoQtGLWidget * publ);
  ~SoQtGLWidgetP();

  static void GLAreaKeyEvent(QKeyEvent * e, void * userdata);
  void buildGLWidget(void);
  virtual bool eventFilter(QObject * obj, QEvent * e);
  static void eventHandler(QWidget *, void *, QEvent *, bool *);

  const class QGLContext * getNormalContext(void);
  const class QGLContext * getOverlayContext(void);

  SbVec2s glSize;
  SbBool wasresized;
  const QGLContext * oldcontext;

  class SoQtGLArea * currentglwidget;
  class SoQtGLArea * previousglwidget;
  QWidget * glparent;
  class QFrame * borderwidget;
  int borderthickness;
  class QGLFormat * glformat;

public slots:
  void gl_init(void);
  void gl_reshape(int, int);
  void gl_exposed(void);

protected:
  virtual SbBool isDirectRendering(void);
};

// ************************************************************************

#endif // !SOQTGLWIDGETP_H
