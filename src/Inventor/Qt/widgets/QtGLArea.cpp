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

/*!
  \class QtGLArea QtGLArea.h
  \brief The QtGLArea class is an internal class for managing an OpenGL canvas.
  \internal

  It's purpose was to maek a GL widget that was totally manageable through
  signals and slots, that doesn't need to be overloaded.
*/

#include <assert.h>

#include <Inventor/Qt/widgets/QtGLArea.h>

// *************************************************************************

/*!
  Constructor.
*/

QtGLArea::QtGLArea(
  QWidget * const parent,
  const char * const name)
: inherited( parent, name )
, dorender( true )
{
  this->owner = owner;
} // QtGLArea()

/*!
  The destructor.
*/

QtGLArea::~QtGLArea(
  void )
{
} // ~QtGLArea()

/*
  Set/unset flag to actually do render the scene upon paintGL() events.
  Useful for postponing render actions during resizes etc.
*/

void
QtGLArea::doRender(
  bool flag )
{
  this->dorender = flag;
} // doRender()

/*
  Overloaded from QtGLWidget.
*/

void
QtGLArea::initializeGL(
  void )
{
  inherited::initializeGL();
  this->setBackgroundMode(QWidget::NoBackground);
  this->setBackgroundColor(QColor(0,0,0));
  this->makeCurrent();

  // Need to call this explicitly, as it seems to have been forgotten
  // in Open Inventor.
  glEnable(GL_DEPTH_TEST);
} // initializeGL()

/*
  Overloaded from QtGLWidget.
*/

void
QtGLArea::resizeGL(
  int width,
  int height )
{
#if 0 // debug
  SoDebugError::postInfo("PrivateGLWidget::resizeGL", "start");
#endif // debug
  inherited::resizeGL(w, h);
#if 0 // debug
  SoDebugError::postInfo("PrivateGLWidget::resizeGL", "done");
#endif // debug
} // resizeGL()

/*
  Emit a signal whenever we need to repaint (usually (always?) because
  of expose events).
*/

void
QtGLArea::paintGL(
  void )
{
#if 0 // debug
  SoDebugError::postInfo("PrivateGLWidget::paintGL", "%s",
                         this->dorender ? "executing" : "ignoring");
#endif //debug
  if (this->dorender) {
    inherited::paintGL();
    emit this->do_repaint();
  }
} // paintGL()

/*
  We need to overload QGLWidget::swapBuffers() like this to be able to
  heed the *DrawToFrontBufferEnable() setting.
*/

void
QtGLArea::swapBuffers(
  void )
{
  if (this->owner->drawToFrontBuffer) {
    // FIXME: need some OpenGL trickery here to be able to draw to the
    // front buffer of a double buffered GL widget. 990209 mortene.
    inherited::swapBuffers(); // tmp hack
  } else {
    inherited::swapBuffers();
  }

  this->owner->drawToFrontBuffer = FALSE;
} // swapBuffers()

// *************************************************************************
