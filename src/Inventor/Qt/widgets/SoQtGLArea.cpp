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

#if SOQT_DEBUG
static const char rcsid[] =
  "$Id$";
#endif // SOQT_DEBUG

// This class' purpose is to overload the Qt OpenGL widget, so we can
// do our own initialization and event handling on resizes and expose
// events.

#include <assert.h>
#if HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include <qmetaobject.h>
#include <moc_SoQtGLArea.cpp>

#if SOQT_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // SOQT_DEBUG

#include <soqtdefs.h>
#include <Inventor/Qt/widgets/SoQtGLArea.h>

// *************************************************************************

#if SOQT_DEBUG && 0 // switch 0<->1 to toggle debugging info on/off

#define SOQT_GLAREA_DEBUG_INFO(_funcname_, _infostr_) \
  do { \
    SbString s("QtGLArea::"); \
    s += SO__QUOTE(_funcname_); \
    SoDebugError::postInfo(s.getString(), _infostr_); \
  } while (0)

#define SOQT_GLAREA_DEBUG_START(_funcname_)  SOQT_GLAREA_DEBUG_INFO(_funcname_, "start")
#define SOQT_GLAREA_DEBUG_DONE(_funcname_)  SOQT_GLAREA_DEBUG_INFO(_funcname_, "done")

#else // !debug

#define SOQT_GLAREA_DEBUG_START(_funcname_)
#define SOQT_GLAREA_DEBUG_DONE(_funcname_)

#endif // !debug

// *************************************************************************

SoQtGLArea::SoQtGLArea(QGLFormat * const format,
                       QWidget * const parent,
                       const QGLWidget * sharewidget,
                       const char * const name)
  // The 3rd argument is supposed to be the widget name, but when
  // running on QGL v4.30 and Qt v2.1.0 application code will crash on
  // exit under freak conditions -- see Bugzilla #264. 20001120 mortene.
  : inherited(*format, parent, NULL, sharewidget, WResizeNoErase)
{
#if HAVE_QGLWIDGET_SETAUTOBUFFERSWAP
  // We'll handle the OpenGL buffer swapping ourselves, to support the
  // different combinations of rendering options (doublebuffer with
  // the "DrawToFront" flag is for instance hard to do within the
  // QGLWidget model).
  this->setAutoBufferSwap(FALSE);
#endif // HAVE_QGLWIDGET_SETAUTOBUFFERSWAP

  this->keycb = NULL;
  this->setFocusPolicy(QWidget::StrongFocus);
}

SoQtGLArea::~SoQtGLArea()
{
}

/*
  Overloaded from QGLWidget to emit a signal.
*/
void
SoQtGLArea::initializeGL(void)
{
  SOQT_GLAREA_DEBUG_START(initializeGL);
  this->setBackgroundMode(QWidget::NoBackground); // Avoid unnecessary flicker.
  emit this->init_sig();
  SOQT_GLAREA_DEBUG_DONE(initializeGL);
}

/*
  Overloaded from QtGLWidget to emit a signal.
*/
void
SoQtGLArea::resizeGL(int width, int height)
{
  SOQT_GLAREA_DEBUG_START(resizeGL);
  emit this->reshape_sig(width, height);
  SOQT_GLAREA_DEBUG_DONE(resizeGL);
}

/*
  Emit a signal whenever we need to repaint because of an expose event.
*/
void
SoQtGLArea::paintGL(void)
{
  SOQT_GLAREA_DEBUG_START(paintGL);
  emit this->expose_sig();
  SOQT_GLAREA_DEBUG_DONE(paintGL);
}

// *************************************************************************

bool
SoQtGLArea::event(QEvent * e)
{
  if ((e->type() == QEvent::KeyPress) || (e->type() == QEvent::KeyRelease)) {
    if (this->keycb) {
      QKeyEvent * ke = (QKeyEvent *)e;
      this->keycb(ke, this->keycbuserdata);
      ke->accept();
      return TRUE;
    }
  }

  QGLWidget::event(e);
}

// *************************************************************************
