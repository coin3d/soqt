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

/*!
  \fn void SoQtGLWidget::setStereoBuffer(SbBool flag)
  
  Sets whether OpenGL stereo buffers (quad buffer stereo) should be used.
*/

/*!
  \fn SbBool SoQtGLWidget::isStereoBuffer(void) const

  Returns whether OpenGL stereo buffers are being used.
*/

// *************************************************************************

#include <qevent.h>
#include <qframe.h>

#include <Inventor/errors/SoDebugError.h>
#include <Inventor/misc/SoBasic.h>

#include <soqtdefs.h>
#include <Inventor/Qt/SoQtBasic.h>
#include <Inventor/Qt/widgets/SoQtGLArea.h>
#include <Inventor/Qt/SoQtGLWidget.h>
#include <Inventor/Qt/SoAny.h>

#if HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

// Abstract the overlay handling methods on QGLFormat and QGLWidget,
// because they may or may not be there depending on the version of
// the QGL library installed on the developer's system.
//
// (And we'd like to avoid scattering #ifdef's all over the code, so
// we make some new functions.)
//
#if HAVE_QGLFORMAT_SETOVERLAY
static inline bool QGLFormat_hasOverlay(const QGLFormat * f)
{ return f->hasOverlay(); }
static inline void QGLFormat_setOverlay(QGLFormat * f, bool enable)
{ f->setOverlay( enable ); }
static inline void QGLFormat_makeOverlayCurrent(QGLWidget * w)
{ w->makeOverlayCurrent(); }
static inline const QGLContext * QGLWidget_overlayContext(QGLWidget * w)
{ return w->overlayContext(); }
static inline const QColor QGLContext_overlayTransparentColor(const QGLContext * c)
{ return c->overlayTransparentColor(); }
#else // !HAVE_QGLFORMAT_SETOVERLAY
static inline bool QGLFormat_hasOverlay(const QGLFormat * f) { return false; }
static inline void QGLFormat_setOverlay(QGLFormat * f, bool enable) { }
static inline void QGLFormat_makeOverlayCurrent(QGLWidget * w) { }
static inline const QGLContext * QGLWidget_overlayContext(QGLWidget * w) { return NULL; }
static inline const QColor QGLContext_overlayTransparentColor(const QGLContext * c) { return QColor(0, 0, 0); }
#endif // !HAVE_QGLFORMAT_SETOVERLAY


// For Qt v2.2.2 at least, Troll Tech forgot to include
// operator==(QGLFormat&,QGLFormat&) in the publicly exported API for
// MSWindows DLLs. This abstracts the workaround into a method
// QGLFormat_eq().
//
#if HAVE_QGLFORMAT_EQ_OP
static inline bool
QGLFormat_eq(const QGLFormat & a, const QGLFormat & b)
{
  return (a == b);
}
#else // !HAVE_QGLFORMAT_EQ_OP
static inline bool
QGLFormat_eq(const QGLFormat & a, const QGLFormat & b)
{
  if (a.doubleBuffer() != b.doubleBuffer()) return false;
  if (a.depth() != b.depth()) return false;
  if (a.rgba() != b.rgba()) return false;
  if (a.stereo() != b.stereo()) return false;
  if (QGLFormat_hasOverlay(&a) != QGLFormat_hasOverlay(&b)) return false;
  return true;
}
#endif // !HAVE_QGLFORMAT_EQ_OP

// *************************************************************************

// The private data for the SoQtGLWidget.

class SoQtGLWidgetP {
public:
  SbVec2s glSize;
  SbBool wasresized;

  SoQtGLArea * currentglwidget;
  SoQtGLArea * previousglwidget;
  QWidget * glparent;
  QFrame * borderwidget;
  int borderthickness;
  QGLFormat * glformat;
};

#define THIS (this->pimpl)

// *************************************************************************

SOQT_OBJECT_ABSTRACT_SOURCE(SoQtGLWidget);

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
  THIS = new SoQtGLWidgetP;

  THIS->glSize = SbVec2s( 0, 0 );
  THIS->wasresized = FALSE;

  THIS->glformat = new QGLFormat;
  THIS->glformat->setDoubleBuffer((glmodes & SO_GL_DOUBLE) ? true : false);
  THIS->glformat->setDepth((glmodes & SO_GL_ZBUFFER) ? true : false);
  THIS->glformat->setRgba((glmodes & SO_GL_RGB) ? true : false);
  THIS->glformat->setStereo((glmodes & SO_GL_STEREO) ? true : false);
  bool enableoverlay = (glmodes & SO_GL_OVERLAY) ? true : false;
  QGLFormat_setOverlay(THIS->glformat, enableoverlay);

#if SOQT_DEBUG && 0
  // people ask if this warning is a problem - it is harmless, so we
  // don't display it anymore [2001-05-18 larsa]

  // FIXME: this is *not* a good way to handle this case.  What should
  // be done is 1) default to set up a QGLWidget without overlay
  // planes, 2) when an overlay scenegraph is attempted registered
  // with the SoQtRenderArea -- *then* try to make a QGLWidget with
  // overlay planes, and if that's not possible, display this
  // warning. 20010805 mortene.

  if (enableoverlay && !QGLFormat_hasOverlay(THIS->glformat)) {
    SoDebugError::postWarning( "SoQtGLWidget::SoQtGLWidget",
                               "your Qt/QGL library has no support "
                               "for handling overlay planes" );
  }
#endif // SOQT_DEBUG

  THIS->glparent = NULL;
  THIS->currentglwidget = NULL;
  THIS->previousglwidget = NULL;
  THIS->borderwidget = NULL;

  if ( ! QGLFormat::hasOpenGL() ) {
    SoDebugError::post( "SoQtGLWidget::SoQtGLWidget",
                        "OpenGL not available!" );
    return;
  }

  THIS->borderthickness = 0;

  if ( ! build )
    return;

  this->setClassName( "SoQtGLWidget" );
  QWidget * parentwidget = this->getParentWidget();
  QWidget * widget = this->buildWidget( parentwidget );
  this->setBaseWidget( widget );
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

  if (THIS->currentglwidget) SoAny::si()->unregisterGLContext((void*) this);
  
  delete THIS->glformat;
  delete THIS;
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

  THIS->borderwidget = new QFrame( parent );
  this->registerWidget( THIS->borderwidget );

  THIS->borderwidget->setFrameStyle( QFrame::Panel | QFrame::Raised );
  THIS->borderwidget->setLineWidth( THIS->borderthickness );
  THIS->borderwidget->setMargin( 0 );
  THIS->borderwidget->move( 0, 0 );

  // Remember our parent widget so we can use it in tests in the
  // eventFilter().
  THIS->glparent = parent;

  this->buildGLWidget();

  return THIS->borderwidget;
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
                         THIS->glformat->doubleBuffer() ? "double" : "single",
                         THIS->glformat->depth() ? "z-buffer" : "no z-buffer",
                         THIS->glformat->rgba() ? "RGBA" : "colorindex",
                         THIS->glformat->stereo() ? "stereo" : "mono",
                         QGLFormat_hasOverlay(THIS->glformat) ? "overlay" : "no overlay");
#endif // debug

  SoQtGLArea * wascurrent = THIS->currentglwidget;
  SoQtGLArea * wasprevious = THIS->previousglwidget;

  void * display = NULL;
  void * screen = NULL;
#if defined(_WS_X11_) // Qt defines this under X11
  // the following Qt methods are only available under X11
  display = (void*) QPaintDevice::x11AppDisplay();
  screen = (void*) ((unsigned int) QPaintDevice::x11AppScreen());
#endif // _WS_X11_

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
    //    QObject::disconnect( wascurrent, SIGNAL(reshape_sig()), this, SLOT(gl_reshape()));
    THIS->previousglwidget = wascurrent;
  }

  if ( wasprevious && QGLFormat_eq(*THIS->glformat, wasprevious->format() ) ) {
    // Reenable the previous widget.
    if (THIS->currentglwidget) SoAny::si()->unregisterGLContext((void*) this);
    THIS->currentglwidget = wasprevious;
    SoAny::si()->registerGLContext((void*) this, display, screen);
#if SOQT_DEBUG && 0 // debug
    SoDebugError::postInfo("SoQtGLWidget::buildGLWidget",
                           "reused previously used GL widget");
#endif // debug
  }
  else {
    // Couldn't use the previous widget, make a new one.
    SoQtGLWidget * sharewidget = (SoQtGLWidget*) SoAny::si()->getSharedGLContext(display, screen);
    if (THIS->currentglwidget) SoAny::si()->unregisterGLContext((void*) this);
    THIS->currentglwidget = new SoQtGLArea(THIS->glformat,
                                           THIS->borderwidget,
                                           sharewidget ? (const QGLWidget*) sharewidget->getGLWidget() : NULL);
    SoAny::si()->registerGLContext((void*) this, display, screen);
    // Send this one to the final hunting grounds.    
    delete wasprevious;
  }

  if ( ! THIS->currentglwidget->isValid() ) {
    SoDebugError::post("SoQtGLWidget::SoQtGLWidget",
                       "Your graphics hardware is weird! Can't use it.");
    // FIXME: should be fatal? 20001122 mortene.
  }

#if SOQT_DEBUG // Warn about requested features that we didn't get.
  QGLFormat * w = THIS->glformat; // w(anted)
  QGLFormat g = THIS->currentglwidget->format(); // g(ot)

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

  if (QGLFormat_hasOverlay(w) != QGLFormat_hasOverlay(&g)) {
    SoDebugError::postWarning("SoQtGLWidget::buildGLWidget",
                              "wanted %s, but that is not supported "
                              "by the OpenGL driver",
                              QGLFormat_hasOverlay(w) ?
                              "overlay plane(s)" :
                              "visual without overlay plane(s)");
  }

#undef GLWIDGET_FEATURECMP

#endif // SOQT_DEBUG


  *THIS->glformat = THIS->currentglwidget->format();

  int frame = this->isBorder() ? THIS->borderthickness : 0;
  THIS->currentglwidget->setGeometry( frame, frame,
                                      THIS->glSize[0] - 2*frame,
                                      THIS->glSize[1] - 2*frame);

  QObject::connect( THIS->currentglwidget, SIGNAL(init_sig()),
                    this, SLOT(gl_init()));
  //  QObject::connect( THIS->currentglwidget, SIGNAL(reshape_sig(int, int)),
  //                    this, SLOT(gl_reshape(int, int)));
  QObject::connect( THIS->currentglwidget, SIGNAL(expose_sig()),
                    this, SLOT(gl_exposed()));

  THIS->currentglwidget->setMouseTracking( TRUE );
  THIS->currentglwidget->installEventFilter( this );

  // Reset to avoid unnecessary scenegraph redraws.
  this->waitForExpose = TRUE;

  // We've changed to a new widget, so notify subclasses through this
  // virtual method.
  this->widgetChanged(THIS->currentglwidget);

  if (wascurrent) {
    // If we are rebuilding, we need to explicitly call show() here,
    // as no message to show will be given from an already visible
    // parent. (If the glwidget was built but not shown before the
    // rebuild, the call below doesn't do any harm, as the glwidget
    // still won't become visible until all parents are visible.)
    THIS->currentglwidget->show();
    THIS->currentglwidget->raise();
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
    (e->type() == QEvent::KeyPress) || (e->type() == QEvent::KeyRelease);

  if (keyboardevent) {
    // Redirect absolutely all keyboard events to the GL canvas
    // widget, ignoring the current focus setting.
    obj = THIS->currentglwidget;
    // isAccepted() usually defaults to TRUE, but we need to manually
    // set this (probably due to the way we intercept all events
    // through this eventfilter).
    ((QKeyEvent *)e)->accept();
  }


  if ( obj == (QObject *) THIS->glparent ) {
    // If this hits, the THIS->glparent QWidget is a toplevelshell, so
    // we resize the GL widget along with it.
    if (e->type() == QEvent::Resize) {
      QResizeEvent * r = (QResizeEvent *)e;
#if SOQT_DEBUG && 0  // debug
      SoDebugError::postInfo("SoQtGLWidget::eventFilter",
                             "resize parent %p: (%d, %d)",
                             THIS->glparent,
                             r->size().width(), r->size().height());
#endif // debug

      THIS->borderwidget->resize(r->size());
//      int newwidth = r->size().width() - 2 * THIS->borderthickness;
//      int newheight = r->size().height() - 2 * THIS->borderthickness;

//      this->glwidget->setGeometry( THIS->borderthickness,
//                                   THIS->borderthickness,
//                                   newwidth - 1, newheight -1 );
//      QRect glarea = THIS->borderwidget->contentsRect();
//      glarea =
//      this->glwidget->setGeometry( THIS->borderwidget->contentsRect() );

/*
      int newwidth = r->size().width();
      int newheight = r->size().height();
      this->sizeChanged( SbVec2s(newwidth - 1, newheight - 1) );
*/
#if 0 // debug
      SoDebugError::postInfo("SoQtGLWidget::eventFilter", "resize done");
#endif // debug
    }

  } else if ( obj == (QObject *) THIS->currentglwidget ) {
#if 1  // debug
    if (e->type() == QEvent::Resize) {
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
  THIS->borderthickness = (enable ? SO_BORDER_THICKNESS : 0);
  if ( THIS->borderwidget != NULL ) {
    THIS->borderwidget->setLineWidth( THIS->borderthickness );
    THIS->currentglwidget->move( THIS->borderthickness, THIS->borderthickness );
    QSize frame( THIS->borderwidget->size() );
    THIS->currentglwidget->setGeometry(
      QRect( THIS->borderthickness, THIS->borderthickness,
             frame.width() - 2 * THIS->borderthickness,
             frame.height() - 2 * THIS->borderthickness ) );

//    this->glwidget->resize(
//      frame.width() - 2 * THIS->borderthickness,
//      frame.height() - 2 * THIS->borderthickness );
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
  return THIS->borderthickness ? TRUE : FALSE;
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
  if ( (enable && THIS->glformat->doubleBuffer()) ||
       (!enable && !THIS->glformat->doubleBuffer()) )
    return;

  THIS->glformat->setDoubleBuffer(enable);
  // Rebuild if a GL widget has already been built.
  if (THIS->currentglwidget) this->buildGLWidget();
}

/*!
  Returns the status of the buffer mode.

  \sa setDoubleBuffer()
 */
SbBool
SoQtGLWidget::isDoubleBuffer(void) const
{
  return THIS->glformat->doubleBuffer();
}

/*!
  Enables or disables quad buffer stereo.
*/
void
SoQtGLWidget::setQuadBufferStereo(const SbBool enable)
{
  if ( (enable && THIS->glformat->stereo()) ||
       (!enable && !THIS->glformat->stereo()) )
    return;

  THIS->glformat->setStereo(enable);
  // Rebuild if a GL widget has already been built.
  if (THIS->currentglwidget) this->buildGLWidget();
}

/*!
  Returns \c TRUE if quad buffer stereo is enabled for this widget.
*/

SbBool
SoQtGLWidget::isQuadBufferStereo(void) const
{
  return THIS->glformat->stereo();
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
  At the moment this is just a stub prototype for OIV compatibility.
*/

QWidget *
SoQtGLWidget::getNormalWidget(
  void ) const
{
  return this->getGLWidget();
}

/*!
  Returns widget associated with overlay planes, or \c NULL if no
  overlay planes are available.

  For the Qt toolkit, overlay planes is a feature of the QGLWidget,
  and not seen at a separate widget entity. So this call will just
  return the same widget reference as the SoQt::getGLWidget() call (if
  overlay planes are supported).
*/

QWidget *
SoQtGLWidget::getOverlayWidget(
  void ) const
{
  // Cast away this-pointer constness, as
  // SoQtGLWidget::getOverlayContext() is not defined as const.
  SoQtGLWidget * that = (SoQtGLWidget *)this;

  return that->getOverlayContext() ? this->getGLWidget() : NULL;
}

// *************************************************************************

/*!
  Sets the size of the GL canvas.
*/

void
SoQtGLWidget::setGLSize(
  const SbVec2s size )
{
  if (size == THIS->glSize) return;
#if SOQT_DEBUG && 0 // debug
  SoDebugError::postInfo( "SoQtGLWidget::setGLSize",
    "[invoked (%d, %d)]", size[0], size[1] );
#endif // debug
  THIS->glSize = size;
  if ( THIS->currentglwidget ) {
    int frame = this->isBorder() ? THIS->borderthickness : 0;
    THIS->currentglwidget->setGeometry( QRect( frame, frame, THIS->glSize[0], THIS->glSize[1] ) );
  }
} // setGLSize()

/*!
  Return the dimensions of the OpenGL canvas.
*/

SbVec2s
SoQtGLWidget::getGLSize(
  void ) const
{
  return THIS->glSize;
}

/*!
  Return the aspect ratio of the OpenGL canvas.
*/

float
SoQtGLWidget::getGLAspectRatio(
  void ) const
{
  return float(THIS->currentglwidget->width()) /
    float(THIS->currentglwidget->height());
}  // getGLAspectRatio()

/*!
  \fn void SoQtGLWidget::setGlxSize( const SbVec2s size )
  This function has been renamed to the more appropriate setGLSize.
  \sa setGLSize
*/

/*!
  \fn SbVec2s SoQtGLWidget::getGlxSize( void ) const
  This function has been renamed to the more appropriate getGLSize.
  \sa getGLSize
*/

/*!
  \fn float SoQtGLWidget::getGlxAspectRatio(void) const
  This function has been renamed to the more appropriate getGLAspectRatio.
  \sa getGLAspectRatio
*/

// *************************************************************************

/*!
  Returns a pointer to the Qt QGLWidget.
*/

QWidget *
SoQtGLWidget::getGLWidget(void) const
{
  return THIS->currentglwidget;
} // getGLWidget()


// *************************************************************************

/*!
  This is the method which gets called whenever we change which OpenGL
  widget is used.

  Should be overloaded in subclasses which directly or indirectly
  store the return value from the SoQtGLWidget::getGLWidget() method.

  \sa sizeChanged()
*/

void
SoQtGLWidget::widgetChanged( // virtual
  QWidget * w )
{
}

/*!
  Any events from the native window system that goes to the OpenGL
  canvas gets piped through this method.

  It is overloaded in the subclasses to catch user interaction with
  the render canvas in the viewers, aswell as forwarding relevant
  events to the scenegraph.
*/
void
SoQtGLWidget::processEvent(QEvent * anyevent)
{
  // Nothing is done here for the SoQtGLWidget, as realize, resize and
  // expose events are caught by explicitly attaching signal callbacks
  // to the widget.
}

// *************************************************************************

/*!
  This method calls make-current on the correct context and ups the lock
  level.
*/

void
SoQtGLWidget::glLockNormal(
  void )
{
  assert( THIS->currentglwidget != NULL );
  ((SoQtGLArea *)THIS->currentglwidget)->makeCurrent();
} // glLockNormal()

/*!
  This method drops the lock level.
*/

void
SoQtGLWidget::glUnlockNormal(
  void )
{
  // does nothing under Qt. Under BeOS the buffer needs to be unlocked
} // glUnlockNormal()

/*!
  FIXME: write doc
*/

void
SoQtGLWidget::glSwapBuffers(
  void )
{
  assert( THIS->currentglwidget != NULL );
  ((SoQtGLArea *)THIS->currentglwidget)->swapBuffers();
} // glSwapBuffers()

/*!
  Flush the current GL buffer. Simply calls glFlush().
*/
void 
SoQtGLWidget::glFlushBuffer(void)
{
  // might be called for both normal and overlay widgets
  glFlush();
}

/*!
  This method calls make-current on the correct context and ups the lock
  level.
*/

void
SoQtGLWidget::glLockOverlay(
  void )
{
  assert( THIS->currentglwidget != NULL );
  QGLFormat_makeOverlayCurrent((SoQtGLArea *)THIS->currentglwidget);
} // glLock()

/*!
  This method drops the lock level.
*/

void
SoQtGLWidget::glUnlockOverlay(
  void )
{
  // does nothing under Qt. Under BeOS the buffer needs to be unlocked  
} // glUnlock()

/*!
  FIXME: write doc
*/

void
SoQtGLWidget::gl_init( // slot
  void )
{
  this->initGraphic();
} // gl_init()

/*!
  FIXME: write doc
*/
void
SoQtGLWidget::gl_reshape( // slot
  int width,
  int height )
{
  fprintf(stderr,"gl_reshape\n");
  THIS->glSize = SbVec2s((short) width, (short) height);
  THIS->wasresized = TRUE;
} // gl_reshape()

/*!
  FIXME: write doc
*/
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
  if (THIS->wasresized) {
    this->sizeChanged(THIS->glSize);
    THIS->wasresized = FALSE;
  }

  if (!this->glScheduleRedraw()) {
    this->redraw();
  }
} // gl_exposed()

// *************************************************************************

/*!
  FIXME: write doc
*/
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

/*!
  Returns the normal GL context.
*/
const QGLContext * 
SoQtGLWidget::getNormalContext(void)
{
  QGLWidget * w = (QGLWidget*) this->getGLWidget();
  if (w) return w->context();
  return NULL;
}

/*!
  Returns the overlay GL context.
*/
const QGLContext * 
SoQtGLWidget::getOverlayContext(void)
{
  QGLWidget * w = (QGLWidget*) this->getGLWidget();
  if (w) { return QGLWidget_overlayContext(w); }
  return NULL;
}

/*!
  Returns the overlay transparent pixel.
*/
unsigned long 
SoQtGLWidget::getOverlayTransparentPixel(void)
{
  const QGLContext * ctx = this->getOverlayContext();
  if (ctx) {
    QColor color = QGLContext_overlayTransparentColor(ctx);
    return color.pixel();
  }
  return 0;
}

/*!
  Returns TRUE if the normal GL context is in RGBA mode.
  Return FALSE if color index mode is used.
*/
SbBool 
SoQtGLWidget::isRGBMode(void)
{
  return (SbBool) THIS->glformat->rgba();
}

/*!
  Renders the overlay scene graph. Default method is empty. Subclasses
  should overload this method.
*/
void 
SoQtGLWidget::redrawOverlay(void)
{
  // should be empty. It's up subclasses to do some work here
}

/*!
  Will be called when GL widget should initialize graphic, after
  the widget has been created. Default method enabled GL_DEPTH_TEST.
*/
void 
SoQtGLWidget::initGraphic(void)
{
  this->glLockNormal();
  // Need to set this explicitly when running on top of Open Inventor,
  // as it seems to have been forgotten there.
  // This code should be invoked from SoQtRenderArea::initGraphics()
  glEnable( GL_DEPTH_TEST );
  this->glUnlockNormal();
}

/*!
  Will be called after the overlay widget has been created, and subclasses
  should overload this to initialize overlay stuff.

  Default method does nothing.
*/
void 
SoQtGLWidget::initOverlayGraphic(void)
{
  // FIXME: can't see this function called from anywhere within SoQt.
  // That seems bogus. 20010831 mortene.
}

/*!
  Will be called every time the size of the GL widget changes.
*/
void
SoQtGLWidget::sizeChanged(
  const SbVec2s size )
{
} // sizeChanged()

/*!
  Will be called whenever scene graph needs to be redrawn().
  If this method return FALSE, redraw() will be called immediately.

  Default method simply returns FALSE. Overload this method to
  schedule a redraw and return TRUE if you're trying to do The Right
  Thing.  
*/
SbBool 
SoQtGLWidget::glScheduleRedraw(void)
{
  return FALSE;
}

/*!
  Should return TRUE if an overlay GL drawing area exists.
*/
SbBool 
SoQtGLWidget::hasOverlayGLArea(void) const 
{
  return this->getOverlayWidget() != NULL;
}

/*!
  Should return TRUE if a normal GL drawing area exists.
*/
SbBool 
SoQtGLWidget::hasNormalGLArea(void) const 
{
  return this->getNormalWidget() != NULL;
}

// *************************************************************************
