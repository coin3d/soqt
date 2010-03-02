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

// This class' purpose is to overload the Qt OpenGL widget, so we can
// do our own initialization and event handling on resizes and expose
// events.

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H
#include <qt-config.h>

#include <assert.h>

#include <qmetaobject.h>
#include <qnamespace.h>
#include <qevent.h>

#include <Inventor/errors/SoDebugError.h>

#include <Inventor/Qt/widgets/SoQtGLArea.h>
#include <Inventor/Qt/widgets/moc_SoQtGLArea.icc>
#include <soqtdefs.h>

// ************************************************************************

// Take care of namespace incompatibilities between Qt 3 and Qt 4.

#if QT_VERSION < 0x040000 // pre Qt 4
#define QTWIDGET_STRONGFOCUS QWidget::StrongFocus
#else // Qt 4.0.0+
#define QTWIDGET_STRONGFOCUS Qt::StrongFocus
#endif // Qt 4.0.0+

// *************************************************************************

#if SOQT_DEBUG && 0 // switch 0<->1 to toggle debugging info on/off

#define SOQT_GLAREA_DEBUG_INFO(_funcname_, _infostr_) \
  do { \
    SbString s("SoQtGLArea::"); \
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
#if QT_VERSION >= 0x040000
   : inherited(*format, parent, sharewidget)
#else
   : inherited(*format, parent, NULL, sharewidget, Qt::WResizeNoErase)
#endif
{
#if QT_VERSION >= 0x040000
  this->setObjectName(name);
#else
  this->setName(name);
#endif
#if HAVE_QGLWIDGET_SETAUTOBUFFERSWAP
  // We'll handle the OpenGL buffer swapping ourselves, to support the
  // different combinations of rendering options (doublebuffer with
  // the "DrawToFront" flag is for instance hard to do within the
  // QGLWidget model).
  this->setAutoBufferSwap(FALSE);
#endif // HAVE_QGLWIDGET_SETAUTOBUFFERSWAP

  this->keycb = NULL;
  this->setFocusPolicy(QTWIDGET_STRONGFOCUS);
}

SoQtGLArea::~SoQtGLArea()
{
}

// Overridden from QGLWidget to emit a signal.
void
SoQtGLArea::initializeGL(void)
{
  SOQT_GLAREA_DEBUG_START(initializeGL);
  emit this->init_sig();
  SOQT_GLAREA_DEBUG_DONE(initializeGL);
}

// Overridden from QtGLWidget to emit a signal.
void
SoQtGLArea::resizeGL(int width, int height)
{
  SOQT_GLAREA_DEBUG_START(resizeGL);
  emit this->reshape_sig(width, height);
  SOQT_GLAREA_DEBUG_DONE(resizeGL);
}

// Overridden from QtGLWidget. Emit a signal whenever we need to
// repaint because of an expose event.
void
SoQtGLArea::paintGL(void)
{
  SOQT_GLAREA_DEBUG_START(paintGL);
  emit this->expose_sig();
  SOQT_GLAREA_DEBUG_DONE(paintGL);
}

// Overridden from QWidget to avoid update() being called when we
// enable another focuspolicy than QWidget::NoFocus.
void
SoQtGLArea::focusInEvent(QFocusEvent * e)
{
  // Here's what the QWidget implementation of this method does:

//     if ( focusPolicy() != NoFocus || !isTopLevel() ) {
//        update();
//        if ( testWState(WState_AutoMask) )
//            updateMask();
//        setMicroFocusHint(width()/2, 0, 1, height(), FALSE);
//     }

  // QWidget::update() calls repaint(), which causes paintGL() to be
  // invoked on all focus-in and focus-out events.
}

// See doc on focusInEvent() above.
void
SoQtGLArea::focusOutEvent(QFocusEvent * e)
{
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

  // The following is a workaround for what may be a Qt bug (or at
  // least very peculiar behavior).
  //
  // In a Qt MDI application, with multiple windows, each containing a
  // SoQtExaminerViewer, use of the mousewheel over a viewer that
  // doesn't have the focus causes wheel events to end up in both the
  // viewer under the mouse and the viewer that has the focus.
  //
  // Our workaround is thus to ignore a wheel event when the widget
  // doesn't have the focus.
  //
  // Problem found with Win2000 and Qt 3.3.2.
  if (e->type() == QEvent::Wheel && ! this->hasFocus()) { return FALSE; }

  return QGLWidget::event(e);
}

// *************************************************************************
