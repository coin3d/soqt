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

// FIXME: get rid of this before 1.0 release by converting everything
// to Qt version 2.x API? 19990630 mortene.
#include <qevent.h>
#include <qframe.h>
#if QT_VERSION >= 200
#include <q1xcompatibility.h>
#endif // Qt v2.x

#include <Inventor/errors/SoDebugError.h>
#include <Inventor/misc/SoBasic.h>

#include <soqtdefs.h>
#include <Inventor/Qt/SoQtBasic.h>
#include <Inventor/Qt/widgets/SoQtGLArea.h>
#include <Inventor/Qt/SoQtGLWidget.h>

#if HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

// *************************************************************************

/*!
  \class SoQtGLWidget SoQtGLWidget.h Inventor/Qt/SoQtGLWidget.h
  \brief The SoQtGLWidget class contains an OpenGL canvas.

  TODO:
  - doc on how this needs Qt OpenGL extension library, w/html links to Qt doc
  - use the add/removeVisibilityCB methods in SoQtComponent?
  - there's a heap of methods missing from SoXtGLWidget, none (or few)
    of which seems relevant for the Qt implementation -- check the truth of
    this statement
*/

// *************************************************************************

SOQT_OBJECT_ABSTRACT_SOURCE(SoQtGLWidget);

// *************************************************************************

/*!
  \fn virtual void SoQtGLWidget::redraw(void)
  This method will be called when we need a redraw. It must be overloaded in
  non-abstract subclasses.
 */
/*!
  \var SbBool SoQtGLWidget::waitForExpose
  If this is \c TRUE, rendering should not be done yet. Upon the first
  expose event of a newly created OpenGL widget, this variable will
  be set to \c FALSE.
*/
/*!
  \var SbBool SoQtGLWidget::drawToFrontBuffer
  If this is \c TRUE, rendering will happen in the front buffer even
  if the current rendering mode is double buffered.
*/


static const int SO_BORDER_THICKNESS = 2;

// *************************************************************************

/*!
  Protected Constructor.
*/

SoQtGLWidget::SoQtGLWidget(
  QWidget * const parent,
  const char * const name,
  const SbBool embed,
  const int glModes,
  const SbBool build )
: inherited( parent, name, embed )
, waitForExpose( TRUE )
, drawToFrontBuffer( FALSE )
{
  this->glSize = SbVec2s( 0, 0 );
  this->glLockLevel = 0;
  this->glmodebits = glModes;

  this->glparent = NULL;
  this->glwidget = NULL;
  this->borderwidget = NULL;

  if ( ! QGLFormat::hasOpenGL() ) {
    SoDebugError::post( "SoQtGLWidget::SoQtGLWidget",
      "OpenGL not available!" );
    return;
  }


  this->properties.mouseinput = FALSE;
  this->properties.keyboardinput = FALSE;

  this->borderthickness = 0;

  if ( build ) {
    QWidget * widget = this->buildWidget( this->getParentWidget() );
    this->setBaseWidget( widget );
  }
} // SoQtGLWidget()

// *************************************************************************

/*!
  FIXME: write function documentation
*/

QWidget *
SoQtGLWidget::buildWidget(
  QWidget * parent )
{
  if ( parent != NULL && this->isTopLevelShell() )
    parent->installEventFilter( this );

  this->borderwidget = new QFrame( parent );
  this->registerWidget( this->borderwidget );

  this->borderwidget->setFrameStyle( QFrame::Panel | QFrame::Raised );
  this->borderwidget->setLineWidth( this->borderthickness );
  this->borderwidget->setMargin( 0 );
  this->borderwidget->move( 0, 0 );

  // what's this then?
  this->glparent = parent;

  this->buildGLWidget();

  return this->borderwidget;
} // buildWidget()

void 
SoQtGLWidget::buildGLWidget(void)
{
  if (this->glwidget) {
    this->glwidget->removeEventFilter( this );
    this->glwidget->setMouseTracking( FALSE );
    QObject::disconnect( this->glwidget, SIGNAL(expose_sig()), this, SLOT(gl_exposed()));
    QObject::disconnect( this->glwidget, SIGNAL(init_sig()), this, SLOT(gl_init()));
    delete this->glwidget;
    this->glwidget = NULL;
  }
  QGLFormat f;
  f.setDoubleBuffer((this->glmodebits & SO_GLX_DOUBLE) ? TRUE : FALSE);
  f.setDepth((this->glmodebits & SO_GLX_ZBUFFER) ? TRUE : FALSE);
  f.setRgba((this->glmodebits & SO_GLX_RGB) ? TRUE : FALSE);
  f.setStereo((this->glmodebits & SO_GLX_STEREO) ? TRUE : FALSE);

#if HAVE_QGLFORMAT_SETOVERLAY
  f.setOverlay( FALSE ); // at the time being...
#endif // HAVE_QGLFORMAT_SETOVERLAY

  // FIXME: the SO_GLX_OVERLAY bit is not considered (Qt doesn't seem
  // to support overlay planes -- check this with the Qt FAQ or
  // mailing list archives). 990210 mortene.
  // UPDATE: overlay planes are supported with Qt 2.x. 19991218 mortene.

  this->glwidget = new SoQtGLArea( &f, this->borderwidget );

  if ( ! this->glwidget->isValid() )
    SoDebugError::post("SoQtGLWidget::SoQtGLWidget",
                       "Your graphics hardware is weird! Can't use it.");

  QRect temp = borderwidget->contentsRect();
//  SoDebugError::postInfo( "", "rect = %d, %d, %d, %d",
//    temp.left(), temp.top(), temp.right(), temp.bottom() );
  this->glwidget->setGeometry( borderwidget->contentsRect() );


  QObject::connect( this->glwidget, SIGNAL(init_sig()), this, SLOT(gl_init()));
//  QObject::connect( this->glwidget, SIGNAL(reshape_sig(int, int)),
//                   this, SLOT(gl_reshape(int, int)));
  QObject::connect( this->glwidget, SIGNAL(expose_sig()), this, SLOT(gl_exposed()));

  this->glwidget->setMouseTracking( TRUE );
  this->glwidget->installEventFilter( this );

#if 0 // debug
  SoDebugError::postInfo("SoQtGLWidget::buildWidget",
                         "installeventfilter, parent: %p, glwidget: %p",
                         parent, this->glwidget);
#endif // debug

}

// *************************************************************************

  static const char eventnaming[][50] = {
    "None", // 0
    "Timer",
    "MouseButtonPress",
    "MouseButtonRelease",
    "MouseButtonDblClick",
    "MouseMove",
    "KeyPress",
    "KeyRelease",
    "FocusIn",
    "FocusOut",
    "Enter",
    "Leave",
    "Paint",
    "Move",
    "Resize",
    "Create",
    "Destroy",
    "Show",
    "Hide",
    "Close",
    "Quit", // 20
    "*error*", "*error*", "*error*", "*error*", "*error*",
    "*error*", "*error*", "*error*", "*error*",
    "Accel", // 30
    "Wheel",
    "AccelAvailable", // 32
    "*error*", "*error*", "*error*", "*error*",
    "*error*", "*error*", "*error*",
    "Clipboard", // 40
    "*error*", "*error*", "*error*", "*error*", "*error*",
    "*error*", "*error*", "*error*", "*error*",
    "SockAct", // 50
    "*error*", "*error*", "*error*", "*error*", "*error*",
    "*error*", "*error*", "*error*", "*error*",
    "DragEnter", // 60
    "DragMove",
    "DragLeave",
    "Drop",
    "DragResponse", // 64
    "*error*", "*error*", "*error*", "*error*", "*error*",
    "ChildInserted", // 70
    "ChildRemoved",
    "LayoutHint", // 72
    "*error*", "*error*", "*error*", "*error*", "*error*",
    "*error*", "*error*",
    "ActivateControl", // 80
    "DeactivateControl"
  };

/*!
  FIXME: write function documentation
*/

bool
SoQtGLWidget::eventFilter(
  QObject * obj,
  QEvent * e )
{
#if SOQT_DEBUG && 0
  SoDebugError::postInfo( "SoQtGLWidget::eventFilter", "[invoked]" );
#endif // SOQT_DEBUG

#if 0 // debug
  SoDebugError::postInfo("SoQtGLWidget::eventFilter", "obj: %p", obj);

  
  SoDebugError::postInfo("SoQtGLWidget::eventFilter", "%s",
                         eventnaming[e->type()]);
#endif // debug

#if QT_VERSION >= 200
  // Qt 2 introduced "accelerator" type keyboard events, which should
  // simply be ignored (all keyboard events are first attempted passed
  // by the Qt event engine as accelerator events, before they are
  // re-sent as "ordinary" keyboard events).
  if (e->type() == QEvent::Accel || e->type() == QEvent::AccelAvailable) {
    ((QKeyEvent *)e)->ignore();
    // It might not matter whether we return TRUE or FALSE here, but
    // it seems more natural to return FALSE according to the
    // semantics of the eventFilter() method (FALSE means Qt should
    // re-dispatch "normally").
    return FALSE;
  }
#endif // Qt v2.0


  SbBool stopevent = FALSE;

  SbBool keyboardevent =
    ( e->type() == Event_KeyPress) || (e->type() == Event_KeyRelease);

  if (keyboardevent) {
    // Redirect absolutely all keyboard events to the GL canvas
    // widget, ignoring the current focus setting.
    obj = this->glwidget;
    // isAccepted() usually defaults to TRUE, but we need to manually
    // set this (probably due to the way we intercept all events
    // through this eventfilter).
    ((QKeyEvent *)e)->accept();
  }


  if ( obj == (QObject *) this->glparent ) {
    if (e->type() == Event_Resize) {
//      SoDebugError::postInfo( "", "event_resize: glparent" );
      QResizeEvent * r = (QResizeEvent *)e;
#if 0  // debug
      SoDebugError::postInfo("SoQtGLWidget::eventFilter",
                             "resize %p: (%d, %d)",
                             this->glwidget,
                             r->size().width(), r->size().height());
#endif // debug

      this->borderwidget->resize(r->size());
//      int newwidth = r->size().width() - 2 * this->borderthickness;
//      int newheight = r->size().height() - 2 * this->borderthickness;

//      this->glwidget->setGeometry( this->borderthickness,
//                                   this->borderthickness,
//                                   newwidth - 1, newheight -1 );
//      QRect glarea = this->borderwidget->contentsRect();
//      glarea = 
//      this->glwidget->setGeometry( this->borderwidget->contentsRect() );
  
/*
      int newwidth = r->size().width();
      int newheight = r->size().height();
      this->sizeChanged( SbVec2s(newwidth - 1, newheight - 1) );
*/
#if 0 // debug
      SoDebugError::postInfo("SoQtGLWidget::eventFilter", "resize done");
#endif // debug
    }

  } else if ( obj == (QObject *) this->glwidget ) {
#if 1  // debug
    if (e->type() == Event_Resize) {
      QResizeEvent * r = (QResizeEvent *)e;
#if 0
      SoDebugError::postInfo("SoQtGLWidget::eventFilter",
        "glwidget event (%d, %d)",
        (int) r->size().width(), (int) r->size().height() );
#endif
      return true;
    }
#endif // debug
  } else {
    // Handle in superclass.
    stopevent = inherited::eventFilter( obj, e );
  }
  if (!stopevent) {
    this->processEvent(e);
  }

  return stopevent;
}

// *************************************************************************

/*!
  Specify that there should be a border around the OpenGL canvas (or not).

  \sa isBorder()
*/

void
SoQtGLWidget::setBorder(
  const SbBool enable )
{
  this->borderthickness = (enable ? SO_BORDER_THICKNESS : 0);
  if ( this->borderwidget != NULL ) {
    this->borderwidget->setLineWidth( this->borderthickness );
    this->glwidget->move( this->borderthickness, this->borderthickness );
    QSize frame( this->borderwidget->size() );
    this->glwidget->setGeometry(
      QRect( this->borderthickness, this->borderthickness,
             frame.width() - 2 * this->borderthickness,
             frame.height() - 2 * this->borderthickness ) );
   
//    this->glwidget->resize(
//      frame.width() - 2 * this->borderthickness,
//      frame.height() - 2 * this->borderthickness );
  }
} // setBorder()

/*!
  Returns whether or not there's a border around the OpenGL canvas.

  \sa setBorder()
*/

SbBool
SoQtGLWidget::isBorder(
  void ) const
{
  return this->borderthickness ? TRUE : FALSE;
} // isBorder()

// *************************************************************************


/*!
  Switch between single and double buffer mode for the OpenGL canvas.
  The default is to use a single buffer canvas.

  \sa isDoubleBuffer()
*/

void
SoQtGLWidget::setDoubleBuffer(
  const SbBool enable )
{
  if (this->glwidget) {
//    if (enable != this->getQtGLArea()->doubleBuffer()) {
    if ( enable != (SbBool) this->getQtGLArea()->doubleBuffer() ) {
      QGLFormat format = this->getQtGLArea()->format();
      format.setDoubleBuffer(enable);
      this->getQtGLArea()->setFormat(format);
      if(!this->getQtGLArea()->isValid()) {
        SoDebugError::post("SoQtGLWidget::setDoubleBuffer",
                           "Couldn't switch to %s buffer mode. "
                           "Falling back on %s buffer.",
                           enable ? "double" : "single",
                           enable ? "single" : "double");
        format.setDoubleBuffer(!enable);
        this->getQtGLArea()->setFormat(format);
      }

      if (this->glwidget->doubleBuffer()) this->glmodebits |= SO_GLX_DOUBLE;
      else this->glmodebits &= ~SO_GLX_DOUBLE;
    }
  }
  else {
    if (enable) this->glmodebits |= SO_GLX_DOUBLE;
    else this->glmodebits &= ~SO_GLX_DOUBLE;
  }
}

/*!
  Returns the status of the buffer mode.

  \sa setDoubleBuffer()
 */
SbBool
SoQtGLWidget::isDoubleBuffer(void) const
{
  if(this->glwidget) return this->glwidget->doubleBuffer();
  else return (this->glmodebits & SO_GLX_DOUBLE) ? TRUE : FALSE;
}

/*!
  Enables or disables Quad buffer stereo.
*/
void 
SoQtGLWidget::setQuadBufferStereo(const SbBool enable)
{
  SbBool oldenable = (this->glmodebits & SO_GLX_STEREO) ? TRUE : FALSE;
  if ( enable != oldenable ) {
    if (enable) this->glmodebits |= SO_GLX_STEREO;
    else this->glmodebits &= ~SO_GLX_STEREO;
    this->buildGLWidget();
  }
}

/*!
  Returns TRUE if quad buffer stereo is enabled for this widget.
*/
SbBool 
SoQtGLWidget::isQuadBufferStereo(void) const
{
  return (this->glmodebits & SO_GLX_STEREO) ? TRUE : FALSE;
}


/*!
  FIXME: write function documentation
*/
void
SoQtGLWidget::setDrawToFrontBufferEnable(const SbBool enable)
{
  this->drawToFrontBuffer = enable;
}

/*!
  FIXME: write function documentation
*/
SbBool
SoQtGLWidget::isDrawToFrontBufferEnable(void) const
{
  return this->drawToFrontBuffer;
}

// *************************************************************************

/*!
  FIXME: write function documentation
*/

void
SoQtGLWidget::setGlxSize(
  const SbVec2s size )
{
  this->setGLSize( size );
} // setGlxSize()

/*!
*/

void
SoQtGLWidget::setGLSize(
  const SbVec2s size )
{
  SoDebugError::postInfo( "SoQtGLWidget::setGLSize",
    "[invoked (%d, %d)]", size[0], size[1] );
  if ( this->borderwidget ) {
    int frame = this->borderwidget->frameWidth();
    this->borderwidget->resize( size[0] + 2 * frame, size[1] + 2 * frame );
    this->glwidget->setGeometry( QRect( frame, frame, size[0], size[1] ) );
//    this->glwidget->move( frame, frame );
//    this->glwidget->resize( size[0], size[1] );
  }
  this->glSize = size;
} // setGLSize()


/*!
  Return the dimensions of the OpenGL canvas.
*/

SbVec2s
SoQtGLWidget::getGlxSize(
  void ) const
{
  return this->getGLSize();
} // getGlxSize()

/*!
*/

SbVec2s
SoQtGLWidget::getGLSize(
  void ) const
{
  return this->glSize;
}

/*!
  Return the aspect ratio of the OpenGL canvas.
*/

float
SoQtGLWidget::getGlxAspectRatio(void) const
{
  return this->getGLAspectRatio();
}

/*!
*/

float
SoQtGLWidget::getGLAspectRatio(
  void ) const
{
  return float(this->glwidget->width())/float(this->glwidget->height());
}  // getGLAspectRatio()

// *************************************************************************

/*!
  Returns a pointer to the Qt QGLWidget.
*/

SoQtGLArea *
SoQtGLWidget::getQtGLArea(void)
{
  return (SoQtGLArea *) this->glwidget;
} // getQtGLArea()

/*!
*/

QWidget *
SoQtGLWidget::getGLWidget(void)
{
  return this->glwidget;
} // getGLWidget()

/*!
  FIXME: write function documentation
*/

void
SoQtGLWidget::sizeChanged(
  const SbVec2s size )
{
#if SOQT_DEBUG && 0
  SoDebugError::postInfo( "SoQtGLWidget::sizeChanged",
    "[invoked] ( %d, %d ) [%d, %d]", size[0], size[1], this->glSize[0], this->glSize[1] );
#endif // SOQT_DEBUG
//  this->borderwidget->resize( size[0] - 1, size[1] );
//  int sub = this->borderwidget->frameWidth() * 2;
//  geometry = QRect( geometry.left(), geometry.top(),
//    geometry.width() - sub, geometry.height() - sub );
  int frame = this->isBorder() ? SO_BORDER_THICKNESS : 0;
  this->glSize = SbVec2s( size[0] - 2 * frame, size[1] - 2 * frame );
  if ( this->glwidget ) {
    this->glwidget->setGeometry( QRect( frame, frame, this->glSize[0], this->glSize[1] ) );
//    this->glwidget->move( frame, frame );
//    this->glwidget->resize( this->glSize[0], this->glSize[1] );
    this->glReshape( this->glSize[0], this->glSize[1] );
    this->glRender();
  }
} // sizeChanged()

/*!
  This is the method which gets called whenever the OpenGL widget
  changes in any way.  Should be overloaded in subclasses.

  \sa sizeChanged()
*/

// *************************************************************************

void
SoQtGLWidget::widgetChanged(
  QWidget * w )
{
}

/*!
  FIXME: write function documentation
*/

void
SoQtGLWidget::processEvent(QEvent * /* anyevent */)
{
//  SoDebugError::postInfo( "processEvent", "called" );
  // FIXME: anything to do here? 981029 mortene.
}

// *************************************************************************

void
SoQtGLWidget::glLock(
  void )
{
  assert( this->glwidget != NULL );
  this->glLockLevel++;
  assert( this->glLockLevel < 10 && "must be programming error" );
  ((SoQtGLArea *)this->glwidget)->makeCurrent();
} // glLock()

void
SoQtGLWidget::glUnlock(
  void )
{
  this->glLockLevel--;
  assert( this->glLockLevel >= 0 && "programming error" );
} // glUnlock()

void
SoQtGLWidget::glSwapBuffers(
  void )
{
  assert( this->glwidget != NULL );
  assert( this->glLockLevel > 0 );
#if SOQT_DEBUG && 0 // debug
  SoDebugError::postInfo( "SoQtGLWidget::glSwapBuffers", "start" );
#endif // debug
  ((SoQtGLArea *)this->glwidget)->swapBuffers();
#if SOQT_DEBUG && 0 // debug
  SoDebugError::postInfo( "SoQtGLWidget::glSwapBuffers", "done" );
#endif // debug
} // glSwapBuffers()

void
SoQtGLWidget::glFlushBuffer(
  void )
{
  assert( this->glLockLevel > 0 );
  SOQT_STUB();
} // glFlushBuffer()

void
SoQtGLWidget::glInit( // virtual
  void )
{
#if 0 // SOQT_DEBUG
  SoDebugError::postInfo( "SoQtGLWidget::glInit", "called" );
#endif // 0 was SOQT_DEBUG

  glLock();
  // Need to set this explicitly when running on top of Open Inventor,
  // as it seems to have been forgotten there.
  glEnable( GL_DEPTH_TEST );
  glUnlock();
} // glInit()

void
SoQtGLWidget::gl_init( // slot
  void )
{
  this->glInit();
} // gl_init()

void
SoQtGLWidget::glReshape( // virtual
  int width,
  int height )
{
#if SOQT_DEBUG && 0
  SoDebugError::postInfo( "SoQtGLWidget::glReshape",
    "[invoked (%d, %d)]", width, height );
#endif // SOQT_DEBUG
  this->glSize = SbVec2s( (short) width, (short) height );
} // glReshape()

void
SoQtGLWidget::gl_reshape( // slot
  int width,
  int height )
{
#if SOQT_DEBUG
  SoDebugError::postInfo( "SoQtGLWidget::gl_reshape slot",
    "[invoked (%d, %d)]", width, height );
#endif // SOQT_DEBUG
//  this->sizeChanged( SbVec2s( width, height ) );
  this->glReshape( width, height );
} // gl_reshape()

void
SoQtGLWidget::glRender( // virtual
  void )
{
#if 0 // SOQT_DEBUG
  SoDebugError::postInfo( "SoQtGLWidget::glRender", "called" );
#endif // 0 was SOQT_DEBUG
  // nada
  this->redraw();
} // glRender()

void
SoQtGLWidget::gl_exposed( // slot
  void )
{
  this->glRender();
  this->waitForExpose = FALSE; // Gets flipped from TRUE on first expose.
} // gl_exposed()

// *************************************************************************

void
SoQtGLWidget::eventHandler(
  QWidget * widget,
  void * closure,
  QEvent * event,
  bool * ) // ? )
{
  assert( closure != NULL );
  SoQtGLWidget * component = (SoQtGLWidget *) closure;
  component->processEvent( event );
} // eventHandler()

// *************************************************************************
