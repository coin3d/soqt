/**************************************************************************\
 *
 *  Copyright (C) 1998-2000 by Systems in Motion.  All rights reserved.
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

static const char rcsid[] =
  "$Id$";

// This class' purpose is to overload the Qt OpenGL widget, so we can
// do our own initialization and event handling on resizes and expose
// events.

#include <assert.h>
#include <config.h>
#include <Inventor/Qt/widgets/SoQtGLArea.h>

#if SOQT_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // SOQT_DEBUG

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

SoQtGLArea::SoQtGLArea(
  QGLFormat * const format,
  QWidget * const parent,
  const char * const name )
: inherited( *format, parent, name, 0x0, WResizeNoErase )
{
#if HAVE_QGLWIDGET_SETAUTOBUFFERSWAP
  // We'll handle the OpenGL buffer swapping ourselves, to support the
  // different combinations of rendering options (doublebuffer with
  // the "DrawToFront" flag is for instance hard to do within the
  // QGLWidget model).
  this->setAutoBufferSwap( FALSE );
#endif // HAVE_QGLWIDGET_SETAUTOBUFFERSWAP
} // SoQtGLArea()

SoQtGLArea::~SoQtGLArea(
  void )
{
} // ~SoQtGLArea()

/*
  Overloaded from QGLWidget to emit a signal.
*/

void
SoQtGLArea::initializeGL(
  void )
{
  SOQT_GLAREA_DEBUG_START(initializeGL);
  this->setBackgroundMode(QWidget::NoBackground); // Avoid unnecessary flicker.
  emit this->init_sig();
  SOQT_GLAREA_DEBUG_DONE(initializeGL);
} // initializeGL()

/*
  Overloaded from QtGLWidget to emit a signal.
*/

void
SoQtGLArea::resizeGL(
  int width,
  int height )
{
  SOQT_GLAREA_DEBUG_START(resizeGL);
  emit this->reshape_sig( width, height );
  SOQT_GLAREA_DEBUG_DONE(resizeGL);
} // resizeGL()

/*
  Emit a signal whenever we need to repaint because of an expose event.
*/

void
SoQtGLArea::paintGL(
  void )
{
  SOQT_GLAREA_DEBUG_START(paintGL);
  emit this->expose_sig();
  SOQT_GLAREA_DEBUG_DONE(paintGL);
} // paintGL()

// *************************************************************************
