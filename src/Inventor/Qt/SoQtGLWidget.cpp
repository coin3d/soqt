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

// *************************************************************************

/*!
  \class SoQtGLWidget SoQtGLWidget.h Inventor/Qt/SoQtGLWidget.h
  \brief The SoQtGLWidget class contains an OpenGL canvas.

  [FIXME: basic doc here]

  An important thing to know about embedding SoQtGLWidget derived
  components into other Qt widgets is that you need to set up "focus
  proxying" to have events still be set to the OpenGL canvas
  widget. This is true for both the SoQtRenderArea aswell as all the
  viewer components (like SoQtExaminerViewer, SoQtWalkViewer etc).  As
  an example, if you embed an SoQtExaminerViewer inside a QFrame like
  this:

  \code
  QMainWindow * toplevel = new QMainWindow;
  QFrame * frame = new QFrame(toplevel);
  SoQtExaminerViewer * viewer = new SoQtExaminerViewer(toplevelwidget);
  \endcode

  ..events from the keyboard will not always automatically be
  forwarded to the viewer OpenGL canvas. This is the code you need to
  add in this case:

  \code
  toplevel->setFocusProxy(viewer);
  \endcode
*/

//  FIXME:
//    - use the add/removeVisibilityCB methods in SoQtComponent?
//    - there's a heap of methods missing from SoXtGLWidget, none (or few)
//      of which seems relevant for the Qt implementation -- check the truth of
//      this statement

// *************************************************************************

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

static inline bool
QGLFormat_eq(const QGLFormat & a, const QGLFormat & b)
{
  // For Qt v2.2.2 at least, Troll Tech forgot to include
  // operator==(QGLFormat&,QGLFormat&) in the publicly exported API
  // for MSWindows DLLs.
#ifndef HAVE_QGLFORMAT_EQ_OP
  if (a.doubleBuffer() != b.doubleBuffer()) return false;
  if (a.depth() != b.depth()) return false;
  if (a.rgba() != b.rgba()) return false;
  if (a.stereo() != b.stereo()) return false;
#if HAVE_QGLFORMAT_SETOVERLAY
  if (a.hasOverlay() != b.hasOverlay()) return false;
#endif // HAVE_QGLFORMAT_SETOVERLAY
  return true;
#else // HAVE_QGLFORMAT_EQ_OP
  return (a == b);
#endif // HAVE_QGLFORMAT_EQ_OP
}

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
  Protected constructor.
*/

SoQtGLWidget::SoQtGLWidget(
  QWidget * const parent,
  const char * const name,
  const SbBool embed,
  const int glmodes,
  const SbBool build )
: inherited( parent, name, embed )
, waitForExpose( TRUE )
, drawToFrontBuffer( FALSE )
{
  this->glSize = SbVec2s( 0, 0 );
  this->glLockLevel = 0;

  this->glformat = new QGLFormat;
  this->glformat->setDoubleBuffer((glmodes & SO_GL_DOUBLE) ? true : false);
  this->glformat->setDepth((glmodes & SO_GL_ZBUFFER) ? true : false);
  this->glformat->setRgba((glmodes & SO_GL_RGB) ? true : false);
  this->glformat->setStereo((glmodes & SO_GL_STEREO) ? true : false);
  // FIXME: SoQt overlay handling. 20001121 mortene.
#if HAVE_QGLFORMAT_SETOVERLAY
  //    this->glformat->setOverlay((glmodes & SO_GL_OVERLAY) ? true : false);
#endif // HAVE_QGLFORMAT_SETOVERLAY

  this->glparent = NULL;
  this->currentglwidget = NULL;
  this->previousglwidget = NULL;
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
  Protected destructor.
*/

SoQtGLWidget::~SoQtGLWidget(void)
{
  // Don't delete the widgets we've allocated, as they are destructed
  // implicitly when their parent widgets die. (Destructing "our"
  // child widgets in this destructor can in fact lead to crashes due
  // to the widgets being deallocated multiple times.)

  delete this->glformat;
}

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

  // Remember our parent widget so we can use it in tests in the
  // eventFilter().
  this->glparent = parent;

  this->buildGLWidget();

  return this->borderwidget;
} // buildWidget()


// The GL widget rebuilding has been written to remember the previous
// GL widget, which might be swapped back in if it fits the wanted
// format.
//
// There are two reasons for keeping track of both the current and the
// previous widget:
//
//  1) efficiency; often one swaps back and forth between only two
//  different visuals -- like single and double buffering, or stereo
//  mode on and off
//
//  2) robustness; killing off the previous widget in the build-method
//  below has nasty sideeffects (like "random" coredumps), since the
//  Qt event loop might be using it
void 
SoQtGLWidget::buildGLWidget(void)
{
#if SOQT_DEBUG && 0 // debug
  SoDebugError::postInfo("SoQtGLWidget::buildGLWidget",
                         "%s, %s, %s, %s, %s",
                         this->glformat->doubleBuffer() ? "double" : "single",
                         this->glformat->depth() ? "z-buffer" : "no z-buffer",
                         this->glformat->rgba() ? "RGBA" : "colorindex",
                         this->glformat->stereo() ? "stereo" : "mono",
#if HAVE_QGLFORMAT_SETOVERLAY
                         this->glformat->hasOverlay() ?
#else // !HAVE_QGLFORMAT_SETOVERLAY
                         FALSE ?
#endif // !HAVE_QGLFORMAT_SETOVERLAY
                         "overlay" : "no overlay");

#endif // debug

  SoQtGLArea * wascurrent = this->currentglwidget;
  SoQtGLArea * wasprevious = this->previousglwidget;

  if (wascurrent) {
    // Do _not_ turn off mousetracking or remove the eventfilter, as
    // we'd loose events after the switch has happened if the user is
    // already interacting with the canvas (e.g. when starting a drag
    // in BUFFER_INTERACTIVE mode).
#if 0 // Keep this code around so we don't accidentally reinsert it. :^}
    wascurrent->removeEventFilter( this );
    wascurrent->setMouseTracking( FALSE );
#endif // Permanently disabled.
    QObject::disconnect( wascurrent, SIGNAL(expose_sig()), this, SLOT(gl_exposed()));
    QObject::disconnect( wascurrent, SIGNAL(init_sig()), this, SLOT(gl_init()));
    this->previousglwidget = wascurrent;
  }

  if ( wasprevious && QGLFormat_eq(*this->glformat, wasprevious->format() ) ) {
    // Reenable the previous widget.
    this->currentglwidget = wasprevious;
#if SOQT_DEBUG && 0 // debug
    SoDebugError::postInfo("SoQtGLWidget::buildGLWidget",
                           "reused previously used GL widget");
#endif // debug
  }
  else {
    // Couldn't use the previous widget, make a new one.
    this->currentglwidget = new SoQtGLArea( this->glformat,
                                            this->borderwidget );
    // Send this one to the final hunting grounds.
    delete wasprevious;
  }

  if ( ! this->currentglwidget->isValid() ) {
    SoDebugError::post("SoQtGLWidget::SoQtGLWidget",
                       "Your graphics hardware is weird! Can't use it.");
    // FIXME: should be fatal? 20001122 mortene.
  }

#if SOQT_DEBUG // Warn about requested features that we didn't get.
  QGLFormat * w = this->glformat; // w(anted)
  QGLFormat g = this->currentglwidget->format(); // g(ot)

#define GLWIDGET_FEATURECMP(_glformatfunc_, _truestr_, _falsestr_) \
  do { \
    if (w->_glformatfunc_() != g._glformatfunc_()) { \
      SoDebugError::postWarning("SoQtGLWidget::buildGLWidget", \
                                "wanted %s, but that is not supported " \
                                "by the OpenGL driver", \
                                w->_glformatfunc_() ? _truestr_ : _falsestr_); \
    } \
  } while (0)

  GLWIDGET_FEATURECMP(doubleBuffer, "doublebuffer visual", "singlebuffer visual");
  GLWIDGET_FEATURECMP(depth, "visual with depthbuffer", "visual without depthbuffer");
  GLWIDGET_FEATURECMP(rgba, "RGBA buffer", "colorindex buffer");
  GLWIDGET_FEATURECMP(stereo, "stereo buffers", "mono buffer");
#if HAVE_QGLFORMAT_SETOVERLAY
  GLWIDGET_FEATURECMP(hasOverlay, "overlay plane(s)", "visual without overlay plane(s)");
#endif // HAVE_QGLFORMAT_SETOVERLAY

#undef GLWIDGET_FEATURECMP

#endif // SOQT_DEBUG


  *this->glformat = this->currentglwidget->format();

  int frame = this->isBorder() ? this->borderthickness : 0;
  this->currentglwidget->setGeometry( frame, frame,
                                      this->glSize[0] - 2*frame,
                                      this->glSize[1] - 2*frame);

  QObject::connect( this->currentglwidget, SIGNAL(init_sig()),
                    this, SLOT(gl_init()));
//  QObject::connect( this->glwidget, SIGNAL(reshape_sig(int, int)),
//                   this, SLOT(gl_reshape(int, int)));
  QObject::connect( this->currentglwidget, SIGNAL(expose_sig()),
                    this, SLOT(gl_exposed()));

  this->currentglwidget->setMouseTracking( TRUE );
  this->currentglwidget->installEventFilter( this );

  // Reset to avoid unnecessary scenegraph redraws.
  this->waitForExpose = TRUE;

  // We've changed to a new widget, so notify subclasses through this
  // virtual method.
  this->widgetChanged(this->currentglwidget);

  if (wascurrent) {
    // If we are rebuilding, we need to explicitly call show() here,
    // as no message to show will be given from an already visible
    // parent. (If the glwidget was built but not shown before the
    // rebuild, the call below doesn't do any harm, as the glwidget
    // still won't become visible until all parents are visible.)
    this->currentglwidget->show();
    this->currentglwidget->raise();
  }
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
#if SOQT_DEBUG && 0 // debug
  SoDebugError::postInfo("SoQtGLWidget::eventFilter",
                         "[invoked] obj: %p %s",
                         obj,
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
    obj = this->currentglwidget;
    // isAccepted() usually defaults to TRUE, but we need to manually
    // set this (probably due to the way we intercept all events
    // through this eventfilter).
    ((QKeyEvent *)e)->accept();
  }


  if ( obj == (QObject *) this->glparent ) {
    // If this hits, the this->glparent QWidget is a toplevelshell, so
    // we resize the GL widget along with it.
    if (e->type() == Event_Resize) {
      QResizeEvent * r = (QResizeEvent *)e;
#if SOQT_DEBUG && 0  // debug
      SoDebugError::postInfo("SoQtGLWidget::eventFilter",
                             "resize parent %p: (%d, %d)",
                             this->glparent,
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

  } else if ( obj == (QObject *) this->currentglwidget ) {
#if 1  // debug
    if (e->type() == Event_Resize) {
      QResizeEvent * r = (QResizeEvent *)e;
#if 0
      SoDebugError::postInfo("SoQtGLWidget::eventFilter",
        "glwidget event (%d, %d)",
        (int) r->size().width(), (int) r->size().height() );
#endif
      // Do not redispatch.
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
    this->currentglwidget->move( this->borderthickness, this->borderthickness );
    QSize frame( this->borderwidget->size() );
    this->currentglwidget->setGeometry(
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
  if ( (enable && this->glformat->doubleBuffer()) ||
       (!enable && !this->glformat->doubleBuffer()) )
    return;

  this->glformat->setDoubleBuffer(enable);
  // Rebuild if a GL widget has already been built.
  if (this->currentglwidget) this->buildGLWidget();
}

/*!
  Returns the status of the buffer mode.

  \sa setDoubleBuffer()
 */
SbBool
SoQtGLWidget::isDoubleBuffer(void) const
{
  return this->glformat->doubleBuffer();
}

/*!
  Enables or disables quad buffer stereo.
*/
void 
SoQtGLWidget::setQuadBufferStereo(const SbBool enable)
{
  if ( (enable && this->glformat->stereo()) ||
       (!enable && !this->glformat->stereo()) )
    return;

  this->glformat->setStereo(enable);
  // Rebuild if a GL widget has already been built.
  if (this->currentglwidget) this->buildGLWidget();
}

/*!
  Returns \c TRUE if quad buffer stereo is enabled for this widget.
*/
SbBool 
SoQtGLWidget::isQuadBufferStereo(void) const
{
  return this->glformat->stereo();
}


/*!
  If this is set to \c TRUE, rendering will happen in the front buffer
  even if the current rendering mode is double buffered.
*/
void
SoQtGLWidget::setDrawToFrontBufferEnable(const SbBool enable)
{
  this->drawToFrontBuffer = enable;
}

/*!
  \sa setDrawToFrontBufferEnable()
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
#if SOQT_DEBUG && 0 // debug
  SoDebugError::postInfo( "SoQtGLWidget::setGLSize",
    "[invoked (%d, %d)]", size[0], size[1] );
#endif // debug
  this->glSize = size;
  if ( this->currentglwidget ) {
    int frame = this->isBorder() ? this->borderthickness : 0;
    this->currentglwidget->setGeometry( QRect( frame, frame, this->glSize[0], this->glSize[1] ) );
    // FIXME: this is crap, we should use glRender() instead, but that
    // won't work because of the way they are overloaded in
    // SoGuiRenderArea. 20001126 mortene.
    this->glReshape( this->glSize[0], this->glSize[1] );
  }
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
  return float(this->currentglwidget->width()) /
    float(this->currentglwidget->height());
}  // getGLAspectRatio()

// *************************************************************************

/*!
  Returns a pointer to the Qt QGLWidget.
*/

QWidget *
SoQtGLWidget::getGLWidget(void)
{
  return this->currentglwidget;
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

  if ( this->borderwidget ) this->borderwidget->resize( size[0], size[1] );
  int frame = this->isBorder() ? this->borderthickness : 0;
  this->setGLSize( SbVec2s( size[0] - 2 * frame, size[1] - 2 * frame ) );
} // sizeChanged()

// *************************************************************************

/*!
  This is the method which gets called whenever we change which OpenGL
  widget is used.

  Should be overloaded in subclasses which directly or indirectly
  store the return value from the SoQtGLWidget::getGLWidget() method.

  \sa sizeChanged()
*/

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
  assert( this->currentglwidget != NULL );
  this->glLockLevel++;
  assert( this->glLockLevel < 10 && "must be programming error" );
  ((SoQtGLArea *)this->currentglwidget)->makeCurrent();
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
  assert( this->currentglwidget != NULL );
  assert( this->glLockLevel > 0 );
#if SOQT_DEBUG && 0 // debug
  SoDebugError::postInfo( "SoQtGLWidget::glSwapBuffers", "start" );
#endif // debug
  ((SoQtGLArea *)this->currentglwidget)->swapBuffers();
#if SOQT_DEBUG && 0 // debug
  SoDebugError::postInfo( "SoQtGLWidget::glSwapBuffers", "done" );
#endif // debug
} // glSwapBuffers()

void
SoQtGLWidget::glFlushBuffer(
  void )
{
  assert( this->glLockLevel > 0 );
  glFlush();
} // glFlushBuffer()

void
SoQtGLWidget::glInit( // virtual
  void )
{
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

/*!
  This method will be called whenever the OpenGL canvas changes size.
 */
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
#if SOQT_DEBUG && 0 // debug
  SoDebugError::postInfo( "SoQtGLWidget::glRender", "called" );
#endif // debug
  this->redraw();
} // glRender()

void
SoQtGLWidget::gl_exposed( // slot
  void )
{
  if (this->waitForExpose) {
    this->waitForExpose = FALSE; // Gets flipped from TRUE on first expose.
#if 0 // tmp disabled
    // The Qt library uses QApplication::sendPostedEvents() for
    // passing out various delayed events upon show(), among them a
    // bunch of bl**dy resize events which will overload any size
    // settings done before we show the SoQt component widgets.

    // FIXME: should probably be an afterRealizeHook() fix. 20001125 mortene.

    this->setSize(this->getSize());
#endif // tmp disabled
  }

  this->glRender();
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
